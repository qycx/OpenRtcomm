



#ifndef  __QMCSHAREIC_H__
#define  __QMCSHAREIC_H__	//  {

//#include	"amCapProc.h"


typedef  struct  __shareIc_t			{
			
				 BOOL							bInited;

				 //
				 bool							bQuit;			//  线程停止运行

				 //
				 bool							bRunning;		//  启动采集
				
				 //
				 TCHAR							displayName_aDev[128];
				 TCHAR							displayName_vDev[128];

				 //				 
				 BOOL							bAudio;
				 BOOL							bVideo;

				 //
				 HANDLE							hThread_cap;

				 //
				 SAMPLE_grabberCb_var			m_var;

				 //
				 int							index_sharedObj;

				 //
}		 SHARE_IC;


//
//
#define		CONST_cfgName_icCapTest				_T(  "icCapTest")
#define		CONST_cfgName_useWireless			_T(  "useWireless")
#define		CONST_cfgName_useShare			    _T(  "useShare")
#define		CONST_cfgName_useSelectVideo		_T(  "useSelectVideo")


//
#endif  //  }


