
#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<winsock2.h>
#include	<windows.h>
#include	<stddef.h>
#include	<assert.h>
#include	<tchar.h>
#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif

	#include	<mmreg.h>
	#include	<MSAcm.h>
#endif
#include	<Wincrypt.h>

#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qmOpenCommon.h"
#include	"qyMsgFunc.h"

#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyq2.h"				//  2009/05/13

#include	"qnmCommProc_mis.h"
#include	"qnmPcComm.h"
#include	"qnmAssetsCommProc.h"
#include	"qnmSpCommProc.h"
#include	"qwmNetworkStatusCommProc.h"
#include	"qyTCharCommProc.h"
#include	"qnmCustom.h"
#include	"qySyncCommProc.h"
#include	"qmCrypt.h"
#include	"qnmFwCommProc.h"
#include	"qyString.h"


//
 QY_DMITEM  CONST_channelTypeTable[]  =
{
	{		CONST_channelType_null,								(TCHAR*)_T(  ""  ),					},
	{		CONST_channelType_talking,							(TCHAR*)_T(  "Talk"  ),				},
	{		CONST_channelType_robot,							(TCHAR*)_T(  "Robot"  ),			},
	{		CONST_channelType_webSending,						(TCHAR*)_T(  "WebTalk"  ),			},
	{		CONST_channelType_media,							(TCHAR*)_T(  "Video"  ),			},
	{		CONST_channelType_realTimeMedia,					(TCHAR*)_T(  "Audio"  ),			},
	{		CONST_channelType_rtOp,								(TCHAR*)_T(  "Op"  ),			},
	{		-1,																				},
};


 /*
  QY_DMITEM  CONST_usRunningStatusTable[]  =
 {
	 {		CONST_usRunningStatus_null,							_T(  ""  ),			},
	 {		CONST_usRunningStatus_online,						_T(  "ÔÚÏß"  ),		},
	 {		CONST_usRunningStatus_offline,						_T(  "ÀëÏß"  ),		},
	 {		CONST_usRunningStatus_away,							_T(  "Àë¿ª"  ),		},
	 {		CONST_usRunningStatus_hide,							_T(  "ÒþÉí"  ),		},
	 {		CONST_usRunningStatus_neverLogon,					_T(  "Î´ÉÏÏß"  ),	},
	 {		-1,																		},
 };
 */

 QY_DMITEM  CONST_usRunningStatusTable_en[] =
 {
	 {		CONST_usRunningStatus_null,							(TCHAR*)_T(""),			},
	 {		CONST_usRunningStatus_online,						(TCHAR*)_T("online"),		},
	 {		CONST_usRunningStatus_offline,						(TCHAR*)_T("offline"),		},
	 {		CONST_usRunningStatus_away,							(TCHAR*)_T("away"),		},
	 {		CONST_usRunningStatus_hide,							(TCHAR*)_T("hide"),		},
	 {		CONST_usRunningStatus_neverLogon,					(TCHAR*)_T("neverLogon"),	},
	 {		-1,																		},
 };

 
 //
 #include<sstream>
#include <myTChar.h>

//
QY_MESSENGER_ID  *  idStr2Info(  char  *  idStr,  QY_MESSENGER_ID  *  pIdInfo  )
{
	 int	iErr	=	-1;

	 if  (  !idStr  ||  !pIdInfo  )  return  NULL;

	 try  {
	 
		 //
		 std::stringstream  conv;
		 conv << idStr;
		 conv >> pIdInfo->ui64Id;
	 }
	 catch  (  ...  )  {
			return  NULL;
	 }
	 //pIdInfo->ui64Id  =  (  unsigned  __int64  )atof(  idStr  );	//  2007/04/03, 这里暂时只取低位的数。
	 
	 
	 
	 return  pIdInfo;
}

 char  *  idInfo2Str(  QY_MESSENGER_ID  *  pIdInfo,  char  *  idStr,  unsigned  int  size  )
{
	 if  (    !pIdInfo  ||!idStr  ||  size  <=  CONST_qyMessengerIdStrLen  )  return  NULL;
	 //_snprintf(  idStr,  size,  "%018I64u",  pIdInfo->ui64Id  );
	 _snprintf(  idStr,  size,  "%020I64u",  pIdInfo->ui64Id  );
	 return  idStr;
}



 //
 int getSeg(char* pData, char* seg, int segSize)
 {
	 int  iErr = -1;
	 if (!pData)return  -1;
	 if (!seg)return -1;
	 if (!segSize) return -1;

	 for (; ; ) {
		 //
		 char* pStart = strchr(pData, '[');
		 if (!pStart)  break;
		 char* pEnd = strchr(pStart, ']');
		 if (!pEnd)break;

		 int len = pEnd - pStart;
		 if (segSize < len) break;

		 //
		 safeStrnCpy(pStart + 1, seg, len);

		 //
		 iErr = 0;
		 //
		 break;
	 }

	 return  iErr;
 }

 //
 __int64 geti64Val(char* str, char* tag)
 {
	 __int64  i64Val = 0;

	 if (!str) return -1;
	 if (!tag) return -1;


	 char* p0 = stristr(str, tag);
	 if (p0) {
		 char* p1 = p0 + strlen(tag);

		 QY_MESSENGER_ID  idInfo;
		 idStr2Info(p1, &idInfo);

		 i64Val = idInfo.ui64Id;
	 }

	 return  i64Val;
 }


 //
