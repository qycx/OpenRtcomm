// CSDemoServerDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "CSDemoServer.h"
#include "CSDemoServerDlg.h"

#include "CServerAuth.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// 对话框数据
    enum { IDD = IDD_ABOUTBOX };

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// CCSDemoServerDlg 对话框
CCSDemoServerDlg::CCSDemoServerDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CCSDemoServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ReciveClientReqThreadHandle = NULL;
	m_ListenThreadStopFlag = FALSE;
	m_RadioGroupConnMode = 0;
	m_pServerAuth = NULL;

	

}

CCSDemoServerDlg::~CCSDemoServerDlg()
{

	if(m_pServerAuth != NULL)
	{

		delete m_pServerAuth;
		m_pServerAuth = NULL;
	}

	//　停用线程
	
    m_ListenThreadStopFlag = TRUE;

	// 关闭Socket
    if (m_ListenSocket!=INVALID_SOCKET)
    {
        closesocket(m_ListenSocket);
        m_ListenSocket = INVALID_SOCKET; 
    }
    // 如果线程还没有退出，强制退出
    DWORD dwExitCode = 0;
    GetExitCodeThread(m_ReciveClientReqThreadHandle, &dwExitCode);
    if (dwExitCode!=STILL_ACTIVE)
    {
        m_ReciveClientReqThreadHandle = NULL;
    }

    if (m_ReciveClientReqThreadHandle!=NULL)
    {
        TerminateThread(m_ReciveClientReqThreadHandle, 0);
        m_ReciveClientReqThreadHandle = NULL;
    }
	m_ListenThreadStopFlag = FALSE;

    WSACleanup();
}

void CCSDemoServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_StartServer);
	DDX_Control(pDX, IDC_IPADDRESS_GATEWAY, m_GateWayIP);
	DDX_Control(pDX, IDC_IPADDRESS_SERVER, m_ServerIP);
	DDX_Radio(pDX, IDC_RADIO_UNECRYPT, m_RadioGroupConnMode);
}

BEGIN_MESSAGE_MAP(CCSDemoServerDlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDOK, &CCSDemoServerDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &CCSDemoServerDlg::OnBnClickedCancel)
    ON_BN_CLICKED(IDC_BUTTON_STOP, &CCSDemoServerDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_RADIO_UNECRYPT, &CCSDemoServerDlg::OnBnClickedRadioConnMode)
	ON_BN_CLICKED(IDC_RADIO_SINGLE_SSL, &CCSDemoServerDlg::OnBnClickedRadioConnMode)
END_MESSAGE_MAP()

// CCSDemoServerDlg 消息处理程序
BOOL CCSDemoServerDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // 将“关于...”菜单项添加到系统菜单中。

    // IDM_ABOUTBOX 必须在系统命令范围内。
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE); // 设置大图标
    SetIcon(m_hIcon, FALSE); // 设置小图标

    // TODO: 在此添加额外的初始化代码

	SetDlgItemText(IDC_EDIT_SERVERPORT, _T("8000"));
    //
	SetDlgItemText(IDC_IPADDRESS_SERVER, _T("127.0.0.1"));
    SetDlgItemText(IDC_IPADDRESS_SERVER, _T("10.0.1.35"));
    //SetDlgItemText(IDC_IPADDRESS_SERVER, _T("192.168.1.6"));

    //
	SetDlgItemText(IDC_EDIT_GATEWATPORT, _T("6180"));
	SetDlgItemText(IDC_IPADDRESS_GATEWAY, _T("127.0.0.1"));
	//SetDlgItemText(IDC_IPADDRESS_GATEWAY, _T("192.168.9.120"));
    SetDlgItemText(IDC_IPADDRESS_GATEWAY, _T("124.207.188.210"));
    //
	SetDlgItemText(IDC_EDIT_APPFLAG, _T("testApp"));

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCSDemoServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CCSDemoServerDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作矩形中居中
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 绘制图标
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CCSDemoServerDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CCSDemoServerDlg::OnBnClickedButtonStop()
{
    
	if(m_pServerAuth != NULL)
	{
		//
		delete m_pServerAuth;
		m_pServerAuth = NULL;
	}
	//　停用线程
	
    m_ListenThreadStopFlag = TRUE;

	// 关闭Socket
    if (m_ListenSocket!=INVALID_SOCKET)
    {
        closesocket(m_ListenSocket);
        m_ListenSocket = INVALID_SOCKET; 
    }
    // 如果线程还没有退出，强制退出
    DWORD dwExitCode = 0;
    GetExitCodeThread(m_ReciveClientReqThreadHandle, &dwExitCode);
    if (dwExitCode!=STILL_ACTIVE)
    {
        m_ReciveClientReqThreadHandle = NULL;
    }

    if (m_ReciveClientReqThreadHandle!=NULL)
    {
        TerminateThread(m_ReciveClientReqThreadHandle, 0);
        m_ReciveClientReqThreadHandle = NULL;
    }
	m_ListenThreadStopFlag = FALSE;
    
    m_StartServer.EnableWindow(TRUE);
}

