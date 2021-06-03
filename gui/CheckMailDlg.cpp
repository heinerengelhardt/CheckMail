// CheckMailDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CheckMail.h"
#include "CheckMailDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_ICON_NOTIFY      WM_USER+10
#define WM_WINDOW_SHOWN     WM_USER+20
#define WM_CONFIG_CHANGED   WM_USER+30

#define RUN_TIMER           WM_USER+40
#define ONLINE_CHECK_TIMER  WM_USER+50

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogfelddaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CHyperLink	m_staticHomepage;
	CHyperLink	m_staticEmail;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT

	m_staticEmail.SetURL("mailto:engelhardt@dvoid.org");
    m_staticEmail.ModifyLinkStyle(0, CHyperLink::StyleUseHover);

    m_staticHomepage.SetURL("http://www.dvoid.org");
    m_staticHomepage.ModifyLinkStyle(0, CHyperLink::StyleUseHover);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_LINK_HOMEPAGE, m_staticHomepage);
	DDX_Control(pDX, IDC_LINK_EMAIL, m_staticEmail);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckMailDlg Dialogfeld

CCheckMailDlg::CCheckMailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckMailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCheckMailDlg)
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    m_configDlg = new CConfigDlg( this );
    m_pMailsDlg = new CMailsDlg;
    m_pTrayIcon = new CTrayIcon;

    m_uiMin     = 60000;
}

void CCheckMailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCheckMailDlg)
	DDX_Control(pDX, IDCANCEL, m_buttonExit);
	DDX_Control(pDX, IDC_BUTTON_PREFERENCES, m_buttonPreferences);
	DDX_Control(pDX, ID_TOTRAY, m_buttonToTray);
	DDX_Control(pDX, IDC_LINK_EMAIL, m_linkEmail);
    DDX_Control(pDX, IDC_LINK_HOMEPAGE, m_linkHomepage);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCheckMailDlg, CDialog)
	//{{AFX_MSG_MAP(CCheckMailDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_TRAY_EXIT, OnTrayExit)
	ON_BN_CLICKED(IDC_BUTTON_PREFERENCES, OnButtonPreferences)
	ON_COMMAND(ID_TRAY_PREFERENCES, OnTrayPreferences)
	ON_COMMAND(ID_MAILER, OnMailer)
	ON_BN_CLICKED(ID_TOTRAY, OnButtonToTray)
	ON_COMMAND(ID_TRAY_RESTORE, OnTrayRestore)
	ON_WM_TIMER()
	ON_COMMAND(ID_TRAY_ENABLE, OnTrayEnable)
	ON_COMMAND(ID_TRAY_DISABLE, OnTrayDisable)
	ON_COMMAND(ID_TRAY_DETAILEDINFO, OnTrayDetailedInfo)
	ON_MESSAGE(WM_ICON_NOTIFY, OnTrayNotification)
    ON_MESSAGE(WM_WINDOW_SHOWN, OnDialogShown)
    ON_MESSAGE(WM_CONFIG_CHANGED, OnConfigChanged)
	ON_COMMAND(ID_TRAY_ABOUT, OnTrayAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckMailDlg Nachrichten-Handler


BOOL CCheckMailDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Hinzufügen des Menübefehls "Info..." zum Systemmenü.

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{	
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	
	// ZU ERLEDIGEN: Hier zusätzliche Initialisierung einfügen

	m_linkEmail.SetURL("mailto:engelhardt@dvoid.org");
    m_linkEmail.ModifyLinkStyle(0, CHyperLink::StyleUseHover);

    m_linkHomepage.SetURL("http://www.dvoid.org");
    m_linkHomepage.ModifyLinkStyle(0, CHyperLink::StyleUseHover);

    ConvertToNewIniFile();

    m_configDlg->Create( IDD_CONFIG, this );
    m_pMailsDlg->Create( IDD_MAILS, this );
    m_pTrayIcon->Create( this,
                         WM_ICON_NOTIFY,
                         TEXT("CheckMail"),
                         AfxGetApp()->LoadIcon(IDI_NO_MAIL),
                         IDR_MENU_TRAY );

    m_config                 = m_configDlg->GetConfig();
    m_configDlg->m_pTrayIcon = m_pTrayIcon;

    if( !m_configDlg->ShallMinimize() ) {
        ::PostMessage( m_hWnd, WM_WINDOW_SHOWN, 0, 0 );
    }

    SetTimer( RUN_TIMER, m_uiMin * m_config->m_uiMinutes, NULL );
    SetTimer( ONLINE_CHECK_TIMER, static_cast<UINT>(5000), NULL );

    StartCheckMailThread();

	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

void CCheckMailDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CCheckMailDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, während der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CCheckMailDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCheckMailDlg::OnCancel() 
{
	// TODO: Zusätzlichen Bereinigungscode hier einfügen

    m_pTrayIcon->RemoveIcon();

    if( m_pTrayIcon ) {
        delete m_pTrayIcon;
    }

    if( m_configDlg ) {
        delete m_configDlg;
    }

    if( m_config ) {
        delete m_config;
    }

    if( m_pMailsDlg ) {
        delete m_pMailsDlg;
    }

	CDialog::OnCancel();

    if( this ) {
        delete this;
    }
}

void CCheckMailDlg::OnTrayExit() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen

    OnCancel();
}

void CCheckMailDlg::OnButtonPreferences() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_configDlg->ShowWindow(SW_SHOW);
}

