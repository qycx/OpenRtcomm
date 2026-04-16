

#ifndef  __dec_d3d11_func_h__	
#define  __dec_d3d11_func_h__	//  {


//
//
//
//  2016/04/09
typedef  struct  __tmpDecTex_t						{

				 ID3D11Texture2D	*               m_pTex;

				 //
				 unsigned  int						tmp_sn;
				 //
				 BOOL								bExists_sn;

}		 TMP_dec_tex;


//
typedef  struct  __dec_d3d11_devVar_t	{
			
		 //
		 BOOL								bInited_sharedTexes;
		 //
		 SHARED_tex							sharedTexes[MAX_sharedTexes_dec];
		 //
		unsigned  char						ucMaxCnt_shared_pTexes;

		//
#define		MAX_tmpDecTexes					4	//  8	//  10
		//
		struct								{
			TMP_dec_tex						mems[MAX_tmpDecTexes];
			unsigned  char					ucMaxCnt_tmpDecTexes;
			//
			unsigned  int					uiCnt_filled;
		}									tmpDecTexes;
		
		//
		unsigned  int						tn_sharedTex;
		DWORD								dwProcessId;
		//
		 unsigned  int						uiSeqNo_newSharedTex1;
	
	 	 //
		 unsigned  int						uiSeqNo_lastCopied;

		 //			
		unsigned  int						uiLoopCtrls;;
		//
		 DWORD								dwLastTickCnt_renderFrame;	
		 //
		 unsigned  int						uiNewMax_intervalInMs_renderFrame;
		 DWORD								dwStartTickCnt_toGetNew;
		 //
		 unsigned  int						uiMax_intervalInMs_renderFrame;

}	 DEC_d3d11_devVar;


//
//
//#define		M_getTexName_dec(  dwProcessId,  tn_sharedTex,  real_index,  tName,  cnt  )		_sntprintf(  tName,  cnt,  _T(  "qmstd%d-%d-%d"  ),  dwProcessId,  tn_sharedTex,  real_index  );


//
extern  "C"  __declspec(  dllexport  )  void  *  DEC_d3d11_devVar_new(  );
extern  "C"  __declspec(  dllexport  )  void  DEC_d3d11_devVar_free(  void  **  ppDEC_d3d11_devVar  );

//
extern  "C"  __declspec(  dllexport  )  int  decDev_my_RenderFrame(	QDC_OBJ_INFO							*  pQdcObjInfo,
						     void									*  pDEC_d3d11_devVar,  				
							ID3D11Device							*  m_pD3D11Device,
							ID3D11DeviceContext						*  m_pD3D11Ctx,						   
							ID3D11VideoDevice						*  m_pDX11VideoDevice,						   
							ID3D11VideoContext						*  m_pVideoContext,
							ID3D11VideoProcessorEnumerator			*  m_VideoProcessorEnum,
							ID3D11VideoProcessor					*  m_pVideoProcessor,
							
							ID3D11Texture2D							*  pRTTexture2D,
							unsigned  short							   CropW,
							unsigned  short							   CropH,
							int										   m_nViews,
							//
							PKTS_sharedTexInfo_forYuvWriter			*  pPkts_sharedTexInfo,
							//
							BOOL										g_bShowDec_sharedTexStatus,
							unsigned  int								g_uiXql_player,
							//
							QIS_trace_common						*	pQtc
							);




#endif  //  }

