

#ifndef  __QYVDEV_H__
#define  __QYVDEV_H__	//  {

//
#ifndef  CONST_qyPropertyId_null
		 #define		CONST_qyPropertyId_null								0		//  2008/01/01
		 //
		 #define		CONST_qyPropertyId_vDev								1000	//  2008/01/01
		 #define		CONST_qyPropertyId_bPhoneMsgrListAccepted			1001	//  2008/02/05
		 #define		CONST_qyPropertyId_ucbOnlyNetSm						1002	//  2008/02/10  
		 #define		CONST_qyPropertyId_baud								1003	//  2008/11/22	
		 //
#endif

#define		DEFAULT_vDevId_base												128		//  uiVDevId为0是为qyMc准备的。所以，不能为0，设一个基数

typedef struct  __qyVDev_t						{
	             unsigned  int					uiType;
				 //
				 unsigned  int					uiVDevId;							//  虚拟设备的ID。由qyMc来分配。有唯一性。
				 //
				 HMODULE						hModule;
				 QY_GUI_OPEN_vDev			*	pGuiOpen;
				 //  
				 HWND							hWnd_test;
				 BOOL							bDebug;								//  
				 //
				 BOOL							bInited;
}		QY_VDEV;






 //  common interfaces
 //
 //  qyVDev_getPtrProperty(  0,  CONST_qyPropertyId_vDev,  0  ) is the first call, to fill hModule.
 //
  extern  "C"  __declspec( dllexport )  int  qyVDev_getPtrProperty(  void  *  p0,  void  *  propertyIdParam,  void  *  p2  );
  extern  "C"  __declspec( dllexport )  int  qyVDev_getInfo(  void  *  p0,  void  *  p1,  void  *  p2  );
  extern  "C"  __declspec( dllexport )  int  qyVDev_getCfg(  void  *  p0,  void  *  p1,  void  *  p2  );
  extern  "C"  __declspec( dllexport )  int  qyVDev_op(  void  *  p0,  void  *  p1,  void  *  p2  );
  extern  "C"  __declspec( dllexport )  int  qyVDev_chkBeforeInit(  void  *  p0,  void  *  p1,  void  *  p2  );
  extern  "C"  __declspec( dllexport )  int  qyVDev_init(  void  *  p0,  void  *  p1,  void  *  p2  );
  extern  "C"  __declspec( dllexport )  int  qyVDev_chkAfterInit(  void  *  p0,  void  *  p1,  void  *  p2  );
  extern  "C"  __declspec( dllexport )  int  qyVDev_start(  void  *  p0,  void  *  p1,  void  *  p2  );
  extern  "C"  __declspec( dllexport )  int  qyVDev_stop(  void  *  p0,  void  *  p1,  void  *  p2  );
  extern  "C"  __declspec( dllexport )  int  qyVDev_exit(  void  *  p0,  void  *  p1,  void  *  p2  );
  //
  extern  "C"  __declspec( dllexport )  BOOL  qyVDev_isSendable(  void  *  p0,  void  *  uiObjTypeParam,  void  *  wDevIdStrParam  );
  //
  extern  "C"  __declspec( dllexport )  int  qyVDev_postStr2Dev(  char  *  idStr_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  LPCTSTR  str,  unsigned  int  uiDevType_to,  WCHAR  *  wDevIdStr_to,  WCHAR  *  wForwardPath,  HWND  hWnd_notify,  int  iUsrData  );
  extern  "C"  __declspec( dllexport )  int  qyVDev_postData2Dev(  char  *  idStr_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  void  *  pQyVDevData,  unsigned  int  uiDataLen,  unsigned  int  uiDevType_to,  WCHAR  *  wDevIdStr_to,  unsigned  int  uiDevIndex  );

 
 ////



#endif  //  }


