// Pop.h: Schnittstelle für die Klasse CPop.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POP_H__769FEF30_7499_4CEB_8FC6_43816BA4363A__INCLUDED_)
#define AFX_POP_H__769FEF30_7499_4CEB_8FC6_43816BA4363A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#ifndef __AFXWIN_H__
//	#error include 'stdafx.h' before including this file for PCH
//#endif

#define CONNECTION_CHECK 0
#define USER_CHECK		1
#define PASSWORD_CHECK	2
#define QUIT_CHECK		3
#define DELETE_CHECK	4
#define RSET_CHECK		5 
#define STAT_CHECK		6 
#define NOOP_CHECK		7
#define LIST_CHECK		8
#define RETR_CHECK		9

/////////////////////////////////////////////////////////////////////////////
// CPopApp:
// See Pop.cpp for the implementation of this class
//

//class CPopApp : public CWinApp
//{
//public:
//	CPopApp();
//
//// Overrides
//	// ClassWizard generated virtual function overrides
//	//{{AFX_VIRTUAL(CPopApp)
//	public:
//	virtual BOOL InitInstance();
//	//}}AFX_VIRTUAL
//
//// Implementation
//
//	//{{AFX_MSG(CPopApp)
//		// NOTE - the ClassWizard will add and remove member functions here.
//		//    DO NOT EDIT what you see in these blocks of generated code !
//	//}}AFX_MSG
//	DECLARE_MESSAGE_MAP()
//};


/////////////////////////////////////////////////////////////////////////////

class CPop  
{
public: 
	CString GetSubject();
    BOOL List(); 
    CWordArray m_SizeOfMsg; 
    CString GetErrorMessage();             // If there is any error this will return it method 
    CString GetPassword();                 // Getting Password stored in class 
    void SetPassword(CString& Password);   // Setting Password in class 
    CString GetUser();                     // Getting user name stored in class 
    void SetUser(CString& User);           // Setting user name in class 
    CString GetHost();                     // Getting Host name (email server name) stored in class 
    void SetHost(CString& Host);           // Setting Host name (email server name) in class 
    BOOL Connect();                        // Connecting to email server 
    int GetTotalMailSize();                // it returns the Total Mail Size 
    int GetNumberOfMails();                // It return the number of mails 
    CString GetMsgContents();         
    BOOL Statistics();                     // issue the STAT command on email server 
    BOOL Retrieve(int MsgNumber);          // Getting any particular mail message 
    BOOL Reset();                          // issue the reset command on email server 
    int  GetMessageSize(int MsgNumber);    // Return a size of any particular mail 
    BOOL Noop();                           // issue the NOOP command on email server 
    BOOL Disconnect();                     // issue the QUIT command on email server 
    BOOL Delete(int& MsgNumber);           // Deleteing a particular message from email server 
    BOOL Connect(CString& Host, CString& User, CString& Password); 
    CPop(); 
    virtual ~CPop(); 

private: 
    CString m_ErrorMessage; 
    BOOL CheckResponse(int ResponseType); 
    CString m_Password; 
    CString m_User; 
    CString m_Host; 
    CString m_MsgContents; 
    int m_TotalSize; 
    int m_NumberMail; 
    CSocket m_PopServer;
};

#endif // !defined(AFX_POP_H__769FEF30_7499_4CEB_8FC6_43816BA4363A__INCLUDED_)
