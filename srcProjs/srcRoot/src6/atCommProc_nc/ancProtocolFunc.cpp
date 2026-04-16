
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
#include	"../atInclude/ancCorePublic.h"
#include	"ancCommProc.h"


//
bool  g_bUseMsb_cfgHead_toh = true;// true;// false;	//  就是不用msb方式接收
bool  g_bUseMsb_cfgHead_ton = true;// false;// true;// false;	//  就是不用msb方式发送

//
//  1msb +  3bits dataType  +  (4bits+8bits  )usCfgId  

// 将iDataType和usCfgId填入ptr开头的字节流里。
// 返回处理了几个字节

int ton_cfgHead(int iDataType, unsigned  short usCfgId, char** p_ptr, int size, int  *p_total )
{
	int  iErr = -1;
	int  headLen = 0;
	int len;

	//
	if (!p_ptr)  return  -1;
	char* ptr = *p_ptr;

	//
	do {
		int  ii = -1;
		ii = (byte)ii;
		ii = (byte)ii & ~CONST_atCommFlg_msb;
		//
		if (  iDataType  <  0  ||  iDataType > 127) {
			//
			traceLog((TCHAR*)_T("to_cfgHead err, iDataType err"));
			//
			break;
		}

		//
		if (!g_bUseMsb_cfgHead_ton) {
			M_ton_atbyte(iDataType, ptr, len);  headLen += len;
			M_ton_short(usCfgId, ptr, len);  headLen += len;
		}
		else {
			if (iDataType >= 0 && iDataType < 8 && usCfgId <= MAX_12bits) {
				byte  buf[2];
				byte* tmp_p = buf;
				M_ton_short(usCfgId, tmp_p, len);
				//
				byte b0 = (iDataType << 4) | CONST_atCommFlg_msb;
				buf[0] |= b0;
				//
				if (size < 2) {
					showInfo_open0(0, 0, _T("ton_cfgHead failed"));
					break;
				}
				memcpy(ptr, buf, 2);
				headLen += 2;

				//				
			}
			else {
				M_ton_atbyte(iDataType, ptr, len);  headLen += len;
				M_ton_short(usCfgId, ptr, len);  headLen += len;
			}
		}

		//
		*p_ptr += headLen;
		*p_total += headLen;


		//
		iErr = 0;

	} while (false);


	//
	return  iErr  ?  -1  :  headLen;
}


//
int toh_cfgHead(char* tmp_p, int size, int* piDataType, unsigned  short* p_usCfgId)
{
	int  iErr = -1;
	int headLen = 0;
	int  tmpLen;

	do {
		if (!g_bUseMsb_cfgHead_toh) {
			//
			M_toh_atbyte(tmp_p, *piDataType, tmpLen);  headLen += tmpLen;
			M_toh_short(tmp_p, *p_usCfgId, tmpLen);  headLen += tmpLen;
		}
		else {
			if (size <= 0) {
				showInfo_open0(0, 0, _T("toh_cfgHead failed, size <=0"));
				break;
			}
			byte b0 = tmp_p[0];
			if ((b0 & CONST_atCommFlg_msb)) {
				b0 &= ~CONST_atCommFlg_msb;
				*piDataType = b0 >> 4;
				byte low4 = (byte)(b0 & 0x0F);
				char buf[2];
				buf[0] = low4;
				buf[1] = tmp_p[1];
				char* pp = buf;
				M_toh_short(pp, *p_usCfgId, tmpLen);
				//
				headLen = 2;


			}
			else {
				//
				M_toh_atbyte(tmp_p, *piDataType, tmpLen);  headLen += tmpLen;
				M_toh_short(tmp_p, *p_usCfgId, tmpLen);  headLen += tmpLen;

			}

		}

		//
		iErr = 0;

	} while (false);
	//
	return  iErr  ?  -1  :  headLen;
}





 


