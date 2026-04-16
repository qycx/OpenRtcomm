
//
#ifndef  __aisCommProc_h__
#define  __aisCommProc_h__	//  {

#include <cstdint>

//
#include	"myTypes.h"

//
#include	"ancCommProc_open.h"
#include	"atMsgFunc.h"










//
//
#ifdef  __USE_atbyte_short__
#define		hton_atbyte(x,n_b)		n_b  =  qyhtons(x);
#define		ntoh_atbyte(n_b,x)		x  =  qyntohs(n_b);
#else 
#define  hton_atbyte(b, n_b)		n_b  =  b;
#define  ntoh_atbyte(n_b,x)			x  =  (n_b);
#endif 

//
#define		M_ton_atbyte(b1,ptr,len)  {  atbyte n_b1;  hton_atbyte(b1,n_b1);  memcpy(  ptr,  &n_b1, sizeof(atbyte)  );  len  =  sizeof(atbyte);  ptr  +=  len;  }
//
#define		M_ton_byte(b1,ptr,len)  {  byte n_b1;  n_b1  =  b1;  memcpy(  ptr,  &n_b1, sizeof(byte)  );  len  =  sizeof(byte);  ptr  +=  len;  }
//
#define		M_ton_short(s,ptr,len)  {  short n_s;  n_s  =  qyhtons(s);  memcpy(  ptr,  &n_s, 2  );  len  =  2;  ptr  +=  len;  }
#define		M_ton_long(l,ptr,len)  {  long n_l;  n_l  =  qyhtonl(l);  memcpy(  ptr,  &n_l, 4  );  len  =  4;  ptr  +=  len;  }
#define		M_ton_l64(l64,ptr,len)  {  __int64 n_l64;  n_l64  =  qyhtonl64(l64);  memcpy(  ptr,  &n_l64, 8  );  len  =  8;  ptr  +=  len;  }

//
#define		M_ton_data(data,dataLen, ptr,len)  {  memcpy(ptr,data,dataLen);  len=dataLen;  ptr+=  len; }


/////////////////////////////////
#define		M_toh_atbyte(ptr,b1, len)  {  atbyte n_b1;  memcpy(  &n_b1, ptr,  sizeof(atbyte)  );  ntoh_atbyte(n_b1,b1);  len  =  sizeof(atbyte);  ptr  +=  len;  }
//
#define		M_toh_byte(ptr,b1,len)  {  byte n_b1;  memcpy(  &n_b1, ptr, sizeof(byte)  );  b1  =  n_b1;  len  =  sizeof(byte);  ptr  +=  len;  }
#define		M_toh_short(ptr,s,len)  {  short n_s;  memcpy(  &n_s, ptr, 2  );  s  =  qyntohs(n_s);  len  =  2;  ptr  +=  len;  }
#define		M_toh_long(ptr,l,len)  {  long n_l;  memcpy(  &n_l, ptr, 4  );  l  =  qyntohl(n_l);  len  =  4;  ptr  +=  len;  }
#define		M_toh_l64(ptr,l64,len)  {  __int64 n_l64;  memcpy(  &n_l64, ptr, 8  );  l64  =  qyntohl64(n_l64);  len  =  8;  ptr  +=  len;  }



//
typedef  struct  __atCfgItem_t {
	unsigned  short								cfgId;
	atbyte										dataType;
}		 AT_CFGITEM;


typedef  struct  __atCfgItemLong_t {
	unsigned  short								cfgId;
	atbyte										dataType;
	unsigned  long									ulVal;
}		 AT_CFGITEM_LONG;


typedef  struct  __atCfgItemL64_t {			//  ÒòÎª´Ó×Ö½ÚË³ÐòÉÏ£¬¿ÉÄÜ__int64ºÍunsigned  short²»ÄÜË³×Ö½Ú´æ·Å£¬¹ÊÖ»ÄÜÓÃÒ»¸öchar»º´æÀ´Ìæ»»
	unsigned  short								cfgId;
	atbyte										dataType;
	char											buf_l64Val[sizeof(__int64)];	//  unsigned  __int64								ui64Val;
}		 AT_CFGITEM_L64;


typedef  struct  __atCfgItemChar_t {			//  2007/08/05
	unsigned  short								cfgId;
	atbyte										dataType;
	unsigned  char									ucVal;
}		 AT_CFGITEM_CHAR;


typedef  struct  __atCfgItemShort_t {			//  2007/08/05
	unsigned  short								cfgId;
	atbyte										dataType;
	unsigned  short								usVal;
}		 AT_CFGITEM_SHORT;

//
#define		CONST_cntofStr_cfgItemStr			4096
#define		CONST_cntofWstr_cfgItemWStr			4096


//
typedef  struct  __atCfgItemStr_t {
	unsigned  short								cfgId;
	atbyte										dataType;
	unsigned  short								len;
	char											str[CONST_cntofStr_cfgItemStr];		//  2007/03/31, ½«»º³åµÄ³¤¶È±ä³¤ÁË
}		 AT_CFGITEM_STR;


typedef  struct  __atCfgItemWStr_t {				//  2007/03/31
	unsigned  short								cfgId;
	atbyte										dataType;
	unsigned  short								len;
	WCHAR											wStr[CONST_cntofWstr_cfgItemWStr];
}		 AT_CFGITEM_WSTR;


#define		CONST_bufSize_cfgItemData							32  *  1024		//  2007/03/31, ½«»º³åµÄ³¤¶È±ä³¤ÁË
#define		CONST_bufSize_cfgItemLData							1024  *  1024	//  2008/03/22

typedef  struct  __atCfgItemData_t {
	unsigned  short								cfgId;
	atbyte										dataType;
	unsigned  short								len;
	char											buf[CONST_bufSize_cfgItemData + 1];
}		 AT_CFGITEM_DATA;

typedef  struct  __atCfgItemLData_t {
	unsigned  short								cfgId;
	atbyte										dataType;
	unsigned  long									ulLen;
	char											buf[CONST_bufSize_cfgItemLData + 1];
}		 AT_CFGITEM_LDATA;



//
 int  atData2Stream(int  iDataType, unsigned  short  usCfgId, void* orgData, unsigned  int  orgDataSize, char** pptr_usable, unsigned  int* pSize_usable);

 //
 int  atStream2Data(char** pCfgsBuf_usable, unsigned  int* pSize_usable, PF_handler_stream2Data  pf_filter, PF_handler_stream2Data  pf, void* p0, void* p1);


 
 //
 int32_t int24_to_int32(int32_t int24);
 bool int32_to_int24(int32_t int32, int32_t* int24_result);



 //
 extern  "C"  int  athtonl3(int  x, unsigned  char* buf, int  bufSize);
 extern  "C"  int  atntohl3(unsigned  char* buf, int  bufSize);

 //
 extern  "C"  int  AT_MSG_HEAD_hton(__int64  i64StartTime_base,  QY_MSG_HEAD_h* pH, QY_MSG_HEAD_n* pN);
 extern  "C"  int  AT_MSG_HEAD_ntoh(__int64  i64StartTime_base,  QY_MSG_HEAD_n* pN, QY_MSG_HEAD_h* pH);

 //
 extern  "C"  int  atntohCfgItem(char* p, int size, QY_CFGITEM_ntoh_U* pItem);


 //
#endif  //  }

