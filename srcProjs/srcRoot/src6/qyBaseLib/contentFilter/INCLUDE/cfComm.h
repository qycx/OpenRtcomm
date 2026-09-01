


#ifndef  __CFCOMM_H__
#define  __CFCOMM_H__	/* { */

#define		CF_CMD_LOG_FILE_TRANSFER	1
#define		CF_CMD_DICT_FILE_TRANSFER	2
#define		CF_CMD_ON					3
#define		CF_CMD_QUERY_STATUS			4
#define		CF_CMD_QUERY_DICT			5


#define		CF_RESP_CODE_LEN			2

typedef  struct  __cf_comm_head_t  {
				 char					cmd;
				 union	{
						struct	{
								char	fileName[256];
								int		fileLen;
						}				fileTransfer;
						struct	{
								char	bCFOn;
								char	bCFLogOn;
						}				on;
				}						u;
}		 CF_COMM_HEAD;


#define CF_RC_OK	"OK"
#define CF_RC_ERR	"ER"

typedef struct __cf_comm_resp_t {
	char respCode[CF_RESP_CODE_LEN + 1];
} CF_COMM_RESP;

typedef struct __cf_comm_resp_head_t {
	char respCode[CF_RESP_CODE_LEN + 1];
	union {
		struct {
			char bDictOn;
			char bCFOn;
			char bCFLogOn;
		} queryStatus;
		struct {
			int len;
		} dict;
	} u;
} CF_COMM_RESP_HEAD;



#endif /* } __CFCOMM_H__ */




