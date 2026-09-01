/*

typedef struct __awm_nh_cfg_t {
	unsigned int loopInterval;
	char dsnName[64];
	
} AWM_NH_CFG;

typedef struct __awmNhScanner_t {

	AWM_NH_CFG cfg;
	char instPath[2048];
	void *pDb;

} AWM_NH_SCANNER;


typedef struct __awm_path_field_t{
	char sp[256];
}AWM_PATH_FIELD;

typedef struct __awm_scanned_info_t {
	char keyword[40];
	int  val;
	int  count;
	long totalVal;
	char cLevel;

} AWM_SCANNED_INFO;


typedef struct __awm_nh_file_t {
	char dirName[2048];
	char fileName[256];
	unsigned long size;
	char lastTime[15];

} AWM_NH_FILE;

typedef struct __awm_scanned_file_t {
	char scannedFileName[2048];
	char id[256];
	char scanTime[15];

} AWM_SCANNED_FILE;

typedef struct __awm_nh_paras_t {
	AWM_NH_SCANNER		*pANS;
	AWM_NH_FILE			*pANF;
	AWM_SCANNED_FILE	*pASF;
	AWM_SCANNED_INFO    asi;
	unsigned long       id;
}AWM_NH_PARAS;*/

//extern BOOL awmKeyUpdate( AWM_NH_SCANNER *pANS, AWM_SCANNED_INFO *pASI, unsigned long id );
