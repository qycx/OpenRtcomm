

#ifndef  __remoteStorageCfg_h__
#define  __remoteStorageCfg_h__	//  {

#include	"comPortCfg.h"


typedef  struct  __remoteStorageCfg_t			{

				 QY_MESSENGER_ID								idInfos_allowed[MAX_idInfos_allowed];		//  5

}		 REMOTE_storage_cfg;



__declspec(  dllexport  )  int  getRemoteStorageCfg(  REMOTE_storage_cfg  *  pCfg  );



#endif  //  }

