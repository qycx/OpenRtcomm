
#ifndef __AWMCOMM_H__
#define __AWMCOMM_H__	/* { */

/*
1.暗绿->（绿闪烁）->亮绿->超时->暗绿
    | |   	         |
    | |   	          ->暗绿
    | ->（红闪烁）->黄->超长时->暗绿
    |
    ->超更长时->消失
*/

//     仅有 AWM_STATUS_NORMAL、AWM_STATUS_WARNING、AWM_STATUS_RAS_ON
// 三个状态会在状态消息里发送


#define AWM_STATUS_NORMAL		1
#define AWM_STATUS_ALERT		2
#define AWM_STATUS_WARNING		3
#define AWM_STATUS_DEL			4	// 要被删除的节点
// #define AWM_STATUS_ERASE		5	// 弃用
#define AWM_STATUS_RAS_ON		6
#define AWM_STATUS_EMPTY		7	// 组状态

#define AWM_SUB_STATUS_1		1
#define AWM_SUB_STATUS_2		2

#define AWM_ACTION_RAS_ILLEG    1
#define AWM_ACTION_RAS_ON		2
#define AWM_ACTION_RAS_OFF      3

#define ASR_CMD_TELL_WM_INFO	105

#define AWM_MSG_STATUS_INFO		1
#define AWM_MSG_CFG				2	//级别修改
#define AWM_MSG_ACTION			3

typedef struct __awm_comm_msg_t {
	int msgId;
	int len;
	union {
		struct {
			unsigned long ulIp;
			unsigned char level;
			char time[15];
			int iStatus;
		} status;
		struct {
			unsigned long ulIp;
			unsigned char level;
			char time[15];
		} cfg;
		struct {
			unsigned long ulIp;
			unsigned char level;
			char time[15];
			int iAction;
		} action;
	} u;
} AWM_COMM_MSG;

#endif /* } */


