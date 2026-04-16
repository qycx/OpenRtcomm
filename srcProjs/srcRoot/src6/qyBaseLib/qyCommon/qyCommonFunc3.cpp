
#include	"qyPrecomp.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<ctype.h>
#include	<windows.h>
#if  0
#include	<lm.h>
#include	<lmshare.h>
#endif


extern "C" unsigned char *trimRight( unsigned char *str )
{
	int len;

	if ( !str || !strlen( ( const char * )str ) ) return NULL;
	len = strlen( ( const char * )str );
	while ( len ) {
		if ( !isspace( str[len - 1] ) ) break;
		str[len - 1] = '\0';
		len --;
	}
	if ( !len ) return NULL;

	return str;

}

 extern "C" char *asrGetFullPath( char *path, char *file, char *buf, unsigned int bufSize )
{

	if ( !trimRight( ( unsigned char * )path ) ) return NULL;
	if ( path[strlen( path ) -1] == '\\' ) {
		if ( strlen( path ) + strlen( file ) >= bufSize ) return NULL;
		sprintf( buf, "%s%s", path, file );
		}
	else {
		if ( strlen( path ) + 1 + strlen( file ) >= bufSize ) return NULL;
		sprintf( buf, "%s\\%s", path, file );
	}

	return buf;
	
}




