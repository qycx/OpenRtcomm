

#ifndef  __QYMCMAINCUSMODULEMENU_H__
#define  __QYMCMAINCUSMODULEMENU_H__	//  {


//
#include	"qmCusModuleDefs.h"


//
typedef  int  (  *  PF_qyVDev_postStr2Dev  )(  char  *  idStr_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  LPCTSTR  str,  unsigned  int  uiDevType_to,  WCHAR  *  wDevIdStr_to,  WCHAR  *  wForwardPath,  HWND  hWnd_notify,  int  iUsrData  );
typedef  int  (  *  PF_qyVDev_postData2Dev  )(  char  *  idStr_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  void  *  pQyVDevData,  unsigned  int  uiDataLen,  unsigned  int  uiDevType_to,  WCHAR  *  wDevIdStr_to,  unsigned  int  uiDevIndex  );


#define		MACRO_cusModuleCommon				unsigned  int					uiType;								\
												TCHAR							name[32  +  1];						\
												BOOL							bLoaded;							\
												TCHAR							path[MAX_PATH  +  1];				\
												HMODULE							hModule;
//  2014/06/19
//  cusModule doesnt need be dynLoaded, it can also be loaded by being linked. 

typedef  struct  __cusModuleCommon_t			{
				 MACRO_cusModuleCommon
}		 CUS_MODULE_common;

typedef  struct  __cusModuleVDev_t				{
				 MACRO_cusModuleCommon			

				 PF_commonHandler				pf_qyVDev_getPtrProperty;
				 PF_commonHandler				pf_qyVDev_getInfo;
				 PF_commonHandler				pf_qyVDev_getCfg;
				 PF_commonHandler				pf_qyVDev_op;
				 PF_commonHandler				pf_qyVDev_chkBeforeInit;
				 PF_commonHandler				pf_qyVDev_init;
				 PF_commonHandler				pf_qyVDev_chkAfterInit;
				 PF_commonHandler				pf_qyVDev_start;
				 PF_commonHandler				pf_qyVDev_stop;
				 PF_commonHandler				pf_qyVDev_exit;
				 //
				 PF_bCommonHandler				pf_qyVDev_isSendable;
				 //
				 PF_qyVDev_postStr2Dev			pf_qyVDev_postStr2Dev;
				 PF_qyVDev_postData2Dev			pf_qyVDev_postData2Dev;
 
 
				 unsigned  char					ucbVDevInited;
				 unsigned  char					ucbVDevStarted;

				 unsigned  int					uiCmd;										//  
				 
}		 CUS_MODULE_vDev;





typedef  struct  __cusModuleCompress_t			{											//  2010/04/28
				 MACRO_cusModuleCommon			

				 QDC_MGR						mgr;

				 PF_qdcInit						pf_qdcInit;
				 PF_qdcExit						pf_qdcExit;

				 //
				 PF_qdcGetProp					pf_qdcGetProp;								//  2015/10/20
				 PF_qdcSetProp					pf_qdcSetProp;								//  2016/04/09

				 //
				 PF_qdcGetCompressAudioCfg		pf_qdcGetCompressAudioCfg;
				 PF_qdcGetCompressVideoCfg		pf_qdcGetCompressVideoCfg;

				 PF_qdcInitCompressAudio		pf_qdcInitCompressAudio;
				 PF_qdcExitCompressAudio		pf_qdcExitCompressAudio;
				 PF_qdcCompressAudio			pf_qdcCompressAudio;
				 PF_qdcCompressAudioRun			pf_qdcCompressAudioRun;						//  2016/12/05

				 //
				 PF_qdcInitDecompressAudio		pf_qdcInitDecompressAudio;
				 PF_qdcExitDecompressAudio		pf_qdcExitDecompressAudio;  
				 PF_qdcDecompressAudio			pf_qdcDecompressAudio;
				 PF_qdcDecompressAudioRun		pf_qdcDecompressAudioRun;					//  2016/12/05
				   
				 //
				 PF_qdcInitCompressVideo		pf_qdcInitCompressVideo;  
				 PF_qdcExitCompressVideo		pf_qdcExitCompressVideo;
				 PF_qdcCompressVideo			pf_qdcCompressVideo;
				 PF_qdcCompressVideoRun			pf_qdcCompressVideoRun;						//  2014/04/02
			   	
				 //  2014/03/30
				 PF_qdcGetSpsPps				pf_qdcGetSpsPps;

				 //
				 PF_qdcInitDecompressVideo		pf_qdcInitDecompressVideo;
				 PF_qdcExitDecompressVideo		pf_qdcExitDecompressVideo;
				 PF_qdcDecompressVideo			pf_qdcDecompressVideo;  

				 //  2011/12/10
				 PF_qdcDecompressVideoAndOutput	pf_qdcDecompressVideoAndOutput;

				 //  2014/03/28
				 PF_qdcDecompressVideoRun		pf_qdcDecompressVideoRun;

				 //
				 PF_qdcGetOutputByIndex			pf_qdcGetOutputByIndex;
				 PF_qdcClearOutputs				pf_qdcClearOutputs;
				 
				 //
				 unsigned  char					ucbInited;

}		 CUS_MODULE_compress;


