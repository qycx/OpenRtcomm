// CSDemoClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CSDemoClient.h"
#include "CSDemoClientDlg.h"
#include <comutil.h>

#include "gm3000_dll.h"
#include "ClientAuth.h"

// CCSDemoClientDlg 对话框
IMPLEMENT_DYNAMIC(CCSDemoClientDlg, CDialog)

CCSDemoClientDlg::CCSDemoClientDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CCSDemoClientDlg::IDD, pParent)
{
}

CCSDemoClientDlg::~CCSDemoClientDlg()
{
}

void CCSDemoClientDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CHECKCert, m_ChkCert);
    DDX_Control(pDX, IDC_CHECKPasswd, m_ChkPwd);
    DDX_Control(pDX, IDC_IPADDRESSIP, m_ServerIPCtrl);
}

BEGIN_MESSAGE_MAP(CCSDemoClientDlg, CDialog)
    ON_BN_CLICKED(IDC_BUTTON1, &CCSDemoClientDlg::OnBnClickedBtnAuth)
    ON_BN_CLICKED(IDC_BUTTON2, &CCSDemoClientDlg::OnBnClickedClose)
END_MESSAGE_MAP()

// CCSDemoClientDlg 消息处理程序
void CCSDemoClientDlg::OnBnClickedClose()
{
    OnCancel();
}

BOOL CCSDemoClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_EDITPort, _T("8000"));
	SetDlgItemText(IDC_IPADDRESSIP, _T("127.0.0.1"));
	//SetDlgItemText(IDC_EDITRootDN, _T("CN=DemoCA,O=JIT,C=CN"));

	m_ChkCert.SetCheck(BST_CHECKED);

    return TRUE;
}

//TCHAR strCertSettings[MAX_DATA_LEN] = _T("<?xml version=\"1.0\" encoding=\"gb2312\"?><authinfo><liblist><lib type=\"CSP\" version=\"1.0\" dllname=\"\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib><lib type=\"SKF\" version=\"1.1\" dllname=\"SERfR01DQUlTLmRsbA==\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib><lib type=\"SKF\" version=\"1.1\" dllname=\"U2h1dHRsZUNzcDExXzMwMDBHTS5kbGw=\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib><lib type=\"SKF\" version=\"1.1\" dllname=\"U0tGQVBJLmRsbA==\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib></liblist></authinfo>");

//获取 KEY类型管理信息
//KEY类型管理信息 是从网关服务器导出。
// KEY类型管理信息 由应用程序自行管理。
// 在本示例中，假设 KEY类型管理信息 存放在 KeySettings.txt 文件中。
DWORD CCSDemoClientDlg::getCertSettings(char *strCertSettings)
{
#ifdef USE_JIT_SAFEMODULE
	//使用密码模块证书
	char sKeyInfo[MAX_DATA_LEN] = "<?xml version=\"1.0\" encoding=\"gb2312\"?><authinfo><liblist><lib type=\"CSP\" version=\"1.0\" dllname=\"\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib><lib type=\"SKF\" version=\"1.1\" dllname=\"SklUU2FmZU1vZGVsLmRsbA\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib></liblist></authinfo>";
#else
	//使用龙脉key证书
	char sKeyInfo[MAX_DATA_LEN] = "<?xml version=\"1.0\" encoding=\"gb2312\"?><authinfo><liblist><lib type=\"CSP\" version=\"1.0\" dllname=\"\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib><lib type=\"SKF\" version=\"1.1\" dllname=\"bXRva2VuX2dtMzAwMC5kbGw\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib></liblist></authinfo>";
#endif
	
	if(NULL != strCertSettings)
		strcpy_s(strCertSettings,MAX_DATA_LEN,sKeyInfo);

	/*
	int nReadLen = 0;
	FILE *fp = NULL;
	fp = fopen("KeySettings.txt", "rb"); //在本示例中，假设 KEY类型管理信息 存放在 KeySettings.txt 文件中。
	if(fp != NULL)
	{
		nReadLen = fread(strCertSettings, sizeof(CHAR), 4096, fp);
		fclose(fp);
		fp = NULL;
		return nReadLen;
	}
	*/
	return 0;
}

