
#include	"stdafx.h"

#include	"qyPrecomp.h"

#include	<Winsock2.h>

#include	<windows.h>
#include	<stddef.h>
#include	<tchar.h>
#include	<stdio.h>
#include	<time.h>
#include	<stdlib.h>

#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmPcComm.h"
#include	"qnmAssetsCommProc.h"
#include	"qnmSpCommProc.h"
#include	"qwmNetworkStatusCommProc.h"
#include	"qyTCharCommProc.h"
#include	"qnmCustom.h"
#include	"tmpLib.h"
#include	"tmpCeLib.h"
#include	"qySyncCommProc.h"

//




/*     ±¾ÎÄ¼þ´æ·ÅÎªÔÚËùÓÐµÄqyNetMcÏîÄ¿ÖÐ¹²ÓÃµÄº¯Êý£¬
   °üÀ¨qwmSvrºÍServer¶ËµÄ³ÌÐò£¬Ðë×¢ÒâC¿âº¯Êý²»ÄÜÔÚ´Ëµ÷ÓÃ£¬
   ²»ÓÃÔÚqwmSvrÖÐµÄÒ»Ð©º¯Êý¿É¿¼ÂÇ·ÅÔÚqnmCommProc1.cppÖÐ
 */


  extern  "C"  DWORD64  qyhtonl64(  DWORD64  x  )
{
	 unsigned  char	buf[8];

	 buf[0]  =  (  unsigned  char  )(  (  x  &  0xff00000000000000  )  >>  56  );
	 buf[1]  =  (  unsigned  char  )(  (  x  &    0xff000000000000  )  >>  48  );
	 buf[2]  =  (  unsigned  char  )(  (  x  &      0xff0000000000  )  >>  40  );
	 buf[3]  =  (  unsigned  char  )(  (  x  &		  0xff00000000  )  >>  32  );
	 buf[4]  =  (  unsigned  char  )(  (  x  &		    0xff000000  )  >>  24  );
	 buf[5]  =  (  unsigned  char  )(  (  x  &            0xff0000  )  >>  16  );
	 buf[6]  =  (  unsigned  char  )(  (  x  &              0xff00  )  >>  8   );
	 buf[7]  =  (  unsigned  char  )(  (  x  &                0xff  )  );


	 return  *(  DWORD64  *  )buf;
}

 extern  "C"  DWORD64  qyntohl64(  DWORD64  x  )
{
	 DWORD64				l64Ret  =  0;
	 DWORD64				l64		=	0;
	 unsigned  char			buf[sizeof(  x  )];
	 int					i;

	 memcpy(  buf,  &x,  sizeof(  x  )  );
	 //  l64Ret  =  (  buf[0]  <<  56  )  +  (  buf[1]  <<  48  )  +  (  buf[2]  <<  40  )  +  (  buf[3]  <<  32  )
	 //	 +  (  buf[4]  <<  24  )  +  (  buf[5]  <<  16  )  +  (  buf[6]  <<  8  )  +  buf[7];;
	 for  (  i  =  0;  i  <  sizeof(  x  );  i  ++   )  {
		  l64  =  buf[i];
		  l64Ret  +=  l64  <<  (  (  sizeof(  x  )  -  1  -  i  )  *  8  );
	 }

	 return  l64Ret;
}



 //  ·µ»Ø×ª»¯ºóµÄ×Ö½ÚÁ÷³¤¶È, 0 ±íÊ§°Ü
 extern  "C"  int  qyhtonCfgItem(  QY_CFGITEM  *  pItem  )
{
	 int  len  =  0;
	 
	 pItem->cfgId  =  qyhtons(  pItem->cfgId  );
	 
	 switch  (  pItem->dataType  )  {
			 case  CONST_qyDataType_long:  {
				   QY_CFGITEM_LONG  *  pLong  =  (  QY_CFGITEM_LONG  *  )pItem;

				   len  =  2  +  2  +  4;
				   pLong->dataType  =  qyhtons(  pLong->dataType  );
				   pLong->ulVal  =  qyhtonl(  pLong->ulVal  );
				 	}
				   break;
			 case  CONST_qyDataType_char:  {
				   QY_CFGITEM_CHAR	*	pChar	=	(  QY_CFGITEM_CHAR  *  )pItem;
				   //
				   len  =  2  +  2  +  1;
				   MACRO_htons(  pChar->dataType  );
				   //
					}
				   break;
			 case  CONST_qyDataType_short:  {
				   QY_CFGITEM_SHORT  *  pShort  =  (  QY_CFGITEM_SHORT  *  )pItem;
				   //
				   len  =  2  +  2  +  2;
				   MACRO_htons(  pShort->dataType  );
				   MACRO_htons(  pShort->usVal  );
					}
				   break;
			 case  CONST_qyDataType_l64:  {
				   QY_CFGITEM_L64	*	pL64  =  (  QY_CFGITEM_L64  *  )pItem;
				   //
				   len  =  2  +  2  +  8;
				   MACRO_htons(  pL64->dataType  );
				   MACRO_htonl64(  *(  __int64  *  )pL64->buf_l64Val  );
				   //				   
					}
				   break;
			 case  CONST_qyDataType_data:
			 case  CONST_qyDataType_str:  
			 case  CONST_qyDataType_utf8Str:  {
				   QY_CFGITEM_STR  *  pStr  =  (  QY_CFGITEM_STR  *  )pItem;
				   
				   len  =  2  +  2  +  2  +  pStr->len;
				   pStr->dataType  =  qyhtons(  pStr->dataType  );
				   pStr->len  =  qyhtons(  pStr->len  );
					}
				   break;
			 case  CONST_qyDataType_lData:  {		//  2008/04/01
				   QY_CFGITEM_LDATA  *  pLData  =  (  QY_CFGITEM_LDATA  *  )pItem;

				   len  =  2  +  2  +  4  +  pLData->ulLen;
				   MACRO_htons(  pLData->dataType  );
				   MACRO_htonl(  pLData->ulLen  );
				   }
				   break;
			 default:
					 len  =  0;
					 break;
	 }

	 return  len;

}

 //  
#if  0
 extern  "C"  int  qyntohCfgItem(  QY_CFGITEM  *  pItem  )
{
	 int				len			=	0;

	 //  pItem->cfgId  =  qyntohs(  pItem->cfgId  );
	 //  pItem->dataType  =  qyntohs(  pItem->dataType  );
	 MACRO_ntohs(  pItem->cfgId  );
	 MACRO_ntohs(  pItem->dataType  );

	 unsigned  short	dataType	=	0; 
	 memcpy(  &dataType,  &pItem->dataType,  sizeof(  short  )  );
	 switch  (  dataType  )  {
			 case  CONST_qyDataType_long:  {
				   QY_CFGITEM_LONG  *  pLong  =  (  QY_CFGITEM_LONG  *  )pItem;

				   //  pLong->ulVal  =  qyntohl(  pLong->ulVal  );
				   MACRO_ntohl(  pLong->ulVal  );

				   len  =  2  +  2  +  4;
					}
				   break;
			 case  CONST_qyDataType_char:  {
				   QY_CFGITEM_CHAR	*	pChar	=	(  QY_CFGITEM_CHAR  *  )pItem;
				   //
				   len  =  2  +  2  +  1;
				   //
					}
				   break;
			 case  CONST_qyDataType_short:  {
				   QY_CFGITEM_SHORT  *  pShort  =  (  QY_CFGITEM_SHORT  *  )pItem;
				   //
				   MACRO_ntohs(  pShort->usVal  );

				   len  =  2  +  2  +  2;
					}
				   break;
			 case  CONST_qyDataType_l64:  {
				   QY_CFGITEM_L64	*	pL64  =  (  QY_CFGITEM_L64  *  )pItem;
				   //
				   MACRO_ntohl64(  *(  __int64  *  )pL64->buf_l64Val  );		

				   len  =  2  +  2  +  8;
					}
				   break;
			 case  CONST_qyDataType_data:
			 case  CONST_qyDataType_str:  
			 case  CONST_qyDataType_utf8Str:  {
				   QY_CFGITEM_STR  *  pStr  =  (  QY_CFGITEM_STR  *  )pItem;

				   //  pStr->len  =  qyntohs(  pStr->len  );
				   MACRO_ntohs(  pStr->len  );

				   //  len  =  2  +  2  +  2  +  pStr->len;
				   unsigned  short  tmp_us;	
				   memcpy(  &tmp_us,  &pStr->len,  sizeof(  short  )  );
				   len  =  2  +  2  +  2  +  tmp_us;
					}
				   break;
			 case  CONST_qyDataType_lData:  {		//  2008/04/01
				   QY_CFGITEM_LDATA  *  pLData  =  (  QY_CFGITEM_LDATA  *  )pItem;
				   //
				   MACRO_ntohl(  pLData->ulLen  );

				   //  len  =  2  +  2  +  4  +  pLData->ulLen;
				   unsigned  long  tmp_ul;
				   memcpy(  &tmp_ul,  &pLData->ulLen,  sizeof(  long  )  );
				   len  =  2  +  2  +  4  +  tmp_ul;
				   }
				   break;
			 default:
				    len  =  0;
					break;
	 }

	 return  len;

}
#endif

 //  2010/07/09
  extern  "C"  int  qyntohCfgItem(  char  *  p,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int				len			=	0;
	 int				headLen		=	sizeof(  QY_CFGITEM  );
	 int				dataLen		=	0;

	 //  pItem->cfgId  =  qyntohs(  pItem->cfgId  );
	 //  pItem->dataType  =  qyntohs(  pItem->dataType  );
	 memset(  pItem,  0,  sizeof(  *pItem  )  );
	 memcpy(  pItem,  p,  sizeof(  QY_CFGITEM  )  );
	 MACRO_ntohs(  pItem->head.cfgId  );
	 MACRO_ntohs(  pItem->head.dataType  );

	 switch  (  pItem->head.dataType  )  {
			 case  CONST_qyDataType_long:  {
				   
				   dataLen  =  4;
				   memcpy(  (  (  char  *  )pItem  )  +  headLen,  p  +  headLen,  dataLen  );

				   QY_CFGITEM_LONG  *  pLong  =  (  QY_CFGITEM_LONG  *  )pItem;

				   //  pLong->ulVal  =  qyntohl(  pLong->ulVal  );
				   MACRO_ntohl(  pLong->ulVal  );

				   len  =  2  +  2  +  4;
					}
				   break;
			 case  CONST_qyDataType_char:  {
				   
				   dataLen  =  1;
				   memcpy(  (  (  char  *  )pItem  )  +  headLen,  p  +  headLen,  dataLen  );

				   QY_CFGITEM_CHAR	*	pChar	=	(  QY_CFGITEM_CHAR  *  )pItem;
				   //
				   len  =  2  +  2  +  1;
				   //
					}
				   break;
			 case  CONST_qyDataType_short:  {

				   dataLen  =  2;
				   memcpy(  (  (  char  *  )pItem  )  +  headLen,  p  +  headLen,  dataLen  );

				   QY_CFGITEM_SHORT  *  pShort  =  (  QY_CFGITEM_SHORT  *  )pItem;
				   //
				   MACRO_ntohs(  pShort->usVal  );

				   len  =  2  +  2  +  2;
					}
				   break;
			 case  CONST_qyDataType_l64:  {

				   dataLen  =  8;
				   memcpy(  (  (  char  *  )pItem  )  +  headLen,  p  +  headLen,  dataLen  );

				   QY_CFGITEM_L64	*	pL64  =  (  QY_CFGITEM_L64  *  )pItem;
				   //
				   MACRO_ntohl64(  *(  __int64  *  )pL64->buf_l64Val  );		

				   len  =  2  +  2  +  8;
					}
				   break;
			 case  CONST_qyDataType_data:
			 case  CONST_qyDataType_str:  
			 case  CONST_qyDataType_utf8Str:  {
				   
				   dataLen  =  2;
				   memcpy(  (  (  char  *  )pItem  )  +  headLen,  p  +  headLen,  dataLen  );
				   pItem->data.p  =  p  +  headLen  +  dataLen;

				   QY_CFGITEM_STR  *  pStr  =  (  QY_CFGITEM_STR  *  )pItem;

				   //  pStr->len  =  qyntohs(  pStr->len  );
				   MACRO_ntohs(  pStr->len  );


				   //  len  =  2  +  2  +  2  +  pStr->len;
				   unsigned  short  tmp_us;	
				   memcpy(  &tmp_us,  &pStr->len,  sizeof(  short  )  );
				   len  =  2  +  2  +  2  +  tmp_us;
					}
				   break;
			 case  CONST_qyDataType_lData:  {		//  2008/04/01

				   dataLen  =  4;
				   memcpy(  (  (  char  *  )pItem  )  +  headLen,  p  +  headLen,  dataLen  );
				   pItem->lData.p  =  p  +  headLen  +  dataLen;

				   QY_CFGITEM_LDATA  *  pLData  =  (  QY_CFGITEM_LDATA  *  )pItem;
				   //
				   MACRO_ntohl(  pLData->ulLen  );

				   //  len  =  2  +  2  +  4  +  pLData->ulLen;
				   unsigned  long  tmp_ul;
				   memcpy(  &tmp_ul,  &pLData->ulLen,  sizeof(  long  )  );
				   len  =  2  +  2  +  4  +  tmp_ul;
				   }
				   break;
			 default:
				    len  =  0;
					break;
	 }


	 return  len;

}




/////////////
 QY_DMITEM  CONST_qnmStopMonTable_en[]  =  
{
	{  (  unsigned  char  )FALSE,			(TCHAR*)_T(  "²»Ð¶ÔØ"  ),				},
	{  (  unsigned  char  )TRUE,			(TCHAR*)_T(  "Ð¶ÔØ"  ),					},
	{	-1,									NULL,					},
};


 QY_DMITEM  CONST_qnmCfgRasCmdTable_en[]  =
{
	{	CONST_rasCmd_permitted,				(TCHAR*)_T(  "ÔÊÐí²¦ºÅ"  ),		(TCHAR*)_T(  CONST_rasCmdStr_permitted  ),			},
	{	CONST_rasCmd_prohibited,			(TCHAR*)_T(  "½ûÖ¹²¦ºÅ"  ),		(TCHAR*)_T(  CONST_rasCmdStr_prohibited  ),			},
	{	CONST_rasCmd_offlinePermitted,		(TCHAR*)_T(  "ÀëÏßÔÊÐí"  ),		(TCHAR*)_T(  CONST_rasCmdStr_offlinePermitted  ),	},
	{	-1,									NULL,												},
};
 
 QY_DMITEM  CONST_qnmRasCmdTable_en[]  =
{
	{	CONST_rasCmd_default,				(TCHAR*)_T(  "Default"  ),				},
	{	CONST_rasCmd_permitted,				(TCHAR*)_T(  "Permitted"  ),			},
	{	CONST_rasCmd_prohibited,			(TCHAR*)_T(  "Prohibited"  ),			},
	{	CONST_rasCmd_offlinePermitted,		(TCHAR*)_T(  "Offline permitted"  ),	},
	{	CONST_rasCmd_zdhmyx,				(TCHAR*)_T(  "Some phonenum permitted"  ),	},		
	{	-1,									NULL,				},
};

 QY_DMITEM  CONST_qnmRasCmdTable_cn[]  =
{
	{	CONST_rasCmd_default,				(TCHAR*)_T(  "缺省"  ),				},
	{	CONST_rasCmd_permitted,				(TCHAR*)_T(  "拨号允许"  ),			},
	{	CONST_rasCmd_prohibited,			(TCHAR*)_T(  "拨号阻断"  ),			},
	{	CONST_rasCmd_offlinePermitted,		(TCHAR*)_T(  "离线允许"  ),			},
	{	CONST_rasCmd_zdhmyx,				(TCHAR*)_T(  "允许特许号码"  ),		},		
	{	-1,									NULL,				},
};