//
typedef  union  __cusModuleU_t					{
				CUS_MODULE_common				common;
				CUS_MODULE_vDev					vDev;
				CUS_MODULE_compress				compress;
				struct							{
					MACRO_cusModuleCommon
					void					*	ps[50];
				}								maxMem;
}		 CUS_MODULE_U;

//
//  #define		CONST_maxCusModules				12					//  2012/09/15
//#define		CONST_maxCusModules				16					//  2014/07/19
#define		CONST_maxCusModules					25					//  2025/10/29

//
typedef  struct  __cusModules_t					{	

				 unsigned  short				usCnt;
				 CUS_MODULE_U					mems[CONST_maxCusModules];

				 //
				 //CUS_MODULE_U				*	pIpp;				//  2011/07/31
				 //
				 CUS_MODULE_U				*	pMediaSdk_dec;		//  2014/03/27
				 CUS_MODULE_U				*	pMediaSdk_enc;		//  2014/03/27
				 //CUS_MODULE_U				*	pMediaSdk_enc_conf;	//  2014/07/01
				 //
				 CUS_MODULE_U				*	pDec_vpl;			//  
				 CUS_MODULE_U				*	pEnc_vpl;			//  


				 //  
				 CUS_MODULE_U				*	pDec_nv;			//  2014/06/19
				 CUS_MODULE_U				*	pDecD3d_nv;			//  2014/06/19
				 CUS_MODULE_U				*	pEnc_nv;			//  2014/06/19
				 CUS_MODULE_U				*	pEncD3d_nv;			//  2014/06/19

				 
				 //
				 CUS_MODULE_U				*	pDec_amf;			//  2015/04/30
				 CUS_MODULE_U				*	pEnc_amf;			//  2015/04/30
				 

				 //
				 CUS_MODULE_U				*	pQdc_vorbis_dec;	//  2015/02/13
				 CUS_MODULE_U				*	pQdc_vorbis_enc;	//  2015/02/13
				 //  
				 CUS_MODULE_U				*	pDec_vp8;			//  2014/07/18
				 CUS_MODULE_U				*	pEnc_vp8;			//  2014/07/18
				 
				 //
				 CUS_MODULE_U				*	pFfmpeg;

				 CUS_MODULE_U               *   pAAC;

				 //
				 CUS_MODULE_U				*	pLyra;

				 //
}		 CUS_MODULES;




 //
 BOOL  bFindMenuItem(  HMENU  hMenu, LPCTSTR  MenuString,  int  *  pnPos  );

 int  cusModuleMenu(  void  *  pQyMc,  HMENU  hMenuFrm,  int  iResId_menu_modulesGuanLi  );

 int  loadCusModules(  void  *  pQyMc  );
 int  unloadCusModules(  void  *  pQyMc  );
 //
 //  int  initCusModules(  void  *  pQyMcParam  );
 int  initCusModules(  void  *  pQyMcParam );
 int  startCusModules(  void  *  pQyMcParam  );
 int  stopCusModules(  void  *  pQyMcParam  );

 //
 CUS_MODULE_U  *  getCusModule(  CUS_MODULES  *  pModules,  unsigned  int  uiModuleType,  unsigned  int  uiVDevId  =  0,  unsigned  int  uiDevType  =  0,  WCHAR  *  wDevIdStr  =  NULL  );

 //
 int  myVDev_postStr2Dev(  void  *  pQyMc,  char  *  idStr_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  LPCTSTR  str,  unsigned  int  uiDevType_to,  WCHAR  *  wDevIdStr_to,  WCHAR  *  wForwardPath,  HWND  hWnd_notify,  int  iUsrData  );
 int  myVDev_postData2Dev(  void  *  pQyMc,  unsigned  int  uiVDevId,  char  *  idStr_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  void  *  pQyVDevData,  unsigned  int  uiDataLen,  unsigned  int  uiDevType_to,  WCHAR  *  wDevIdStr_to,  unsigned  int  uiDevIndex  );

