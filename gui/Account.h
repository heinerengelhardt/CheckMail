// Accounts.h: Schnittstelle für die Klasse CAccounts.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCOUNT_H__5079410A_B269_4BFC_88E5_3DD155CE8F0A__INCLUDED_)
#define AFX_ACCOUNT_H__5079410A_B269_4BFC_88E5_3DD155CE8F0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAccount
{
public:
	CAccount();
	virtual ~CAccount();

    CString csName;
    CString csLogin;
    CString csPop3;
    CString csPassword;

};

#endif // !defined(AFX_ACCOUNT_H__5079410A_B269_4BFC_88E5_3DD155CE8F0A__INCLUDED_)
