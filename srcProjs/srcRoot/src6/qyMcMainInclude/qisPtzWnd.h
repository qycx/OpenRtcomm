
#ifndef  __qisPtzWnd_h__
#define  __qisPtzWnd_h__	//  {

//
#include	"comPortCfg.h"


//
//  2015/09/20
typedef  struct												{
			
				COM_PORT_cfg								cfg;
				
}		 PTZ_mem_var;


//
typedef  struct  __qis_ptz_wnd_t							{

				 PTZ_mem_var								m_var;
					 
				 //  true.
				 unsigned  char								ucbNeedRestart;
				 //
				 HWND										hWnd_localPtzControl;										//  2012/08/01

}		 QIS_ptz_wnd;





#endif  //  }


