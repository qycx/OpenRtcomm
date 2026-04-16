

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
#include "../atInclude/ancCorePublic.h"
#include	"ancCommProc.h"


  //  2014/09/23
 BOOL  bSupported_sendVhDec(  )
{
#ifdef  __DEBUG__
#if  0
		traceLog(  _T(  "Note: no VhDec"  )  );
		return  FALSE;
#else
	static bool  bWarned  =  FALSE;
	if  (  !bWarned  )  {
		bWarned  =  TRUE;
		traceLog(  (TCHAR*)_T(  "Note: VhDec should not be sent"  )  );
	}
#endif

#endif

		return  TRUE;
}

 


 //  对orgData是WCHAR的情况，orgDataSize表示WCHAR的count
 //  对这个流要求用CONST_qnmCfgId_null结尾
 //  *pptr指向下一个空间，而不是输出串
 //  *pSize为剩余的字节数，不是一共得到了多少
 int  data2Stream(  int  iDataType,  unsigned  short  usCfgId,  void  *  orgData,  unsigned  int  orgDataSize,  char  **  pptr_usable,  unsigned  int  *  pSize_usable  )
{
	 //
	 if (M_isCommVer1) {

		 //
		 int  tmpiRet;
		 tmpiRet = atData2Stream(iDataType, usCfgId, orgData, orgDataSize, pptr_usable, pSize_usable);

		 return  tmpiRet;
	 }

	 //
	 int					iErr			=	-1;
	 QY_CFGITEM_STR			itemStr;
	 QY_CFGITEM_LONG		itemLong;
	 QY_CFGITEM_CHAR		itemChar;
	 QY_CFGITEM_SHORT		itemShort;
	 QY_CFGITEM_L64			itemL64;
	 QY_CFGITEM			*	pItem			=	NULL;
	 unsigned  int			len;
	 unsigned  int			size			=	0;
	 char				*	ptr				=	NULL;
	 CQyMalloc				mallocObj;

	 if  (  !pptr_usable  ||  !*pptr_usable  ||  !pSize_usable  )  return  -1;
	 if  (  !orgData  )  {
		 switch  (  iDataType  )  {
			     case  CONST_qyDataType_long:
				 case  CONST_qyDataType_char:
				 case  CONST_qyDataType_short:
					   break;
				 default:
					     return  -1;	//  非数值的值为地址，不能为空
		 }
	 }
	 if  (  iDataType  ==  CONST_qyDataType_l64  )  {
		 if  (  orgDataSize  &&  orgDataSize  <  sizeof(  __int64  )  )  {		//  传入0也算了，早期代码都用0。2007/12/11
			 traceLogA(  (char*)"data2Stream: l64需要传入数据地址，故建议输入数据长度应>=sizeof(  __int64  )"  );  
		 }
	 }

	 ptr  =  *pptr_usable;
	 size  =  *pSize_usable;

	 switch  (  iDataType  )  {
			 case  CONST_qyDataType_long:
				   itemLong.cfgId  =  usCfgId;
				   itemLong.dataType  =  iDataType;
				   itemLong.ulVal  =  (  unsigned  long  )orgData;
				   pItem  =  (  QY_CFGITEM  *  )&itemLong;
				   break;
			 case  CONST_qyDataType_char:
				   itemChar.cfgId  =  usCfgId;
				   itemChar.dataType  =  iDataType;
				   itemChar.ucVal  =  (  unsigned  char  )orgData;
				   pItem  =  (  QY_CFGITEM  *  )&itemChar;
				   break;
			 case  CONST_qyDataType_short:
				   itemShort.cfgId  =  usCfgId;
				   itemShort.dataType  =  iDataType;
				   itemShort.usVal  =  (  unsigned  short  )orgData;
				   pItem  =  (  QY_CFGITEM  *  )&itemShort;				   
				   break;
			 case  CONST_qyDataType_data:  {
				   QY_CFGITEM_DATA	*	pItemData		=	NULL;
				   int					tmpSize			=	offsetof(  QY_CFGITEM_DATA,  buf  )  +  orgDataSize;	//  sizeof(  QY_CFGITEM_DATA  )	//  2010/09/10
				   //
				   if  (  !(  pItemData  =  (  QY_CFGITEM_DATA  *  )mallocObj.mallocf(  tmpSize  )  )  )  {
					   traceLogA(  (char*)"data2Stream. malloc from QY_CFGITEM_DATA failed."  );  goto  errLabel;
				   }
				   //
				   pItemData->cfgId  =  usCfgId;
				   pItemData->dataType  =  iDataType;
				   if  (  orgDataSize  >  sizeof(  pItemData->buf  )  )  {
					   traceLogA(  (char*)"data2Stream: dataType_data: too big dataSize"  );  goto  errLabel;
				   }
				   pItemData->len  =  orgDataSize;
				   if  (  pItemData->len  !=  orgDataSize  )  {		//  2008/04/01, 
					   //
					   traceLogA(  (char*)"data2Stream: dataType_data error, buf truncated. data can't more than short"  );  
					   //
					   goto  errLabel;
				   }
				   memcpy(  pItemData->buf,  orgData,  pItemData->len  );
				   pItem  =  (  QY_CFGITEM  *  )pItemData;				
					}
				   break;
			 case  CONST_qyDataType_lData:  {
				   QY_CFGITEM_LDATA	*	pItemLData		=	NULL;
				   int					tmpSize			=	offsetof(  QY_CFGITEM_LDATA,  buf  )  +  orgDataSize;	//  sizeof(  QY_CFGITEM_LDATA  )	//  2010/09/10
				   //
				   if  (  !(  pItemLData  =  (  QY_CFGITEM_LDATA  *  )mallocObj.mallocf(  tmpSize  )  )  )  {
					   traceLogA(  (char*)"data2Stream. malloc from QY_CFGITEM_LDATA failed."  );  goto  errLabel;
				   }
				   //
				   pItemLData->cfgId  =  usCfgId;
				   pItemLData->dataType  =  iDataType;
				   if  (  orgDataSize  >  sizeof(  pItemLData->buf  )  )  {
					   traceLogA(  (char*)"data2Stream: dataType_lData: too big dataSize"  );  goto  errLabel;
				   }
				   pItemLData->ulLen  =  orgDataSize;
				   memcpy(  pItemLData->buf,  orgData,  pItemLData->ulLen  );
				   pItem  =  (  QY_CFGITEM  *  )pItemLData;				
				   }
				   break;
			 case  CONST_qyDataType_l64:
				   itemL64.cfgId  =  usCfgId;
				   itemL64.dataType  =  iDataType;
				   memcpy(  itemL64.buf_l64Val,  orgData,  sizeof(  __int64  )  );
				   pItem  =  (  QY_CFGITEM  *  )&itemL64;
				   break;
			 case  CONST_qyDataType_str:  
			 case  CONST_qyDataType_utf8Str:  {
				   //
				   itemStr.cfgId  =  usCfgId;
				   itemStr.dataType  =  iDataType;
				   itemStr.len  =  min(  sizeof(  itemStr.str  ),  orgDataSize  );
				   memcpy(  itemStr.str,  orgData,  itemStr.len  );
				   pItem  =  (  QY_CFGITEM  *  )&itemStr;
					}
				   break;
			 case  CONST_qyDataType_wStr:  {
				   WCHAR  *  wStr  =  (  WCHAR  *  )orgData;
				   wStr[orgDataSize]  =  0;
				   //
				   if  (  orgDataSize  <  1024  )  {
					   itemStr.cfgId  =  usCfgId;
					   if  (  !myWChar2Utf8(  wStr,  itemStr.str,  sizeof(  itemStr.str  )  )  )  goto  errLabel;
					   itemStr.dataType  =  CONST_qyDataType_utf8Str;
					   itemStr.len  =  strlen(  itemStr.str  );
					   pItem  =  (  QY_CFGITEM  *  )&itemStr;
					   }
				   else  {  //2010/12/05
		   				 QY_CFGITEM_DATA	*	pItemData		=	NULL;
						 int					tmpBufSize		=	(  orgDataSize  +  1  )  *  sizeof(  WCHAR  );
						 int					tmpSize			=	offsetof(  QY_CFGITEM_DATA,  buf  )  +  tmpBufSize;
						 //
						 if  (  tmpBufSize  >  sizeof(  pItemData->buf  )  )  {
							 traceLogA(  (char*)"data2Stream: dataType_wStr: too big dataSize"  );  
							 goto  errLabel;				   
						 }
						 //
						 if  (  !(  pItemData  =  (  QY_CFGITEM_DATA  *  )mallocObj.mallocf(  tmpSize  )  )  )  {
							 traceLogA(  (char*)"data2Stream. malloc from QY_CFGITEM_DATA failed."  );  
							 goto  errLabel;				   
						 }
						 //
						 pItemData->cfgId  =  usCfgId;
						 if  (  !myWChar2Utf8(  wStr,  pItemData->buf,  tmpBufSize  )  )  goto  errLabel;
						 pItemData->dataType  =  CONST_qyDataType_utf8Str;
						 pItemData->len  =  strlen(  pItemData->buf  );
						 pItem  =  (  QY_CFGITEM  *  )pItemData;									     
				   }
					}
				   break;
			 default:
					goto  errLabel;
					
	 }


	 if  (  !pItem  )  goto  errLabel;
	 len  =  qyhtonCfgItem(  pItem  );
	 if  (  len  <=  0  ||  size  <  len  )  {
		 traceLogA(  (char*)"getStream_wStr  error."  );  goto  errLabel;
	 }

	 memcpy(  ptr,  (  char  *  )pItem,  len  );  ptr  +=  len;  size  -=  len;

	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *pptr_usable  =  ptr;
		 *pSize_usable  =  size;
	 }
	 return  iErr;
}





//
 int  stream2Data(  char  **  pCfgsBuf_usable,  unsigned  int  *  pSize_usable,  PF_handler_stream2Data  pf_filter,  PF_handler_stream2Data  pf,  void  *  p0,  void  *  p1  )
{
	 //
	 if (M_isCommVer1) {
		 int  tmpiRet = -1;

		 tmpiRet = atStream2Data(pCfgsBuf_usable, pSize_usable, pf_filter, pf, p0, p1);
		 return  tmpiRet;
	 }

	 //
	int						iErr			=	-1;
	unsigned  int			len;
	char				*	ptr				=	0;
	QY_CFGITEM_ntoh_U		item_ntoh_U;
	QY_CFGITEM_ntoh_U	*	pItem			=	NULL;
	//  QY_CFGITEM_WSTR			itemWStr;
	CQyString				wStr;
	//
	CTX_stream2Data			ctx;
	memset(  &ctx,  0,  sizeof(  ctx  )  );
	//
	int						nStarts			=	0;
	//unsigned  int			uiStreamIds[5]	=	{	0,	};
	int						tmpiRet;
	char		*			cfgsBuf			=	NULL;
	unsigned  int			size			=	0;
	unsigned  short			tmp_cfgId;			//  2010/04/08
	unsigned  short			tmp_dataType;		//  2010/04/08

	if  (  !pCfgsBuf_usable  ||  !pSize_usable  )  return  -1;

	cfgsBuf  =  *pCfgsBuf_usable;
	size  =  *pSize_usable;
	//
	if  (  !cfgsBuf  ||  !size  ||  !pf_filter  ||  !pf  )  return  -1;

	len  =  0;
	ptr  =  cfgsBuf;
	for  (  ;  size;  )  {
#if  0
		 pItem  =  (  QY_CFGITEM  *  )ptr;
		 len  =  qyntohCfgItem(  pItem  );		//  这里要注意：这里qyntohCfgItem(  )返回的是转换前的字节流长度。和qyhtonCfgItem(  )返回的不同
#endif
		 len			=  qyntohCfgItem(  ptr,  &item_ntoh_U  );		//  这里要注意：这里qyntohCfgItem(  )返回的是转换前的字节流长度。和qyhtonCfgItem(  )返回的不同
		 pItem			=	&item_ntoh_U;

		 if  (  len  <=  0  ||  len  >  size  )  goto  errLabel;

		 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );			//  2010/04/08
		 memcpy(  &tmp_dataType,  &pItem->head.dataType,  sizeof(  short  )  );		//  2010/04/08
	 
		 ptr  +=  len;  size  -=  len;		 

		 if  (  !nStarts  )  {
			 if  (  tmp_cfgId  !=  CONST_qnmCfgId_start  )  goto  errLabel;
			 if  (  tmp_dataType  !=  CONST_qyDataType_long  )  goto  errLabel;
		 }

		 if  (  tmp_cfgId  ==  CONST_qnmCfgId_start  )  {

			 nStarts  ++  ;
			 if  (  nStarts  >  mycountof(  ctx.uiStreamIds  )  )  goto  errLabel;

			 //  uiStreamId  =  (  (  QY_CFGITEM_LONG  *  )pItem  )->ulVal;
			 memcpy(  &ctx.uiStreamIds[nStarts  -  1],  &(  (  QY_CFGITEM_LONG  *  )pItem  )->ulVal,  sizeof(  ctx.uiStreamIds[0]  )  );
			 //
			 ctx.index_streamId  =  nStarts  -  1;
			 if  (  (  tmpiRet  =  pf(  &ctx,  p0,  p1,  ctx.uiStreamIds[nStarts  -  1],  pItem  )  )  )  {		//  这里有利于处理结构起始时初始化，2007/08/01
				 iErr  =  tmpiRet;  goto  errLabel;
			 }
			 continue;
		 }
	
		 if  (  tmp_cfgId  ==  CONST_qnmCfgId_null  )  {
			 //
			 ctx.index_streamId  =  nStarts  -  1;
			 if  (  (  tmpiRet  =  pf(  &ctx,  p0,  p1,  ctx.uiStreamIds[nStarts  -  1],  pItem  )  )  )  {		//  这里有利于处理结构结束时做结尾工作，2007/08/01
				 iErr  =  tmpiRet;  goto  errLabel;
			 }
			 nStarts  --  ;
			 if  (  !nStarts  )  break;
			 continue;
		 }
			 
		 if  (  tmp_dataType  ==  CONST_qyDataType_utf8Str  )  {

//  #define		CONST_bufSize_utf8Str		4096
#define		CONST_bufSize_utf8Str		32  *  1024		//  2010/12/05

			 CQyMalloc				mallocObj_buf;
			 int					bufSize		=  CONST_bufSize_utf8Str;
			 char				*	pBuf		=	NULL;

			 if  (  pItem->data.len  +  1  >  CONST_bufSize_utf8Str  )  {
				 traceLog(  (TCHAR*)_T(  "stream2Data: utf8 too long string"  )  );
				 goto  errLabel;
			 }
			 bufSize  =  pItem->data.len  +  1;
			 pBuf  =  mallocObj_buf.mallocf(  bufSize  );
			 if  (  !pBuf  )  goto  errLabel;

			 //
#if  0
			 QY_CFGITEM_STR  *  pItemStr  =  (  QY_CFGITEM_STR  *  )pItem;
			 unsigned  short  tmp_len;
			 memcpy(  &tmp_len,  &pItemStr->len,  sizeof(  short  )  );

			 itemWStr.cfgId  =  tmp_cfgId;
			 safeStrnCpy(  pItemStr->str,  pBuf,  min(  tmp_len  +  1,  bufSize  )  );
			 if  (  !myUtf82WChar(  pBuf,  itemWStr.wStr,  mycountof(  itemWStr.wStr  )  )  )  goto  errLabel;
			 itemWStr.len  =  min(  wcslen(  itemWStr.wStr  ),  mycountof(  itemWStr.wStr  )  -  1  );
			 itemWStr.dataType  =  CONST_qyDataType_wStr;
			 pItem  =  (  QY_CFGITEM  *  )&itemWStr;
#endif
			 safeStrnCpy(  pItem->data.p,  pBuf,  min(  pItem->data.len  +  1,  bufSize  )  );
			 wStr  =  CQyString(  pBuf  );
			 pItem->wStr.dataType  =  CONST_qyDataType_wStr;
			 pItem->wStr.len  =  wStr.GetLength(  );
			 pItem->wStr.pWStr  =  (  WCHAR  *  )wStr.GetBuffer(  0  );
		 }
		 ctx.index_streamId  =  nStarts  -  1;
		 if  (  (  tmpiRet  =  pf_filter(  &ctx,  p0,  p1,  ctx.uiStreamIds[nStarts  -  1],  pItem  )  )  )  {		//  2008/12/03, 主要是对pItem里的数据进行过滤。不是对结果的
			 iErr  =  tmpiRet;  goto  errLabel;
		 }
		 ctx.index_streamId  =  nStarts  -  1;
		 if  (  (  tmpiRet  =  pf(  &ctx,  p0,  p1,  ctx.uiStreamIds[nStarts  -  1],  pItem  )  )  )  {
			 iErr  =  tmpiRet;  goto  errLabel;
		 }
	}
	
	 iErr  =  0;
errLabel:

	 if  (  !iErr  )  {
		 *pCfgsBuf_usable  =  ptr;
		 *pSize_usable  =  size;
	 }

	 return  iErr;
}










 //
#if  0
 extern  "C"  int  getFieldData_data(  QY_CFGITEM  *  pItem,  char  *  val,  unsigned  int  *  pSize  )
{
	 if  (  !pSize  )  return  -1;
	 if  (  pItem->dataType  !=  CONST_qyDataType_data  )  return  -1;

	 QY_CFGITEM_DATA *	pItemData	=	(  QY_CFGITEM_DATA  *  )pItem;
	 
	 if  (  pItemData->len  >  *pSize  )  return  -1;			//  2008/03/23

	 memcpy(  val,  pItemData->buf,  pItemData->len  );
	 *pSize  =  pItemData->len;

	 return  0;
}
#else
 extern  "C"  int  getFieldData_data(  QY_CFGITEM_ntoh_U  *  pItem,  char  *  val,  unsigned  int  *  pSize  )
{
	 if  (  !pSize  )  return  -1;

	 unsigned  short  tmp_dataType;
	 memcpy(  &tmp_dataType,  &pItem->head.dataType,  sizeof(  short  )  );
	 if  (  tmp_dataType  !=  CONST_qyDataType_data  )  return  -1;

	 //  QY_CFGITEM_DATA *	pItemData	=	(  QY_CFGITEM_DATA  *  )pItem;

	 unsigned  short  tmp_len;
	 memcpy(  &tmp_len,  &pItem->data.len,  sizeof(  short  )  );
	 if  (  tmp_len  >  *pSize  )  return  -1;			//  2008/03/23

	 memcpy(  val,  pItem->data.p,  tmp_len  );
	 //	*pSize  =  pItemData->len;
	 *pSize  =  tmp_len;

	 return  0;
}
#endif

#if  0
 extern  "C"  int  getFieldData_lData(  QY_CFGITEM  *  pItem,  char  *  val,  unsigned  int  *  pSize  )
{
	 if  (  !pSize  )  return  -1;
	 if  (  pItem->dataType  !=  CONST_qyDataType_lData  )  return  -1;

	 QY_CFGITEM_LDATA *	pItemData	=	(  QY_CFGITEM_LDATA  *  )pItem;
	 
	 if  (  pItemData->ulLen  >  *pSize  )  return  -1;			//  2008/03/23

	 memcpy(  val,  pItemData->buf,  pItemData->ulLen  );
	 *pSize  =  pItemData->ulLen;

	 return  0;
}
#else
 extern  "C"  int  getFieldData_lData(  QY_CFGITEM_ntoh_U  *  pItem,  char  *  val,  unsigned  int  *  pSize  )
{
	 if  (  !pSize  )  return  -1;

	 unsigned  short  tmp_dataType;
	 memcpy(  &tmp_dataType,  &pItem->head.dataType,  sizeof(  short  )  );
	 if  (  tmp_dataType  !=  CONST_qyDataType_lData  )  return  -1;

	 //  QY_CFGITEM_LDATA *	pItemData	=	(  QY_CFGITEM_LDATA  *  )pItem;
	 
	 unsigned  long  tmp_ulLen;
	 memcpy(  &tmp_ulLen,  &pItem->lData.ulLen,  sizeof(  long  )  );	 
	 if  (  tmp_ulLen  >  *pSize  )  return  -1;			//  2008/03/23

	 memcpy(  val,  pItem->lData.p,  tmp_ulLen  );
	 *pSize  =  tmp_ulLen;

	 return  0;
}
#endif  

#if  0
 extern  "C"  int  getFieldData_str(  QY_CFGITEM  *  pItem,  char  *  val,  unsigned  int  size  )
{
	 if  (  pItem->dataType  !=  CONST_qyDataType_str  )  return  -1;
	 QY_CFGITEM_STR	*	pItemStr	=	(  QY_CFGITEM_STR  *  )pItem;
	 
	 safeStrnCpy(  pItemStr->str,  val,  min(  (  unsigned  int  )(  pItemStr->len  +  1  ),  size  )  );

	 return  0;
}
#else 
 extern  "C"  int  getFieldData_str(  QY_CFGITEM_ntoh_U  *  pItem,  char  *  val,  unsigned  int  size  )
{
	 unsigned short  tmp_dataType;
	 memcpy(  &tmp_dataType,  &pItem->head.dataType,  sizeof(  short  )  );
	 if  (  tmp_dataType  !=  CONST_qyDataType_str  )  return  -1;

	 //  QY_CFGITEM_STR	*	pItemStr	=	(  QY_CFGITEM_STR  *  )pItem;

	 unsigned short  tmp_len;
	 memcpy(  &tmp_len,  &pItem->data.len,  sizeof(  short  )  );
	 safeStrnCpy(  pItem->data.p,  val,  min(  (  unsigned  int  )(  tmp_len  +  1  ),  size  )  );

	 return  0;
}
#endif

