
#ifndef  __WgcCapObj_h__	
#define  __WgcCapObj_h__	//  {

//
#include	"avCapDevTmpl.h"
#include	"wgcCapturePublic.h"
#include	"qisPipe_open.h"
#include <wgcCapDev.h>


//  2026/09/15  看门狗参数
#define		WGC_watch_intervalMs			1000		//  巡检间隔
#define		WGC_waitStarted_timeoutMs		20000		//  启动后等进入取帧的最长时间
#define		WGC_dataStale_timeoutMs			30000		//  多久没有帧就判异常(见 wgcCapObj.cpp 里的 WGC_ucbChk_dataStale)
#define		WGC_restart_minIntervalMs		3000		//  两次重建的最小间隔
#define		WGC_restart_backoffMaxMs		30000		//  连续失败时的最大退避
#define		WGC_stopReading_timeoutMs		3000		//  等读回调退出的超时
#define		WGC_exitWaitThread_timeoutMs	20000		//  退出时等监控线程收尾的超时


//  wrapper
//
//  2026/09/15
//  WgcCapObj = 外壳 + 看门狗. 里面裹一只 WgcCapDev(真正干活的).
//  外壳负责: 建 / 放内层设备, 并盯住它 —— 内层拉起来的 anWgcTool.exe 掉了,
//  就整只重建内层, 让上层(doCmd_startShareWgcCapture / 压缩线程 / 会议成员)不用改.
//
class WgcCapObj : public AvCapDevTmpl {

public:

	//  启动参数(重建时要用)
	//
	void				*	param_p0{};
	BITMAPINFOHEADER		param_bih_suggested{};
	LONG_PTR				param_lInstanceData{};

	//
	struct {
		//
		int					index_sharedObj;
		int					index_capBmp;

		//
		BITMAPINFOHEADER	bih_dec;

		//  2026/09/15  被监控的内层设备 + 自愈状态
		//
		WgcCapDev		*	pCapDev;				//  内层设备
		int					w, h;					//  当前协商到的分辨率

		int					nRestart_ok;			//  重建成功次数
		int					nRestart_failed;		//  重建失败次数
		DWORD				dwLastTickCnt_restart;	//  上次重建时刻(限频用)
		int					iBackoffLevel;			//  连续失败退避档位
		bool				bRecovering;			//  正在重建(重入保护)
		bool				bWatching;				//  监控线程已启动

	}  m_var;
	



	//
	HANDLE	m_hThread_capDev{};

	//
	bool  m_bQuit{};


	//
public:
	WgcCapObj();
	virtual  ~WgcCapObj();

	//
	virtual  int  initDev(void* p0, BITMAPINFOHEADER* pBih_suggested1, LONG_PTR lInstanceData);

	//
	virtual  int  exitDev(void** ppShareMediaDeviceParam);

	virtual  BOOL  bGetCapturePara(CCtxQmc* pProcInfo, int  iIndex_capAudio, int  iIndex_capBmp, void* pShareMediaDevice, WAVEFORMATEX* pWf_org, QY_VIDEO_HEADER* pVh_org, SAMPLE_grabberCb_cache* pCache);

	virtual  int  runDev(void* pShareMediaDeviceParam);
	virtual  int  stopDev(void* pShareMediaDeviceParam);

	//
	int readShmPkt( VT_shm_content* pShmContent, int  index_toRead);

	//  2026/09/15  内层 WgcCapDev 的建立 / 释放 / 自愈
	int   startCapDev();
	int   stopCapDev();
	int   restartCapDev(LPCTSTR hint);
	bool  isCapDevOk();

	//
	int   getRestartCnt_ok()      { return  m_var.nRestart_ok;     }
	int   getRestartCnt_failed()  { return  m_var.nRestart_failed; }


};



#endif  //  }