//////////////////
//  对orgData是WCHAR的情况，orgDataSize表示WCHAR的count
//  对这个流要求用CONST_qnmCfgId_null结尾
//  *pptr指向下一个空间，而不是输出串
//  *pSize为剩余的字节数，不是一共得到了多少
 int  atData2Stream(int  iDataType, unsigned  short  usCfgId, void* orgData, unsigned  int  orgDataSize, char** pptr_usable, unsigned  int* pSize_usable)
 {
	 //
	 int					iErr = -1;
	 QY_CFGITEM_STR			itemStr;
	 QY_CFGITEM_LONG		itemLong;
	 QY_CFGITEM_CHAR		itemChar;
	 QY_CFGITEM_SHORT		itemShort;
	 QY_CFGITEM_L64			itemL64;
	 QY_CFGITEM* pItem = NULL;
	 unsigned  int			len;
	 unsigned  int			size = 0;
	 char* ptr = NULL;
	 CQyMalloc				mallocObj;

	 if (!pptr_usable || !*pptr_usable || !pSize_usable)  return  -1;
	 if (!orgData) {
		 switch (iDataType) {
		 case  CONST_qyDataType_long:
		 case  CONST_qyDataType_char:
		 case  CONST_qyDataType_short:
			 break;
		 default:
			 return  -1;	//  非数值的值为地址，不能为空
		 }
	 }
	 if (iDataType == CONST_qyDataType_l64) {
		 if (orgDataSize && orgDataSize < sizeof(__int64)) {		//  传入0也算了，早期代码都用0。2007/12/11
			 traceLogA((char*)"data2Stream: l64需要传入数据地址，故建议输入数据长度应>=sizeof(  __int64  )");
		 }
	 }

	 //
	 ptr = *pptr_usable;
	 size = *pSize_usable;

	 //
	 bool  bProcessed = false;

	 //
	 if (10) 
	 {
#if  10
		 if (iDataType == CONST_qyDataType_l64) {
			 unsigned  __int64  ul64;  memcpy(&ul64, orgData, sizeof(__int64));
			 unsigned  int high4Bytes;
			 unsigned  int  low4Bytes;

			 // 方法1：位运算（右移32位，截断为32位）
			 high4Bytes = (unsigned  int)(ul64 >> 32);
			 low4Bytes = (unsigned  int)ul64;
			 if (!high4Bytes) {
				 return  atData2Stream(CONST_qyDataType_l32, usCfgId, (void*)low4Bytes, 0, pptr_usable, pSize_usable);
			 }
		 }
#endif
		 //
#if  10
		 if (iDataType == CONST_qyDataType_l32) {
			 unsigned  int  ul32;  ul32 = (unsigned  int)orgData;
			 unsigned  short  high2Bytes;
			 unsigned  short  low2Bytes;
			 //
			 high2Bytes = (unsigned  short)(ul32 >> 16);
			 low2Bytes = (unsigned  short)ul32;
			 if (!high2Bytes) {
				 return  atData2Stream(CONST_qyDataType_short, usCfgId, (void*)low2Bytes, 0, pptr_usable, pSize_usable);
			 }
		 }
#endif 
		 //
#if  10

		 if (iDataType == CONST_qyDataType_short) {
			 unsigned  short  us16;  us16 = (unsigned  short)orgData;
			 unsigned  char  high1Bytes;
			 unsigned  char  low1Bytes;
			 //
			 high1Bytes = (unsigned  char)(us16 >> 8);
			 low1Bytes = (unsigned char)us16;
			 if (!high1Bytes) {
				 return  atData2Stream(CONST_qyDataType_byte, usCfgId, (void*)low1Bytes, 0, pptr_usable, pSize_usable);
			 }

		 }
#endif 
	 }



	 //
	 int total = 0;
	 //
#ifdef  __USE_atCommVer_1__
	 M_ton_short(usCfgId, ptr, len);  total += len;
	 M_ton_atbyte(iDataType, ptr, len);  total += len;
#else
	 //
	 if (0) {
		 M_ton_atbyte(iDataType, ptr, len);  total += len;
		 M_ton_short(usCfgId, ptr, len);  total += len;
	 }
	 else {
		 //
		 if (ton_cfgHead(iDataType, usCfgId, &ptr, size, &total) < 0) {
			 return  -1;
		 }
	 }
	 //
#endif 

	 //
	 switch (iDataType) {
			case  CONST_qyDataType_long:
				  //  AT_CFGITEM_LONG
				  //
				  unsigned  long ulVal;  ulVal = (unsigned  long)orgData;
				  M_ton_long(ulVal, ptr, len); total += len;
				  //
				  //  	 memcpy(ptr, (char*)pItem, len);  ptr += len;  size -= len;
				  size -= total;
				  //
				  bProcessed = true;
				  break;
			case  CONST_qyDataType_char:
				//  AT_CFGITEM_CHAR
				//
				unsigned  char  ucVal;  ucVal = (unsigned  char)orgData;
				M_ton_byte(ucVal, ptr, len); total += len;
				//
				size -= total;
				//
				bProcessed = true;
				//
				break;
			case  CONST_qyDataType_short:
				//  AT_CFGITEM_SHORT  
				//
				unsigned  short  usVal;  usVal = (unsigned  short)orgData;
				M_ton_short(usVal, ptr, len); total += len;
				//
				size -= total;
				//
				bProcessed = true;
				//
				break;
			case  CONST_qyDataType_data: {
					//  AT_CFGITEM_DATA
					//
				if (orgDataSize > CONST_bufSize_cfgItemData) {
					traceLogA((char*)"data2Stream: dataType_data: too big dataSize");  goto  errLabel;
				}
				unsigned  short  usLen;  usLen  = orgDataSize;
				if (usLen != orgDataSize) {		//  2008/04/01, 
					//
					traceLog((TCHAR*) _T(  "data2Stream: dataType_data error, buf truncated. data can't more than short" )  );
					//
					goto  errLabel;
				}
				M_ton_short(usLen, ptr, len);  total += len;
				M_ton_data(orgData, usLen, ptr, len);  total += len;
				//
				size -= total;
				//
				bProcessed = true;
				//
			}
									   break;
			case  CONST_qyDataType_lData: {
				  //  AT_CFGITEM_LDATA
				//
				if (orgDataSize > CONST_bufSize_cfgItemLData) {
					//
					traceLog((TCHAR*)_T("data2Stream: dataType_lData: too big dataSize"));  
					//
					goto  errLabel;
				}
				unsigned  int  ulLen;  ulLen = orgDataSize;
				//
				M_ton_long(ulLen, ptr, len);  total += len;
				M_ton_data(orgData, ulLen, ptr, len); total += len;
				//
				size -= total;
				//
				bProcessed = true;
				//

			}
										break;
			case  CONST_qyDataType_l64:
				  //AT_CFGITEM_L64 
				  // 
				//
				unsigned  __int64  ul64;  memcpy(&ul64, orgData, sizeof(__int64));
				M_ton_l64(ul64, ptr, len); total += len;
				//
				size -= total;
				//
				bProcessed = true;
				//
				break;

			case  CONST_qyDataType_str:
			case  CONST_qyDataType_utf8Str: {
				//
				//AT_CFGITEM_STR  
				//
				unsigned  short  usLen = min(CONST_cntofStr_cfgItemStr, orgDataSize);
				M_ton_short(usLen, ptr, len); total += len;
				M_ton_data(orgData, usLen, ptr, len);  total += len;
				//
				size -= total;
				//
				bProcessed = true;
				//

			}
										  break;
			case  CONST_qyDataType_wStr: {
				  //
				  //  AT_CFGITEM_WSTR
				  //
				WCHAR* wStr = (WCHAR*)orgData;
				wStr[orgDataSize] = 0;
				//
				if (orgDataSize < 1024) {
					//
					char  str[CONST_cntofStr_cfgItemStr];
					int  tmp_iDataType = 0;
					//
					if (!myWChar2Utf8(wStr, str, sizeof(str)))  goto  errLabel;
					tmp_iDataType = CONST_qyDataType_utf8Str;
					unsigned  short  usLen;  usLen = strlen(str);
					
					//
					ptr = *pptr_usable;
					size = *pSize_usable;

					//
					total = 0;
					//
#ifdef  __USE_atCommVer_1__
					M_ton_short(usCfgId, ptr, len);  total += len;
					M_ton_atbyte(tmp_iDataType, ptr, len);  total += len;
#else
					if (0) {
						M_ton_atbyte(tmp_iDataType, ptr, len);  total += len;
						M_ton_short(usCfgId, ptr, len);  total += len;
					}
					else {
						if (0 > ton_cfgHead(tmp_iDataType, usCfgId, &ptr, size, &total)) {
							goto  errLabel;
						}
					}
#endif 
					//
					M_ton_short(usLen, ptr, len); total += len;
					//
					M_ton_data(str, usLen, ptr, len); total += len;
					//
					size -= total;
					//
					bProcessed = true;

				}
				else {  //2010/12/05
					//QY_CFGITEM_DATA* pItemData = NULL;
					int					tmpBufSize = (orgDataSize + 1) * sizeof(WCHAR);
					//int					tmpSize = offsetof(QY_CFGITEM_DATA, buf) + tmpBufSize;
					//
					if (tmpBufSize > CONST_bufSize_cfgItemData) {
						traceLogA((char*)"data2Stream: dataType_wStr: too big dataSize");
						goto  errLabel;
					}
					//
					char* str;
					if (!(str = mallocObj.mallocf(tmpBufSize))) {
						traceLogA((char*)"data2Stream. malloc from QY_CFGITEM_DATA failed.");
						goto  errLabel;
					}
					//
					//pItemData->cfgId = usCfgId;
					if (!myWChar2Utf8(wStr, str, tmpBufSize))  goto  errLabel;
					int  tmp_iDataType;
					tmp_iDataType = CONST_qyDataType_utf8Str;
					unsigned  short  usLen;  usLen  = strlen(str);
					//pItem = (QY_CFGITEM*)pItemData;
					//

										//
					ptr = *pptr_usable;
					size = *pSize_usable;

					//
					total = 0;
					//
#ifdef  __USE_atCommVer_1__
					M_ton_short(usCfgId, ptr, len);  total += len;
					M_ton_atbyte(tmp_iDataType, ptr, len);  total += len;
#else
					if (0) {
						M_ton_atbyte(tmp_iDataType, ptr, len);  total += len;
						M_ton_short(usCfgId, ptr, len);  total += len;
					}
					else {
						if (0 > ton_cfgHead(tmp_iDataType, usCfgId, &ptr, size, &total)) {
							goto  errLabel;
						}
					}
#endif 
					//
					M_ton_short(usLen, ptr, len); total += len;
					//
					M_ton_data(str, usLen, ptr, len); total += len;
					//
					size -= total;
					//
					bProcessed = true;



				}
			}
									   break;



			default:
					break;
	 }


	 //
	 if (!bProcessed) {

		 //
		 ptr = *pptr_usable;
		 size = *pSize_usable;

		 //
		 switch (iDataType) {
		 case  CONST_qyDataType_long:
			 itemLong.cfgId = usCfgId;
			 itemLong.dataType = iDataType;
			 itemLong.ulVal = (unsigned  long)orgData;
			 pItem = (QY_CFGITEM*)&itemLong;
			 break;
		 case  CONST_qyDataType_char:
			 itemChar.cfgId = usCfgId;
			 itemChar.dataType = iDataType;
			 itemChar.ucVal = (unsigned  char)orgData;
			 pItem = (QY_CFGITEM*)&itemChar;
			 break;
		 case  CONST_qyDataType_short:
			 itemShort.cfgId = usCfgId;
			 itemShort.dataType = iDataType;
			 itemShort.usVal = (unsigned  short)orgData;
			 pItem = (QY_CFGITEM*)&itemShort;
			 break;
		 case  CONST_qyDataType_data: {
			 QY_CFGITEM_DATA* pItemData = NULL;
			 int					tmpSize = offsetof(QY_CFGITEM_DATA, buf) + orgDataSize;	//  sizeof(  QY_CFGITEM_DATA  )	//  2010/09/10
			 //
			 if (!(pItemData = (QY_CFGITEM_DATA*)mallocObj.mallocf(tmpSize))) {
				 traceLogA((char*)"data2Stream. malloc from QY_CFGITEM_DATA failed.");  goto  errLabel;
			 }
			 //
			 pItemData->cfgId = usCfgId;
			 pItemData->dataType = iDataType;
			 if (orgDataSize > sizeof(pItemData->buf)) {
				 traceLogA((char*)"data2Stream: dataType_data: too big dataSize");  goto  errLabel;
			 }
			 pItemData->len = orgDataSize;
			 if (pItemData->len != orgDataSize) {		//  2008/04/01, 
				 //
				 traceLog((TCHAR*)_T("data2Stream: dataType_data error, buf truncated. data can't more than short"));
				 //
				 goto  errLabel;
			 }
			 memcpy(pItemData->buf, orgData, pItemData->len);
			 pItem = (QY_CFGITEM*)pItemData;
		 }
									break;
		 case  CONST_qyDataType_lData: {
			 QY_CFGITEM_LDATA* pItemLData = NULL;
			 int					tmpSize = offsetof(QY_CFGITEM_LDATA, buf) + orgDataSize;	//  sizeof(  QY_CFGITEM_LDATA  )	//  2010/09/10
			 //
			 if (!(pItemLData = (QY_CFGITEM_LDATA*)mallocObj.mallocf(tmpSize))) {
				 traceLogA((char*)"data2Stream. malloc from QY_CFGITEM_LDATA failed.");  goto  errLabel;
			 }
			 //
			 pItemLData->cfgId = usCfgId;
			 pItemLData->dataType = iDataType;
			 if (orgDataSize > sizeof(pItemLData->buf)) {
				 traceLogA((char*)"data2Stream: dataType_lData: too big dataSize");  goto  errLabel;
			 }
			 pItemLData->ulLen = orgDataSize;
			 memcpy(pItemLData->buf, orgData, pItemLData->ulLen);
			 pItem = (QY_CFGITEM*)pItemLData;
		 }
									 break;
		 case  CONST_qyDataType_l64:
			 itemL64.cfgId = usCfgId;
			 itemL64.dataType = iDataType;
			 memcpy(itemL64.buf_l64Val, orgData, sizeof(__int64));
			 pItem = (QY_CFGITEM*)&itemL64;
			 break;
		 case  CONST_qyDataType_str:
		 case  CONST_qyDataType_utf8Str: {
			 //
			 itemStr.cfgId = usCfgId;
			 itemStr.dataType = iDataType;
			 itemStr.len = min(sizeof(itemStr.str), orgDataSize);
			 memcpy(itemStr.str, orgData, itemStr.len);
			 pItem = (QY_CFGITEM*)&itemStr;
		 }
									   break;
		 case  CONST_qyDataType_wStr: {
			 WCHAR* wStr = (WCHAR*)orgData;
			 wStr[orgDataSize] = 0;
			 //
			 if (orgDataSize < 1024) {
				 itemStr.cfgId = usCfgId;
				 if (!myWChar2Utf8(wStr, itemStr.str, sizeof(itemStr.str)))  goto  errLabel;
				 itemStr.dataType = CONST_qyDataType_utf8Str;
				 itemStr.len = strlen(itemStr.str);
				 pItem = (QY_CFGITEM*)&itemStr;
			 }
			 else {  //2010/12/05
				 QY_CFGITEM_DATA* pItemData = NULL;
				 int					tmpBufSize = (orgDataSize + 1) * sizeof(WCHAR);
				 int					tmpSize = offsetof(QY_CFGITEM_DATA, buf) + tmpBufSize;
				 //
				 if (tmpBufSize > sizeof(pItemData->buf)) {
					 traceLogA((char*)"data2Stream: dataType_wStr: too big dataSize");
					 goto  errLabel;
				 }
				 //
				 if (!(pItemData = (QY_CFGITEM_DATA*)mallocObj.mallocf(tmpSize))) {
					 traceLogA((char*)"data2Stream. malloc from QY_CFGITEM_DATA failed.");
					 goto  errLabel;
				 }
				 //
				 pItemData->cfgId = usCfgId;
				 if (!myWChar2Utf8(wStr, pItemData->buf, tmpBufSize))  goto  errLabel;
				 pItemData->dataType = CONST_qyDataType_utf8Str;
				 pItemData->len = strlen(pItemData->buf);
				 pItem = (QY_CFGITEM*)pItemData;
			 }
		 }
									break;
		 default:
			 goto  errLabel;

		 }


		 if (!pItem)  goto  errLabel;
		 len = qyhtonCfgItem(pItem);
		 if (len <= 0 || size < len) {
			 traceLogA((char*)"getStream_wStr  error.");  goto  errLabel;
		 }

		 memcpy(ptr, (char*)pItem, len);  ptr += len;  size -= len;

	 }

	 //
	 iErr = 0;
 errLabel:
	 if (!iErr) {
		 *pptr_usable = ptr;
		 *pSize_usable = size;
	 }
	 return  iErr;
	 }


	 //
		///////////////
	// 有符号24位整数的范围