#if  0  //  old
 extern  "C"  int  iigetFieldData_long(QY_CFGITEM_ntoh_U * pItem, long* plVal)
 {
	 if (!pItem || !plVal)  return  -1;

	 unsigned  short	tmp_dataType;
	 memcpy(&tmp_dataType, &pItem->head.dataType, sizeof(tmp_dataType));

	 if (tmp_dataType != CONST_qyDataType_long)  return  -1;

	 //  *plVal  =  (  (  QY_CFGITEM_LONG  *  )pItem  )->ulVal;
	 memcpy(plVal, &((QY_CFGITEM_LONG*)pItem)->ulVal, sizeof(long));

	 return  0;
 }
#endif

 //
 extern  "C"  int  getFieldData_long(QY_CFGITEM_ntoh_U * pItem, long* plVal)
 {
	 if (!pItem || !plVal)  return  -1;

	 unsigned  short	tmp_dataType;
	 memcpy(&tmp_dataType, &pItem->head.dataType, sizeof(tmp_dataType));

	 //if (tmp_dataType != CONST_qyDataType_long)  return  -1;

	 switch (tmp_dataType) {
	 case  CONST_qyDataType_l32:

		 //  *plVal  =  (  (  QY_CFGITEM_LONG  *  )pItem  )->ulVal;
		 memcpy(plVal, &((QY_CFGITEM_LONG*)pItem)->ulVal, sizeof(long));
		 break;
	 case  CONST_qyDataType_short:
	 default: {
		 unsigned  short sVal = 0;
		 if (getFieldData_short(pItem, (short*) & sVal)) {
			 return  -1;
		 }
		 *plVal = sVal;
	 }
			break;

	 }

	 //
	 return  0;
 }

 //
#if  0  //  old
 extern  "C"  int  iigetFieldData_short(QY_CFGITEM_ntoh_U * pItem, short* psVal)
 {
	 if (!pItem || !psVal)  return  -1;

	 unsigned  short	tmp_dataType;
	 memcpy(&tmp_dataType, &pItem->head.dataType, sizeof(tmp_dataType));

	 if (tmp_dataType != CONST_qyDataType_short) {
		 return  -1;
	 }

	 //  *psVal  =  (  (  QY_CFGITEM_SHORT  *  )pItem  )->usVal;
	 memcpy(psVal, &((QY_CFGITEM_SHORT*)pItem)->usVal, sizeof(short));

	 return  0;

 }
#endif

 //
 extern  "C"  int  getFieldData_short(QY_CFGITEM_ntoh_U * pItem, short* psVal)
 {
	 if (!pItem || !psVal)  return  -1;

	 unsigned  short	tmp_dataType;
	 memcpy(&tmp_dataType, &pItem->head.dataType, sizeof(tmp_dataType));

	 //
#if  0
	 if (tmp_dataType != CONST_qyDataType_short) {
		 return  -1;
	 }
#endif 
	 //
	 switch (tmp_dataType) {
	 case  CONST_qyDataType_short:
		 //  *psVal  =  (  (  QY_CFGITEM_SHORT  *  )pItem  )->usVal;
		 memcpy(psVal, &((QY_CFGITEM_SHORT*)pItem)->usVal, sizeof(short));
		 break;
	 default: {
		 unsigned  char  ucVal;  ucVal = 0;
		 if (getFieldData_char(pItem, (char*)&ucVal)) {
			 return  -1;
		 }
		 //short  sVal = ucVal;
		 //memcpy(psVal, &sVal, sizeof(short));
		 *psVal = ucVal;
	 }
			break;
	 }
	 return  0;

 }




 //
 extern  "C"  int  getFieldData_char(QY_CFGITEM_ntoh_U * pItem, char* pcVal)
 {
	 if (!pItem || !pcVal)  return  -1;

	 unsigned  short	tmp_dataType;
	 memcpy(&tmp_dataType, &pItem->head.dataType, sizeof(tmp_dataType));
	 if (tmp_dataType != CONST_qyDataType_char)  return  -1;

	 *pcVal = ((QY_CFGITEM_CHAR*)pItem)->ucVal;

	 return  0;

 }




#if  0  //  old
 extern  "C"  int  iigetFieldData_l64(QY_CFGITEM_ntoh_U * pItem, __int64* pl64Val)
 {
	 if (!pItem || !pl64Val)  return  -1;

	 unsigned  short  tmp_dataType;
	 memcpy(&tmp_dataType, &pItem->head.dataType, sizeof(short));
	 if (tmp_dataType != CONST_qyDataType_l64)  return  -1;

	 //  *pl64Val  =  *(  __int64  *  )(  (  QY_CFGITEM_L64  *  )pItem  )->buf_l64Val;
	 memcpy(pl64Val, ((QY_CFGITEM_L64*)pItem)->buf_l64Val, sizeof(__int64));	//  2010/04/08


	 //
	 return  0;

 }
#endif 

 extern  "C"  int  getFieldData_l64(QY_CFGITEM_ntoh_U * pItem, __int64* pl64Val)
 {
	 if (!pItem || !pl64Val)  return  -1;

	 unsigned  short  tmp_dataType;
	 memcpy(&tmp_dataType, &pItem->head.dataType, sizeof(short));


	 //if (tmp_dataType != CONST_qyDataType_l64)  return  -1;
	 switch (tmp_dataType) {
	 case  CONST_qyDataType_l64:

		 //  *pl64Val  =  *(  __int64  *  )(  (  QY_CFGITEM_L64  *  )pItem  )->buf_l64Val;
		 memcpy(pl64Val, ((QY_CFGITEM_L64*)pItem)->buf_l64Val, sizeof(__int64));	//  2010/04/08
		 break;
	 case  CONST_qyDataType_l32:
	 default:
	 {
		 unsigned  long  lVal = 0;
		 if (getFieldData_long(pItem, (long*) & lVal)) {
			 return  -1;
		 }
		 *pl64Val = lVal;
	 }
	 break;

	 }

	 //
	 return  0;

 }