void CCSDemoClientDlg::OnBnClickedBtnAuth()
{
    ///////////////////////////////////////////////////////////////////////////////
    // 入口参数检查部分
    ///////////////////////////////////////////////////////////////////////////////
	DWORD nLen = 0,dwError = 0;

    // 参数状态检查
    if (m_ChkCert.GetCheck()!= BST_CHECKED && m_ChkPwd.GetCheck()!= BST_CHECKED)
    {
        //MessageBox(_T("请选择一个认证模式。"), _T("提示"), MB_OK | MB_ICONINFORMATION);
		//
        return;
    }

    // 获取用户名和密码
	TCHAR strUserName[STRING_LENGTH] = {0}, strPassword[STRING_LENGTH] = {0};
    if( m_ChkPwd.GetCheck()== BST_CHECKED)
    {
        GetDlgItemText(IDC_EDIT_USERNAME, strUserName,STRING_LENGTH);
        GetDlgItemText(IDC_EDIT_PASSWORD, strPassword,STRING_LENGTH);
        if( _tcslen(strUserName) == 0 || _tcslen(strPassword) == 0)
        {
            //MessageBox(_T("用户名或密码不能为空。"), _T("提示"), MB_OK | MB_ICONINFORMATION);
			//
            return;
        }
    }

    // 获取应用服务的IP和端口
	TCHAR strServerPort[STRING_LENGTH] = {0};
    GetDlgItemText(IDC_EDITPort, strServerPort,STRING_LENGTH);
    if( _tcslen(strServerPort) == 0)
    {
        //MessageBox(_T("请输入服务器Port。"), _T("提示"), MB_OK | MB_ICONINFORMATION);
		//
        return;
    }

    if( m_ServerIPCtrl.IsBlank())
    {
        //MessageBox(_T("请输入服务器IP。"), _T("提示"), MB_OK | MB_ICONINFORMATION);
		//
        return;
    }
	
	TCHAR strServerIP[STRING_LENGTH] = {0};
    GetDlgItemText(IDC_IPADDRESSIP, strServerIP,STRING_LENGTH);

    // 获取根证书主题
	TCHAR strRootDN[STRING_LENGTH] = {0};
    GetDlgItemText(IDC_EDITRootDN, strRootDN,STRING_LENGTH);

	//获取KEY类型管理信息, 此信息由网关服务器导出
	char szCertSettings[MAX_DATA_LEN] = {0};
	getCertSettings(szCertSettings);
	TCHAR *strCertSettings = _bstr_t(szCertSettings);

    ///////////////////////////////////////////////////////////////////////////////
    // 生成客户端到应用服务器的认证信息
    ///////////////////////////////////////////////////////////////////////////////
	TCHAR strOriginal[MAX_PATH] = {0};
    LPTSTR pAuthInfo = NULL;

	m_pClientAuth = new CClientAuth();
	if(m_pClientAuth != NULL)
	{
		//获取认证原文
		dwError = getRandOriginal(strServerIP, strServerPort, strOriginal);
		//显示错误信息
			switch(dwError)
			{
			case AUTH_CODE_FAIL:
				MessageBox(_T("获取原文失败"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				goto End;
			case AUTH_CODE_SOCKET_FAIL:
				//MessageBox(_T("网络通讯初始化失败"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				//
				goto End;
			case AUTH_CODE_CONNECT_FAIL:
				//MessageBox(_T("连接服务器失败"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				//
				goto End;
			case AUTH_CODE_SEND_INFO_FAIL:
				//MessageBox(_T("发送请求信息失败"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				//
				goto End;
			case AUTH_CODE_RECV_INFO_FAIL:
				MessageBox(_T("接收响应信息失败"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				goto End;
			default:
				break;
			}

		///////////////////////////////////////////////////////////////////////////////证书认证
		if( m_ChkCert.GetCheck()==BST_CHECKED)
		{
			///////////////////////////////////////////////////////////////////////////////
			// 证书认证，生成认证请求XML
			///////////////////////////////////////////////////////////////////////////////
			//获取缓冲区大小
			dwError = m_pClientAuth->StartAuth( NULL, nLen, strOriginal, strCertSettings, strRootDN, NULL, NULL, 1, 0);
			if(dwError == AUTH_CODE_SUCCESS)
			{
				if(nLen > 0)
				{
					pAuthInfo = new TCHAR[nLen + 1];
					if(pAuthInfo != NULL)
					{
						memset(pAuthInfo, 0,sizeof(TCHAR)*(nLen+1));
						dwError = m_pClientAuth->StartAuth( pAuthInfo, nLen, strOriginal, strCertSettings, strRootDN, NULL, NULL, 1, 0);
					}
				}
			}
			
			
		}
		///////////////////////////////////////////////////////////////////////////////证书认证

		if( m_ChkPwd.GetCheck()==BST_CHECKED)
		{
			///////////////////////////////////////////////////////////////////////////////
			// 口令认证，生成认证请求XML
			///////////////////////////////////////////////////////////////////////////////
			//获取缓冲区大小
			dwError = m_pClientAuth->StartAuth( NULL, nLen, strOriginal, strCertSettings, strRootDN, strUserName, strPassword, 2);
			if(dwError == AUTH_CODE_SUCCESS)
			{
				if(nLen > 0)
				{
					pAuthInfo = new TCHAR[nLen + 1];
					if(pAuthInfo != NULL)
					{
						memset(pAuthInfo, 0,sizeof(TCHAR)*(nLen+1));
						dwError = m_pClientAuth->StartAuth( pAuthInfo, nLen, strOriginal, strCertSettings, strRootDN, strUserName, strPassword, 2);
					}
				}
			}
		}

		//显示错误信息
			switch(dwError)
			{
			case AUTH_CODE_FAIL:
				MessageBox(_T("认证失败"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				goto End;
			case AUTH_CODE_CREATE_PNXCLIENT_FAIL:
				MessageBox(_T("请安装PNXClient认证插件"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				goto End;
			case AUTH_CODE_INIT_PNXCLIENT_FAIL:
				MessageBox(_T("初始化PNXClient认证插件失败"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				goto End;
			case AUTH_CODE_SELECT_CERT_FAIL:
				MessageBox(_T("选择认证证书失败"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				goto End;
			case AUTH_CODE_AUTH_QUERY_FAIL:
				MessageBox(_T("生成认证原文认证请求信息失败"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				goto End;
			case AUTH_CODE_NOT_ENOUGH_MEMORY:
				//MessageBox(_T("认证请求没有足够的内存"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				//
				goto End;
			default:
				break;
			}

			//发送认证请求并获取返回结果
			dwError = verifyAuthRequest(strServerIP, strServerPort, pAuthInfo);
			//显示错误信息
			switch(dwError)
			{
			case AUTH_CODE_SUCCESS:
				MessageBox(_T("认证成功"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				goto End;
			case AUTH_CODE_DENY:
				MessageBox(_T("没有权限"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				goto End;
			case AUTH_CODE_FAIL:
				MessageBox(_T("认证失败"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				goto End;
			case AUTH_CODE_SOCKET_FAIL:
				//MessageBox(_T("网络通讯初始化失败"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				//
				goto End;
			case AUTH_CODE_CONNECT_FAIL:
				//MessageBox(_T("连接服务器失败"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				//
				goto End;
			case AUTH_CODE_SEND_INFO_FAIL:
				//MessageBox(_T("发送请求信息失败"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				//
				goto End;
			case AUTH_CODE_RECV_INFO_FAIL:
				//MessageBox(_T("接收响应信息失败"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				//
				goto End;
			default:
				break;
			}
End:
		//释放内存
		if(pAuthInfo != NULL)
		{
			delete pAuthInfo;
			pAuthInfo = NULL;
		}
		if(m_pClientAuth != NULL)
		{
			delete m_pClientAuth;
			m_pClientAuth = NULL;
		}
	}
    
    return;
}

DWORD CCSDemoClientDlg::getRandOriginal(const PTCHAR strServerIP, const PTCHAR strServerPort, PTCHAR strOriginal)
{
	DWORD dwRet = AUTH_CODE_SUCCESS;
    WSADATA wsaData;
    if(strServerIP == NULL || strServerPort == NULL || strOriginal == NULL)
	{
		dwRet = AUTH_CODE_FAIL;
		return dwRet;
	}
    int nRet = ::WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (nRet != 0)
    {
		dwRet = AUTH_CODE_SOCKET_FAIL;
        return dwRet;
    }

    SOCKET socketServer = (int)::socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in connServerAddr;
    connServerAddr.sin_family = AF_INET;
    connServerAddr.sin_port = htons(atoi(_bstr_t(strServerPort)));
    connServerAddr.sin_addr.s_addr = inet_addr(_bstr_t(strServerIP));
    // 开始连接应用服务器
    int error = ::connect(socketServer, (struct sockaddr *)&connServerAddr, sizeof(struct sockaddr));
    if (error == SOCKET_ERROR)
    {
        closesocket(socketServer);
        ::WSACleanup();

		dwRet = AUTH_CODE_CONNECT_FAIL;
        return dwRet;
    }
    // 取得认证原文
    TCHAR strRequesInfo[] = _T("OriginalService");
    // 开始发送认证原文请求
    
    string strSendMsg = (LPCSTR)(_bstr_t(strRequesInfo));
    DWORD   dwLens = strSendMsg.length() ;
    char    *pchSendMeg = NULL ;
    pchSendMeg = new char [sizeof(DWORD) + dwLens + 1] ;
    memset(pchSendMeg, 0, sizeof(DWORD) + dwLens + 1) ;
    memcpy(pchSendMeg, &dwLens, sizeof(DWORD)) ;
    memcpy(pchSendMeg + sizeof(DWORD), strSendMsg.c_str(), (int)strSendMsg.length()) ;

    //error = ::send(socketServer, strSendMsg.c_str(), (int)strSendMsg.length(), 0);
    error = ::send(socketServer, pchSendMeg, sizeof(DWORD) + dwLens, 0);
    if (error == SOCKET_ERROR)
    {
        closesocket(socketServer);
        ::WSACleanup();

		dwRet = AUTH_CODE_SEND_INFO_FAIL;
        return dwRet;
    }

    // 接收认证原文响应结果
    char charBuffer[4096 + 1] = {0};
    error = ::recv(socketServer, charBuffer, 4096, 0);
    if (error == SOCKET_ERROR)
    {
        closesocket(socketServer);
        ::WSACleanup();

		dwRet = AUTH_CODE_RECV_INFO_FAIL;
        return dwRet;
    }
	//
	TCHAR tmpBuffer[] = _T("renzheng failed");
	//
	_tcscpy_s(strOriginal, MAX_PATH,(LPCTSTR)_bstr_t(charBuffer));
    if((_tcsicmp(strOriginal, tmpBuffer) == 0) || (0 == _tcslen(strOriginal)))
	{
		dwRet = AUTH_CODE_FAIL;
	}
	else
	{
		DWORD nLen = _tcslen((LPCTSTR)_bstr_t(charBuffer));
		strOriginal[nLen] = _T('\0');
		
	}

    closesocket(socketServer);
    ::WSACleanup();
    return dwRet;
}

DWORD CCSDemoClientDlg::verifyAuthRequest(const PTCHAR strServerIP, const PTCHAR strServerPort, const PTCHAR strRequesInfo)
{
    WSADATA wsaData;
	DWORD dwRet = AUTH_CODE_SUCCESS;
	if(strRequesInfo == NULL)
	{
		dwRet = AUTH_CODE_FAIL;
		return dwRet;
	}

    int nRet = ::WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (nRet != 0)
    {
		dwRet = AUTH_CODE_SOCKET_FAIL;
		return dwRet;
    }
    SOCKET socketServer = (int)::socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in connServerAddr;
    connServerAddr.sin_family = AF_INET;
    connServerAddr.sin_port = htons(atoi(_bstr_t(strServerPort)));
    connServerAddr.sin_addr.s_addr = inet_addr(_bstr_t(strServerIP));
    // 开始连接应用服务器
    int error = ::connect(socketServer, (struct sockaddr *)&connServerAddr, sizeof(struct sockaddr));
    if (error == SOCKET_ERROR)
    {
        closesocket(socketServer);
        ::WSACleanup();
        dwRet = AUTH_CODE_CONNECT_FAIL;
		return dwRet;
    }

    // 发送客户端认证请求信息数据到服务器
    string strSendMsg = (LPCSTR)(_bstr_t(strRequesInfo));
    DWORD   dwLens = strSendMsg.length() ;
    char    *pchSendMeg = NULL ;
    pchSendMeg = new char [sizeof(DWORD) + dwLens + 1] ;
    memset(pchSendMeg, 0, sizeof(DWORD) + dwLens + 1) ;
    memcpy(pchSendMeg, &dwLens, sizeof(DWORD)) ;
    memcpy(pchSendMeg + sizeof(DWORD), strSendMsg.c_str(), (int)strSendMsg.length()) ;


    //error = ::send(socketServer, strSendMsg.c_str(), (int)strSendMsg.length(), 0);
    error = ::send(socketServer, pchSendMeg, sizeof(DWORD) + dwLens, 0);
    
    if (error == SOCKET_ERROR)
    {
        closesocket(socketServer);
        ::WSACleanup();
		dwRet = AUTH_CODE_SEND_INFO_FAIL;
		return dwRet;
    }

    // 接收响应结果
    char charBuffer[4096 + 1] = {0};
    error = ::recv(socketServer, charBuffer, 4096, 0);
    if (error == SOCKET_ERROR)
    {
        
        closesocket(socketServer);
        ::WSACleanup();
		dwRet = AUTH_CODE_RECV_INFO_FAIL;
		return dwRet;
    }

	//
	std::wstring rzcg = L"认证成功！ ";
	std::wstring myqx = L"没有权限！ ";

	//
#if  0
	//
	if(_tcsicmp((LPCTSTR)_bstr_t(charBuffer),_T("认证成功！")) == 0)
	{
		dwRet = AUTH_CODE_SUCCESS;
	}
	else if(_tcsicmp((LPCTSTR)_bstr_t(charBuffer),_T("没有权限！")) == 0)
	{
		dwRet = AUTH_CODE_DENY;
	}
	else
	{
		dwRet = AUTH_CODE_FAIL;
	}
	//
#else
	//
	if (_tcsstr((LPCTSTR)_bstr_t(charBuffer), rzcg.c_str()) == 0)
	{
		dwRet = AUTH_CODE_SUCCESS;
	}
	else if (_tcsstr((LPCTSTR)_bstr_t(charBuffer), myqx.c_str()) == 0)
	{
		dwRet = AUTH_CODE_DENY;
	}
	else
	{
		dwRet = AUTH_CODE_FAIL;
	}


	//
#endif 




    // 显示响应
    //::MessageBox(m_hWnd,_bstr_t(charBuffer), _T("提示"), MB_OK | MB_ICONINFORMATION);

    closesocket(socketServer);
    ::WSACleanup();
	return dwRet;
}