#if  0
 extern  "C"  int  getFieldData_wStr(  QY_CFGITEM  *  pItem,  WCHAR  *  val,  unsigned  int  size  )
{
	 if  (  pItem->dataType  !=  CONST_qyDataType_wStr  )  return  -1;
	 QY_CFGITEM_WSTR  *  pItemWStr  =  (  QY_CFGITEM_WSTR  *  )pItem;
	 
	 safeWcsnCpy(  pItemWStr->wStr,  val,  min(  (  unsigned  int  )(  pItemWStr->len  +  1  ),  size  )  );
	 return  0;
}
#else
 extern  "C"  int  getFieldData_wStr(  QY_CFGITEM_ntoh_U  *  pItem,  WCHAR  *  val,  unsigned  int  size  )
{
	 unsigned  short  tmp_dataType;
	 memcpy(  &tmp_dataType,  &pItem->head.dataType,  sizeof(  short  )  );
	 if  (  tmp_dataType  !=  CONST_qyDataType_wStr  )  return  -1;

	 //  QY_CFGITEM_WSTR  *  pItemWStr  =  (  QY_CFGITEM_WSTR  *  )pItem;
	 
	 unsigned  short  tmp_len;
	 memcpy(  &tmp_len,  &pItem->wStr.len,  sizeof(  short  )  );
	 safeWcsnCpy(  pItem->wStr.pWStr,  val,  min(  (  unsigned  int  )(  tmp_len  +  1  ),  size  )  );
	 return  0;
}
#endif


 /////////////

 

 
 //  网络上的idInfo不能是0的。但是，在手机外设发短信到本机上时，可能用的是0。然后用uiObjType来识别。
 BOOL  bMessengerIdValid(  QY_MESSENGER_ID  *  pIdInfo  )
{
	//  if  (  pIdInfo  &&  pIdInfo->ui64Id  &&  pIdInfo->ui64Id  !=  CONST_invalidMessengerId  )  return  TRUE;
	if  (  pIdInfo  &&  pIdInfo->ui64Id  !=  CONST_invalidMessengerId  )  return  TRUE;
	return  FALSE;
}

 BOOL  bMessengerIdStrValid(  char  *  idStr  )
{
	 if  (  !idStr  ||  strlen(  idStr  )  !=  CONST_qyMessengerIdStrLen  )  return  FALSE;
	 for  (  int  i  =  0;  i  <  CONST_qyMessengerIdStrLen;  i  ++  )  {
		  if  (  !isdigit(  idStr[i]  )  )  return  FALSE;
	 }
	 return  TRUE;
}


 ////
 BOOL  bMessengerGuest(  unsigned  int  uiObjType  )
{
	switch  (  uiObjType  )  {
		    case  CONST_objType_webGuest:
			case  CONST_objType_phoneGuest:
			case  CONST_objType_newDevGuest:
				  return  TRUE;
			default:
					break;
	}
	return  FALSE;
}


 ///////////


 /////////////////////
//
//  2008/12/03, 为通信加一个过滤规则。

#define		CONST_filterChars	"'"

 int  filterStream_is(  CTX_stream2Data  * pCtx,  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	int							iErr		=	-1;
	//  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	unsigned  short				tmp_len;

	unsigned  short	tmp_dataType;
	memcpy(  &tmp_dataType,  &pItem->head.dataType,  sizeof(  tmp_dataType  )  );
	
	switch  (  tmp_dataType  )  {
			case  CONST_qyDataType_str:
			case  CONST_qyDataType_utf8Str:
				  memcpy(  &tmp_len,  &(  (  QY_CFGITEM_STR  *  )pItem  )->len,  sizeof(  tmp_len  )  );
				  fwFilterBuf(  (char*)CONST_filterChars,  pItem->data.p,  tmp_len  );
				  break;
			case  CONST_qyDataType_wStr:
				  switch  (  uiStreamId  )  {
						  case  CONST_imCommType_htmlContent:	
							    switch  (  pItem->head.cfgId  )  {
										case  CONST_qnmCfgId_hint:
											  iErr  =  0;  goto  errLabel;
											  break;
										default:
												break;
								}
							    break;
						  default:
								 break;
				  }
				  memcpy(  &tmp_len,  &(  (  QY_CFGITEM_WSTR  *  )pItem  )->len,  sizeof(  tmp_len  )  );
				  fwFilterTBuf(  (TCHAR*)_T(  CONST_filterChars  ),  pItem->wStr.pWStr,  tmp_len  );
				  break;
			default:
					break;
	}

	iErr  =  0;
errLabel:
	return  iErr;
}

/////////////////////////

  

 int  commAuthInfo2Stream_mis(  QY_COMM_AUTHINFO_MIS  *  pAuthInfo,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pAuthInfo  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_auth,  0,  &ptr,  &len  )  )  goto  errLabel;
	 if  (  pAuthInfo->ver[0]  &&  data2Stream(  CONST_qyDataType_str,  CONST_qnmCfgId_clientVer,  pAuthInfo->ver,  strlen(  pAuthInfo->ver  ),  &ptr,  &len  )  )  goto  errLabel;
	 if  (  pAuthInfo->usAuthCmd  &&  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_authCmd,  (  void  *  )pAuthInfo->usAuthCmd,  0,  &ptr,  &len  )  )  goto  errLabel;
#if  0
	 if  (  pAuthInfo->uiObjType  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiObjType,  (  void  *  )pAuthInfo->uiObjType,  0,  &ptr,  &len  )  )  goto  errLabel;
#endif
	 if  (  pAuthInfo->iAppType  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_iAppType,  (  void  *  )pAuthInfo->iAppType,  0,  &ptr,  &len  )  )  goto  errLabel;		//  2011/03/27
	 if  (  pAuthInfo->iCustemId  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_iCustemId,  (  void  *  )pAuthInfo->iCustemId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 if  (  pAuthInfo->uiChannelType  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiChannelType,  (  void  *  )pAuthInfo->uiChannelType,  0,  &ptr,  &len  )  )  goto  errLabel;	//  2007/07/08

	 //
	 if  (  pAuthInfo->usLangId  &&  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_langId,  (  void  *  )pAuthInfo->usLangId,  0,  &ptr,  &len  )  )  goto  errLabel;	//  2007/07/08
	 if  (  pAuthInfo->uiDevType  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiDevType_from,  (  void  *  )pAuthInfo->uiDevType,  0,  &ptr,  &len  )  )  goto  errLabel;	//  2007/07/08

	 //
	 if  (  pAuthInfo->usAuthType  &&  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usAuthType,  (  void  *  )pAuthInfo->usAuthType,  0,  &ptr,  &len  )  )  goto  errLabel;	//  2011/03/22

	 //
	 for  (  i  =  0;  i  <  mycountof(  pAuthInfo->macsInfo.macs  );  i  ++  )  {
		  if  (  bMacValid(  (  char  *  )pAuthInfo->macsInfo.macs[i]  )  &&  data2Stream(  CONST_qyDataType_str,  CONST_qnmCfgId_mac,  pAuthInfo->macsInfo.macs[i],  sizeof(  pAuthInfo->macsInfo.macs[i]  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  bIpValid(  pAuthInfo->ip  )  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_ulIp,  (  void  *  )inet_addr(  pAuthInfo->ip  ),  0,  &ptr,  &len  )  )  goto  errLabel;
	 if  (  pAuthInfo->pcName[0]  &&  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_pcName,  pAuthInfo->pcName,  wcslen(  pAuthInfo->pcName  ),  &ptr,  &len  )  )  goto  errLabel;
	 if  (  pAuthInfo->domainName[0]  &&  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_domainName,  pAuthInfo->domainName,  wcslen(  pAuthInfo->domainName  ),  &ptr,  &len  )  )  goto  errLabel;
	 if  (  pAuthInfo->osUsrName[0]  &&  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_osUsrName,  pAuthInfo->osUsrName,  wcslen(  pAuthInfo->osUsrName  ),  &ptr,  &len  )  )  goto  errLabel;
	 
#if  0
	 //  2011/08/15
	 if  (  pAuthInfo->usAppAvLevel  &&  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usAppAvLevel,  (  void  *  )pAuthInfo->usAppAvLevel,  0,  &ptr,  &len  )  )  goto  errLabel;
