
#ifndef  __smLoginProc_h__
#define  __smLoginProc_h__		//  {


//
#include	"stdafx.h"
#include	"qmCaProc.h"
#include	"hgCommProc.h"
#include	"qmcStruct_defs.h"
#include	"qmcCommFunc_mis.h"
//#include	"smProc.h"



//
#define		CONST_cfgName_sm_terminalIp					"sm_terminalIp"
#define		CONST_cfgName_sm_terminalMask				"sm_terminalMask"
#define		CONST_cfgName_sm_terminalGateway			"sm_terminalGateway"
#define		CONST_cfgName_sm_terminalDns				"sm_terminalDns"
#define		CONST_cfgName_sm_terminalMcu				"sm_terminalMcu"			//  mcu IP
#define		CONST_cfgName_sm_terminalMcu2				"sm_terminalMcu2"			//  mcu IP
#define		CONST_cfgName_sm_terminalSqm				"sm_terminalSqm"			//  终端授权码，由会管服务器上产生，人工告诉

//
#define		CONST_cfgName_sm_devPrefix					"sm_devPrefix"

//
#define		CONST_cfgName_fake_usrName					"fake_usrName"
#define		CONST_cfgName_fake_passwd					"fake_passwd"

//
#define		CONST_cfgName_authType						"authType"
#define		CONST_cfgName_fake_devLoginName				"fake_devLoginName"
#define		CONST_cfgName_fake_devLoginPasswd			"fake_devLoginPasswd"
#define		CONST_cfgName_fake_talkerDesc				"fake_talkerDesc"

//
//
typedef  struct {
			char	terminal_ip[CONST_qyMaxIpLen + 1];
			char	terminal_mask[CONST_qyMaxIpLen + 1];
			char	terminal_gateway[CONST_qyMaxIpLen + 1];
			char	terminal_dns[CONST_qyMaxIpLen + 1];
			//
			char	terminal_mcu[255];						//  也可能是域名
			char	terminal_mcu2[255];						//  也可能是域名
			//
			char	terminal_sqm[255];						//  会管给与的授权码

			//
			TCHAR	devPrefix[128];							//  

			//
			TCHAR	fake_usrName[128];						//  模拟登录用的用户名
			char	fake_passwd[128];						//  模拟登录用的密码

			//
			int		authType;
			TCHAR	fake_devLoginName[128];
			char	fake_devLoginPasswd[128];
			TCHAR	fake_talkerDesc[128];

	//
}  Sm_terminal_initCfg;




//
typedef  struct {
	TCHAR							tStatusBuf[128];

	//
	Tool_ca							toolCa;


	//
	DWORD							dwLastTickCnt_chkLogin;

	//
	int								nTimes_chkLogin;
	char							mcuIp_toChk[CONST_qyMaxIpLen + 1];

	//
	DWORD							dwLastTickCnt_chk_thread_ca;

	//
	struct {

		bool						bStart_toGetUsrName;

		//
		TCHAR						tUsrName[256];

		bool						bGot_ca_usrName;

	}								dev;

	//
	struct {
		char						ca_sendData[4096];
		unsigned  int				ca_sendDataLen;
	}								cli;

	//
	struct {

		//
		struct {

			//
			bool					bGot_caServCfg;				//  得到caServCfg信息

			//
			bool					bGot_random;

			//
			bool					bGot_cli_ca_sendData;		//  得到之后，如果和mcu建立了通信，这一步就Ok

		}							loginToMcu;

		//
		DWORD						dwLastTickCnt_startToSxrz;


		//
		struct {

			//
			bool					bGot_servReply;

			//
			bool					bGot_cliData;

			//
			bool					bSent_cliData;

			//
			bool					bDone_sxrz;

			//
			bool					bSent_sqm;

			//
			bool					bDone_sqm;

			//
		}							sxrz;

		//
	}								flgs;

	//
	struct {
		struct {
			//
			Param_sxrz_servReply	param_sxrz_servReply;

		}							serv;

		//
		struct {
			char					cert[4096];
			char					signData[256];

		}							cli;

	}								sxrz;

	//
	int								nTimes_toReadKey;

	//
}									Var_ca_dev_qmc;


