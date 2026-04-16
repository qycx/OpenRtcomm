
#ifndef __CFCFG_H__
#define __CFCFG_H__	/* { */

#include "cfComm.h"

#define CF_DICT_DIR	 "db\\dict\\"
#define CF_LOG_DIR	"log\\"
#define CF_LOG_FILE	"asrCf.log"
#define CF_LOG_CASH_DIR	"log\\cache\\"
#define CF_CFG_FILE	"db\\dict\\asrCf.cfg"

#define G2B_FILE	"G2BTable.txt"
#define B2G_FILE	"B2GTable.txt"


#define MAX_LOG_FILE_LEN			9000000		// 9m


typedef struct __cf_cfg_struct_t {
	
	char cfDictDir[QY_MAXPATHLEN + 1];
	
} CF_CFG_STRUCT;


#endif /* } */