#define INT24_MIN (-8388608L)
#define INT24_MAX (8388607L)

	 //
	 // 24位有符号整数类型（用32位存储，高8位无效）
	 typedef int32_t int24_t;


	 // 将32位整数截断为24位（保留低24位，符号位扩展）
	 int24_t to_int24(int32_t value) {
		 // 若超过最大值，截断为8388607
		 if (value > 8388607) return 8388607;
		 // 若小于最小值，截断为-8388608
		 if (value < -8388608) return -8388608;

		 return value;
	 }



// 24位整数转32位整数（符号扩展）
	 int32_t int24_to_int32(int32_t int24) 
	 {
		 // 提取24位的符号位（第23位）
		 uint32_t sign_bit = (int24 >> 23) & 1;
		 if (sign_bit) {
			 // 负数：高8位补1（0xFF）
			 return int24 | 0xFF000000;
		 }
		 else {
			 // 正数：高8位补0
			 return int24 & 0x00FFFFFF;
		 }
	 }

	 
	 // 32位整数转24位整数（带溢出检查）
	 bool int32_to_int24(int32_t int32, int32_t* int24_result) 
	 {
		 if (int32 < INT24_MIN || int32 > INT24_MAX) {
			 //return false; // 溢出，转换失败
			 int32 = to_int24(int32);
		 }
		 // 保留低24位
		 *int24_result = int32 & 0x00FFFFFF;
		 return true; // 转换成功
	 }



	 //  存放3个字节的数字
	 extern  "C"  int  athtonl3(int  x,  unsigned  char  *  buf,  int  bufSize)
	 {
		 if (bufSize < 3)  return  -1;

		 //
		 int  x24 = 0;
		 int32_to_int24(x,&x24);
		 x = x24;

		 //
		 //buf[0] = (unsigned  char)((x & 0xff000000) >> 24);
		 buf[0] = (unsigned  char)((x & 0xff0000) >> 16);
		 buf[1] = (unsigned  char)((x & 0xff00) >> 8);
		 buf[2] = (unsigned  char)((x & 0xff));

		 //return  *(unsigned  long*)buf;
		 return  0;
	 }

	 extern  "C"  int  atntohl3(unsigned  char  *  buf,  int  bufSize )
	 {
		 int			iRet;

		 if (bufSize < 3)  return  -1;

		 //memcpy(buf, &x, 4);
		 iRet = //(buf[0] << 24) + 
			 (buf[0] << 16) + 
			 (buf[1] << 8) + 
			 buf[2];

		 //
		 iRet = int24_to_int32(iRet);

		 //
		 return  iRet;
	 }