void CCSDemoServerDlg::OnBnClickedCancel()
{
    OnBnClickedButtonStop();
    OnCancel();
}

// 认证处理过程
void CCSDemoServerDlg::OnBnClickedOk()
{
    // 输入参数正确性检查
	TCHAR strServerPort[MAX_PATH] = {0};
    GetDlgItemText(IDC_EDIT_SERVERPORT, strServerPort,MAX_PATH);
    if ( _tcslen(strServerPort) == 0)
    {
        MessageBox(_T("请输入服务器Port。"), _T("提示"), MB_OK | MB_ICONINFORMATION);
        return;
    }

    if (m_ServerIP.IsBlank())
    {
        MessageBox(_T("请输入服务器IP。"), _T("提示"), MB_OK | MB_ICONINFORMATION);
        return;
    }
	// 读取IP地
    TCHAR strServerIP[MAX_PATH] = {0};
    GetDlgItemText(IDC_IPADDRESS_SERVER, strServerIP,MAX_PATH);
	if (_tcslen(strServerIP) == 0)
    {
        MessageBox(_T("请输入服务器IP。"), _T("提示"), MB_OK | MB_ICONINFORMATION);
        return;
    }

    TCHAR strGateWayPort[MAX_PATH] = {0};
    GetDlgItemText(IDC_EDIT_GATEWATPORT, strGateWayPort,MAX_PATH);
    if (_tcslen(strGateWayPort) == 0)
    {
        MessageBox(_T("请输入网关Port。"), _T("提示"), MB_OK | MB_ICONINFORMATION);
        return;
    }

    if (m_GateWayIP.IsBlank())
    {
        MessageBox(_T("请输入网关IP。"), _T("提示"), MB_OK | MB_ICONINFORMATION);
        return;
    }
	// 读取IP地
    TCHAR strGateWayIP[MAX_PATH] = {0};
    GetDlgItemText(IDC_IPADDRESS_GATEWAY, strGateWayIP, MAX_PATH);
	if ( _tcslen(strGateWayIP) == 0)
    {
        MessageBox(_T("请输入网关IP。"), _T("提示"), MB_OK | MB_ICONINFORMATION);
        return;
    }

    TCHAR strAppFlag[MAX_PATH] = {0};
    GetDlgItemText(IDC_EDIT_APPFLAG, strAppFlag, MAX_PATH);
    if (_tcslen(strAppFlag) == 0)
    {
        MessageBox(_T("请输入应用标识。"), _T("提示"), MB_OK | MB_ICONINFORMATION);
        return;
    }
	bool bIsPlain = false;
	if(m_RadioGroupConnMode == 0)
	{
		bIsPlain = true;
	}
	
	//指定XML报文版本为11，即 随机数由网关生成
	int nXMLVer = 11;

	//创建对象
	m_pServerAuth = new CServerAuth(strGateWayIP, strGateWayPort, strAppFlag, bIsPlain, nXMLVer);
	if(m_pServerAuth == NULL)
	{
		MessageBox(_T("对象创建失败！"),_T("提示"),MB_OK);
	}

	//　启用线程
	DWORD dwThreadId = 0;
	m_ReciveClientReqThreadHandle = CreateThread(NULL, 0, ReciveClientRequestThread, this, 0, &dwThreadId);
	if (m_ReciveClientReqThreadHandle!=NULL)
	{
		//启用线程成功
		//禁用按键
		m_StartServer.EnableWindow(FALSE);
	}
	else
	{
		MessageBox(_T("线程启动失败！"),_T("提示"),MB_OK);
	}

	

}

