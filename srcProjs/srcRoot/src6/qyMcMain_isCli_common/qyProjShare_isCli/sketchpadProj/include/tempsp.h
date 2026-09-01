
#ifndef __TEMPSKETCHPAD_H__
#define __TEMPSKETCHPAD_H__ /* { */

#ifdef __cplusplus
 extern "C" {
#endif


#if	1		//  def __DEBUG__

 extern int printQ( GENERIC_Q *pQ );
 extern int printSelectedQ( GENERIC_Q *pQ );

 extern int printInfo( char *fmt, ... );
 extern int printSpObj( void *pSpObj );
 extern char *showSpObjType( BYTE type, BYTE subType );
 extern char *showSpObjStatus( BYTE status );
 extern char *showSpObjOp( BYTE op );


 extern BOOL CHECK_OP_NULL( void *pSpObj, SP_DRIVER *pDriver, BYTE op, SP_OP_PARM *pOpParm );
 extern BOOL CHECK_OP_FIXED( void *pSpObj, SP_DRIVER *pDriver, BYTE op, SP_OP_PARM *pOpParm );
 extern BOOL CHECK_OP_MOVE( void *pSpObj, SP_DRIVER *pDriver, BYTE op, SP_OP_PARM *pOpParm );
 extern BOOL CHECK_OP_CONSTRAINTED_MOVE( void *pSpObj, SP_DRIVER *pDriver, BYTE op, SP_OP_PARM *pOpParm );
 
 extern BOOL CAN_OP_FIXED( void *pSpObj, SP_DRIVER *pDriver, BYTE op, SP_OP_PARM *pOpParm );
 extern BOOL CAN_OP_MOVE( void *pSpObj, SP_DRIVER *pDriver, BYTE op, SP_OP_PARM *pOpParm );
 extern BOOL CAN_OP_CONSTRAINTED_MOVE( void *pSpObj, SP_DRIVER *pDriver, BYTE op, SP_OP_PARM *pOpParm );
 

#endif


#ifdef __cplusplus
 }
#endif

#endif /* } __TEMPSKETCHPAD_H__ defined */
