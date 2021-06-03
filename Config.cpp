// Config.cpp: Implementierung der Klasse CConfig.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "Config.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CConfig::CConfig()
{
    m_iAccounts = 0;
    m_iForeground = 0;
}

CConfig::~CConfig()
{

}

int CConfig::InsertAccount(CString csAccountName, CString csPop3, CString csLogin, CString csPassword)
{
    m_iAccounts++;
    m_vAccount.resize(m_iAccounts);

    CAccount acc;
    acc.csName     = csAccountName;
    acc.csPop3     = csPop3;
    acc.csLogin    = csLogin;
    acc.csPassword = csPassword;
    m_vAccount[m_iAccounts-1] = acc;

    return m_iAccounts;
}

std::vector<CAccount> CConfig::GetAccounts()
{
    return m_vAccount;
}

void CConfig::DeleteAccount(UINT pos)
{
    m_vAccount[pos-1] = m_vAccount[m_iAccounts-1];

    m_iAccounts--;
    m_vAccount.resize(m_iAccounts);
}

void CConfig::ChangeAccount(UINT pos, CString csAccountName, CString csPop3, CString csLogin, CString csPassword)
{
    CAccount acc;

    acc.csName     = csAccountName;
    acc.csPop3     = csPop3;
    acc.csLogin    = csLogin;
    acc.csPassword = csPassword;

    m_vAccount[pos-1] = acc;
}

void CConfig::SetAccounts(std::vector<CAccount> vAccount)
{
    m_vAccount = vAccount;
    m_iAccounts = vAccount.size();
}
