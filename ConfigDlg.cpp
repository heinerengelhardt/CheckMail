// ConfigDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CheckMail.h"
#include "ConfigDlg.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_CONFIG_CHANGED   WM_USER+30

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CConfigDlg 


CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigDlg)
	m_editAccount = _T("");
	m_editLogin = _T("");
	m_editMinutes = 1;
	m_editPassword = _T("");
	m_editPop3 = _T("");
    m_editMailer = _T("");
	m_editWave = _T("");
	m_radioFive = -1;
	m_checkTray = FALSE;
	m_checkNotify = FALSE;
	m_checkPopup = FALSE;
	m_radioForeground = -1;
	//}}AFX_DATA_INIT
    
    m_config = new CConfig;
    ASSERT(pParent);
}


void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	DDX_Control(pDX, IDC_BUTTON_APPLY, m_buttonApply);
	DDX_Control(pDX, IDC_SPIN_MINUTES, m_spinMinutes);
	DDX_Control(pDX, IDC_BUTTON_CHOOSE_FILE, m_buttonChooseFile);
    DDX_Control(pDX, IDC_BUTTON_CHOOSE_MAILER, m_buttonChooseMailer);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_buttonDelete);
	DDX_Control(pDX, IDC_BUTTON_CHANGE, m_buttonChange);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_buttonAdd);
	DDX_Control(pDX, IDC_LIST_ACCOUNTS, m_listAccounts);
	DDX_Text(pDX, IDC_EDIT_ACCOUNT, m_editAccount);
	DDV_MaxChars(pDX, m_editAccount, 100);
	DDX_Text(pDX, IDC_EDIT_LOGIN, m_editLogin);
	DDV_MaxChars(pDX, m_editLogin, 100);
	DDX_Text(pDX, IDC_EDIT_MINUTES, m_editMinutes);
	DDV_MinMaxUInt(pDX, m_editMinutes, 1, 100);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_editPassword);
	DDV_MaxChars(pDX, m_editPassword, 100);
	DDX_Text(pDX, IDC_EDIT_POP3, m_editPop3);
	DDV_MaxChars(pDX, m_editPop3, 100);
    DDX_Text(pDX, IDC_EDIT_MAILER, m_editMailer);
	DDV_MaxChars(pDX, m_editMailer, 1000);
	DDX_Text(pDX, IDC_EDIT_WAVE, m_editWave);
	DDV_MaxChars(pDX, m_editWave, 1000);
	DDX_Radio(pDX, IDC_RADIO_FIVE, m_radioFive);
	DDX_Check(pDX, IDC_CHECK_TRAY, m_checkTray);
	DDX_Check(pDX, IDC_CHECK_NOTIFY, m_checkNotify);
	DDX_Check(pDX, IDC_CHECK_POPUP, m_checkPopup);
	DDX_Radio(pDX, IDC_RADIO_FOREGROUND, m_radioForeground);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigDlg)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MINUTES, OnDeltaposSpinMinutes)
	ON_EN_KILLFOCUS(IDC_EDIT_MINUTES, OnKillfocusEditMinutes)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, OnButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ACCOUNTS, OnClickListAccounts)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_FILE, OnButtonChooseFile)
    ON_BN_CLICKED(IDC_BUTTON_CHOOSE_MAILER, OnButtonChooseMailer)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_CHECK_TRAY, OnCheckTray)
	ON_BN_CLICKED(IDC_CHECK_NOTIFY, OnCheckNotify)
	ON_BN_CLICKED(IDC_RADIO_FIVE, OnRadioFive)
	ON_BN_CLICKED(IDC_RADIO_ALL, OnRadioAll)
	ON_EN_CHANGE(IDC_EDIT_WAVE, OnChangeEditWave)
	ON_EN_CHANGE(IDC_EDIT_MAILER, OnChangeEditMailer)
	ON_BN_CLICKED(IDC_CHECK_POPUP, OnCheckPopup)
	ON_BN_CLICKED(IDC_RADIO_FOREGROUND, OnRadioForeground)
	ON_BN_CLICKED(IDC_RADIO_BACKGROUND, OnRadioBackground)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CConfigDlg 