void CCheckMailDlg::OnTrayPreferences() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	m_configDlg->ShowWindow(SW_SHOW);
}

void CCheckMailDlg::OnMailer() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	WinExec(m_configDlg->m_editMailer, SW_SHOW);
}

LRESULT CCheckMailDlg::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
    // Delegate all the work back to the default implementation in CTrayIcon.
    return m_pTrayIcon->OnTrayNotification(wParam, lParam);
}

void CCheckMailDlg::OnButtonToTray() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	this->ShowWindow( SW_HIDE );
}

void CCheckMailDlg::OnTrayRestore() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	this->ShowWindow( SW_SHOW );
}


LRESULT CCheckMailDlg::OnDialogShown(WPARAM wParam, LPARAM lParam)
{
    this->ShowWindow( SW_SHOW );
    return 0;
}

void CCheckMailDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	// CDialog::OnTimer(nIDEvent);
    switch( nIDEvent ) {

        case RUN_TIMER:             StartCheckMailThread();
                                    break;

        case ONLINE_CHECK_TIMER:    CheckOnlineStatus();
                                    break;

        default:                    break;
    }
}

void CCheckMailDlg::CheckOnlineStatus()
{
    return;
}

void CCheckMailDlg::StartCheckMailThread()
{
    CCheck* check = new CCheck(m_config, m_pTrayIcon);
    check->m_pMailsDlg = m_pMailsDlg;

    _beginthread( check->StartCheckMailThread, (UINT) 0, (PVOID) check );
}

LRESULT CCheckMailDlg::OnConfigChanged(WPARAM wParam, LPARAM lParam)
{
    KillTimer(RUN_TIMER);
    SetTimer(RUN_TIMER, m_uiMin * m_config->m_uiMinutes, NULL);

    StartCheckMailThread();
    
    return 0;
}

void CCheckMailDlg::OnTrayEnable() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
    KillTimer(RUN_TIMER);
    SetTimer(RUN_TIMER, m_uiMin * m_config->m_uiMinutes, NULL);

    StartCheckMailThread();
	
}

void CCheckMailDlg::OnTrayDisable() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
    m_pTrayIcon->SetIcon(IDI_DISABLED);
    m_pTrayIcon->SetTooltipText(_T("Disabled"));
    KillTimer(RUN_TIMER);
}

void CCheckMailDlg::OnTrayDetailedInfo() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
      
    m_pMailsDlg->ShowWindow( SW_SHOW );
}


void CCheckMailDlg::OnTrayAbout() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	
    CAboutDlg adlg;
    adlg.DoModal();
}

