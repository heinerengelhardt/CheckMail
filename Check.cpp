// Check.cpp: Implementierung der Klasse CCheck.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Check.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CCheck::CCheck(CConfig* config, CTrayIcon* trayicon)
    : m_config( config ), m_trayIcon( trayicon )
{
    m_hNoMailIcon       = AfxGetApp()->LoadIcon( IDI_NO_MAIL );
    m_hNewMailIcon      = AfxGetApp()->LoadIcon( IDI_NEW_MAIL );
    m_hCheckMailIcon    = AfxGetApp()->LoadIcon( IDI_CHECK_MAIL );

    m_iMailSize = 0;
    m_vAccount  = m_config->GetAccounts();
}

CCheck::~CCheck()
{

}

void CCheck::StartCheckMailThread( PVOID pParam )
{
    CCheck* chk = (CCheck*) pParam;  
    chk->CheckMails();
    if ( chk ) {
        delete chk;
    }
    _endthread();
}

void CCheck::CheckMails()
{  
    CString csHost      = _T("");
    CString csUser      = _T("");
    CString csPwd       = _T("");
    CString csToolTip   = _T("");
    CString csTmp       = _T("");
    UINT uiToolTipStyle = SINGLE_LINE;
    int iAccounts       = 0;
    int iNumberOfMails  = 0;
    int iTotalMails     = 0;
    static int iSum     = 0;
    BOOL bOnline        = FALSE;
    CHAR szToolTip[100] = {"\0"};

    iAccounts  = m_vAccount.size();
    m_vRevievedMails.resize( iAccounts );
    m_vMailSize.resize( iAccounts );
    m_vMailSubject.resize( iAccounts );

    for(int z=0; z<iAccounts; z++) {
        m_vRevievedMails[z] = 0;
        m_vMailSize[z] = 0;
        m_vMailSubject[z] = _T("");
    }

    uiToolTipStyle = GetToolTipStyleByOS();
    m_trayIcon->SetIcon( m_hCheckMailIcon );

    for(int i=0; i<iAccounts; i++) {
        csHost = m_vAccount[i].csPop3;
        csUser = m_vAccount[i].csLogin;
        csPwd  = m_vAccount[i].csPassword;

        iNumberOfMails = CheckSpecificMailbox(csHost, csUser, csPwd, i);
        m_vRevievedMails[i] = iNumberOfMails;
    }

    for(int k=0; k<iAccounts; k++) {
        if ( m_vRevievedMails[k] >= 0 ) {
            iTotalMails += m_vRevievedMails[k];
        }
    }

    if( m_trayIcon->GetIcon() == AfxGetApp()->LoadIcon( IDI_DISABLED ) ) {
        m_trayIcon->SetIcon(IDI_DISABLED);
        m_trayIcon->SetTooltipText(_T("Disabled"));

        iSum = iTotalMails = 0;

        for(int k=0; k<iAccounts; k++) {
            m_vRevievedMails[k] = -1;
        }
    }
    else {
        if( !m_config->m_iFive ) {
            int iTTc = (iAccounts > 5) ? 5 : iAccounts;
            for(int j=0; j<iTTc; j++) {
                csToolTip += m_vAccount[j].csName;
                csToolTip += _T(": ");
                if ( m_vRevievedMails[j] >= 0 ) {
                    csTmp.Format(_T("%d"), m_vRevievedMails[j]);
                }
                else {
                    csTmp.Format(_T("-"));
                }
                csToolTip += csTmp;

                if( j<iTTc-1 ) {
                    if( uiToolTipStyle == MULTI_LINE ) {
                        csToolTip += _T("\n");
                    }
                    else {
                        csToolTip += _T("  ");
                    }
                }
            }
            strcpy(szToolTip, csToolTip);
            m_trayIcon->SetTooltipText(szToolTip);
        }
        else {
            if( uiToolTipStyle == MULTI_LINE ) {
                csToolTip.Format(_T("Accounts: %d\nTotal mails: %d\nTotel size: %d kB"), iAccounts, iTotalMails, m_iMailSize/1024);
            }
            else {
                csToolTip.Format(_T("Accounts: %d  Total mails: %d  Totel size: %ud kB"), iAccounts, iTotalMails, m_iMailSize/1024);
            }
            strcpy(szToolTip, csToolTip);
            m_trayIcon->SetTooltipText(szToolTip);
        }

        m_pMailsDlg->UpdateList( m_vAccount, m_vRevievedMails, m_vMailSize, m_vMailSubject );

        if( iTotalMails > 0 ) {
            m_trayIcon->SetIcon(m_hNewMailIcon);
        }
        else {
            m_trayIcon->SetIcon(m_hNoMailIcon);
        }

        if( iTotalMails > iSum ) {
            if( m_config->m_bPlaySound ) {
                PlaySound( m_config->m_csWafeFile, NULL, SND_FILENAME | SND_ASYNC );
            }

            if( m_config->m_bPopup ) {
                m_pMailsDlg->ShowWindow( SW_SHOW );
                if( !m_config->m_iForeground ) {
                    m_pMailsDlg->SetForegroundWindow();
                }
            }
        }
        
        iSum = iTotalMails;
    }
}