BOOL CConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen

	m_buttonChooseFile.SetIcon( IDI_EXPLORE );
    m_buttonChooseMailer.SetIcon( IDI_EXPLORE );

    m_radioFive       = 0;
    m_radioForeground = 0;

    InitList();
    ReadIniFile();
    UpdateList();

    if( (m_editMinutes < 1) || (m_editMinutes > 100) ) {
        m_editMinutes = 1;
    }

    if( m_checkNotify == TRUE ) {
        m_checkNotify = TRUE;
        GetDlgItem( IDC_EDIT_WAVE )->EnableWindow( TRUE );
    }
    else {
        m_checkNotify = FALSE;
        GetDlgItem( IDC_EDIT_WAVE )->EnableWindow( FALSE );
    }

    if( m_checkPopup == TRUE ) {
        m_checkPopup = TRUE;
        GetDlgItem( IDC_RADIO_FOREGROUND )->EnableWindow( TRUE );
        GetDlgItem( IDC_RADIO_BACKGROUND )->EnableWindow( TRUE );
    }
    else {
        m_checkPopup = FALSE;
        GetDlgItem( IDC_RADIO_FOREGROUND )->EnableWindow( FALSE );
        GetDlgItem( IDC_RADIO_BACKGROUND )->EnableWindow( FALSE );
    }

    m_buttonApply.EnableWindow(FALSE);
    m_buttonDelete.EnableWindow(FALSE);
    m_buttonChange.EnableWindow(FALSE);

    UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CConfigDlg::InitList()
{
	LVCOLUMN lvc;
    ZeroMemory( &lvc, sizeof(LVCOLUMN) );

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvc.iSubItem = 0;
	lvc.pszText  = _T("");
	lvc.cx       = 20;
	lvc.fmt      = LVCFMT_LEFT;
	m_listAccounts.InsertColumn(0,&lvc);

	lvc.iSubItem = 1;
	lvc.pszText  = _T("Name");
	lvc.cx       = 55;
	lvc.fmt      = LVCFMT_LEFT;
	m_listAccounts.InsertColumn(1,&lvc);

	lvc.iSubItem = 2;
	lvc.pszText  = _T("POP3");
	lvc.cx       = 85;
	lvc.fmt      = LVCFMT_LEFT;
	m_listAccounts.InsertColumn(2,&lvc);

	m_listAccounts.DeleteAllItems();
	m_listAccounts.SetExtendedStyle(LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}

void CConfigDlg::OnDeltaposSpinMinutes(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
    
    UpdateData(TRUE);
    
    if( pNMUpDown->iDelta == -1 && m_editMinutes < 100 ) {
        m_editMinutes++;
    }

    if( pNMUpDown->iDelta == 1 && m_editMinutes > 1 ) {
        m_editMinutes--;
    }

    m_buttonApply.EnableWindow(TRUE);
    UpdateData(FALSE);
    
	*pResult = 0;
}

void CConfigDlg::OnKillfocusEditMinutes() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
    UpdateData(TRUE);

    if( m_editMinutes < 1 ) {
        m_editMinutes = 1;
    }

    if( m_editMinutes > 100 ) {
        m_editMinutes = 100;
    }

    m_buttonApply.EnableWindow(TRUE);
    UpdateData(FALSE);
}

void CConfigDlg::OnButtonAdd() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

    UpdateData(TRUE);

    if( m_editAccount == _T("") || m_editPop3 == _T("") || m_editLogin == _T("") || m_editPassword == _T("") ) {
        MessageBox(_T("All Fields are required to add an Account!"), _T("Add Account"), MB_OK | MB_ICONEXCLAMATION);
        return;
    }

    int count = m_config->InsertAccount(m_editAccount, m_editPop3, m_editLogin, m_editPassword);

    LVITEM lvi;
    ZeroMemory( &lvi, sizeof(LVITEM) );
	
	lvi.mask      = LVIF_TEXT | LVIF_IMAGE;
	lvi.iSubItem  = 0;
	lvi.stateMask = LVIS_STATEIMAGEMASK;
	lvi.state     = INDEXTOSTATEIMAGEMASK(1);
	lvi.iImage    = 1;

    CString csNr;
	lvi.iItem = count;
	csNr.Format("%d", count);
    lvi.pszText = (PSTR)csNr.GetBuffer(0);
    m_listAccounts.InsertItem(&lvi);
    m_listAccounts.SetItemText(count-1, 1, m_editAccount);
    m_listAccounts.SetItemText(count-1, 2, m_editPop3);

    m_editAccount  = _T("");
    m_editPop3     = _T("");
    m_editLogin    = _T("");
    m_editPassword = _T("");

    m_buttonApply.EnableWindow(TRUE);
    UpdateData(FALSE);
}