#endif

	 //
	 if  (  pAuthInfo->messengerName[0]  &&  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_messengerName,  pAuthInfo->messengerName,  wcslen(  pAuthInfo->messengerName  ),  &ptr,  &len  )  )  goto  errLabel;
	 if  (  pAuthInfo->messengerPasswd[0]  &&  data2Stream(  CONST_qyDataType_str,  CONST_qnmCfgId_messengerPasswd,  pAuthInfo->messengerPasswd,  strlen(  pAuthInfo->messengerPasswd  ),  &ptr,  &len  )  )  goto  errLabel;

	 //
	 if  (  pAuthInfo->ca_sendDataLen && data2Stream(CONST_qyDataType_data, CONST_qnmCfgId_ca_sendData, pAuthInfo->ca_sendData, pAuthInfo->ca_sendDataLen, &ptr, &len))  goto  errLabel;
	 //
	 if (pAuthInfo->ca_usrName[0] && data2Stream(CONST_qyDataType_wStr, CONST_qnmCfgId_ca_usrName, pAuthInfo->ca_usrName, wcslen(pAuthInfo->ca_usrName), &ptr, &len))  goto  errLabel;
	 if (pAuthInfo->ca_tmp_passwd[0]) {
		 if (data2Stream(CONST_qyDataType_str, CONST_qnmCfgId_ca_tmp_passwd, pAuthInfo->ca_tmp_passwd, strlen(pAuthInfo->ca_tmp_passwd), &ptr, &len))  goto  errLabel;
	 }
																		  
	 //
	 if  (  pAuthInfo->wRndName_serv[0]  &&  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_wRndName_serv,  (  void  *  )pAuthInfo->wRndName_serv,  wcslen(  pAuthInfo->wRndName_serv  ),  &ptr,  &len  )  )  goto  errLabel;  //  2007/11/22
	 if  (  pAuthInfo->uiRnd_cli  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiRnd_cli,  (  void  *  )pAuthInfo->uiRnd_cli,  0,  &ptr,  &len  )  )  goto  errLabel;  //  2007/11/22
	 //  if  (  pAuthInfo->uiWebSessId  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiWebSessId,  (  void  *  )pAuthInfo->uiWebSessId,  0,  &ptr,  &len  )  )  goto  errLabel;  //  2007/11/22
	 if  (  pAuthInfo->uiLogonId  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiLogonId,  (  void  *  )pAuthInfo->uiLogonId,  0,  &ptr,  &len  )  )  goto  errLabel;  //  2007/11/22

	 
	 //  2008/06/10
	 if  (  pAuthInfo->uiBlobLen_sessionKey  )  {
		 if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_sessionKeyBlob,  pAuthInfo->sessionKeyBlob,  pAuthInfo->uiBlobLen_sessionKey,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  pAuthInfo->usSessionEncType  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usSessionEncType,  (  void  *  )pAuthInfo->usSessionEncType,  0,  &ptr,  &len  )  )  goto  errLabel;	//  2011/03/22
	 }
	 if  (  pAuthInfo->usLen_sessionIv  )  {
		 if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_sessionIv,  pAuthInfo->sessionIv,  pAuthInfo->usLen_sessionIv,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2CommAuthInfo_mis(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 QY_COMM_AUTHINFO_MIS  *	pAuthInfo	=	(  QY_COMM_AUTHINFO_MIS  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 long						lVal;
	 short  sVal  =  0;

	 //
	 if  (  uiStreamId  !=  CONST_imCommType_auth  )  goto  errLabel;

	 //
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:	//  2007/12/11
				   break;
			 case  CONST_qnmCfgId_null:		//  2007/12/11
				   break;
			 case  CONST_qnmCfgId_clientVer:
				   getFieldData_str(  pItem,  pAuthInfo->ver,  mycountof(  pAuthInfo->ver  )  );
				   break;
			 case  CONST_qnmCfgId_authCmd:
				   if  (  getFieldData_short(  pItem,  &sVal  )  )  goto  errLabel;
				   pAuthInfo->usAuthCmd  =  (  unsigned  short  )sVal;
				   break;
#if  0
			 case  CONST_qnmCfgId_uiObjType:
				   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
				   pAuthInfo->uiObjType  =  lVal;
				   break;
#endif
			 case  CONST_qnmCfgId_iAppType:							//  2011/03/27
				   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
				   pAuthInfo->iAppType  =  lVal;
				   break;
			 case  CONST_qnmCfgId_iCustemId:
				   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
				   pAuthInfo->iCustemId  =  lVal;
				   break;
			 case  CONST_qnmCfgId_uiChannelType:	//  2007/07/08
				   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
				   pAuthInfo->uiChannelType  =  lVal;
				   break;
			 case  CONST_qnmCfgId_langId:
				   unsigned  short  tmp_dataType;
				   memcpy(  &tmp_dataType,  &pItem->head.dataType,  sizeof(  short  )  );
				   if  (  tmp_dataType  ==  CONST_qyDataType_long  )  {
					   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
					   pAuthInfo->usLangId  =  (  unsigned  short  )lVal;				 
					   }
				   else  if  (  tmp_dataType  ==  CONST_qyDataType_short  )  {			//  2007/12/07, 允许usLangId以long或者short的形式发送.
					         if  (  getFieldData_short(  pItem,  (  short  *  )&pAuthInfo->usLangId  )  )  goto  errLabel;
							 }
				   else  {
					     //
					     //traceLogA(  (char*)"CONST_qnmCfgId_usLangId的传输类型不对。"  );  
						 //
						 goto  errLabel;					
				   }
				   break;
			 case  CONST_qnmCfgId_uiDevType_from:
  				   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
				   pAuthInfo->uiDevType  =  lVal;				 
				   break;
			 case  CONST_qnmCfgId_usAuthType:			//  2011/03/22
				   short  sVal;
				   if  (  getFieldData_short(  pItem,  &sVal  )  )  goto  errLabel;
				   pAuthInfo->usAuthType  =  sVal;
				   break;
			 case  CONST_qnmCfgId_mac:
				   if  (  pAuthInfo->macsInfo.nMacs  >=  mycountof(  pAuthInfo->macsInfo.macs  )  )  {
					   traceLogA(  (char*)"too many macs"  );  goto  errLabel;
				   }				   
				   getFieldData_str(  pItem,  (  char  *  )pAuthInfo->macsInfo.macs[pAuthInfo->macsInfo.nMacs],  sizeof(  pAuthInfo->macsInfo.macs[pAuthInfo->macsInfo.nMacs]  )  );
				   pAuthInfo->macsInfo.nMacs  ++  ;
				   break;
			 case  CONST_qnmCfgId_ulIp:  
				   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
				   ulIp2Str(  lVal,  pAuthInfo->ip,  mycountof(  pAuthInfo->ip  )  );				   
				   break;
			 case  CONST_qnmCfgId_pcName:
				   getFieldData_wStr(  pItem,  pAuthInfo->pcName,  mycountof(  pAuthInfo->pcName  )  );
				   break;
			 case  CONST_qnmCfgId_domainName:
				   getFieldData_wStr(  pItem,  pAuthInfo->domainName,  mycountof(  pAuthInfo->domainName  )  );
				   break;
			 case  CONST_qnmCfgId_osUsrName:
				   getFieldData_wStr(  pItem,  pAuthInfo->osUsrName,  mycountof(  pAuthInfo->osUsrName  )  );
				   break;
#if  0
			 case  CONST_qnmCfgId_usAppAvLevel:		//  2011/08/15
				   getFieldData_short(  pItem,  (  short  *  )&pAuthInfo->usAppAvLevel  );
				   break;
#endif
			 case  CONST_qnmCfgId_messengerName:
				   getFieldData_wStr(  pItem,  pAuthInfo->messengerName,  mycountof(  pAuthInfo->messengerName  )  );
				   break;
			 case  CONST_qnmCfgId_messengerPasswd:	//  2010/01/02
				   getFieldData_str(  pItem,  pAuthInfo->messengerPasswd,  mycountof(  pAuthInfo->messengerPasswd  )  );
				   break;

				   //
			 case  CONST_qnmCfgId_ca_sendData:
				   pAuthInfo->ca_sendDataLen = mycountof(pAuthInfo->ca_sendData);
				   if (getFieldData_data(pItem, pAuthInfo->ca_sendData, &pAuthInfo->ca_sendDataLen))  goto  errLabel;
				   break;
				   //
			 case  CONST_qnmCfgId_ca_usrName:
				   getFieldData_wStr(pItem, pAuthInfo->ca_usrName, mycountof(pAuthInfo->ca_usrName));
				   break;
			 case  CONST_qnmCfgId_ca_tmp_passwd:
				   getFieldData_str(pItem, pAuthInfo->ca_tmp_passwd, mycountof(pAuthInfo->ca_tmp_passwd));
				   break;
				   //
			 case  CONST_qnmCfgId_wRndName_serv:
				   getFieldData_wStr(  pItem,  pAuthInfo->wRndName_serv,  mycountof(  pAuthInfo->wRndName_serv  )  );
				   break;
			 case  CONST_qnmCfgId_uiRnd_cli:	//  2007/11/22
				   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
				   pAuthInfo->uiRnd_cli  =  lVal;
				   break;
			 case  CONST_qnmCfgId_uiLogonId:	//  2007/11/22
				   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
				   pAuthInfo->uiLogonId  =  lVal;
				   break;
			 case  CONST_qnmCfgId_sessionKeyBlob:
				   pAuthInfo->uiBlobLen_sessionKey  =  mycountof(  pAuthInfo->sessionKeyBlob  );
				   if  (  getFieldData_data(  pItem,  pAuthInfo->sessionKeyBlob,  &pAuthInfo->uiBlobLen_sessionKey  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usSessionEncType:
				   if  (  getFieldData_short(  pItem,  &sVal  )  )  goto  errLabel;
				   pAuthInfo->usSessionEncType=sVal;
				   break;
			 case  CONST_qnmCfgId_sessionIv:
				   unsigned  int  len;
				   len  =  mycountof(  pAuthInfo->sessionIv  );
				   if  (  getFieldData_data(  pItem,  pAuthInfo->sessionIv,  &len  )  )  goto  errLabel;
				   pAuthInfo->usLen_sessionIv  =  len;
				   break;
			 default:
				    traceLogA(  (char*)"tmpHandler_stream2CommAuthInfo_mis: 未处理的cfgId %d",  pItem->head.cfgId  );
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}


//
 int  authResp2Stream_mis(  unsigned  int  uiStreamId,  AUTH_RESP_MIS  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 //  serverHello
	 if  (  pReq->uiCommEncCtxType  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiCommEncCtxType,  (  void  *  )pReq->uiCommEncCtxType,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->uiBlobLen_publicKey  )  {
		 if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_publicKeyBlob,  pReq->publicKeyBlob,  pReq->uiBlobLen_publicKey,  &ptr,  &len  )  )  goto  errLabel;  
	 }

	 //  
	 if  (  pReq->idInfo.ui64Id  )  {						   
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  &pReq->idInfo.ui64Id,  sizeof(  pReq->idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  pReq->uiLogonId  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiLogonId,  (  void  *  )pReq->uiLogonId,  0,  &ptr,  &len  )  )  goto  errLabel;  
	 }
	 if  (  pReq->wRndName_serv[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_wRndName_serv,  pReq->wRndName_serv,  wcslen(  pReq->wRndName_serv  ),  &ptr,  &len  )  )  goto  errLabel;  
	 }

	 //  2009/10/11
	 if  (  pReq->ucbDaemonDemo  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbDaemonDemo,  (  void  *  )pReq->ucbDaemonDemo,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //  2009/11/05
	 if  (  pReq->usMaxVideoConferenceMems  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMaxVideoConferenceMems,  (  void  *  )pReq->usMaxVideoConferenceMems,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->ucDays_left  )  {	//  2010/03/22
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucDays_left,  (  void  *  )pReq->ucDays_left,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //  2011/10/22
	 //if  (  pReq->usAppAvLevel_daemon  &&  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usAppAvLevel,  (  void  *  )pReq->usAppAvLevel_daemon,  0,  &ptr,  &len  )  )  goto  errLabel;

	 //  2017/06/21
	 if  (  pReq->usSubSystemId_daemon  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_subSystemId,  (  void  *  )pReq->usSubSystemId_daemon,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //  2011/04/07
	 if  (  pReq->talkerDesc[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_talkerDesc,  pReq->talkerDesc,  lstrlen(  pReq->talkerDesc  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 
	 //  2016/08/10
	 if  (  pReq->clientWelcomeMsg[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_clientWelcomeMsg,  pReq->clientWelcomeMsg,  lstrlen(  pReq->clientWelcomeMsg  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  pReq->wBuf_hint[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_hint,  pReq->wBuf_hint,  lstrlen(  pReq->wBuf_hint  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  pReq->ca_usrName[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_ca_usrName,  pReq->ca_usrName,  lstrlen(  pReq->ca_usrName  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->ca_tmp_passwd[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_str,  CONST_qnmCfgId_ca_tmp_passwd,   pReq->ca_tmp_passwd,  strlen(  pReq->ca_tmp_passwd  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if (pReq->caGwCfg[0]) {
		 if (data2Stream(CONST_qyDataType_str, CONST_qnmCfgId_caGwCfg, pReq->caGwCfg, strlen(pReq->caGwCfg), &ptr, &len))  goto  errLabel;
	 }

	 //
	 if (pReq->caRandom[0]) {
		 if (data2Stream(CONST_qyDataType_str, CONST_qnmCfgId_ca_random, pReq->caRandom, strlen(pReq->caRandom), &ptr, &len))  goto  errLabel;
	 }

	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 //
 int  tmpHandler_stream2AuthResp_mis(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0
	 AUTH_RESP_MIS			*	pAuthResp	=	(  AUTH_RESP_MIS  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;

	 if  (  uiStreamId  !=  CONST_imCommType_authResp  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
	 switch  (  tmp_cfgId  )  {
		     case  CONST_qnmCfgId_uiCommEncCtxType:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pAuthResp->uiCommEncCtxType  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_publicKeyBlob:
				   pAuthResp->uiBlobLen_publicKey  =  sizeof(  pAuthResp->publicKeyBlob  );
				   if  (  getFieldData_data(  pItem,  pAuthResp->publicKeyBlob,  &pAuthResp->uiBlobLen_publicKey  )  )  goto  errLabel;
				   break;
				   //
			 case  CONST_qnmCfgId_messengerId:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pAuthResp->idInfo.ui64Id  )  )  {
					   goto  errLabel;
				   }
				   break;
			 case  CONST_qnmCfgId_uiLogonId:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pAuthResp->uiLogonId  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_wRndName_serv:
				   if  (  getFieldData_wStr(  pItem,  pAuthResp->wRndName_serv,  mycountof(  pAuthResp->wRndName_serv  )  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_ucbDaemonDemo:	//  2009/10/11
				   if  (  getFieldData_char(  pItem,  (  char  *  )&pAuthResp->ucbDaemonDemo  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usMaxVideoConferenceMems:	//  2009/11/05
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pAuthResp->usMaxVideoConferenceMems  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_ucDays_left:				//  2010/03/22
				   if  (  getFieldData_char(  pItem,  (  char  *  )&pAuthResp->ucDays_left  )  )  goto  errLabel;
				   break;
				   //
#if  0
			 case  CONST_qnmCfgId_usAppAvLevel:		//  2011/10/22
				   getFieldData_short(  pItem,  (  short  *  )&pAuthResp->usAppAvLevel_daemon  );
				   break;
#endif
				   //
			 case  CONST_qnmCfgId_subSystemId:
				   getFieldData_short(  pItem,  (  short  *  )&pAuthResp->usSubSystemId_daemon  );
				   break;
				   //
			 case  CONST_qnmCfgId_talkerDesc:
				   if  (  getFieldData_wStr(  pItem,  pAuthResp->talkerDesc,  mycountof(  pAuthResp->talkerDesc  )  )  )  goto  errLabel;
				   break;
				   //
			 case  CONST_qnmCfgId_clientWelcomeMsg:  //  2016/08/10
				   if  (  getFieldData_wStr(  pItem,  pAuthResp->clientWelcomeMsg,  mycountof(  pAuthResp->clientWelcomeMsg  )  )  )  goto  errLabel;
				   break;
				   //
			 case  CONST_qnmCfgId_hint:
				   getFieldData_wStr(  pItem,  pAuthResp->wBuf_hint,  mycountof(  pAuthResp->wBuf_hint  )  );
				   break;
				   //
			 case  CONST_qnmCfgId_ca_usrName:
				   getFieldData_wStr(  pItem,  pAuthResp->ca_usrName,  mycountof(  pAuthResp->ca_usrName  )  );
				   break;
			 case  CONST_qnmCfgId_ca_tmp_passwd:
				   if  ( getFieldData_str(pItem,  pAuthResp->ca_tmp_passwd,  mycountof(  pAuthResp->ca_tmp_passwd  )  )  )  goto  errLabel;
				   break;
				   //
			 case  CONST_qnmCfgId_caGwCfg:
				 if (getFieldData_str(pItem, pAuthResp->caGwCfg, mycountof(pAuthResp->caGwCfg)))  goto  errLabel;
				   break;
				   //
			 case  CONST_qnmCfgId_ca_random:  
				   getFieldData_str(pItem, pAuthResp->caRandom, mycountof(pAuthResp->caRandom));
				   break;

				   //

			 default:
					break;
					
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
	 
}


 //
 int  chkLogonIdReq2Stream(unsigned  int  uiStreamId, ChkLogonIdReq* pReq, char* buf, unsigned  int* uiBufSize)
 {
	 int				iErr = -1;
	 int				i = 0;
	 char* ptr = buf;
	 unsigned  int		len = *uiBufSize;

	 if (!pReq)  return  -1;
	 if (!buf)  return  -1;

	 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_start, (void*)uiStreamId, 0, &ptr, &len))  goto  errLabel;

	 //  
	 if (pReq->ucbResp) {
		 if (data2Stream(CONST_qyDataType_char, CONST_qnmCfgId_ucbResp, (void*)pReq->ucbResp, 0, &ptr, &len))  goto  errLabel;
	 }
	 if (pReq->uiLogonId) {
		 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_uiLogonId, (void*)pReq->uiLogonId, 0, &ptr, &len))  goto  errLabel;
	 }


	 //
	 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_null, 0, 0, &ptr, &len))  goto  errLabel;

	 iErr = 0;
 errLabel:
	 if (!iErr) {
		 *uiBufSize = *uiBufSize - len;
	 }
	 return  iErr;

 }


 //
 int  tmpHandler_stream2ChkLogonIdReq(CTX_stream2Data* pCtx, void* p0, void* p1, unsigned  int  uiStreamId, QY_CFGITEM_ntoh_U* pItem)
 {
	 int						iErr = -1;
	 //  p0
	 ChkLogonIdReq* pReq = (ChkLogonIdReq*)p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;

	 if (uiStreamId != CONST_imCommType_chkLogonIdReq)  goto  errLabel;
	 pReq->uiType  =  uiStreamId;

	 unsigned  short  tmp_cfgId;
	 memcpy(&tmp_cfgId, &pItem->head.cfgId, sizeof(short));
	 switch (tmp_cfgId) {
			case  CONST_qnmCfgId_start:
				   pReq->uiType  =  uiStreamId;   
				   break;
			 case  CONST_qnmCfgId_ucbResp:
				   if (getFieldData_char(pItem, (char*)&pReq->ucbResp))  goto  errLabel;		
				   break;
			 case  CONST_qnmCfgId_uiLogonId:
				   if (getFieldData_long(pItem, (long*)&pReq->uiLogonId))  goto  errLabel;		 
				   break;		 
				   //
			 default:
					 break;

	 }

	 //
	 iErr = 0;
 errLabel:
	 return  iErr;

 }







 //
 int  msgRoute2Stream(  unsigned  int  uiStreamId,  MSG_ROUTE  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->idInfo_to.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId_to,  (  void  *  )&pReq->idInfo_to.ui64Id,  sizeof(  pReq->idInfo_to.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->idInfo_from.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId_from,  (  void  *  )&pReq->idInfo_from.ui64Id,  sizeof(  pReq->idInfo_from.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //
	 if  (  pReq->uiMsgRouteId  )  {		//  2008/05/27
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiMsgRouteId,  (  void  *  )pReq->uiMsgRouteId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //
	 if  (  pReq->uiLogonId  )  {			//  2007/12/22
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiLogonId,  (  void  *  )pReq->uiLogonId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //
	 if  (  pReq->usLangId_from  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_langId,  (  void  *  )pReq->usLangId_from,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //
	 if  (  pReq->uiDevType_to  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiDevType_to,  (  void  *  )pReq->uiDevType_to,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
#if  0
	 if  (  pReq->wDevIdStr_to[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_wDevIdStr_to,  pReq->wDevIdStr_to,  lstrlen(  pReq->wDevIdStr_to  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
#endif 
	 if  (  pReq->uiDevType_from  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiDevType_from,  (  void  *  )pReq->uiDevType_from,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
#if  0
	 if  (  pReq->wDevIdStr_from[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_wDevIdStr_from,  pReq->wDevIdStr_from,  lstrlen(  pReq->wDevIdStr_from  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
#endif 
	 //
#if  0	//  2014/09/29
	 if  (  pReq->wReversePath[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_wReversePath,  pReq->wReversePath,  lstrlen(  pReq->wReversePath  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->wForwardPath[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_wForwardPath,  pReq->wForwardPath,  lstrlen(  pReq->wForwardPath  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
#endif
	 //
	 /*	 
	 struct												{
			 QY_MESSENGER_ID							idInfo;
	 }													mems_to[CONST_maxMsgrs_sendTo];	//  2008/03/27, 可同时发到的若干联系人.
	 */
	 //  2009/09/12
	 for  (  i  =  0;  i  <  mycountof(  pReq->mems_to  );  i  ++  )  {
		  //  
		  if  (  !pReq->mems_to[i].idInfo.ui64Id  )  break;
		  //
		  if  (  pReq->mems_to[i].idInfo.ui64Id  )  {		  
			  if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId_to,  (  void  *  )&pReq->mems_to[i].idInfo.ui64Id,  sizeof(  pReq->mems_to[i].idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
		  }
	 }
	 //
	 if  (  pReq->uiObjType_src  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiObjType,  (  void  *  )pReq->uiObjType_src,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->ulDetectedIp_from  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_ulDetectedIp,  (  void  *  )pReq->ulDetectedIp_from,  0,  &ptr,  &len  )  )  goto  errLabel;    
	 }
	 if  (  pReq->displayName_from[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_displayName, pReq->displayName_from,  lstrlen(  pReq->displayName_from  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //  以下为了解数据报的性能而做.通常在release中是要取消的
	 if  (  pReq->debugInfo.tTime_start  )  {

		 //  发起端
		 if  (  pReq->debugInfo.tTime_start  )  {
			 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tTime_start,  (  void  *  )&pReq->debugInfo.tTime_start,  sizeof(  pReq->debugInfo.tTime_start  ),  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.usElapsed_toSend  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_toSend,  (  void  *  )pReq->debugInfo.usElapsed_toSend,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }

		 //  2008/11/19
		 if  (  pReq->debugInfo.index  )  {
			 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_index,  (  void  *  )pReq->debugInfo.index,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }

		 //  server转发请求
		 if  (  pReq->debugInfo.req.tTime_serv_startToRecv  )  {
			 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tTime_serv_startToRecv,  (  void  *  )&pReq->debugInfo.req.tTime_serv_startToRecv,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.req.usElapsed_serv_recved  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_serv_recved,  (  void  *  )pReq->debugInfo.req.usElapsed_serv_recved,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.req.usElapsed_serv_startToProcess  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_serv_startToProcess,  (  void  *  )pReq->debugInfo.req.usElapsed_serv_startToProcess,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }				 
		 if  (  pReq->debugInfo.req.usElapsed_serv_toFindDst  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_serv_toFindDst,  (  void  *  )pReq->debugInfo.req.usElapsed_serv_toFindDst,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.req.usElapsed_serv_toBeSwitched  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_serv_toBeSwitched,  (  void  *  )pReq->debugInfo.req.usElapsed_serv_toBeSwitched,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.req.usElapsed_serv_toSend  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_serv_toSend,  (  void  *  )pReq->debugInfo.req.usElapsed_serv_toSend,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }

		 //  接受并响应端
		 if  (  pReq->debugInfo.dwTickCnt_peer_recved  )  {
			 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_dwTickCnt_peer_recved,  (  void  *  )pReq->debugInfo.dwTickCnt_peer_recved,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.tTime_peer_recved  )  {
			 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tTime_peer_recved,  (  void  *  )&pReq->debugInfo.tTime_peer_recved,  sizeof(  pReq->debugInfo.tTime_peer_recved  ),  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.usElapsed_peer_resp_toSend  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_peer_resp_toSend,  (  void  *  )pReq->debugInfo.usElapsed_peer_resp_toSend,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }

		 //  server转发响应
		 if  (  pReq->debugInfo.resp.tTime_serv_startToRecv  )  {
			 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tTime_serv_resp_startToRecv,  (  void  *  )&pReq->debugInfo.resp.tTime_serv_startToRecv,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.resp.usElapsed_serv_recved  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_serv_resp_recved,  (  void  *  )pReq->debugInfo.resp.usElapsed_serv_recved,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.resp.usElapsed_serv_startToProcess  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_serv_resp_startToProcess,  (  void  *  )pReq->debugInfo.resp.usElapsed_serv_startToProcess,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }				 
		 if  (  pReq->debugInfo.resp.usElapsed_serv_toFindDst  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_serv_resp_toFindDst,  (  void  *  )pReq->debugInfo.resp.usElapsed_serv_toFindDst,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.resp.usElapsed_serv_toBeSwitched  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_serv_resp_toBeSwitched,  (  void  *  )pReq->debugInfo.resp.usElapsed_serv_toBeSwitched,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.resp.usElapsed_serv_toSend  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_serv_resp_toSend,  (  void  *  )pReq->debugInfo.resp.usElapsed_serv_toSend,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }

		 //  响应回到发起端
		 //  if  (  pReq->debugInfo.dwTickCnt_resp_recved  )  {
		 //		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_dwTickCnt_resp_recved,  (  void  *  )pReq->debugInfo.dwTickCnt_resp_recved,  0,  &ptr,  &len  )  )  goto  errLabel;
		 //	 }
		 //	 if  (  pReq->debugInfo.usElapsed_resp_end  )  {
		 //		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_resp_end,  (  void  *  )pReq->debugInfo.usElapsed_resp_end,  0,  &ptr,  &len  )  )  goto  errLabel;
		 //	 }
	 }
				
	 

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2MsgRoute(  CTX_stream2Data  *  pCtx,  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 MSG_ROUTE				*	pContent	=	(  MSG_ROUTE  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_msgRoute  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_displayName:
				   if  (  getFieldData_wStr(  pItem,  pContent->displayName_from,  mycountof(  pContent->displayName_from  )  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_ulDetectedIp:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->ulDetectedIp_from  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiObjType:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiObjType_src  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiDevType_from:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiDevType_from  )  )  goto  errLabel;
				   break;
#if  0
			 case  CONST_qnmCfgId_wDevIdStr_from:
				   if  (  getFieldData_wStr(  pItem,  pContent->wDevIdStr_from,  mycountof(  pContent->wDevIdStr_from  )  )  )  goto  errLabel;
				   break;
#endif 
			 case  CONST_qnmCfgId_uiDevType_to:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiDevType_to  )  )  goto  errLabel;
				   break;
#if  0
			 case  CONST_qnmCfgId_wDevIdStr_to:
				   if  (  getFieldData_wStr(  pItem,  pContent->wDevIdStr_to,  mycountof(  pContent->wDevIdStr_to  )  )  )  goto  errLabel;
				   break;
#endif 
				#if  0	//  2014/09/29
			 case  CONST_qnmCfgId_wReversePath:
				   if  (  getFieldData_wStr(  pItem,  pContent->wReversePath,  mycountof(  pContent->wReversePath  )  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_wForwardPath:
				   if  (  getFieldData_wStr(  pItem,  pContent->wForwardPath,  mycountof(  pContent->wForwardPath  )  )  )  goto  errLabel;
				   break;
				#endif
			 case  CONST_qnmCfgId_langId:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usLangId_from  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiLogonId:		//  2007/12/22
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiLogonId  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiMsgRouteId:		//  2008/05/27
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiMsgRouteId  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_messengerId_from:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->idInfo_from.ui64Id  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_messengerId_to:
				   if  (  !pContent->idInfo_to.ui64Id  )  {
					   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->idInfo_to.ui64Id  )  )  goto  errLabel;
					   }
				   else  {
					     if  (  pContent->tmpInternal.usCnt_mems_to  >=  mycountof(  pContent->mems_to  )  )  {
							 traceLogA(  (char*)"stream2MsgRoute: usCnt_mems_to >= mycountof(  mems_to  )"  );
						     break;
						 }
						 if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->mems_to[pContent->tmpInternal.usCnt_mems_to].idInfo.ui64Id  )  )  goto  errLabel;
						 pContent->tmpInternal.usCnt_mems_to  ++  ;					     
				   }
				   break;

		     //  下面为一些用于性能评估的参数

			 case  CONST_qnmCfgId_tTime_start:
				   if  (  getFieldData_l64(  pItem,  &pContent->debugInfo.tTime_start  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_toSend:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.usElapsed_toSend  )  )  goto  errLabel;
				   break;

			 case  CONST_qnmCfgId_index:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->debugInfo.index  )  )  goto  errLabel;
				   break;
			 //
			 case  CONST_qnmCfgId_tTime_serv_startToRecv:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->debugInfo.req.tTime_serv_startToRecv  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_serv_recved:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.req.usElapsed_serv_recved  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_serv_startToProcess:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.req.usElapsed_serv_startToProcess  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_serv_toFindDst:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.req.usElapsed_serv_toFindDst  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_serv_toBeSwitched:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.req.usElapsed_serv_toBeSwitched  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_serv_toSend:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.req.usElapsed_serv_toSend  )  )  goto  errLabel;
				   break;
			 //			
			 case  CONST_qnmCfgId_dwTickCnt_peer_recved:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->debugInfo.dwTickCnt_peer_recved  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_tTime_peer_recved:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->debugInfo.tTime_peer_recved  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_peer_resp_toSend:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.usElapsed_peer_resp_toSend  )  )  goto  errLabel;
				   break;
		     //		
			 case  CONST_qnmCfgId_tTime_serv_resp_startToRecv:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->debugInfo.resp.tTime_serv_startToRecv  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_serv_resp_recved:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.resp.usElapsed_serv_recved  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_serv_resp_startToProcess:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.resp.usElapsed_serv_startToProcess  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_serv_resp_toFindDst:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.resp.usElapsed_serv_toFindDst  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_serv_resp_toBeSwitched:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.resp.usElapsed_serv_toBeSwitched  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_serv_resp_toSend:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.resp.usElapsed_serv_toSend  )  )  goto  errLabel;
				   break;
			 //
			 //  case  CONST_qnmCfgId_dwTickCnt_resp_recved:
			 //	   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->debugInfo.dwTickCnt_resp_recved  )  )  goto  errLabel;
			 //	   break;
			 //  case  CONST_qnmCfgId_usElapsed_resp_end:
			 //	   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.usElapsed_resp_end  )  )  goto  errLabel;
			 //	   break;
				

			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}


////////////////


 int  imHtmlContent2Stream(  unsigned  int  uiStreamId,  IM_HTML_CONTENT  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 //  2014/07/11
	 if  (  pReq->ucbResp  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbResp,  (  void  *  )pReq->ucbResp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //  2015/02/16
	 if  (  pReq->idInfo_logicalPeer.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_logicalPeer,  (  void  *  )&pReq->idInfo_logicalPeer.ui64Id,  sizeof(  pReq->idInfo_logicalPeer.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
	 }



	 //
	 if  (  pReq->uiSerialNo  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiSerialNo,  (  void  *  )pReq->uiSerialNo,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->wBuf[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_hint, pReq->wBuf,  lstrlen(  pReq->wBuf  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2ImHtmlContent(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 IM_HTML_CONTENT		*	pContent	=	(  IM_HTML_CONTENT  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_htmlContent  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pContent->uiType  =  uiStreamId;   
				   break;
				   //  2014/07/11
			 case  CONST_qnmCfgId_ucbResp:
				   if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->ucbResp  )  )  goto  errLabel;
				   break;
				   //  2015/02/14
			 case  CONST_qnmCfgId_idInfo_logicalPeer:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->idInfo_logicalPeer.ui64Id  )  )  goto  errLabel;				   
				   break;

				   //
			 case  CONST_qnmCfgId_hint:
				   if  (  getFieldData_wStr(  pItem,  pContent->wBuf,  mycountof(  pContent->wBuf  )  )  )  goto  errLabel;
				   break;
#if  0
			 case  CONST_qnmCfgId_tStartTime_serv:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->tStartTime_serv  )  )  goto  errLabel;
				   break;
#endif
			 case  CONST_qnmCfgId_uiSerialNo:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiSerialNo  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}


 ///////////////////////  2014/07/11
 int  queryPeerStatus2Stream(  unsigned  int  uiStreamId,  QUERY_peer_status  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 if  (  pReq->ucbResp  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbResp,  (  void  *  )pReq->ucbResp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}

  int  tmpHandler_stream2QueryPeerStatus(  CTX_stream2Data  *  pCtx,  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 QUERY_peer_status		*	pContent	=	(  QUERY_peer_status  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_queryPeerStatus  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pContent->uiType  =  uiStreamId;   
				   break;
			 case  CONST_qnmCfgId_ucbResp:
				   if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->ucbResp  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}

////////////////////


 int  rtcCallReq2Stream(  unsigned  int  uiStreamId,  RTC_CALL_REQ  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->uiTaskType  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTaskType,  (  void  *  )pReq->uiTaskType,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->ulIp_caller  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_ulIp_caller,  (  void  *  )pReq->ulIp_caller,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2RtcCallReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 RTC_CALL_REQ			*	pContent	=	(  RTC_CALL_REQ  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_rtcCallReq  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pContent->uiType  =  uiStreamId;
				   break;
			 case  CONST_qnmCfgId_uiTaskType:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTaskType  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_ulIp_caller:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->ulIp_caller  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}


//////////////////

  int  qyhtonVideoHeader(  QY_VIDEO_HEADER  *  pVh  )
{
	if  (  !pVh  )  return  -1;
	BITMAPINFOHEADER	*	p  =  &pVh->bih;

	if  (  !p->biSize  )  p->biSize  =  sizeof(  BITMAPINFOHEADER  );
	if  (  p->biSize  <  sizeof(  pVh->bih  )  )  {
		traceLogA( (char*) "Warning: qyhtonVideoHeader failed: biSize too small, %d",  p->biSize  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  NULL,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "qyhtonVideoHeader: biSize too small %d"  ),  p->biSize  );
		return  -1;
	}
	if  (  p->biSize  >  sizeof(  pVh->bih  )  +  sizeof(  pVh->bPrivateData  )  )  {
		traceLogA(  (char*)"qyhtonVideoHeader failed: biSize too large, %d",  p->biSize  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  NULL,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "qyhtonVideoHeader: biSize too large %d"  ),  p->biSize  );
		return  -1;
	}

	DWORD	biSize  =  p->biSize;

	MACRO_htonl(  p->biSize  );
	MACRO_htonl(  p->biWidth  );
	MACRO_htonl(  p->biHeight  );
	MACRO_htons(  p->biPlanes  );
	MACRO_htons(  p->biBitCount  );
	MACRO_htonl(  p->biCompression  );
	MACRO_htonl(  p->biSizeImage  );
	MACRO_htonl(  p->biXPelsPerMeter  );
	MACRO_htonl(  p->biYPelsPerMeter  );
	MACRO_htonl(  p->biClrUsed  );
	MACRO_htonl(  p->biClrImportant  );

	return  biSize;
}

#if  0
 int  qyntohVideoHeader(  QY_VIDEO_HEADER  *  pVh  )
{
	if  (  !pVh  )  return  -1;
	BITMAPINFOHEADER  *  p  =  &pVh->bih;
	
	MACRO_ntohl(  p->biSize  );
	if  (  !p->biSize  )  p->biSize  =  sizeof(  BITMAPINFOHEADER  );
	if  (  p->biSize  <  sizeof(  pVh->bih  )  )  {
		traceLogA(  "Warning: qyntohVideoHeader: biSize too small, %d",  p->biSize  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  NULL,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "qyntohVideoHeader: biSize to small %d"  ),  p->biSize  );
		return  -1;
	}
	if  (  p->biSize  >  sizeof(  pVh->bih  )  +  sizeof(  pVh->bPrivateData  )  )  {
		traceLogA(  "qyntohVideoHeader: biSize too large, %d",  p->biSize  );
		return  -1;
	}

	MACRO_ntohl(  p->biWidth  );
	MACRO_ntohl(  p->biHeight  );
	MACRO_ntohs(  p->biPlanes  );
	MACRO_ntohs(  p->biBitCount  );
	MACRO_ntohl(  p->biCompression  );
	MACRO_ntohl(  p->biSizeImage  );
	MACRO_ntohl(  p->biXPelsPerMeter  );
	MACRO_ntohl(  p->biYPelsPerMeter  );
	MACRO_ntohl(  p->biClrUsed  );
	MACRO_ntohl(  p->biClrImportant  );

	return  sizeof(  pVh[0]  );
}
#else
 int  qyntohVideoHeader(  QY_VIDEO_HEADER  *  pVh  )
{
	if  (  !pVh  )  return  -1;
	BITMAPINFOHEADER  *  p  =  &pVh->bih;
	
	MACRO_ntohl(  p->biSize  );

	DWORD  tmp_biSize;
	memcpy(  &tmp_biSize,  &p->biSize,  sizeof(  tmp_biSize  )  );
	if  (  !tmp_biSize  )  tmp_biSize  =  sizeof(  BITMAPINFOHEADER  );
	if  (  tmp_biSize  <  sizeof(  pVh->bih  )  )  {
		traceLogA(  (char*)"Warning: qyntohVideoHeader: biSize too small, %d",  tmp_biSize  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  NULL,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "qyntohVideoHeader: biSize to small %d"  ),  tmp_biSize  );
		return  -1;
	}
	if  (  tmp_biSize  >  sizeof(  pVh->bih  )  +  sizeof(  pVh->bPrivateData  )  )  {
		traceLogA(  (char*)"qyntohVideoHeader: biSize too large, %d",  tmp_biSize  );
		return  -1;
	}
	memcpy(  &p->biSize,  &tmp_biSize,  sizeof(  p->biSize  )  );

	MACRO_ntohl(  p->biWidth  );
	MACRO_ntohl(  p->biHeight  );
	MACRO_ntohs(  p->biPlanes  );
	MACRO_ntohs(  p->biBitCount  );
	MACRO_ntohl(  p->biCompression  );
	MACRO_ntohl(  p->biSizeImage  );
	MACRO_ntohl(  p->biXPelsPerMeter  );
	MACRO_ntohl(  p->biYPelsPerMeter  );
	MACRO_ntohl(  p->biClrUsed  );
	MACRO_ntohl(  p->biClrImportant  );

	return  sizeof(  pVh[0]  );
}
#endif





/////////////////

  int  qyhtonAudioHeader(  QY_AUDIO_HEADER  *  pAh  )
{
	if  (  !pAh  )  return  -1;
	WAVEFORMATEX  *  p  =  &pAh->wfx;
	if  (  p->cbSize  >  sizeof(  pAh->bExtraData  )  )  {
		traceLogA(  (char*)"qyhtonAudioHeader failed: cbSize too large, %d",  p->cbSize  );
		return  -1;
	}

	DWORD	biSize  =  sizeof(  p[0]  )  +  p->cbSize;

	MACRO_htons(  p->wFormatTag  );        // format type 
	MACRO_htons(  p->nChannels  );         // number of channels (i.e. mono, stereo...) 
	MACRO_htonl(  p->nSamplesPerSec  );    // sample rate 
	MACRO_htonl(  p->nAvgBytesPerSec  );   // for buffer estimation 
	MACRO_htons(  p->nBlockAlign  );       // block size of data 
	MACRO_htons(  p->wBitsPerSample  );    // Number of bits per sample of mono data 
	MACRO_htons(  p->cbSize  );            // The count in bytes of the size of  

	return  biSize;
}

 int  qyntohAudioHeader(  QY_AUDIO_HEADER  *  pAh  )
{
	if  (  !pAh  )  return  -1;
	WAVEFORMATEX	*	p	=	&pAh->wfx;

	MACRO_ntohs(  p->wFormatTag  );        // format type 
	MACRO_ntohs(  p->nChannels  );         // number of channels (i.e. mono, stereo...) 
	MACRO_ntohl(  p->nSamplesPerSec  );    // sample rate 
	MACRO_ntohl(  p->nAvgBytesPerSec  );   // for buffer estimation 
	MACRO_ntohs(  p->nBlockAlign  );       // block size of data 
	MACRO_ntohs(  p->wBitsPerSample  );    // Number of bits per sample of mono data 
	MACRO_ntohs(  p->cbSize  );            // The count in bytes of the size of  

	WORD	tmp_cbSize;
	memcpy(  &tmp_cbSize,  &p->cbSize,  sizeof(  tmp_cbSize  )  );
	if  (  tmp_cbSize  >  sizeof(  pAh->bExtraData  )  )  {
		traceLogA(  (char*)"qyntohAudioHeader failed: cbSize too large, %d",  tmp_cbSize  );
		return  -1;
	}

	return  sizeof(  p[0]  );
}

 //  2014/11/07
 int  tmp_htonTranVideo(  TRAN_video  *  pTranVideo,  char  **  ppBuf,  unsigned  int  *  puiBufSize  )
 {
	int					iErr	=	-1;
	int					i		=  0;
	char			*	ptr		=	*ppBuf;
	unsigned  int		len		=	*puiBufSize;


#if  10	//  2014/11/07
	 //
	 if  (  pTranVideo->uiTranNo_openAvDev  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_openVideoDev,  (  void  *  )pTranVideo->uiTranNo_openAvDev,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  pTranVideo->compressor.common.ucCompressors  )  {  //  200903/30
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucVideoCompressors,  (  void  *  )pTranVideo->compressor.common.ucCompressors,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pTranVideo->compressor.common.fourccStr[0]  )  {
		 //if  (  data2Stream(  CONST_qyDataType_str,  CONST_qnmCfgId_fourccStr,  pTranVideo->compressor.common.fourccStr,  strlen(  pTranVideo->compressor.common.fourccStr  ),  &ptr,  &len  )  )  goto  errLabel;
		 int iFourcc = fourccStr2i(pTranVideo->compressor.common.fourccStr);
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_iFourcc,  (void*)iFourcc,  0,  &ptr,  &len  )  )  goto  errLabel;
		 
	 }
	 //	 
	 if (0 != pTranVideo->compressor.ucbNeedKeyFrameFirst)
	 {
		 if (0 != data2Stream(CONST_qyDataType_byte, CONST_qnmCfgId_ucbNeedKeyFrameFirst, (void*)pTranVideo->compressor.ucbNeedKeyFrameFirst, 0, &ptr, &len)) goto errLabel;
	 }
	 //

	 //
	 if  (  pTranVideo->compressor.common.usMaxFps_toShareBmp  )  {	//  2014/08/07
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMaxFps_toShareBmp,  (  void  *  )pTranVideo->compressor.common.usMaxFps_toShareBmp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //
#if  0
	 if  (  pTranVideo->compressor.common.ucbOutputFlippedImg  )  {	//  2011/12/11
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbFlippedImg,  (  void  *  )pTranVideo->compressor.common.ucbOutputFlippedImg,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
#endif
	 
	 //  
	 int												tmpLen;
	 QY_VIDEO_HEADER									vh;
	 memcpy(  &vh,  &pTranVideo->vh_compress,  sizeof(  vh  )  );
	 if  (  (  tmpLen  =  qyhtonVideoHeader(  &vh  )  )  <  0  )  goto  errLabel;
	 if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_bih_compress,  &vh,  tmpLen,  &ptr,  &len  )  )  goto  errLabel;

	 //  2014/09/23
	 if  (  bSupported_sendVhDec(  )  )  {
		 memcpy(  &vh,  &pTranVideo->vh_decompress,  sizeof(  vh  )  );
		 if  (  (  tmpLen  =  qyhtonVideoHeader(  &vh  )  )  <  0  )  goto  errLabel;
		 if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_bih_decompress,  &vh,  tmpLen,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //  2014/03/30
	 if  (  pTranVideo->vh_stream.usCnt  )  {
		 char  spsPps[512]  =  "";
		 unsigned  int	spsLen  =  0;
#if  0
		 if  (  pTranVideo->vh_stream.usCnt  >  mycountof(  pTranVideo->vh_stream.mems  )  )  goto  errLabel;
		 for  (  i  =  0;  i  <  pTranVideo->vh_stream.usCnt;  i  ++  )  {
			  if  (  spsLen  +  pTranVideo->vh_stream.mems[i].usLen  >  sizeof(  spsPps  )  )  {
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  NULL,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "htonAvTranInfo failed: spsLen too small"  )  );
				  goto  errLabel;
			  }
			  memcpy(  spsPps  +  spsLen,  pTranVideo->vh_stream.mems[i].spsPps,  pTranVideo->vh_stream.mems[i].usLen  );
			  spsLen  +=  pTranVideo->vh_stream.mems[i].usLen;
		 }
#endif
		 //  2017/10/10
		 spsLen  =  mycountof(  spsPps  );
		 if  (  makeSpsPps(  &pTranVideo->vh_stream,  spsPps,  &spsLen  )  )  {
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  NULL,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "htonAvTranInfo failed: makeSpsPps failed"  )  );
			 goto  errLabel;
		 }
		 //
		 if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_spsPps,  spsPps,  spsLen,  &ptr,  &len  )  )  goto  errLabel;
	 }
#endif


	iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *ppBuf  =  ptr;
		 *puiBufSize  =  len;
	 }
	 return  iErr;

 }



 int  tmp_ntohTranVideo(  QY_CFGITEM_ntoh_U  *  pItem,  TRAN_video  *  pTranVideo,  BOOL  *  pbProcessed  )
{
	 int						iErr		=	-1;
	 int						tmpLen;
	 char						buf[sizeof(  QY_VIDEO_HEADER  )  +  1024];
	 BOOL						bProcessed  =  FALSE;

	 	 

	 //
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

				   
	 //
	 if  (  pTranVideo  )  {
		 //
		 bProcessed  =  TRUE;
		 //
		 switch  (  tmp_cfgId  )  {
				 case  CONST_qnmCfgId_uiTranNo_openVideoDev:
					   if  (  getFieldData_long(  pItem,  (  long  *  )&pTranVideo->uiTranNo_openAvDev  )  )  goto  errLabel;
					   break;

				 case  CONST_qnmCfgId_ucVideoCompressors:	//  2009/03/30
					   if  (  getFieldData_char(  pItem,  (  char  *  )&pTranVideo->compressor.common.ucCompressors  )  )  goto  errLabel;
					   break;
				 case  CONST_qnmCfgId_iFourcc:
					   //if  (  getFieldData_str(  pItem,  pTranVideo->compressor.common.fourccStr,  mycountof(  pTranVideo->compressor.common.fourccStr  )  )  )  goto  errLabel;
					   int iFourcc;
					   if  (  getFieldData_long(  pItem, (long*) &iFourcc  )  )  goto  errLabel;
					   iFourcc2Str(iFourcc,pTranVideo->compressor.common.fourccStr,mycountof(pTranVideo->compressor.common.fourccStr));					   
					   break;
					   //
				 case CONST_qnmCfgId_ucbNeedKeyFrameFirst:
					 if (0 != getFieldData_char(pItem, (char*)&pTranVideo->compressor.ucbNeedKeyFrameFirst)) goto errLabel;
					 break;

				 case  CONST_qnmCfgId_usMaxFps_toShareBmp:	//  2014/08/07
					   if  (  getFieldData_short(  pItem,  (  short  *  )&pTranVideo->compressor.common.usMaxFps_toShareBmp  )  )  goto  errLabel;
					   break;
#if  0  //  2014/12/02
				 case  CONST_qnmCfgId_ucbFlippedImg:		//  2011/12/11
					   if  (  getFieldData_char(  pItem,  (  char  *  )&pTranVideo->compressor.common.ucbOutputFlippedImg  )  )  goto  errLabel;
					   break;
#endif
				 case  CONST_qnmCfgId_bih_compress:
					   tmpLen  =  sizeof(  buf  );
					   if  (  getFieldData_data(  pItem,  buf,  (  unsigned  int  *  )&tmpLen  )  )  goto  errLabel;
					   if  (  tmpLen  >  sizeof(  buf  )  )  goto  errLabel;											//  impossible  
					   memset(  buf  +  tmpLen,  0,  sizeof(  buf  )  -  tmpLen  );
					   if  (  qyntohVideoHeader(  (  QY_VIDEO_HEADER  *  )buf  )  <  0  )  goto  errLabel;
					   memcpy(  &pTranVideo->vh_compress,  buf,  sizeof(  pTranVideo->vh_compress  )  );
					   break;
				 case  CONST_qnmCfgId_bih_decompress:
					   tmpLen  =  sizeof(  buf  );
					   if  (  getFieldData_data(  pItem,  buf,  (  unsigned  int  *  )&tmpLen  )  )  goto  errLabel;
					   if  (  tmpLen  >  sizeof(  buf  )  )  goto  errLabel;											//  impossible  
					   memset(  buf  +  tmpLen,  0,  sizeof(  buf  )  -  tmpLen  );
					   if  (  qyntohVideoHeader(  (  QY_VIDEO_HEADER  *  )buf  )  <  0  )  goto  errLabel;
					   memcpy(  &pTranVideo->vh_decompress,  buf,  sizeof(  pTranVideo->vh_decompress  )  );
					   break;
				 case  CONST_qnmCfgId_spsPps:  {	//  2014/03/30
					   tmpLen  =  sizeof(  buf  );
					   if  (  getFieldData_data(  pItem,  buf,  (  unsigned  int  *  )&tmpLen  )  )  goto  errLabel;
					   if  (  tmpLen  >  sizeof(  buf  )  )  goto  errLabel;
					   //  2017/10/09
					   int  iFourcc  =  fourccStr2i(  pTranVideo->compressor.common.fourccStr  );
					   if  (  !iFourcc  )  {
						   iFourcc  =  pTranVideo->vh_stream.dwFourcc;
					   }
					   //
					   VH_stream  *  pVh_stream  =  &pTranVideo->vh_stream;
					   //
#if  0  //  2017/10/10
					   unsigned  int  spsLen  =  sizeof(  pVh_stream->mems[0].spsPps  );
					   unsigned  int  ppsLen  =  sizeof(  pVh_stream->mems[1].spsPps  );
					   if  (  parseSpsPps(  iFourcc,  buf,  tmpLen,  pVh_stream->mems[0].spsPps,  &spsLen,  pVh_stream->mems[1].spsPps,  &ppsLen,  NULL,  NULL  )  )  {
						   //
						   qyShowInfo1(  CONST_qyShowType_qwmComm,  NULL,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tmp_ntohTranVideo: parseSpsPps failed"  )  );
						   //
						   goto  errLabel;
					   }
					   pVh_stream->mems[0].usLen  =  spsLen;
					   pVh_stream->mems[1].usLen  =  ppsLen;
					   pVh_stream->usCnt  =  2;
#endif
					   //  2017/10/10
					   if  (  parseSpsPps1(  iFourcc,  buf,  tmpLen,  pVh_stream  )  )  {
						   qyShowInfo1(  CONST_qyShowType_qwmComm,  NULL,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tmp_ntohTranVideo: parseSpsPps1 failed"  )  );
						   goto  errLabel;
					   }
					   //
					   }
					   break;
				 default:
					    //
					    bProcessed  =  FALSE;

						break;	 
		 }
	 }


	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 if  (  pbProcessed  )  *pbProcessed  =  bProcessed;
	 }
	 return  iErr;
}


 //////////////////////////////

 int  tmp_htonAudioPlayCfg(  AUDIO_PLAY_CFG  *  pAudioPlayCfg,  char  **  ppBuf,  unsigned  int  *  puiBufSize  )
 {
	int					iErr	=	-1;
	int					i		=  0;
	char			*	ptr		=	*ppBuf;
	unsigned  int		len		=	*puiBufSize;

#if  0

	 //  2009/06/14
	 if  (  pAudioPlayCfg->usMinTimeInMsOfAudioDataPlaying  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMinTimeInMsOfAudioDataPlaying,  (  void  *  )pAudioPlayCfg->usMinTimeInMsOfAudioDataPlaying,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pAudioPlayCfg->usAudioDataAddedToPlayEveryTime  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usAudioDataAddedToPlayEveryTime,  (  void  *  )pAudioPlayCfg->usAudioDataAddedToPlayEveryTime,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pAudioPlayCfg->usNotifyIntervalInMs_needMoreAudioData  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usNotifyIntervalInMs_needMoreAudioData,  (  void  *  )pAudioPlayCfg->usNotifyIntervalInMs_needMoreAudioData,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //  2012/01/27
	 if  (  pAudioPlayCfg->usMinTimeInMsToPlay  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMinTimeInMsToPlay,  (  void  *  )pAudioPlayCfg->usMinTimeInMsToPlay,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //  2009/06/03
	 if  (  pAudioPlayCfg->usMaxTimeInMsToPlay  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMaxTimeInMsToPlay,  (  void  *  )pAudioPlayCfg->usMaxTimeInMsToPlay,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pAudioPlayCfg->usMaxTimeInMsToBeRemoved  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMaxTimeInMsToBeRemoved,  (  void  *  )pAudioPlayCfg->usMaxTimeInMsToBeRemoved,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
#endif


	iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *ppBuf  =  ptr;
		 *puiBufSize  =  len;
	 }
	 return  iErr;

 }


 int  tmp_ntohAudioPlayCfg(  QY_CFGITEM_ntoh_U  *  pItem,  AUDIO_PLAY_CFG  *  pAudioPlayCfg,  BOOL  *  pbProcessed  )
{
	 int						iErr		=	-1;
	 int						tmpLen;
	 char						buf[sizeof(  QY_VIDEO_HEADER  )  +  1024];
	 BOOL						bProcessed  =  FALSE;
	 
	 //
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
	 

	 if  (  pAudioPlayCfg  )  {
		 //
		 bProcessed  =  TRUE;
		 //
		 switch  (  tmp_cfgId  )  {
#if  0
				   //  2009/06/14
			 case  CONST_qnmCfgId_usMinTimeInMsOfAudioDataPlaying:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pAudioPlayCfg->usMinTimeInMsOfAudioDataPlaying  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usAudioDataAddedToPlayEveryTime:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pAudioPlayCfg->usAudioDataAddedToPlayEveryTime  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usNotifyIntervalInMs_needMoreAudioData:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pAudioPlayCfg->usNotifyIntervalInMs_needMoreAudioData  )  )  goto  errLabel;
				   break;
				   //
			 case  CONST_qnmCfgId_usMinTimeInMsToPlay:		//  2012/01/27
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pAudioPlayCfg->usMinTimeInMsToPlay  )  )  goto  errLabel;
				   break;
				   //
			 case  CONST_qnmCfgId_usMaxTimeInMsToPlay:		//  2009/06/03
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pAudioPlayCfg->usMaxTimeInMsToPlay  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usMaxTimeInMsToBeRemoved:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pAudioPlayCfg->usMaxTimeInMsToBeRemoved  )  )  goto  errLabel;
				   break;
#endif
			 default:
				    bProcessed  =  FALSE;

					break;	 
		 }
	 }

	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 if  (  pbProcessed  )  *pbProcessed  =  bProcessed;
	 }
	 return  iErr;
}




 /////////////////////////////////////


 //  2014/11/07
 int  tmp_htonTranAudio(  TRAN_audio  *  pTranAudio,  char  **  ppBuf,  unsigned  int  *  puiBufSize  )
 {
	int					iErr	=	-1;
	int					i		=  0;
	char			*	ptr		=	*ppBuf;
	unsigned  int		len		=	*puiBufSize;


	//  2014/11/07
	 //
	 if  (  pTranAudio->uiTranNo_openAvDev  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_openAudioDev,  (  void  *  )pTranAudio->uiTranNo_openAvDev,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pTranAudio->compressor.common.ucCompressors  )  {		//  2009/05/18
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucAudioCompressors,  (  void  *  )pTranAudio->compressor.common.ucCompressors,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pTranAudio->compressor.uiBytesRecorded_perBlockAlign  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiBytesRecorded_perBlockAlign,  (  void  *  )pTranAudio->compressor.uiBytesRecorded_perBlockAlign,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }


	 int												tmpLen;
	 //  WAVEFORMATEX										wf;
	 QY_AUDIO_HEADER									ah;
	 memcpy(  &ah,  &pTranAudio->ah_compress,  sizeof(  ah  )  );
	 if  (  (  tmpLen  =  qyhtonAudioHeader(  &ah  )  )  <  0  )  goto  errLabel;
	 if  (  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_wf_compress,  &ah,  tmpLen,  &ptr,  &len  )  )  )  goto  errLabel;

	 //  2009/04/27
	 memcpy(  &ah,  &pTranAudio->ah_decompress,  sizeof(  ah  )  );
	 if  (  (  tmpLen  =  qyhtonAudioHeader(  &ah  )  )  <  0  )  goto  errLabel;
	 if  (  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_wf_decompress,  &ah,  tmpLen,  &ptr,  &len  )  )  )  goto  errLabel;

	 //  2016/12/23
	 if  (  pTranAudio->ah_stream.mems[0].usLen  +  pTranAudio->ah_stream.mems[1].usLen  +  pTranAudio->ah_stream.mems[2].usLen  )  {
		 AH_stream  *  pAs  =  &pTranAudio->ah_stream;
		 if  (  pAs->mems[0].usLen  +  pAs->mems[1].usLen  +  pAs->mems[2].usLen  >  sizeof(  pAs->buf  )  )  goto  errLabel;
		 char  *  pHeader0  =  pAs->buf;
		 char  *  pHeader1  =  pAs->buf  +  pAs->mems[0].usLen;
		 char  *  pHeader2  =  pAs->buf  +  pAs->mems[0].usLen  +  pAs->mems[1].usLen;
		 //
#if  0
		 if  (  pAs->mems[0].usLen  )  {
			 if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_vorbis_header0,  pHeader0,  pAs->mems[0].usLen,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pAs->mems[1].usLen  )  {
			 if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_vorbis_header1,  pHeader1,  pAs->mems[1].usLen,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pAs->mems[2].usLen  )  {
			 if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_vorbis_header2,  pHeader2,  pAs->mems[2].usLen,  &ptr,  &len  )  )  goto  errLabel;
		 }
#endif

		 //
		 #ifdef  __DEBUG__
		#if  10
			  int  iii;
			  for  (  iii  =  0;  iii  <  58;  iii  ++  )  {
				   TCHAR  tt[128];
				   _sntprintf(  tt,  mycountof(  tt  ),  _T(  "header[%d] %02x\n"  ),  iii,  (  unsigned  char  )pAs->buf[iii]  );
				   OutputDebugString(  tt  );
			  }
			  iii  =  iii;
		#endif
#endif

	 }



	 //
#if  0
	 //  2009/06/14
	 if  (  pTranAudio->compressor.playCfg.usMinTimeInMsOfAudioDataPlaying  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMinTimeInMsOfAudioDataPlaying,  (  void  *  )pTranAudio->compressor.playCfg.usMinTimeInMsOfAudioDataPlaying,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pTranAudio->compressor.playCfg.usAudioDataAddedToPlayEveryTime  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usAudioDataAddedToPlayEveryTime,  (  void  *  )pTranAudio->compressor.playCfg.usAudioDataAddedToPlayEveryTime,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pTranAudio->compressor.playCfg.usNotifyIntervalInMs_needMoreAudioData  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usNotifyIntervalInMs_needMoreAudioData,  (  void  *  )pTranAudio->compressor.playCfg.usNotifyIntervalInMs_needMoreAudioData,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //  2012/01/27
	 if  (  pTranAudio->compressor.playCfg.usMinTimeInMsToPlay  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMinTimeInMsToPlay,  (  void  *  )pTranAudio->compressor.playCfg.usMinTimeInMsToPlay,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //  2009/06/03
	 if  (  pTranAudio->compressor.playCfg.usMaxTimeInMsToPlay  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMaxTimeInMsToPlay,  (  void  *  )pTranAudio->compressor.playCfg.usMaxTimeInMsToPlay,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pTranAudio->compressor.playCfg.usMaxTimeInMsToBeRemoved  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMaxTimeInMsToBeRemoved,  (  void  *  )pTranAudio->compressor.playCfg.usMaxTimeInMsToBeRemoved,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
#endif
	 //  2014/11/07
	 if  (  tmp_htonAudioPlayCfg(  &pTranAudio->compressor.playCfg,  &ptr,  &len  )  )  goto  errLabel;



	iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *ppBuf  =  ptr;
		 *puiBufSize  =  len;
	 }
	 return  iErr;

 }



 int  tmp_ntohTranAudio(  QY_CFGITEM_ntoh_U  *  pItem,  TRAN_audio  *  pTranAudio,  BOOL  *  pbProcessed  )
{
	 int						iErr		=	-1;
	 int						tmpLen;
	 char						buf[max(  sizeof(  QY_AUDIO_HEADER  ), sizeof(  AH_stream  )  )  +  1024];
	 BOOL						bProcessed  =  FALSE;
	 
	 //
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
	 

	 if  (  pTranAudio  )  {
		 //
		 bProcessed  =  TRUE;
		 //
		 switch  (  tmp_cfgId  )  {
				   //
			 case  CONST_qnmCfgId_uiTranNo_openAudioDev:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pTranAudio->uiTranNo_openAvDev  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_ucAudioCompressors:		//  2009/05/18
				 if  (  getFieldData_char(  pItem,  (  char  *  )&pTranAudio->compressor.common.ucCompressors  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiBytesRecorded_perBlockAlign:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pTranAudio->compressor.uiBytesRecorded_perBlockAlign  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_wf_compress:
				   tmpLen  =  sizeof(  buf  );
				   if  (  getFieldData_data(  pItem,  buf,  (  unsigned  int  *  )&tmpLen  )  )  goto  errLabel;
				   if  (  tmpLen  >  sizeof(  buf  )  )  goto  errLabel;
				   memset(  buf  +  tmpLen,  0,  sizeof(  buf  )  -  tmpLen  );
				   if  (  qyntohAudioHeader(  (  QY_AUDIO_HEADER  *  )buf  )  <  0  )  goto  errLabel;
				   memcpy(  &pTranAudio->ah_compress,  buf,  sizeof(  pTranAudio->ah_compress  )  );
				   break;
			 case  CONST_qnmCfgId_wf_decompress:	//  2009/04/27
				   tmpLen  =  sizeof(  buf  );
				   if  (  getFieldData_data(  pItem,  buf,  (  unsigned  int  *  )&tmpLen  )  )  goto  errLabel;
				   if  (  tmpLen  >  sizeof(  buf  )  )  goto  errLabel;
				   memset(  buf  +  tmpLen,  0,  sizeof(  buf  )  -  tmpLen  );
				   if  (  qyntohAudioHeader(  (  QY_AUDIO_HEADER  *  )buf  )  <  0  )  goto  errLabel;
				   memcpy(  &pTranAudio->ah_decompress,  buf,  sizeof(  pTranAudio->ah_decompress  )  );
				   break;
#if  0
			 case  CONST_qnmCfgId_vorbis_header0:  {				 	
				   tmpLen  =  sizeof(  buf  );
				   if  (  getFieldData_data(  pItem,  buf,  (  unsigned  int  *  )&tmpLen  )  )  goto  errLabel;
				   if  (  tmpLen  >  sizeof(  buf  )  )  goto  errLabel;
				   //
				   AH_stream  *  pAs  =  &pTranAudio->ah_stream;
				   if  (  tmpLen  >  sizeof(  pAs->buf  )  )  goto  errLabel;
				   memcpy(  pAs->buf,  buf,  tmpLen  );
				   pAs->mems[0].usLen  =  tmpLen;
				   //
				   pAs->mems[1].usLen  =  0;
				   pAs->mems[2].usLen  =  0;
				   }
				   break;
			 case  CONST_qnmCfgId_vorbis_header1:  {				 	
				   tmpLen  =  sizeof(  buf  );
				   if  (  getFieldData_data(  pItem,  buf,  (  unsigned  int  *  )&tmpLen  )  )  goto  errLabel;
				   if  (  tmpLen  >  sizeof(  buf  )  )  goto  errLabel;
				   //
				   AH_stream  *  pAs  =  &pTranAudio->ah_stream;
				   if  (  tmpLen  +  pAs->mems[0].usLen  >  sizeof(  pAs->buf  )  )  goto  errLabel;
				   memcpy(  pAs->buf  +  pAs->mems[0].usLen,  buf,  tmpLen  );
				   pAs->mems[1].usLen  =  tmpLen;
				   //
				   pAs->mems[2].usLen  =  0;
				   }
				   break;
			 case  CONST_qnmCfgId_vorbis_header2:  {				 	
				   tmpLen  =  sizeof(  buf  );
				   if  (  getFieldData_data(  pItem,  buf,  (  unsigned  int  *  )&tmpLen  )  )  {
					   showInfo_open0(  0,  0,  _T(  "tmp_ntohTranAudio failed, cfgId_header2, getFieldData_data failed"  )  );
					   goto  errLabel;
				   }
				   if  (  tmpLen  >  sizeof(  buf  )  )  goto  errLabel;
				   //
				   AH_stream  *  pAs  =  &pTranAudio->ah_stream;
				   if  (  tmpLen  +  pAs->mems[0].usLen  +  pAs->mems[1].usLen  >  sizeof(  pAs->buf  )  )  goto  errLabel;
				   memcpy(  pAs->buf  +  pAs->mems[0].usLen  +  pAs->mems[1].usLen,  buf,  tmpLen  );
				   pAs->mems[2].usLen  =  tmpLen;
				   //

				   #ifdef  __DEBUG__
						#if  10
							  int  iii;
							  for  (  iii  =  0;  iii  <  58;  iii  ++  )  {
								   TCHAR  tt[128];
								   _sntprintf(  tt,  mycountof(  tt  ),  _T(  "header[%d] %02x\n"  ),  iii,  (  unsigned  char  )pAs->buf[iii]  );
								   OutputDebugString(  tt  );
							  }
							  iii  =  iii;
						#endif
					#endif


				   }
				   break;
#endif

				   //

			 default:
				    bProcessed  =  FALSE;
					//
					if  (  tmp_ntohAudioPlayCfg(  pItem,  &pTranAudio->compressor.playCfg,  &bProcessed  )  )  goto  errLabel;
					if  (  bProcessed  )  {
						iErr  =  0;  goto  errLabel;
					}

					break;	 
		 }
	 }

	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 if  (  pbProcessed  )  *pbProcessed  =  bProcessed;
	 }
	 return  iErr;
}



 //////////////////
  int  tmp_htonTranConfCfg(  TRAN_conf_cfg  *  pConfCfg,  char  **  ppBuf,  unsigned  int  *  puiBufSize  )
{
	int					iErr	=	-1;
	int					i		=  0;
	char			*	ptr		=	*ppBuf;
	unsigned  int		len		=	*puiBufSize;

	if  (  pConfCfg  )  {
		//  2014/09/23
		TRAN_conf_cfg  *  pHead  =  pConfCfg;

		 //
		if  (  pHead->usMaxSpeakers  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMaxSpeakers,  (  void  *  )pHead->usMaxSpeakers,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }

		 if  (  pHead->conf.usMaxFps_toShareBmp_conf  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMaxFps_toShareBmp_conf,  (  void  *  )pHead->conf.usMaxFps_toShareBmp_conf,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 //  2014/08/15
		 if  (  pHead->conf.iWidth_pic_conf  )  {
			 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_iWidth_pic_conf,  (  void  *  )pHead->conf.iWidth_pic_conf,  0,  &ptr,  &len  )  )  goto  errLabel;		 
		 }
		 if  (  pHead->conf.iHeight_pic_conf  )  {
			 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_iHeight_pic_conf,  (  void  *  )pHead->conf.iHeight_pic_conf,  0,  &ptr,  &len  )  )  goto  errLabel;		 
	 
		 }

		 //
		 if (pHead->conf.conf_ucAudioCompressors) {
			 if (data2Stream(CONST_qyDataType_byte, CONST_qnmCfgId_conf_ucAudioCompressors, (void*)pHead->conf.conf_ucAudioCompressors, 0, &ptr, &len))  goto  errLabel;
		 }

		 //
		 if  (  pHead->conf.conf_iFourcc  )  {
			 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_conf_iFourcc,  (  void  *  )pHead->conf.conf_iFourcc,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if (pHead->conf.conf_bitrateInKbps_ul) {
			 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_conf_bitrateInKbps_ul, (void*)pHead->conf.conf_bitrateInKbps_ul, 0, &ptr, &len))goto  errLabel;
		 }

		 //
		 if (pHead->conf.conf_ucb100k) {
			 if (data2Stream(CONST_qyDataType_byte, CONST_qnmCfgId_conf_ucb100k, (void*)pHead->conf.conf_ucb100k, 0, &ptr, &len))goto  errLabel;
		 }
		 
		 //  2017/07/06
		 if  (  pHead->conf.confCtrl.ucbConfCtrl_starter  )  {
			 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbConfCtrl_starter,  (  void  *  )pHead->conf.confCtrl.ucbConfCtrl_starter,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }

		 //  2017/08/02
		 if  (  pHead->ucbVideoConference  )  {	
			 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbVideoConference,  (  void  *  )pHead->ucbVideoConference,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 //  2017/08/25
		 if  (  pHead->usConfType  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usConfType,  (  void  *  )pHead->usConfType,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }

		 //  2017/07/17
#if  0
		 if  (  pHead->ucbAvConsole  )  {
			 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbAvConsole,  (  void  *  )pHead->ucbAvConsole,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
#endif

		 //
		 if  (  pHead->idInfo_initiator.ui64Id  )  {
			 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_initiator,  &pHead->idInfo_initiator.ui64Id,  sizeof(  __int64  ),  &ptr,  &len  )  )  goto  errLabel;
		 }

		 //
#if 0
		 if (pHead->hgInfo.ui64MeetingId_hg) {
			 if (data2Stream(CONST_qyDataType_l64, CONST_qnmCfgId_meetingId_hg, &pHead->hgInfo.ui64MeetingId_hg, sizeof(pHead->hgInfo.ui64MeetingId_hg), &ptr, &len))  goto  errLabel;
		 }
		 if (pHead->hgInfo.iMeetingType_hg) {
			 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_meetingType_hg, (void*)pHead->hgInfo.iMeetingType_hg, 0, &ptr, &len))goto  errLabel;
		 }
#endif
		 //
		 tmp_htonConfHgInfo(&pHead->hgInfo, &ptr, &len);

		 //
	}
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *ppBuf  =  ptr;
		 *puiBufSize  =  len;
	 }
	 return  iErr;
 
}


 int  tmp_ntohTranConfCfg(  QY_CFGITEM_ntoh_U  *  pItem,  TRAN_conf_cfg  *  pConfCfg,  BOOL  *  pbProcessed  )
{
	 int						iErr		=	-1;
	 int						tmpLen;
	 char						buf[sizeof(  QY_VIDEO_HEADER  )  +  1024];
	 BOOL						bProcessed  =  FALSE;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 if  (  pConfCfg  )  {
		 TRAN_conf_cfg  *  pHead  =  pConfCfg;
		 //
		 bProcessed  =  TRUE;
		 //
		 switch  (  tmp_cfgId  )  {
				/*
				 case  CONST_qnmCfgId_usCntLimit_mems_from:			//  2009/05/30
					   if  (  getFieldData_short(  pItem,  (  short  *  )&pHead->usCntLimit_mems_from  )  )  goto  errLabel;
					   break;
					   */
				 case  CONST_qnmCfgId_usMaxSpeakers:	//  2009/05/31
					   if  (  getFieldData_short(  pItem,  (  short  *  )&pHead->usMaxSpeakers  )  )  goto  errLabel;
					   break;
				 case  CONST_qnmCfgId_usMaxFps_toShareBmp_conf:
					   if  (  getFieldData_short(  pItem,  (  short  *  )&pHead->conf.usMaxFps_toShareBmp_conf  )  )  goto  errLabel;
					   break;
				 case  CONST_qnmCfgId_iWidth_pic_conf:	//  2014/08/15
					   if  (  getFieldData_long(  pItem,  (  long  *  )&pHead->conf.iWidth_pic_conf  )  )  goto  errLabel;
					   break;
				 case  CONST_qnmCfgId_iHeight_pic_conf:	//  2014/08/15
					   if  (  getFieldData_long(  pItem,  (  long  *  )&pHead->conf.iHeight_pic_conf  )  )  goto  errLabel;
					   break;
					   //
				 case  CONST_qnmCfgId_conf_ucAudioCompressors:
					   if (getFieldData_char(pItem, (char*)&pHead->conf.conf_ucAudioCompressors))  goto  errLabel;
					   break;
					   //
				 case  CONST_qnmCfgId_conf_iFourcc:
					   if  (  getFieldData_long(  pItem,  (  long  *  )&pHead->conf.conf_iFourcc  )  )  goto  errLabel;
					   break;
					   //
				 case  CONST_qnmCfgId_conf_bitrateInKbps_ul:
					   if (getFieldData_long(pItem, (long*)&pHead->conf.conf_bitrateInKbps_ul))goto  errLabel;
					   break;
					   //
				 case  CONST_qnmCfgId_conf_ucb100k:
					 if (getFieldData_char(pItem, (char*) & pHead->conf.conf_ucb100k)) goto  errLabel;
					 break;
					   //
				 case  CONST_qnmCfgId_ucbConfCtrl_starter:
					   if  (  getFieldData_char(  pItem,  (  char  *  )&pHead->conf.confCtrl.ucbConfCtrl_starter  )  )  goto  errLabel;
					   break;
					   //
				 case  CONST_qnmCfgId_ucbVideoConference:  //  2017/08/02
					   if  (  getFieldData_char(  pItem,  (  char  *  )&pHead->ucbVideoConference  )  )  goto  errLabel;
					   break;
					   //
				 case  CONST_qnmCfgId_usConfType:	//  2017/08/25
					   if  (  getFieldData_short(  pItem,  (  short  *  )&pHead->usConfType  )  )  goto  errLabel;
					   break;
					   //
#if  0
				 case  CONST_qnmCfgId_ucbAvConsole:  //  2017/07/17
					   if  (  getFieldData_char(  pItem,  (  char  *  )&pHead->ucbAvConsole  )  )  goto  errLabel;
					   break;
#endif
					   //
				 case  CONST_qnmCfgId_idInfo_initiator:
					   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pHead->idInfo_initiator.ui64Id  )  )  goto  errLabel;
					   break;
					   //
#if 0
				 case  CONST_qnmCfgId_meetingId_hg:
					   if (getFieldData_l64(pItem, (__int64*)&pHead->hgInfo.ui64MeetingId_hg))  goto  errLabel;
					   break;
				 case  CONST_qnmCfgId_meetingType_hg:
					 if (getFieldData_long(pItem, (long*)&pHead->hgInfo.iMeetingType_hg))goto  errLabel;
					 break;
#endif
					   //
				 default:
					    bProcessed  =  FALSE;
						if  (  pHead->usMaxSpeakers  )  {
							//if  (  tmp_ntohAudioPlayCfg(  pItem,  &pConfCfg->audioPlayCfg,  &bProcessed  )  )  goto  errLabel;
						}
						tmp_ntohConfHgInfo(pItem, &pHead->hgInfo, &bProcessed);
						if  (  bProcessed  )  {
							iErr  =  0;  goto  errLabel;
						}

						break;
		 }
	 }
				   

	 iErr  =  0;
errLabel:
	 
	 if  (  !iErr  )  {
		if  (  pbProcessed  )  *pbProcessed  =  bProcessed;
	 }

	 return  iErr;
}



 ///////////////////


 //
 int  tmp_htonAvTranInfo(  AV_TRAN_INFO  *  pTranInfo,  char  **  ppBuf,  unsigned  int  *  puiBufSize  )  
 {
	int					iErr	=	-1;
	int					i		=  0;
	char			*	ptr		=	*ppBuf;
	unsigned  int		len		=	*puiBufSize;

	//
	AV_tranInfo_head  *  pHead  =  &pTranInfo->head;
	TRAN_audio  *  pTranAudio  =  &pTranInfo->audio;
	TRAN_video  *  pTranVideo  =  &pTranInfo->video;
	

	//
	if  (  pHead  )  {
		//  2014/09/23
		if  (  pHead->shClientVer  )  {
			if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_shVer,  (  void  *  )pHead->shClientVer,  0,  &ptr,  &len  )  )  goto  errLabel;
		}

	}

	 
	 //  2014/11/07
	 if  (  pTranVideo  )  {
		 if  (  pTranVideo->uiTranNo_openAvDev  )  {	 
			 if  (  tmp_htonTranVideo(  pTranVideo,  &ptr,  &len  )  )  goto  errLabel;
		 }
	 }

	 //  2014/11/07
	 if  (  pTranAudio  )  {
		 if  (  pTranAudio->uiTranNo_openAvDev  )  {
			 if  (  tmp_htonTranAudio(  pTranAudio,  &ptr,  &len  )  )  goto  errLabel;
		 }
	 }

	 //  2015/03/12
	 if  (  pTranInfo->taskAvProps.v.ucAvFlg  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucAvFlg,  (  void  *  )pTranInfo->taskAvProps.v.ucAvFlg,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 
	 //
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *ppBuf  =  ptr;
		 *puiBufSize  =  len;
	 }
	 return  iErr;
 
}

