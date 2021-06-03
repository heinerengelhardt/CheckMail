// Check.h: Schnittstelle für die Klasse CCheck.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECK_H__BC160D52_8A5E_4FDC_AA84_22FDD5A5A06B__INCLUDED_)
#define AFX_CHECK_H__BC160D52_8A5E_4FDC_AA84_22FDD5A5A06B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Config.h"
#include "TrayIcon.h"
#include "mmsystem.h"
#include "Account.h"
#include "resource.h"
#include "Pop.h"
#include "process.h"
#include "MailsDlg.h"

#define SINGLE_LINE  0
#define MULTI_LINE   1

class CCheck
{
public:
    CCheck( CConfig* config, CTrayIcon* trayicon );
	virtual ~CCheck();

    void        CheckMails();
    static void StartCheckMailThread( PVOID pParam );

    CMailsDlg* m_pMailsDlg;

private:
    HICON m_hNoMailIcon;
    HICON m_hNewMailIcon;
    HICON m_hCheckMailIcon;

    std::vector<CAccount> m_vAccount;
    std::vector<int>      m_vRevievedMails;
    std::vector<int>      m_vMailSize;
    std::vector<CString>  m_vMailSubject;

    CConfig*   m_config;
    CTrayIcon* m_trayIcon;
    UINT       m_iMailSize;

    void SocketThreadInit();
   	BOOL IsInternetConnected();
	int  CheckSpecificMailbox( CString csHost, CString csUser, CString csPwd, int iNumber );
	UINT GetToolTipStyleByOS();
};

#endif // !defined(AFX_CHECK_H__BC160D52_8A5E_4FDC_AA84_22FDD5A5A06B__INCLUDED_)