/*
 QY_DMITEM	CONST_qnmDevCmdTable[]  =
{
	{	CONST_devCmd_permitted,				(TCHAR*)_T(  "ÔÊÐíÊ¹ÓÃ"  ),				},
	{	CONST_devCmd_prohibited,			(TCHAR*)_T(  "½ûÖ¹Ê¹ÓÃ"  ),				},
	{	-1,									NULL,					},

};


 QY_DMITEM  CONST_qnmUsbCmdTable[]  =
{
	{	CONST_devCmd_permitted,				(TCHAR*)_T(  "ÔÊÐíÊ¹ÓÃ"  ),				},
	#ifndef  __NOTSUPPORT_FILEMON__
		{	CONST_devCmd_permittedAndMon,		(TCHAR*)_T(  "ÔÊÐí²¢¼àÊÓ"  ),			},
	#endif
	{	CONST_devCmd_prohibited,			(TCHAR*)_T(  "½ûÖ¹Ê¹ÓÃ"  ),				},
	{	CONST_devCmd_restartToProhibit,		(TCHAR*)_T(  "ÖØÆð×è¶Ï"  ),				},		//  2005/06/22
	{	-1,									NULL,					},
};


 QY_DMITEM  CONST_qnmAutorunCmdTable[]  =	//  2007/02/13
{
	{	CONST_devCmd_none,					(TCHAR*)_T(  "Î´ÅäÖÃ"  ),				},		//  2007/02/13
	{	CONST_devCmd_permitted,				(TCHAR*)_T(  "ÔÊÐíÊ¹ÓÃ"  ),				},
	{	CONST_devCmd_prohibited,			(TCHAR*)_T(  "½ûÖ¹Ê¹ÓÃ"  ),				},
	{	-1,									NULL,					},
};

 //  2007/02/12
 
 QY_DMITEM  CONST_qnmNetShareCmdTable[]	=
{
	{	CONST_devCmd_permitted,				(TCHAR*)_T(  "ÔÊÐíÊ¹ÓÃ"  ),				},
	{	CONST_devCmd_prohibited,			(TCHAR*)_T(  "½ûÖ¹Ê¹ÓÃ"  ),				},
	{	-1,						},
};

*/

 QY_DMITEM  CONST_qnmDevCmdTable0_en[]	=		//  ÓÃÀ´»ã×ÜËùÓÐµÄÃüÁî£¬ÔÚÏÔÊ¾ÖÐÒ²·½±ã. 2005/06/22
{
	{	CONST_devCmd_permitted,				(TCHAR*)_T(  "permitted"  ),				},
	{	CONST_devCmd_prohibited,			(TCHAR*)_T(  "prohibited"  ),				},
	{	CONST_devCmd_restartToProhibit,		(TCHAR*)_T(  "restartToProhibit"  ),				},		//  2005/06/22
	{	CONST_devCmd_permittedAndLog,		(TCHAR*)_T(  "permittedAndLog"  ),				},
	{	CONST_devCmd_prohibitedCanReboot,	(TCHAR*)_T(  "prohibitedCanReboot"  ),			},			//  2011/08/28. 如果设备被锁住，那么可以重启操作系统

	{	CONST_devCmd_none,					(TCHAR*)_T(  "none"  ),				},		//  2007/02/13
	{	-1,									NULL,					},
};

 QY_DMITEM  CONST_fieldIdTable_en[]  =
{
	{	CONST_fieldId_yhlx,					(TCHAR*)_T(  "用户类型"  ),				},
	{	CONST_fieldId_syr,					(TCHAR*)_T(  "Username"  ),				},
	{	CONST_fieldId_bm,					(TCHAR*)_T(  "Department"  ),					},
	{	CONST_fieldId_dw,					(TCHAR*)_T(  "Company"  ),					},
	{	CONST_fieldId_bb,					(TCHAR*)_T(  "Local branch"  ),					},
	{	CONST_fieldId_zb,					(TCHAR*)_T(  "Group"  ),					},
	{	CONST_fieldId_qtdw,					(TCHAR*)_T(  "Other"  ),				},
	//
	{	CONST_fieldId_zcbh0,				(TCHAR*)_T(  "Asset no"  ),				},
	{	CONST_fieldId_zcbh1,				(TCHAR*)_T(  "Asset no1"  ),			},
	{	CONST_fieldId_zcbh2,				(TCHAR*)_T(  "Asset no2"  ),			},
	//  #define		CONST_fieldId_zcsm0								123
	{	CONST_fieldId_zcsm1,				(TCHAR*)_T(  "Asset note1"  ),			},
	{	CONST_fieldId_zcsm2,				(TCHAR*)_T(  "Asset note2"  ),			},
	{	CONST_fieldId_jqlx,					(TCHAR*)_T(  "Type"  ),				},
	{	CONST_fieldId_lxdh,					(TCHAR*)_T(  "Telephone"  ),				},
	{	CONST_fieldId_sydd,					(TCHAR*)_T(  "Address"  ),				},
	{	CONST_fieldId_zyyt,					(TCHAR*)_T(  "Use for"  ),				},
	{	CONST_fieldId_bz1,					(TCHAR*)_T(  "Remarks1"  ),				},
	{	CONST_fieldId_bz2,					(TCHAR*)_T(  "Remarks2"  ),				},
	//
	{	-1,									NULL,					},
};




 //  ¼ì²éÖÕ¶ËµÄÊÂ¼þÁÐ±í
 //  ÔÝÊ±ºÍÉÏÃæÒ»Ñù£¬²ÎÕÕ.hÀïµÄ¶¨Òå

 //  É¨ÃèÃüÁîÁÐ±í
 QY_DMITEM  CONST_nmsOpTable[]  =
{	
	{	CONST_nmsOp_snmpScan,		(TCHAR*)_T(  "snmpScan"  ),		},		//  È±Ê¡
	{	CONST_nmsOp_nbtScan,		(TCHAR*)_T(  "nbtScan"  ),		},
	{	-1,							NULL,			},
};


 //




 //
  QY_DMITEM	CONST_qyPlatformTable[]  =
{
#if  0
	{  CONST_qyPlatform_win32,		(TCHAR*)_T(  "Win32"  ),				},	//  2
	{  CONST_qyPlatform_win95,		(TCHAR*)_T(  "Win95"  ),				},	//  3
	{  CONST_qyPlatform_win98,		(TCHAR*)_T(  "Win98"  ),				},	//  4
	{  CONST_qyPlatform_winme,		(TCHAR*)_T(  "WinMe"  ),				},	//  5
	{  CONST_qyPlatform_nt,			(TCHAR*)_T(  "WinNT"  ),				},	//  6
	{  CONST_qyPlatform_win2k,		(TCHAR*)_T(  "Win2000"  ),				},	//  7
#endif
	{  CONST_qyPlatform_winxp,		(TCHAR*)_T(  "WinXP"  ),				},	//  8
	{  CONST_qyPlatform_win2003,	(TCHAR*)_T(  "Win2003"  ),				},	//  9
	{  CONST_qyPlatform_winVista,	(TCHAR*)_T(  "WinVista"  ),				},	//  10
	{	CONST_qyPlatform_win2008,	(TCHAR*)_T(  "Win2008"  ),				},	//  11						//  2009/11/06
	{	CONST_qyPlatform_win7,		(TCHAR*)_T(  "Win7"  ),					},	//  12						//  2009/11/06
	{	CONST_qyPlatform_win2008R2,	(TCHAR*)_T(  "Win2008R2"  ),			},	//  13						//  2009/11/06
	{  -1,							NULL,					},
};




 extern  "C"  TCHAR  *  qyPlatformStr(  int  iPlatform  )
{
	 TCHAR	*  ptr  =  qyGetDesByType(  CONST_qyPlatformTable,  iPlatform  );

	 return  ptr  ?  ptr  :  (TCHAR*)_T(  "Unsupported OS"  );
}




 //
 //
 //
 BOOL		g_bIsWinNT=1;

#if  0
 // Determine Operating System Version
 extern  "C"  void  GetOSVersion(  )
{
	OSVERSIONINFO osvi;

	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	
	if  (  GetVersionEx(&osvi)==FALSE  )  {
		return;
	}

	if  (  osvi.dwPlatformId==VER_PLATFORM_WIN32s  )  {
		return;		
	}
	
	if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT) 
		g_bIsWinNT = 1;
	else 
		g_bIsWinNT = 0;
}
#endif



  //  2005/11/29¼Ó£¬ÒòÎª98µÄINETMIB²»¹»ÎÈ¶¨£¬Ö»ÄÜµ÷ÓÃÒ»´Î£¬·ñÔòÈÝÒ×³öÎÊÌâ
