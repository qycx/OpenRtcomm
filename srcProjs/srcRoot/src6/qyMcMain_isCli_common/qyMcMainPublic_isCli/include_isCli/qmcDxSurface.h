



#ifndef  __QMCDXSURFACE_H__
#define  __QMCDXSURFACE_H__		//  {

#if  0
typedef  struct							{
			#if  0						//  2010/04/01
				LPDIRECTDRAW4			lpDD4;        // DirectDraw object
				LPDIRECTDRAWSURFACE4    lpDDSPrimary; // DirectDraw primary
				LPDIRECTDRAWSURFACE4	lpDDSOffscreen; 
			#endif
				LPDIRECTDRAW			lpDD4;        // DirectDraw object
				LPDIRECTDRAWSURFACE	    lpDDSPrimary; // DirectDraw primary
				LPDIRECTDRAWSURFACE		lpDDSOffscreen; 

				LPDIRECTDRAWCLIPPER		lpDDClipper;

				int						iWidth;
				int						iHeight;

}										QY_dxSurface_mgr;

extern  QY_dxSurface_mgr	gDxSurfaceMgr;

#endif

#endif  //  }



