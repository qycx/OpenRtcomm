
#ifndef  __QYIMCCOMMONCFG_H__
#define  __QYIMCCOMMONCFG_H__	/*  {  */


#define		QY_IMC_TMPLOGFILEID_VAL						( "lf" )			// 若设为"2"则取TMPLOGFILE2, 
																			// 否则取TMPLOGFILE1
#define		QY_IMC_TMPLOGFILE1PROCEDLEN_VAL				( "lf1L" )
#define		QY_IMC_TMPLOGFILE2PROCEDLEN_VAL				( "lf2L" )

#define		QY_IMC_TMPLOGFILE1_ID						1
#define		QY_IMC_TMPLOGFILE2_ID						2
#ifdef  __DEBUG__
	#define		QY_IMC_TMPLOGFILE1						"cf1.log"
	#define		QY_IMC_TMPLOGFILE2						"cf2.log"
#else
	#define		QY_IMC_TMPLOGFILE1						"~mns1.tmp"
	#define		QY_IMC_TMPLOGFILE2						"~mns2.tmp"
#endif

#define		QY_IMC_MAXTMPLOGSIZE						1000000


#define		DEFAULT_QY_IMC_INFO_FILE					( "~DFqD3F.tmp" )
#define		DEFAULT_PHYS_MEMORY_MIN_SIZE				48000000			// 48M可用内存仅允许使用FILE_MIN_SIZE的共享内存
#define		DEFAULT_QY_IMC_INFO_MIN_SIZE				1000000				// 应能容纳10000个URL
#define		DEFAULT_QY_IMC_INFO_SIZE					3000000				// 应能容纳10000个URL, 10000个简体字，10000个繁体字.
// size of info file = magic + info_size + tail_magic

#define		QY_INFO_FILE_MAGIC_LEN						16
#define		QY_INFO_FILE_MAGIC							"QYIMC00120020730"
#define		QY_INFO_FILE_TAIL_START_MAGIC				"0000000000000000"
#define		QY_INFO_FILE_TAIL_END_MAGIC					"7893634298325910"


#define		DEFAULT_QY_IMC_LOGDBFILE					"~nsi.tmp"
#define		DEFAULT_QY_IMC_TMPLOGDBFILE					"~vbsi.tmp"

#define		QY_IELCKFILE								"~eiDx9.tmp"

#define		IEM_INIT_MUTEX_TIMEOUT						5000	// 初始化的Mutex的超时
#define		CONST_nSecondsOfIeActiveTimeout				60
#define		CONST_nSecondsOfPcLost						3600



#endif  /*  }  */