/* //  2007/01/20Ç°°æ±¾
 extern  "C"  void  getQwmMacs(  int  iPlatformId,  QWM_MACS_INFO  *  pMacsInfo  )	//  ÒòÎªÕâ¸öº¯ÊýºÍg_bIsWinNTÏà¹ØÁª£¬ËùÒÔÃ»·ÅÔÚ¹«¹²º¯ÊýÇø£¬·ÅÔÚqwmPublicÏÂÁË
{
	 if  (  !pMacsInfo  )  return;

	 if  (  g_bIsWinNT  )  mygetQwmMacs(  pMacsInfo  );
	 else  {	
			static  BOOL				bMacsGot	=	FALSE;
			static  QWM_MACS_INFO		macsInfo;
			if  (  !bMacsGot  )  {
				memset(  pMacsInfo,  0,  sizeof(  QWM_MACS_INFO  )  );
				mygetQwmMacs(  pMacsInfo  );
				if  (  pMacsInfo->nMacs  )  {
					bMacsGot  =  TRUE;
					memcpy(  &macsInfo,  pMacsInfo,  sizeof(  QWM_MACS_INFO  )  );
				}
				}
			else  {
				  memcpy(  pMacsInfo,  &macsInfo,  sizeof(  QWM_MACS_INFO  )  );
			}
	 }
	 return;
}
*/

 extern  "C"  int  qnmCompareMacs(  const  void  *  arg1,  const  void  *  arg2  )
{
   /* Compare all of both strings: */
   return  memcmp(  *(  char  **  )arg1,  *(  char  **  )arg2,  CONST_qyMacLen  );
}

 
 extern  "C"  int  sortQwmMacs(  QWM_MACS_INFO  *  pMacsInfo  )
{
	 QWM_MACS_INFO				tmpMacsInfo;
	 unsigned  char			*	pMacs[CONST_qnmMaxMacs];
	 int						nMacs						=	0;
	 int						i;

	 if  (  !pMacsInfo  ||  pMacsInfo->nMacs  >  mycountof(  pMacsInfo->macs  )  )  return  -1;
	 
	 memcpy(  &tmpMacsInfo,  pMacsInfo,  sizeof(  QWM_MACS_INFO  )  );
	 for  (  i  =  0;  i  <  tmpMacsInfo.nMacs;  i  ++  )  {
		  pMacs[i]  =  tmpMacsInfo.macs[i];
	 }
	 qsort(  (  void  *  )pMacs,  tmpMacsInfo.nMacs,  sizeof(  char  *  ),  qnmCompareMacs  ); 

	 for  (  i  =  0;  i  <  (  int  )tmpMacsInfo.nMacs;  i  ++  )  {
		  safeStrnCpy(  (  char  *  )pMacs[i],  (  char  *  )pMacsInfo->macs[i],  sizeof(  pMacsInfo->macs[i]  )  );
	 }
	 return  0;

}




 extern  "C"  char  *  qnmBatIp(  char  *  ip,  unsigned  int  size  )
{
	ip[0]  =  0;

	if  (  size  <=  CONST_qyMaxIpLen  )  return  NULL;

	if  (  qyGetRegCfg(   _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_domainSvrIp  ),  ip,  size  )  )  {
		if  (  getHostIp(  NULL,  ip  )  )  {
			strcpy(  ip,  "0.0.0.0"  );
		}
	}
	if  (  !ip[0]  )  return  NULL;
	if  (  inet_addr(  ip  )  ==  inet_addr(  "127.0.0.1"  )  )  return  NULL;
	trim(  ip  );
	return  ip;

}


 extern  "C"  char  *  qnmCntIp(  char  *  ip,  unsigned  int  size  )
{
	 if  (  qyGetRegCfg(   _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_cntIp  ),  ip,  size  )  )  {
		 if  (  !qnmBatIp(  ip,  size  )  )  {
			 return  NULL;
		 }
	 }
	 if  (  inet_addr(  ip  )  ==  inet_addr(  "127.0.0.1"  )  )  return  NULL;
	 trim(  ip  );
	 return  ip;
}


 extern  "C"  int  qnmCntPort(  int  iServiceId  )
{
	switch  (  iServiceId  )  {
			case  CONST_qyServiceId_netMc:
				  return  DEFAULT_qyMcServPort;
			case  CONST_qyServiceId_mis:
				  return  DEFAULT_qyPort_mis;
			default:
					break;
	}
	return  -1;
}


 extern  "C"  int getQnmCntCfg(  void  *  p0,  BOOL  bServer,  int  iServiceId,  HKEY  hKeyRoot0,  LPCTSTR  rootKey_qnmScheduler,  QNM_CNT_CFG  *  pCfg  )
{
	TCHAR	tBuf[255  +  1]		=	_T(  ""  );
	char	buf[256]			=	"";

	if  (  !pCfg  )  return  -1;

	memset(  pCfg,  0,  sizeof(  pCfg[0]  )  );

	if  (  bServer  )  {
		pCfg->ucbAutoCntIp  =  TRUE;
		if  (  !qyGetRegCfgT(  hKeyRoot0,  rootKey_qnmScheduler,  _T(  CONST_regValName_bNotAutoCntIp  ),  buf,  sizeof(  buf  ),  0  )  )  pCfg->ucbAutoCntIp  =  FALSE;
		//
		if  (  !qnmCntIp(  buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
		safeStrnCpy(  buf,  pCfg->cntIp,  sizeof(  pCfg->cntIp  )  );
		}
	else  {  
		  if  (  qyGetRegCfgT(  hKeyRoot0,  rootKey_qnmScheduler,  _T(  CONST_regValName_cntIp  ),  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
		  tTrim(  tBuf  );  myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
		  if  (  bIpValid(  buf  )  )  safeStrnCpy(  buf,  pCfg->cntIp,  sizeof(  pCfg->cntIp  )  );
	}
	//
	if  (  qyGetRegCfgT(  hKeyRoot0,  rootKey_qnmScheduler,  _T(  CONST_regValName_cntAddr1  ),  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	tTrim(  tBuf  );  myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
	safeStrnCpy(  buf,  pCfg->cntAddrs[0],  sizeof(  pCfg->cntAddrs[0]  )  );
	if  (  qyGetRegCfgT(  hKeyRoot0,  rootKey_qnmScheduler,  _T(  CONST_regValName_cntAddr2  ),  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	tTrim(  tBuf  );  myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
	safeStrnCpy(  buf,  pCfg->cntAddrs[1],  sizeof(  pCfg->cntAddrs[1]  )  );
	//
	if  (  iServiceId  !=  CONST_qyServiceId_netMc  )  {	
		if  (  qyGetRegCfgT(  hKeyRoot0,  rootKey_qnmScheduler,  _T(  CONST_regValName_cntPort  ),  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
		tTrim(  tBuf  );  
		pCfg->usCntPort  =  _ttol(  tBuf  );
	}

	if  (  iServiceId  ==  CONST_qyServiceId_netMc  )  {	//  2011/03/19
		if  (  !pCfg->usCntPort  )  {
			pCfg->usCntPort  =  (  unsigned  short  )qnmCntPort(  iServiceId  );
		}
	}


	return  0;
}


 //  2005/06/25
 extern  "C"  int  qyntohCommServiceResp(  QY_COMM_SERVICERESP  *  p  )
{
	 MACRO_ntohl(  p->uiType  );
	 MACRO_ntohl(  p->uiSize  );
	 return  sizeof(  QY_COMM_SERVICERESP  );
}

 extern  "C"  int  qyhtonCommServiceResp(  QY_COMM_SERVICERESP  *  p  )
{
	 MACRO_htonl(  p->uiType  );
	 MACRO_htonl(  p->uiSize  );
	 return  sizeof(  QY_COMM_SERVICERESP  );
}


  extern  "C"  int  qyntohQwmEvent(  QWM_EVENT  *  pEvent  )
{
	 pEvent->eventType  =  qyntohl(  pEvent->eventType  );
	 pEvent->iCustomId  =  qyntohl(  pEvent->iCustomId  );

	 //  2011/09/21
	 MACRO_ntohs(  pEvent->usQwmDevType  );

	 return  sizeof(  QWM_EVENT  );
}

 extern  "C"  int  qyhtonQwmEvent(  QWM_EVENT  *  pEvent  )
{
	 pEvent->eventType  =  qyhtonl(  pEvent->eventType  );
	 pEvent->iCustomId  =  qyhtonl(  pEvent->iCustomId  );

	 //  2011/09/21
	 MACRO_htons(  pEvent->usQwmDevType  );

	 return  sizeof(  QWM_EVENT  );
}

 extern  "C"  int  qyntohQnmSecChkCommHead(  QNM_SECCHK_COMMHEAD  *  pSecChkCommHead  )
{
	 pSecChkCommHead->lEventCnt  =  qyntohl(  pSecChkCommHead->lEventCnt  );
	 pSecChkCommHead->uiEventSndSize  =  qyntohl(  pSecChkCommHead->uiEventSndSize  );
	 return  sizeof(  QNM_SECCHK_COMMHEAD  );
}


 extern  "C"  int  qyhtonQnmSecChkCommHead(  QNM_SECCHK_COMMHEAD  *  pSecChkCommHead  )
{
	 pSecChkCommHead->lEventCnt  =  qyhtonl(  pSecChkCommHead->lEventCnt  );
	 pSecChkCommHead->uiEventSndSize  =  qyhtonl(  pSecChkCommHead->uiEventSndSize  );
	 return  sizeof(  QNM_SECCHK_COMMHEAD  );
}


 extern  "C"  int  qyntohQnmSecChkEvent(  QNM_SECCHK_EVENT  *  pEvent  )
{
	 pEvent->lEventType  =  qyntohl(  pEvent->lEventType  );
	 return  sizeof(  QNM_SECCHK_EVENT  );
}

 extern  "C"  int  qyhtonQnmSecChkEvent(  QNM_SECCHK_EVENT  *  pEvent  )
{
	 pEvent->lEventType  =  qyhtonl(  pEvent->lEventType  );
	 return  sizeof(  QNM_SECCHK_EVENT  );
}
 

 extern  "C"  int  qyntohQwmInfo(  QWM_INFO  *  pQwmInfo  )
{
	 pQwmInfo->iPlatformId  =  qyntohl(  pQwmInfo->iPlatformId  );
	 pQwmInfo->uiLangId  =  qyntohl(  pQwmInfo->uiLangId  );		//  2005/01/22
	 return  sizeof(  QWM_INFO  );
}

 extern  "C"  int  qyhtonQwmInfo(  QWM_INFO  *  pQwmInfo  )
{
	 pQwmInfo->iPlatformId  =  qyhtonl(  pQwmInfo->iPlatformId  );
	 pQwmInfo->uiLangId  =  qyhtonl(  pQwmInfo->uiLangId  );		//  2005/01/22
	 return  sizeof(  QWM_INFO  );
}

 extern  "C"  int  qyntohQwmInfoEx(  QWM_INFO_EX  *  pQwmInfoEx  )
{
	 pQwmInfoEx->type  =  qyntohl(  pQwmInfoEx->type  );
	 switch  (  pQwmInfoEx->type  )  {
			 case  CONST_qwmInfoType_sp:	//  2005/06/25
				   qyntohQwmInfo(  &pQwmInfoEx->u.sp.qwm  );
				   break;
			 default:
					break;
	 }
	 return  sizeof(  QWM_INFO_EX  );
}

 extern  "C"  int  qyhtonQwmInfoEx(  QWM_INFO_EX  *  pQwmInfoEx  )
{
	 switch  (  pQwmInfoEx->type  )  {
			 case  CONST_qwmInfoType_sp:	//  2005/06/25
				   qyhtonQwmInfo(  &pQwmInfoEx->u.sp.qwm  );
				   break;
			 default:
					break;
	 }
	 pQwmInfoEx->type  =  qyhtonl(  pQwmInfoEx->type  );
	 return  sizeof(  QWM_INFO_EX  );
}






 //  2007/03/06
 extern "C" int safeWcsCpy(  LPCWSTR  strIn,  WCHAR  *  strOut,  unsigned  int  size  )
{
	 if  (  !strIn  ||  !strOut  )  return  -1;
	 if  (  wcslen(  strIn  )  >=  (  int  )size  ) return -1;
	 wcscpy(  strOut,  strIn  );
	 return  0;
}

 //  ÕâÀïµÄsizeÎª×Ö·ûµÄcount
 extern  "C"  void  safeWcsnCpy(  LPCWSTR  strIn,  WCHAR  *  strOut,  unsigned  int  size  )
{
	 if  (  !size  ||  !strIn  ||  !strOut  )  return;
	 unsigned  int	len  =  min(  size  -  1,  (  unsigned  int  )wcslen(  strIn  )  );
	 memcpy(  strOut,  strIn,  sizeof(  WCHAR  )  * len  );
	 strOut[len]  =  0;
	 return;
}




 //  ·µ»ØÖµ°üº¬Í·µÄ³¤¶È
 extern  "C"  int  qyntohQwmAssetsInfo(  QWM_ASSETS_INFO  *  pQwmAssetInfo  )
{	 
	 QWM_COMPONENT_INFO		*	pComponent	=	NULL;
	 unsigned  char				ucbUtf8		=	(  pQwmAssetInfo->uiCodePage  ==  CP_UTF8  );
	 
#define	MACRO_tmpUtf82TChar(  x,  sizeOfBytes  )	{  TCHAR  tBuf[512]  =  _T(  ""  );	myUtf82TChar(  x,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  lstrcpyn(  (  TCHAR  *  )x,  tBuf,  sizeOfBytes  /  sizeof(  TCHAR  )  );  }

	 if  (  !pQwmAssetInfo->ucbHeadProced  )  {
		 pQwmAssetInfo->uiLangId  =  qyntohl(  pQwmAssetInfo->uiLangId  );				//  2005/01/24
	 	 if  (  !pQwmAssetInfo->ucbNotConvrtPlatformId  )  pQwmAssetInfo->iPlatformId  =  qyhtonl(  pQwmAssetInfo->iPlatformId  );	
	 	 if  (  ucbUtf8  )  myUtf82Str(  pQwmAssetInfo->winDir,  sizeof(  pQwmAssetInfo->winDir  )  );
	 	 if  (  ucbUtf8  )  myUtf82Str(  pQwmAssetInfo->usrName,  sizeof(  pQwmAssetInfo->usrName  )  );
		 //
		 pQwmAssetInfo->ucbHeadProced  =  TRUE;
	 }
	 //  ÒÔÉÏ2005/01/14, 

	 pQwmAssetInfo->cnt  =  qyntohl(  pQwmAssetInfo->cnt  );
	 if  (  pQwmAssetInfo->cnt  >  sizeof(  pQwmAssetInfo->components  )  /  sizeof(  pQwmAssetInfo->components[0]  )  )  return  -1;
  
	 for  (  unsigned  int  i  =  0;  i  <  pQwmAssetInfo->cnt;  i  ++  )  {
		  pComponent  =  &pQwmAssetInfo->components[i];
		  MACRO_ntohl(  pComponent->uiPktSize  );
		  MACRO_ntohl(  pComponent->uiType  );
		  switch  (  pComponent->uiType  )  {
			      case  CONST_assetType_cpu:
					    MACRO_ntohl(  pComponent->u.cpu.iManufacturer  );
						MACRO_ntohl(  pComponent->u.cpu.iType  );
						MACRO_ntohl(  pComponent->u.cpu.iFamily  );
						MACRO_ntohl(  pComponent->u.cpu.iModel  );
						MACRO_ntohl(  pComponent->u.cpu.iCache  );
						MACRO_ntohl(  pComponent->u.cpu.iRevision  );
						MACRO_ntohl(  pComponent->u.cpu.iExtendedFamily  );
						MACRO_ntohl(  pComponent->u.cpu.iExtendedModel  );
						MACRO_ntohl(  pComponent->u.cpu.iFrequency  );
						MACRO_ntohl(  pComponent->u.cpu.uiBrandId  );	//  2005/01/16
						break;
				  case  CONST_assetType_cpu1:			//  2005/08/07
					    MACRO_ntohl(  pComponent->u.cpu1.uimHz  );		//  ÏÂÃæ£²ÐÐ£¬£²£°£°£µ£¯£±£±£¯£±£¶¼Ó£¬ÒÔºó£¬componentÀïµÄÊý¾Ý½«×ª³É£Õ£Î£É£Ã£Ï£Ä£Å£¬¹ÊÊ¹ÓÃÊ±Ó¦(  TCHAR *  )Ç¿ÖÆ×ª»»
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.cpu1.processorName,  sizeof(  pComponent->u.cpu1.processorName  )  );
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.cpu1.vendor,  sizeof(  pComponent->u.cpu1.vendor  )    );
					    break;
				  case  CONST_assetType_mem:
					    MACRO_ntohl(  pComponent->u.mem.uiTotalPhys  );
						break;
				  case  CONST_assetType_bios:
					    if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.bios.identifier,  sizeof(  pComponent->u.bios.identifier  )  );
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.bios.systemBiosVer,  sizeof(  pComponent->u.bios.systemBiosVer  )  );
						break;
				  case  CONST_assetType_floppy:
					    if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.floppy.driverDesc,  sizeof(  pComponent->u.floppy.driverDesc  )  );
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.floppy.driverVersion,  sizeof(  pComponent->u.floppy.driverVersion  )  );
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.floppy.vendor,  sizeof(  pComponent->u.floppy.vendor  )  );
						break;
				  case  CONST_assetType_monitor:
					    if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.monitor.driverDesc,  sizeof(  pComponent->u.monitor.driverDesc  )  );
						//  char								driverDate[14];
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.monitor.driverVersion,  sizeof(  pComponent->u.monitor.driverVersion  )  );
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.monitor.vendor,  sizeof(  pComponent->u.monitor.vendor  )  );
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.monitor.locationInformation,  sizeof(  pComponent->u.monitor.locationInformation  )  );
					    break;
				  case  CONST_assetType_ideHardDisk:
				  case  CONST_assetType_scsiHardDisk:
				  case  CONST_assetType_ideCdrom:
				  case  CONST_assetType_usbDisk:	//  2005/11/16
					    if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.disk.modelNo  ,  sizeof(  pComponent->u.disk.modelNo  )  );
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.disk.firmwareRevision,  sizeof(  pComponent->u.disk.firmwareRevision  )  );
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.disk.serialNo,  sizeof(  pComponent->u.disk.serialNo  )  );
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.disk.locationInformation,  sizeof(  pComponent->u.disk.locationInformation  )  );
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.disk.vendor,  sizeof(  pComponent->u.disk.vendor  )  );
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.disk.driverDesc,  sizeof(  pComponent->u.disk.driverDesc  )  );
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.disk.driverVersion,  sizeof(  pComponent->u.disk.driverVersion  )  );
					    break;
				  case  CONST_assetType_display:
					    if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.display.vendor,  sizeof(  pComponent->u.display.vendor  )  );
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.display.driverDesc,  sizeof(  pComponent->u.display.driverDesc  )  );
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.display.driverVersion,  sizeof(  pComponent->u.display.driverVersion  )  );
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.display.locationInformation,  sizeof(  pComponent->u.display.locationInformation  )  );
					    break;
				  case  CONST_assetType_networkCard:
					    if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.net.name,  sizeof(  pComponent->u.net.name  )  );
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.net.networkaddress,  sizeof(  pComponent->u.net.networkaddress  )  );
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.net.vendor,  sizeof(  pComponent->u.net.vendor  )  );
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.net.driverDesc,  sizeof(  pComponent->u.net.driverDesc  )  );
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.net.driverVersion,  sizeof(  pComponent->u.net.driverVersion  )  );
						if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.net.locationInformation,  sizeof(  pComponent->u.net.locationInformation  )  );
						break;
				  case  CONST_assetType_soundCard:
					    break;
				  case  CONST_assetType_software:
					    if  (  ucbUtf8  )  MACRO_tmpUtf82TChar(  pComponent->u.software.displayName,  sizeof(  pComponent->u.software.displayName  )  );
					    break;
				  default:
					      break;
		  }
	 }
	 return  offsetof(  QWM_ASSETS_INFO,  components  )  +  pQwmAssetInfo->cnt  *  sizeof(  pQwmAssetInfo->components[0]  );
}

  //  ·µ»ØÖµ°üº¬Í·µÄ³¤¶È
 extern  "C"  int  qyhtonQwmAssetsInfo(  QWM_ASSETS_INFO  *  pQwmAssetInfo  )
{	 
	 unsigned  int				len			=	0;
	 QWM_COMPONENT_INFO		*	pComponent	=	NULL;
	 unsigned  char				ucbUtf8		=  FALSE;	//  (  pQwmAssetInfo->uiCodePage  ==  CP_UTF8  );
	 unsigned  int				uiCodePage_component;

	 if  (  pQwmAssetInfo->cnt  >  sizeof(  pQwmAssetInfo->components  )  /  sizeof(  pQwmAssetInfo->components[0]  )  )  return  -1;

	 len  =  offsetof(  QWM_ASSETS_INFO,  components  )  +  pQwmAssetInfo->cnt  *  sizeof(  pQwmAssetInfo->components[0]  );
	 for  (  unsigned  int  i  =  0;  i  <  pQwmAssetInfo->cnt;  i  ++  )  {
		  pComponent  =  &pQwmAssetInfo->components[i];
		  uiCodePage_component  =  pQwmAssetInfo->uiCodePages[i];		//  2006/05/06
		  switch  (  pComponent->uiType  )  {
			      case  CONST_assetType_cpu:
					    MACRO_htonl(  pComponent->u.cpu.iManufacturer  );
						MACRO_htonl(  pComponent->u.cpu.iType  );
						MACRO_htonl(  pComponent->u.cpu.iFamily  );
						MACRO_htonl(  pComponent->u.cpu.iModel  );
						MACRO_htonl(  pComponent->u.cpu.iCache  );
						MACRO_htonl(  pComponent->u.cpu.iRevision  );
						MACRO_htonl(  pComponent->u.cpu.iExtendedFamily  );
						MACRO_htonl(  pComponent->u.cpu.iExtendedModel  );
						MACRO_htonl(  pComponent->u.cpu.iFrequency  );
						MACRO_htonl(  pComponent->u.cpu.uiBrandId  );
						break;
				  case  CONST_assetType_cpu1:		//  2005/8/07
					    MACRO_htonl(  pComponent->u.cpu1.uimHz  );	//  ÏÂÃæ2ÐÐÊÇ2005/11/16¼Ó
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.cpu1.processorName,  sizeof(  pComponent->u.cpu1.processorName  )  );
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.cpu1.vendor,  sizeof(  pComponent->u.cpu1.vendor  )  );
						break;
				  case  CONST_assetType_mem:
					    MACRO_htonl(  pComponent->u.mem.uiTotalPhys  );
						break;
				  case  CONST_assetType_bios:
					    if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.bios.identifier,  sizeof(  pComponent->u.bios.identifier  )  );
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.bios.systemBiosVer,  sizeof(  pComponent->u.bios.systemBiosVer  )  );
					    break;
				  case  CONST_assetType_floppy:
					    if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.floppy.driverDesc,  sizeof(  pComponent->u.floppy.driverDesc  )  );
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.floppy.driverVersion,  sizeof(  pComponent->u.floppy.driverVersion  )  );
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.floppy.vendor,  sizeof(  pComponent->u.floppy.vendor  )  );
						break;
				  case  CONST_assetType_monitor:
					    if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.monitor.driverDesc,  sizeof(  pComponent->u.monitor.driverDesc  )  );
						//  char								driverDate[14];
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.monitor.driverVersion,  sizeof(  pComponent->u.monitor.driverVersion  )  );
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.monitor.vendor,  sizeof(  pComponent->u.monitor.vendor  )  );
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.monitor.locationInformation,  sizeof(  pComponent->u.monitor.locationInformation  )  );
					    break;
				  case  CONST_assetType_ideHardDisk:
				  case  CONST_assetType_scsiHardDisk:
				  case  CONST_assetType_ideCdrom:
				  case  CONST_assetType_usbDisk:	//  2005/11/16
					    if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.disk.modelNo  ,  sizeof(  pComponent->u.disk.modelNo  )  );
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.disk.firmwareRevision,  sizeof(  pComponent->u.disk.firmwareRevision  )  );
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.disk.serialNo,  sizeof(  pComponent->u.disk.serialNo  )  );
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.disk.locationInformation,  sizeof(  pComponent->u.disk.locationInformation  )  );
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.disk.vendor,  sizeof(  pComponent->u.disk.vendor  )  );
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.disk.driverDesc,  sizeof(  pComponent->u.disk.driverDesc  )  );
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.disk.driverVersion,  sizeof(  pComponent->u.disk.driverVersion  )  );
					    break;
				  case  CONST_assetType_display:
					    if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.display.vendor,  sizeof(  pComponent->u.display.vendor  )  );
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.display.driverDesc,  sizeof(  pComponent->u.display.driverDesc  )  );
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.display.driverVersion,  sizeof(  pComponent->u.display.driverVersion  )  );
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.display.locationInformation,  sizeof(  pComponent->u.display.locationInformation  )  );
						break;
				  case  CONST_assetType_networkCard:
 					    if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.net.name,  sizeof(  pComponent->u.net.name  )  );
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.net.networkaddress,  sizeof(  pComponent->u.net.networkaddress  )  );
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.net.vendor,  sizeof(  pComponent->u.net.vendor  )  );
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.net.driverDesc,  sizeof(  pComponent->u.net.driverDesc  )  );
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.net.driverVersion,  sizeof(  pComponent->u.net.driverVersion  )  );
						if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.net.locationInformation,  sizeof(  pComponent->u.net.locationInformation  )  );
						break;
				  case  CONST_assetType_soundCard:
					    break;
				  case  CONST_assetType_software:
					    if  (  uiCodePage_component  !=  CP_UTF8  )  {
							if  (  ucbUtf8  )  myStr2Utf8(  pComponent->u.software.displayName,  sizeof(  pComponent->u.software.displayName  )  );
						}
					    break;
				  default:
					      break;
			      
		  }
		  MACRO_htonl(  pComponent->uiType  );
		  MACRO_htonl(  pComponent->uiPktSize  );
	 }
	 pQwmAssetInfo->cnt  =  qyhtonl(  pQwmAssetInfo->cnt  );

	 //  ÒÔÏÂ2005/01/14¼Ó, ÎªÁË·ÀÖ¹ÖØ¸´×ª»»£¬¼ÓÈëÒ»¸ö¿ØÖÆÁ¿
	 if  (  !pQwmAssetInfo->ucbHeadProced  )  {		
		 if  (  ucbUtf8  )  myStr2Utf8(  pQwmAssetInfo->usrName,  sizeof(  pQwmAssetInfo->usrName  )  );
		 if  (  ucbUtf8  )  myStr2Utf8(  pQwmAssetInfo->winDir,  sizeof(  pQwmAssetInfo->winDir  )  );
		 pQwmAssetInfo->iPlatformId		=	qyhtonl(  pQwmAssetInfo->iPlatformId  );	//  2005/01/14
		 pQwmAssetInfo->uiLangId		=	qyhtonl(  pQwmAssetInfo->uiLangId  );	//  2005/01/25
		 //
		 pQwmAssetInfo->ucbHeadProced  =  TRUE;	
	 }

	 return  len;
}


 //  2005/02/01
 extern  "C"  int  qyhtonQwmQueryPcSpReq(  QWM_QUERYPCSP_REQ  *  pReq  )
{
	 MACRO_htonl(  pReq->uiType  );
	 MACRO_htonl(  pReq->ulQwmIp  );
	 return  sizeof(  QWM_QUERYPCSP_REQ  );
}

  //  2005/02/01
 extern  "C"  int  qyntohQwmQueryPcSpReq(  QWM_QUERYPCSP_REQ  *  pReq  )
{
	 MACRO_ntohl(  pReq->uiType  );
	 MACRO_ntohl(  pReq->ulQwmIp  );
	 return  sizeof(  QWM_QUERYPCSP_REQ  );
}

 //  2005/02/01
 extern  "C"  int  qyhtonQwmQueryPcSpResp(  QWM_QUERYPCSP_RESP  *  pResp  )
{
	 MACRO_htonl(  pResp->uiType  );								//  ·´Ó¦ÀàÐÍ
	 MACRO_htonl(  pResp->iPlatformId  );						
	 MACRO_htonl(  pResp->uiLangId  );
	 MACRO_htonl(  pResp->uiPcSpCnt  );
	 MACRO_htonl(  pResp->uiPcSpSize  );
	 return  sizeof(  QWM_QUERYPCSP_RESP  );
}

 //  2005/02/01
 extern  "C"  int  qyntohQwmQueryPcSpResp(  QWM_QUERYPCSP_RESP  *  pResp  )
{
	 MACRO_ntohl(  pResp->uiType  );								//  ·´Ó¦ÀàÐÍ
	 MACRO_ntohl(  pResp->iPlatformId  );						
	 MACRO_ntohl(  pResp->uiLangId  );
	 MACRO_ntohl(  pResp->uiPcSpCnt  );
	 MACRO_ntohl(  pResp->uiPcSpSize  );
	 return  sizeof(  QWM_QUERYPCSP_RESP  );
}

 extern  "C"  int  qyhtonQwmPcSpInfo(  QWM_PC_SPINFO  *  pSpInfo  )
{ 
	 MACRO_htonl(  pSpInfo->iType  );
	 return  sizeof(  QWM_PC_SPINFO  );
}

 extern  "C"  int  qyntohQwmPcSpInfo(  QWM_PC_SPINFO  *  pSpInfo  )
{ 
	 MACRO_ntohl(  pSpInfo->iType  );
	 return  sizeof(  QWM_PC_SPINFO  );
}


 //  2005/05/02
 extern  "C"  int  qyhtonShowQwmSvrStatus(  QNM_CMDPARAM_showQwmSvrStatus  *  pStatus  )
{
	 MACRO_htonl(  pStatus->uiQwmSvrStatus  );
	 MACRO_htonl(  pStatus->uiSecChkEventCnt  );				//  Ðè·¢ËÍ¼ÇÂ¼×ÜÊý
	 MACRO_htonl(  pStatus->uiSecChkEventSentCnt  );				//  ÒÑ·¢ËÍ¼ÇÂ¼×ÜÊý

	 return  sizeof(  QNM_CMDPARAM_showQwmSvrStatus  );  
}

 extern  "C"  int  qyntohShowQwmSvrStatus(  QNM_CMDPARAM_showQwmSvrStatus  *  pStatus  )
{
	 MACRO_ntohl(  pStatus->uiQwmSvrStatus  );
	 MACRO_ntohl(  pStatus->uiSecChkEventCnt  );				//  Ðè·¢ËÍ¼ÇÂ¼×ÜÊý
	 MACRO_ntohl(  pStatus->uiSecChkEventSentCnt  );				//  ÒÑ·¢ËÍ¼ÇÂ¼×ÜÊý

	 return  sizeof(  QNM_CMDPARAM_showQwmSvrStatus  );  
}


 extern  "C"  int  qyhtonQyPcAdapterProp(  QY_PCADAPTER_PROP  *  p  )
{
	 MACRO_htonl(  p->uiType  );
	 MACRO_htonl(  p->uiSize  );
	 MACRO_htonl(  p->iPlatformId  );
	 MACRO_htonl(  p->uiLangId  );
	 MACRO_htonl(  p->devIndex  );
	 MACRO_htonl(  p->uiAdapterType  );
	 MACRO_htonl(  p->lLeaseObtained  );

	 return  sizeof(  QY_PCADAPTER_PROP  );
}


 extern  "C"  int  qyntohQyPcAdapterProp(  QY_PCADAPTER_PROP  *  p  )
{
	 MACRO_ntohl(  p->uiType  );
	 MACRO_ntohl(  p->uiSize  );
	 MACRO_ntohl(  p->iPlatformId  );
	 MACRO_ntohl(  p->uiLangId  );
	 MACRO_ntohl(  p->devIndex  );
	 MACRO_ntohl(  p->uiAdapterType  );
	 MACRO_ntohl(  p->lLeaseObtained  );

	 return  sizeof(  QY_PCADAPTER_PROP  );
}


 //  2006/05/21
 extern  "C"  int  qyhtonQwmWindowsUpdatePolicyProp(  QWM_WINDOWSUPDATEPOLICY_PROP  *  p  )
{
	 MACRO_htonl(  p->uiType  );
	 MACRO_htonl(  p->uiSize  );
	 MACRO_htonl(  p->iPlatformId  );
	 MACRO_htonl(  p->uiLangId  );

	 MACRO_htonl(  p->RescheduleWaitTime  );
	 MACRO_htonl(  p->RescheduleWaitTimeEnabled  );
	 MACRO_htonl(  p->NoAutoRebootWithLoggedOnUsers  );
	 MACRO_htonl(  p->NoAutoUpdate  );
	 MACRO_htonl(  p->AUOptions  );
	 MACRO_htonl(  p->ScheduledInstallDay  );
	 MACRO_htonl(  p->ScheduledInstallTime  );
	 MACRO_htonl(  p->DetectionFrequencyEnabled  );
	 MACRO_htonl(  p->DetectionFrequency  );
	 MACRO_htonl(  p->UseWUServer  );
	 //
	 MACRO_htonl(  p->ElevateNonAdmins  );
	 MACRO_htonl(  p->TargetGroupEnabled  );
	 //
	 MACRO_htonl(  p->AutoUpdate_AUOptions  ); 
	 MACRO_htonl(  p->AutoUpdate_ScheduledInstallDay  );
	 MACRO_htonl(  p->AutoUpdate_ScheduledInstallTime  );

	 return  sizeof(  QWM_WINDOWSUPDATEPOLICY_PROP  );
}

 //  2006/05/21
 extern  "C"  int  qyntohQwmWindowsUpdatePolicyProp(  QWM_WINDOWSUPDATEPOLICY_PROP  *  p  )
{
	 MACRO_ntohl(  p->uiType  );
	 MACRO_ntohl(  p->uiSize  );
	 MACRO_ntohl(  p->iPlatformId  );
	 MACRO_ntohl(  p->uiLangId  );

	 MACRO_ntohl(  p->RescheduleWaitTime  );
	 MACRO_ntohl(  p->RescheduleWaitTimeEnabled  );
	 MACRO_ntohl(  p->NoAutoRebootWithLoggedOnUsers  );
	 MACRO_ntohl(  p->NoAutoUpdate  );
	 MACRO_ntohl(  p->AUOptions  );
	 MACRO_ntohl(  p->ScheduledInstallDay  );
	 MACRO_ntohl(  p->ScheduledInstallTime  );
	 MACRO_ntohl(  p->DetectionFrequencyEnabled  );
	 MACRO_ntohl(  p->DetectionFrequency  );
	 MACRO_ntohl(  p->UseWUServer  );
	 //
	 MACRO_ntohl(  p->ElevateNonAdmins  );
	 MACRO_ntohl(  p->TargetGroupEnabled  );
	 //
	 MACRO_ntohl(  p->AutoUpdate_AUOptions  ); 
	 MACRO_ntohl(  p->AutoUpdate_ScheduledInstallDay  );
	 MACRO_ntohl(  p->AutoUpdate_ScheduledInstallTime  );

	 return  sizeof(  QWM_WINDOWSUPDATEPOLICY_PROP  );
}


 extern  "C"  int  qyhtonQyPcNetworkPropU(  QY_PCNETWORK_PROPU  *  p  )
{
#if  0
	 switch  (  p->uiType  )  {
			 case  CONST_pcNetworkPropType_adapter:
				   qyhtonQyPcAdapterProp(  &p->adapter  );
				   break;
			 case  CONST_pcCommType_windowsUpdatePolicy:
				   qyhtonQwmWindowsUpdatePolicyProp(  &p->windowsUpdatePolicy  );
				   break;
			 default:
				    MACRO_htonl(  p->head.uiType  );
				    MACRO_htonl(  p->head.uiSize  );
					MACRO_htonl(  p->head.iPlatformId  );
					MACRO_htonl(  p->head.uiLangId  );
					break;				   
	 }
#endif 
	 return  sizeof(  QY_PCNETWORK_PROPU  );
}

 extern  "C"  int  qyntohQyPcNetworkPropU(  QY_PCNETWORK_PROPU  *  p  )
{	 
#if  0
	 switch  (  qyntohl(  p->uiType  )  )  {
		     case  CONST_pcNetworkPropType_adapter:
				   qyntohQyPcAdapterProp(  &p->adapter  );
				   break;
			 case  CONST_pcCommType_windowsUpdatePolicy:
				   qyntohQwmWindowsUpdatePolicyProp(  &p->windowsUpdatePolicy  );
				   break;
			 default:
					 MACRO_ntohl(  p->head.uiType  );
					 MACRO_ntohl(  p->head.uiSize  );
					 MACRO_ntohl(  p->head.iPlatformId  );
					 MACRO_ntohl(  p->head.uiLangId  );
					 break;
	 }
#endif 
	 return  sizeof(  QY_PCNETWORK_PROPU  );
}


 extern  "C"  int  qyhtonQyProcessProp0326(  QY_PROCESS_PROP0326  *  p  )
{
		MACRO_htonl(  p->dwPid  );
		MACRO_htonl(  p->dwPpid  );			//  ¸¸½ø³Ì
		MACRO_htonl(  p->dwCpuPercent  );	//  CPUÕ¼ÓÐÂÊ
		MACRO_htonl(  p->dwCpuTime  );		//  CPUÊ±¼ä
		MACRO_htonl(  p->dwMemInK  );		//  ÄÚ´æ´óÐ¡
		MACRO_htonl(  p->dwVmemInK  );		//  Ðé´æ´óÐ¡
		MACRO_htonl(  p->dwHandles  );		//  ¾ä±úÊý
		MACRO_htonl(  p->dwThreads  );		//  Ïß³ÌÊý				 		

	 return  sizeof(  QY_PROCESS_PROP0326  );
}

 extern  "C"  int  qyntohQyProcessProp0326(  QY_PROCESS_PROP0326  *  p  )
{
		MACRO_ntohl(  p->dwPid  );
		MACRO_ntohl(  p->dwPpid  );			//  ¸¸½ø³Ì
		MACRO_ntohl(  p->dwCpuPercent  );	//  CPUÕ¼ÓÐÂÊ
		MACRO_ntohl(  p->dwCpuTime  );		//  CPUÊ±¼ä
		MACRO_ntohl(  p->dwMemInK  );		//  ÄÚ´æ´óÐ¡
		MACRO_ntohl(  p->dwVmemInK  );		//  Ðé´æ´óÐ¡
		MACRO_ntohl(  p->dwHandles  );		//  ¾ä±úÊý
		MACRO_ntohl(  p->dwThreads  );		//  Ïß³ÌÊý				 		

	 return  sizeof(  QY_PROCESS_PROP0326  );
}

