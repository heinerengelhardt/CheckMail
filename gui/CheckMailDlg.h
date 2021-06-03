// CheckMailDlg.h : Header-Datei
//

#if !defined(AFX_CHECKMAILDLG_H__30D36993_7002_47B9_9867_5BD7BBFE81B5__INCLUDED_)
#define AFX_CHECKMAILDLG_H__30D36993_7002_47B9_9867_5BD7BBFE81B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCheckMailDlg Dialogfeld

#include "ConfigDlg.h"
#include "TrayIcon.h"
#include "Hyperlink.h"
#include "ButtonST.h"
#include "Check.h"
#include "process.h"
#include "MailsDlg.h"
#include "Account.h"
#include <vector>

class CCheckMailDlg : public CDialog
{
// Konstruktion
public:
	CCheckMailDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

    CConfigDlg*      m_configDlg;
	CTrayIcon*       m_pTrayIcon;
    CConfig*         m_config;
    CMailsDlg*       m_pMailsDlg;

// Dialogfelddaten
	//{{AFX_DATA(CCheckMailDlg)
	enum { IDD = IDD_CHECKMAIL_DIALOG };
	CButton	m_buttonExit;
	CButton	m_buttonPreferences;
	CButton	m_buttonToTray;
	CHyperLink	m_linkEmail;
    CHyperLink	m_linkHomepage;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CCheckMailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CCheckMailDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	afx_msg void OnTrayExit();
	afx_msg void OnButtonPreferences();
	afx_msg void OnTrayPreferences();
	afx_msg void OnMailer();
	afx_msg void OnButtonToTray();
	afx_msg void OnTrayRestore();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnTrayEnable();
	afx_msg void OnTrayDisable();
	afx_msg void OnTrayDetailedInfo();
	afx_msg void OnTrayAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ConvertToNewIniFile();
	void CheckOnlineStatus();
	void StartCheckMailThread();
    UINT m_uiMin;

  	LRESULT OnConfigChanged(WPARAM wParam, LPARAM lParam);
	LRESULT OnDialogShown(WPARAM wParam, LPARAM lParam);
    LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_CHECKMAILDLG_H__30D36993_7002_47B9_9867_5BD7BBFE81B5__INCLUDED_)
