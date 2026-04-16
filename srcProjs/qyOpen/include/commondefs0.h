
/*
**	COMMONDEFS.H -- COMMONDEFS.H -- some common definitions
*/


#ifndef __COMMONDEFS_H__
#define __COMMONDEFS_H__	/* { */

#if !defined( BOOL )
 #define BOOL int
#endif

#if !defined( bool )
	#define bool BOOL
#endif

#if !defined( TRUE ) && !defined( FALSE )
	#define TRUE 1
	#define FALSE 0
#endif

#if !defined( ON ) && !defined( OFF )
	#define ON 0
	#define OFF -1
#endif

#if !defined( SUCCESS ) && !defined( FAILURE )
	#define SUCCESS 0
	#define FAILURE -1
#endif 

#if !defined( INVALID_PID )
	#define INVALID_PID -1
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif
#ifndef max
	#define max(x,y)	((x)>(y)?(x):(y))
#endif

# define bitset(bit, word)	(((word) & (bit)) != 0)

#ifndef MAX_IP_ADDR_LEN
	#define MAX_IP_ADDR_LEN	15
#endif

#define OCTET_STR	0

#ifndef SIG_HANDLER	
	typedef void (*SIG_HANDLER)(int);
#endif

#define TYPE_SIZE(type,x) ( sizeof(x)/sizeof(type) )
#define STRUCT_MEM_SIZE(struct_typ,mem)	sizeof( ((struct_typ *)0)->mem )

typedef struct __msg_buf_t {

	int mType;
	char mText[1];

 }		MSG_BUF;

#define MAX_DIR_LEN			255
#define MAX_FULL_FILE_NAME_LEN		255
#define MAX_FILE_NAME_LEN_WITHOUT_DIR	255


#define RC_SUCCESS	0
#define RC_FAILURE	-1
#define RC_TIMEOUT	-2
#define RC_EOF		-3
#define RC_INTERRUPTED	-4
#define RC_TIMEOUTX	-5


#endif	/* } __COMMONDEFS_H__ defined */