//

 extern  "C"  int  qyhtonQyProcessProp(  QY_PROCESS_PROP  *  p  )
{
		MACRO_htonl(  p->dwPid  );
		MACRO_htonl(  p->dwPpid  );			//  ¸¸½ø³Ì
		MACRO_htonl(  p->dwCpuPercent  );	//  CPUÕ¼ÓÐÂÊ
		MACRO_htonl(  p->dwCpuTime  );		//  CPUÊ±¼ä
		MACRO_htonl(  p->dwMemInK  );		//  ÄÚ´æ´óÐ¡
		MACRO_htonl(  p->dwVmemInK  );		//  Ðé´æ´óÐ¡
		MACRO_htonl(  p->dwHandles  );		//  ¾ä±úÊý
		MACRO_htonl(  p->dwThreads  );		//  Ïß³ÌÊý				 		

	 return  sizeof(  QY_PROCESS_PROP  );
}

 extern  "C"  int  qyntohQyProcessProp(  QY_PROCESS_PROP  *  p  )
{
		MACRO_ntohl(  p->dwPid  );
		MACRO_ntohl(  p->dwPpid  );			//  ¸¸½ø³Ì
		MACRO_ntohl(  p->dwCpuPercent  );	//  CPUÕ¼ÓÐÂÊ
		MACRO_ntohl(  p->dwCpuTime  );		//  CPUÊ±¼ä
		MACRO_ntohl(  p->dwMemInK  );		//  ÄÚ´æ´óÐ¡
		MACRO_ntohl(  p->dwVmemInK  );		//  Ðé´æ´óÐ¡
		MACRO_ntohl(  p->dwHandles  );		//  ¾ä±úÊý
		MACRO_ntohl(  p->dwThreads  );		//  Ïß³ÌÊý				 		

	 return  sizeof(  QY_PROCESS_PROP  );
}

//


 extern  "C"  int  qyhtonQyEventLogProp(  QY_EVENTLOG_PROP  *  p  )
{
	 MACRO_htonl(  p->dwRecordNumber  );  // Absolute record number
	 MACRO_htons(  p->wEventType  );
	 MACRO_htons(  p->wEventCategory  );
	 MACRO_htonl(  p->dwEventID  );

	 return  sizeof(  QY_EVENTLOG_PROP  );
}

 extern  "C"  int  qyntohQyEventLogProp(  QY_EVENTLOG_PROP  *  p  )
{
	 MACRO_ntohl(  p->dwRecordNumber  );  // Absolute record number
	 MACRO_ntohs(  p->wEventType  );
	 MACRO_ntohs(  p->wEventCategory  );
	 MACRO_ntohl(  p->dwEventID  );

	 return  sizeof(  QY_EVENTLOG_PROP  );
}

 //  2005/09/17
 extern  "C"  int  qyhtonmyMIB_TCPROW(  myMIB_TCPROW  *  p  )
{
	 MACRO_htonl(  p->dwState  );
	 //  MACRO_htonl(  p->dwLocalAddr  );
	 p->dwLocalPort  =  qyntohs(  (  unsigned  short  )p->dwLocalPort  );	MACRO_htonl(  p->dwLocalPort  );
	 //  MACRO_htonl(  p->dwRemoteAddr  );
	 p->dwRemotePort  =  qyntohs(  (  unsigned  short  )p->dwRemotePort  );	MACRO_htonl(  p->dwRemotePort  );

	 return  sizeof(  myMIB_TCPROW  );
}

 extern  "C"  int  qyntohmyMIB_TCPROW(  myMIB_TCPROW  *  p  )
{
	 MACRO_ntohl(  p->dwState  );
	 //  MACRO_ntohl(  p->dwLocalAddr  );
	 MACRO_ntohl(  p->dwLocalPort  );
	 //  MACRO_ntohl(  p->dwRemoteAddr  );
	 MACRO_ntohl(  p->dwRemotePort  );

	 return  sizeof(  myMIB_TCPROW  );
}

 extern  "C"  int  qyhtonmyMIB_UDPROW(  myMIB_UDPROW  *  p  )
{
	 //  MACRO_htonl(  p->dwLocalAddr  );
	 p->dwLocalPort  =  qyntohs(  (  unsigned  short  )p->dwLocalPort  );  MACRO_htonl(  p->dwLocalPort  );
	 return  sizeof(  myMIB_UDPROW  );
}

 extern  "C"  int  qyntohmyMIB_UDPROW(  myMIB_UDPROW  *  p  )
{
	 //  MACRO_ntohl(  p->dwLocalAddr  );
	 MACRO_ntohl(  p->dwLocalPort  );
	 return  sizeof(  myMIB_UDPROW  );
}

