
#ifndef __ZHFUNC_H__
#define __ZHFUNC_H__	/* { */

#ifdef __cplusplus
extern "C" {
#endif

int initAsrZh( void *p);
void exitAsrZh( );

void g2bFunc( unsigned char *buf, int len );
void b2gFunc( unsigned char *buf, int len );

#ifdef __cplusplus
 }
#endif

#endif /* } */

