
#ifndef  __CONTENTFILTER_H__
#define  __CONTENTFILTER_H__	/* { */


#include	"qyCommon.h"
#include	"vardefine.h"
#include	"commonfunc.h"
#include	"keyvalue.h"
#include	"cfCfg.h"

#ifndef  __WITH_9C__
  #define  __WITH_9C__
#endif


typedef  struct  __cf_dict_t  {
				 int							size;			// total memory( file ) size for dict can use.
				 int							type;
				 QY_CFOP_STRUCT					opInfos[256];
				 struct  KeyHashHead			KeyHash[HASH_LEN];
				 __u64							KeyIndex[INDEX_LEN];
				 char  *						pStart;
				 char  *						pEnd;
}		CF_DICT;


typedef  struct  __env_struct_t  {
}		ENV_STRUCT;

typedef  struct  __cfg_struct_t  {
	
				 int							sysLogFlg;
	
				 union	{ 		
						CF_CFG_STRUCT			cCS;
				 }								var;
}		 CFG_STRUCT;

typedef  struct  __shm_cfg_space_t {
				 char			*				setupDictShmAddr;			//  共享内存在创建进程中的地址
				 unsigned  char					bDictChanged;
				 unsigned  char					bDictOn;
				 unsigned  char					bCFOn;
				 unsigned  char					bCFLogOn;
				 unsigned  int					iIeCnt;						//  IE操作的计数器，用以表明IE的访问。
}		 SHM_CFG_SPACE;

#define		SHM_CFG_SPACE_LEN					sizeof( SHM_CFG_SPACE )

typedef  struct  __status_struct_t  {

				 int							primaryErrNo;				/*It primarily determines what shall do next*/
				 int							generalErrNo;	
				 #ifdef __PROXY_DEBUG__
						int						debugOPtion;
				 #endif

}		 STATUS_STRUCT;	

typedef  struct  __session_info_t  {
				 
				 int							charsetType;
				 int							contentType;
				 char	*						pTmpB;
				 int							bSize;
				 int							bLen;
				 char	*						pTmpS;
				 int							sSize;
				 int							sLen;

}		 SESSION_INFO;

typedef  struct  __session_buf_t  {
}		 SESSION_BUF;

typedef  struct  __qy_cf_gbuf_struct_t  {

				 ENV_STRUCT						env;
				 CFG_STRUCT						cfg;
				 char			*				shmAddr;
				 int							shmSize;
				 SHM_CFG_SPACE	*				pShmCfgSpace;
				 int							cfDictCnt;
				 CF_DICT		*				pCFDict[TOTAL_CF_DICTS];
	
				 //  const char	*				pCfDictFile;

				 //  special setup for every server
				 //  MSGHANDLER	*				pMsgHandler;	//  TOTALSMTPCMDS
				 //  *****************************

				 STATUS_STRUCT					status;
	
}		 QY_CF_GBUF_STRUCT;



//#define	initDoCF						initHttpCF
#define		KeyHash							gpCFDict[0]->KeyHash
#define		KeyIndex						gpCFDict[0]->KeyIndex

extern	int	 giShmDiff ;
extern	CF_DICT	*	gpCFDict[TOTAL_CF_DICTS];

extern	void  showHashUnit(  HashUnit  *  p  );
extern	void  showKeyHashHead(  KeyHashHead  *  p  );
int  getCFDictAvailable(  CF_DICT  *  p  );


#endif /* } */