/*
				 int									iRuleId;						//  ÓÃÀ´±êÊ¶ÅäÖÃÏîµÄÊý¾Ý¿â¼ÇÂ¼
				 unsigned  char							ucFlg;							//  ÓÃÀ´±êÊ¶Æä×´Ì¬
				 unsigned  char							ucbKey;							//  ÊÇ·ñÊÇkey, ²»ÊÇµÄ»°¾ÍÊÇvalue
				 unsigned  char							ucbERROR_MORE_DATA;				//  ÊÇ·ñ¼üÃû»ò¼üÖµÌ«³¤
				 unsigned  int							uiCfgNameLen;					//  ÅäÖÃÃû³¤¶È
				 char									cfgName[255  +  1];
				 int									iValType;
				 unsigned  int							uiValLenInBytes;				//  ÖµµÄ³¤¶È
				 union									{
					 int								iCfgVal;
				 	 char								cfgVal[255  +  1];
				 }										u;

*/

 //  2006/07/16
 extern  "C"  int  qyhtonQyPcRegistryVal(  QY_PC_REGISTRYVAL  *  p  )
{
	 WCHAR		wBuf[512]	=	L"";
	 char		buf[1024]	=	"";

	 switch  (  p->iValType  )  {
			 case  REG_SZ:
			 case  REG_EXPAND_SZ:
			 case  REG_MULTI_SZ:
				   safeWcsnCpy(  p->u.wCfgVal,  wBuf,  mycountof(  wBuf  )  );
				   buf[0]  =  0;
				   myWChar2Utf8(  wBuf,  buf,  sizeof(  buf  )  );
				   safeStrnCpy(  buf,  (  char  *  )p->u.wCfgVal,  sizeof(  p->u.wCfgVal  )  );
				   //  myWChar2Utf8(  wBuf,  (  char  *  )p->u.wCfgVal,  sizeof(  p->u.wCfgVal  )  );
				   break;
			 case  REG_DWORD:
			 case  REG_DWORD_BIG_ENDIAN:
				   MACRO_htonl(  p->u.iCfgVal  );
				   break;
			 default:
					break;
					
	 }

	 MACRO_htonl(  p->iRuleId  );
	 MACRO_htonl(  p->uiCfgNameLen  );
	 MACRO_htonl(  p->iValType  );
	 MACRO_htonl(  p->uiValLenInBytes  );
	 
	 return  sizeof(  QY_PC_REGISTRYVAL  );
}

 extern  "C"  int  qyntohQyPcRegistryVal(  QY_PC_REGISTRYVAL  *  p  )
{
	 WCHAR		wBuf[512]	=	L"";

	 MACRO_ntohl(  p->iRuleId  );
	 MACRO_ntohl(  p->uiCfgNameLen  );
	 MACRO_ntohl(  p->iValType  );
	 MACRO_ntohl(  p->uiValLenInBytes  );

	 switch  (  p->iValType  )  {
			 case  REG_SZ:
			 case  REG_EXPAND_SZ:
			 case  REG_MULTI_SZ:
				   myUtf82WChar(  (  char  *  )p->u.wCfgVal,  wBuf,  mycountof(  wBuf  )  );
				   safeWcsnCpy(  wBuf,  p->u.wCfgVal,  mycountof(  p->u.wCfgVal  )  );
				   break;
			 case  REG_DWORD:
			 case  REG_DWORD_BIG_ENDIAN:
				   MACRO_ntohl(  p->u.iCfgVal  );
				   break;
			 default:
					break;
					
	 }

	 return  sizeof(  QY_PC_REGISTRYVAL  );
}

 extern  "C"  int  qyhtonQyPcNetFlowProp(  QY_PCNETFLOW_PROP  *  p  )
{	 		
	 MACRO_htonl(  p->dwIndex  );		//  ºÜ¶à³ÉÔ±Õª×ÔMIB_IFROW
	 MACRO_htonl(  p->dwType  );			
	 MACRO_htonl(  p->dwSpeed  );		
	 MACRO_htonl(  p->dwInSpeed  );		//  ÈëÁ÷Á¿, ×Ô¶¨Òå
	 MACRO_htonl(  p->dwOutSpeed  );		//  ³öÁ÷Á¿, ×Ô¶¨Òå
	 MACRO_htonl(  p->dwPhysAddrLen  );
	 //  BYTE										bPhysAddr[CONST_myMAXLEN_PHYSADDR];
	 //									
	 MACRO_htonl(  p->dwMtu  );
	 MACRO_htonl(  p->dwAdminStatus  );
	 MACRO_htonl(  p->dwOperStatus  );
	 MACRO_htonl(  p->dwLastChange  );
	 MACRO_htonl(  p->dwInOctets  );
	 MACRO_htonl(  p->dwInUcastPkts  );
	 MACRO_htonl(  p->dwInNUcastPkts  );
	 MACRO_htonl(  p->dwInDiscards  );
	 MACRO_htonl(  p->dwInErrors  );
	 MACRO_htonl(  p->dwInUnknownProtos  );
	 MACRO_htonl(  p->dwOutOctets  );
	 MACRO_htonl(  p->dwOutUcastPkts  );
	 MACRO_htonl(  p->dwOutNUcastPkts  );
	 MACRO_htonl(  p->dwOutDiscards  );
	 MACRO_htonl(  p->dwOutErrors  );
	 MACRO_htonl(  p->dwOutQLen  );
				 //
	
	 //  unsigned  char								ucWarnCnt;
	 //  unsigned  char								iireserved[3];

	 return  sizeof(  QY_PCNETFLOW_PROP  );
}

 extern  "C"  int  qyntohQyPcNetFlowProp(  QY_PCNETFLOW_PROP  *  p  )
{
	 MACRO_ntohl(  p->dwIndex  );		//  ºÜ¶à³ÉÔ±Õª×ÔMIB_IFROW
	 MACRO_ntohl(  p->dwType  );			
	 MACRO_ntohl(  p->dwSpeed  );		
	 MACRO_ntohl(  p->dwInSpeed  );		//  ÈëÁ÷Á¿, ×Ô¶¨Òå
	 MACRO_ntohl(  p->dwOutSpeed  );		//  ³öÁ÷Á¿, ×Ô¶¨Òå
	 MACRO_ntohl(  p->dwPhysAddrLen  );
	 //  BYTE										bPhysAddr[CONST_myMAXLEN_PHYSADDR];
	 //									
	 MACRO_ntohl(  p->dwMtu  );
	 MACRO_ntohl(  p->dwAdminStatus  );
	 MACRO_ntohl(  p->dwOperStatus  );
	 MACRO_ntohl(  p->dwLastChange  );
	 MACRO_ntohl(  p->dwInOctets  );
	 MACRO_ntohl(  p->dwInUcastPkts  );
	 MACRO_ntohl(  p->dwInNUcastPkts  );
	 MACRO_ntohl(  p->dwInDiscards  );
	 MACRO_ntohl(  p->dwInErrors  );
	 MACRO_ntohl(  p->dwInUnknownProtos  );
	 MACRO_ntohl(  p->dwOutOctets  );
	 MACRO_ntohl(  p->dwOutUcastPkts  );
	 MACRO_ntohl(  p->dwOutNUcastPkts  );
	 MACRO_ntohl(  p->dwOutDiscards  );
	 MACRO_ntohl(  p->dwOutErrors  );
	 MACRO_ntohl(  p->dwOutQLen  );
				 //
	
	 //  unsigned  char								ucWarnCnt;
	 //  unsigned  char								iireserved[3];

	 return  sizeof(  QY_PCNETFLOW_PROP  );
}


 //  2007/02/14
 extern  "C"  int  qyhtonQyPcNetShareProp(  QY_PCNETSHARE_PROP  *  p  )
{	 		
	 char	buf[1024]	=	"";

	 myWChar2Utf8(  p->shi502_netname,  buf,  sizeof(  buf  )  );  safeStrnCpy(  buf,  (  char  *  )p->shi502_netname,  sizeof(  p->shi502_netname  )  );
	 MACRO_htonl(  p->shi502_type  );
	 myWChar2Utf8(  p->shi502_path,  buf,  sizeof(  buf  )  );  safeStrnCpy(  buf,  (  char  *  )p->shi502_path,  sizeof(  p->shi502_path  )  );

	 return  sizeof(  p[0]  );
}

 extern  "C"  int  qyntohQyPcNetShareProp(  QY_PCNETSHARE_PROP  *  p  )
{	 		
	 char	buf[1024]	=	"";

	 safeStrnCpy(  (  char  *  )p->shi502_netname,  buf,  sizeof(  buf  )  );  myUtf82WChar(  buf,  p->shi502_netname,  mycountof(  p->shi502_netname  )  );
	 MACRO_ntohl(  p->shi502_type  );
	 safeStrnCpy(  (  char  *  )p->shi502_path,  buf,  sizeof(  buf  )  );  myUtf82WChar(  buf,  p->shi502_path,  mycountof(  p->shi502_path  )  );
	 
	 return  sizeof(  p[0]  );
}


 extern  "C"  int  qyhtonQyPcCommU(  long  lhQwnVer,  QY_PC_COMMU  *  pPcCommU  )
{
	 int				len				=	-1;
	 unsigned  int		i;
	 WCHAR				wBuf[512]		=	L"";

	 
	 if  (  pPcCommU->head.uiSize  >  sizeof(  QY_PC_COMMU  )  )  return  -1;

#if  0
	 switch  (  pPcCommU->uiType  )  {
			 case  CONST_pcCommType_process:
				   /*	//  <=0326µÄ°æ±¾µÄ×ª»»
				   if  (  pPcCommU->processesInfo0326.cnt  >  sizeof(  pPcCommU->processesInfo0326.mems  )  /  sizeof(  pPcCommU->processesInfo0326.mems[0]  )  )  goto  errLabel;
				   len  =  offsetof(  QY_PC_PROCESSES0326,  mems  )  +  pPcCommU->processesInfo0326.cnt  *  sizeof(  pPcCommU->processesInfo0326.mems[0]  );
				   for  (  i  =  0;  i  <  pPcCommU->processesInfo0326.cnt;  i  ++  )  {
					    qyhtonQyProcessProp0326(  &pPcCommU->processesInfo0326.mems[i]  );
				   }
				   */
				   if  (  pPcCommU->processesInfo.cnt  >  mycountof(  pPcCommU->processesInfo.mems  )  )  goto  errLabel;
				   len  =  offsetof(  QY_PC_PROCESSES,  mems  )  +  pPcCommU->processesInfo.cnt  *  sizeof(  pPcCommU->processesInfo.mems[0]  );
				   for  (  i  =  0;  i  <  pPcCommU->processesInfo.cnt;  i  ++  )  {
					    qyhtonQyProcessProp(  &pPcCommU->processesInfo.mems[i]  );
				   }
				   break;
			 case  CONST_pcCommType_eventLog:
				   if  (  pPcCommU->eventLogsInfo.cnt  >  sizeof(  pPcCommU->eventLogsInfo.mems  )  /  sizeof(  pPcCommU->eventLogsInfo.mems  [0]  )  )  goto  errLabel;
				   len  =  offsetof(  QY_PC_EVENTLOGS,  mems  )  +  pPcCommU->eventLogsInfo.cnt  *  sizeof(  pPcCommU->eventLogsInfo.mems[0]  );
				   for  (  i  =  0;  i  <  pPcCommU->eventLogsInfo.cnt;  i  ++  )  {
					    qyhtonQyEventLogProp(  &pPcCommU->eventLogsInfo.mems[i]  );
				   }
				   break;
			 case  CONST_pcCommType_usrInfo:	//  2005/09/04
				   if  (  pPcCommU->usrInfos.cnt  >  sizeof(  pPcCommU->usrInfos.mems  )  /  sizeof(  pPcCommU->usrInfos.mems[0]  )  )  goto  errLabel;
				   len  =  offsetof(  QY_PC_USRINFOS,  mems  )  +  pPcCommU->usrInfos.cnt  *  sizeof(  pPcCommU->usrInfos.mems[0]  );
				   break;
			 case  CONST_pcCommType_printers:
				   if  (  pPcCommU->printers.cnt  >  sizeof(  pPcCommU->printers.mems  )  /  sizeof(  pPcCommU->printers.mems[0]  )  )  goto  errLabel;
				   len  =  offsetof(  QY_PC_PRINTERS,  mems  )  +  pPcCommU->head.cnt  *  sizeof(  pPcCommU->printers.mems[0]  );
				   break;
			 case  CONST_pcCommType_tcpTable:
				   if  (  pPcCommU->tcpTable.cnt  >  sizeof(  pPcCommU->tcpTable.mems  )  /  sizeof(  pPcCommU->tcpTable.mems[0]  )  )  goto  errLabel;
				   len  =  offsetof(  QY_PC_TCPTABLE,  mems  )  +  pPcCommU->tcpTable.cnt  *  sizeof(  pPcCommU->tcpTable.mems[0]  );
				   for  (  i  =  0;  i  <  pPcCommU->tcpTable.cnt;  i  ++  )  {
					    qyhtonmyMIB_TCPROW(  &pPcCommU->tcpTable.mems[i]  );
				   }
				   break;
			 case  CONST_pcCommType_udpTable:
				   if  (  pPcCommU->udpTable.cnt  >  sizeof(  pPcCommU->udpTable.mems  )  /  sizeof(  pPcCommU->udpTable.mems[0]  )  )  goto  errLabel;
				   len  =  offsetof(  QY_PC_UDPTABLE,  mems  )  +  pPcCommU->udpTable.cnt  *  sizeof(  pPcCommU->udpTable.mems[0]  );
				   for  (  i  =  0;  i  <  pPcCommU->udpTable.cnt;  i  ++  )  {
					    qyhtonmyMIB_UDPROW(  &pPcCommU->udpTable.mems[i]  );
				   }
				   break;
			 case  CONST_pcCommType_processModule:
				   if  (  pPcCommU->processModulesInfo.cnt  >  mycountof(  pPcCommU->processModulesInfo.mems  )  )  goto  errLabel;
				   len  =  offsetof(  QY_PC_PROCESSMODULES,  mems  )  +  pPcCommU->processModulesInfo.cnt  *  sizeof(  pPcCommU->processModulesInfo.mems[0]  );
				   for  (  i  =  0;  i  <  pPcCommU->processModulesInfo.cnt;  i  ++  )  {
					    //
				   }				   
				   break;
			 case  CONST_pcCommType_registryVal:
				   if  (  pPcCommU->registryVals.cnt  >  mycountof(  pPcCommU->registryVals.mems  )  )  goto  errLabel;
				   len  =  offsetof(  QY_PC_REGISTRYVALS,  mems  )  +  pPcCommU->registryVals.cnt  *  sizeof(  pPcCommU->registryVals.mems[0]  );
				   //
				   safeWcsnCpy(  pPcCommU->registryVals.wUsrName,  wBuf,  mycountof(  wBuf  )  );
				   myWChar2Utf8(  wBuf,  (  char  *  )pPcCommU->registryVals.wUsrName,  sizeof(  pPcCommU->registryVals.wUsrName  )  );
				   //
				   for  (  i  =  0;  i  <  pPcCommU->registryVals.cnt;  i  ++  )  {
					    qyhtonQyPcRegistryVal(  &pPcCommU->registryVals.mems[i]  );
				   }
				   break;
			 case  CONST_pcCommType_queryCfgs:
				   if  (  pPcCommU->queryCfgs.cnt  >  mycountof(  pPcCommU->queryCfgs.mems  )  )  goto  errLabel;
				   len  =  offsetof(  QY_PC_QUERYCFGS,  mems  )  +  pPcCommU->queryCfgs.cnt  *  sizeof(  pPcCommU->queryCfgs.mems[0]  );
				   //
				   for  (  i  =  0;  i  <  pPcCommU->queryCfgs.cnt;  i  ++  )  {
					    MACRO_htonl(  pPcCommU->queryCfgs.mems[i].uiChangesId_fileMon  );
						MACRO_htonl(  pPcCommU->queryCfgs.mems[i].uiQueryTimes  );
				   }
				   break;
			 case  CONST_pcCommType_netFlow:
				   if  (  pPcCommU->netFlows.cnt  >  mycountof(  pPcCommU->netFlows.mems  )  )  goto  errLabel;
				   len  =  offsetof(  QY_PC_NETFLOWS,  mems  )  +  pPcCommU->netFlows.cnt  *  sizeof(  pPcCommU->netFlows.mems[0]  );
				   //
				   for  (  i  =  0;  i  <  pPcCommU->netFlows.cnt;  i  ++  )  {
					    qyhtonQyPcNetFlowProp(  &pPcCommU->netFlows.mems[i]  );
				   }
				   break;
			 case  CONST_pcCommType_netShare:	//  2007/02/14
				   if  (  pPcCommU->netShares.cnt  >  mycountof(  pPcCommU->netShares.mems  )  )  goto  errLabel;
				   len  =  offsetof(  QY_PC_NETSHARES,  mems  )  +  pPcCommU->netShares.cnt  *  sizeof(  pPcCommU->netShares.mems[0]  );
				   //
				   for  (  i  =  0;  i  <  pPcCommU->netShares.cnt;  i  ++  )  {
					    qyhtonQyPcNetShareProp(  &pPcCommU->netShares.mems[i]  );
				   }
				   break;
			 default:
				   break;
					
	 }
#endif 
				  
	 MACRO_htonl(  pPcCommU->head.cnt  );
	 //
	 MACRO_htonl(  pPcCommU->head.iPlatformId  );
	 MACRO_htonl(  pPcCommU->head.uiLangId  );
	 MACRO_htonl(  pPcCommU->head.uiSize  );
	 MACRO_htonl(  pPcCommU->uiType  );

errLabel:

	 return  len;

}


 extern  "C"  int  qyntohQyPcCommU(  long  lhQwmVer,  QY_PC_COMMU  *  pPcCommU  )
{
	 int				len				=  -1;
	 unsigned  int		i;
	 WCHAR				wBuf[512]		=	L"";
	 QY_PC_COMMU		tmpPcCommU;					//  2006/09/06

	 MACRO_ntohl(  pPcCommU->head.iPlatformId  );
	 MACRO_ntohl(  pPcCommU->head.uiLangId  );
	 MACRO_ntohl(  pPcCommU->head.uiSize  );
	 MACRO_ntohl(  pPcCommU->uiType  );
	 //
	 MACRO_ntohl(  pPcCommU->head.cnt  );
 
	 if  (  pPcCommU->head.uiSize  >  sizeof(  QY_PC_COMMU  )  )  return  -1;

#if  0
	 switch  (  pPcCommU->uiType  )  {
			 case  CONST_pcCommType_process:
				   if  (  lhQwmVer  <=  326  )  {
				   	   if  (  pPcCommU->processesInfo0326.cnt  >  sizeof(  pPcCommU->processesInfo0326.mems  )  /  sizeof(  pPcCommU->processesInfo0326.mems[0]  )  )  return  -1;
				   	   for  (  i  =  0;  i  <  pPcCommU->processesInfo0326.cnt;  i  ++  )  {
						    qyntohQyProcessProp0326(  &pPcCommU->processesInfo0326.mems[i]  );
				   	   }
				   	   len  =  offsetof(  QY_PC_PROCESSES0326,  mems  )  +  pPcCommU->processesInfo0326.cnt  *  sizeof(  pPcCommU->processesInfo0326.mems[0]  );
					   //  ÔÙ½Ó×Å×ª»»µ½ÐÂµÄ½á¹¹, 2006/09/06
					   memset(  &tmpPcCommU,  0,  sizeof(  tmpPcCommU  )  );
					   memcpy(  &tmpPcCommU,  pPcCommU,  sizeof(  tmpPcCommU  )  );
					   for  (  i  =  0;  i  <  pPcCommU->head.cnt;  i  ++  )  {
						    memset(  &tmpPcCommU.processesInfo.mems[i],  0,  sizeof(  tmpPcCommU.processesInfo.mems[i]  )  );
						    memcpy(  &tmpPcCommU.processesInfo.mems[i],  &pPcCommU->processesInfo0326.mems[i],  min(  sizeof(  tmpPcCommU.processesInfo.mems[i]  ),  sizeof(  pPcCommU->processesInfo0326.mems[i]  )  )  );
					   }
					   memcpy(  pPcCommU,  &tmpPcCommU,  sizeof(  pPcCommU[0]  )  );
					   len  =  offsetof(  QY_PC_PROCESSES,  mems  )  +  pPcCommU->processesInfo.cnt  *  sizeof(  pPcCommU->processesInfo.mems[0]  );
						}
				   else  {		//  2006/09/06, Ôö¼ÓÐÂµÄ¶¨Òå£¬Ö÷Òª±ä»¯ÔÚprocessInfo.memsÀïÔö¼ÓÁËcmdLine
				   	     if  (  pPcCommU->processesInfo.cnt  >  mycountof(  pPcCommU->processesInfo.mems  )  )  return  -1;
				   	     for  (  i  =  0;  i  <  pPcCommU->processesInfo.cnt;  i  ++  )  {
						 	  qyntohQyProcessProp(  &pPcCommU->processesInfo.mems[i]  );
				   	   	 }
				   	   	 len  =  offsetof(  QY_PC_PROCESSES,  mems  )  +  pPcCommU->processesInfo.cnt  *  sizeof(  pPcCommU->processesInfo.mems[0]  );
				   }
				   break;
			 case  CONST_pcCommType_eventLog:
				   if  (  pPcCommU->eventLogsInfo.cnt  >  sizeof(  pPcCommU->eventLogsInfo.mems  )  /  sizeof(  pPcCommU->eventLogsInfo.mems[0]  )  )  return  -1;
				   for  (  i  =  0;  i  <  pPcCommU->eventLogsInfo.cnt;  i  ++  )  {
					    qyntohQyEventLogProp(  &pPcCommU->eventLogsInfo.mems[i]  );
				   }
				   len  =  offsetof(  QY_PC_EVENTLOGS,  mems  )  +  pPcCommU->eventLogsInfo.cnt  *  sizeof(  pPcCommU->eventLogsInfo.mems[0]  );
				   break;
			 case  CONST_pcCommType_usrInfo:
				   if  (  pPcCommU->head.cnt  >  sizeof(  pPcCommU->usrInfos.mems  )  /  sizeof(  pPcCommU->usrInfos.mems[0]  )  )  return  -1;
				   len  =  offsetof(  QY_PC_USRINFOS,  mems  )  +  pPcCommU->head.cnt  *  sizeof(  pPcCommU->usrInfos.mems[0]  );
				   break;
			 case  CONST_pcCommType_printers:
				   if  (  pPcCommU->head.cnt  >  sizeof(  pPcCommU->printers.mems  )  /  sizeof(  pPcCommU->printers.mems[0]  )  )  goto  errLabel;
				   len  =  offsetof(  QY_PC_PRINTERS,  mems  )  +  pPcCommU->head.cnt  *  sizeof(  pPcCommU->printers.mems[0]  );
				   break;
			 case  CONST_pcCommType_tcpTable:
				   if  (  pPcCommU->tcpTable.cnt  >  sizeof(  pPcCommU->tcpTable.mems  )  /  sizeof(  pPcCommU->tcpTable.mems[0]  )  )  goto  errLabel;
				   for  (  i  =  0;  i  <  pPcCommU->tcpTable.cnt;  i  ++  )  {
					    qyntohmyMIB_TCPROW(  &pPcCommU->tcpTable.mems[i]  );
				   }
				   len  =  offsetof(  QY_PC_TCPTABLE,  mems  )  +  pPcCommU->tcpTable.cnt  *  sizeof(  pPcCommU->tcpTable.mems[0]  );
				   break;
			 case  CONST_pcCommType_udpTable:
				   if  (  pPcCommU->udpTable.cnt  >  sizeof(  pPcCommU->udpTable.mems  )  /  sizeof(  pPcCommU->udpTable.mems[0]  )  )  goto  errLabel;
				   len  =  offsetof(  QY_PC_UDPTABLE,  mems  )  +  pPcCommU->udpTable.cnt  *  sizeof(  pPcCommU->udpTable.mems[0]  );
				   for  (  i  =  0;  i  <  pPcCommU->udpTable.cnt;  i  ++  )  {
					    qyntohmyMIB_UDPROW(  &pPcCommU->udpTable.mems[i]  );
				   }
				   break;
			 case  CONST_pcCommType_processModule:
				   if  (  pPcCommU->processModulesInfo.cnt  >  mycountof(  pPcCommU->processModulesInfo.mems  )  )  goto  errLabel;
				   len  =  offsetof(  QY_PC_PROCESSMODULES,  mems  )  +  pPcCommU->processModulesInfo.cnt  *  sizeof(  pPcCommU->processModulesInfo.mems[0]  );
				   for  (  i  =  0;  i  <  pPcCommU->processModulesInfo.cnt;  i  ++  )  {
					    //
				   }				   
				   break;
			 case  CONST_pcCommType_registryVal:
				   if  (  pPcCommU->registryVals.cnt  >  mycountof(  pPcCommU->registryVals.mems  )  )  goto  errLabel;
				   len  =  offsetof(  QY_PC_REGISTRYVALS,  mems  )  +  pPcCommU->registryVals.cnt  *  sizeof(  pPcCommU->registryVals.mems[0]  );
				   //
				   myUtf82WChar(  (  char  *  )pPcCommU->registryVals.wUsrName,  wBuf,  mycountof(  wBuf  )  );
				   safeWcsnCpy(  wBuf,  pPcCommU->registryVals.wUsrName,  mycountof(  pPcCommU->registryVals.wUsrName  )  );
				   //
				   for  (  i  =  0;  i  <  pPcCommU->registryVals.cnt;  i  ++  )  {
					    qyntohQyPcRegistryVal(  &pPcCommU->registryVals.mems[i]  );
				   }
				   break;
			 case  CONST_pcCommType_queryCfgs:
				   if  (  pPcCommU->queryCfgs.cnt  >  mycountof(  pPcCommU->queryCfgs.mems  )  )  goto  errLabel;
				   len  =  offsetof(  QY_PC_QUERYCFGS,  mems  )  +  pPcCommU->queryCfgs.cnt  *  sizeof(  pPcCommU->queryCfgs.mems[0]  );
				   //
				   for  (  i  =  0;  i  <  pPcCommU->queryCfgs.cnt;  i  ++  )  {
					    MACRO_ntohl(  pPcCommU->queryCfgs.mems[i].uiChangesId_fileMon  );
						MACRO_ntohl(  pPcCommU->queryCfgs.mems[i].uiQueryTimes  );
				   }
				   break;
			 case  CONST_pcCommType_netFlow:
				   if  (  pPcCommU->netFlows.cnt  >  mycountof(  pPcCommU->netFlows.mems  )  )  goto  errLabel;
				   len  =  offsetof(  QY_PC_NETFLOWS,  mems  )  +  pPcCommU->netFlows.cnt  *  sizeof(  pPcCommU->netFlows.mems[0]  );
				   //
				   for  (  i  =  0;  i  <  pPcCommU->netFlows.cnt;  i  ++  )  {
					    qyntohQyPcNetFlowProp(  &pPcCommU->netFlows.mems[i]  );
				   }
				   break;
			 case  CONST_pcCommType_netShare:
				   if  (  pPcCommU->netShares.cnt  >  mycountof(  pPcCommU->netShares.mems  )  )  goto  errLabel;
				   len  =  offsetof(  QY_PC_NETSHARES,  mems  )  +  pPcCommU->netShares.cnt  *  sizeof(  pPcCommU->netShares.mems[0]  );
				   //
				   for  (  i  =  0;  i  <  pPcCommU->netShares.cnt;  i  ++  )  {
					    qyntohQyPcNetShareProp(  &pPcCommU->netShares.mems[i]  );
				   }
				   break;
			 default:
				    break;
					
	 }
#endif 

errLabel:

	 return  len;

}


 /////////////////////////////////
 //
 //  2006/07/16
 extern  "C"  int  qyhtonQyPcRegistryRule(  QY_PC_REGISTRYRULE  *  p  )
{
	 WCHAR	wBuf[1024];

	 MACRO_htonl(  p->id  );
	 MACRO_htonl(  p->iRootKey  );
	 wcsncpy(  wBuf,  p->wSubKey,  mycountof(  wBuf  )  );  myWChar2Utf8(  wBuf,  (  char  *  )p->wSubKey,  sizeof(  p->wSubKey  )  );
	 wcsncpy(  wBuf,  p->wCfgName,  mycountof(  wBuf  )  );  myWChar2Utf8(  wBuf,  (  char  *  )p->wCfgName,  sizeof(  p->wCfgName  )  );

	 return  sizeof(  QY_PC_REGISTRYRULE  );
}

 //  2006/07/16
 extern  "C"  int  qyntohQyPcRegistryRule(  QY_PC_REGISTRYRULE  *  p  )
{
	 char		buf[1024];

	 MACRO_ntohl(  p->id  );
	 MACRO_ntohl(  p->iRootKey  );
	 safeStrnCpy(  (  char  *  )p->wSubKey,  buf,  sizeof(  buf  )  );  myUtf82WChar(  buf,  p->wSubKey,  mycountof(  p->wSubKey  )  );
	 safeStrnCpy(  (  char  *  )p->wCfgName,  buf,  sizeof(  buf  )  );  myUtf82WChar(  buf,  p->wCfgName,  mycountof(  p->wCfgName  )  );

	 return  sizeof(  QY_PC_REGISTRYRULE  );
}


 extern  "C"  int  qyhtonQyPcRulesU(  QY_PC_RULESU  *  pU  )
{
	 int				len		=	-1;
	 unsigned  int		i;
	 
#if  0
	 switch  (  pU->uiType  )  {
			 case  CONST_pcCommType_registryRule:
				   if  (  pU->registryRules.cnt  >  mycountof(  pU->registryRules.mems  )  )  goto  errLabel;
				   for  (  i  =  0;  i  <  pU->registryRules.cnt;  i  ++  )  {
					    qyhtonQyPcRegistryRule(  &pU->registryRules.mems[i]  );
				   }
				   len  =  offsetof(  QY_PC_REGISTRYRULES,  mems  )  +  pU->registryRules.cnt  *  sizeof(  pU->registryRules.mems[0]  );
				   MACRO_htonl(  pU->registryRules.cnt  );
				   break;
			 default:
					break;
	 }
#endif 

	 MACRO_htonl(  pU->head.uiType  );		 
	 MACRO_htonl(  pU->head.uiChangesId  );		 
errLabel:
	 return  len;
}

 extern  "C"  int  qyntohQyPcRulesU(  QY_PC_RULESU  *  pU  )
{
	 int				len		=	-1;
	 unsigned  int		i;

	 MACRO_ntohl(  pU->head.uiType  );		 
	 MACRO_ntohl(  pU->head.uiChangesId  );		 

#if  0
	 switch  (  pU->uiType  )  {
			 case  CONST_pcCommType_registryRule:
				   MACRO_ntohl(  pU->registryRules.cnt  );
				   if  (  pU->registryRules.cnt  >  mycountof(  pU->registryRules.mems  )  )  goto  errLabel;
				   for  (  i  =  0;  i  <  pU->registryRules.cnt;  i  ++  )  {
					    qyntohQyPcRegistryRule(  &pU->registryRules.mems[i]  );
				   }
				   len  =  offsetof(  QY_PC_REGISTRYRULES,  mems  )  +  pU->registryRules.cnt  *  sizeof(  pU->registryRules.mems[0]  );
				   break;
			 default:
					break;
	 }
#endif 


errLabel:
	 return  len;
}



 //
 //
 ///////////////////////////////////////////////


 
 //  intervalÓ¦ÒÔÃëÎªµ¥Î»
 extern  "C"  BOOL  b2TimeNear(  char  *  time1,  char  *  time2,  int  interval  )
{
	time_t t1, t2;

	t1 = gettTimeByBuf( time1 );
	t2 = gettTimeByBuf( time2 );
	if ( t1 == ( time_t )-1 || t2 == ( time_t )-1 ) return FALSE;
	if ( abs( t1 - t2 ) > abs( interval ) ) return FALSE;
	return TRUE;
}


 extern  "C"  int  getTimeByInterval(  char  *  oldTime,  int  interval,  char  *  newTime,  unsigned  int  newTimeSize  )
{
	time_t t1;

	if ( !oldTime || !newTime ) return -1; 
	t1 = gettTimeByBuf( oldTime );
	if ( t1 == ( time_t )-1 ) t1 = 0;
	t1 += interval;
	if ( t1 < 0 ) t1 = 0;

	getTimeStr(  t1,  newTime,  newTimeSize  );
	
	return 0;

}


