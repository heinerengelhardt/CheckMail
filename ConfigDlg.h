#if !defined(AFX_CONFIGDLG_H__51C4EF1F_AADF_4E5F_9247_87C8F80F693B__INCLUDED_)
#define AFX_CONFIGDLG_H__51C4EF1F_AADF_4E5F_9247_87C8F80F693B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CConfigDlg 

#include "Account.h"
#include "ButtonST.h"
#include "Config.h"
#include <vector>
#include "Check.h"
#include "TrayIcon.h"

class CConfigDlg : public CDialog
{
// Konstruktion
public:
    CTrayIcon* m_pTrayIcon;
    CConfig*   m_config;

	CConfig* GetConfig();
	BOOL ShallMinimize();
	CConfigDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CConfigDlg)
	enum { IDD = IDD_CONFIG };
	CButton	m_buttonApply;
	CSpinButtonCtrl	m_spinMinutes;
	CButtonST	m_buttonChooseFile;
    CButtonST	m_buttonChooseMailer;
	CButton	m_buttonDelete;
	CButton	m_buttonChange;
	CButton	m_buttonAdd;
	CListCtrl	m_listAccounts;
	CString	m_editAccount;
	CString	m_editLogin;
	UINT	m_editMinutes;
	CString	m_editPassword;
	CString	m_editPop3;
    CString	m_editMailer;
	CString	m_editWave;
	int		m_radioFive;
	BOOL	m_checkTray;
	BOOL	m_checkNotify;
	BOOL	m_checkPopup;
	int		m_radioForeground;
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CConfigDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpinMinutes(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEditMinutes();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonChange();
	afx_msg void OnButtonDelete();
	afx_msg void OnClickListAccounts(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonChooseFile();
    afx_msg void OnButtonChooseMailer();
	afx_msg void OnButtonOk();
	afx_msg void OnButtonCancel();
	afx_msg void OnButtonApply();
	afx_msg void OnCheckTray();
	afx_msg void OnCheckNotify();
	afx_msg void OnRadioFive();
	afx_msg void OnRadioAll();
	afx_msg void OnChangeEditWave();
	afx_msg void OnChangeEditMailer();
	afx_msg void OnCheckPopup();
	afx_msg void OnRadioForeground();
	afx_msg void OnRadioBackground();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString Decrypt( CString csText );
	CString Encrypt(CString csText);
	CString GetWorkingDirectory();
	void WriteIniFile();
	void ReadIniFile();
	void InitList();
	void UpdateList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_CONFIGDLG_H__51C4EF1F_AADF_4E5F_9247_87C8F80F693B__INCLUDED_
