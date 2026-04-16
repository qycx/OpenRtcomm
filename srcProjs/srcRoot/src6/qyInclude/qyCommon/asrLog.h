
#ifndef  __ASR_LOG_H__
#define  __ASR_LOG_H__	/* { */

#include  "asrObjs.h"


typedef  struct  __asr_log_context_t	{
				 char					unused;
}		 ASR_LOG_CONTEXT;

#define		RCD_LEN								90		//  76 + 12 mac地址占用12个字节  
#define		RULE_LEN							51		//  21 lastScanTime14个字节，mac 12个字节
#define		REM_REC_LEN							95		//  81 + 14 新增加了[mac]



#define		ASR_RAS_ILLEG						1
#define		ASR_RAS_ON							2
#define		ASR_RAS_OFF							3

//#define	ASR_RAS_ILLEG						AWM_ACTION_RAS_ILLEG
//#define	ASR_RAS_ON							AWM_ACTION_RAS_ON
//#define	ASR_RAS_OFF							AWM_ACTION_RAS_OFF

typedef  struct  __awm_log_rcd_t			{
	
				 unsigned  char				type;
				 unsigned  short			proto;	// reserved.
				 unsigned  char				time[14 + 1];
				 unsigned  char				level;
				 unsigned  short			action;	
				 unsigned  char				phonenum[20 + 1];
				 unsigned  char				ip[15 + 1];
				 unsigned  char				mac[12 + 1];
}		 AWM_LOG_RCD;

typedef  struct  __awm_rule_rcd_t  {
	
				 unsigned  char				ip[15 + 1];
				 unsigned  char				level;
				 unsigned  char				lastScanTime[14 + 1];
				 unsigned  char				mac[12 + 1];

}		 AWM_RULE_RCD;

typedef  struct  __asr_log_rcd_t	{
			union					{
				AWM_LOG_RCD			awmLogRcd;
			}						u;
}		 ASR_LOG_RCD;



int sndSavedTmpLog( ASR_LOG_CONTEXT *pAsrLogContex, char *fileName );



#endif /* } */