void CConfigDlg::OnButtonChange() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
    UpdateData(TRUE);

    POSITION pos;
    ZeroMemory( &pos, sizeof(POSITION) );

    pos = m_listAccounts.GetFirstSelectedItemPosition();
    if( (UINT)pos == 0 ) {
        return;
    }

    m_config->ChangeAccount((UINT)pos, m_editAccount, m_editPop3, m_editLogin, m_editPassword);

    UpdateList();

    m_editAccount  = _T("");
    m_editLogin    = _T("");
    m_editPassword = _T("");
    m_editPop3     = _T("");

    m_buttonDelete.EnableWindow(FALSE);
    m_buttonChange.EnableWindow(FALSE);
    m_buttonApply.EnableWindow(TRUE);

    UpdateData(FALSE);	
}

void CConfigDlg::OnButtonDelete() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
    UpdateData(TRUE);

    m_editAccount  = _T("");
    m_editPop3     = _T("");
    m_editLogin    = _T("");
    m_editPassword = _T("");

    POSITION pos;
    ZeroMemory( &pos, sizeof(POSITION) );

    pos = m_listAccounts.GetFirstSelectedItemPosition();
    if( (UINT)pos == 0 ) {
        return;
    }

    m_listAccounts.DeleteItem((UINT)pos-1);
    m_config->DeleteAccount((UINT)pos);

    UpdateList();

    m_buttonApply.EnableWindow(TRUE);
    m_buttonDelete.EnableWindow(FALSE);
    m_buttonChange.EnableWindow(FALSE);

    UpdateData(FALSE);
}

void CConfigDlg::OnClickListAccounts(NMHDR* pNMHDR, LRESULT* pResult) 
{
    // TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
    POSITION pos;
    ZeroMemory( &pos, sizeof(POSITION) );

    pos = m_listAccounts.GetFirstSelectedItemPosition();
    if( (UINT)pos == 0 ) {
        m_editAccount  = _T("");
        m_editLogin    = _T("");
        m_editPassword = _T("");
        m_editPop3     = _T("");
        m_buttonChange.EnableWindow(FALSE);
        m_buttonDelete.EnableWindow(FALSE);
        UpdateData(FALSE);
        return;
    }

    std::vector<CAccount> vAccount = m_config->GetAccounts();

    m_editAccount  = vAccount[(UINT)pos-1].csName;
    m_editPop3     = vAccount[(UINT)pos-1].csPop3;
    m_editLogin    = vAccount[(UINT)pos-1].csLogin;
    m_editPassword = vAccount[(UINT)pos-1].csPassword;

    m_buttonChange.EnableWindow(TRUE);
    m_buttonDelete.EnableWindow(TRUE);

    UpdateData(FALSE);

	*pResult = 0;
}

void CConfigDlg::OnButtonChooseFile() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	OPENFILENAME ofn;
	ZeroMemory( &ofn, sizeof(OPENFILENAME) );

	CHAR szNdir[MAX_PATH]  = {"\0"};
    CHAR szNname[MAX_PATH] = {"\0"};

	ofn.lStructSize     = sizeof(OPENFILENAME);
	ofn.hwndOwner       = m_hWnd;
	ofn.hInstance       = AfxGetInstanceHandle();
	ofn.lpstrFile       = szNname;
	ofn.nMaxFile        = sizeof(szNname);
	ofn.lpstrFilter     = (LPCTSTR)_T("Wave Audio (*.wav)\0*.WAV\0");
	ofn.nFilterIndex    = 1;
	ofn.lpstrFileTitle  = NULL;
	ofn.lpstrTitle      = NULL;
	ofn.nMaxFileTitle   = 0;
	ofn.lpstrInitialDir = szNdir;
	ofn.Flags           = OFN_PATHMUSTEXIST | OFN_EXPLORER | OFN_HIDEREADONLY;

	GetOpenFileName(&ofn);

    CString csFile = ofn.lpstrFile;
    m_editWave = (csFile == _T("")) ? m_editWave : csFile;

    m_buttonApply.EnableWindow(TRUE);
    UpdateData(FALSE);
}

