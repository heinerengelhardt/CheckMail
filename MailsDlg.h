#if !defined(AFX_MAILSDLG_H__820E1755_1157_472A_A350_4F9F97BE2A11__INCLUDED_)
#define AFX_MAILSDLG_H__820E1755_1157_472A_A350_4F9F97BE2A11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MailsDlg.h : Header-Datei
//

#include "Account.h"
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CMailsDlg 

class CMailsDlg : public CDialog
{
// Konstruktion
public:
    void UpdateList( std::vector<CAccount> vAccount, std::vector<int> vMailCount, std::vector<int> vMailSize, std::vector<CString> vMailSubject );
	CMailsDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CMailsDlg)
	enum { IDD = IDD_MAILS };
	CListCtrl	m_listMails;
	BOOL	m_bAlwaysOnTop;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CMailsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CMailsDlg)
	afx_msg void OnButtonOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckTop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_MAILSDLG_H__820E1755_1157_472A_A350_4F9F97BE2A11__INCLUDED_
