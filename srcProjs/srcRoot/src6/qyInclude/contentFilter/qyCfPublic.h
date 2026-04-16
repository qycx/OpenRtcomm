
#ifndef  __QYCFPUBLIC_H__
#define  __QYCFPUBLIC_H__	/* { */


#ifdef  __cplusplus
  extern  "C"  {
#endif

  //  以下宏从keyValue.h中取出.
#define		OFF_ART_TYPE				55					//  protocol type 1byte
// #define	ART_TYPE_HTTP				0
#define		ART_TYPE_UNKNOWN			99					// Modified by ywm on 2002/08/04
#define		ART_TYPE_SMTP				1
#define		ART_TYPE_POP3				2
#define		ART_TYPE_FTP				3
#define		ART_TYPE_HTTP				4					// Modified by ywm on 2002/08/04

  //  以下宏从keyValue.h中取出.
  //  文字类型，扩展为key的类型
#define		CS_LANGUAGE					1
	#define		CS_LANGTYPE_UNKNOWN		99					//  以后作为CS_LANGUAGE的子类型					
	#define		CS_LANGTYPE_EN			1					//  以后作为CS_LANGUAGE的子类型
	#define		CS_LANGTYPE_GB			2					//  以后作为CS_LANGUAGE的子类型
	#define		CS_LANGTYPE_BIG5		3					//  以后作为CS_LANGUAGE的子类型
#define		CS_URL						2
	#define		CS_URLTYPE_HTTP			1


  // key的级别
#define		CF_OK						0					// 允许
#define		CF_DENY						(  (  int  )'D'  )	// 拒绝或禁止
#define		CF_WARNING					(  (  int  )'W'  )
#define		CF_WAIT						(  (  int  )'T'  )	
#define		CF_ALERT					(  (  int  )'A'  )	

#define		QY_IMC_URLDICTNAME			"url.txt"
#define		QY_IMC_GBDICTNAME			"gb.txt"
#define		QY_IMC_BIG5DICTNAME			"big5.txt"

#define		MAX_N_MATCHED_AND_STOP		99999
#define		DEFAULT_N_MATCHED_AND_STOP	2

#define		QY_CF_MAX_CONTEXT_LEN		128								//  关键字匹配后，取得上下文的最大字数
#define		CONTEXT_N_LEFT				5								//  关键字匹配后，取得上下文的上文字数

typedef  int  (  * PF_cfPreSetupDict  )(  void  *  pCfFile,  FILE  *  fp,  void  *  opStruct  );
typedef  int  (  * PF_cfGetPhrase  )(  void  *  pCfFile,  FILE  *  fp,  char  *  buf,  unsigned  int  len,  int  *  lang,  int  *  pKeyTypeCode,  int  *  level  );
typedef  int  (  * QY_CF_CALLBACK  )(  void  * p1,  void  *  p2  );		//  此函数为内容过滤而设，
																		//  当返回0时，过滤继续


#define		CONST_qyCfKeyTypeNameLen	8



typedef  struct  __qyCfOpStruct_t  {
				 char					op[2];
				 char					keyTypeName[8];
}		 QY_CFOP_STRUCT;
																		//  非0时，过滤中断。

typedef  struct  __qyCfFile_t  {
				 QY_FILE_HEAD			head;
				 QY_FILE_OBJHEAD		curObjHead;
				 unsigned  char			curLangMode;
				 long					curlTypeInfo;
				 unsigned  long			curObjLen;						//  尚未读出的对象长度 
				 //  int				type;							//  使用上面key的类型
				 char					fileName[64];	
				 PF_cfPreSetupDict		preSetupDict;
				 PF_cfGetPhrase			getPhrase;
}		 QY_CF_FILE;


typedef  struct  __qyCfStruct_t  {
				 QY_BUF		*			pSharedDataBuf;
				 const char	*			pDictDir;
				 int					cfFileCnt;
				 QY_CF_FILE	*			pCfFiles;
				 BOOL					bDictRefreshed;
}		 QY_CF_STRUCT;


typedef  struct  __cf_info_t  {
				 unsigned char			cArtType;			/*  __u8  */
				 unsigned char			cArtLangMode;		/*  __u8  */
				 char					serviceType[3];

				 short 					value;
				 char *					pKey;
				 unsigned int			keyLen;
				 char			*		pContext;
				 unsigned int			contextLen;
				 QY_CFOP_STRUCT	*		pOpInfo;			/*  与value关联的操作模式  */

				 BOOL 					bCFLogOn;
				 unsigned int			nMatchedAndStop;	// n次匹配后则停止这一次过滤。	
				 QY_CF_CALLBACK			pfCallback;
				 void *					pVoid1;			
				 void *					pVoid2;
}		 CF_INFO;

int				initCF(  QY_CF_STRUCT  *  p  );
void			exitCF(  );
void			cfIncIeCnt(  );
int				cfGetIeCnt(  );
unsigned  int	uCfDealArticle(  char  *  pcFileBuf,  unsigned  int  dwFileLen,  CF_INFO  *  pCI,  void  *  pDb  );
unsigned  int	uCfDealAddr(  char  *  serviceType,  char  *  pcAddrBuf,  unsigned  int  dwAddrLen,  CF_INFO  *  pCI,  void  *  pDb  );
void			showDict(  );


#ifdef __cplusplus
  }
#endif

#endif /* } */