///////////////////

 extern  "C"  char  *  qyStdToIp12(  char  *  ip,  char  *  ip12  )
{
	 unsigned  long  ulIp;

	 if  (  !ip  ||  !ip12  )  return  NULL;		//  2003/10/14
	 if  (  !ip[0]  )  return  NULL;				//  2011/02/05

	 ulIp  =  inet_addr(  ip  );
	 ulIp  =  qyntohl(  ulIp  );
	 sprintf(  ip12,  "%03d%03d%03d%03d",  MACRO_byte3(  ulIp  ),  MACRO_byte2(  ulIp  ),  MACRO_byte1(  ulIp  ),  MACRO_byte0(  ulIp  )  );
	 return  ip12;
}

 extern  "C"  char  *  qyIp12ToStd(  char  *  ip12,  char  *  ip  )
{
	 char			buf[12  +  1];
	 unsigned  char  b0, b1, b2, b3;

	 if  (  !ip12  ||  !ip  ||  strlen(  ip12  )  <  12  )  return  NULL;		//  2003/10/14

	 memcpy(  buf,  ip12,  12  );  buf[12]  =  0;
	 b0  =  (  unsigned  char  )atol(  buf  +  9  );
	 buf[9]  =  0;
	 b1  =  (  unsigned  char  )atol(  buf  +  6  );
	 buf[6]  =  0;
	 b2  =  (  unsigned  char  )atol(  buf  +  3  );
	 buf[3]  =  0;	 
	 b3  =  (  unsigned  char  )atol(  buf  );
	 
	 sprintf(  ip,  "%d.%d.%d.%d",  b3,  b2,  b1,  b0  );
	 return  ip;

}

 extern  "C"  char  *  ulIp2Str(  unsigned  long  lVal,  char  *  ip,  unsigned  int  size  )
{
	 struct  in_addr  tmpInAddr;
	 char  *			p;
	 
	 if  (  !ip  ||  size  <  CONST_qyMaxIpLen  +  1  )  return  NULL;

	 tmpInAddr.s_addr  =  lVal;
	 if  (  (  p  =  inet_ntoa(  tmpInAddr  )  )  )  safeStrnCpy(  p,  ip,  size  );

	 return  p  ?  ip  :  NULL;
}



//////////////////////////////////////////////



 extern  "C"  int  qySetRegCfgT(  HKEY  hRoot,  LPCTSTR  rootKey,  LPCTSTR  cfgName,  LPCTSTR  cfgVal  )
{
	int		iRet			=	-1;
	BOOL	bKeyCreated		=	FALSE;
	HKEY	hKey;
	int		rc				=	-1;
	// char buf[256];
	
	// wsprintf( buf, "%d", ASR_QUIT_VAL );

	if ( ( rc = RegCreateKeyEx( hRoot, rootKey, 0,  (TCHAR*)_T(  ""  ),  NULL,  KEY_ALL_ACCESS,  NULL,  &hKey,  NULL  ) ) != ERROR_SUCCESS ) {
		traceLogA(  (char*) "asrSetRegCfg( ): RegCreateKey( ) failed: %d", rc );
		goto errLabel;
	}
	bKeyCreated = TRUE;
	if  (  RegSetValueEx(  hKey,  cfgName,  0,  REG_SZ,  (  const  unsigned  char  *  )cfgVal,  sizeof(  TCHAR  )  *  (  lstrlen(  cfgVal  )  +  1  )  )  !=  ERROR_SUCCESS  )  {
		traceLogA(  (char*) "asrSetRegCfg( ): RegSetValueEx( ) failed." );
		goto  errLabel;
	}

	iRet = 0;

errLabel:

	if  (  bKeyCreated  )  RegCloseKey(  hKey  );

	return  iRet;

}


 extern  "C"  int  qyGetRegCfgT(  HKEY  hKeyRoot0,  LPCTSTR  rootKey,  LPCTSTR  cfgName,  char  *  cfgVal,  int  size,  unsigned  int  *  puiType  )
{
	int		iRet		=	-1;
	BOOL	bKeyOpen	=	FALSE;
	HKEY	hKey;
	int		lRet		=	0;
	long	cb;
	DWORD	type;
			
	if  (  !rootKey  || !rootKey[0]  )  return  -1;
	if  (  !hKeyRoot0  )  hKeyRoot0  =  HKEY_LOCAL_MACHINE;

	lRet  =  RegOpenKeyEx(  hKeyRoot0,  rootKey,  0,  KEY_QUERY_VALUE,  & hKey  );
	if  (  lRet  !=  ERROR_SUCCESS  )  {
		//  traceLogA(  (char*)  "qyGetRegCfg(  ):  RegOpenKey( %s )  failed.",  rootKey  );
		goto  errLabel;
	}
	bKeyOpen  =  TRUE;
	
	cb  =  size;
	if  (  RegQueryValueEx(  hKey,  cfgName,  0,  & type,  (  unsigned  char  *  )cfgVal, 
			(  unsigned  long  *  ) & cb  )  !=  ERROR_SUCCESS  ) 
	{
		//  traceLogA(  (char*)  "qyGetRegCfg(  ):  RegQueryValueEx( %s )  failed.",  cfgName  );
		goto errLabel;
	}
	//  2003/09/12¼ÓÈëÁË¶ÔÀàÐÍµÄÅÐ¶Ï£¬½ö¶Ô×Ö·û´®×÷½áÎ²
	if  (  type  ==  REG_SZ  ||  type  ==  REG_MULTI_SZ  ||  type  ==  REG_EXPAND_SZ   )  {
		if  (  cb  <  sizeof(  TCHAR  )  )  (  (  TCHAR  *  )cfgVal  )[0]	=	0;
		else  (  (  TCHAR  *  )cfgVal  )[cb  /  sizeof(  TCHAR  )  -  1] = 0;
	}
	
	iRet  =  0;
	
errLabel:

	if  (  bKeyOpen  )  RegCloseKey(  hKey  );

	if  (  !iRet  )  {
		if  (  puiType  )  *  puiType  =  type;		//  2004/08/06¼Ó
	}

	return iRet;

}


 extern  "C"  int  qyDelRegCfgT(  HKEY  hKeyRoot0,  LPCTSTR  rootKey,  LPCTSTR  cfgName  )
{
	int		iRet		=	-1;
	BOOL	bKeyOpen	=	FALSE;
	HKEY	hKey;
	long	lRet;
			
	if  (  !rootKey  || !rootKey[0]  )  return  -1;
	lRet  =  RegOpenKeyEx(  hKeyRoot0,  rootKey,  0,  KEY_SET_VALUE,  &hKey  );
	if  (  lRet  !=  ERROR_SUCCESS  )  {		
		goto  errLabel;
	}
	bKeyOpen  =  TRUE;

	if  (  ERROR_SUCCESS  !=  RegDeleteValue(  hKey,  cfgName  )  )  goto  errLabel;
	
	iRet  =  0;
	
errLabel:

	if  (  bKeyOpen  ) RegCloseKey(  hKey  );

	return  iRet;

}


