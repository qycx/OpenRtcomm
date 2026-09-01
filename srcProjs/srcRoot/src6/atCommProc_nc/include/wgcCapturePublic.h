
#ifndef  __wgcCapturePublic_h__
#define  __wgcCapturePublic_h__		//  {

//
class  CCtxQmcTmpl;

//
class WgcCapture
{
public:
	//
	struct {
		//
		CCtxQmcTmpl		*	pProcInfoTmpl;

		//
		bool				bQuit;
		//
		int					w, h;
		//
		bool				bGot_wh;

		//
		bool				bInited;
		bool				bRunning;

		//
		bool				bDbg;
		//
		bool				bDbg_traceRt_wgc;


	}						m_var;
	//
	HANDLE					hThread_cap;

	//
	WgcCapture() {
		//
		memset(&m_var, 0, sizeof(m_var));
		//
		hThread_cap = mynull;

		//
		if (1) {
			//m_var.bDbg = true;
		}

	}
	~WgcCapture() {
		return;
	}

};

//
class  CCtxQmc;


//
__declspec(dllexport)  int  wgc_initDev(WgcCapture* pWgc);

__declspec(dllexport)  int  wgc_exitDev(WgcCapture* pWgc);

__declspec(dllexport)  BOOL  wgc_bGetCapturePara(WgcCapture* pWgc, WAVEFORMATEX* pWf_org, QY_VIDEO_HEADER* pVh_org);

__declspec(dllexport)  int  wgc_runDev(WgcCapture* pWgc);

__declspec(dllexport)  int  wgc_stopDev(WgcCapture* pWgc);




#ifdef  __DEBUG__
__declspec(dllexport) int test_wgc();
#endif 




#endif  //  }


