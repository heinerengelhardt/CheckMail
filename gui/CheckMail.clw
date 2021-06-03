; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCheckMailDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "checkmail.h"
LastPage=0

ClassCount=7
Class1=CButtonST
Class2=CCheckMailApp
Class3=CAboutDlg
Class4=CCheckMailDlg
Class5=CConfigDlg
Class6=CHyperLink

ResourceCount=5
Resource1=IDD_ABOUTBOX (Englisch (USA))
Resource2=IDD_CONFIG (Englisch (USA))
Resource3=IDD_CHECKMAIL_DIALOG (Englisch (USA))
Resource4=IDR_MENU_TRAY
Class7=CMailsDlg
Resource5=IDD_MAILS (Englisch (USA))

[CLS:CButtonST]
Type=0
BaseClass=CButton
HeaderFile=ButtonST.h
ImplementationFile=ButtonST.cpp

[CLS:CCheckMailApp]
Type=0
BaseClass=CWinApp
HeaderFile=CheckMail.h
ImplementationFile=CheckMail.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=CheckMailDlg.cpp
ImplementationFile=CheckMailDlg.cpp
LastObject=IDC_LINK_EMAIL
Filter=D
VirtualFilter=dWC

[CLS:CCheckMailDlg]
Type=0
BaseClass=CDialog
HeaderFile=CheckMailDlg.h
ImplementationFile=CheckMailDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=ID_TRAY_DETAILEDINFO

[CLS:CConfigDlg]
Type=0
BaseClass=CDialog
HeaderFile=ConfigDlg.h
ImplementationFile=ConfigDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CConfigDlg

[CLS:CHyperLink]
Type=0
BaseClass=CStatic
HeaderFile=Hyperlink.h
ImplementationFile=HyperLink.cpp
LastObject=CHyperLink

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_CHECKMAIL_DIALOG]
Type=1
Class=CCheckMailDlg

[DLG:IDD_CONFIG]
Type=1
Class=CConfigDlg

[DLG:IDD_MAILS (Englisch (USA))]
Type=1
Class=CMailsDlg
ControlCount=4
Control1=IDC_BUTTON_OK,button,1342242816
Control2=IDC_STATIC,static,1342177296
Control3=IDC_LIST_MAILS,SysListView32,1350664197
Control4=IDC_CHECK_TOP,button,1342242819

[MNU:IDR_MENU_TRAY]
Type=1
Class=?
Command1=ID_TRAY_RESTORE
Command2=ID_TRAY_ABOUT
Command3=ID_TRAY_PREFERENCES
Command4=ID_MAILER
Command5=ID_TRAY_DETAILEDINFO
Command6=ID_TRAY_ENABLE
Command7=ID_TRAY_DISABLE
Command8=ID_TRAY_EXIT
CommandCount=8

[DLG:IDD_ABOUTBOX (Englisch (USA))]
Type=1
Class=?
ControlCount=7
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_LINK_EMAIL,static,1342308352
Control6=IDC_LINK_HOMEPAGE,static,1342308352
Control7=IDC_STATIC,static,1342177296

[DLG:IDD_CHECKMAIL_DIALOG (Englisch (USA))]
Type=1
Class=?
ControlCount=10
Control1=ID_TOTRAY,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342177283
Control4=IDC_STATIC,static,1342308480
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_LINK_EMAIL,static,1342308352
Control8=IDC_LINK_HOMEPAGE,static,1342308352
Control9=IDC_STATIC,static,1342177296
Control10=IDC_BUTTON_PREFERENCES,button,1342242816

[DLG:IDD_CONFIG (Englisch (USA))]
Type=1
Class=?
ControlCount=35
Control1=IDC_EDIT_ACCOUNT,edit,1350631552
Control2=IDC_EDIT_POP3,edit,1350631552
Control3=IDC_EDIT_LOGIN,edit,1350631552
Control4=IDC_EDIT_PASSWORD,edit,1350631584
Control5=IDC_BUTTON_ADD,button,1342242816
Control6=IDC_LIST_ACCOUNTS,SysListView32,1350664205
Control7=IDC_BUTTON_CHANGE,button,1342242816
Control8=IDC_BUTTON_DELETE,button,1342242816
Control9=IDC_EDIT_MINUTES,edit,1350639618
Control10=IDC_SPIN_MINUTES,msctls_updown32,1342177698
Control11=IDC_CHECK_TRAY,button,1342242819
Control12=IDC_CHECK_NOTIFY,button,1342242819
Control13=IDC_EDIT_WAVE,edit,1350631552
Control14=IDC_BUTTON_CHOOSE_FILE,button,1342242816
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,button,1342177287
Control22=IDC_STATIC,button,1342177287
Control23=IDC_BUTTON_OK,button,1342242816
Control24=IDC_EDIT_MAILER,edit,1350631552
Control25=IDC_STATIC,static,1342308352
Control26=IDC_BUTTON_CHOOSE_MAILER,button,1342242816
Control27=IDC_STATIC,static,1342308352
Control28=IDC_RADIO_FIVE,button,1342308361
Control29=IDC_RADIO_ALL,button,1342185481
Control30=IDC_BUTTON_CANCEL,button,1342242816
Control31=IDC_BUTTON_APPLY,button,1342242816
Control32=IDC_CHECK_POPUP,button,1342242819
Control33=IDC_RADIO_FOREGROUND,button,1342312457
Control34=IDC_RADIO_BACKGROUND,button,1342181385
Control35=IDC_STATIC,static,1342308352

[CLS:CMailsDlg]
Type=0
HeaderFile=MailsDlg.h
ImplementationFile=MailsDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CMailsDlg