///////////////////////// 2010/05/11

  extern  "C"  int  qySetRegCfgEx(  QY_REG  *  pReg,  LPCTSTR  cfgName,  LPCTSTR  cfgVal  ) 
{
	 int				iErr				=	-1;
	 
	 if  (  !pReg->pEncCtx  )  return  tmpSetRegCfgEx(  pReg,  cfgName,  (  char  *  )cfgVal,  0  );		//  2007/02/17

	 CQyMalloc		mallocObj_pCfgVal_utf8;
	 CQyMalloc		mallocObj_pxBuf;
	 CQyMalloc		mallocObj_ptBuf;
	 char		*	pCfgVal_utf8		=	NULL;
	 char			encBuf[1024];
	 char		*	pxBuf				=	NULL;
	 TCHAR		*	ptBuf				=	NULL;
	 unsigned  int	len;

	 len  =  1024;
	 pCfgVal_utf8  =  mallocObj_pCfgVal_utf8.mallocf(  len  );
	 if  (  !pCfgVal_utf8  )  goto  errLabel;
	 if  (  !myTChar2Utf8(  cfgVal,  pCfgVal_utf8,  len  )  )  goto  errLabel;
	 pCfgVal_utf8[len  -  1]  =  0;

	 len  =  sizeof(  encBuf  );
	 if  (  qnmEncStr(  pReg->pEncCtx,  pCfgVal_utf8,  encBuf,  &len  )  )  goto  errLabel;
	 encBuf[sizeof(  encBuf  )  -  1]  =  0;

	 pxBuf  =  mallocObj_pxBuf.mallocf(  len  *  2  +  1  );
	 if  (  !pxBuf  )  goto  errLabel;

	 qybuf2x(  encBuf,  len,  pxBuf  );
	 len  =  len  *  2;
	 pxBuf[len]  =  0;

	 ptBuf  =  (  TCHAR  *  )mallocObj_ptBuf.mallocf(  (  len  +  1  )  *  sizeof(  TCHAR  )  );
	 if  (  !ptBuf  )  goto  errLabel;
	 if  (  !myUtf82TChar(  pxBuf,  ptBuf,  len  +  1  )  )  goto  errLabel;
	 ptBuf[len]  =  0;

	 if  (  tmpSetRegCfgEx(  pReg,  cfgName,  (  char  *  )ptBuf,  0  )  )  goto  errLabel;	//  2007/02/17, ÐÞ¸ÄÉÏÃæµÄ»°£¬ÒÔ±ãÄÜ¹»Ð´µ½hkey_current_userÏÂÃæ

	 iErr  =  0;

errLabel:

	 return  iErr;

}

   //  
 extern  "C"  int  qyGetRegCfgEx(  QY_REG  *  pReg,  LPCTSTR  cfgName,  char  *  cfgVal,  int  size  )
{
	 int			iErr	=	-1;
	 
	 if  (  !pReg->pEncCtx  )  {
		 //  return  tmp_qyGetRegCfg1(  pReg->hKeyRoot0,  pReg->rootKey,  cfgName,  (  LPBYTE  )cfgVal,  size,  &pReg->uiType  );
		 return  tmpGetRegCfgEx(  pReg,  cfgName,  cfgVal,  (  unsigned  int  *  )&size  );
	 }
	 
	 CQyMalloc			mallocObj_ptBuf;
	 CQyMalloc			mallocObj_pxBuf;
	 CQyMalloc			mallocObj_pEncBuf;
	 unsigned  int		uiCnt_ptBuf		=	2048;
	 TCHAR			*	ptBuf			=	(  TCHAR  *  )mallocObj_ptBuf.mallocf(  uiCnt_ptBuf  *  sizeof(  TCHAR  )  );
	 if  (  !ptBuf  )  goto  errLabel;
	 char* pxBuf;pxBuf = NULL;
	 char* pEncBuf;pEncBuf = NULL;
	 unsigned  int		len;
	 unsigned  int		cfgValLen;

	 int  tmp_size;tmp_size = uiCnt_ptBuf * sizeof(TCHAR);
	 if  (  tmpGetRegCfgEx(  pReg,  cfgName,  (  char  *  )ptBuf,  (  unsigned  int  *  )&tmp_size  )  )  goto  errLabel;
	 ptBuf[uiCnt_ptBuf  -  1]  =  0;
	 pxBuf  =  mallocObj_pxBuf.mallocf(  tmp_size  );
	 if  (  !pxBuf  )  goto  errLabel;
	 myTChar2Utf8(  ptBuf,  pxBuf,  tmp_size  );
	 pxBuf[tmp_size  -  1]  =  0;

	 len  =  strlen(  pxBuf  )  /  2;
	 pEncBuf  =  mallocObj_pEncBuf.mallocf(  len  +  1  );
	 if  (  !pEncBuf  )  goto  errLabel;
	 if  (  qyx2buf(  pxBuf,  strlen(  pxBuf ),  pEncBuf  )  !=  len  )  goto  errLabel;
	 pEncBuf[len]  =  0;

#if  0
	 cfgValLen  =  size;
	 if  (  qnmDec(  pReg->pEncCtx,  pEncBuf,  len,  cfgVal,  &cfgValLen  )  )  goto  errLabel;
	 if  (  (  int  )cfgValLen  >=  size  )  goto  errLabel;
	 cfgVal[cfgValLen]  =  0;
#endif

	 cfgValLen  =  tmp_size;
	 if  (  qnmDec(  pReg->pEncCtx,  pEncBuf,  len,  pxBuf,  &cfgValLen  )  )  goto  errLabel;
	 if  (  (  int  )cfgValLen  >=  tmp_size  )  goto  errLabel;
	 pxBuf[cfgValLen]  =  0;

	 if  (  !myUtf82TChar(  pxBuf,  (  TCHAR  *  )cfgVal,  size  /  sizeof(  TCHAR  )  )  )  goto  errLabel;

	 pReg->uiType  =  REG_SZ;

	 iErr  =  0;

errLabel:

	 return  iErr;

}

