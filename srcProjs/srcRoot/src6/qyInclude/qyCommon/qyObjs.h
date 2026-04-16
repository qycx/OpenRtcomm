
#ifndef  __QYOBJS_H__
#define  __QYOBJS_H__	/*  {  */

#include	"qyDefs.h"


typedef  struct  __qyLogicalServer_t		{
				 char						ip[QY_MAXIPLEN + 1];
				 unsigned  short			port;
}		 QY_LOGICAL_SERVER;


typedef  struct  __qwmMacsInfo_t			{
				 unsigned  char				macs[CONST_qnmMaxMacs][CONST_qyMacLen  +  1];
				 unsigned  char				nMacs;
}		 QWM_MACS_INFO;


typedef  struct  __qyFileHead_t				{
				 char						objName[8];
				 char						ver[4];
}		 QY_FILE_HEAD;


typedef  struct  __qyFileEnd_t				{
				 char						endFlg[4];
}		 QY_FILE_END;


typedef  struct  __qyFileObjHead_t			{
				 char						objName[8];
				 char						objLenStr[8];						//  objHead
}		 QY_FILE_OBJHEAD;




//
typedef  struct  __qyEnv_t					{
				 int						iEnvType;
				 unsigned  int				iPlatformId;
				 TCHAR						systemBuf[128];						//  2003/09/12Ìí¼Ó
				 TCHAR						servicePackBuf[128];				//  2003/09/12Ìí¼Ó
				 TCHAR					*	svRunKey;
				 unsigned  char				ucbWinNt;							//  2003/11/21Ìí¼Ó£¬ÊÇ·ñÊÇNTÏµÁÐ(nt,2k,xp...)
				 LANGID						usLangId;							//  ²Ù×÷ÏµÍ³ÓïÑÔÀàÐÍ£¬2005/11/03
				 void					*	pDynLibs;							//  2007/01/21

				 //
				 DWORD						dwPageSize;							//  2010/04/25
				 BOOL						bWow64Process;						//  2010/05/15

				 //
				 BOOL						bDebugInfo;							//  2008/11/19. ÊÇ·ñÏÔÊ¾Ò»Ð©debugÐÅÏ¢£¬¶ÔÔÚrelease°æ±¾ÏÂÏÔÊ¾Ä³Ð©ÐÅÏ¢ÓÐÓÃ

				 void					*	pShmMemory;							//  2010/04/26
				 void					*	pTmpMemorys;						//  2010/09/18

}		 QY_ENV;

//  typedef		QY_ENV  *						PF_qyEnv;							//  2012/12/07

//
#define		MACRO_qyAppCommonMems		int			iSystemType_reserved;	\
										int			iSystemId;				\
										int			iAppType;				\
										int			iAppId;					\
										int			iCustomId;				\
									    int			iServiceId;				\
										char		ver[CONST_qyMaxVerLen  +  1];


#define		MACRO_qyModuleCommonMems	int			iSystemType_reserved;	\
										int			iSystemId;				\
										int			iModuleType;			\
										int			iModuleId;				\
										int			iCustomId;

#endif  /*  }  */

