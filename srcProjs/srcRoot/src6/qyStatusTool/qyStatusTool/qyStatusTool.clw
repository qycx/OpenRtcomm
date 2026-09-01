; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgFilters
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "qystatustool.h"
LastPage=0

ClassCount=7
Class1=CQyPs
Class2=CPpQnmChkingStatus
Class3=CPpQwmCommStatus
Class4=CPpScanningIpStatus
Class5=CQyStatusToolApp

ResourceCount=7
Resource1=IDD_ABOUTBOX (English (U.S.))
Resource2=IDD_qnmChkingStatus (English (U.S.))
Resource3=IDD_qwmCommStatus (English (U.S.))
Resource4=IDD_ip (English (U.S.))
Resource5=IDD_filters (English (U.S.))
Class6=CDlgFilters
Resource6=IDD_scanningIpStatus (English (U.S.))
Class7=CDlgQyCommStatus
Resource7=IDD_qyCommStatus (English (U.S.))

[CLS:CQyPs]
Type=0
HeaderFile=\qycx4\Develop4\src5\qyMc\include\qyps.h
ImplementationFile=\qycx4\Develop4\src5\qyMc\qymcpublic\qyps.cpp
BaseClass=CPropertySheet
LastObject=CQyPs

[CLS:CPpQnmChkingStatus]
Type=0
BaseClass=CPropertyPage
HeaderFile=PpQnmChkingStatus.h
ImplementationFile=PpQnmChkingStatus.cpp
LastObject=CPpQnmChkingStatus

[CLS:CPpQwmCommStatus]
Type=0
BaseClass=CPropertyPage
HeaderFile=PpQwmCommStatus.h
ImplementationFile=PpQwmCommStatus.cpp

[CLS:CPpScanningIpStatus]
Type=0
BaseClass=CPropertyPage
HeaderFile=PpScanningIpStatus.h
ImplementationFile=PpScanningIpStatus.cpp

[CLS:CQyStatusToolApp]
Type=0
BaseClass=CWinApp
HeaderFile=qyStatusTool.h
ImplementationFile=qyStatusTool.cpp
LastObject=CQyStatusToolApp

[DLG:IDD_qnmChkingStatus (English (U.S.))]
Type=1
Class=CPpQnmChkingStatus
ControlCount=5
Control1=IDC_LIST_display,listbox,1352728835
Control2=IDC_STATIC_nm,static,1342308352
Control3=IDC_STATIC_serviceStatus_netMc,static,1342308352
Control4=IDC_CHECK_autoClearup,button,1342242819
Control5=IDC_COMBO_select,combobox,1344340227

[DLG:IDD_qwmCommStatus (English (U.S.))]
Type=1
Class=CPpQwmCommStatus
ControlCount=10
Control1=IDC_COMBO_select,combobox,1344339971
Control2=IDC_STATIC_filter0,static,1073877505
Control3=IDC_LIST_display,listbox,1352728835
Control4=IDC_STATIC_nm,static,1342308352
Control5=IDC_STATIC_serviceStatus_netMc,static,1342308352
Control6=IDC_CHECK_autoClearup,button,1342242819
Control7=IDC_STATIC_serviceStatus_is,static,1342308352
Control8=IDC_STATIC_filter1,static,1073877505
Control9=IDC_STATIC_clientIp0,static,1073877505
Control10=IDC_STATIC_clientIp1,static,1073877505

[DLG:IDD_scanningIpStatus (English (U.S.))]
Type=1
Class=CPpScanningIpStatus
ControlCount=5
Control1=IDC_STATIC_scanningIp,static,1342308864
Control2=IDC_STATIC_scanningNetworkSegment,static,1342308864
Control3=IDC_STATIC_ipScan,static,1342308864
Control4=IDC_STATIC_serviceStatus_netMc,static,1342308864
Control5=IDC_STATIC_bhbScanningNetworkSegment,static,1342308864

[DLG:IDD_ip (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDC_IP,SysIPAddress32,1342242816
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC_ver,static,1342308480
Control3=IDC_STATIC_qycxCopyRight,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CDlgFilters]
Type=0
HeaderFile=DlgFilters.h
ImplementationFile=DlgFilters.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[DLG:IDD_filters (English (U.S.))]
Type=1
Class=CDlgFilters
ControlCount=14
Control1=IDC_EDIT_clientIp0,edit,1350631552
Control2=IDC_EDIT_clientIp1,edit,1350631552
Control3=IDC_EDIT_filter0,edit,1350631552
Control4=IDC_EDIT_filter1,edit,1350631552
Control5=IDC_EDIT_filter2,edit,1350631552
Control6=IDC_EDIT_filter3,edit,1350631552
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816
Control9=IDC_STATIC_staticFilter0,static,1342308864
Control10=IDC_STATIC_staticFilter1,static,1342308864
Control11=IDC_STATIC_clientIp0,static,1342308864
Control12=IDC_STATIC_clientIp1,static,1342308864
Control13=IDC_STATIC_staticFilter2,static,1342308864
Control14=IDC_STATIC_staticFilter3,static,1342308864

[DLG:IDD_qyCommStatus (English (U.S.))]
Type=1
Class=CDlgQyCommStatus
ControlCount=15
Control1=IDC_COMBO_select,combobox,1344339971
Control2=IDC_RADIO_qwmComm,button,1342177289
Control3=IDC_RADIO_qnmChking,button,1342177289
Control4=IDC_RADIO_scanningIp,button,1342177289
Control5=IDC_STATIC_filter0,static,1073877505
Control6=IDC_LIST_display,listbox,1352728833
Control7=IDC_STATIC_nm,static,1342308352
Control8=IDC_STATIC_serviceStatus_netMc,static,1342308352
Control9=IDC_CHECK_autoClearup,button,1342242819
Control10=IDC_STATIC_serviceStatus_is,static,1342308352
Control11=IDC_STATIC_filter1,static,1073877505
Control12=IDC_STATIC_clientIp0,static,1073877505
Control13=IDC_STATIC_clientIp1,static,1073877505
Control14=IDC_STATIC_contentFilter2,static,1073877505
Control15=IDC_STATIC_contentFilter3,static,1073877505

[CLS:CDlgQyCommStatus]
Type=0
HeaderFile=DlgQyCommStatus.h
ImplementationFile=DlgQyCommStatus.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgQyCommStatus
VirtualFilter=dWC

