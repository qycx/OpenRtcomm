

#ifndef  __CFCOMMON_H__
#define  __CFCOMMON_H__  /*  {  */


#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>

#if  0
	#include	<sys/types.h>
#endif

// #include	<unistd.h>	
// this modified by frank because we cant find this header in vc++
#include	<string.h>
// #include	<sys/socket.h>
// #include	<netinet/in.h>
// #include	<arpa/inet.h>
// #include	<netdb.h>
#include	<math.h>

#if  0
#include	<errno.h>
#endif

// #include </usr/include/linux/types.h>
// #include	<sys/wait.h>

#include	"qyCommon.h"
/*
#include	"qyTypes.h"
#include	"qyDefs.h"
#include	"commondefs.h"
#include	"commonFunc.h"
#include	"qyCommonDefs5.h"
#include	"qyCommonFunc5.h"
*/
#include	"vardefine.h"
#include	"cfComm.h"

#define		NET_BUF_LEN								65535
#define		SAVE_OPTION_NUM							4
#define		OPTION_FILE_LEN							1024
// #define	MAX_DIR_LEN								256  +  1
#define		MAX_ASCIP_LEN							15  +  1
#define		FILE_INITSETUP 							"initsetup.dat"
#define		SECTION_WORKDIR 						"[HOSTWORKDIR]"
#define		SECTION_GETFILE_IP 						"[GETFILEIP]"
#define		SECTION_GETFILE_DIR						"[GETFILEDIR]"
#define		SECTION_SAVE_DIR						"[HOSTSAVEDIR]"


// #define	MAXLINE 								1024
#define		MAX_STATEMSG_LEN						40

#define		SYS_VER_OFF 							0	//  comunication protocal version offset
#define		SYS_VER									1	//  system version
#define		SYS_CHILD_FLAG_OFF 						1	//  child system flag offset
#define		SYS_MONITOR_CENTER						1	//  monitor center identifier
#define		SYS_KEY_FILTER							6	//  key filter child system identifier
#define		SYS_MSG_TYPE_OFF 						2	//  message type flag offset
#define		SYS_ACT_MSG								1	//  child system live state message
#define		SYS_ERROR_MSG							2	//  child system error message
#define		SYS_SETUP_MSG							3	//  child system setup message
#define		SYS_WARN_MSG							4	//  child system warn message
#define		SYS_DATA_LEN_OFF 						4	//  transported data length offset(2 byte)
#define		SYS_DATA_OFF 							6	//  data offset
#define		PROT_HEAD_LEN							6	//  the protocal head length


// (keys filter child system)combuf+SYS_CHILD_FLAG_OFF=6
// state message(key filter child system transport to monitor center)
#define		STAT_KEY_RUN_OFF						(  PROT_HEAD_LEN  +  0  )	//  run state(1byte)
#define		STAT_KEY_NORMAL							0x1							//	running normal
#define		STAT_KEY_PAUSE 							0x2							//	no keys

#define		STAT_KEY_CPU_OFF 						(  PROT_HEAD_LEN  +  1  )	//  cpu used percent offset(1 BYTE)
#define		STAT_KEY_MEM_OFF 						(  PROT_HEAD_LEN  +  2  )	//  mem used percent offset(1 BYTE)
#define		STAT_KEY_DISK_OFF 						(  PROT_HEAD_LEN  +  3  )	//  disk used percent offset(1 BYTE)
#define		STAT_KEY_GETDIR_OFF						(  PROT_HEAD_LEN  +  4  )	//  get dir offset(4byte)
#define		STAT_KEY_MSG_LEN						8

#define		ERROR_KEY_RIGHT							0x00						//  no error
// ERROR message(key filter child system transort to monitor center)
#define		WARN_KEY_FLAG							(  PROT_HEAD_LEN  +  0  )
#define		WARN_KEY_NOKEY 							0x01						//	nokey error
#define		WARN_KEY_GETDIR 						0x02						//	get file dir error
#define		WARN_KEY_PUTDIR 						0x03						//	put file dir error
#define		WARN_KEY_DIR_OFF						(  PROT_HEAD_LEN  +  1  )

// setup message(key filter center transport to analyse child system)
#define		SET_KEY_TYPE_OFF						(  PROT_HEAD_LEN  +  0  )
#define		SET_KEY_ADD_KEY							0x01						//	add new keys
#define		SET_KEY_DEL_KEY 						0x02						//	delete keys
#define		SET_KEY_GETDIR							0x03						//	setup get file dir
#define		SET_KEY_PUTDIR							0x04						//	setup put file dir
#define		SET_KEY_ADD_EMAIL						0x05						//	add new email_box
#define		SET_KEY_MOD_RESET						0x06						//	module reset
#define		SET_KEY_MAC_RESET						0x07						//	machine reset
#define		SET_KEY_PAUSE							0x08						//	program pause

#define		SET_KEY_ENDFLAG_OFF						(  PROT_HEAD_LEN  +  1  )
#define		SET_KEY_NOTEND							0x01
#define		SET_KEY_END								0x02

#define		SET_KEY_NUM_OFF							(  PROT_HEAD_LEN  +  2  )	//	add or delete keys number offset(4BYTE)
#define		SET_KEY_OFF								(  PROT_HEAD_LEN  +  6  )	//	add or delete keys offset
#define		SET_KEY_NUMLEN							4

//  以下是CF_KEY的成员长度定义
// #define	SET_KEY_KEYLEN							40
// #define	SET_KEY_DIRLEN							20
#define		SET_KEY_KEYLEN							64							// 注：	SET_KEY_KEYLEN 
#define		SET_KEY_DIRLEN							4							//		和 SET_KEY_DIRLEN须是4的倍数
#define		SET_KEY_USRLEN							100
#define		SET_KEY_LANGLEN							1
#define		SET_KEY_VALLEN							2
#define		SET_KEY_TYPEINFOLEN						4							//  added by ywm.
#define		SET_KEY_LENGTH							(  SET_KEY_KEYLEN  +  SET_KEY_DIRLEN  +  SET_KEY_LANGLEN  +  SET_KEY_VALLEN  +  SET_KEY_TYPEINFOLEN  )

#define		SET_KEY_DIR_OFF							(  PROT_HEAD_LEN  +  1  )	//	get dir offset
#define		SET_KEY_EMAILLEN						128
#define		SET_KEY_EMAIL_LENGTH					(  SET_KEY_EMAILLEN  +  SET_KEY_USRLEN  +  SET_KEY_VALLEN  )

#define		SET_KEY_KEYOFF							0							//	40 BYTE
#define		SET_KEY_DIROFF							40							//	20 BYTE
#define		SET_KEY_LANGOFF							60							//	1 BYTE
#define		SET_KEY_VALUEOFF						61							//	2 BYTE

#define		SET_KEY_EMAILOFF						0							//	128 BYTE
#define		SET_KEY_USROFF							128							//	100 BYTE
#define		SET_KEY_EMAILVALUEOFF					228							//	2 BYTE

#ifdef  __cplusplus
  extern  "C"  {
#endif

typedef  struct  __cf_key_t  {
				 char								key[SET_KEY_KEYLEN];
				 char								direction[SET_KEY_DIRLEN];
				 char								language[SET_KEY_LANGLEN];
				 char								value[SET_KEY_VALLEN];
				 char								typeInfo[SET_KEY_TYPEINFOLEN];
}		 CF_KEY;



#ifdef  __cplusplus
  }
#endif

// #define MIN_DICT_AVAILABLE						500000
#define		MIN_DICT_AVAILABLE						5000

#endif  __CFCOMMON_H__  /*  }  */