void CConfigDlg::OnButtonChooseMailer() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	OPENFILENAME ofn;
	ZeroMemory( &ofn, sizeof(OPENFILENAME) );

	CHAR szNdir[MAX_PATH]  = {"\0"};
    CHAR szNname[MAX_PATH] = {"\0"};

	ofn.lStructSize     = sizeof(OPENFILENAME);
	ofn.hwndOwner       = m_hWnd;
	ofn.hInstance       = AfxGetInstanceHandle();
	ofn.lpstrFile       = szNname;
	ofn.nMaxFile        = sizeof(szNname);
	ofn.lpstrFilter     = (LPCTSTR)_T("Program (*.exe)\0*.EXE\0");
	ofn.nFilterIndex    = 1;
	ofn.lpstrFileTitle  = NULL;
	ofn.lpstrTitle      = NULL;
	ofn.nMaxFileTitle   = 0;
	ofn.lpstrInitialDir = szNdir;
	ofn.Flags           = OFN_PATHMUSTEXIST | OFN_EXPLORER | OFN_HIDEREADONLY;

	GetOpenFileName(&ofn);

    CString csFile = ofn.lpstrFile;
    m_editMailer = (csFile == _T("")) ? m_editMailer : csFile;

    m_buttonApply.EnableWindow(TRUE);
    UpdateData(FALSE);
}

void CConfigDlg::UpdateList()
{
	m_listAccounts.DeleteAllItems();

    LVITEM lvi;
    ZeroMemory( &lvi, sizeof(LVITEM) );

	lvi.mask      = LVIF_TEXT;
	lvi.iSubItem  = 0;
	lvi.stateMask = LVIS_STATEIMAGEMASK;
	lvi.state     = INDEXTOSTATEIMAGEMASK(1);
	lvi.iImage    = 1;

    std::vector<CAccount> vAccount = m_config->GetAccounts();

    CString csNr = _T("");
	for(int i=0; i<vAccount.size(); i++) {
		lvi.iItem = i;
		csNr.Format("%d", i+1);
        lvi.pszText = (PSTR) csNr.GetBuffer(0);
        m_listAccounts.InsertItem(&lvi);
        m_listAccounts.SetItemText(i, 1, vAccount[i].csName);
	    m_listAccounts.SetItemText(i, 2, vAccount[i].csPop3);
	}
}

void CConfigDlg::OnButtonCancel() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

  	this->ShowWindow(SW_HIDE);
}

void CConfigDlg::WriteIniFile()
{
    std::vector<CAccount> vAccount = m_config->GetAccounts();
    int iAccounts = vAccount.size();

    LPCTSTR lpszIniFileName = _T("checkmail.ini");
    CString csWorkingDirectory = GetWorkingDirectory();
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
    WritePrivateProfileString(_T("CheckMail"), _T("Sound"), m_editWave, lpszIniFile);
    WritePrivateProfileString(_T("CheckMail"), _T("Mailer"), m_editMailer, lpszIniFile);
    csTemp.Format(_T("%d"), m_editMinutes);
    WritePrivateProfileString(_T("CheckMail"), _T("Minutes"), csTemp, lpszIniFile);
    csTemp.Format(_T("%d"), m_checkNotify);
    WritePrivateProfileString(_T("CheckMail"), _T("Notify"), csTemp, lpszIniFile);
    csTemp.Format(_T("%d"), m_checkTray);
    WritePrivateProfileString(_T("CheckMail"), _T("ToTray"), csTemp, lpszIniFile);
    csTemp.Format(_T("%d"), m_checkPopup);
    WritePrivateProfileString(_T("CheckMail"), _T("PopUp"), csTemp, lpszIniFile);
    csTemp.Format(_T("%d"), m_radioFive);
    WritePrivateProfileString(_T("CheckMail"), _T("ShowFive"), csTemp, lpszIniFile);
    csTemp.Format(_T("%d"), m_radioForeground);
    WritePrivateProfileString(_T("CheckMail"), _T("ForegroundWindow"), csTemp, lpszIniFile);

    CString csT = _T("");
    for(int j=0; j<iAccounts; j++) {
        csTemp.Format(_T("Account%d"), j+1);
        WritePrivateProfileString(csTemp, _T("Name"), vAccount[j].csName, lpszIniFile);
        WritePrivateProfileString(csTemp, _T("Pop3"), vAccount[j].csPop3, lpszIniFile);
        csT = Encrypt( vAccount[j].csLogin );
        WritePrivateProfileString(csTemp, _T("Login"), csT, lpszIniFile);
        csT = Encrypt( vAccount[j].csPassword );
        WritePrivateProfileString(csTemp, _T("Password"), csT, lpszIniFile);
    }

    m_config->m_iFive       = m_radioFive;
    m_config->m_bPlaySound  = m_checkNotify;
    m_config->m_csWafeFile  = m_editWave;
    m_config->m_uiMinutes   = m_editMinutes;
    m_config->m_bPopup      = m_checkPopup;
    m_config->m_iForeground = m_radioForeground;

    m_config->m_csWafeFile.Replace(_T("\\"), _T("\\\\"));

    m_config->SetAccounts(vAccount);
}