#if  0
	 unsigned  short					usCode;				// 
	 unsigned  char						ucFlg;				//  2007/04/22
	 char								reserved[1];		//  
	 unsigned  int						uiLen;				//  
	 __int64							i64StartTime;		//  2007/05/07, 
	 unsigned  int						uiTranNo;			//  2007/05/02
	 unsigned  short					usSeqNo;			//  2007/05/02
	 char								reserved1[2];		//  				 
#endif 


	 //
	 extern  "C"  int  AT_MSG_HEAD_hton(__int64  i64StartTime_base,  QY_MSG_HEAD_h* pH, QY_MSG_HEAD_n* pN)
	 {
		 unsigned  char* tmp_p;
		 int  tmpLen;

		 //
		 //__int64  i64StartTime_base = 0;


		 //
#ifdef  __USE_old_msgHead_n__  

		 //memcpy(&tmpHead, &pIoContext->msgHead, sizeof(tmpHead));
		 pN->usCode  =  qyhtons(pH->usCode);
		 pN->ucFlg = pH->ucFlg;
		 pN->uiLen  =  qyhtonl(pH->uiLen);
		 pN->i64StartTime  =  qyhtonl64(pH->i64StartTime);
		 pN->uiTranNo  =  qyhtonl(pH->uiTranNo);
		 pN->usSeqNo=qyhtons(pH->usSeqNo);

#else 
		 //
		 if (0) {
			 tmp_p = pN->usCode_buf;
			 M_ton_short(pH->usCode, tmp_p, tmpLen);
			 //
			 tmp_p = pN->ucFlg_buf;
			 M_ton_byte(pH->ucFlg, tmp_p, tmpLen);
		 }
		 else {
			 tmp_p = pN->ucFlg_buf;
			 M_ton_byte(pH->ucFlg, tmp_p, tmpLen);
			 //
			 tmp_p = pN->usCode_buf;
			 M_ton_short(pH->usCode, tmp_p, tmpLen);
		 }
		 //
		 tmp_p = pN->uiLen_buf;
		 M_ton_long(pH->uiLen, tmp_p, tmpLen);
		 //
		 int  l3_elapse = pH->i64StartTime - i64StartTime_base;
		 athtonl3(l3_elapse, (unsigned  char*)pN->l3_elapse_buf, sizeof(pN->l3_elapse_buf));
		 //
		 tmp_p = pN->uiTranNo_buf;
		 M_ton_long(pH->uiTranNo, tmp_p, tmpLen);
		 //
		 tmp_p = pN->usSeqNo_buf;
		 M_ton_short(pH->usSeqNo, tmp_p, tmpLen);

		 //
#ifdef  __USE_dbg_i64StartTime__
		 tmp_p = (unsigned  char  *  )pN->dbg_i64StartTime_buf;
		 M_ton_l64(pH->i64StartTime, tmp_p, tmpLen);
#endif 

		 //
		 if (0) {
			 //
			 if (!pH->i64StartTime) {
				 int  ii = 0;
			 }
			 //
			 TCHAR  tBuf[128];
			 _sntprintf(tBuf, mycountof(tBuf), _T("AT_MSG_HEAD_hton: pH->i64StartTime %I64u, StartTime_base %I64u, l3 %d\n"), pH->i64StartTime, i64StartTime_base, l3_elapse);
			 OutputDebugString((TCHAR*)tBuf);
			 //
			 showInfo_open0(0, 0, tBuf);

		 }


#endif 

		 //
		 return  0;
	 }


