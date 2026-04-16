
#ifndef  __MODULE_QISCAMCAP_H__
#define  __MODULE_QISCAMCAP_H__		//  {


#include	"qisCamCapOpenCommon.h"


typedef  struct  __moduleCamCap_t				{							//  2010/07/26
				 MACRO_cusModuleCommon			

				 PF_setGuiOpen					pf_setGuiOpen;

				 //  2010/08/02
				 PF_doInitRecordSound			pf_doInitRecordSound;
				 PF_doExitRecordSound			pf_doExitRecordSound;

				 //
				 PF_initVideoCapDev				pf_initVideoCapDev;
				 PF_exitVideoCapDev				pf_exitVideoCapDev;

				 PF_bGetCapturePara				pf_bGetCapturePara;
								 
				 PF_startCapture				pf_startCapture;
				 PF_stopCapture					pf_stopCapture;
					 

}		 MODULE_camCap;



#endif  //  }