void CConfigDlg::ReadIniFile()
{
    std::vector<CAccount> vAccount;
    int iAccounts = 0;

    LPCTSTR lpszIniFileName = _T("checkmail.ini");
    CString csWorkingDirectory = GetWorkingDirectory();
    CString csIniFilee = csWorkingDirectory + static_cast<CString>(lpszIniFileName);
    LPCTSTR lpszIniFile = csIniFilee.GetBuffer(0);

    CHAR szTmp[MAX_PATH] = {"\0"};
    GetPrivateProfileString(_T("CheckMail"), _T("Accounts"), "", szTmp, MAX_PATH, lpszIniFile);
    iAccounts = atoi(szTmp);
    GetPrivateProfileString(_T("CheckMail"), _T("Sound"), "", szTmp, MAX_PATH, lpszIniFile);
    m_editWave = szTmp;
    GetPrivateProfileString(_T("CheckMail"), _T("Mailer"), "", szTmp, MAX_PATH, lpszIniFile);
    m_editMailer = szTmp;
    GetPrivateProfileString(_T("CheckMail"), _T("Minutes"), "", szTmp, MAX_PATH, lpszIniFile);
    m_editMinutes = atoi(szTmp);
    GetPrivateProfileString(_T("CheckMail"), _T("Notify"), "", szTmp, MAX_PATH, lpszIniFile);
    m_checkNotify = atoi(szTmp);
    GetPrivateProfileString(_T("CheckMail"), _T("ToTray"), "", szTmp, MAX_PATH, lpszIniFile);
    m_checkTray = atoi(szTmp);
    GetPrivateProfileString(_T("CheckMail"), _T("PopUp"), "", szTmp, MAX_PATH, lpszIniFile);
    m_checkPopup = atoi(szTmp);
    GetPrivateProfileString(_T("CheckMail"), _T("ShowFive"), "", szTmp, MAX_PATH, lpszIniFile);
    m_radioFive = atoi(szTmp);
    GetPrivateProfileString(_T("CheckMail"), _T("ForegroundWindow"), "", szTmp, MAX_PATH, lpszIniFile);
    m_radioForeground = atoi(szTmp);

    vAccount.resize(iAccounts);

    CString csTemp = _T("");
    for(int i=0; i<iAccounts; i++) {
        csTemp.Format(_T("Account%d"), i+1);
        GetPrivateProfileString(csTemp, _T("Name"), "", szTmp, MAX_PATH, lpszIniFile);
        vAccount[i].csName = static_cast<CString>(szTmp);
        GetPrivateProfileString(csTemp, _T("Pop3"), "", szTmp, MAX_PATH, lpszIniFile);
        vAccount[i].csPop3 = static_cast<CString>(szTmp);
        GetPrivateProfileString(csTemp, _T("Login"), "", szTmp, MAX_PATH, lpszIniFile);
        vAccount[i].csLogin = Decrypt( static_cast<CString>(szTmp) );
        GetPrivateProfileString(csTemp, _T("Password"), "", szTmp, MAX_PATH, lpszIniFile);
        vAccount[i].csPassword = Decrypt( static_cast<CString>(szTmp) );
    }

    if(m_editMinutes < 1) {
        m_editMinutes = 1;
    }

    m_config->m_iFive       = m_radioFive;
    m_config->m_uiMinutes   = m_editMinutes;
    m_config->m_bPlaySound  = m_checkNotify;
    m_config->m_csWafeFile  = m_editWave;
    m_config->m_bPopup      = m_checkPopup;
    m_config->m_iForeground = m_radioForeground;

    m_config->m_csWafeFile.Replace(_T("\\"), _T("\\\\"));

    m_config->SetAccounts(vAccount);
}

BOOL CConfigDlg::ShallMinimize()
{
    return m_checkTray;
}

CConfig* CConfigDlg::GetConfig()
{
    if( m_config ) {
        return m_config;
    }
    else {
        return NULL;
    }
}

