

#ifndef  __QYAVRECORD_H__
#define	 __QYAVRECORD_H__  //  {

/*
#include	<mmsystem.h>
#include	<dsound.h>
#include	<d3d9.h>
#include	<d3dx9.h>
//  #include	<dmoreg.h>
*/


//  #define		DINV		3
#define		DINV		2

#ifndef CAPTUREBLT
	#define CAPTUREBLT (DWORD)0x40000000 
#endif


#define		CONST_mutexName_syncAvRecord		_T(  "qmcSyncAvRecord"  )


class  CQyBoundWnd;

typedef  struct  __qyAvRecordMgr_t				{
	
				 BOOL							bInited;		 

				 struct							{
					 
					 HWND						hWndMgr;			//  捕获鼠标选区的窗口

					 HWND						hWndStarter;		//  发起操作的窗口

					 BOOL						bSaveToAviFile;		//  是否保存到Avi文件

					 unsigned  short			usCnt_avRecords;	//  一共有多少个。注意用mutex来同步
					 BOOL						bStop;				//  通知所有的avRecord停止

					 BOOL						bCapFullScreen;		//  是否捕获全屏
					 BOOL						bRemoteAssist;		//  是否远程协助
					 BOOL						bDirectX;			//  是否使用directX的抓屏方式
					 int						level1;				//  2012/10/29
					 int						iParam;				//  2009/09/13

					 BOOL						bCapturing;

					 int						maxxScreen;
					 int						maxyScreen;
					 
					 RECT						rcClip; 
					 RECT						old_rcClip;
					 RECT						rcUse; 

					 POINT						ptOrigin;

					 HBITMAP					savedBitmap;
					 
					 int						supportMouseDrag;

					 int						bits;				//  = 24; 
					 int						nColors;			//  = 24;

					 DWORD						compfccHandler;		//  = 0;

					 int						versionOp;

					 int						frames_per_second;	//  = 200;

					 int						flashingRect;		//  =1;
					 
					 int						captureTrans;		//  =1;

					 HCURSOR					hSavedCursor;

					 BOOL						bRecordCursor;			//  =1; 
					 int						selected_compressor;	// = -1;
					 int						compquality;			//	 = 7000;
					 int						keyFramesEvery;			// = 200;
					 //
					 //
					 //Ver 1.2
					 //Video Compress Parameters
                     LPVOID						pVideoCompressParams;	// = NULL; 
                     DWORD						CompressorStateIsFor;	// = 0;
					 DWORD						CompressorStateSize;	// = 0;
					 LPVOID						pParamsUse;				// = NULL; 

					 //
					 int						RecordingMode;			// = 0;
					 //Misc Vars
					 int						threadPriority;			// = THREAD_PRIORITY_NORMAL;

					 unsigned  char				ucbNotAutoResizeCapScreen;	//  自动校正到常用分辨率

				 }								m_var;

				 __qyAvRecordMgr_t(  )  {	
					 memset(  this,  0,  sizeof(  struct  __qyAvRecordMgr_t  )  );  
					 OutputDebugString(  _T(  "qyAvRecordMgr is inited.\n"  )  );
				 };

}		 QY_AV_recordMgr;

#ifdef  _D3D9_H_
		#define		P_IDirect3D9		IDirect3D9	*
		#define		P_IDirect3DDevice9	IDirect3DDevice9  *
		#define		P_IDirect3DSurface9	IDirect3DSurface9  *
#else
		#define		P_IDirect3D9		void  *
		#define		P_IDirect3DDevice9	void  *
		#define		P_IDirect3DSurface9	void  *
#endif


typedef  struct  __qyAvRecord_t					{

				 RECT							rcUse; 
				 HWND							hWnd_notifyEnd;			//  2009/04/23.  捕获线程停止时通知的窗口，实际是mainWnd

				 CQyBoundWnd				*	pFrame;					//  =  NULL;

				 DWORD							initialtime;			//	=  0;

				 int							nActualFrame;			//	=  0;
				 int							nCurrFrame;				//	=  0;
				 //
				 float							fActualRate;			//	=  0.0;
				 float							fTimeLength;			//	=  0.0;
				 float							fRate;					//	=  0.0;
				 int							alreadyMCIPause;		//	=  0;

				 COLORREF						borderColor;			//  

				 //
				 int							nBits;
				 //
				 BITMAPINFO						bmpInfo;
				 LPVOID							pBits;

				 BOOL							bUseDirectX;			//  2009/09/23
				 struct							{
					 P_IDirect3D9				g_pD3D;					//  IDirect3D9			*	g_pD3D;	
					 P_IDirect3DDevice9			g_pd3dDevice;			//  IDirect3DDevice9	*	g_pd3dDevice;
					 P_IDirect3DSurface9		g_pSurface;				//  IDirect3DSurface9	*	g_pSurface;

					 //  HBITMAP					hBackBitmap;

					 RECT						gCapturedRect;

				 }								directX;				//  在使用directX抓屏时的变量

}		 QY_AV_RECORD;


extern  QY_AV_recordMgr	gQyAvRecordMgr;


int  createMouseCaptureWnd(  HINSTANCE  g_hInst,  QY_AV_recordMgr  *  p  );
int  destroyMouseCaptureWnd(  QY_AV_recordMgr  *  p  );






#endif  //  }




