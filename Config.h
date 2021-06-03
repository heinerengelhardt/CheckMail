// Config.h: Schnittstelle für die Klasse CConfig.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIG_H__829E63D5_D57A_48BB_BF00_ED155C8F37BD__INCLUDED_)
#define AFX_CONFIG_H__829E63D5_D57A_48BB_BF00_ED155C8F37BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "Account.h"

class CConfig
{
public:
	void SetAccounts(std::vector<CAccount> vAccount);
	void ChangeAccount(UINT pos, CString csAccountName, CString csPop3, CString csLogin, CString csPassword);
	void DeleteAccount(UINT pos);
	int  InsertAccount(CString csAccountName, CString csPop3, CString csLogin, CString csPassword);
    std::vector<CAccount> GetAccounts();

	CConfig();
	virtual ~CConfig();

    std::vector<CAccount> m_vAccount;
    UINT m_iAccounts;
	CString m_csWafeFile;
    BOOL m_bPlaySound;
    UINT m_uiMinutes;
	BOOL m_bPopup;
	int m_iFive;
    int m_iForeground;
};

#endif // !defined(AFX_CONFIG_H__829E63D5_D57A_48BB_BF00_ED155C8F37BD__INCLUDED_)
