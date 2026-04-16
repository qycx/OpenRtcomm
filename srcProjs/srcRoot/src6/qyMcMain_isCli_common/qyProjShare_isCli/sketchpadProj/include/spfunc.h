
#ifndef __SKETCHPADFUNC_H__
#define __SKETCHPADFUNC_H__ /* { */

#ifdef __cplusplus
 extern "C" {
#endif

#define WIN32_LP			1
#define NORMAL_LP			2
#define MOVE_AND_ROTATE_LP	3

typedef union __lp_parm {

	struct {
		short height;
	} win32Lp;

	struct {
		short xO, yO;
		short A180;
	} moveAndRotateLp;

} LP_PARM;

 extern int spLpToLp( int fromMode, short fromX, short fromY, int toMode, short *pToX, short *pToY, LP_PARM *p );

 extern int getDriverOpParm( SP_STRUCT *pSp, Q_NODE *pQNode, SP_OP_PARM *pSpOpParm );

 extern int getEquationAnswer( float a, float b, float c, float *pX1, float *pX2, int *pCount );

#ifdef __SP_DEBUG__
 extern int printInfo( char *fmt, ... );
#endif

#define getDOf2Points( /* SP_RECT_COORD * */ p1, /* SP_RECT_COORD * */ p2 ) sqrt(  (  float  )SQUARE( ( p1 )->x - ( p2 )->x ) + SQUARE( ( p1 )->y - ( p2 )->y ) )
#define getDOf2SpPoints( /* SP_POINT * */ p1, /* SP_POINT * */ p2 ) sqrt(  (  float  )SQUARE( ( p1 )->point.rect.x - ( p2 )->point.rect.x ) + SQUARE( ( p1 )->point.rect.y - ( p2 )->point.rect.y ) )
extern float getDOfPointFromSegment( SP_RECT_COORD *pPoint, SP_RECT_COORD *pFirstPoint, SP_RECT_COORD *pSecondPoint );
extern float getAOf3Ds( float d12, float d13, float d23 );

#define getPointWith2PointsAndRate( /* SP_RECT_COORD * */ p1, /* SP_RECT_COORD * */ p2, /* float */ rate, /* SP_RECT_COORD * */ p )	\
			{																														\
				( p )->x = ( p1 )->x + ( short )( ( rate ) * ( ( p2 )->x - ( p1 )->x ) );											\
				( p )->y = ( p1 )->y + ( short )( ( rate ) * ( ( p2 )->y - ( p1 )->y ) );											\
			}

#define getPointWith2SpPointsAndRate( /* SP_POINT * */ p1 , /* SP_POINT * */ p2, /* float */ rate, /* SP_RECT_COORD * */ p )	\
			getPointWith2PointsAndRate( &( p1 )->point.rect, &( p2 )->point.rect, rate, p )

#define getMidPointWith2SpPoints( /* SP_POINT * */ p1, /* SP_POINT * */ p2, /* SP_RECT_COORD * */ p )	\
			{																							\
				( p )->x = ( short )( ( ( p1 )->point.rect.x + ( p2 )->point.rect.x ) / 2.0 );			\
				( p )->y = ( short )( ( ( p1 )->point.rect.y + ( p2 )->point.rect.y ) / 2.0 );			\
			}

extern int getRayPointForAngleBisector( SP_POINT *p1, SP_POINT *p2, SP_POINT *p3, SP_RECT_COORD *pRayPoint );
extern void getRayBorderPoint( SP_RECT_COORD *pStart, SP_RECT_COORD *pForward, unsigned short width, unsigned short height, SP_RECT_COORD *pBorderPoint );


extern Q_NODE *findNextpQNodeOfSamePlaceSpObj( Q_NODE *pQNode, SP_OBJ *pSpObj );
extern Q_NODE *findpQNodeOfSpPoint( GENERIC_Q *pSpObjQ, SP_POINT *pSpPoint );

extern Q_NODE *findpQNodeOfSpPoint( GENERIC_Q *pSpObjQ, SP_POINT *pSpPoint );
extern Q_NODE *findNextpQNodeSelected( Q_NODE *pQNode, SP_RECT_COORD *pPoint );

extern void spShowInfo( char *fmt, ... );

extern int getNearestPointOnPath( SP_POINT *pSpPoint, SP_OBJ *pPath, SP_RECT_COORD *p );
extern int getNearestPointOnSegment( SP_POINT *pSpPoint, SP_SEGMENT *pSegment, SP_RECT_COORD *p );

extern int tryToChangeNewSpPointSubType( GENERIC_Q *pSpObjQ, GENERIC_Q *pNewSpObjQ, SP_POINT *pSpPoint );

extern int getRAPI( float *pR, float *pA, int x, int y );

extern int procSpIntersectPoint( SP_INTERSECT_POINT *pSpIntersectPoint );

extern int refresh2CirclesSpIntersectPoint( SP_INTERSECT_POINT *pSIP );
extern int refresh2SegmentsSpIntersectPoint( SP_INTERSECT_POINT *pSIP );

extern int refreshSpIntersectPoint( SP_INTERSECT_POINT *pSIP );
extern int refreshSpPointOnObj( SP_POINT_ON_OBJ *pSPOO, SP_TRAN_PARM *pSpTranParm );

extern int getReflectPoint( SP_SEGMENT *pMirror, SP_RECT_COORD *pPoint, SP_RECT_COORD *pReflectPoint );
extern int getRotatePoint( SP_POINT *pCenter, SP_RECT_COORD *pPoint, SP_RECT_COORD *pRotatePoint, short A180 );


extern int setSpObjOpMove( SP_STRUCT  *  pSp,  Q_NODE *pQNode, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm );
extern int setSpObjOpConstraintedMove( Q_NODE *pQNode, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm );
extern int setSpObjOpFixed( Q_NODE *pQNode, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm );


#ifdef __cplusplus
 }
#endif

#endif /* } __SKETCHPADFUNC_H__ defined */