//
int  tmp_ntohAvTranInfo(  QY_CFGITEM_ntoh_U  *  pItem,  AV_TRAN_INFO  *  pTranInfo,  BOOL  *  pbProcessed  )
{
	 int						iErr		=	-1;
	 int						tmpLen;
	 char						buf[sizeof(  QY_VIDEO_HEADER  )  +  1024];
	 BOOL  bProcessed  =  FALSE;

	 //	 
	 AV_tranInfo_head  *  pHead  =  &pTranInfo->head;
	 TRAN_audio  *  pTranAudio  =  &pTranInfo->audio;
	 TRAN_video  *  pTranVideo  =  &pTranInfo->video;


	 //
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 if  (  pHead  )  {
		 switch  (  tmp_cfgId  )  {
				 case  CONST_qnmCfgId_shVer:	//  2014/09/23
					   if  (  getFieldData_short(  pItem,  (  short  *  )&pHead->shClientVer  )  )  goto  errLabel;
					   break;
				 default:
						break;
		 }
	 }
				   
	 //
	 if  (  pTranVideo  )  {
		 //
		 bProcessed  =  FALSE;
		 if  (  tmp_ntohTranVideo(  pItem,  pTranVideo,  &bProcessed  )  )  {
			 goto  errLabel;
		 }
		 if  (  bProcessed  )  {
			 iErr  =  0;  goto  errLabel;
		 }
	 }


	 if  (  pTranAudio  )  {
		 //
		 bProcessed  =  FALSE;
		 if  (  tmp_ntohTranAudio(  pItem,  pTranAudio,  &bProcessed  )  )  {
			 goto  errLabel;
		 }
		 if  (  bProcessed  )  {
			 iErr  =  0;  goto  errLabel;
		 }
	 }

	 //  2015/03/12
	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_ucAvFlg:
				   if  (  getFieldData_char(  pItem,  (  char  *  )&pTranInfo->taskAvProps.v.ucAvFlg  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }


	 iErr  =  0;
errLabel:

	 if  (  pbProcessed  )  *pbProcessed  =  bProcessed;

	 return  iErr;
}


 ////////////////////////////

 int  tmp_htonAvStream(  AV_stream  *  pObj,  char  **  ppBuf,  unsigned  int  *  puiBufSize  )  
 {
	int					iErr	=	-1;
	int					i		=  0;
	char			*	ptr		=	*ppBuf;
	unsigned  int		len		=	*puiBufSize;

	//
	if  (  !pObj->idInfo.ui64Id
		&&  !pObj->obj.resObj.uiObjType  
		&&  !pObj->obj.tranInfo.audio.uiTranNo_openAvDev  
		&&  !pObj->obj.tranInfo.video.uiTranNo_openAvDev  )
	{
		return  0;
	}

	//
	if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_avStream,  0,  &ptr,  &len  )  )  goto  errLabel;

	//
	if  (  pObj->idInfo.ui64Id  )  {
		if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pObj->idInfo.ui64Id,  sizeof(  pObj->idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;		
	}

	//	
	if  (  pObj->obj.resObj.uiObjType  )  {		
		if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiObjType,  (  void  *  )pObj->obj.resObj.uiObjType,  0,  &ptr,  &len  )  )  goto  errLabel;
	}	
	if  (  pObj->obj.resObj.usIndex_obj  )  {
		if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_index,  (  void  *  )pObj->obj.resObj.usIndex_obj,  0,  &ptr,  &len  )  )  goto  errLabel;
	}

	//
	if  (  tmp_htonAvTranInfo(  &pObj->obj.tranInfo,  &ptr,  &len  )  )  goto  errLabel;

	//
	if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	
	 //
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *ppBuf  =  ptr;
		 *puiBufSize  =  len;
	 }
	 return  iErr;
 
}