//
//
typedef  struct {
	TCHAR							tStatusBuf[128];


	//
	Tool_ca							toolCa;

	//
	bool							bExists_usrKey;								//  key存在

	//
	DWORD							dwTickCnt_lastChkUsrKey;					//  定期检测key
	bool							bTryToChkUsrKey;							//  设置此标志位表示检测key


	//
	struct {
		//
		char						keyPasswd[128];

		//
		bool						bFailed_getUsrName;							//  取用户信息失败，一般为密码错误
		//
		int							iPinRetryCount;

		//
		bool						bGot_ca_cliUsrDataResp;						//  身份验证ok

		//
		TCHAR						tUsrName[256];

		//
		bool						bSent_cliUsrData;

		//
		bool						bDone;

		//
		int							iRc;

		TCHAR						tRcDesc[256];

		//
		struct {
			TCHAR					tUsrName[128];
			char					passwd[128];

		}							loginUsingName;

	}								usrLogin;

	//


}									Var_ca_usr_qmc;




//
struct  __ctx_sm_t {

		//
		Sm_terminal_initCfg		smTerminalInitCfg;

		//
		char					caGwIp[15 + 1];
		int						caGwPort;
		char					hgGwIp[15 + 1];
		int						hgGwPort;
		char					caYqServIp[15 + 1];
		int						caYqServPort;
		char					debugIp[15 + 1];
		int						debugPort;

		//
		Var_ca_dev_qmc			ca_dev;
		//
		long					tn0_ca;

		//
		Var_ca_usr_qmc			ca_usr;

		//
		struct {
			MeetingInfo			meetingInfos[MAX_meetingInfos];

			//
			struct {
				int				cnt;
				P2pInfo			mems[MAX_p2pInfos];
			}					p2pInfos;
			//
			bool				bDone_p2p;
			
			struct {
				bool		bWarn;
				TCHAR		p2pContent[128];
			}					p2pWarn;

			struct {
				bool		bMsg;
				TCHAR		formTermName[128];
				QY_MESSENGER_ID			idInfo_grp;
				int			p2pLevel;

			}					p2pMsg;
			struct {
				int			n_a;
				int			n_v;



			}				avDev;

			//
			struct {
				int intervalInS_xt;  //心跳间隔
				int	intervalInS_over; //超时时间
				int system_level;	//系统密级


			}		systemConfig;

			struct {
				int bPortEnd;   //菜单的端口管理权限打开
			}	 menuPower;


		}						hg;

		//
		bool					bNeedRestart;
		int						nTimes_beforeRestart;

		//
		struct {

			//
			char				usrName[128];
			char				passwd[32];

			//
			bool				bUsrLogined;

			//
			struct {
				bool			bExists_usrKey;				//  是否采用用户key登录
			}					loginState;

			//
		}						usrLogin_sm;


		
};




//
extern  "C"  BOOL  bMaskValid(char* ip);




//
bool bGetSmTerminalInitCfg(TCHAR* cfgFileName, Sm_terminal_initCfg* pCfg);
int saveSmTerminalInitCfg(Sm_terminal_initCfg* pCfg, TCHAR* cfgFileName);




//
extern  "C"  BOOL  bGetCaServCfg(QY_ENV * pEnv, char* serverIp, unsigned  short  serverPort, MIS_CNT * pMisCnt, QY_COMM_AUTHINFO_MIS * pAuthInfo, int  serviceId, char* ver, QY_ENC_CTX * pCommEncCtx, __int64  i64StartTime_base,  SOCK_TIMEOUT * pTo);
extern  "C"  BOOL  bGetCaRandom(QY_ENV * pEnv, char* serverIp, unsigned  short  serverPort, MIS_CNT * pMisCnt, QY_COMM_AUTHINFO_MIS * pAuthInfo, int  serviceId, char* ver, QY_ENC_CTX * pCommEncCtx, __int64 i64StartTime_base,  SOCK_TIMEOUT * pTo);

//
void smLogin_onTimer(HWND  hDlgLogin, DLG_mcClientLogon_var* pm_var, Ctx_sm* pCtxSm, bool* pbNeedAccept);
void  smLogin_clean(SmLoginVar& m_smLoginVar, Ctx_sm* pCtxSm);
//
int sm_sxrz_yq(QIS_ca_req* p);

//
int smUsrLogin_onTimer(HWND  hDlgLogin, DLG_mcClientLogon_var* pm_var, Ctx_sm* pCtxSm, bool& bNeedShowLogon, bool& bNeedClose, int terminal_type);
void smUsrLogin_clean(SmUsrLoginVar& m_usrVar, Ctx_sm* pCtxSm);





//
#endif  //  }


