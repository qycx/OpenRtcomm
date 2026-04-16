
#ifndef __OPSKETCHPAD_H__
#define __OPSKETCHPAD_H__ /* { */

#ifdef __cplusplus
 extern "C" {
#endif

#define OP_NULL						0
#define OP_DELETE					2
#define OP_DRAW_A_RGN				3
#define OP_MOVE						4
#define OP_CREATE_A_POINT			5
#define OP_CREATE_A_SEGMENT			6
#define OP_CREATE_A_CIRCLE			7
#define OP_CREATE_A_MEMO			8
#define OP_HELP						9
#define OP_ANIMATE					10
#define OP_PATH						11
#define OP_CHECK					12
#define OP_REFRESH_CONSTRAINT		13
#define OP_CONSTRAINTED_MOVE		14
#define OP_FIXED					15
#define OP_REFRESH_CONSTRAINTED_OP	16


//  2009/09/28
#define		CONST_opFlg_x			(  1  <<  0  )
#define		CONST_opFlg_y			(  1  <<  1  )


#if	0	//  ndef __DEBUG__

 #define CHECK_OP_NULL( pSpObj, pDriver, op )													\
					( ( pSpObj )->op == ( op ) )
 #define CHECK_OP_FIXED( pSpObj, pDriver, op )													\
					( ( pSpObj )->op == ( op ) )
 #define CHECK_OP_MOVE( pSpObj, pDriver, op )													\
					( ( pSpObj )->driver.pDriverQNode == ( pDriver )->pDriverQNode				\
					&& ( pSpObj )->op == ( op ) ) 
 #define CHECK_OP_CONSTRAINTED_MOVE( pSpObj, pDriver, op )										\
					( ( pSpObj )->driver.pDriverQNode == ( pDriver )->pDriverQNode				\
					&& ( pSpObj )->driver.pConstraintedQNode == ( pDriver )->pConstraintQNode	\
					&& ( pSpObj )->op == ( op ) ) 
 #define CHECK_OP_FIXED( pSpObj, pDriver, op )	CHECK_OP_CONSTRAINTED_MOVE( pSpObj, pDriver, op )

#endif





extern int  postToOpedQ(  Q_NODE  *  pQNode,  SP_STRUCT  *  pSp  );
extern int preOpSp( SP_STRUCT *pSp );

extern int preOpSpObj( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm );

extern int preOpSpPoint( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm );
extern int preOpSpGenericPoint( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm );
extern int preOpSpPointOnObj( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm );
extern int preOpSpIntersectPoint( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm );
extern int preOpSpReflectPoint( SP_STRUCT *pSp, Q_NODE *pQNode, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm );
extern int preOpSpRotatePoint( SP_STRUCT *pSp, Q_NODE *pQNode, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm );


extern int preOpSpSegment( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm );
extern int preOpSpGenericSegment( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm );
extern int preOpSpLine( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm );
extern int preOpSpPerpendicularLine( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm );
extern int preOpSpReflectSegment( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm );
extern int preOpSpReflectLine( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm );
extern int preOpSpReflectSegment( SP_STRUCT *pSp, Q_NODE *pQNode, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm );


extern int preOpSpCircle( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm );
extern int preOpSpGenericCircle( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm );

extern int preOpSpAnimator( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm );

extern int preOpSpRectangle( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm );


#ifdef __cplusplus
 }
#endif

#endif /* } __OPSKETCHPAD_H__ */