//
int  tmp_ntohAvStream(  QY_CFGITEM_ntoh_U  *  pItem,  AV_stream  *  pObj,  BOOL  *  pbProcessed  )
{
	 int						iErr		=	-1;
	 int						tmpLen;
	 //char						buf[sizeof(  QY_VIDEO_HEADER  )  +  1024];
	 BOOL  bProcessed  =  FALSE;

	 //
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 //
	 bProcessed  =  true;
	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_messengerId:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pObj->idInfo.ui64Id  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiObjType:
							     long  lVal;
							     if  (  getFieldData_long(  pItem,  (  long  *  )&lVal  )  )  goto  errLabel;				   
								 //
								 pObj->obj.resObj.uiObjType  =  lVal;
							     break;						   
			 case  CONST_qnmCfgId_index:
							     short  sVal;
								 if  (  getFieldData_short(  pItem,  (  short  *  )&sVal  )  )  goto  errLabel;				   
								 //
								 pObj->obj.resObj.usIndex_obj  =  sVal;								 
							     break;
			 default:
				    bProcessed  =  false;
					if  (  tmp_ntohAvTranInfo(  pItem,  &pObj->obj.tranInfo,  &bProcessed  )  )  goto  errLabel;
					//
					if  (  bProcessed  )  {
						iErr  =  0;  goto  errLabel;
					}
					break;
	 }

	 iErr  =  0;
