// MailsDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "checkmail.h"
#include "MailsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CMailsDlg 


CMailsDlg::CMailsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMailsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMailsDlg)
	m_bAlwaysOnTop = FALSE;
	//}}AFX_DATA_INIT
}


void CMailsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMailsDlg)
	DDX_Control(pDX, IDC_LIST_MAILS, m_listMails);
	DDX_Check(pDX, IDC_CHECK_TOP, m_bAlwaysOnTop);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMailsDlg, CDialog)
	//{{AFX_MSG_MAP(CMailsDlg)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnButtonOk)
	ON_BN_CLICKED(IDC_CHECK_TOP, OnCheckTop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CMailsDlg 

void CMailsDlg::OnButtonOk() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
    this->ShowWindow( SW_HIDE );
}

BOOL CMailsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen

    InitList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CMailsDlg::InitList()
{
	LVCOLUMN lvc;
    ZeroMemory( &lvc, sizeof(LVCOLUMN) );

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvc.iSubItem = 0;
	lvc.pszText  = _T("");
	lvc.cx       = 20;
	lvc.fmt      = LVCFMT_LEFT;
	m_listMails.InsertColumn(0,&lvc);

	lvc.iSubItem = 1;
	lvc.pszText  = _T("Name");
	lvc.cx       = 55;
	lvc.fmt      = LVCFMT_LEFT;
	m_listMails.InsertColumn(1,&lvc);

	lvc.iSubItem = 2;
	lvc.pszText  = _T("POP Server");
	lvc.cx       = 85;
	lvc.fmt      = LVCFMT_LEFT;
	m_listMails.InsertColumn(2,&lvc);

//	lvc.iSubItem = 3;
//	lvc.pszText  = _T("Subject");
//	lvc.cx       = 75;
//	lvc.fmt      = LVCFMT_LEFT;
//	m_listMails.InsertColumn(3,&lvc);

	lvc.iSubItem = 3;
	lvc.pszText  = _T("Mails");
	lvc.cx       = 40;
	lvc.fmt      = LVCFMT_RIGHT;
	m_listMails.InsertColumn(3,&lvc);

	lvc.iSubItem = 4;
	lvc.pszText  = _T("Size");
	lvc.cx       = 60;
	lvc.fmt      = LVCFMT_RIGHT;
	m_listMails.InsertColumn(4,&lvc);

	m_listMails.DeleteAllItems();
	m_listMails.SetExtendedStyle(LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}


void CMailsDlg::UpdateList( std::vector<CAccount> vAccount, std::vector<int> vMailCount, std::vector<int> vMailSize, std::vector<CString> vMailSubject )
{
	m_listMails.DeleteAllItems();

    LVITEM lvi;
    ZeroMemory( &lvi, sizeof(LVITEM) );

	lvi.mask      = LVIF_TEXT;
	lvi.iSubItem  = 0;
	lvi.stateMask = LVIS_STATEIMAGEMASK;
	lvi.state     = INDEXTOSTATEIMAGEMASK(1);
	lvi.iImage    = 1;

    CString csTmp = _T("");
	for(int i=0; i<vAccount.size(); i++) {
		lvi.iItem = i;
		csTmp.Format("%d", i+1);
        lvi.pszText = (PSTR) csTmp.GetBuffer(0);
        m_listMails.InsertItem(&lvi);
        m_listMails.SetItemText(i, 1, vAccount[i].csName );
	    m_listMails.SetItemText(i, 2, vAccount[i].csPop3 );
        //m_listMails.SetItemText(i, 3, vMailSubject[i] );
        if( vMailCount[i] >= 0 ) {
            csTmp.Format("%d", vMailCount[i] );
            m_listMails.SetItemText(i, 3, csTmp );
            if( vMailSize[i] < 1024 ) {
                if( vMailSize[i] == 0 ) {
                    csTmp.Format("%d", vMailSize[i] );
                }
                else {
                    csTmp.Format("%d Byte", vMailSize[i] );
                }
            }
            else {
                csTmp.Format("%d kB", vMailSize[i] / 1024 );
            }
            m_listMails.SetItemText(i, 4, csTmp );
        }
        else {
            m_listMails.SetItemText(i, 3, _T("-") );
            m_listMails.SetItemText(i, 4, _T("-") );
        }
	}

    UpdateData( FALSE );
}

void CMailsDlg::OnCheckTop() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
    UpdateData( TRUE );

  	CRect rect;
   	GetWindowRect( rect );

    if( m_bAlwaysOnTop ) {
        ::SetWindowPos( m_hWnd,
                        HWND_TOPMOST,
	    	            rect.left,
		                rect.top,
    		            rect.Width(),
	    	            rect.Height(),
		                SWP_SHOWWINDOW );
    }
    else {
        ::SetWindowPos( m_hWnd,
                        HWND_NOTOPMOST,
	    	            rect.left,
		                rect.top,
    		            rect.Width(),
	    	            rect.Height(),
		                SWP_SHOWWINDOW );
    }
}