//
#if  0
BOOL  bSupported_mediaSdk_enc(  );
BOOL  bSupported_mediaSdk_dec(  );
#endif

//
#if  0
							case  CONST_moduleType_ipp:																			\
								pModule = (pCusModules)->pIpp;														\
								break;																						\

#endif 

//  2012/09/09
#define		M_getCompressModule(  pCusModules,  uiModuleType,  pModule  )  {													\
					switch  (  uiModuleType  )  {																				\
							case  CONST_moduleType_qdc_vorbis_dec:																\
								  pModule	=	(  pCusModules  )->pQdc_vorbis_dec;												\
								  break;																						\
							case  CONST_moduleType_qdc_vorbis_enc:																\
								  pModule	=	(  pCusModules  )->pQdc_vorbis_enc;												\
								  break;																						\
							case  CONST_moduleType_mediaSdk_dec:																\
								  pModule  =  (  pCusModules  )->pMediaSdk_dec;													\
								  break;																						\
							case  CONST_moduleType_mediaSdk_enc:																\
								  pModule  =  (  pCusModules  )->pMediaSdk_enc;													\
								  break;																						\
							case  CONST_moduleType_dec_vpl:																		\
								  pModule  =  (  pCusModules  )->pDec_vpl;														\
								  break;																						\
							case  CONST_moduleType_enc_vpl:																		\
								  pModule  =  (  pCusModules  )->pEnc_vpl;														\
								  break;																						\
							case  CONST_moduleType_dec_nv:																		\
								  pModule  =  (  pCusModules  )->pDec_nv;														\
								  break;																						\
							case  CONST_moduleType_decD3d_nv:																	\
								  pModule  =  (  pCusModules  )->pDecD3d_nv;													\
								  break;																						\
							case  CONST_moduleType_enc_nv:																		\
								  pModule  =  (  pCusModules  )->pEnc_nv;														\
								  break;																						\
							case  CONST_moduleType_encD3d_nv:																	\
								  pModule  =  (  pCusModules  )->pEncD3d_nv;													\
								  break;																						\
							case  CONST_moduleType_dec_amf:																		\
								  pModule  =  (  pCusModules  )->pDec_amf;														\
								  break;																						\
							case  CONST_moduleType_enc_amf:																		\
								  pModule  =  (  pCusModules  )->pEnc_amf;														\
								  break;																						\
							case  CONST_moduleType_enc_vp8:																		\
								  pModule  =  (  pCusModules  )->pEnc_vp8;														\
								  break;																						\
							case  CONST_moduleType_dec_vp8:																		\
								  pModule  =  (  pCusModules  )->pDec_vp8;														\
								  break;																						\
							case  CONST_moduleType_ffmpeg:																		\
								  pModule = ( pCusModules )->pFfmpeg;															\
								  break;																						\
							case  CONST_moduleType_lyra:																		\
								  pModule = ( pCusModules )->pLyra;																\
								  break;																						\
                            case  CONST_moduleType_aac:  																		\
								  pModule = ( pCusModules )->pAAC;			     												\
								  break;	                                                                                    \
							case  CONST_moduleType_compress:																	\
								  pModule	=	getCusModule(  (  pCusModules  ),  CONST_moduleType_compress  );				\
								  break;																						\
							default:																							\
									pModule  =  NULL;																			\
									break;																						\
					}																											\
			}



//
//  2015/10/20
int  getModuleTypeBySth_toEnc(  void  *  pProcInfo,  unsigned  char  ucCompressors    );

//
int  getVal_bSupported_pktResType_sharedTex(  void  *  pProcInfo,  unsigned  int  uiModuleType,  int  propId,  void  *  pParam_input,  BOOL  *  pbVal   );






#endif  //  }


