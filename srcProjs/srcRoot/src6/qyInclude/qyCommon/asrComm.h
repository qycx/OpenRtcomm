
#ifndef  __CFCOMM_H__
#define  __CFCOMM_H__	/* { */

#define		MAX_ASR_VERSION_LEN					14

#define		ASR_RAS_ROOT_RUN_KEY				"Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define		ASR_RAS_RUN_TRANS_KEY				"asrCfTrans"

// #define	ASR_RAS_ROOT_SUB_KEY				"Software\\asr\\awm\\doCfg"
#define		ASR_RAS_WORKDIR_CFG					"installPath"

#define		CF_ROOT_RUN_KEY						"Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define		CF_RUN_TRANS_KEY					"asrCfTrans"

#define		CF_ROOT_SUB_KEY						"Software\\asr\\awm\\trans"
#define		CF_WORKDIR_CFG						"installPath"
#define		DEAMON_LCK_FILE						"trans.lck"
#define		CLIENT_LCK_FILE						"client.lck"


#define		ASR_SERVICE_RAS_MONITORING			1

#define		ASR_CMD_QUERY_SERVICE				101
#define		ASR_CMD_LOG_RCD_TRANSFER			102
#define		ASR_CMD_CFG_TRANSFER				103
#define		ASR_CMD_TELL_SERVICE				104
#define		ASR_CMD_RULE_TRANSFER				105
#define		ASR_CMD_PROXY_MGR_INFO_TRANSFER		106
#define		ASR_CMD_CLIENT_CHECK_INVALID		107

	
#define		ASR_RESP_CODE_LEN					2

#define		ASR_DENY							( (int) 'D' )	
#define		ASR_OFFLINE							( (int) 'N' )
#define		ASR_PERMIT							( (int) 'W' )	
#define		ASR_ERROR							( (int) 'E' )

#define		ASR_RC_OK							"OK"
#define		ASR_RC_ERR							"ER"

#define		AWM_STATUS_NORMAL					1
#define		AWM_STATUS_ALERT					2
#define		AWM_STATUS_WARNING					3
#define		AWM_STATUS_DEL						4	// 要被删除的节点
#define		AWM_STATUS_ERASE					5
#define		AWM_STATUS_RASON					6


typedef  struct  __asr_comm_head_t  {
				 int				cmd;
				 unsigned  char		ip[15 + 1];
				 union  {
					struct  {
						char fileName[256];
						int fileLen;
					} fileTransfer;
					struct  {
						int iLogRcds;
					} logRcdTransfer;
					struct {
						int serviceId;
						char groupName[20 + 1];
					} tellService;
					struct {
						int iStatus;
					} tellStatus;
					struct {
						char version[MAX_ASR_VERSION_LEN + 1];
					} proxyMgrInfo;
					struct {
						unsigned char mac[12 + 1];	//12个字节的MAC二进制数
					} cfgInfo;		
				 } u;
}		ASR_COMM_HEAD;


#define		CFG_ID_AWM_LEVEL_ID						1
#define		CFG_ID_AWM_SERVER_IP					2
#define		CFG_ID_AWM_UPDATE_TIME					3
#define		CFG_ID_AWM_REAL_UPDATE_TIME				4
#define		CFG_ID_AWM_PROXY_MGR_INFO				5	
#define		CFG_ID_AWM_PROXY_SCRIPT_INFO			6

typedef  struct  __awm_cfg_content_t  {

				 int			cfgId;
				 int			len;
				 union	{
					 struct		{
						 char	levelId;
					 }			rasLevel;
					 struct		{
						 char	serverIp[15 + 1];
					 }			serverIp;
					 struct		{
						 char	updateTime[14 + 1];
					 }			liveUpdate;
					 struct		{
						 char	stopMon[1 + 1];
					 }			mgrInfo;
					 struct		{
						 char	stopScript[1 + 1];
					 }			mgrScript;
				 }				u;
}		 AWM_CFG_CONTENT;


typedef  struct  __asr_comm_resp_head_t  {
	
				 char				respCode[ASR_RESP_CODE_LEN + 1];
				 union  {
					 struct  {
						 int		serviceId;
					 }				queryService;
					 struct  {
						 int		nCfgs;
					 }				cfg;
				 }	u;
				 char				strTime[15];
				 long				indexId;
				 BOOL				bQuit;

}		 ASR_COMM_RESP_HEAD;

/*  描述受控端程序是否被破坏的结构
typedef  struct  __awm_control_client_info_t  {
				 BOOL				bFileDel;			  
				 BOOL				bModified;
				 BOOL				bNODel;
				 BOOL				bRunDel;
				 char				lastWriteTime[15];
}		 AWM_CONTROL_CLIENT_INFO;
*/

#endif /* } __CFCOMM_H__ */

