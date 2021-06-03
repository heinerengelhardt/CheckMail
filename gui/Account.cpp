// Account.cpp: Implementierung der Klasse CAccounts.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Account.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CAccount::CAccount()
{
    csLogin    = _T("");
    csName     = _T("");
    csPop3     = _T("");
    csPassword = _T("");
}

CAccount::~CAccount()
{

}