//　主要接收客户端请求，并组织请求信息到认证服务器
DWORD WINAPI CCSDemoServerDlg::ReciveClientRequestThread(LPVOID lpParameter)
{
	DWORD dwError = 0;

    // 参数检查
    if (lpParameter == NULL)
        return -1;

    CCSDemoServerDlg* pDlg = (CCSDemoServerDlg*)lpParameter;

	//　初始化SOCKET
    WSADATA wsaData;
    int nRet = WSAStartup(MAKEWORD(2, 2), &wsaData);

    pDlg->m_ListenSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (INVALID_SOCKET == pDlg->m_ListenSocket)
    {
		pDlg->MessageBox(_T("网络通讯初始化失败"),_T("提示"),MB_OK);
        return -1;
    }

    // 读取IP地
    TCHAR strServerIP[MAX_PATH] = {0};
    pDlg->GetDlgItemText(IDC_IPADDRESS_SERVER, strServerIP,MAX_PATH);
	TCHAR strServerPort[MAX_PATH] = {0};
    pDlg->GetDlgItemText(IDC_EDIT_SERVERPORT, strServerPort,MAX_PATH);

    sockaddr_in listenAddress;
    memset((void *)&listenAddress, 0x0, sizeof(listenAddress));
    listenAddress.sin_family = AF_INET;
    listenAddress.sin_addr.s_addr = inet_addr(_bstr_t(strServerIP));
    listenAddress.sin_port = htons(atoi(_bstr_t(strServerPort)));

    // 绑定端口
    int bind_ = ::bind(pDlg->m_ListenSocket, (sockaddr *)&listenAddress, sizeof(listenAddress));
    if (SOCKET_ERROR == bind_)
    {
        if(pDlg->m_ListenSocket != INVALID_SOCKET)
        {
            closesocket(pDlg->m_ListenSocket);
            pDlg->m_ListenSocket = INVALID_SOCKET;
        }
		pDlg->MessageBox(_T("绑定SOCKET失败"),_T("提示"),MB_OK);
        return -1;
    }

    // 开始监听
    int listenResult = ::listen(pDlg->m_ListenSocket, 1000);
    if (SOCKET_ERROR == listenResult)
    {
        if(pDlg->m_ListenSocket != INVALID_SOCKET)
        {
            closesocket(pDlg->m_ListenSocket);
            pDlg->m_ListenSocket = INVALID_SOCKET;
        }
		pDlg->MessageBox(_T("监听SOCKET失败"),_T("提示"),MB_OK);
        return -1;
    }
	
			
	//启动监听
	sockaddr_in acceptSocketAddr;
    memset((void *)&acceptSocketAddr, 0x0, sizeof(acceptSocketAddr));
    int client_addr_size = sizeof(acceptSocketAddr);
			
	while (!pDlg->m_ListenThreadStopFlag)
	{
    
		// 等待客户端认证连接
		SOCKET clientsocket = accept(pDlg->m_ListenSocket, (struct sockaddr *)&acceptSocketAddr, &client_addr_size);
	
		if (INVALID_SOCKET == clientsocket)
		{
			TCHAR str[MAX_PATH] = {0};
			int iLastError = WSAGetLastError();

			if(iLastError==WSAENOTSOCK)
			{
				break;
			}

			continue;
		}
		
		///////////////////////////////////////////////////
		// 接收客户端认证原文请求信息
		///////////////////////////////////////////////////
		char recvBuf[1024 * 8] = {0};
        char *pchrecvBuf = recvBuf ;
		unsigned long recvBufLen = 1024 * 8;
        unsigned long ulFinishRecvLen = 0 ;
        int     recvRet = 0 ;

        do 
        {
            recvRet = recv(clientsocket, recvBuf+ulFinishRecvLen, recvBufLen, 0);            
            if(SOCKET_ERROR == recvRet)
            {
                break ;
            }
            if (recvRet == 0)
            {
                break ;
            }
            if (*(DWORD*)&recvBuf + sizeof(DWORD) == ulFinishRecvLen + recvRet)
            {
                ulFinishRecvLen = ulFinishRecvLen + recvRet ;
                break ;
            }
            ulFinishRecvLen = ulFinishRecvLen + recvRet ;
        } while (TRUE);


        if (*(DWORD*)&recvBuf + sizeof(DWORD) != ulFinishRecvLen)
        {
            TCHAR strRndResponeInfo[MAX_PATH] = {0};
            _tcscpy(strRndResponeInfo, _T("认证失败！接收到的数据格式不对！"));
            string strRndReponse = _bstr_t(strRndResponeInfo);
            send(clientsocket, strRndReponse.c_str(), (int)strRndReponse.length(), 0);
            closesocket(clientsocket);
            pDlg->SetDlgItemText(IDC_EDIT_STATUS, strRndResponeInfo);
            pDlg->UpdateData(FALSE) ;
            continue ;
        }
        else
        {
            pchrecvBuf = pchrecvBuf + sizeof(DWORD) ;
        }

		if (strcmp((char *)pchrecvBuf, "OriginalService") == 0)
		{
			// 发送到认证服务器，取得认证原文，同时回应客户端
			DWORD dwLen = 0;
			LPTSTR pRndResponeInfo = NULL;
			string strRndReponse;
			dwError = pDlg->m_pServerAuth->GetRandOriginal(NULL, dwLen);
			if(dwError == AUTH_CODE_SUCCESS)
			{
				if(dwLen > 0)
				{
					pRndResponeInfo = new TCHAR[dwLen + 1];
					if(pRndResponeInfo != NULL)
					{
						dwError = pDlg->m_pServerAuth->GetRandOriginal(pRndResponeInfo, dwLen);
						if(dwError == AUTH_CODE_SUCCESS)
						{
							//成功则发送原文信息
							strRndReponse = _bstr_t(pRndResponeInfo);
							
						}

						delete pRndResponeInfo;
						pRndResponeInfo = NULL;
					}
				}
			}
			if(dwError != AUTH_CODE_SUCCESS)
			{
				//失败
				TCHAR strRndResponeInfo[MAX_PATH] = {0};
				_tcscpy(strRndResponeInfo, _T("认证失败！"));
				strRndReponse = _bstr_t(strRndResponeInfo);
			}

			//发送随机数回客户端 
			send(clientsocket, strRndReponse.c_str(), (int)strRndReponse.length(), 0);
			closesocket(clientsocket);
			
			continue;
		}

		sockaddr_in stClientInfo = {0};
		int nLen = sizeof(stClientInfo);

		getpeername(clientsocket, (sockaddr *)&stClientInfo, &nLen);
		// 发送到认证服务器认证，并处理服务器响应信息，同时回应客户端认证成功

        //
        LPCTSTR  clientIp = (LPCTSTR)_bstr_t(inet_ntoa(stClientInfo.sin_addr));
        clientIp = _T("1.1.1.1");
        int nn = strlen(pchrecvBuf);
		
		TCHAR strAuthReponseInfo[MAX_PATH] = {0};
		//dwError = pDlg->m_pServerAuth->StartAuth(_bstr_t((LPCSTR)pchrecvBuf), (LPCTSTR)_bstr_t(inet_ntoa(stClientInfo.sin_addr)));
        dwError = pDlg->m_pServerAuth->StartAuth(_bstr_t((LPCSTR)pchrecvBuf), clientIp);
		if(dwError == AUTH_CODE_SUCCESS)
		{
			DWORD nLength = 0;
			PTCHAR pMessageCode = NULL;
			_tcscpy(strAuthReponseInfo, _T("认证成功！"));	
		}
		else if (dwError == AUTH_CODE_DENY)
		{
			_tcscpy(strAuthReponseInfo, _T("没有权限！"));
		}
		else
		{
			_tcscpy(strAuthReponseInfo, _T("认证失败！"));
		}

		string strReponse = _bstr_t(strAuthReponseInfo);
		send(clientsocket, strReponse.c_str(), (int)strReponse.length(), 0);
		closesocket(clientsocket);

		//显示认证结果
		pDlg->DisplayAuthResult();
		
	}// end while
	
	 // 销毁内存信息
    if(pDlg->m_ListenSocket != INVALID_SOCKET)
    {
        closesocket(pDlg->m_ListenSocket);
        pDlg->m_ListenSocket = INVALID_SOCKET;
    }
	pDlg->m_StartServer.EnableWindow(TRUE);

    return 0;
}