#if  0
	 typedef  struct  __qyMsgHead_n_t {

		 //
		 unsigned  char						usCode_buf[2];				// 
		 unsigned  char						ucFlg_buf[1];				//  2007/04/22
		 unsigned  char						uiLen_buf[4];				//
		 char								i64StartTime_elapse_buf[3];		//  2007/05/07, 
		 unsigned  char						uiTranNo_buf[4];			//  2007/05/02
		 unsigned  char						usSeqNo_buf[2];			//  2007/05/02


	 }		 QY_MSG_HEAD_n;
#endif 

	 //
	 extern  "C"  int  AT_MSG_HEAD_ntoh(__int64  i64StartTime_base,  QY_MSG_HEAD_n* pN, QY_MSG_HEAD_h* pH)
	 {
		 //
		 unsigned  char* tmp_p;
		 int  tmpLen;

		 //
		 //__int64  i64StartTime_base = 0;


		 //
#ifdef  __USE_old_msgHead_n__  

		 pH->usCode  =  qyntohs(pN->usCode);
		 pH->ucFlg = pN->ucFlg;
		 pH->uiLen = qyntohl(pN->uiLen);
		 pH->i64StartTime  =  qyntohl64(pN->i64StartTime);	//  2007/05/07
		 pH->uiTranNo  =  qyntohl(pN->uiTranNo);
		 pH->usSeqNo  =  qyntohs(pN->usSeqNo);

#else
		 //
		 if (0) {
			 tmp_p = pN->usCode_buf;
			 M_toh_short(tmp_p, pH->usCode, tmpLen);
			 //
			 tmp_p = pN->ucFlg_buf;
			 M_toh_byte(tmp_p, pH->ucFlg, tmpLen);
		 }
		 else {
			 tmp_p = pN->ucFlg_buf;
			 M_toh_byte(tmp_p, pH->ucFlg, tmpLen);
			 //
			 tmp_p = pN->usCode_buf;
			 M_toh_short(tmp_p, pH->usCode, tmpLen);

		 }
		 //
		 tmp_p = pN->uiLen_buf;
		 M_toh_long(tmp_p, pH->uiLen, tmpLen);
		 tmp_p = (unsigned  char  * )pN->l3_elapse_buf;
		 int  l3;
		 l3  =  atntohl3(tmp_p, sizeof(pN->l3_elapse_buf));
		 //
		 pH->l3_elapse = l3;
		 //
		 pH->i64StartTime = i64StartTime_base + l3;
		 //
		 tmp_p = pN->uiTranNo_buf;
		 M_toh_long(tmp_p, pH->uiTranNo, tmpLen);
		 //
		 tmp_p = pN->usSeqNo_buf;
		 M_toh_short(tmp_p, pH->usSeqNo, tmpLen);

		 //
		 __int64  l64;  l64 = 0;
		 //
#ifdef  __USE_dbg_i64StartTime__
		 tmp_p = (unsigned  char  *  )pN->dbg_i64StartTime_buf;
		 M_toh_l64(tmp_p, l64, tmpLen);
		 if (pH->i64StartTime != l64) {
			 TCHAR  tBuf[128];
			 _sntprintf(tBuf, mycountof(tBuf), _T("AT_MSG_HEAD_ntoh err: pH->i64StartTime %I64u isnot ok, StartTime_base %I64u, l3 %d, dbg_st %I64u\n"),  pH->i64StartTime,  i64StartTime_base,  l3,  l64   );
			 OutputDebugString((TCHAR *)tBuf);
			 //
			 showInfo_open0(0, 0, tBuf);
		 }
		 pH->dbg_i64StartTime = l64;
#endif 
		 
		 //
#ifdef  __DEBUG__
		 if  (  0  )
		 {
			 TCHAR  tBuf[128];
			 _sntprintf(tBuf, mycountof(tBuf), _T("ntoh: l3 %d, (%d,%d,%d), base %I64u,  startTime %I64u, tn %d"), pH->l3_elapse,  
				 (int)(byte)pN->l3_elapse_buf[0], (int)(byte)pN->l3_elapse_buf[1],(int)(byte)pN->l3_elapse_buf[2],
				 i64StartTime_base,  pH->i64StartTime, pH->uiTranNo);
			 if (isUcFlgResp(pH->ucFlg))  _sntprintf(tBuf, mycountof(tBuf), _T("%s resp"), tBuf);
			 showInfo_open0(0, 0, tBuf);
		 }
#endif 
		 

		 //
#endif 

		 //
		 return  0;
	 }






	 //
	 extern  "C"  int  atntohCfgItem(char* p, int size, QY_CFGITEM_ntoh_U * pItem)
	 {
		 int				len = 0;
		 int				headLen = sizeof(short) + sizeof(atbyte);// sizeof(QY_CFGITEM);
		 int				dataLen = 0;

		 //
		 char* tmp_p;
		 int  tmpLen;

		 //
		 tmp_p = p;
		 tmpLen = 0;

		 //  pItem->cfgId  =  qyntohs(  pItem->cfgId  );
		 //  pItem->dataType  =  qyntohs(  pItem->dataType  );
		 memset(pItem, 0, sizeof(*pItem));
		 //memcpy(pItem, p, sizeof(QY_CFGITEM));
		 //MACRO_ntohs(pItem->head.cfgId);
		 //MACRO_ntohs(pItem->head.dataType);
#ifdef  __USE_atCommVer_1__
		 M_toh_short(tmp_p, pItem->head.cfgId, tmpLen);
		 M_toh_atbyte(tmp_p, pItem->head.dataType, tmpLen);		
#else
		 if (0) {
			 M_toh_atbyte(tmp_p, pItem->head.dataType, tmpLen);
			 M_toh_short(tmp_p, pItem->head.cfgId, tmpLen);
		 }
		 else {
			 int  tmp_iDataType = 0;
			 unsigned  short  tmp_usCfgId = 0;
			 tmpLen = toh_cfgHead(tmp_p, size, &tmp_iDataType, &tmp_usCfgId);
			 if (tmpLen < 0) {
				 return  -1;
			 }
			 pItem->head.dataType = tmp_iDataType;
			 pItem->head.cfgId = tmp_usCfgId;
			 //
			 tmp_p += tmpLen;
			 //
			 headLen = tmpLen;
		 }
#endif 

		 //
		 switch (pItem->head.dataType) {
		 case  CONST_qyDataType_long: {

			 dataLen = 4;
			 //memcpy(((char*)pItem) + headLen, p + headLen, dataLen);

			 QY_CFGITEM_LONG* pLong = (QY_CFGITEM_LONG*)pItem;

			 //  pLong->ulVal  =  qyntohl(  pLong->ulVal  );
			 //MACRO_ntohl(pLong->ulVal);
			 M_toh_long(tmp_p, pLong->ulVal, tmpLen);

			 len = headLen + 4;
		 }
									break;
		 case  CONST_qyDataType_char: {

			 dataLen = 1;
			 //memcpy(((char*)pItem) + headLen, p + headLen, dataLen);

			 QY_CFGITEM_CHAR* pChar = (QY_CFGITEM_CHAR*)pItem;
			 //
			 M_toh_byte(tmp_p, pChar->ucVal, tmpLen);
			 //
			 len = headLen + 1;
			 //
		 }
									break;
		 case  CONST_qyDataType_short: {

			 dataLen = 2;
			 //memcpy(((char*)pItem) + headLen, p + headLen, dataLen);

			 QY_CFGITEM_SHORT* pShort = (QY_CFGITEM_SHORT*)pItem;
			 //
			 //MACRO_ntohs(pShort->usVal);
			 M_toh_short(tmp_p, pShort->usVal, tmpLen);

			 len = headLen + 2;
		 }
									 break;
		 case  CONST_qyDataType_l64: {

			 dataLen = 8;
			 //memcpy(((char*)pItem) + headLen, p + headLen, dataLen);

			 QY_CFGITEM_L64* pL64 = (QY_CFGITEM_L64*)pItem;
			 //
			 //MACRO_ntohl64(*(__int64*)pL64->buf_l64Val);
			 __int64  tmpL64;
			 M_toh_l64(tmp_p, tmpL64, tmpLen);
			 memcpy(pL64->buf_l64Val, &tmpL64, sizeof(__int64));

			 len = headLen + 8;
		 }
								   break;
		 case  CONST_qyDataType_data:
		 case  CONST_qyDataType_str:
		 case  CONST_qyDataType_utf8Str: {

			 dataLen = 2;
			 //memcpy(((char*)pItem) + headLen, p + headLen, dataLen);

			 QY_CFGITEM_STR* pStr = (QY_CFGITEM_STR*)pItem;

			 M_toh_short(tmp_p, pStr->len, tmpLen);
				 pItem->data.p = p + headLen + dataLen;

			 //  pStr->len  =  qyntohs(  pStr->len  );
			 //MACRO_ntohs(pStr->len);


			 //  len  =  2  +  2  +  2  +  pStr->len;
			 unsigned  short  tmp_us;
			 memcpy(&tmp_us, &pStr->len, sizeof(short));
			 len = headLen + 2 + tmp_us;
		 }
									   break;
		 case  CONST_qyDataType_lData: {		//  2008/04/01

			 dataLen = 4;
			 //memcpy(((char*)pItem) + headLen, p + headLen, dataLen);
			 
			 QY_CFGITEM_LDATA* pLData = (QY_CFGITEM_LDATA*)pItem;
			 
			 M_toh_long(tmp_p, pLData->ulLen, tmpLen);
			 pItem->lData.p = p + headLen + dataLen;

			 //
			 //MACRO_ntohl(pLData->ulLen);

			 //  len  =  2  +  2  +  4  +  pLData->ulLen;
			 unsigned  long  tmp_ul;
			 memcpy(&tmp_ul, &pLData->ulLen, sizeof(long));
			 len = headLen + 4 + tmp_ul;
		 }
									 break;
		 default:
			 len = 0;
			 break;
		 }


		 return  len;

	 }

	 //
	 int  atStream2Data(char** pCfgsBuf_usable, unsigned  int* pSize_usable, PF_handler_stream2Data  pf_filter, PF_handler_stream2Data  pf, void* p0, void* p1)
	 {
		 //

		 //
		 int						iErr = -1;
		 unsigned  int			len;
		 char* ptr = 0;
		 QY_CFGITEM_ntoh_U		item_ntoh_U;
		 QY_CFGITEM_ntoh_U* pItem = NULL;
		 //  QY_CFGITEM_WSTR			itemWStr;
		 CQyString				wStr;
		 //
		 CTX_stream2Data			ctx;
		 memset(&ctx, 0, sizeof(ctx));
		 //
		 int						nStarts = 0;
		 //unsigned  int			uiStreamIds[5]	=	{	0,	};
		 int						tmpiRet;
		 char* cfgsBuf = NULL;
		 unsigned  int			size = 0;
		 unsigned  short			tmp_cfgId;			//  2010/04/08
		 unsigned  short			tmp_dataType;		//  2010/04/08

		 if (!pCfgsBuf_usable || !pSize_usable)  return  -1;

		 cfgsBuf = *pCfgsBuf_usable;
		 size = *pSize_usable;
		 //
		 if (!cfgsBuf || !size || !pf_filter || !pf)  return  -1;

		 len = 0;
		 ptr = cfgsBuf;
		 for (; size; ) {
#if  0
			 pItem = (QY_CFGITEM*)ptr;
			 len = qyntohCfgItem(pItem);		//  这里要注意：这里qyntohCfgItem(  )返回的是转换前的字节流长度。和qyhtonCfgItem(  )返回的不同
#endif
			 //
			 len = atntohCfgItem(ptr, size, &item_ntoh_U);		//  这里要注意：这里qyntohCfgItem(  )返回的是转换前的字节流长度。和qyhtonCfgItem(  )返回的不同
			 pItem = &item_ntoh_U;

			 if (len <= 0 || len > size)  goto  errLabel;

			 memcpy(&tmp_cfgId, &pItem->head.cfgId, sizeof(short));			//  2010/04/08
			 memcpy(&tmp_dataType, &pItem->head.dataType, sizeof(short));		//  2010/04/08

			 ptr += len;  size -= len;

			 if (!nStarts) {
				 if (tmp_cfgId != CONST_qnmCfgId_start)  goto  errLabel;
				 //
				 //if (tmp_dataType != CONST_qyDataType_long)  goto  errLabel;
				 //
			 }

			 if (tmp_cfgId == CONST_qnmCfgId_start) {

				 nStarts++;
				 if (nStarts > mycountof(ctx.uiStreamIds))  goto  errLabel;

				 //  uiStreamId  =  (  (  QY_CFGITEM_LONG  *  )pItem  )->ulVal;
				 long uiSteamId;
				 getFieldData_long(pItem, &uiSteamId);
				 //memcpy(&ctx.uiStreamIds[nStarts - 1], &((QY_CFGITEM_LONG*)pItem)->ulVal, sizeof(ctx.uiStreamIds[0]));
				 memcpy(&ctx.uiStreamIds[nStarts - 1], &uiSteamId, sizeof(ctx.uiStreamIds[0]));
				 //
				 ctx.index_streamId = nStarts - 1;
				 if ((tmpiRet = pf(&ctx, p0, p1, ctx.uiStreamIds[nStarts - 1], pItem))) {		//  这里有利于处理结构起始时初始化，2007/08/01
					 iErr = tmpiRet;  goto  errLabel;
				 }
				 continue;
			 }

			 if (tmp_cfgId == CONST_qnmCfgId_null) {
				 //
				 ctx.index_streamId = nStarts - 1;
				 if ((tmpiRet = pf(&ctx, p0, p1, ctx.uiStreamIds[nStarts - 1], pItem))) {		//  这里有利于处理结构结束时做结尾工作，2007/08/01
					 iErr = tmpiRet;  goto  errLabel;
				 }
				 nStarts--;
				 if (!nStarts)  break;
				 continue;
			 }

			 if (tmp_dataType == CONST_qyDataType_utf8Str) {

				 //  #define		CONST_bufSize_utf8Str		4096
#define		CONST_bufSize_utf8Str		32  *  1024		//  2010/12/05

				 CQyMalloc				mallocObj_buf;
				 int					bufSize = CONST_bufSize_utf8Str;
				 char* pBuf = NULL;

				 if (pItem->data.len + 1 > CONST_bufSize_utf8Str) {
					 traceLog((TCHAR*)_T("stream2Data: utf8 too long string"));
					 goto  errLabel;
				 }
				 bufSize = pItem->data.len + 1;
				 pBuf = mallocObj_buf.mallocf(bufSize);
				 if (!pBuf)  goto  errLabel;

				 //
#if  0
				 QY_CFGITEM_STR* pItemStr = (QY_CFGITEM_STR*)pItem;
				 unsigned  short  tmp_len;
				 memcpy(&tmp_len, &pItemStr->len, sizeof(short));

				 itemWStr.cfgId = tmp_cfgId;
				 safeStrnCpy(pItemStr->str, pBuf, min(tmp_len + 1, bufSize));
				 if (!myUtf82WChar(pBuf, itemWStr.wStr, mycountof(itemWStr.wStr)))  goto  errLabel;
				 itemWStr.len = min(wcslen(itemWStr.wStr), mycountof(itemWStr.wStr) - 1);
				 itemWStr.dataType = CONST_qyDataType_wStr;
				 pItem = (QY_CFGITEM*)&itemWStr;
#endif
				 safeStrnCpy(pItem->data.p, pBuf, min(pItem->data.len + 1, bufSize));
				 wStr = CQyString(pBuf);
				 pItem->wStr.dataType = CONST_qyDataType_wStr;
				 pItem->wStr.len = wStr.GetLength();
				 pItem->wStr.pWStr = (WCHAR*)wStr.GetBuffer(0);
			 }
			 ctx.index_streamId = nStarts - 1;
			 if ((tmpiRet = pf_filter(&ctx, p0, p1, ctx.uiStreamIds[nStarts - 1], pItem))) {		//  2008/12/03, 主要是对pItem里的数据进行过滤。不是对结果的
				 iErr = tmpiRet;  goto  errLabel;
			 }
			 ctx.index_streamId = nStarts - 1;
			 if ((tmpiRet = pf(&ctx, p0, p1, ctx.uiStreamIds[nStarts - 1], pItem))) {
				 iErr = tmpiRet;  goto  errLabel;
			 }
		 }

		 iErr = 0;
	 errLabel:

		 if (!iErr) {
			 *pCfgsBuf_usable = ptr;
			 *pSize_usable = size;
		 }

		 return  iErr;
	 }


