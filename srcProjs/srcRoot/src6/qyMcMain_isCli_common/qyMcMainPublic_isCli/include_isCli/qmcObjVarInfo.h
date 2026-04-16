
#ifndef  __qmcTalkerInfo_h__
#define  __qmcTalkerInfo_h__	//  {


//
#include	"qmcObjVarPublic.h"


//
#define		CONST_objVarDataType_null								0
#define		CONST_objVarDataType_dlgTalk							1
#define		CONST_objVarDataType_dlgDynBmps							2


//
#define		MACRO_objVarData_commonMems							unsigned  int				uiType;				


//
typedef  struct			{
						MACRO_objVarData_commonMems
}		 QMC_objVarData_common;


//
#include	"dlgtalkproc.h"


//
void  *  newQmcObjVarData(  unsigned  int  uiType  );
void  freeQmcObjVarData(  void  **  pp  );


//  2014/09/24
typedef  struct  __qmcObjVarInfo_t								{
				 BOOL											bUsed;

				 //
				 SYNC_mt_cnt									syncMtCnt;


				 struct											{
					 DWORD										dwTickCnt_start;
					 
					 //
					 BOOL										bInvalid;						//  要释放时，先设置此标志位。 2015/11/15

					 //
					 HWND										hWnd;
					 //
					 QY_MESSENGER_ID							idInfo;					
					 unsigned  int								uiTranNo_shadow;				//  用来标识辅助talker窗口,为0时为主窗口
					 
					 //
					 void								*		pData;

				 }												var;


}		 QMC_objVar_info;


//
QMC_objVar_info  *  getQmcObjVarInfoByIndex(  MC_VAR_common  *  pProcInfo,  int  index  );
//
int  getObjVarInfoIndexByWnd(  MC_VAR_common  *  pProcInfoParam,  HWND  hWnd  );






#endif  //  }



