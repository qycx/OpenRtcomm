
#ifndef  __d2dProcPublic_h__
#define  __d2dProcPublic_h__	//  {

//
//
typedef  struct  __dmdr_help_t							{
				 void  *								pD2D_mgr_deviceResources;				
}		 D2D_mgr_deviceResources_help;



//
int  initD2dMgr(  void  **  ppD2D_mgr  );
int  exitD2dMgr(  void  **  ppD2D_mgr  );

//
//
int  myCreateDeviceResources(  ID3D11Device  *  m_pDevice,  UINT  w,  UINT  h,  void  *  pD2D_mgr,  D2D_mgr_deviceResources_help  *  pDmdrh,  QIS_trace_common  *  pQtc  );
void myDiscardDeviceResources(  D2D_mgr_deviceResources_help  *  pDmdrh  );





//
int  init_d2d_txt_font(  void  *  pD2D_mgr,  D2D_mgr_deviceResources_help  *  pDmdrh,  SUBTITLE_cfgEx  *  pMemCfg,  void  **  ppD2D_txt_font  );
int  exit_d2d_txt_font(  void  **  ppD2D_txt_font  );



#endif  //  }