void CCheckMailDlg::ConvertToNewIniFile()
{
    std::vector<CAccount> vAccount;
    int     iAccounts       = 0;
    CString editWave        = _T("");
    CString editMailer      = _T("");
    CString editSound       = _T("");
    int     editMinutes     = 1;
    BOOL    checkNotify     = 0;
    BOOL    checkTray       = 0;
    BOOL    checkPopup      = 0;
    int     radioForeground = 0;
    int     radioFive       = 0;
    LPCTSTR szFile          = _T("checkmail.ini");

/* Check, if there are any old files */
    CHAR szWindowsDir[MAX_PATH] = {"\0"};
    GetWindowsDirectory(szWindowsDir, MAX_PATH);

    CHAR szCmdataFileName[] = _T("\\cmdata.ini");
    CHAR szCmailFileName[]  = _T("\\checkmail.ini");
    CHAR szCmdataFile[MAX_PATH] = {"\0"};
    CHAR szCmailFile[MAX_PATH] = {"\0"};

    strcpy(szCmdataFile, szWindowsDir);
    strcat(szCmdataFile, szCmdataFileName);

    strcpy(szCmailFile, szWindowsDir);
    strcat(szCmailFile, szCmailFileName);

    CFile CMdataFile;
    if( !CMdataFile.Open(szCmdataFile, CFile::modeRead) ) {
        return;
    }
    CMdataFile.Close();

    CFile CMailFile;
    if( !CMailFile.Open(szCmailFile, CFile::modeRead) ) {
        return;
    }
    CMailFile.Close();

/* Read old Ini File*/
    CHAR szTmp[MAX_PATH] = {"\0"};
    GetPrivateProfileString(_T("CheckMail"), _T("Accounts"), "", szTmp, MAX_PATH, szFile);
    iAccounts = atoi(szTmp);
    GetPrivateProfileString(_T("CheckMail"), _T("Sound"), "", szTmp, MAX_PATH, szFile);
    editWave = szTmp;
    GetPrivateProfileString(_T("CheckMail"), _T("Mailer"), "", szTmp, MAX_PATH, szFile);
    editMailer = szTmp;
    GetPrivateProfileString(_T("CheckMail"), _T("Minutes"), "", szTmp, MAX_PATH, szFile);
    editMinutes = atoi(szTmp);
    GetPrivateProfileString(_T("CheckMail"), _T("Notify"), "", szTmp, MAX_PATH, szFile);
    checkNotify = atoi(szTmp);
    GetPrivateProfileString(_T("CheckMail"), _T("ToTray"), "", szTmp, MAX_PATH, szFile);
    checkTray = atoi(szTmp);
    GetPrivateProfileString(_T("CheckMail"), _T("Five"), "", szTmp, MAX_PATH, szFile);
    radioFive = atoi(szTmp);

    vAccount.resize(iAccounts);

    CString csTmp = _T("");
    for(int i=0; i<iAccounts; i++) {
        csTmp.Format(_T("Account%d"), i+1);
        GetPrivateProfileString(csTmp, _T("Name"), "", szTmp, MAX_PATH, szFile);
        vAccount[i].csName = szTmp;
        GetPrivateProfileString(csTmp, _T("Pop3"), "", szTmp, MAX_PATH, szFile);
        vAccount[i].csPop3 = szTmp;
    }

    if(editMinutes < 1) {
        editMinutes = 1;
    }

/* Decryption */
    CHAR szWinDir[MAX_PATH] = {"\0"};
    GetWindowsDirectory(szWinDir, MAX_PATH);

    CHAR szCurFile[] = _T("\\cmdata.ini");
    CHAR szSecFile[MAX_PATH] = {"\0"};

    strcpy(szSecFile, szWinDir);
    strcat(szSecFile, szCurFile);

    try {
        CFile* pfl = new CFile(szSecFile, CFile::modeRead);

        iAccounts = vAccount.size();
    
        try {
            CArchive ar( pfl, CArchive::load );

            CString csLogTmp = _T("");
            CString csLogPwd = _T("");
            for(int z=0; z<iAccounts; z++) {
                ar >> csLogTmp;
                ar >> csLogPwd;

                csLogTmp.Replace("  ::  ", "a");
                csLogPwd.Replace("  ::  ", "a");

                csLogTmp.Replace("{l}[m]", "_");
                csLogPwd.Replace("{l}[m]", "_");

                csLogTmp.Replace("#'(7)", "i");
                csLogPwd.Replace("#'(7)", "i");

                csLogTmp.Replace("=!AA))=", "p");
                csLogPwd.Replace("=!AA))=", "p");

                csLogTmp.Replace("%$%R%qq%", "d");
                csLogPwd.Replace("%$%R%qq%", "d");

                csLogTmp.Replace("?=/", "e");
                csLogPwd.Replace("?=/", "e");

                csLogTmp.Replace("§$§", ".");
                csLogPwd.Replace("§$§", ".");

                csLogTmp.Replace("~2~", "@");
                csLogPwd.Replace("~2~", "@");

                csLogTmp.MakeReverse();
                csLogPwd.MakeReverse();

                vAccount[z].csLogin = csLogTmp;
                vAccount[z].csPassword = csLogPwd;
            }
            ar.Close();
        }
        catch(...) {}

        if( pfl ) {
            delete pfl;
        }
    }
    catch(...) {}

/* Write new Ini File */
    iAccounts = vAccount.size();

    LPCTSTR lpszIniFileName = _T("checkmail.ini");
    TCHAR szPathName[_MAX_PATH];
    ::GetModuleFileName(NULL, szPathName, _MAX_PATH);
    LPTSTR pszFileName = _tcsrchr(szPathName, '\\') + 1;
    *pszFileName = '\0';
    CString csWorkingDirectory = static_cast<CString>(szPathName);
    CString csIniFilee = csWorkingDirectory + static_cast<CString>(lpszIniFileName);
    LPCTSTR lpszIniFile = csIniFilee.GetBuffer(0);

    CFile file;
    if( file.Open(lpszIniFile, CFile::modeRead) ) {
        file.Close();
        file.Remove(lpszIniFile);
    }

    CString csTemp = _T("");
    csTemp.Format(_T("%d"), iAccounts);
    WritePrivateProfileString(_T("CheckMail"), _T("Accounts"), csTemp, lpszIniFile);
    WritePrivateProfileString(_T("CheckMail"), _T("Sound"), editWave, lpszIniFile);
    WritePrivateProfileString(_T("CheckMail"), _T("Mailer"), editMailer, lpszIniFile);
    csTemp.Format(_T("%d"), editMinutes);
    WritePrivateProfileString(_T("CheckMail"), _T("Minutes"), csTemp, lpszIniFile);
    csTemp.Format(_T("%d"), checkNotify);
    WritePrivateProfileString(_T("CheckMail"), _T("Notify"), csTemp, lpszIniFile);
    csTemp.Format(_T("%d"), checkTray);
    WritePrivateProfileString(_T("CheckMail"), _T("ToTray"), csTemp, lpszIniFile);
    csTemp.Format(_T("%d"), checkPopup);
    WritePrivateProfileString(_T("CheckMail"), _T("PopUp"), csTemp, lpszIniFile);
    csTemp.Format(_T("%d"), radioFive);
    WritePrivateProfileString(_T("CheckMail"), _T("ShowFive"), csTemp, lpszIniFile);
    csTemp.Format(_T("%d"), radioForeground);
    WritePrivateProfileString(_T("CheckMail"), _T("ForegroundWindow"), csTemp, lpszIniFile);

    CString csT = _T("");
    for(int j=0; j<iAccounts; j++) {
        csTemp.Format(_T("Account%d"), j+1);
        WritePrivateProfileString(csTemp, _T("Name"), vAccount[j].csName, lpszIniFile);
        WritePrivateProfileString(csTemp, _T("Pop3"), vAccount[j].csPop3, lpszIniFile);
        vAccount[j].csLogin.MakeReverse();
        LPSTR lpszText = vAccount[j].csLogin.GetBuffer(0);
        int len = vAccount[j].csLogin.GetLength();
        CHAR szA = 0;
        for(int k=0; k<len; k++) {
            if( k%3 ) {
                szA = lpszText[k] - 2;
            }
            else if( k%2 ) {
                szA = lpszText[k] + 3;
            }
            else {
                szA = lpszText[k] - 1;
            }

            lpszText[k] = szA;
        }
        csT = static_cast<CString>(lpszText);
        WritePrivateProfileString(csTemp, _T("Login"), csT, lpszIniFile);
        vAccount[j].csPassword.MakeReverse();
        lpszText = vAccount[j].csPassword.GetBuffer(0);
        len = vAccount[j].csPassword.GetLength();
        szA = 0;
        for(int l=0; l<len; l++) {
            if( l%3 ) {
                szA = lpszText[l] - 2;
            }
            else if( l%2 ) {
                szA = lpszText[l] + 3;
            }
            else {
                szA = lpszText[l] - 1;
            }

            lpszText[l] = szA;
        }
        csT = static_cast<CString>(lpszText);
        WritePrivateProfileString(csTemp, _T("Password"), csT, lpszIniFile);
    }

    CMdataFile.Close();
    CMdataFile.Remove(szCmdataFile);

    CMailFile.Close();
    CMailFile.Remove(szCmailFile);

    return;
}