void CCheck::SocketThreadInit() {
    #ifndef _AFXDLL
    #define _AFX_SOCK_THREAD_STATE AFX_MODULE_THREAD_STATE
    #define _afxSockThreadState AfxGetModuleThreadState()

    _AFX_SOCK_THREAD_STATE* pState = _afxSockThreadState;
    if (pState->m_pmapSocketHandle == NULL)
       pState->m_pmapSocketHandle = new CMapPtrToPtr;
    if (pState->m_pmapDeadSockets == NULL)
       pState->m_pmapDeadSockets = new CMapPtrToPtr;
    if (pState->m_plistSocketNotifications == NULL)
       pState->m_plistSocketNotifications = new CPtrList;

    #endif
}

BOOL CCheck::IsInternetConnected()
{
    int nCheck = 0;
    CSocket m_Server;
    HKEY hKey;
    DWORD dwDial, dwDialType = REG_DWORD, dwDialSize = 4;
    DWORD dwNew = 0;
    BOOL bResult = true;
 
    if( RegOpenKeyEx ( HKEY_CURRENT_USER,
                        _T("Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings"),
                        0, KEY_QUERY_VALUE | KEY_SET_VALUE, &hKey) != ERROR_SUCCESS) {}
    // We cannot find the key. Handle this situation or just continue
                                                
    if( RegQueryValueEx( hKey, _T("EnableAutodial"), NULL, &dwDialType,
        (BYTE *) &dwDial, &dwDialSize ) != ERROR_SUCCESS ) {}
    // We cannot find the value. Handle it.

    if( dwDial ) { // We need to change the value, in order to make
                   // a dialup window not to show up.
  
        if ( (nCheck = RegSetValueEx( hKey, _T("EnableAutodial"), NULL,
            dwDialType, (BYTE *) &dwNew, dwDialSize )) != ERROR_SUCCESS) {}
        // Failed? We shouldn't get here. You decide how to handle it
    }
  
 
    if ( !m_Server.Create() ) {                                                       
        // m_sError = _T( "Unable to create the socket." );
        bResult = FALSE;
    }   

    // You can use www.microsoft.com in order to check whether DNS is available
    // or numeric IP otherwise 
    else if ( !m_Server.Connect( _T("www.microsoft.com"), 80 ) ) {     //  207.46.130.150
        //m_sError = _T( "Unable to connect to server" );        
        m_Server.Close();
        bResult = FALSE;
    }
 
 
    if ( dwDial ) {
        if ( (nCheck = RegSetValueEx( hKey, _T("EnableAutodial"), NULL,
            dwDialType, (BYTE *) &dwDial, dwDialSize )) != ERROR_SUCCESS) {}
        // Failed? We shouldn't get it. You decide how to handle this.
    }
 
    RegCloseKey( hKey );
    return bResult;
}

UINT CCheck::GetToolTipStyleByOS()
{
/*
    [OS          = major.minor.build; platform id]

    Win 95       = 4.00.950;          VER_PLATFORM_WIN32_WINDOWS
    Win 95 OSR 2 = 4.00.1111;         VER_PLATFORM_WIN32_WINDOWS
    Win 98       = 4.10.1998;         VER_PLATFORM_WIN32_WINDOWS
    Win 98 SE    = 4.10.2222;         VER_PLATFORM_WIN32_WINDOWS
    Win Me       = 4.90.3000;         VER_PLATFORM_WIN32_WINDOWS

    Win NT4      = 4.00.1381;         VER_PLATFORM_WIN32_NT
    Win 2000     = 5.00.2195;         VER_PLATFORM_WIN32_NT
    Win XP       = 5.01.(??);         VER_PLATFORM_WIN32_NT
*/

    OSVERSIONINFO os;
    ZeroMemory(&os, sizeof(os));
    os.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&os);

    if( os.dwMajorVersion < (DWORD) 5 ) {
        return SINGLE_LINE;
    }
    else {
        return MULTI_LINE;
    }
}

int CCheck::CheckSpecificMailbox(CString csHost, CString csUser, CString csPwd, int iNumber)
{
    int iNumberOfMails = -1;
    BOOL bConOk = FALSE;

    SocketThreadInit();
    CPop pop;

    bConOk = pop.Connect(csHost, csUser, csPwd);

    if( bConOk ) {
        pop.Statistics();
        iNumberOfMails = pop.GetNumberOfMails();
        m_vMailSize[iNumber] = (UINT) pop.GetTotalMailSize();
        m_vMailSubject[iNumber] = pop.GetSubject();
        m_iMailSize += m_vMailSize[iNumber];
    }

    pop.Disconnect();

    return ( (iNumberOfMails < 0) ? (-1) : (iNumberOfMails) );
}