errLabel:

	 if  (  pbProcessed  )  *pbProcessed  =  bProcessed;

	 return  iErr;
}






/////////////////////////////////////////


//
 int  transferAvInfo2Stream(  unsigned  int  uiStreamId,  TRANSFER_AV_INFO  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->ucbResp  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbResp,  (  void  *  )pReq->ucbResp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  pReq->uiTaskType  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTaskType,  (  void  *  )pReq->uiTaskType,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //
	 if (pReq->shareDevice_grp_index) {
		 if (data2Stream(CONST_qyDataType_l32, CONST_qnmCfgId_shareDevice_grp_index, (void*)pReq->shareDevice_grp_index, 0, &ptr, &len))  goto  errLabel;
	 }


	 //  2014/11/07
	 if  (  tmp_htonTranConfCfg(  &pReq->confCfg,  &ptr,  &len  )  )  goto  errLabel;

	 //
	 AV_stream  tmpAs;

	 //
	 //if  (  tmp_htonAvTranInfo(  &pReq->tranInfo,  &ptr,  &len  )  )  goto  errLabel;
	 memset(  &tmpAs,  0,  sizeof(  tmpAs  )  );
	 tmpAs.obj  =  pReq->ass;
	 if  (  tmp_htonAvStream(  &tmpAs,  &ptr,  &len  )  )  goto  errLabel;

	 //  2014/11/07
	 for  (  i  =  0;  i  <  2;  i  ++  )  {	 
		  MOSAIC_TRAN_INFO  *  pMosaic  =  NULL;
		  switch  (  i  )  {
				  case  0:
					    pMosaic  =  &pReq->confMosaicTranInfo_video;
						break;
				  case  1:
					    pMosaic  =  &pReq->confMosaicTranInfo_resource;
						break;
				  default:
						 break;
		  }
		  if  (  !pMosaic  )  break;
		  //
		 if  (  pMosaic->resObj.uiObjType  &&  pMosaic->video.uiTranNo_openAvDev  )  {

#if  0
			 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_struct,  0,  &ptr,  &len  )  )  goto  errLabel;

			 //
			 if  (  pMosaic->resObj.uiObjType  )  {
				 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiObjType,  (  void  *  )pMosaic->resObj.uiObjType,  0,  &ptr,  &len  )  )  goto  errLabel;
			 }
			 if  (  pMosaic->resObj.usIndex_obj  )  {
				 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_index,  (  void  *  )pMosaic->resObj.usIndex_obj,  0,  &ptr,  &len  )  )  goto  errLabel;
			 }
			 //
			 if  (  tmp_htonTranVideo(  &pMosaic->video,  &ptr,  &len  )  )  goto  errLabel;

			 //
			 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
#endif
#if  10
			 //
			 memset(  &tmpAs,  0,  sizeof(  tmpAs  )  );
			 tmpAs.obj.resObj  =  pMosaic->resObj;
			 tmpAs.obj.tranInfo.video  =  pMosaic->video;
			 //
			 if  (  tmp_htonAvStream(  &tmpAs,  &ptr,  &len  )  )  {
				 goto  errLabel;
			 }
#endif
		 }
	 }
	 
	 //  2009/09/07
#if  0
	 if  (  pReq->viewDynBmp.resObj.uiObjType  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiObjType,  (  void  *  )pReq->viewDynBmp.resObj.uiObjType,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->viewDynBmp.resObj.usIndex_obj  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_index,  (  void  *  )pReq->viewDynBmp.resObj.usIndex_obj,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->viewDynBmp.resObj.usHelp_subIndex  )  {	//  2016/07/24
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_help_subIndex,  (  void  *  )pReq->viewDynBmp.resObj.usHelp_subIndex,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
#endif
	 //  2014/08/04
	 if  (  pReq->viewDynBmp.ucbSaveVideo  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbSaveVideo,  (  void  *  )pReq->viewDynBmp.ucbSaveVideo,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }


	 //  2009/10/18
	 if  (  pReq->idInfo_logicalPeer.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_logicalPeer,  (  void  *  )&pReq->idInfo_logicalPeer.ui64Id,  sizeof(  pReq->idInfo_logicalPeer.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //  2014/11/22
	 if  (  pReq->uiTranNo_avTask_starter  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_avTask_starter,  (  void  *  )pReq->uiTranNo_avTask_starter,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }


	 //  2014/11/20
#if  0
	 if  (  pReq->proxiedTranInfo.idInfo.ui64Id  &&  pReq->proxiedTranInfo.uiObjType  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_struct,  0,  &ptr,  &len  )  )  goto  errLabel;

		 PROXIED_TRAN_INFO  *  pProxied  =  &pReq->proxiedTranInfo;

		 if  (  pProxied->idInfo.ui64Id  )  {		
			 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pProxied->idInfo.ui64Id,  sizeof(  pProxied->idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;		
		 }

		 //
		 if  (  pProxied->uiObjType  )  {
			 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiObjType,  (  void  *  )pProxied->uiObjType,  0,  &ptr,  &len  )  )  goto  errLabel;			 
		 }			
		 //		
		 if  (  tmp_htonAvTranInfo(  &pProxied->ti,  &ptr,  &len  )  )  goto  errLabel;
		 
		 //		
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
#endif

	 //  qyShowInfo1(  CONST_qyShowType_debug,  (  ""  ),  _T(  ""  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    transferAvInfo2stream: uiTranNo_openAvDev %d"  ),  pReq->uiTranNo_openAvDev  );

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 //
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
#ifdef  __DEBUG__
		if  (  iErr  )  {
			int  i;
			i  =  0;
		}
#endif
	 return  iErr;	 

}


 int  tmpHandler_stream2TransferAvInfo(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 TRANSFER_AV_INFO		*	pContent	=	(  TRANSFER_AV_INFO  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  int						tmpLen;
	 //  char						buf[sizeof(  QY_VIDEO_HEADER  )  +  1024];
	 
	 if  (  !pContent  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 //
	 int  uiStreamId_1; uiStreamId_1 = 0;
	 if  (  pCtx->index_streamId  >  0  )  {
		 uiStreamId_1  =  pCtx->uiStreamIds[1];
	 }

	 //
#if  0
	 if  (  uiStreamId_1  ==  CONST_imCommType_confKey  )  {

		 //		
		 if  (  tmpHandler_stream2VideoConferenceStatus(  pCtx,  p0,  &pContent->videoConferenceStatus,  uiStreamId,  pItem  )  )  {		
			 goto  errLabel;			
		 }				   

		 int  ii  =  0;
		 iErr  =  0;  goto  errLabel;
	 }
#endif


	 //
	 switch  (  uiStreamId  )  {
			 case  CONST_imCommType_transferAvInfo:
				   switch  (  tmp_cfgId  )  {
					       case  CONST_qnmCfgId_start:
							     pContent->uiType  =  uiStreamId;				   
								 break;
						   case  CONST_qnmCfgId_null:  {
							     int  ii  =  0;
								 }
							     break;
						   case  CONST_qnmCfgId_ucbResp:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->ucbResp  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_uiTaskType:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTaskType  )  )  goto  errLabel;				   
								 break;
						   case  CONST_qnmCfgId_shareDevice_grp_index:
							     if (getFieldData_long(pItem, (long*)&pContent->shareDevice_grp_index))  goto  errLabel;
							     break;
#if  0
						   case  CONST_qnmCfgId_uiObjType:				   
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->viewDynBmp.resObj.uiObjType  )  )  goto  errLabel;				   
								 break;			 
						   case  CONST_qnmCfgId_index:				   
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->viewDynBmp.resObj.usIndex_obj  )  )  goto  errLabel;				   
								 break;			
						   case  CONST_qnmCfgId_help_subIndex:  //  2016/07/24
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->viewDynBmp.resObj.usHelp_subIndex  )  )  goto  errLabel;
							     break;
#endif
						   case  CONST_qnmCfgId_ucbSaveVideo:	//  2014/08/04				   
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->viewDynBmp.ucbSaveVideo  )  )  goto  errLabel;				   
								 break;				   
								 //			 
						   case  CONST_qnmCfgId_idInfo_logicalPeer:				   
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->idInfo_logicalPeer.ui64Id  )  )  goto  errLabel;				   
								 break;		
								 //
						   case  CONST_qnmCfgId_uiTranNo_avTask_starter:  //  2014/11/22
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTranNo_avTask_starter  )  )  goto  errLabel;
							     break;
								 //
						   default:
								  //				    
							      BOOL  bProcessed  =  FALSE;					
								  //					
								  if  (  tmp_ntohTranConfCfg(  pItem,  &pContent->confCfg,  &bProcessed  )  )  {
									  goto  errLabel;					
								  }
								  if  (  bProcessed  )  break;					
								  //				    
#if  0
								  if  (  tmp_ntohAvTranInfo(  pItem,  &pContent->tranInfo,  &bProcessed  )  )  {
									  goto  errLabel;					
								  }
								  if  (  bProcessed  )  break;
#endif
								  break;	 
				   }	 
				   break;
#if  0
			 case  CONST_imCommType_struct:		
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
							     memset(  &pContent->tmp_internal.streamInfo,  0,  sizeof(  pContent->tmp_internal.streamInfo  )  );
							     break;
						   case  CONST_qnmCfgId_messengerId:  //  2014/11/20
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->tmp_internal.streamInfo.idInfo.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_uiObjType:
							     long  lVal;
							     if  (  getFieldData_long(  pItem,  (  long  *  )&lVal  )  )  goto  errLabel;				   
								 //
								 pContent->tmp_internal.streamInfo.uiObjType  =  lVal;
							     break;
						   case  CONST_qnmCfgId_index:
							     short  sVal;
								 if  (  getFieldData_short(  pItem,  (  short  *  )&sVal  )  )  goto  errLabel;				   
								 //
								 pContent->tmp_internal.streamInfo.usIndex_obj  =  sVal;								 
							     break;
						   case  CONST_qnmCfgId_null:
								#if  0
							     if  (  pContent->tmp_internal.streamInfo.uiObjType  ==  CONST_objType_cosult_mem  )  {
									 //
									 if  (  pContent->tmp_internal.usCnt_consult_mems  <  mycountof(  pContent->confCfg.info_consult_yz.mems  )  )  {										
										 CONSULT_mem  *  pConsultMem  =  NULL;
										 //									 
										 pConsultMem  =  &pContent->confCfg.info_consult_yz.mems[pContent->tmp_internal.usCnt_consult_mems];
										 //										
										 pConsultMem->idInfo.ui64Id  =  pContent->tmp_internal.streamInfo.idInfo.ui64Id;
										 //
									 }									 
									 //
									 pContent->tmp_internal.usCnt_consult_mems  ++  ;
								 }
								#endif
							     break;
						   default:  {
							         MOSAIC_TRAN_INFO  *  pMosaic  =  NULL;;
									 PROXIED_TRAN_INFO  *  pProxied  =  NULL;
									 //CONSULT_mem  *  pConsultMem  =  NULL;
									 //
									 if  (  pContent->tmp_internal.streamInfo.uiObjType  ==  CONST_objType_mosaicStream_video  )  {
										 if  (  pContent->tmp_internal.streamInfo.usIndex_obj  ==  CONST_usIndex_photomosaic_video  )  {										 
											 pMosaic  =  &pContent->confMosaicTranInfo_video;										  										
										 }
										 }									 
									 else  if  (  pContent->tmp_internal.streamInfo.uiObjType  ==  CONST_objType_mosaicStream_resource  )  {
											   if  (  pContent->tmp_internal.streamInfo.usIndex_obj  ==  CONST_usIndex_photomosaic_resource  )  {
												pMosaic  =  &pContent->confMosaicTranInfo_resource;
												}
									 }
									 else  if  (  pContent->tmp_internal.streamInfo.uiObjType  ==  CONST_objType_proxiedStream_video  )  {
											   pProxied  =  &pContent->proxiedTranInfo;
									 }
#if  0
									 else  if  (  pContent->tmp_internal.streamInfo.uiObjType  ==  CONST_objType_cosult_mem  )  {
#if  0
											   if  (  pContent->tmp_internal.usCnt_consult_mems  <  mycountof(  pContent->confCfg.info_consult_yz.mems  )  )  {
												   pConsultMem  =  &pContent->confCfg.info_consult_yz.mems[pContent->tmp_internal.usCnt_consult_mems];
											   }
#endif
									 }
#endif
									 //
									 if  (  !pMosaic  &&  !pProxied  
										 //&&  !pConsultMem  
										 )  
									 {
										 break;									  
									 }									 
									 //
									 if  (  pMosaic  )  {
										 if  (  !pMosaic->resObj.uiObjType  )  pMosaic->resObj.uiObjType  =  pContent->tmp_internal.streamInfo.uiObjType;									 
										 if  (  !pMosaic->resObj.usIndex_obj  )  pMosaic->resObj.usIndex_obj  =  pContent->tmp_internal.streamInfo.usIndex_obj;
										 if  (  pMosaic->resObj.uiObjType  !=  pContent->tmp_internal.streamInfo.uiObjType  
											 ||  pMosaic->resObj.usIndex_obj  !=  pContent->tmp_internal.streamInfo.usIndex_obj  )									 
										 {
											  qyShowInfo1(  CONST_qyShowType_qwmComm,  NULL,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "ntohMosaic failed"  )  );
											  goto  errLabel;									  
										 }
									 
										 //  									 
										 BOOL  bProcessed  =  FALSE;									 
										 if  (  tmp_ntohTranVideo(  pItem,  &pMosaic->video,  &bProcessed  )  )  goto  errLabel;
										 if  (  bProcessed  )  {
											  iErr  =  0;  goto  errLabel; 									  
										 }												
									 }
									 //
									 if  (  pProxied  )  {
										 if  (  !pProxied->idInfo.ui64Id  )  pProxied->idInfo.ui64Id  =  pContent->tmp_internal.streamInfo.idInfo.ui64Id;
										 if  (  !pProxied->uiObjType  )  pProxied->uiObjType  =  pContent->tmp_internal.streamInfo.uiObjType;
										 if  (  pProxied->idInfo.ui64Id  !=  pContent->tmp_internal.streamInfo.idInfo.ui64Id  
											 ||  pProxied->uiObjType  !=  pContent->tmp_internal.streamInfo.uiObjType  )
										 {
											  qyShowInfo1(  CONST_qyShowType_qwmComm,  NULL,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "ntohProxied failed"  )  );
											  goto  errLabel;									  
										 }
										 //  									 
										 BOOL  bProcessed  =  FALSE;									 
										 if  (  tmp_ntohAvTranInfo(  pItem,  &pProxied->ti,  &bProcessed  )  )  goto  errLabel;
										 if  (  bProcessed  )  {
											  iErr  =  0;  goto  errLabel; 									  
										 }												
									 }
									 //
#if  0
									 if  (  pConsultMem  )  {
										 switch  (  tmp_cfgId  )  {
												 case  CONST_qnmCfgId_ksName:
													   getFieldData_wStr(  pItem,  pConsultMem->ksName,  mycountof(  pConsultMem->ksName  )  );
													   break;
												 case  CONST_qnmCfgId_ysName:
													   getFieldData_wStr(  pItem,  pConsultMem->ysName,  mycountof(  pConsultMem->ysName  )  );													   
													   break;
												 default:
														break;
										 }
									 }
#endif

							      //
								  }
								  break;
							     
				   }
				   break;				 
#endif
			 case  CONST_imCommType_avStream:
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
								 memset(  &pContent->tmp_internal.tmpAs,  0,  sizeof(  pContent->tmp_internal.tmpAs  )  );
								 break;				   
						   case  CONST_qnmCfgId_null:
							     switch  (  pContent->tmp_internal.tmpAs.obj.resObj.uiObjType  )  {
										 case  CONST_objType_mosaicStream_video:
											   pContent->confMosaicTranInfo_video.resObj  =  pContent->tmp_internal.tmpAs.obj.resObj;
											   pContent->confMosaicTranInfo_video.video  =  pContent->tmp_internal.tmpAs.obj.tranInfo.video;
											   break;
										 case  CONST_objType_mosaicStream_resource:
											   pContent->confMosaicTranInfo_resource.resObj  =  pContent->tmp_internal.tmpAs.obj.resObj;
											   pContent->confMosaicTranInfo_resource.video  =  pContent->tmp_internal.tmpAs.obj.tranInfo.video;
											   break;
										 default:
											    pContent->ass  =  pContent->tmp_internal.tmpAs.obj;
												break;
								 }								 
							     break;
						   default:
							      BOOL  bProcessed  =  false;
							      if  (  tmp_ntohAvStream(  pItem,  &pContent->tmp_internal.tmpAs,  &bProcessed  )  )  {
									  goto  errLabel;
								  }
								  if  (  bProcessed  )  {
									  iErr  =  0;  goto  errLabel;
								  }							      
								  break;						   
				   }
				   break;
			 default:
					break;
	 }



	 iErr  =  0;
errLabel:

#ifdef  __DEBUG__
	    if  (  iErr  )  {
			int  i;  
			i  =  0;
		}
#endif
	 return  iErr;
}



 //  2011/12/24
 int  transferAvReplyInfo2Stream(  unsigned  int  uiStreamId,  TRANSFER_AV_replyInfo  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->usOp  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usOp,  (  void  *  )pReq->usOp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->tStartTime_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tStartTime_org,  &pReq->tStartTime_org,  sizeof(  pReq->tStartTime_org  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->uiTranNo_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_org,  (  void  *  )pReq->uiTranNo_org,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 //if  (  tmp_htonAvTranInfo(  &pReq->tranInfo,  &ptr,  &len  )  )  goto  errLabel;
	 AV_stream  tmpAs;
	 memset(  &tmpAs,  0,  sizeof(  tmpAs  )  );
	 tmpAs.obj.tranInfo  =  pReq->tranInfo;
	 if  (  tmp_htonAvStream(  &tmpAs,  &ptr,  &len  )  )  {
		 goto  errLabel;
	 }

	 //  2014/09/04
	 if  (  pReq->viewDynBmpReply.ucbSaveVideo  )  {	//  2014/09/07
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbSaveVideo,  (  void  *  )pReq->viewDynBmpReply.ucbSaveVideo,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2TransferAvReplyInfo(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 TRANSFER_AV_replyInfo	*	pContent	=	(  TRANSFER_AV_replyInfo  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 int						tmpLen;
	 char						buf[sizeof(  QY_VIDEO_HEADER  )  +  1024];
	 BOOL	bProcessed  =  FALSE;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 //if  (  uiStreamId  !=  CONST_imCommType_transferAvReplyInfo  )  goto  errLabel;

	 //
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 //
	 switch  (  uiStreamId  )  {
			 case  CONST_imCommType_transferAvReplyInfo:
				 switch  (  tmp_cfgId  )  {
						 case  CONST_qnmCfgId_start:
							   pContent->uiType  =  uiStreamId;
							   break;
						 case  CONST_qnmCfgId_usOp:
							   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usOp  )  )  goto  errLabel;
							   break;
						 case  CONST_qnmCfgId_tStartTime_org:
							   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->tStartTime_org  )  )  goto  errLabel;
							   break;
						 case  CONST_qnmCfgId_uiTranNo_org:
							   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTranNo_org  )  )  goto  errLabel;
							   break;

							   //  2014/09/04
						 case  CONST_qnmCfgId_ucbSaveVideo:	//  2014/09/07
							   if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->viewDynBmpReply.ucbSaveVideo  )  )  goto  errLabel;  
							   break;

						 default:
								/*
							    if  (  tmp_ntohAvTranInfo(  pItem,  &pContent->tranInfo,  &bProcessed  )  )  goto  errLabel;
								if  (  bProcessed  )  {
									iErr  =  0;  goto  errLabel;
								}
								*/
								break;
				 }
				 break;
			 case  CONST_imCommType_avStream:
				   switch (  tmp_cfgId  )  {
						  case  CONST_qnmCfgId_start:
							    memset(  &pContent->tmp_internal.tmpAs,  0,  sizeof(  pContent->tmp_internal.tmpAs  )  );
								break;
						  case  CONST_qnmCfgId_null:
							    pContent->tranInfo  =  pContent->tmp_internal.tmpAs.obj.tranInfo;
							    break;
						  default:
							     if  (  tmp_ntohAvStream(  pItem,  &pContent->tmp_internal.tmpAs,  &bProcessed  )  )  goto  errLabel;				   
								 if  (  bProcessed  )  {					   
									 iErr  =  0;  goto  errLabel;				   
								 }				   
								 break;
				   }
				   break;
			 default:
					break;
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}






