

#include <windows.h>
#include "cfComm.h"
#include "cfcommon.h"
#include "contentfilter.h"
#include "cfcfg.h"
#include  "vardefine.h"
#include "contentfilterFunc.h"


/*
#define safeStrCpy( src, des ) {				\
		if ( sizeof( des ) < strlen( src ) ) 		\
			strcpy( des, src );			\
		else {						\
			memcpy( des, src, sizeof( des ) -1 );	\
			des[sizeof( des ) - 1] = 0;		\
		}						\
	}
*/




#define CFG_CF_ON	"contentFilterOn"
#define CFG_CF_LOG_ON	"contentFilterLogOn"

 int getAllCfCfg( QY_CF_GBUF_STRUCT *pGBuf )
{

	pGBuf->pShmCfgSpace->bCFOn = On;
	debuglog( "CF zhang:bCFOn is: %d", pGBuf->pShmCfgSpace->bCFOn );
	pGBuf->pShmCfgSpace->bCFLogOn = On;
	debuglog( "CF zhang:bCFLogOn is: %d", pGBuf->pShmCfgSpace->bCFLogOn );

	return 0;
	
}

 int saveAllCfCfg( QY_CF_GBUF_STRUCT *pGBuf, CF_COMM_HEAD *pCCH )
{

	 FILE *fp = NULL;


	fp = fopen( CF_CFG_FILE, "w" );
	if ( !fp ) return -1;

	fprintf( fp, "%s\t%d\n", CFG_CF_ON, pCCH->u.on.bCFOn );
	fprintf( fp, "%s\t%d\n", CFG_CF_LOG_ON, pCCH->u.on.bCFLogOn );

	fclose( fp );

	return 0;

}
 

 int cfCfgServRun( QY_CF_STRUCT *pCf , QY_CF_GBUF_STRUCT *pGBuf )
{
	int iErr = -1;
	CF_CFG_STRUCT *pCCS = &pGBuf->cfg.var.cCS;
 	
	debugLog( "cfCfgServRun( ) enters ." );
 	
	if ( getCFDicts( pGBuf ) )	{
		debuglog( "CF getCFDicts Failed" );
		goto errLabel;
	}

	if  (  pCf->bDictRefreshed  )	{
		pGBuf->pShmCfgSpace->setupDictShmAddr  =  pGBuf->shmAddr;
		traceLogA(  "cfCfgServRun(  ):  重建字典：setupDictShmAddr is %p",  pGBuf->shmAddr  );
	}
	giShmDiff  = pGBuf->shmAddr - pGBuf->pShmCfgSpace->setupDictShmAddr;
	if  (  giShmDiff  )  {
		traceLogA(  "cfCfgServRun(  ):  shmAddr  is %p,  setupDictShmAddr is %p",  pGBuf->shmAddr,  pGBuf->pShmCfgSpace->setupDictShmAddr  );
		traceLogA(  "cfCfgServRun(  ):  注意，giShmDiff != 0, 产生了地址差距。"  );
	}
	
	if  (  getAllCfCfg(  pGBuf  )  )  {
		debuglog( "CF setAllCfCfg( ) failed, that means content filter can't inited successfully." );
		goto errLabel;
	}
	
	if  (  pCf->bDictRefreshed  )  {
		debugLog(  "cfCfgServRun(  ): 字典将重建."  );
		if ( setupCFDicts( pCf, pGBuf->pCFDict ) ) {
			debugLog( "setupCFDicts( ) failed." );
			goto errLabel;
		}
	}
	
	pGBuf->pShmCfgSpace->bDictOn = TRUE;
	showCFDicts( pGBuf->pCFDict, pGBuf->cfDictCnt );

	iErr = 0;
	
errLabel:

	debugLog( "cfCfgServRun( ) leaves." );

	return iErr;

}
 


 void showShmCfgSpace( SHM_CFG_SPACE *p )
{

	debuglog( "CF bDictOn is %d, bCFOn is %d, bCFLogOn is %d", 
		p->bDictOn, p->bCFOn, p->bCFLogOn );
	return;

}



