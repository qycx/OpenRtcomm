
#ifndef  __VARDEFINE_H__
#define  __VARDEFINE_H__	/*  {  */ 



// #define	CS_UNKNOWN					99
// #define	CS_GB						1
// #define	CS_BIG5						2
// #define	CS_EN						3


#define		MAX_IP_ADDR_LEN				15
#define		MAX_FULL_FILE_NAME_LEN		255
#define		MAX_DIR_LEN					255

#define		TOTAL_CF_DICTS				2

#define		__u64						unsigned __int64
#define		__u32						unsigned __int32
#define		__u16						unsigned __int16
#define		__u8						unsigned __int8
#define		__s16						__int16
#define		__s32						__int32


#define		TMP_B_BUF_SIZE				8192
#define		TMP_S_BUF_SIZE				4096

#define		CF_DICT_GB_IND				0
#define		CF_DICT_BIG5_IND			1
#define		CF_SAVE_WORDS				10


#define		CF_CONTENT_TEXT_HTML		0

#define		lseek						_lseek

#define		On							1
#define		Off							0

#define		_8M							8192000
#define		_2k							2048
#ifndef		__WITH_9C__
  #define	__WITH_9C__
#endif

#define		MAX_FILE_NAME_LEN			2048


#endif	/*  }  */