//  利用新老程序的加密与解密，可以将新老程序的qySetRegDataEx等做成一样的
 //  qySetRegCfgEx可能还是需要的，针对字符串，而data是针对数据流的

  extern  "C"  int  qySetRegDataEx(  QY_REG  *  pReg,  LPCTSTR  cfgName,  char  *  data,  unsigned  long  dataLen  )
{
	 int			iErr				=	-1;
	 
	 if  (  !pReg->pEncCtx  )  return  -1;

	 CQyMalloc			mallocObj_pEncBuf;
	 CQyMalloc			mallocObj_pxBuf;
	 CQyMalloc			mallocObj_ptBuf;
	 char			*	pEncBuf				=	NULL;
	 char			*	pxBuf				=	NULL;
	 TCHAR			*	ptBuf				=	NULL;
	 unsigned  int		len;
	 unsigned  int		uiType;

	 uiType  =  pReg->uiType;		//  ÏÂÃæÒªÒÔreg_szÀ´´æ´¢£¬¹ÊÐèÒª±£ÁôÒ»ÏÂÕâ¸öuiTypeÒÔ±ã»Ö¸´£¬2007/02/18

	 len  =  1024;
	 pEncBuf  =  mallocObj_pEncBuf.mallocf(  len  );
	 if  (  !pEncBuf  )  goto  errLabel;
	 if  (  qnmEncData(  pReg->pEncCtx,  data,  dataLen,  pEncBuf,  &len  )  )  goto  errLabel;

	 pxBuf  =  mallocObj_pxBuf.mallocf(  2  *  len  +  1  );
	 if  (  !pxBuf  )  goto  errLabel;

	 qybuf2x(  pEncBuf,  len,  pxBuf  );
	 len  =  2  *  len;
	 pxBuf[len]  =  0;

	 ptBuf  =  (  TCHAR  *  )mallocObj_ptBuf.mallocf(  (  len  +  1  )  *  sizeof(  TCHAR  )  );
	 if  (  !ptBuf  )  goto  errLabel;
	 if  (  !myUtf82TChar(  pxBuf,  ptBuf,  len  +  1  )  )  goto  errLabel;
	 ptBuf[len]  =  0;

	 //  if  (  qySetRegCfg(  pReg->rootKey,  cfgName,  xBuf  )  )  goto  errLabel;
	 pReg->uiType  =  0;
	 if  (  tmpSetRegCfgEx(  pReg,  cfgName,  (  char  *  )ptBuf,  len  *  sizeof(  TCHAR  )  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 pReg->uiType  =  uiType;

	 return  iErr;

}


  extern  "C"  int  qyGetRegDataEx(  QY_REG  *  pReg,  LPCTSTR  cfgName,  char  *  cfgVal,  unsigned  long  *  pDataLen  )
{
	 int	iErr	=	-1;
	 
	 if  (  !pReg->pEncCtx  )  return  -1;

	 CQyMalloc			mallocObj_ptBuf;
	 CQyMalloc			mallocObj_pxBuf;
	 CQyMalloc			mallocObj_pEncBuf;
	 unsigned  int		uiCnt_ptBuf		=	2048;
	 TCHAR			*	ptBuf			=	(  TCHAR  *  )mallocObj_ptBuf.mallocf(  uiCnt_ptBuf  *  sizeof(  TCHAR  )  );
	 if  (  !ptBuf  )  goto  errLabel;
	 char* pxBuf;pxBuf = NULL;
	 char* pEncBuf;pEncBuf = NULL;
	 unsigned  int		len;
	 unsigned  int		cfgValLen;

	 int  tmp_size;tmp_size = uiCnt_ptBuf * sizeof(TCHAR);
	 if  (  tmpGetRegCfgEx(  pReg,  cfgName,  (  char  *  )ptBuf,  (  unsigned  int  *  )&tmp_size  )  )  goto  errLabel;
	 ptBuf[uiCnt_ptBuf  -  1]  =  0;
	 pxBuf  =  mallocObj_pxBuf.mallocf(  tmp_size  );
	 if  (  !pxBuf  )  goto  errLabel;
	 myTChar2Utf8(  ptBuf,  pxBuf,  tmp_size  );
	 pxBuf[tmp_size  -  1]  =  0;

	 len  =  strlen(  pxBuf  )  /  2;
	 pEncBuf  =  mallocObj_pEncBuf.mallocf(  len  +  1  );
	 if  (  !pEncBuf  )  goto  errLabel;
	 if  (  qyx2buf(  pxBuf,  strlen(  pxBuf ),  pEncBuf  )  !=  len  )  goto  errLabel;
	 pEncBuf[len]  =  0;

	 cfgValLen  =  *pDataLen;
	 if  (  qnmDecData(  pReg->pEncCtx,  pEncBuf,  len,  cfgVal,  &cfgValLen  )  )  goto  errLabel;
	 if  (  (  int  )cfgValLen  >  *pDataLen  )  goto  errLabel;

	 *pDataLen  =  cfgValLen;

	 pReg->uiType  =  REG_BINARY;

	 iErr  =  0;

errLabel:

	 return  iErr;


}







/////////////////////////////


  //  Ö¸ÌØ¶¨µÄÇý¶¯, ½öÔÚwin2kÏÂÊ¹ÓÃ
 extern  "C"  int  qnmInstallDriver(  unsigned  short  idrData,  char  *  drvName  )
{
	 int		iErr  =  -1;
	 TCHAR		drvFile[CONST_qyMaxPathLen  +  1];
	 TCHAR		winDir[CONST_qyMaxPathLen  +  1];
	 //  char		buf[CONST_qyMaxPathLen  +  1];

	 if  (  !drvName  ||  !drvName[0]  ||  strlen(  drvName  )  >  64  )  goto  errLabel;

	 if  (  myGetSystemDirectory(  winDir,  sizeof(  winDir  )  /  sizeof(  winDir[0]  )  )  ==  0  )  goto  errLabel;
	 wsprintf(  drvFile,  _T(  "%s\\drivers\\%s"  ),  winDir,  drvName  );
	 if  (  0xFFFFFFFF  !=  GetFileAttributes(  drvFile  )  )  {
		 iErr  =  0;  goto  errLabel;
	 }

	 //  myTChar2Str(  drvFile,  buf,  sizeof(  buf  )  );
	 //	if  (  qyOutputResourceFile(  idrData,  buf  )  )  goto  errLabel;  //  Éú³É²¢Æô¶¯ÊÜ¿Ø¶Ë³ÌÐò
	 if  (  qyOutputResourceFile(  idrData,  drvFile  )  )  goto  errLabel;  //  Éú³É²¢Æô¶¯ÊÜ¿Ø¶Ë³ÌÐò

	 iErr  =  0;
errLabel:
	 return  iErr;
}

 //  Í¨¹ýÅÐ¶Ï¸½´øµÄdllÊÇ·ñ´æÔÚµÄ·½Ê½À´ÅÐ¶ÏÇý¶¯ÊÇ·ñÎÒÃÇ°²×°£¬´Ó¶ø¾ö¶¨ÊÇ·ñÉ¾³ý
 extern  "C"  int  qnmRemoveDriver(  char  *  drvName,  PF_qyDelService  pf  )
{
	 int				iErr								=	-1;
	 TCHAR				fullFileName[CONST_qyMaxPathLen  +  1];
	 TCHAR				winDir[CONST_qyMaxPathLen  +  1];
	 unsigned  char		ucbDllExists						=	FALSE;

	 if  (  !drvName  ||  !drvName[0]  ||  strlen(  drvName  )  >  64  ||  !pf  )  goto  errLabel;

	 if  (  myGetSystemDirectory(  winDir,  sizeof(  winDir  )  )  ==  0  )  goto  errLabel;
	 wsprintf(  fullFileName,  _T(  "%s\\packet.dll"  ),  winDir  );
	 if  (  -1  !=  GetFileAttributes(  fullFileName  )  )  {
		 traceLogA(  (char*)  "%s exists",  fullFileName  );
		 ucbDllExists  =  TRUE;
	 }
	 if  (  !ucbDllExists  )  {
		 wsprintf(  fullFileName,  _T(  "%s\\wpcap.dll"  ),  winDir  );
		 if  (  -1  !=  GetFileAttributes(  fullFileName  )  )  {
			 traceLogA(  (char*)  "%s exists",  fullFileName  );
			 ucbDllExists  =  TRUE;
		 }
	 }

	 if  (  ucbDllExists  )  {
		 traceLogA(  (char*)  "Õâ¸öÇý¶¯²»ÊÇÎÒÃÇ×°µÄ, ²»ÓÃÉ¾³ý"  );
		 iErr  = 0;  goto  errLabel;
	 }

	 wsprintf(  fullFileName,  _T(  "%s\\drivers\\%s"  ),  winDir,  drvName  );
	 if  (  -1  ==  GetFileAttributes(  fullFileName  )  )  {
		 traceLogA(  (char*)  "Çý¶¯ÒÑÉ¾³ý"  );
		 iErr  =  0;  goto  errLabel;
	 }

	 if  (  pf(  (  char  *  )CONST_NPFServiceName  )  )  goto  errLabel;
	 
	 DeleteFile(  fullFileName  );
	 iErr  =  0;

errLabel:

	 return  iErr;

}




 extern  "C"  int  makeQwmAuthInfo(  char  *  ver,  QWM_MACS_INFO  *  pMacsInfo,  QNM_COMM_AUTHINFO  *  pAuthInfo  )
{
	 int  i  =  0;

	 if  (  !pAuthInfo  )  return  -1;

	 if  (  ver  )  memcpy(  pAuthInfo->ver,  ver,  sizeof(  pAuthInfo->ver  )  );
	 if  (  pMacsInfo  )  {
		 for  (  i  =  0;  i  <  min(  pMacsInfo->nMacs,  CONST_qnmMaxMacs  );  i  ++  )  {	//  2006/06/02, ¶ÔnMacs¼ÓÁËºÍCONST_qnmMaxMacsµÄ±È½Ï
			  memcpy(  pAuthInfo->macs[i],  pMacsInfo->macs[i],  CONST_qyMacLen  );
	 	 }
	 }
	 return  0;	 
}




 extern  "C"  int  qwmGetPcName(  char  *  pcName,  unsigned  int  len  )
{
	 int				iErr	=	-1;
	 //  TCHAR				tBuf[MAX_COMPUTERNAME_LENGTH  +  1];
	 TCHAR				tBuf[15  +  1];
	 unsigned  int		tmpLen  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
	 
	 if  (  !myGetComputerName(  tBuf,  (  unsigned  long  *  )&tmpLen  )  )  goto  errLabel;		 	 
	 if  (  !myTChar2Str(  tBuf,  pcName,  len  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:
	
	 return  iErr;
}


 extern  "C"  int  qnmOpenSession(  char  *  servIp,  unsigned  short  usPort,  QWM_MACS_INFO  *  pMacsInfo,  unsigned  char  ucCmd,  int  iServiceId,  char  *  ver,  void  *  pCommEncCtx,  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  char  *  data,  unsigned  int  *piDataSize  )
{
	 int					iErr			=  -1;	 
	 char					ip[16];
	 QNM_COMM_AUTHINFO		authInfo;
	 QY_COMM_RESP			tmpResp;
	 char					tmpBuf[4096];

	 if  (  !ucCmd  )  {
		 if  (  !pMacsInfo  ||  !pMacsInfo->nMacs  )  return  -1;
	 }

	 if  (  !bQySockOpen(  pSock  )  )  {		//  Èç¹ûÇ°ÃæÒÑ½¨Á¢Á¬½Ó£¬Ôò²»ÐèÒª½¨Á¢ÐÂÁ¬½Ó
		 if  (  qyConnect(  servIp,  usPort,  pSock,  pTo->iConnect  )  )  {
			 goto  errLabel;
		 }
	 }
	 if  (  getLocalIpBySocket(  pSock->sockFd,  ip  )  )  goto  errLabel;
	 memset(  &authInfo,  0,  sizeof(  authInfo  )  );
	 if  (  makeQwmAuthInfo(  ver,  pMacsInfo,  &authInfo  )  )  goto  errLabel;
	 memcpy(  authInfo.ip,  ip,  sizeof(  authInfo.ip  )  );
	 authInfo.cmd  =  ucCmd;

	 if  (  qyTellService(  iServiceId,  ver,  pCommEncCtx,  (  char  *  )&authInfo,  sizeof(  authInfo  ),  pSock,  pTo,  pSession  )  )  goto  errLabel;
	 if  (  qyRecvResp(  pSession,  pSock,  pTo,  &tmpResp,  tmpBuf,  sizeof(  tmpBuf  )  )  )  goto  errLabel;
	 //  traceLogA(  (char*)  "qwmOpenSession: get respCode of qyTellService is %s",  qyGetDesByType1(  CONST_qyRcTable,  tmpResp.head.usCode  )  );
	 //  ÕâÀï²»ÄÜÓÃÀ´ÅÐ¶Ï·µ»ØÂë£¬ÒòÎªÊÇÍ¨ÓÃµÄ½Ó¿Ú£¬Ó¦ÔÚÆäËûµØ·½ÅÐ¶Ï£¬2005/06/25
	 //  if  (  !isRcOk(  tmpResp.head.usCode  )  )  goto  errLabel; 

	 iErr  =  0;

errLabel:
	 
	 if  (  iErr  )  {
		 if  (  bQySockOpen(  pSock  )  )  qyDisconnect(  pSock  );
		}
	 else  {
		   if  (  piDataSize  &&  data  )  {
			   *piDataSize  =  min(  *piDataSize,  tmpResp.head.len  );
			   memcpy(  data,  tmpBuf,  *piDataSize  );
		   }
	 }

	 return  iErr;
}


 extern  "C"  void  qnmCloseSession(  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo  )
{
	 QY_COMM_RESP			tmpResp;

	 if  (  bQySockOpen(  pSock  )  )  {
		 if  (  isRcOk(  pSession->usLastRespCode_i  )  ||  pSession->usLastRespCode_i  ==  CONST_qyRc_user  )  {
			 if  (  !qySendReq(  pSession,  pSock,  pTo,  CONST_qyCmd_end,  NULL,  0  )  )  {
				qyRecvResp(  pSession,  pSock,  pTo,  &tmpResp,  NULL,  0  );
			 }
		 }
		 qyDisconnect(  pSock  );
	 }
	 return;
}



 extern  "C"  int  getQyEnv(  void  *  pDynLibs,  QY_ENV  *  pEnv  )
{
	int			iErr			=	-1;
	int			iPlatformId		=	0;

	if  (  !pEnv  )  goto  errLabel;

	memset(  pEnv,  0,  sizeof(  pEnv[0]  )  );
 	if  (  !bQyGetSystemVersionEx(  &iPlatformId,  pEnv->systemBuf,  mycountof(  pEnv->systemBuf  ),  pEnv->servicePackBuf,  mycountof(  pEnv->servicePackBuf  ),  NULL  )  )  goto  errLabel;
	pEnv->iPlatformId  =  iPlatformId;
	switch  (  pEnv->iPlatformId  )  {
			case  CONST_qyPlatform_win32:
			case  CONST_qyPlatform_win95:
				  goto  errLabel;
			case  CONST_qyPlatform_win98:
			case  CONST_qyPlatform_winme:
				  pEnv->svRunKey  =  (TCHAR*)_T(  CONST_qyCfgName_98RunKey  );
			  	  break;	
			case  CONST_qyPlatform_winCe:						//  2010/04/06
				  //
				  break;
			default:
					pEnv->ucbWinNt  =  TRUE;					//  2007/02/20
				    pEnv->svRunKey  =  (TCHAR*)_T(  CONST_qyCfgName_ntRunKey  );
				    break;
	}

	pEnv->usLangId  =  GetSystemDefaultLangID(  );

	pEnv->pDynLibs  =  pDynLibs;

	SYSTEM_INFO	systemInfo;
	GetSystemInfo(  &systemInfo  );
	pEnv->dwPageSize  =  systemInfo.dwPageSize;
	myIsWow64Process(  pEnv,  GetCurrentProcess(  ),  &pEnv->bWow64Process  );

	//  2008/11/19
	#ifdef  __DEBUG__
			pEnv->bDebugInfo  =  TRUE;
			#if  defined(  __WINCE__  )  &&  defined(  __TEST__  )
				 pEnv->iPlatformId  =  CONST_qyPlatform_winCe;
			#endif
	#endif
	if  (  pEnv->bDebugInfo  )  {
		traceLogA(  (char*)  "Note: getQyEnv: bDebugInfo is true"  );
	}

	iErr  =  0;
errLabel:
	return  iErr;
}




 extern  "C"  int  parseQwmDynCfg(  char  *  pQyCfgs,  unsigned  int  uiCfgSize,  QWM_DYN_CFG  *  pDynCfg  )
{
	 char			*	p					=	NULL;
	 char				buf[1024];
	 int				index;
	 char			*	pCfgName;


	 if  (  !pQyCfgs  ||  !pDynCfg  )  return  -1;
	 if  (  strlen(  pQyCfgs  )  >=  uiCfgSize  )  {
		 traceLogA(  (char*)  "Dynamic cfgs string is too long"  );  return  -1;
	 }

	 memset(  pDynCfg,  0,  sizeof(  pDynCfg[0]  )  );

	 p  =  qwmGetCfg(  pQyCfgs,  (char*)CONST_qyCfgName_cntIp,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 if  (  inet_addr(  p  )  !=  INADDR_NONE  )  {
			 safeStrnCpy(  buf,  pDynCfg->cnt.cntIp,  sizeof(  pDynCfg->cnt.cntIp  )  );		 
		 }
	 }		
	 //
	 index  =  0;	pCfgName  =  (char*)CONST_qyCfgName_cntAddr1;
	 p  =  qwmGetCfg(  pQyCfgs,  pCfgName,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 safeStrnCpy(  buf,  pDynCfg->cnt.cntAddrs[index],  sizeof(  pDynCfg->cnt.cntAddrs[index]  )  );
	 }
	 //
	 index  ++  ;	pCfgName  =  (char*)CONST_qyCfgName_cntAddr2;
	 p  =  qwmGetCfg(  pQyCfgs,  pCfgName,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 safeStrnCpy(  buf,  pDynCfg->cnt.cntAddrs[index],  sizeof(  pDynCfg->cnt.cntAddrs[index]  )  );
	 }
	 //
#if  0
	 index  ++  ;	pCfgName  =  CONST_qyCfgName_cntAddr3;
	 p  =  qwmGetCfg(  pQyCfgs,  pCfgName,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 safeStrnCpy(  buf,  pDynCfg->cnt.cntAddrs[index],  sizeof(  pDynCfg->cnt.cntAddrs[index]  )  );
	 }
#endif
	  

	 //
	 p  =  qwmGetCfg(  pQyCfgs,  (char*)CONST_qyCfgName_cntPort,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 pDynCfg->cnt.usCntPort  =  (  unsigned  short  )atol(  buf  );
	 }	 

	 //
#if 0
	 TCHAR  tBuf[128];
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "port %d"  ),  (int)pDynCfg->cnt.usCntPort  );
	 MessageBox(  0,  tBuf,  _T(  "qycx.com"  ),  MB_OK  );
#endif


	 //
	 return  0;
}





 extern  "C"  int  getIpFromName(  char  *  name,  char  *  ip,  unsigned  int  size  )
{
	 int						iErr	=	-1;
     struct  in_addr			addr;
	 struct  hostent		*	host	=	NULL;
	 char					*	p		=	NULL;
	 
	 if  (  !name  ||  !name[0]  ||  !ip  ||  size  <=  CONST_qyMaxIpLen  )  goto  errLabel;

	 if  (  bIpValid(  name  )  )  {
		 safeStrnCpy(  name,  ip,  size  );
		 iErr  =  0;  goto  errLabel;
	 }

	 if  (  !(  host  =  gethostbyname(  name  )  )  )  goto  errLabel;

	 if  (  !host->h_addr_list  &&  !host->h_addr_list[0]  )  goto  errLabel;
	 memcpy( &addr,  host->h_addr_list[0],  sizeof(  struct  in_addr  )  );

	 if  (  !(  p  =  inet_ntoa(  addr  )  )  )  goto  errLabel;
	 _snprintf(  ip,  size,  "%s",  p  );

	 iErr  =  0;
errLabel:
	 return  iErr;
}


  //  ¿¿´Ëº¯ÊýÀ´´ÓdynCfgÖÐÈ·¶¨ÕæÕýÊ¹ÓÃµÄcntµÄipºÍport
 extern  "C"  int  getCorrectCnt(  QY_ENV  *  pEnv,  QWM_DYN_CFG  *  pDynCfg,  PF_bServConnected  pf_bServConnected,  void  *  pParam,  int  serviceId,  char  *  ver,  QY_ENC_CTX  *  pCommEncCtx,  __int64  i64StartTime_base,  SOCK_TIMEOUT  *  pTo,  QY_LOGICAL_SERVER  *  pCnt  )
{
	 int		iErr							=  -1;
	 char		ip[CONST_qyMaxIpLen  +  1];
	 char	*	pAddrs[mycountof(  pDynCfg->cnt.cntAddrs  )  +  1];
	 int		i;

	 if  (  !pDynCfg  ||  !pCnt  ||  !pf_bServConnected  )  goto  errLabel;

	 memset(  pAddrs,  0,  sizeof(  pAddrs  )  );
	 pAddrs[0]  =	pDynCfg->cnt.cntIp;
	 pAddrs[1]  =	pDynCfg->cnt.cntAddrs[0];
	 pAddrs[2]  =	pDynCfg->cnt.cntAddrs[1];
	 MACRO_qyAssert(  3  <=  mycountof(  pAddrs  ),  _T(  "overflow"  )  );

	 for  (  i  =  0;  i  <  mycountof(  pAddrs  );  i  ++  )  {
		  //
#if  1  //  def  __DEBUG__
		 if (0) {
			 TCHAR  tBuf[128];
			 _sntprintf(tBuf, mycountof(tBuf), _T("getCorrect: addrs[%d] is %S"), i, pAddrs[i]);
			 showInfo_open0(0, 0, tBuf);
			 int  ii = 0;
		 }
#endif
		  //
		  if  (  getIpFromName(  pAddrs[i],  ip,  sizeof(  ip  )  )  )  continue;
		  
		  #if  0	//  2013/04/06. ip的末尾为0或者255时,不一定表明是广播地址,要看掩码.所以这里不能过滤掉
				if  (  !bIpValid(  ip  )  )  continue;
		  #endif
		  
		  //  2007/02/21, ÔÚÉ½¶«Ì©±¦£¬·¢ÏÖÈç¹û¶¯Ì¬ÓòÃûÓÐÊ±»á½âÎö³É127.0.0.1, Îª·ÀÖ¹ÕâÖÖÏÖÏó¡£Òª¶ÔIP½øÐÐ¹ýÂË¡£µ«ÊÇÈç¹ûpAddrs[i]Îª127.0.0.1Ôò²»¹ýÂË
		  if  (  !_stricmp(  ip,  CONST_ip_localhost  )  )  {
			  if  (  _stricmp(  pAddrs[i],  CONST_ip_localhost  )  )  continue;
		  }
		  if  (  pf_bServConnected(  pEnv,  ip,  pDynCfg->cnt.usCntPort,  pParam,  serviceId,  ver,  pCommEncCtx,  i64StartTime_base,  pTo  )  )  break;
	 }

	 if  (  i  ==  mycountof(  pAddrs  )  )  goto  errLabel;

	 memset(  pCnt,  0,  sizeof(  pCnt[0]  )  );
	 safeStrnCpy(  ip,  pCnt->ip,  sizeof(  pCnt->ip  )  );
	 pCnt->port  =  pDynCfg->cnt.usCntPort;

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
	 }

	 return  iErr;

}


 extern  "C"  BOOL  bQnmModuleInstalled(  char  *  rootKey_mc,  char  *  moduleName  )
{
	 BOOL				bRet		=	FALSE;
	 char				buf[1024];
	 HKEY				hKey		=	NULL;
	 TCHAR				tBuf[1024];
	 
	 _snprintf(  buf,  sizeof(  buf  ),  "%s\\%s\\%s",  rootKey_mc,  CONST_qyModulesSubKey,  moduleName  );
	 /*
	 lstrcpyn(  buf,  CONST_qyRootKey_mc,  sizeof(  buf  )  );
	 lstrcpyn(  buf  +  lstrlen(  buf  ),  "\\",  sizeof(  buf  )  -  lstrlen(  buf  )  );
	 lstrcpyn(  buf  +  lstrlen(  buf  ),  CONST_qyModulesSubKey,  sizeof(  buf  )  -  lstrlen(  buf  )  );
	 lstrcpyn(  buf  +  lstrlen(  buf  ),  "\\",  sizeof(  buf  )  -  lstrlen(  buf  )  );
	 lstrcpyn(  buf  +  lstrlen(  buf  ),  moduleName,  sizeof(  buf  )  -  lstrlen(  buf  )  );
	 */

	 myStr2TChar(  buf,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	 if  (  ERROR_SUCCESS  ==  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  tBuf,  0,  KEY_QUERY_VALUE,  &hKey  )  )  {
		 bRet  =  TRUE;
		 RegCloseKey(  hKey  );
	 }

	 return  bRet;
	 
}


 extern  "C"  int  getQnmModulesLoadedInfo(  QNM_MODULES_LOADEDINFO  *  p  )
{
	 if  (  !p  )  return  -1;

	 memset(  p,  0,  sizeof(  p[0]  )  );

	 p->ulbNetMc2ModuleLoaded		=  bQnmModuleInstalled(  (char*)CONST_qyRootKey_mc, (char*)CONST_qyModuleName_netMc2  );
	 p->ulbNmsModuleLoaded			=  bQnmModuleInstalled((char*)CONST_qyRootKey_mc, (char*)CONST_qyModuleName_nms  );
	 p->ulbNetFlowModuleLoaded		=  bQnmModuleInstalled((char*)CONST_qyRootKey_mc, (char*)CONST_qyModuleName_netFlow  );
	 p->ulbSecChkModuleLoaded		=  bQnmModuleInstalled((char*)CONST_qyRootKey_mc, (char*)CONST_qyModuleName_secChk  );
	 //  p->ulbNetMc4ModuleLoaded		=  bQnmModuleInstalled(  CONST_qyRootKey_mc,  CONST_qyModuleName_netMc4  );
	 p->ulbAssetMgrModuleLoaded		=  bQnmModuleInstalled((char*)CONST_qyRootKey_mc, (char*)CONST_qyModuleName_assetMgr  );
	 //
	 p->ulbMsgrMgrModuleLoaded		=  bQnmModuleInstalled((char*)CONST_qyRootKey_mc_mis, (char*)CONST_qyModuleName_msgrMgr  );

	 //
	 p->ulbServiceNetMcLoaded  =  (  p->ulbNetMc2ModuleLoaded  ||  p->ulbNmsModuleLoaded  ||  p->ulbNetFlowModuleLoaded  ||  p->ulbSecChkModuleLoaded  ||  p->ulbAssetMgrModuleLoaded  );
	 p->ulbServiceMisLoaded  =  (  p->ulbMsgrMgrModuleLoaded  );
	 return  0;
}




 extern  "C"  int  getDirAndFinalName_win(  LPCTSTR  svFileName,  TCHAR  *  dirName,  unsigned  int  size,  TCHAR  *  finalName,  unsigned  int  finalNameSize    )
{
	TCHAR  *  pFinalModuleName			=	NULL;
	
	if  (  !svFileName  ||  !lstrlen(  svFileName  )  )  return  -1;

	pFinalModuleName  =  (  TCHAR  *  )_tcsrchr(  svFileName,  _T(  '\\'  )  );
	if  (  pFinalModuleName  )  {
		if  (  finalName  &&  finalNameSize  )  lstrcpyn(  finalName,  pFinalModuleName  +  1,  finalNameSize  );
		if  (  dirName  &&  size  )  lstrcpyn(  dirName,  svFileName,  min(  size,  (  unsigned  int  )(  pFinalModuleName  -  svFileName  +  2  )  )  );
		return  0;
	}

	return  -1;
}





#ifdef  __DEBUG__


 extern  "C"  int  printQwmMacsInfo(  char  *  hint,  QWM_MACS_INFO  *  pMacsInfo  )
{
	 traceLogA(  (char*)  "nMacs is %d,  mac0 is %s, mac1 is %s, mac2 is %s",  pMacsInfo->nMacs,  pMacsInfo->macs[0],  pMacsInfo->macs[1],  pMacsInfo->macs[2]  );
	 return  0;
}



 extern  "C"  int  printQnmRegInfo(  QNM_REG_INFO  *  pRegInfo  )
{
	 /* 
 	 int	i;	 

	 traceLogA(  (char*)  "mac0 is [%s]",  pRegInfo->mac0  );
	 for  (  i  =  0;  i  <  sizeof(  pRegInfo->u.cols  )  /  sizeof(  pRegInfo->u.cols[0]  );  i  ++  )  {
		  traceLogA(  (char*)  "%d×Ö¶Î,  %S,  [%S]",  i,  qyGetDesByType1(  CONST_fieldIdTable,  pRegInfo->uiFieldIds[i]  ),  pRegInfo->u.cols[i]  );
	 }
	 */
	 return  0;
}


#endif


