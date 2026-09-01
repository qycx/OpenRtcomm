
#include	"stdafx.h"
#include	"sp.h"

 int getEquationAnswer( float a, float b, float c, float *pX1, float *pX2, int *pCount )
{
	 int iErr = 0;

	 if ( fabs( a ) <= ZERO_RANGE ) {
			
			if ( fabs( b ) <= ZERO_RANGE ) {
					iErr = -1; goto err;
			}

			*pX1 = c / b;
			*pCount = 1;
			goto err;

	 }

	 *pX1 = ( float )( ( -b + sqrt( b * b - 4 * a * c ) ) / ( 2 * a ) );
	 *pX2 = ( float )( ( -b - sqrt( b * b - 4 * a * c ) ) / ( 2 * a ) );
	 *pCount = 2;

err:

	 return iErr;

}


 int spLpToLp( int fromMode, short fromX, short fromY, int toMode, short *pToX, short *pToY, LP_PARM *p )
{
	 int iErr = 0;

	 switch ( fromMode ) {

 		case NORMAL_LP:
			
			if ( toMode == WIN32_LP ) {
					*pToX = fromX;
					*pToY = p->win32Lp.height - fromY;
					break;
				}
			else if ( toMode == MOVE_AND_ROTATE_LP ) {
					
					float r, aPi;

					if ( getRAPI( &r, &aPi, fromX - p->moveAndRotateLp.xO, fromY - p->moveAndRotateLp.yO ) ) {
							iErr = -1; break;
					}


				}
			else ;

			iErr = -1;	
			break;

		 
		case WIN32_LP:
			
			if ( toMode == NORMAL_LP ) {
					*pToX = fromX;
					*pToY = p->win32Lp.height - fromY;
					break;
				}
			
			iErr = -1;
			break;

		default:

			iErr = -1; 
			break;
	 }
	 
	 return iErr;

}

 int getDriverOpParm( SP_STRUCT *pSp, Q_NODE *pQNode, SP_OP_PARM *pSpOpParm )
{
	 int iErr = 0;

	 if ( pQNode == NULL ) {
			pSpOpParm->move.x = pSp->tranParm.move.curPlace.x - pSp->tranParm.move.lastPlace.x;
			pSpOpParm->move.y = pSp->tranParm.move.curPlace.y - pSp->tranParm.move.lastPlace.y;
		}
	 else iErr = -1;

	 return iErr;

}
 
 Q_NODE *findNextpQNodeOfSamePlaceSpObj( Q_NODE *pQNode, SP_OBJ *pSpObj )
{
	 SP_OBJ *tmppSpObj;

	 for ( ; pQNode; pQNode = pQNode->pNext ) {

		tmppSpObj= ( SP_OBJ * )pQNode->qElemMemory.m_pBuf;

		if ( tmppSpObj->type != pSpObj->type ) continue;
		
		if ( isSamePlaceSpObj( tmppSpObj, pSpObj ) ) break;		

	}

	return pQNode;

}

 Q_NODE *findNextpQNodeSelected( Q_NODE *pQNode, SP_RECT_COORD *pPoint )
{
	 SP_OBJ *pSpObj;
		
	 for ( ; pQNode; pQNode = pQNode->pNext ) {

		 pSpObj = ( SP_OBJ * )pQNode->qElemMemory.m_pBuf;

		 if ( isSpObjSelected( pSpObj, pPoint ) == TRUE ) break;
	 
	 }

	 return pQNode;


}

 

 float getDOfPointFromSegment( SP_RECT_COORD *pPoint, SP_RECT_COORD *pFirstPoint, SP_RECT_COORD *pSecondPoint )
{
	 float dFS, dPF, dPS, d;
	 float angFS; /* PI value */

	 dFS = ( float )sqrt( (  float  )SQUARE( pFirstPoint->x - pSecondPoint->x ) + SQUARE( pFirstPoint->y - pSecondPoint->y ) );
	 dPF = ( float )sqrt( (  float  )SQUARE( pPoint->x - pFirstPoint->x ) + SQUARE( pPoint->y - pFirstPoint->y ) );
	 dPS = ( float )sqrt( (  float  )SQUARE( pPoint->x - pSecondPoint->x ) + SQUARE( pPoint->y - pSecondPoint->y ) );

	 if ( dPF < SP_POINT_RANGE || dPS < SP_POINT_RANGE ) return 0.0; 
	 if ( dFS < SP_POINT_RANGE ) return dPF;

	 angFS = ( float )acos( ( SQUARE( dPS ) - SQUARE( dPF ) - SQUARE( dFS ) ) / ( 2 * dPF * dFS ) );

	 d = dPF * ( float )sin( angFS );

#ifdef __SP_DEBUG__
	 if ( d < 0 ) {
		 logErr( "getDOfPointFromSegment() error: d < 0 " );
		 return -1.0;
	 }
#endif

	 if ( d < dPF && d < dPS) return d;
	 return min( dPF, dPS );
	
}

 
 float getAOf2Points( SP_RECT_COORD *pPoint1, SP_RECT_COORD *pPoint2 )
{
	
	 if ( pPoint1->x == pPoint2->x ) {
		 if ( pPoint1->y == pPoint2->y ) return -1.0;
		 return 0.;
	 }

	 return ( float )atan( (  float  )( pPoint1->y - pPoint2->y ) / ( pPoint1->x - pPoint2->x ) );

}


 float getAOf3Points( SP_RECT_COORD *pPoint1, SP_RECT_COORD *pPoint2, SP_RECT_COORD *pPoint3 )
{
	 float d12, d13, d23;
	 float tmpAng; /* PI value */

	 d12 = ( float )sqrt( (  float  )SQUARE( pPoint1->x - pPoint2->x ) + SQUARE( pPoint1->y - pPoint2->y ) );
	 d13 = ( float )sqrt( (  float  )SQUARE( pPoint1->x - pPoint3->x ) + SQUARE( pPoint1->y - pPoint3->y ) );
	 d23 = ( float )sqrt( (  float  )SQUARE( pPoint2->x - pPoint3->x ) + SQUARE( pPoint2->y - pPoint3->y ) );

	 if ( d12 < SP_POINT_RANGE || d13 < SP_POINT_RANGE || d23 < SP_POINT_RANGE ) 
		 return -1.;

	 tmpAng = ( float )acos( SQUARE( d12 ) + SQUARE( d23 ) - ( SQUARE( d13 ) ) / ( 2 * d12 * d23 ) );

	 return tmpAng;


}

 float getAOf3Ds( float d12, float d23, float d13 )
{

	 return ( float )acos( ( SQUARE( d12 ) + SQUARE( d23 ) - SQUARE( d13 ) ) / ( 2 * d12 * d23 ) );

}

 
 int getRayPointForAngleBisector( SP_POINT *p1, SP_POINT *p2, SP_POINT *p3, SP_RECT_COORD *pRayPoint )
{
	 float d12, d13, d23;
	 SP_POINT tmpSpPoint;

	 if ( p1->type != SP_POINT_TYPE ) return -1;
	 if ( p1->status & STATUS_INVALID ) return -1;
	 if ( p2->type != SP_POINT_TYPE ) return -1;
	 if ( p2->status & STATUS_INVALID ) return -1;
	 if ( p3->type != SP_POINT_TYPE ) return -1;
	 if ( p3->status & STATUS_INVALID ) return -1;
	
	 d12 = ( float )getDOf2SpPoints( p1, p2 );
	 d13 = ( float )getDOf2SpPoints( p1, p3 );
	 d23 = ( float )getDOf2SpPoints( p2, p3 );
		
	 if ( d12 < SP_POINT_RANGE || d13 < SP_POINT_RANGE || d23 < SP_POINT_RANGE ) {
		 return -1;
	 }
	
	if ( d12 <= d23 ) {
			getPointWith2SpPointsAndRate( p2, p3, d12/d23, &tmpSpPoint.point.rect );
			getMidPointWith2SpPoints( p1, &tmpSpPoint, pRayPoint );
		}
	else {
			getPointWith2SpPointsAndRate( p2, p1, d23/d12, &tmpSpPoint.point.rect );
			getMidPointWith2SpPoints( p3, &tmpSpPoint, pRayPoint );
		}

	return 0;

}

 /* this function on used when ox is 0, oy is 0, and the rectangle is in the first domain */
 void getRayBorderPoint( SP_RECT_COORD *pStart, SP_RECT_COORD *pForward, unsigned short width, unsigned short height, SP_RECT_COORD *pBorderPoint )
{
	 float rate;

	 /* first get the intersection point on the left border */

	 rate = ( 0 - pStart->x ) / ( ( float )( pForward->x - pStart->x ) );
	 pBorderPoint->y = ( short )( rate * ( pForward->y - pStart->y ) ) + pStart->y;
	 if ( pBorderPoint->y >= 0 && pBorderPoint->y <= height ) {
		 pBorderPoint->x = 0;
		 return;
	 }

	 /* second get the intersection point on the top border */
	 rate = ( height - pStart->y ) / ( ( float )( pForward->y - pStart->y ) );
	 pBorderPoint->x = ( short )( rate * ( pForward->x - pStart->x ) ) + pStart->x;
	 if ( pBorderPoint->x >= 0 && pBorderPoint->x <= width ) {
		 pBorderPoint->y = height;
		 return;
	 }

	 /* third get the intersection point on the right border */
	 rate = ( width - pStart->x ) / ( ( float )( pForward->x - pStart->x ) );
	 pBorderPoint->y = ( short ) ( rate * ( pForward->y - pStart->y ) ) + pStart->y;
	 if ( pBorderPoint->y >= 0 && pBorderPoint->y <= height ) {
		 pBorderPoint->x = width;
		 return;
	 }

	 /* last get the point on the bottom border */

	 rate = ( 0 - pStart->y ) / ( ( float )( pForward->y - pStart->y ) );
	 pBorderPoint->x = ( short )( rate * ( pForward->x - pStart->x ) ) + pStart->x;
	 pBorderPoint->y = 0;
	 return;

}


 void spShowInfo( char *fmt, ... )
{	 	
	va_list args;
	
	va_start(args,fmt);
	

	/*
	_vsnprintf( gSp.info, sizeof( gSp.info ) - 1, fmt, args );
	gSp.info[sizeof( gSp.info )-1] = '\0';
	*/

	
	va_end(args);
	
	return;


}


 int getNearestPointOnPath( SP_POINT *pSpPoint, SP_OBJ *pPath, SP_RECT_COORD *p )
{
	 int iErr = 0;

	 switch ( pPath->type ) {
		 
		case SP_SEGMENT_TYPE:

			iErr = getNearestPointOnSegment( pSpPoint, ( SP_SEGMENT * )pPath, p );

			break;

		default:

			break;

	 }

	 return iErr;

}

 int getNearestPointOnSegment( SP_POINT *pSpPoint, SP_SEGMENT *pSpSegment, SP_RECT_COORD *p )
{
	 SP_RECT_COORD *p1, *p2, *p0, *tmpp;
	 int iErr = 0;
	 float dp1,dp2,d12, k;

	 
	 p0 = &pSpPoint->point.rect;
	 p1 = &( ( SP_POINT * )pSpSegment->pStartQNode->qElemMemory.m_pBuf )->point.rect;
	 p2 = &( ( SP_POINT * )pSpSegment->pEndQNode->qElemMemory.m_pBuf )->point.rect;
	 
	 /* just for test */
#ifndef __SP_DEBUG__
	 /* error "this must be replaced" */
#endif
/*
	 p->x = p1->x;
	 p->y = p1->y;
	 return 0;
*/

	 /* just for test */



	 if ( p1->y < p2->y ) { tmpp = p1; p1 = p2; p2 = tmpp; }

	 if ( p1->x == p2->x ) {
			p->x = p1->x; p->y = p0->y;
		}
	 else {
		 k = ( p1->y - p2->y ) / ( ( float )( p1->x - p2->x ) );
	 	 p->x = ( short )( ( k * k * p1->x - k * p1->y + p0->x + k * p0->y ) / ( k * k + 1 ) );
	 	 p->y = ( short )( p1->y + k * (p->x - p1->x ) );
	 }
	 dp1 = ( float )getDOf2Points( p, p1 ); dp2 = ( float )getDOf2Points( p, p2 );
	 d12 = ( float )getDOf2Points( p1, p2 );

	 if ( dp1 <= d12 && dp2 <= d12 ) return 0;
	 if ( dp1 <= dp2 ) { p->x = p1->x; p->y = p1->y;  return 0; }
	 p->x = p2->x; p->y = p2->y;
 
	 return iErr;

}

 
 int tryToChangeNewSpPointSubType( GENERIC_Q *pSpObjQ, GENERIC_Q *pNewSpObjQ, SP_POINT *pSpPoint )
{

	 int iErr = 0;
	 Q_NODE *pQNode1 = NULL, *pQNode2 = NULL;
	 
	 
	 if ( !( pQNode1 = findNextpQNodeSelected( pSpObjQ->front.pNext, &pSpPoint->point.rect ) ) ) 
		 return 0;

	 if ( ( ( SP_OBJ * )pQNode1->qElemMemory.m_pBuf )->type == SP_POINT_TYPE ) {
		 return -1;
	 }

	 if ( !( pQNode2 = findNextpQNodeSelected( pQNode1->pNext, &pSpPoint->point.rect ) )
		 || ( ( SP_OBJ * )pQNode2->qElemMemory.m_pBuf )->type == SP_POINT_TYPE ) {
		 
			SP_POINT_ON_OBJ tmpSpPointOnObj;

			tmpSpPointOnObj.type = SP_POINT_TYPE;
			tmpSpPointOnObj.status = 0;
			tmpSpPointOnObj.subType = SP_POINT_ON_OBJ_TYPE;
			tmpSpPointOnObj.pObjQNode = pQNode1;
			tmpSpPointOnObj.point.rect.x = pSpPoint->point.rect.x;
			tmpSpPointOnObj.point.rect.y = pSpPoint->point.rect.y;
		 
			switch ( ( ( SP_OBJ * )pQNode1->qElemMemory.m_pBuf )->type ) {
		
				case SP_SEGMENT_TYPE:

					tmpSpPointOnObj.posParm = ( short )getDOf2SpPoints( pSpPoint, ( SP_POINT * )( ( SP_SEGMENT * )pQNode1->qElemMemory.m_pBuf )->pStartQNode->qElemMemory.m_pBuf );

					break;

				case SP_CIRCLE_TYPE: {

						float r, A;
						int x, y;

						x = tmpSpPointOnObj.point.rect.x - ( ( SP_POINT * )( ( ( SP_CIRCLE * )pQNode1->qElemMemory.m_pBuf )->pCenterQNode->qElemMemory.m_pBuf ) )->point.rect.x;
						y = tmpSpPointOnObj.point.rect.y - ( ( SP_POINT * )( ( ( SP_CIRCLE * )pQNode1->qElemMemory.m_pBuf )->pCenterQNode->qElemMemory.m_pBuf ) )->point.rect.y;
						
						if ( getRAPI( &r, &A, x, y ) ) {
							iErr = -1; break;
						}
						tmpSpPointOnObj.posParm = ( short )API2180( A );

					}

					break;

				default:

					iErr = -1;

					break;

			}

			emptyGenericQ( pNewSpObjQ );
	
			if ( !iErr ) {
								
			 		if ( qPostMsg( &tmpSpPointOnObj, sizeof( tmpSpPointOnObj ),  pNewSpObjQ,  _T(  "tryToChangeNewSpPointSubtype"  ))) {
							iErr = -1;
					}

			}
		 
			 return iErr;

	 }
	 
	 {		 
		 SP_INTERSECT_POINT tmpSpIntersectPoint;
		 
		 tmpSpIntersectPoint.pQNode1 = pQNode1;
		 tmpSpIntersectPoint.pQNode2 = pQNode2;
		 tmpSpIntersectPoint.type = SP_POINT_TYPE;
		 tmpSpIntersectPoint.subType = SP_INTERSECT_POINT_TYPE;
		 tmpSpIntersectPoint.status = 0;
		 tmpSpIntersectPoint.point.rect.x = pSpPoint->point.rect.x;
		 tmpSpIntersectPoint.point.rect.y = pSpPoint->point.rect.y;

		
		 if ( procSpIntersectPoint( &tmpSpIntersectPoint ) ) {
				 iErr = -1;
				 goto err;
		 }

		 emptyGenericQ( pNewSpObjQ );

		 if ( qPostMsg( &tmpSpIntersectPoint, sizeof( tmpSpIntersectPoint ),  pNewSpObjQ,  _T(  "tryToChangeNewSpPointSubtype 1"  ))) {
				 iErr = -1;
		 }

	 }
		 
err:
	 return iErr;

}

 /* get r and complex angle for a point */
 int getRAPI( float *pR, float *pA, int x, int y )
{
	 float cosA, sinA;
	 	 	 
	 *pR = ( float )sqrt( (  float  )SQUARE( x ) + SQUARE( y ) );
	 if ( *pR < SP_POINT_RANGE ) {
		 *pR = 0.; *pA = 0.;
		 return 0;
	 }

	 cosA = x / ( *pR );
	 sinA = y / ( *pR );
	 *pA = ( float )acos( fabs( cosA ) );
	 if ( cosA <= 0 && sinA >= 0 ) 
		 *pA = ( float )CONST_PI - *pA;
	 else if ( cosA <= 0 && sinA <= 0 )
		 *pA = ( float )CONST_PI + *pA;
	 else if ( cosA >= 0 && sinA <= 0 )
		 *pA = 2 * ( float )CONST_PI - *pA;

	 return 0;

}


 int getAPlusAFlag( BOOL *pFlag, SP_CIRCLE *pSpCircle1, SP_CIRCLE *pSpCircle2, SP_RECT_COORD *pPoint )
{
	 float A;	/* PI value */
	 SP_RECT_COORD *pPoint1, *pPoint2, tmpPoint;
	 float r1, r2;
	 float d;
	 float ACenters; /* means the complex angle of ray from circle1's center to circles's */
	 int iErr = 0;

	 pPoint1 = &( ( SP_POINT * )pSpCircle1->pCenterQNode->qElemMemory.m_pBuf )->point.rect;
	 pPoint2 = &( ( SP_POINT * )pSpCircle2->pCenterQNode->qElemMemory.m_pBuf )->point.rect;
	 r1 = ( float )getDOf2Points( &( ( SP_POINT * )pSpCircle1->pCircleQNode->qElemMemory.m_pBuf )->point.rect,
		 pPoint1 );
	 r2 = ( float )getDOf2Points( &( ( SP_POINT * )pSpCircle2->pCircleQNode->qElemMemory.m_pBuf )->point.rect,
		 pPoint2 );
	 d = ( float )getDOf2Points( pPoint1, pPoint2 );

	 if ( getRAPI( &d, &ACenters, pPoint2->x - pPoint1->x, pPoint2->y - pPoint1->y ) ) {
		 iErr = -1; goto err;
	 }

	 A = getAOf3Ds( r1, d, r2 );
	
	 tmpPoint.x = pPoint1->x + ( short )( r1 * cos( A + ACenters ) );
	 tmpPoint.y = pPoint1->y + ( short )( r1 * sin( A + ACenters ) );

	 if ( getDOf2Points( &tmpPoint, pPoint ) < SP_POINT_RANGE ) *pFlag = TRUE;
	 else *pFlag = FALSE;

err:
	 return iErr;

}

 int refresh2CirclesSpIntersectPoint( SP_INTERSECT_POINT *pSIP )
{
	 float A;	/* PI value */
	 SP_RECT_COORD *pPoint1, *pPoint2;
	 SP_CIRCLE *pSpCircle1, *pSpCircle2;
	 float r1, r2;
	 float d;
	 int iErr = 0;
	 float ACenters; /* means the complex angle of ray from circle1's center to circles's */

	 pSpCircle1 = ( SP_CIRCLE * )pSIP->pQNode1->qElemMemory.m_pBuf;
	 pSpCircle2 = ( SP_CIRCLE * )pSIP->pQNode2->qElemMemory.m_pBuf;
	 
	 pPoint1 = &( ( SP_POINT * )pSpCircle1->pCenterQNode->qElemMemory.m_pBuf )->point.rect;
	 pPoint2 = &( ( SP_POINT * )pSpCircle2->pCenterQNode->qElemMemory.m_pBuf )->point.rect;
	 r1 = ( float )getDOf2Points( &( ( SP_POINT * )pSpCircle1->pCircleQNode->qElemMemory.m_pBuf )->point.rect,
		 pPoint1 );
	 r2 = ( float )getDOf2Points( &( ( SP_POINT * )pSpCircle2->pCircleQNode->qElemMemory.m_pBuf )->point.rect,
		 pPoint2 );
	 d = ( float )getDOf2Points( pPoint1, pPoint2 );

	 if ( r1 + r2 <= d || r1 + d < r2 || r2 + d < r1 ) {
		 iErr = -1; goto err;
	 }

	 if ( getRAPI( &d, &ACenters, pPoint2->x - pPoint1->x, pPoint2->y - pPoint1->y ) ) {
		 iErr = -1; goto err;
	 }

	 A = getAOf3Ds( r1, d, r2 );

	 if ( pSIP->posParm == TRUE ) {	
	 		pSIP->point.rect.x = pPoint1->x + ( short )( r1 * cos( A + ACenters ) );
			pSIP->point.rect.y = pPoint1->y + ( short )( r1 * sin( A + ACenters ) );
		 }
	 else {
			pSIP->point.rect.x = pPoint1->x + ( short )( r1 * cos( ACenters - A ) );
	 		pSIP->point.rect.y = pPoint1->y + ( short )( r1 * sin( ACenters - A ) );
	 }


err:

	 return iErr;

}

 int refresh2SegmentsSpIntersectPoint( SP_INTERSECT_POINT *pSIP )
{
	 int iErr = 0;

	 SP_SEGMENT *pSpSegment1, *pSpSegment2;
	 SP_RECT_COORD *p11, *p12, *p21, *p22, tmpI;
	 float k1, k2;


	 pSpSegment1 = ( SP_SEGMENT * )pSIP->pQNode1->qElemMemory.m_pBuf;
	 pSpSegment2 = ( SP_SEGMENT * )pSIP->pQNode2->qElemMemory.m_pBuf;


	 if ( pSpSegment1->subType == SP_GENERIC_SEGMENT_TYPE ) {
			p11 = &( ( SP_POINT * )pSpSegment1->pStartQNode->qElemMemory.m_pBuf )->point.rect;
 			p12 = &( ( SP_POINT * )pSpSegment1->pEndQNode->qElemMemory.m_pBuf )->point.rect;
		}
	 else {
			p11 = &pSpSegment1->point1.rect;
			p12 = &pSpSegment1->point2.rect;
	 }

	 if ( pSpSegment2->subType == SP_GENERIC_SEGMENT_TYPE ) {
			p21 = &( ( SP_POINT * )pSpSegment2->pStartQNode->qElemMemory.m_pBuf )->point.rect;
 			p22 = &( ( SP_POINT * )pSpSegment2->pEndQNode->qElemMemory.m_pBuf )->point.rect;
		}
	 else {
			p21 = &pSpSegment2->point1.rect;
			p22 = &pSpSegment2->point2.rect;
	 }


	 if ( p21->x == p22->x ) {
		 if ( p11->x == p12->x ) {
			 iErr = -1; goto err;
		 }
		 tmpI.x = p21->x;
		 tmpI.y = ( short )( p11->y + ( p12->y - p11->y ) / ( ( float )( p12->x - p11->x ) ) * ( tmpI.x - p11->x ) );
		 }
	 else if ( p11->x == p12->x ) {
		 tmpI.x = p11->x;
		 tmpI.y = ( short )( p21->y + ( p22->y - p21->y ) / ( ( float )( p22->x - p21->x ) ) * ( tmpI.x - p21->x ) );
		}
	 else {
		 
		 float tmpX;
		 
		 k1 = ( p11->y - p12->y ) / ( ( float )( p11->x - p12->x ) );
		 k2 = ( p21->y - p22->y ) / ( ( float )( p21->x - p22->x ) );

		 tmpX = ( p21->y - p11->y + k1 * p11->x - k2 * p21->x ) / ( k1 - k2 );

		 tmpI.x = ( short )( tmpX );
			 
		 tmpI.y = ( short )( k1 * ( tmpX - p11->x ) + p11->y );

	 }

	 pSIP->point.rect.x = tmpI.x;
	 pSIP->point.rect.y = tmpI.y;
	 

err:
	 return iErr;

}

 


 int procSpIntersectPoint( SP_INTERSECT_POINT *pSpIntersectPoint )
{
	 SP_OBJ *pSpObj1, *pSpObj2;
	 int iErr = 0;
	 BOOL flag;

	 pSpObj1 = ( SP_OBJ * )pSpIntersectPoint->pQNode1->qElemMemory.m_pBuf;
	 pSpObj2 = ( SP_OBJ * )pSpIntersectPoint->pQNode2->qElemMemory.m_pBuf;
	 if ( pSpObj1->type == SP_CIRCLE_TYPE && pSpObj2->type == SP_CIRCLE_TYPE ) {
			if ( getAPlusAFlag( &flag, ( SP_CIRCLE * )pSpObj1, ( SP_CIRCLE * )pSpObj2, &pSpIntersectPoint->point.rect ) ) 
				goto err;
			pSpIntersectPoint->posParm = flag;
		}
	 else if ( pSpObj1->type == SP_SEGMENT_TYPE && pSpObj2->type == SP_SEGMENT_TYPE )
		 ;
	 else 
		 iErr = -1;
	 
err:
	
	 return iErr;

}


 int refreshSpPointOnObj( SP_POINT_ON_OBJ *pSPOO, SP_TRAN_PARM *pSpTranParm )
{

	 int iErr = 0;

	 switch ( ( ( SP_OBJ * )pSPOO->pObjQNode->qElemMemory.m_pBuf )->type ) {

		case SP_CIRCLE_TYPE: {

			SP_CIRCLE *pSpCircle;
			SP_POINT *pCenter;
			float r;

			pSpCircle = ( SP_CIRCLE * )pSPOO->pObjQNode->qElemMemory.m_pBuf;
			pCenter = ( SP_POINT * )pSpCircle->pCenterQNode->qElemMemory.m_pBuf;
			r = ( float )getDOf2SpPoints( pCenter, ( SP_POINT * )pSpCircle->pCircleQNode->qElemMemory.m_pBuf );

			if ( pSPOO->op == OP_MOVE ) {

					float r, A;
					
					pSPOO->point.rect.x += pSpTranParm->move.curPlace.x - pSpTranParm->move.lastPlace.x;
					pSPOO->point.rect.y += pSpTranParm->move.curPlace.y - pSpTranParm->move.lastPlace.y;
					getRAPI( &r, &A, pSPOO->point.rect.x - pCenter->point.rect.x, pSPOO->point.rect.y - pCenter->point.rect.y );
					pSPOO->posParm = ( short )API2180( A );
			}

			pSPOO->point.rect.x = ( short )( r * cos( A1802PI( pSPOO->posParm ) ) ) + pCenter->point.rect.x;
			pSPOO->point.rect.y = ( short )( r * sin( A1802PI( pSPOO->posParm ) ) ) + pCenter->point.rect.y;
							 
			}

			break;


		case SP_SEGMENT_TYPE:

			iErr = -1;
			 
			break;

		default:

			iErr = -1;
			break;

	 }

	 return iErr;

}


 int refreshSpIntersectPoint( SP_INTERSECT_POINT *pSIP )
{
	 SP_OBJ *pSpObj1, *pSpObj2;
	 int iErr = 0;

	 pSpObj1 = ( SP_OBJ * )pSIP->pQNode1->qElemMemory.m_pBuf;
	 pSpObj2 = ( SP_OBJ * )pSIP->pQNode2->qElemMemory.m_pBuf;
	 if ( pSpObj1->type == SP_CIRCLE_TYPE && pSpObj2->type == SP_CIRCLE_TYPE ) {

		iErr = refresh2CirclesSpIntersectPoint( pSIP );

		}
	 else if ( pSpObj1->type == SP_SEGMENT_TYPE && pSpObj2->type == SP_SEGMENT_TYPE ) {
	 
		 iErr = refresh2SegmentsSpIntersectPoint( pSIP );

	 }

	 else 
		 iErr = -1;
	 

	 return iErr;

	 
}

 int getReflectPoint( SP_SEGMENT *pMirror, SP_RECT_COORD *pPoint, SP_RECT_COORD *pReflectPoint )
{
	 int iErr = 0;

	 if ( pMirror->point1.rect.x == pMirror->point2.rect.x ) {
		
			if ( pMirror->point1.rect.y == pMirror->point2.rect.y ) {
					iErr = -1; goto err;
			}
	 
			pReflectPoint->y = pPoint->y;
			pReflectPoint->x = 2 * pMirror->point1.rect.x - pPoint->x;

		 }
		
	 else if ( pMirror->point1.rect.y == pMirror->point2.rect.y ) {
		 
			pReflectPoint->x = pPoint->x;
			pReflectPoint->y = 2 * pMirror->point1.rect.y - pPoint->y;

		}

	 else {

			float tmpX, k;

			k = ( pMirror->point1.rect.y - pMirror->point2.rect.y ) / ( ( float )( pMirror->point1.rect.x - pMirror->point2.rect.x ) );

			tmpX = ( pPoint->y - pMirror->point1.rect.y + k * pMirror->point1.rect.x + 1 / k * pPoint->x ) / ( k + 1 / k );
		 	 
			pReflectPoint->x = ( short )( 2 * tmpX - pPoint->x ); 
		
			tmpX = ( short )( k* ( tmpX - pMirror->point1.rect.x ) + pMirror->point1.rect.y );
			 
			pReflectPoint->y = ( short )( 2 * tmpX - pPoint->y );

	 }

err:

	 return iErr;

}


 int getRotatePoint( SP_POINT *pCenter, SP_RECT_COORD *pPoint, SP_RECT_COORD *pRotatePoint, short A180 )
{
	 int iErr = 0;
	 float A_PI, r, a;
	 
	 A_PI = ( float )A1802PI( A180 );
	 
	 if ( getRAPI( &r, &a, pPoint->x - pCenter->point.rect.x, pPoint->y - pCenter->point.rect.y ) ) {
			iErr = -1; goto err;
	 }

	 pRotatePoint->x = ( short )( pCenter->point.rect.x + r * cos( a - A_PI ) );
	 pRotatePoint->y = ( short )( pCenter->point.rect.y + r * sin( a - A_PI ) );

err:

	 return iErr;

}


 
 int setSpObjOpMove( SP_STRUCT  *  pSp,  Q_NODE *pQNode, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm )
{
	 int			iErr		=	-1;
	 SP_OBJ		*	pSpObj		=	NULL;
	 BOOL			bMoved		=	FALSE;

	 if  (  op  !=  OP_MOVE  )  return  -1;

	 pSpObj = ( SP_OBJ * )pQNode->qElemMemory.m_pBuf;

	 switch  (  pSpObj->op  )  {
			 case  OP_NULL:
				   pSpObj->op = OP_MOVE;
				   memcpy(  &pSpObj->driver,  pDriver,  sizeof(  SP_DRIVER  )  );
				   memcpy(  &pSpObj->opParm,  pOpParm,  sizeof(  pSpObj->opParm  )  );
				   break;
			 case  OP_MOVE:
				   if  (  pOpParm->iFlg  &  CONST_opFlg_x  )  {
					   if  (  pSpObj->opParm.iFlg  &  CONST_opFlg_x  )  {
						   if  (  pSpObj->opParm.move.x  !=  pOpParm->move.x  )  goto  errLabel;
						   }
					   else  {
						     pSpObj->opParm.move.x  =  pOpParm->move.x;
							 pSpObj->opParm.iFlg  |=  CONST_opFlg_x;							 
							 bMoved  =  TRUE;
					   }
				   }
				   if  (  pOpParm->iFlg  &  CONST_opFlg_y  )  {
					   if  (  pSpObj->opParm.iFlg  &  CONST_opFlg_y  )  {
						   if  (  pSpObj->opParm.move.y  !=  pOpParm->move.y  )  goto  errLabel;
						   }
					   else  {
						     pSpObj->opParm.move.y  =  pOpParm->move.y;
							 pSpObj->opParm.iFlg  |=  CONST_opFlg_y;
							 bMoved  =  TRUE;
					   }
				   }
				   if  (  !bMoved  )  {
					   iErr  =  0;  goto  errLabel;
				   }
				   break;
			 default:
					goto  errLabel;
	 }
	 
	 traceLogA(  "setSpOpMove: %S moved",  pSpObj->desc  );
	 if  (  postToOpedQ(  pQNode,  pSp  )  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 return iErr;

}

 int setSpObjOpConstraintedMove( Q_NODE *pQNode, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm )
{
	 int iErr = 0;
	 SP_OBJ *pSpObj;

	 pSpObj = ( SP_OBJ * )pQNode->qElemMemory.m_pBuf;

	 if ( pSpObj->op == OP_NULL ) {
			pSpObj->op = OP_CONSTRAINTED_MOVE;
			memcpy( &pSpObj->driver, pDriver, sizeof( SP_DRIVER ) );
			pSpObj->opParm.move.x = pOpParm->move.x;
			pSpObj->opParm.move.y = pOpParm->move.y;
			goto err;
	 }

	 iErr = -1;

err:
	 return iErr;

}

  int setSpObjOpFixed( Q_NODE *pQNode, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm )
{
	 int iErr = 0;
	 SP_OBJ *pSpObj;

	 pSpObj = ( SP_OBJ * )pQNode->qElemMemory.m_pBuf;

	 if ( pSpObj->op == OP_NULL ) {
			pSpObj->op = OP_FIXED;
			memcpy( &pSpObj->driver, pDriver, sizeof( SP_DRIVER ) );
			goto err;
	 }

	 iErr = -1;

err:
	 return iErr;

}



