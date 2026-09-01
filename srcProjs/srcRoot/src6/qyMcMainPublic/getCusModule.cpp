

#include	"stdafx.h"
#include	<tchar.h>
#include	"shlobj.h"
#ifndef  __WINCE__
		 #include	"myresource.h"
#endif
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyVDev.h"


//
 CUS_MODULE_U  *  getCusModule(  CUS_MODULES  *  pModules,  unsigned  int  uiModuleType,  unsigned  int  uiVDevId,  unsigned  int  uiDevType,  WCHAR  *  wDevIdStr  )
{
	int					index	=	0;
	//QY_MC			*	pQyMc	=	(  QY_MC  *  )pQyMcParam;
	CUS_MODULE_U	*	pModule	=	NULL;

	if  (  !pModules  )  return  NULL;

	//
	for  (  index  =  0;  index  <  pModules->usCnt;  index  ++  )  {
		 pModule  =  &pModules->mems[index];
		 //
		 if  (  pModule->common.uiType  !=  uiModuleType  )  continue;

		 //
		 if (!pModule->common.bLoaded) {
			 continue;
		 }


		 //
		 if  (  pModule->common.uiType  ==  CONST_moduleType_vDev  )  {			 
			 if  (  !pModule->vDev.ucbVDevInited  )  continue;
			 if  (  !pModule->vDev.ucbVDevStarted  )  continue;
			 //
			 QY_VDEV	*	pVDev;
			 if (  !(  pVDev  =  (  QY_VDEV  *  )pModule->vDev.pf_qyVDev_getPtrProperty(  0,  (  void  *  )CONST_qyPropertyId_vDev,  0  )  )  )  continue;
			 //
			 if  (  uiVDevId  &&  pVDev->uiVDevId  ==  uiVDevId  )  break;
			 if  (  pModule->vDev.pf_qyVDev_isSendable  &&  pModule->vDev.pf_qyVDev_isSendable(  0,  0,  wDevIdStr  )  )  break;
		 }
		 //
		 break;
	}

	if  (  index  ==  pModules->usCnt  )  return  NULL;

	return  pModule;
}



