
#ifndef  __myCmdParams_open_h__  
#define  __myCmdParams_open_h__		//  {

//
#include	"tmpStrFunc.h"
#include	"tmpDefs_open.h"
#include	"qytcharcommproc.h"


//
#define		CONST_caRet_getRandomErr		-10


//
//
//
inline void	M_getCmd(TCHAR* pT, TCHAR* tBuf, int  cnt_tBuf)
{
	TCHAR* pT2;
	int n;

	//
	//pT2 = _tcschr(pT, _T('-'));
	pT2 = _tcschr(pT, _T(' '));			//  必须用空格

	//
	if (pT2) {
		n = mymin(pT2 - pT  +  1, cnt_tBuf);
		_tcsncpy(tBuf, pT, n);
		tBuf[n  -  1] = 0;
	}
	else {
		_tcsncpy(tBuf, pT, cnt_tBuf);
	}

	tTrim_open(tBuf);

	return;
}







//
#define		CONST_qmCmdLine_ca								_T(  "ca="  )
#define		CONST_qmCmdLine_tn								_T(  "tn="  )
#define		CONST_qmCmdLine_log								_T(  "log="  )
#define		CONST_qmCmdLine_sys								_T(  "sys="  )
//
#define		CONST_qmCmdLine_devPrefix						_T(  "devPre="  )
#define		CONST_qmCmdLine_dev								_T(  "dev="  )
//
#define		CONST_qmCmdLine_devName							_T(  "devName="  )
//
#define		CONST_qmCmdLine_who_showInfo					_T(  "who="  )
#define		CONST_qmCmdLine_caServ							_T(  "caServ="  )
#define		CONST_qmCmdLine_caPort							_T(  "caPort=")
#define		CONST_qmCmdLine_log								_T(  "log="  )
#define		CONST_qmCmdLine_devType							_T(  "devType="  )
//
#define		CONST_qmCmdLine_usr								_T(  "usr="  )
#define		CONST_qmCmdLine_pwd								_T(  "pwd="  )

//
#define		CONST_qmCmdLine_ip								_T(  "ip="  )


//
#define		CONST_caCmd_login_sendData						1		//  取得签名随机数
#define		CONST_caCmd_login_auth							2		//  用签名随机数实现认证，并取得用户信息
//
#define		CONST_caCmd_usrData								3		//  用户身份认证，取得用户信息
#define		CONST_caCmd_chkUsrKey							4		//  检查用户key是否存在


//
#define		CONST_caCmd_getRandom							7
#define		CONST_caCmd_getSxrz  							8


//
#define		CONST_sym_usr									"usr="
#define		CONST_sym_bExists_usrKey						"bExists_usrKey="


//
typedef  struct  __appParams_ca_t {

				 //
				 int				iCmd;
				 
				 //
				 int				tn;

				 //
				 bool				bSys;

				 //
				 TCHAR				devPrefix[128];
				 bool				bDev;
				 bool				bFullCmp;

				 //
				 TCHAR				who_showInfo[32];

				 //
				 char				caGwIp[15 + 1];
				 int				caGwPort;

				 //
				 TCHAR				logFile[256];

				 //
				 char				pwd[256];


}		 AppParams_ca;

//
int  parseCmdLine_ca(  TCHAR  *  pCmdLine, AppParams_ca* pParams);


//
typedef  struct  __appParams_ipcProc_t {

				 //
				 char  nvrIp[15  +  1];
				 //
				 TCHAR  nvrUsr[128];
				 char	nvrPwd[128];

				 //
				 int	tn;
				 int	log;
				 int	devType;


}		 AppParams_ipcProc;


//
int parseCmdLine_ipcProc(TCHAR* pCmdLine, AppParams_ipcProc* pParams);





//
#endif  //   }