////////////////////////

 int  qyhtonRouteTalkData(  MSG_ROUTE  *  pAddr,  char  *  pContentParam,  unsigned  int  lenInBytes_content,  BOOL  bNeedContentConvrted,  unsigned  char  ucFlg,  char  *  buf,  unsigned  int  *puiBufSize,  TCHAR  *  tHintBuf_showInfo,  unsigned  int  uiCnt_tHintBuf_showInfo  ) 
{
	int							iErr									=	-1;
	IM_CONTENTU			*		pContent								=	(  IM_CONTENTU  *  )pContentParam;
	int							lenInBytes;
	char				*		ptr;
	//  IM_L_STREAM			*		pStream									=	NULL;
	unsigned  int				uiBufSize;
	int							lenInBytes_addr							=	0;
	//  long						tmp_l;


	if  (  !buf  ||  !puiBufSize  )  return  -1;
	uiBufSize  =  *puiBufSize;

	if  (  isUcFlgRouteTalkData(  ucFlg  )  )  {

		lenInBytes_addr  =  uiBufSize;
		if  (  msgRoute2Stream(  CONST_imCommType_msgRoute,  pAddr,  buf,  (  unsigned  int  *  )&lenInBytes_addr  )  )  goto  errLabel;
		}
#if  0
	else  if  (  isUcFlgTalkData(  ucFlg  )  )  {		//  仅用来talkData
		  if  (  !pAddr  ||  uiBufSize  <  sizeof(  MSG_SIMPLE_ROUTE  )  )  goto  errLabel;
		  MSG_SIMPLE_ROUTE		talkDataAddr;
		  MSG_SIMPLE_ROUTE  *  pTalkDataAddr	=	&talkDataAddr;
		  //  pTalkDataAddr  =  (  MSG_SIMPLE_ROUTE  *  )buf;
		  pTalkDataAddr->idInfo_from.ui64Id  =  pAddr->idInfo_from.ui64Id;
		  pTalkDataAddr->idInfo_to.ui64Id  =  pAddr->idInfo_to.ui64Id;
		  //
		  MACRO_htonl64(  pTalkDataAddr->idInfo_from.ui64Id  );
		  MACRO_htonl64(  pTalkDataAddr->idInfo_to.ui64Id  );
		  //
		  memcpy(  buf,  pTalkDataAddr,  sizeof(  MSG_SIMPLE_ROUTE  )  );
		  //
		  lenInBytes_addr  =  sizeof(  MSG_SIMPLE_ROUTE  );		  
	}
#endif 
	
	//
	ptr  =  buf  +  lenInBytes_addr;
	
	//  要求不转换的		  
	//
	if  (  !bNeedContentConvrted  )  {										
	
		if  (  lenInBytes_content  >  uiBufSize  -  lenInBytes_addr  )  {
			traceLogA(  (char*)"lenInBytes_content is too large"  );  
			goto  errLabel;
		}
		if  (  !pContent  )  lenInBytes  =  lenInBytes_addr;
		else  {
			  memcpy(  ptr,  pContent,  lenInBytes_content  );
			  lenInBytes  =  lenInBytes_addr  +  lenInBytes_content;			
		}		
			
		iErr  =  0;  goto  errLabel;
	}

	if  (  !pContent  )  goto  errLabel;
	
	switch  (  pContent->uiType  )  {
			case  0:  {
				  unsigned  int  uiType  =  pContent->uiType;
				  MACRO_htonl(  uiType  );
				  lenInBytes  =  sizeof(  uiType  );
				  if  (  uiBufSize  -  lenInBytes_addr  <  lenInBytes  )  goto  errLabel;
				  memcpy(  ptr,  &uiType,  lenInBytes  );
				  lenInBytes  +=  lenInBytes_addr;
				  iErr  =  0;  goto  errLabel;
				  }
				  break;
			case  CONST_imCommType_simpleResp:  {
				  IM_SIMPLE_RESP	simpleResp;
				  memcpy(  &simpleResp,  &pContent->simpleResp,  sizeof(  simpleResp  )  );
				  if  (  (  lenInBytes  =  qyhtonImSimpleResp(  0,  &simpleResp  )  )  <  0  )  goto  errLabel; 
				  if  (  uiBufSize  -  lenInBytes_addr  <  lenInBytes  )  goto  errLabel;
				  memcpy(  ptr,  &simpleResp,  lenInBytes  );
				  lenInBytes  +=  lenInBytes_addr;
				  iErr  =  0;  goto  errLabel;
				  }
				  break;
			default:
					break;
	}

	//
	if (10) {  //  2025/10/24
		switch (pContent->uiType) {
		case  CONST_imCommType_transferAudioData:
			lenInBytes = uiBufSize - lenInBytes_addr;
			//
			//
			{
				int  tmpLen = pContent->transferAudioData.uiLen;
				//
				if (transferAudioData2Stream(pContent->uiType, &pContent->transferAudioData, ptr, (unsigned  int*)&lenInBytes))  goto  errLabel;
				//
#ifdef  __DEBUG__
				//
				if (0) {
					int wrappingLen = lenInBytes - tmpLen;
					//traceLog((TCHAR*)_T("tad.len %d, n.lenInBytes %d, wrappingLen %d, lenInBytes_addr %d"), tmpLen, lenInBytes, wrappingLen, lenInBytes_addr);
					//
					traceLog((TCHAR*)_T("hton: tad.len %d, cnt %d, n.lenInBytes %d, wrappingLen %d, lenInBytes_addr %d. l3494"), tmpLen, (int)pContent->transferAudioData.usCnt, lenInBytes, wrappingLen, lenInBytes_addr);

				}
#endif 
			}
			lenInBytes += lenInBytes_addr;
			//
			iErr = 0;  goto  errLabel;

			//
			break;

#if  10

		case  CONST_imCommType_transferVideoData:
			lenInBytes = uiBufSize - lenInBytes_addr;
			//
			//
			{
				int  tmpLen = pContent->transferVideoData.uiLen;
				//
				if (transferVideoData2Stream(pContent->uiType, &pContent->transferVideoData, ptr, (unsigned  int*)&lenInBytes))  goto  errLabel;
				//
#ifdef  __DEBUG__
				//
				if (0) {
					int wrappingLen = lenInBytes - tmpLen;
					//traceLog((TCHAR*)_T("tad.len %d, n.lenInBytes %d, wrappingLen %d, lenInBytes_addr %d"), tmpLen, lenInBytes, wrappingLen, lenInBytes_addr);
					//
					traceLog((TCHAR*)_T("hton: tvd.len %d, cnt %d, n.lenInBytes %d, wrappingLen %d, lenInBytes_addr %d. l3494"), tmpLen, (int)pContent->transferVideoData.usCnt, lenInBytes, wrappingLen, lenInBytes_addr);

				}
#endif 
			}
			lenInBytes += lenInBytes_addr;
			//
			iErr = 0;  goto  errLabel;

			//
			break;
#endif 


		default:
			break;
		}
	}



	//
	IM_L_STREAM_nh				stream_hton;
	char* stream_pBuf;stream_pBuf = NULL;
	//  pStream  =  (  IM_L_STREAM  *  )ptr;

	if  (  uiBufSize  -  lenInBytes_addr  <  offsetof(  IM_L_STREAM,  buf  )  )  {
		//
		traceLogA(  (char*)"qyhtonRouteTalkData failed: buf is too small"  );  
		//
		goto  errLabel;	//  怕空间不够了
	}
	memset(  &stream_hton,  0,  offsetof(  IM_L_STREAM,  buf  )  );
	stream_hton.uiType  =  CONST_imCommType_lStream;
	stream_hton.uiContentType  =  pContent->uiType;	
	stream_pBuf  =  ptr  +  offsetof( IM_L_STREAM,  buf  );
	lenInBytes  =  uiBufSize  -  lenInBytes_addr;		//  sizeof(  pStream->buf  );				
	switch  (  pContent->uiType  )  {
			case  CONST_imCommType_htmlContent:
				  if  (  imHtmlContent2Stream(  pContent->uiType,  &pContent->html,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferFileReq:
				  if  (  transferFileReq2Stream(  pContent->uiType,  &pContent->transferFileReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_taskProcReq:
				  if  (  taskProcReq2Stream(  pContent->uiType,  &pContent->taskProcReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_taskProcResp:
				  if  (  taskProcResp2Stream(  pContent->uiType,  &pContent->taskProcResp,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferFileReplyReq:
				  if  (  transferFileReplyReq2Stream(  pContent->uiType,  &pContent->transferFileReplyReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferFileDataReq:
				  if  (  transferFileDataReq2Stream(  pContent->uiType,  &pContent->transferFileDataReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferFileDataResp:
				  if  (  transferFileDataResp2Stream(  pContent->uiType,  &pContent->transferFileDataResp,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferFileEndReq:
				  if  (  transferFileEndReq2Stream(  pContent->uiType,  &pContent->transferFileEndReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferFileEndResp:
				  if  (  transferFileEndResp2Stream(  pContent->uiType,  &pContent->transferFileEndResp,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_rtcCallReq:
				  if  (  rtcCallReq2Stream(  pContent->uiType,  &pContent->rtcCallReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferAvInfo:
				  if  (  transferAvInfo2Stream(  pContent->uiType,  &pContent->transferAvInfo,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferAvReplyInfo:
				  if  (  transferAvReplyInfo2Stream(  pContent->uiType,  &pContent->transferAvReplyInfo,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferVideoData:
			{
				int  tmpLen = pContent->transferVideoData.uiLen;
				//
				if (transferVideoData2Stream(pContent->uiType, &pContent->transferVideoData, stream_pBuf, (unsigned  int*)&lenInBytes))  goto  errLabel;
				//
#ifdef  __DEBUG__
				//
				if (10) {
					int wrappingLen = lenInBytes - tmpLen;
					traceLog((TCHAR*)_T("hton: tvd.len %d, n.lenInBytes %d, wrappingLen %d, lenInBytes_addr %d. l3578"), tmpLen, lenInBytes, wrappingLen, lenInBytes_addr);
				}

#endif 
			}
				  break;
			case  CONST_imCommType_transferVideoDataResp:
				  if  (  transferVideoDataResp2Stream(  pContent->uiType,  &pContent->transferVideoDataResp,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;  
				  break;
			case  CONST_imCommType_transferAudioData:
				//
			{
				int  tmpLen = pContent->transferAudioData.uiLen;
				//
				if (transferAudioData2Stream(pContent->uiType, &pContent->transferAudioData, stream_pBuf, (unsigned  int*)&lenInBytes))  goto  errLabel;
				//
#ifdef  __DEBUG__
				//
				if (0) {
					int wrappingLen = lenInBytes - tmpLen;
					traceLog((TCHAR*)_T("hton: tad.len %d, cnt %d, n.lenInBytes %d, wrappingLen %d, lenInBytes_addr %d. l3598"), tmpLen, (int)pContent->transferAudioData.usCnt, lenInBytes, wrappingLen, lenInBytes_addr);
				}
#endif 
			}
				  //
				  break;
			case  CONST_imCommType_transferAudioDataResp:
				  if  (  transferAudioDataResp2Stream(  pContent->uiType,  &pContent->transferAudioDataResp,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_remoteAssistReq:
				  if  (  remoteAssistReq2Stream(  pContent->uiType,  &pContent->remoteAssistReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_taskInteractionReq:
				  if  (  taskInteractionReq2Stream(  pContent->uiType,  &pContent->taskInteractionReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_confKey:
				  if  (  confKey2Stream(  pContent->uiType,  &pContent->confKey,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
				  //
			case  CONST_imCommType_statusConfLayoutParam:
				if (statusConfLayoutParam2Stream(pContent->uiType, &pContent->statusConfLayoutParam, stream_pBuf, (unsigned  int*)&lenInBytes))  goto  errLabel;
				break;

				  //
			case  CONST_imCommType_confLayout:
				  if  (  confLayout2Stream(  pContent->uiType,  &pContent->confLayout,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_confNvrInfo:
				  if (confNvrInfo2Stream(pContent->uiType, &pContent->confNvrInfo, stream_pBuf, (unsigned  int*)&lenInBytes))  goto  errLabel;
				  break;
			case  CONST_imCommType_confState:  //  2017/09/17
				  if  (  confState2Stream(  pContent->uiType,  &pContent->confState,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_confReq:
				  if  (  confReq2Stream(  pContent->uiType,  &pContent->confReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_confCtrlState:
				  if (confCtrlState2Stream(pContent->uiType, &pContent->confCtrlState, stream_pBuf, (unsigned  int*)&lenInBytes))  goto  errLabel;
				  break;
			case  CONST_imCommType_refreshWebContactsInfo:
				  if  (  refreshWebContactsInfo2Stream(  pContent->uiType,  &pContent->refreshWebContactsInfo,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_vDevComs:
				  if  (  qyVDevComs2Stream(  pContent->uiType,  &pContent->vDevComs,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_retrieveSmPolicy:
				  if  (  retrieveSmPolicy2Stream(  pContent->uiType,  &pContent->retrieveSmPolicy,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;	  
				  break;
			case  CONST_imCommType_retrievePhoneMsgrs:
				  if  (  retrievePhoneMsgrs2Stream(  pContent->uiType,  &pContent->retrievePhoneMsgrs,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_getCfgsReq:	//  2011/01/30
				  if  (  qisGetCfgsReq2Stream(  pContent->uiType,  &pContent->getCfgsReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_retrieveToPaths:
				  if  (  retrieveToPaths2Stream(  pContent->uiType,  &pContent->retrieveToPaths,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_refreshDynBmps:
				  if  (  refreshDynBmps2Stream(  pContent->uiType,  &pContent->refreshDynBmps,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_verifyViewDynBmp:	//  2011/10/31
				  if  (  verifyViewDynBmp2Stream(  pContent->uiType,  &pContent->verifyViewDynBmp,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_retrieveDynBmps:
				  if  (  retrieveDynBmps2Stream(  pContent->uiType,  &pContent->retrieveDynBmps,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_qmdStatus:	//  2011/01/09
				  if  (  qmdStatus2Stream(  pContent->uiType,  &pContent->qmdStatus,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_qmdMcuStatusList:
				  if  (  qmdMcuStatusList2Stream(  pContent->uiType,  &pContent->qmdMcuStatusList,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_mcuCmd:
				  if  (  mcuCmd2Stream(  pContent->uiType,  &pContent->mcuCmd,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;       
				  break;
			case  CONST_imCommType_qmdPolicy:
				  if  (  qmdPolicy2Stream(  pContent->uiType,  &pContent->qmdPolicy,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_queryCustomerServiceOfficerReq:	//  2011/04/06
				  if  (  queryCustomerServiceOfficerReq2Stream(  pContent->uiType,  &pContent->queryCustomerServiceOfficerReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_queryCustomerServiceOfficerReplyReq:	//  2011/04/06
				  if  (  queryCustomerServiceOfficerReplyReq2Stream(  pContent->uiType,  &pContent->queryCustomerServiceOfficerReplyReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferGpsInfo:  //  2012/04/20
				  if  (  transferGpsInfo2Stream(  pContent->uiType,  &pContent->transferGpsInfo,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;  
				  break;
			case  CONST_imCommType_transferGpsReplyInfo:	//  2012/04/20
				  if  (  transferGpsReplyInfo2Stream(  pContent->uiType,  &pContent->transferGpsReplyInfo,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;  
				  break;
			case  CONST_imCommType_transferGpsData:
				  if  (  transferGpsData2Stream(  pContent->uiType,  &pContent->transferGpsData,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;  
				  break;
			case  CONST_imCommType_transferGpsDataResp:
				  if  (  transferGpsDataResp2Stream(  pContent->uiType,  &pContent->transferGpsDataResp,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;  
				  break;				  
			case  CONST_imCommType_ptzControlReq:	//  2012/08/05
				  if  (  ptzControlReq2Stream(  pContent->uiType,  &pContent->ptzControlReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;  
				  break;
			case  CONST_imCommType_ptzControlCmd:	//  2012/08/05
				  if  (  ptzControlCmd2Stream(  pContent->uiType,  &pContent->ptzControlCmd,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;  
				  break;
				  //
			case  CONST_imCommType_queryPeerStatus:	//  2014/07/11
				  if  (  queryPeerStatus2Stream(  pContent->uiType,  &pContent->queryPeerStatus,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
				  //
			case  CONST_imCommType_procOfflineRes:  //  2015/08/01
				  if  (  procOfflineResU2Stream(  pContent->uiType,  &pContent->procOfflineResU,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
				  //
			case  CONST_imCommType_imGrp:  //  2018/10/27
				  if  (  imGrpEx2Stream(  pContent->uiType,  &pContent->imGrpEx,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
				  //
			case  CONST_imCommType_qisCaReq:
				  if (qisCaReq2Stream(pContent->uiType, &pContent->qisCaReq, stream_pBuf, (unsigned  int*)&lenInBytes))  goto  errLabel;
				  break;
				  //
			case  CONST_imCommType_refreshImObjMemInfo:
				  if (refreshImObjMemInfo2Stream(pContent->uiType, &pContent->refreshImObjMemInfo, stream_pBuf, (unsigned int*)&lenInBytes))  goto  errLabel;
				  break;
				    
				  //
			default:
				   TCHAR  tBuf[128];
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "qyhtonRouteTalkData: uiContentType %d can't be supported"  ),  pContent->uiType  );
				   #ifdef  __DEBUG__
						   traceLog(  tBuf  );
				   #endif
				   showInfo_open0(  0,  0,  tBuf  );
				   goto  errLabel;
	}
				
	stream_hton.ulStreamLen  =  lenInBytes;
	lenInBytes  +=  offsetof(  IM_L_STREAM,  buf  );

	if  (  (  lenInBytes  =  qyhtonImLStream(  0,  (  IM_L_STREAM  *  )&stream_hton  )  )  ==  -1  )  goto  errLabel;
	memcpy(  ptr,  &stream_hton,  offsetof(  IM_L_STREAM,  buf  )  );

	lenInBytes  +=  lenInBytes_addr;

	iErr  =  0;
errLabel:

	if  (  !iErr  )  {
		*puiBufSize  =  lenInBytes;
	}

	if  (  iErr  )  
	{
		TCHAR  tBuf[128];
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "qyhtonRouteTalkData failed"  )  );
		if  (  pContent  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, uiContentType %d"  ),  tBuf,  pContent->uiType  );
		showInfo_open0(  0,  0,  tBuf  );
	}

	return  iErr;

}



 //  其中ucFlg用来表示要转换成talkData或addrTalkData
 int  qyntohRouteTalkData(  unsigned  char  ucFlg,  char  *  data,  unsigned  int  dataLen,  MSG_ROUTE  *  pAddr,  IM_CONTENTU  *  pContent,  TCHAR  *  tHintBuf_showInfo,  unsigned  int  uiCnt_tHintBuf_showInfo  ) 
{
	int							iErr									=	-1;
	int							lenInBytes;
	char				*		ptr;
	unsigned  int				size;
	TCHAR						tHintBuf[255  +  1]						=	_T(  ""  );
	unsigned  int				uiType									=	0;
	unsigned  int				uiContentType							=	0;
	
	if  (  !data  ||  !pContent  )  return  -1;

	if  (  isUcFlgRouteTalkData(  ucFlg  )  )  {
		 //
		 if  (  !pAddr  )  goto  errLabel;
		 memset(  pAddr,  0,  sizeof(  pAddr[0]  )  );
		 //
		 ptr  =  data;
		 size  =  dataLen;
		 //
		 if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2MsgRoute,  0,  pAddr  )  )  {
			 //
			 OutputDebugString(  _T(  "qyntohRouteTalkData: stream2Data 1 failed.\n"  )  );
			 showInfo_open0(  0,  0,  _T(  "qyntohRouteTalkData: stream2Data 1 failed.\n"  )  );
			 //
			 goto  errLabel;      
		 }
		 //  剩下的size就是pStream
		}
#if  0
	else  if  (  isUcFlgTalkData(  ucFlg  )  )  {		//  仅用来talkData
		      if  (  !pAddr  )  goto  errLabel;
			  memset(  pAddr,  0,  sizeof(  pAddr[0]  )  );
			  if  (  dataLen  <  sizeof(  MSG_SIMPLE_ROUTE  )  )  goto  errLabel;

			  MSG_SIMPLE_ROUTE		*		pTalkDataAddr;
			  int							lenInBytes_addr;

			  pTalkDataAddr  =  (  MSG_SIMPLE_ROUTE  *  )data;
			  pAddr->idInfo_from.ui64Id  =  pTalkDataAddr->idInfo_from.ui64Id;
			  pAddr->idInfo_to.ui64Id  =  pTalkDataAddr->idInfo_to.ui64Id;
			  //
			  MACRO_ntohl64(  pAddr->idInfo_from.ui64Id  );
			  MACRO_ntohl64(  pAddr->idInfo_to.ui64Id  );
			  //
			  lenInBytes_addr  =  sizeof(  MSG_SIMPLE_ROUTE  );		  
			  //
			  ptr  =  data  +  lenInBytes_addr;
			  size  =  dataLen  -  lenInBytes_addr;
			  }
#endif 
	//
	else  {
		  //  这里是没有addr的数据
		  ptr  =  data;
		  size  =  dataLen;
	}
	
	//
	//
	//  这里应该做一个将contentU转换guo来的工作。
	//  注意：在qyMc里，有所有的input的数据转换时，都要修改
	//  另外：要特别注意和老程序的通信的兼容性。老程序的talk和task等结构都是用MIS_MSG_TALKDATA发的。
	//

	if  (  size  <  sizeof(   uiType  )  )  goto  errLabel; 

	//  uiType  =  qyntohl(  (  (  IM_CONTENTU  *  )ptr  )->uiType  );
	//  memcpy(  &uiType,  &(  (  IM_CONTENTU  *  )ptr  )->uiType,  sizeof(  uiType  )  );
	memcpy(  &uiType,  ptr,  sizeof(  uiType  )  );
	MACRO_ntohl(  uiType  );
	switch  (  uiType  )  {
			case  0:
				  if  (  size  <  sizeof(  pContent->uiType  )  )  goto  errLabel;
				  memcpy(  &pContent->uiType,  ptr,  sizeof(  pContent->uiType  )  );
				  MACRO_ntohl(  pContent->uiType  );
				  lenInBytes  =  sizeof(  pContent->uiType  );
				  iErr  =  0;  goto  errLabel;
				  break;
		    case  CONST_imCommType_simpleResp:
				  if  (  size  <  sizeof(  IM_SIMPLE_RESP  )  )  goto  errLabel;
				  memcpy(  &pContent->simpleResp,  ptr,  sizeof(  pContent->simpleResp  )  );
				  if  (  (  lenInBytes  =  qyntohImSimpleResp(  0,  &pContent->simpleResp  )  )  <  0  )  goto  errLabel; 
				  iErr  =  0;  goto  errLabel;
				  break;
			case  CONST_imCommType_refreshRecentFriendsReq:
				  //
#if  0
					memcpy(&pContent->refreshRecentFriendsReq, ptr, min(size, sizeof(pContent->refreshRecentFriendsReq)));
					if ((lenInBytes = qyntohRefreshRecentFriendsReq(0, &pContent->refreshRecentFriendsReq)) < 0)  goto  errLabel;
		
#endif 
					if ((lenInBytes = qyntohRefreshRecentFriendsReq(0, (AT_REFRESH_RECENTFRIENDS_REQ_n  *)ptr, &pContent->refreshRecentFriendsReq)) < 0)  goto  errLabel;

				  //
				  iErr  =  0;  goto  errLabel;
			default:
					break;
	}

#if  0	//  2011/01/29
	if  (  uiType  ==  CONST_imCommType_streamContent  )  {

		IM_STREAM_CONTENT_nh			stream_ntoh;
		IM_STREAM_CONTENT_nh	*		pStream		=	&stream_ntoh;

		//  pStream  =  (  IM_STREAM_CONTENT  *  )ptr;

		if  (  (  lenInBytes  =  qyntohImStreamContent(  0,  ptr,  pStream  )  )  <  0  )  goto  errLabel;

		if  (  size  <  (  unsigned  int  )lenInBytes  )  goto  errLabel;

		ptr  =  pStream->p;
		size  =  pStream->usStreamLen;

		if  (  size  <  offsetof(  IM_STREAM_CONTENT,  buf  )  )  goto  errLabel;

		uiContentType  =  pStream->uiContentType;

		}
	else
#endif
		if  (  uiType  ==  CONST_imCommType_lStream  )  {
		      //
			  IM_L_STREAM_nh				stream_ntoh;
			  IM_L_STREAM_nh		*		pStream			=	&stream_ntoh;

			  //
			  if (size < offsetof(IM_L_STREAM, buf)) {
				  showInfo_open0(0, 0, _T("ntohRouteTalkData failed, lStream. size < offsetof(IM_L_STREAM_buf)"));
				  goto  errLabel;
			  }

			  //  
			  if  (  (  lenInBytes  =  qyntohImLStream(  0,  ptr,  pStream  )  )  <  0  )  goto  errLabel;

			  if  (  size  <  (  unsigned  int  )lenInBytes  )  goto  errLabel;

			  ptr  =  pStream->p;
			  //  size  =  pStream->ulStreamLen;
			  memcpy(  &size,  &pStream->ulStreamLen,  sizeof(  long  )  );

			  //
			  //if (size < offsetof(IM_L_STREAM, buf)) 
			  if  (  size  > CONST_bufSize_imLStream)
			  {
				  showInfo_open0(0, 0, _T("ntohRouteTalkData failed, lStream, ulStreamLen > CONST_bufSize_imLStream"));
				  goto  errLabel;
			  }

			  //  uiContentType  =  pStream->uiContentType;
			  memcpy(  &uiContentType,  &pStream->uiContentType,  sizeof(  long  )  );
		}
	else  {
		  //
			if (1) {
				QY_CFGITEM_ntoh_U		item_ntoh_U;
				QY_CFGITEM_ntoh_U* pItem;
				int len;
				short  tmp_cfgId;
				short  tmp_dataType;
				long uiSteamId = 0;

				len = atntohCfgItem(ptr, size, &item_ntoh_U);		//  这里要注意：这里qyntohCfgItem(  )返回的是转换前的字节流长度。和qyhtonCfgItem(  )返回的不同
				pItem = &item_ntoh_U;

				if (len <= 0 || len > size)  goto  errLabel;

				memcpy(&tmp_cfgId, &pItem->head.cfgId, sizeof(short));			//  2010/04/08
				memcpy(&tmp_dataType, &pItem->head.dataType, sizeof(short));		//  2010/04/08

				//ptr += len;  size -= len;

				//
				if (tmp_cfgId != CONST_qnmCfgId_start)  goto  errLabel;


				if (tmp_cfgId == CONST_qnmCfgId_start) {

					//  
					getFieldData_long(pItem, &uiSteamId);
				}

				//
				uiContentType = uiSteamId;
			}

		    //			
			switch (uiContentType) {
					case  CONST_imCommType_transferAudioData:  {
						  int  iii  =  0;
						  }
						  break;
					case  CONST_imCommType_transferVideoData: {
						  int  ii = 0;
						  }
						  break;
					default:

						  //
						  #ifdef  __DEBUG__
								  traceLogA((char*)"qyntohRouteTalkData 得到了非长流的数据包, uiType %d, size %d", uiType, size);
						  #endif
						  goto  errLabel;

						  //
						 break;
			}
	}
	
	//
#ifdef  __DEBUG__
	if (uiContentType != CONST_imCommType_qisCaReq) {
		int  ii = 0;

		}
#endif 


	//
	{
		switch  (  uiContentType  )  {
				case  CONST_imCommType_htmlContent:
					  memset(  &pContent->html,  0,  sizeof(  pContent->html  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2ImHtmlContent,  0,  pContent  )  )  goto  errLabel;  
					  break;
				case  CONST_imCommType_refreshRecentFriendsResp:
					  memset(  &pContent->refreshRecentFriendsResp,  0,  sizeof(  pContent->refreshRecentFriendsResp  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RefreshRecentFriendsResp,  0,  pContent  )  )  {		//  这里，对万一有数据包下发不完整的情况下，做截断处理。不简单退出
						  //  
						  //  qyShowInfo1(  CONST_qyShowType_qwmComm,  (  ""  ),  _T(  ""  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    stream2Data failed, usCnt is %d, 截断处理"  ),  pContent->refreshRecentFriendsResp.usCnt  );
						  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "stream2Data failed, usCnt is %d, 截断处理"  ),  pContent->refreshRecentFriendsResp.usCnt  );
						  //
						  if  (  pContent->refreshRecentFriendsResp.usCnt_mems  )  pContent->refreshRecentFriendsResp.usCnt_mems  --  ;	//  因为最后一个包不完整，所以要去掉
						  pContent->refreshRecentFriendsResp.usCnt  =  pContent->refreshRecentFriendsResp.usCnt_mems;
						  //
					  }
					  if  (  pContent->refreshRecentFriendsResp.usCnt  >  mycountof(  pContent->refreshRecentFriendsResp.mems  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_getCfgsReq:
					  //  memset(  &pContent->intervalParams,  0,  sizeof(  pContent->intervalParams  )  );
					  memset(  &pContent->getCfgsReq,  0,  sizeof(  pContent->getCfgsReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2QisGetCfgsReq,  0,  pContent  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_retrieveImGrpListResp:
					  memset(  &pContent->retrieveImGrpListResp,  0,  sizeof(  pContent->retrieveImGrpListResp  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RetrieveImGrpListResp,  0,  &pContent->retrieveImGrpListResp  )  )  goto  errLabel;
					  if  (  pContent->retrieveImGrpListResp.usCnt  >  mycountof(  pContent->retrieveImGrpListResp.mems  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_retrieveImGrpMemListResp:
					  memset(  &pContent->retrieveImGrpMemListResp,  0,  sizeof(  pContent->retrieveImGrpMemListResp  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RetrieveImGrpMemListResp,  0,  &pContent->retrieveImGrpMemListResp  )  )  goto  errLabel;
					  if  (  pContent->retrieveImGrpMemListResp.usCnt  >  mycountof(  pContent->retrieveImGrpMemListResp.mems  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_retrieveContactListResp:
					  memset(  &pContent->retrieveContactListResp,  0,  sizeof(  pContent->retrieveContactListResp  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RetrieveContactListResp,  0,  &pContent->retrieveContactListResp  )  )  goto  errLabel;
					  if  (  pContent->retrieveContactListResp.usCnt  >  mycountof(  pContent->retrieveContactListResp.mems  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_retrieveImObjListEndResp:
					  memset(  &pContent->retrieveImObjListEndResp,  0,  sizeof(  pContent->retrieveImObjListEndResp  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RetrieveImObjListEndResp,  0,  &pContent->retrieveImObjListEndResp  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferFileReq:
					  memset(  &pContent->transferFileReq,  0,  sizeof(  pContent->transferFileReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferFileReq,  0,  &pContent->transferFileReq  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferFileReplyReq:
					  memset(  &pContent->transferFileReplyReq,  0,  sizeof(  pContent->transferFileReplyReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferFileReplyReq,  0,  &pContent->transferFileReplyReq  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_taskProcReq:
					  memset(  &pContent->taskProcReq,  0,  sizeof(  pContent->taskProcReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TaskProcReq,  0,  &pContent->taskProcReq  )  )  goto  errLabel;
					  //
#ifdef  __DEBUG__
					  if (1) {
						  if (pContent->taskProcReq.usOp == CONST_imOp_ping) {
							  int  ii = 0;
						  }
					  }
#endif 
					  //
					  break;
				case  CONST_imCommType_taskProcResp:
					  memset(  &pContent->taskProcResp,  0,  sizeof(  pContent->taskProcResp  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TaskProcResp,  0,  &pContent->taskProcResp  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferFileDataReq:
					  memset(  &pContent->transferFileDataReq,  0,  sizeof(  pContent->transferFileDataReq  )  );	
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferFileDataReq,  0,  &pContent->transferFileDataReq  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferFileDataResp:
					  memset(  &pContent->transferFileDataResp,  0,  offsetof(  TRANSFER_FILEDATA_RESP,  buf  )  );	//  把控制数据清空即可
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferFileDataResp,  0,  &pContent->transferFileDataResp  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferFileEndReq:
					  memset(  &pContent->transferFileEndReq,  0,  sizeof(  pContent->transferFileEndReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferFileEndReq,  0,  &pContent->transferFileEndReq  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_rtcCallReq:
					  memset(  &pContent->rtcCallReq,  0,  sizeof(  pContent->rtcCallReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RtcCallReq,  0,  &pContent->rtcCallReq  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferAvInfo:
					  memset(  &pContent->transferAvInfo,  0,  sizeof(  pContent->transferAvInfo  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferAvInfo,  0,  &pContent->transferAvInfo  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferAvReplyInfo:
					  memset(  &pContent->transferAvReplyInfo,  0,  sizeof(  pContent->transferAvReplyInfo  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferAvReplyInfo,  0,  &pContent->transferAvReplyInfo  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferVideoData:
					  memset(  &pContent->transferVideoData,  0,  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  );  //  这里，把控制数据清空即可。
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferVideoData,  0,  &pContent->transferVideoData  )  )  goto  errLabel;
					  //
#ifdef  __DEBUG__
					  if (0) {
						  int  i;
						  TCHAR  tBuf[128];
						  static  int s_last_st = 0;
						  for (i = 0; i < pContent->transferVideoData.usCnt; i++) {
							  TRANSFER_VIDEO_dataMemHead* pMem = &pContent->transferVideoData.mems[i];
							  //
							  int  iDiffInMs = pMem->uiSampleTimeInMs  -  s_last_st;
							  s_last_st = pMem->uiSampleTimeInMs;
							  //
							  _sntprintf(tBuf, mycountof(tBuf), _T("tvd.cnt %d, mem[%d]: pts %d, st %d. diffInMs %dms"), (int)pContent->transferVideoData.usCnt, i, pMem->uiPts, pMem->uiSampleTimeInMs,  iDiffInMs);
							  showInfo_open0(0, 0, tBuf);
						  }
					  }
#endif
					  //
					  break;
				case  CONST_imCommType_transferVideoDataResp:
					  memset(  &pContent->transferVideoDataResp,  0,  sizeof(  pContent->transferVideoDataResp  )  );  //  这里，把控制数据清空即可。
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferVideoDataResp,  0,  &pContent->transferVideoDataResp  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferAudioData:
					  memset(  &pContent->transferAudioData,  0,  offsetof(  TRANSFER_AUDIO_DATA,  buf  )  );  //  这里，把控制数据清空即可。
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferAudioData,  0,  &pContent->transferAudioData  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferAudioDataResp:
					  memset(  &pContent->transferAudioDataResp,  0,  sizeof(  pContent->transferAudioDataResp  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferAudioDataResp,  0,  &pContent->transferAudioDataResp  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_remoteAssistReq:
					  memset(  &pContent->remoteAssistReq,  0,  sizeof(  pContent->remoteAssistReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RemoteAssistReq,  0,  &pContent->remoteAssistReq  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_taskInteractionReq:
					  memset(  &pContent->taskInteractionReq,  0,  sizeof(  pContent->taskInteractionReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TaskInteractionReq,  0,  &pContent->taskInteractionReq  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_confKey:
					  memset(  &pContent->confKey,  0,  sizeof(  pContent->confKey  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2confKey,  0,  &pContent->confKey  )  )  goto  errLabel;
					  break;

				case  CONST_imCommType_statusConfLayoutParam:
					memset(&pContent->statusConfLayoutParam, 0, sizeof(pContent->statusConfLayoutParam));
					if (stream2Data(&ptr, &size, filterStream_is, tmpHandler_stream2statusConfLayoutParam, 0, &pContent->statusConfLayoutParam))  goto  errLabel;
					break;

					  //
				case  CONST_imCommType_confLayout:
					  memset(  &pContent->confLayout,  0,  sizeof(  pContent->confLayout  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2confLayout,  0,  &pContent->confLayout  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_confNvrInfo:
					  memset(&pContent->confNvrInfo, 0, sizeof(pContent->confNvrInfo));
					  if (stream2Data(&ptr, &size, filterStream_is, tmpHandler_stream2confNvrInfo, 0, &pContent->confNvrInfo))  goto  errLabel;
					  break;
				case  CONST_imCommType_confState:  //  2017/09/17
					  memset(  &pContent->confState,  0,  sizeof(  pContent->confState  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2ConfState,  0,  &pContent->confState  )  )  goto  errLabel;
					  break;
					  //
				case  CONST_imCommType_confReq:  //  2017/09/17
					  memset(  &pContent->confReq,  0,  sizeof(  pContent->confReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2ConfReq,  0,  &pContent->confReq  )  )  goto  errLabel;
					  break;
					  //
				case  CONST_imCommType_confCtrlState:  //  2017/09/17
					memset(&pContent->confCtrlState, 0, sizeof(pContent->confCtrlState));
					if (stream2Data(&ptr, &size, filterStream_is, tmpHandler_stream2confCtrlState, 0, &pContent->confCtrlState))  goto  errLabel;
					break;

					  //
				case  CONST_imCommType_refreshWebContactsInfo:
					  memset(  &pContent->refreshWebContactsInfo,  0,  sizeof(  pContent->refreshWebContactsInfo  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RefreshWebContactsInfo,  0,  &pContent->refreshWebContactsInfo  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_vDevComs:
					  memset(  &pContent->vDevComs,  0,  sizeof(  pContent->vDevComs  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2QyVDevComs,  0,  &pContent->vDevComs  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_retrieveSmPolicy:
					  memset(  &pContent->retrieveSmPolicy,  0,  sizeof(  pContent->retrieveSmPolicy  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RetrieveSmPolicy,  0,  &pContent->retrieveSmPolicy  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_retrievePhoneMsgrs:
					  memset(  &pContent->retrievePhoneMsgrs,  0,  sizeof(  pContent->retrievePhoneMsgrs  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RetrievePhoneMsgrs,  0,  &pContent->retrievePhoneMsgrs  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_retrieveToPaths:
					  memset(  &pContent->retrieveToPaths,  0,  sizeof(  pContent->retrieveToPaths  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RetrieveToPaths,  0,  &pContent->retrieveToPaths  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_refreshDynBmps:
					  memset(  &pContent->refreshDynBmps,  0,  sizeof(  pContent->refreshDynBmps  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RefreshDynBmps,  0,  &pContent->refreshDynBmps  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_verifyViewDynBmp:	//  2011/10/31
					  memset(  &pContent->verifyViewDynBmp,  0,  sizeof(  pContent->verifyViewDynBmp  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2VerifyViewDynBmp,  0,  &pContent->verifyViewDynBmp  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_retrieveDynBmps:
					  memset(  &pContent->retrieveDynBmps,  0,  sizeof(  pContent->retrieveDynBmps  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RetrieveDynBmps,  0,  &pContent->retrieveDynBmps  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_refreshImObjRulesReq:	//  2010/08/15
					  memset(  &pContent->refreshImObjRulesReq,  0,  sizeof(  pContent->refreshImObjRulesReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RefreshImObjRulesReq,  0,  &pContent->refreshImObjRulesReq  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_qmdStatus:		//  2011/01/09
					  memset(  &pContent->qmdStatus,  0,  sizeof(  pContent->qmdStatus  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2qmdStatus,  0,  &pContent->qmdStatus  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_qmdMcuStatusList:
					  memset(  &pContent->qmdMcuStatusList,  0,  sizeof(  pContent->qmdMcuStatusList  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2qmdMcuStatusList,  0,  &pContent->qmdMcuStatusList  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_mcuCmd:
					  memset(  &pContent->mcuCmd,  0,  sizeof(  pContent->mcuCmd  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2mcuCmd,  0,  &pContent->mcuCmd  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_qmdPolicy:
					  memset(  &pContent->qmdPolicy,  0,  sizeof(  pContent->qmdPolicy  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2qmdPolicy,  0,  &pContent->qmdPolicy  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_retrieveCustomerServiceObjListReq:	//  2011/04/04
					  memset(  &pContent->retrieveCustomerServiceObjListReq,  0,  sizeof(  pContent->retrieveCustomerServiceObjListReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RetrieveCustomerServiceObjListReq,  0,  &pContent->retrieveCustomerServiceObjListReq  )  )  goto  errLabel;				  
					  break;
				case  CONST_imCommType_queryCustomerServiceOfficerReq:		//  2011/04/06
					  memset(  &pContent->queryCustomerServiceOfficerReq,  0,  sizeof(  pContent->queryCustomerServiceOfficerReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2QueryCustomerServiceOfficerReq,  0,  &pContent->queryCustomerServiceOfficerReq  )  )  goto  errLabel;				  					  
					  break;
				case  CONST_imCommType_queryCustomerServiceOfficerReplyReq:		//  2011/04/06
					  memset(  &pContent->queryCustomerServiceOfficerReplyReq,  0,  sizeof(  pContent->queryCustomerServiceOfficerReplyReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2QueryCustomerServiceOfficerReplyReq,  0,  &pContent->queryCustomerServiceOfficerReplyReq  )  )  goto  errLabel;				  					  
					  break;
				case  CONST_imCommType_transferGpsInfo:		//  2012/04/20
					  memset(  &pContent->transferGpsInfo,  0,  sizeof(  pContent->transferGpsInfo  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferGpsInfo,  0,  &pContent->transferGpsInfo  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferGpsReplyInfo:
					  memset(  &pContent->transferGpsReplyInfo,  0,  sizeof(  pContent->transferGpsReplyInfo  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferGpsReplyInfo,  0,  &pContent->transferGpsReplyInfo  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferGpsData:
					  memset(  &pContent->transferGpsData,  0,  sizeof(  pContent->transferGpsData  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferGpsData,  0,  &pContent->transferGpsData  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferGpsDataResp:
					  memset(  &pContent->transferGpsDataResp,  0,  sizeof(  pContent->transferGpsDataResp  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferGpsDataResp,  0,  &pContent->transferGpsDataResp  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_ptzControlReq:
					  memset(  &pContent->ptzControlReq,  0,  sizeof(  pContent->ptzControlReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2PtzControlReq,  0,  &pContent->ptzControlReq  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_ptzControlCmd:
					  memset(  &pContent->ptzControlCmd,  0,  sizeof(  pContent->ptzControlCmd  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2PtzControlCmd,  0,  &pContent->ptzControlCmd  )  )  goto  errLabel;
					  break;
					  //  
				case  CONST_imCommType_queryPeerStatus:	//  2014/07/11
					  memset(  &pContent->queryPeerStatus,  0,  sizeof(  pContent->queryPeerStatus  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2QueryPeerStatus,  0,  &pContent->queryPeerStatus  )  )  goto  errLabel;
					  break;
					  //
				case  CONST_imCommType_procOfflineRes:  //  2015/08/01
					  memset(  &pContent->procOfflineResU,  0,  sizeof(  pContent->procOfflineResU  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2ProcOfflineResU,  0,  &pContent->procOfflineResU  )  )  goto  errLabel;
					  break;
					  //
				case  CONST_imCommType_imGrp:  //  2017/07/26
					  memset(  &pContent->imGrpEx,  0,  sizeof(  pContent->imGrpEx  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2ImGrpEx,  0,  &pContent->imGrpEx  )  )  goto  errLabel;
					  break;
					  //
				case  CONST_imCommType_qisCaReq:
					  memset(  &pContent->qisCaReq,  0,  sizeof(  pContent->qisCaReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2QisCaReq,  0,  &pContent->qisCaReq  )  )  goto  errLabel;					  
					  break;
					  //
				case  CONST_imCommType_refreshImObjMemInfo:
					  memset(&pContent->refreshImObjMemInfo, 0, sizeof(pContent->refreshImObjMemInfo));
					  if (stream2Data(&ptr, &size, filterStream_is, tmpHandler_stream2RefreshImObjMemInfo, 0, &pContent->refreshImObjMemInfo))  goto  errLabel;
					  break;
					  //
				case  CONST_imCommType_chkLogonIdReq:
					  memset(  &pContent->chkLogonIdReq,  0,  sizeof(  pContent->chkLogonIdReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2ChkLogonIdReq,  0,  &pContent->chkLogonIdReq  )  )  goto  errLabel;					  
					  break;
					  //
				default:
					   TCHAR  tBuf[128];
					   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "qyntohRouteTalkData failed: uiContentType %d %s, error"  ),  uiContentType,  qyGetDesByType1(  CONST_qyCommTypeTable_en,  uiContentType  )  );  
					   #ifdef  __DEBUG__
							   traceLog(  tBuf  );
					   #endif
					   showInfo_open0(  0,  0,  tBuf  );
					   goto  errLabel;	
			}

			iErr  =  0;  goto  errLabel;
	}
			

	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		//  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%scontentType [%s]"  ),  tHintBuf,  qyGetDesByType1(  CONST_qyCommTypeTable,  uiContentType  )  );
		traceLogA(  (char*)"qyntohAddrTalkData failed"  );
	}
	if  (  !iErr  )  {
	}
	//
	if  (  tHintBuf_showInfo  )  lstrcpyn(  tHintBuf_showInfo,  tHintBuf,  uiCnt_tHintBuf_showInfo  );

	return  iErr;

}