void CCSDemoServerDlg::DisplayAuthResult()
{
	DWORD dwLen = 0, nLength = 0;
	TCHAR strAuthResult[MAX_DATA_LENGTH] = {0};
    long lTotalLength = MAX_DATA_LENGTH;
    TCHAR* strResult = new TCHAR[MAX_DATA_LENGTH];
    memset(strResult, 0, MAX_DATA_LENGTH * sizeof(TCHAR));
	PTCHAR pMessageCode = NULL;
	BOOL bIsSuccess = FALSE;

	if(m_pServerAuth->GetMessageCode( NULL, nLength) == FALSE)
	{
		if(nLength == 0)
		{
			//当返回FALSE并且错误码长度为0时，表示认证成功
			bIsSuccess = TRUE;
		}
	}

	_stprintf_s(strResult, lTotalLength - dwLen - 1,_T("=====================================================\r\n"));
	dwLen += _tcslen(strResult);
    memset(strAuthResult,0,MAX_DATA_LENGTH*sizeof(TCHAR));
	if(bIsSuccess)
	{
		LPCTSTR sAcr = m_pServerAuth->GetAccessControlResult();
		if (NULL != sAcr && 0 == _tcsicmp(sAcr,_T("Deny")))
		{
			_stprintf_s(strAuthResult, _T("认证状态：true（true：成功，false：失败）\r\n没有权限!"));
		}
		else
			_stprintf_s(strAuthResult, _T("认证状态：true（true：成功，false：失败）\r\n"));
		_tcscpy(strResult + dwLen, strAuthResult);
		dwLen += _tcslen(strAuthResult);
	}
	else
	{
		_stprintf_s(strAuthResult, _T("认证状态：false（true：成功，false：失败）\r\n"));
		_tcscpy(strResult + dwLen, strAuthResult);
		dwLen += _tcslen(strAuthResult);
		//获取错误码
		if(m_pServerAuth->GetMessageCode( NULL, nLength))
		{
			if(nLength > 0)
			{
				pMessageCode = new TCHAR[nLength + 1];
				if(pMessageCode != NULL)
				{
					if(m_pServerAuth->GetMessageCode( pMessageCode, nLength))
					{
						memset(strAuthResult,0,MAX_DATA_LENGTH*sizeof(TCHAR));
						_stprintf_s(strAuthResult, _T("错误码：%s\r\n"), pMessageCode);
						_tcscpy(strResult + dwLen, strAuthResult);
						dwLen += _tcslen(strAuthResult);
					}
					delete[] pMessageCode;
					pMessageCode = NULL;
				}
			}
		}
	}
	
	if(bIsSuccess)
	{
		_tcscpy(strResult + dwLen, _T("\r\n"));
		dwLen += _tcslen(_T("\r\n"));

		_tcscpy(strResult + dwLen, _T("-----------------------------------------------------\r\n"));
		dwLen += _tcslen(_T("-----------------------------------------------------\r\n"));
		int nAttributesCount = m_pServerAuth->GetAttributeSize();
		for(int i =0;i<nAttributesCount;i++)
		{
			TCHAR* cAttName = NULL;
			TCHAR* AttributeValue = NULL;
			TCHAR* AttributeNameSpace = NULL;
            long NameLength = 0, ValueLength = 0, SpaceLength = 0;
            m_pServerAuth->GetAttribute(i, cAttName, NameLength, AttributeValue, ValueLength, AttributeNameSpace, SpaceLength);
            if (NameLength != 0)
            {
                cAttName = new TCHAR[NameLength];
            }
            if (ValueLength != 0)
            {
                AttributeValue = new TCHAR[ValueLength];
            }
            if (SpaceLength != 0)
            {
                AttributeNameSpace = new TCHAR[SpaceLength];
            }
            m_pServerAuth->GetAttribute(i, cAttName, NameLength, AttributeValue, ValueLength, AttributeNameSpace, SpaceLength);
            
            long lTmpLength = NameLength + ValueLength + SpaceLength + 256;
            TCHAR* strAuthResultTmp = new TCHAR[lTmpLength];
            memset(strAuthResultTmp, 0, lTmpLength * sizeof(TCHAR));
			_stprintf_s(strAuthResultTmp, lTmpLength, _T("属性名称：%s\r\n属性值：%s\r\n名字空间：%s\r\n"), cAttName, AttributeValue, AttributeNameSpace);
            if (cAttName != NULL)
            {
                delete[] cAttName;
            }
            if (AttributeValue != NULL)
            {
                delete[] AttributeValue;
            }
            if (AttributeNameSpace != NULL)
            {
                delete[] AttributeNameSpace;
            }

            if (lTotalLength - dwLen < lTmpLength)
            {
                int i = lTmpLength / MAX_DATA_LENGTH;
                long lIncrementLength = (i + 1) * MAX_DATA_LENGTH;
                lTotalLength += lIncrementLength;
                TCHAR* pNewBuf = new TCHAR[lTotalLength];
                memset(pNewBuf, 0, lTotalLength * sizeof(TCHAR));
                memcpy(pNewBuf, strResult, dwLen * sizeof(TCHAR));
                delete[] strResult;
                strResult = pNewBuf;
            }

			_tcscpy(strResult + dwLen, strAuthResultTmp);
			dwLen += _tcslen(strAuthResultTmp);
            if (strAuthResultTmp != NULL)
            {
                delete[] strAuthResultTmp;
            }
		}

		
	  
	}

    SetDlgItemText(IDC_EDIT_STATUS, strResult);

    if (strResult != NULL)
    {
        delete[] strResult;
    }
}

void CCSDemoServerDlg::OnBnClickedRadioConnMode()
{
	BOOL bSSL = FALSE;
	CButton* pButton = (CButton*)GetDlgItem(IDC_RADIO_SINGLE_SSL);
	if (NULL != pButton)
	{
		bSSL = ( 1 == pButton->GetCheck()) ? TRUE:FALSE;
	}

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_GATEWATPORT);
	if (bSSL)
	{
		if (NULL != pEdit)
			pEdit->SetWindowText(_T("443"));
	}
	else
	{
		if (NULL != pEdit)
			pEdit->SetWindowText(_T("6180"));
	}
	UpdateData(TRUE);
}
