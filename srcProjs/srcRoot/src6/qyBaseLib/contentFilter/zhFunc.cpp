
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <windows.h>

#include "cfCommon.h"
#include "cfCfg.h"
#include "EmailProcess.h"
#include "G2BTABLE.h"
#include "B2GTABLE.h"

CEmailProcess *pEP = NULL;

unsigned char g2bTable[] = G2BTABLE;
unsigned char b2gTable[] = B2GTABLE;

 
 extern "C" int initAsrZh( void *pDictDir )
{
	int iErr = -1;
	char b2gFileName[QY_MAXPATHLEN + 1], g2bFileName[QY_MAXPATHLEN + 1];
	struct _stat tmpStat;
	
	if ( qyStrCat( ( char * )pDictDir, B2G_FILE, b2gFileName, sizeof( b2gFileName ) ) ) {
		goto errLabel;
	}
	if ( qyStrCat( ( char * )pDictDir, G2B_FILE, g2bFileName, sizeof( g2bFileName ) ) ) {
		goto errLabel;
	}

	if ( _stat( g2bFileName, &tmpStat ) ) {
		debugLog( "_stat [%s] failed, so to create g2bTable", g2bFileName );
		if ( bufToFile( ( char * )g2bTable, sizeof( g2bTable ), g2bFileName ) ) {
			debugLog( "g2bTable file can't be created." );
			goto errLabel;
		}
	}
	if ( _stat( b2gFileName, &tmpStat ) ) {
		debugLog( "_stat [%s] failed, so to create b2gTable", b2gFileName );
		if ( bufToFile( ( char * )b2gTable, sizeof( b2gTable ), b2gFileName ) ) {
			debugLog( "b2gTable file can't be created." );
			goto errLabel;
		}
	}

	debuglog("b2gTableFile is [%s] " , b2gFileName );
	debuglog("g2bTableFile is [%s] ", g2bFileName );
	pEP = new CEmailProcess( b2gFileName, g2bFileName );
	if ( !pEP ) goto errLabel;

	iErr = 0;

errLabel:

	if ( iErr ) {
		if ( pEP ) { delete( pEP ); pEP = 0; }
	}

	return iErr;
	 
}

 extern "C" void exitAsrZh( )
{
	 if ( pEP ) {
		 delete( pEP ); pEP = 0; 
	 }
}

 extern "C" void g2bFunc( unsigned char *buf, int len )
{
	 pEP->Gb2Big( buf, len );
}

 extern "C" void b2gFunc( unsigned char *buf, int len )
{
	 pEP->Big2Gb( buf, len );
}



