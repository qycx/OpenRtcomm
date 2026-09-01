// CSDemoClientDlg.h : 头文件
//

#pragma once
//#include "afxwin.h"
//#include "afxcmn.h"



#define STRING_LENGTH 256

#define AUTH_CODE_SOCKET_FAIL			20	//网络通讯初始化失败 
#define AUTH_CODE_CONNECT_FAIL			21	//连接服务器失败 
#define AUTH_CODE_SEND_INFO_FAIL		22	//发送请求信息失败
#define AUTH_CODE_RECV_INFO_FAIL		23	//接收响应信息失败


class CClientAuth;

// CCSDemoClientDlg 对话框
class CCSDemoClientDlg : public CDialog
{
    DECLARE_DYNAMIC(CCSDemoClientDlg)

public:
    CCSDemoClientDlg(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CCSDemoClientDlg();

    virtual BOOL OnInitDialog();

	//获取KEY类型管理信息
	DWORD getCertSettings(char *strCertSettings);
	
	DWORD getRandOriginal(const PTCHAR strServerIP, const PTCHAR strServerPort, PTCHAR strOriginal);
	DWORD verifyAuthRequest(const PTCHAR strServerIP, const PTCHAR strServerPort, const PTCHAR strRequesInfo);

// 对话框数据
    enum { IDD = IDD_CSDEMOCLIENT_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()

protected:
    afx_msg void OnBnClickedBtnAuth();
    afx_msg void OnBnClickedClose();

protected:
    CIPAddressCtrl m_ServerIPCtrl;
	CClientAuth* m_pClientAuth;
    
public:
    CButton m_ChkCert;
    CButton m_ChkPwd;
};
