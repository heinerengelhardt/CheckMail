// CheckMail.h : Haupt-Header-Datei f�r die Anwendung CHECKMAIL
//

#if !defined(AFX_CHECKMAIL_H__0B6C1D4E_9228_48AF_997C_87AD080E4BA2__INCLUDED_)
#define AFX_CHECKMAIL_H__0B6C1D4E_9228_48AF_997C_87AD080E4BA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CCheckMailApp:
// Siehe CheckMail.cpp f�r die Implementierung dieser Klasse
//

class CCheckMailApp : public CWinApp
{
public:
	CCheckMailApp();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CCheckMailApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CCheckMailApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CCheckMailApp theApp;


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_CHECKMAIL_H__0B6C1D4E_9228_48AF_997C_87AD080E4BA2__INCLUDED_)
