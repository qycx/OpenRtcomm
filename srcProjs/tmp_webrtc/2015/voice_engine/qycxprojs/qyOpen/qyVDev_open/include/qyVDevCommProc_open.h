

#ifndef  __QYVDEVCOMMPROCOPEN_H__
#define  __QYVDEVCOMMPROCOPEN_H__	//  {


//
//  对象类型
//

#define		CONST_objType_phone						502												//  电话（手机）.在qnmCommProc_open.h文件里
#define		CONST_objType_dev						503												//  一般外设.在qnmCommProc_open.h文件里

//
//  自定义的类型，应在[CONST_objType_custom_base, CONST_objType_custom_max]之间
//
#define		CONST_objType_custom_base				32000											//  在qnmCommProc_open.h文件里
#define		CONST_objType_newDev					(  CONST_objType_custom_base  +  1  )			//  新设备,在qnmCommProc_open.h文件里

#define		CONST_objType_custom_max				(  40000  -  1  )								//  


//
//
#define		isObjTypeCustom(  objType  )			(  (  objType  )  >=  CONST_objType_custom_base  &&  (  objType  )  <=  CONST_objType_custom_max  )		//  



#define		CONST_str_im							_T(  "im"  )
#define		CONST_str_phone							_T(  "phone"  )												//  电话（手机）.在qnmCommProc_open.h文件里
#define		CONST_str_dev							_T(  "dev"  )												//  一般外设.在qnmCommProc_open.h文件里



//  数据类型
#define		CONST_imCommType_custom_base			32000


#define		CONST_imCommType_custom_max				(  40000  -  1  )

//
//
#define		isImCommTypeCustom(  imCommType  )		(  (  imCommType  )  >=  CONST_imCommType_custom_base  &&  (  imCommType  )  <=  CONST_imCommType_custom_max  )		//  


#define		MACRO_qyVDev_common									unsigned  int  uiType;  unsigned  char  ucbResp;  unsigned  int  uiVDevId;


//  2008/01/25, vDev的通用请求
typedef  struct  __qyVDevData_t									{
				 MACRO_qyVDev_common
				 unsigned  short								usDataLen;
				 char											data[8192];
}		 QY_VDEV_DATA;



typedef  struct  __qvdSmReq_t									{
				  WCHAR											sm[512];
				  char											phoneNo[64];				  
				  HWND											hWnd_notify;
				  int											iUsrData;
}		  QVD_SM_REQ;


typedef  struct  __qvdSmResp_t									{
				 int											iUsrData;
				 int											iErr;
}		 QVD_SM_RESP;



#endif