void CConfigDlg::OnButtonOk() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
    UpdateData(TRUE);

  	this->ShowWindow(SW_HIDE);
   
    WriteIniFile();

    GetParent()->PostMessage(WM_CONFIG_CHANGED);
}

void CConfigDlg::OnButtonApply() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

    WriteIniFile();

    m_buttonApply.EnableWindow(FALSE);
}

void CConfigDlg::OnCheckTray() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

    UpdateData(TRUE);

    if( m_checkTray == TRUE ) {
        m_checkTray = TRUE;
    }
    else {
        m_checkTray = FALSE;
    }

    UpdateData(FALSE);

	m_buttonApply.EnableWindow(TRUE);
}

void CConfigDlg::OnCheckNotify() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

    UpdateData(TRUE);

    if( m_checkNotify == TRUE ) {
        m_checkNotify = TRUE;
        GetDlgItem( IDC_EDIT_WAVE )->EnableWindow( TRUE );
    }
    else {
        m_checkNotify = FALSE;
        GetDlgItem( IDC_EDIT_WAVE )->EnableWindow( FALSE );
    }

    UpdateData(FALSE);

	m_buttonApply.EnableWindow(TRUE);
}

void CConfigDlg::OnRadioFive() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	m_buttonApply.EnableWindow(TRUE);
}

void CConfigDlg::OnRadioAll() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	m_buttonApply.EnableWindow(TRUE);
}

void CConfigDlg::OnChangeEditWave() 
{
	// TODO: Fügen Sie hier Ihren Code für die Benachrichtigungsbehandlungsroutine des Steuerelements hinzu

	m_buttonApply.EnableWindow(TRUE);
}

void CConfigDlg::OnChangeEditMailer() 
{
	// TODO: Fügen Sie hier Ihren Code für die Benachrichtigungsbehandlungsroutine des Steuerelements hinzu

	m_buttonApply.EnableWindow(TRUE);
}

void CConfigDlg::OnCheckPopup() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

    UpdateData(TRUE);

    if( m_checkPopup == TRUE ) {
        m_checkPopup = TRUE;
        GetDlgItem( IDC_RADIO_FOREGROUND )->EnableWindow( TRUE );
        GetDlgItem( IDC_RADIO_BACKGROUND )->EnableWindow( TRUE );
    }
    else {
        m_checkPopup = FALSE;
        GetDlgItem( IDC_RADIO_FOREGROUND )->EnableWindow( FALSE );
        GetDlgItem( IDC_RADIO_BACKGROUND )->EnableWindow( FALSE );
    }

    UpdateData(FALSE);

	m_buttonApply.EnableWindow(TRUE);    
}

void CConfigDlg::OnRadioForeground() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
    m_buttonApply.EnableWindow(TRUE);
}

void CConfigDlg::OnRadioBackground() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
    m_buttonApply.EnableWindow(TRUE);
}

CString CConfigDlg::GetWorkingDirectory()
{
    TCHAR szPathName[_MAX_PATH];
    ::GetModuleFileName(NULL, szPathName, _MAX_PATH);
    LPTSTR pszFileName = _tcsrchr(szPathName, '\\') + 1;
    *pszFileName = '\0';
    
    return static_cast<LPCTSTR>(szPathName);
}

CString CConfigDlg::Encrypt(CString csText)
{
    csText.MakeReverse();
    LPSTR lpszText = csText.GetBuffer(0);
    int len = csText.GetLength();

    CHAR szA = 0;
    for(int i=0; i<len; i++) {
        if( i%3 ) {
            szA = lpszText[i] - 2;
        }
        else if( i%2 ) {
            szA = lpszText[i] + 3;
        }
        else {
            szA = lpszText[i] - 1;
        }

        lpszText[i] = szA;
    }

    return static_cast<CString>(lpszText);
}

CString CConfigDlg::Decrypt(CString csText)
{
    LPSTR lpszText = csText.GetBuffer(0);
    int len = csText.GetLength();

    CHAR szA = 0;
    for(int i=0; i<len; i++) {
        if( i%3 ) {
            szA = lpszText[i] + 2;
        }
        else if( i%2 ) {
            szA = lpszText[i] - 3;
        }
        else {
            szA = lpszText[i] + 1;
        }

        lpszText[i] = szA;
    }

    csText = static_cast<CString>(lpszText);
    csText.MakeReverse();

    return csText;
}
