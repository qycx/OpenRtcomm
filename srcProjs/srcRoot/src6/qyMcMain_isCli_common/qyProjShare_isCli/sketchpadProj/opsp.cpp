
#include	"stdafx.h"
#include	"sp.h"

 const OP_FUNC gOpFunc[ 1 + TOTAL_SUB_TYPES_OF_SP_OBJ ] = { 

			(  OP_FUNC  )opNull,
			
			(  OP_FUNC  )opSpGenericPoint,
			(  OP_FUNC  )opSpIntersectPoint,
			(  OP_FUNC  )opSpPointOnObj,
			(  OP_FUNC  )opSpReflectPoint,
			(  OP_FUNC  )opSpRotatePoint,

			(  OP_FUNC  )opSpGenericSegment,
			(  OP_FUNC  )opSpLine,
			(  OP_FUNC  )opSpPerpendicularLine,
			(  OP_FUNC  )opSpReflectSegment,
			(  OP_FUNC  )opSpReflectLine,

			(  OP_FUNC  )opSpGenericCircle,
			(  OP_FUNC  )opNull,
			(  OP_FUNC  )opNull,
			(  OP_FUNC  )opNull,

			(  OP_FUNC  )opSpGenericAngleBisector,

			(  OP_FUNC  )opSpGenericAnimator,

			(  OP_FUNC  )opSpGenericRectangle,


 };

 OP_FUNC getOpFunc( BYTE type, BYTE subType )
{
	 int indexBase = 0;

	 switch ( type ) {

		case SP_POINT_TYPE:

			indexBase = 1;
			
			break;

		case SP_SEGMENT_TYPE:

			indexBase = 1 + TOTAL_SUB_TYPES_OF_SP_POINT;
			
			break;
			
		case SP_CIRCLE_TYPE:

			indexBase = 1 + TOTAL_SUB_TYPES_OF_SP_POINT + TOTAL_SUB_TYPES_OF_SP_SEGMENT;

			break;

		case SP_ANGLE_BISECTOR_TYPE:

			indexBase = 1 + TOTAL_SUB_TYPES_OF_SP_POINT + TOTAL_SUB_TYPES_OF_SP_SEGMENT +
				TOTAL_SUB_TYPES_OF_SP_CIRCLE;

			break;

		case SP_ANIMATOR_TYPE:

			indexBase = 1 + TOTAL_SUB_TYPES_OF_SP_POINT + TOTAL_SUB_TYPES_OF_SP_SEGMENT +
				TOTAL_SUB_TYPES_OF_SP_CIRCLE + TOTAL_SUB_TYPES_OF_SP_ANGLE_BISECTOR;
						
			break;
		case  SP_RECTANGLE_TYPE:
			  indexBase = 1 + TOTAL_SUB_TYPES_OF_SP_POINT + TOTAL_SUB_TYPES_OF_SP_SEGMENT +
				TOTAL_SUB_TYPES_OF_SP_CIRCLE + TOTAL_SUB_TYPES_OF_SP_ANGLE_BISECTOR  +  TOTAL_SUB_TYPES_OF_SP_ANIMATOR;
			  break;
		default:

			indexBase = 0;

			break;

	 }

	 if ( indexBase ) return gOpFunc[ indexBase + subType ];
	 return gOpFunc[0];

}

__declspec(  dllexport  )   int opSp( SP_STRUCT *pSp )
{
	 Q_NODE *pQNode;
	 int i;

	 
	 switch ( pSp->op ) {
		
		case OP_DELETE: {
		
				Q_NODE *tmppQNode;
				for ( pQNode = pSp->pSpObjQ->front.pNext; pQNode; pQNode = tmppQNode ) {
					tmppQNode = pQNode->pNext;
				if ( ( ( SP_OBJ * )pQNode->qElemMemory.m_pBuf )->op != OP_DELETE ) continue;
			 			removeAQNode( pSp->pSpObjQ, pQNode );
		 		}

			}

			break;
			
		case OP_MOVE:

			for ( pQNode = pSp->pSpObjQ->front.pNext; pQNode; pQNode = pQNode->pNext ) {
						
				if ( opSpObj( pSp, ( SP_OBJ * )pQNode->qElemMemory.m_pBuf ) ) 
			 			( ( SP_OBJ * )pQNode->qElemMemory.m_pBuf )->status |= STATUS_INVALID;
				else
						( ( SP_OBJ * )pQNode->qElemMemory.m_pBuf )->status &= ~STATUS_INVALID;
		 	
			}
	 
			break;

		case OP_ANIMATE:

#ifdef __SP_DEBUG__
			printSpObj( ( SP_OBJ * )pSp->curpProcQNode->qElemMemory.m_pBuf ) ;
#endif
			if ( !( ( ( SP_ANIMATOR * )pSp->curpProcQNode->qElemMemory.m_pBuf )->status & STATUS_ANIMATED ) ) {
					for ( i = 0; ( ( SP_ANIMATOR * )pSp->curpProcQNode->qElemMemory.m_pBuf )->sAP[i].pPointQNode 
							&& ( ( SP_ANIMATOR * )pSp->curpProcQNode->qElemMemory.m_pBuf )->sAP[i].pPathQNode; i ++ ) {
						animateToPath( pSp, &( ( SP_ANIMATOR * )pSp->curpProcQNode->qElemMemory.m_pBuf )->sAP[i] );
					}
					( ( SP_ANIMATOR * )pSp->curpProcQNode->qElemMemory.m_pBuf )->status |= STATUS_ANIMATED;
				}
			else {
				for ( i = 0; ( ( SP_ANIMATOR * )pSp->curpProcQNode->qElemMemory.m_pBuf )->sAP[i].pPointQNode 
							&& ( ( SP_ANIMATOR * )pSp->curpProcQNode->qElemMemory.m_pBuf )->sAP[i].pPathQNode; i ++ ) {
						animateOnPath( pSp, &( ( SP_ANIMATOR * )pSp->curpProcQNode->qElemMemory.m_pBuf )->sAP[i] );
					}
			}
				


			break;
			
		default:

			pSp->errNo = -1;

			break;

	 }

	return pSp->errNo;

}


 int opSpObj( SP_STRUCT *pSp, SP_OBJ *pSpObj )
{
	OP_FUNC pf	=	NULL;

	pf = getOpFunc( pSpObj->type, pSpObj->subType );
	if  (  !pf  )  {
		traceLogA(  "opSpObj failed: pf is null"  );
		return  -1;
	}

	return ( *pf )( pSp, pSpObj );
	 
}

 int opNull( SP_STRUCT *pSp, SP_OBJ *pSpObj )
{
	 return 0;
}
 

 int opSpGenericPoint( SP_STRUCT *pSp, SP_POINT *pSpPoint )
{
	 int iErr = 0;

	 switch ( pSpPoint->op ) {

		case OP_NULL:

			break;
	
		case OP_MOVE:

			pSpPoint->point.rect.x += pSpPoint->opParm.move.x;
			pSpPoint->point.rect.y += pSpPoint->opParm.move.y;
						
			break;


		case OP_FIXED:
				break;

		case OP_CONSTRAINTED_MOVE:

			pSpPoint->point.rect.x += pSpPoint->opParm.move.x;
			pSpPoint->point.rect.y += pSpPoint->opParm.move.y;		

			break;
					
		default:
				
			iErr = -1;
		
			break;

	 }

	 return iErr;

}

  int opSpIntersectPoint( SP_STRUCT *pSp, SP_INTERSECT_POINT *pSpPoint )
{
	 
	 if ( ( ( SP_OBJ * )pSpPoint->pQNode1->qElemMemory.m_pBuf )->status & STATUS_INVALID 
			|| ( ( SP_OBJ * )pSpPoint->pQNode2->qElemMemory.m_pBuf )->status & STATUS_INVALID ) {
		 return -1;
	 }
	 	 
	 if ( refreshSpIntersectPoint( pSpPoint ) ) return -1;

	 return 0;

}

 
 int opSpPointOnObj( SP_STRUCT *pSp, SP_POINT_ON_OBJ *pSpPoint )
{
	 int iErr = 0;

	 if ( ( ( SP_OBJ * )pSpPoint->pObjQNode->qElemMemory.m_pBuf )->status & STATUS_INVALID )
		 return -1;

	 switch ( pSpPoint->op ) {

		case OP_REFRESH_CONSTRAINT:
			
			/* pay attention here, refresh_constraint not implemented */
			iErr = -1;

			break;

		default:

			iErr = refreshSpPointOnObj( pSpPoint, &pSp->tranParm );
			
			break;

	 }

	
	 return iErr;

}

 int opSpReflectPoint( SP_STRUCT *pSp, SP_REFLECT_POINT *pSpPoint )
{
	 int iErr = 0;
	 SP_SEGMENT *pMirror;
	 SP_POINT *pReflectedSpPoint;
	 
	 pMirror = ( SP_SEGMENT * )pSpPoint->pMirrorQNode->qElemMemory.m_pBuf;
	 pReflectedSpPoint = ( SP_POINT * )pSpPoint->pReflectedQNode->qElemMemory.m_pBuf;

	 if ( pMirror->status & STATUS_INVALID || pReflectedSpPoint->status & STATUS_INVALID ) 
		 return -1;

	 switch ( pSpPoint->op ) {

		case OP_MOVE:

			pSpPoint->point.rect.x += pSpPoint->opParm.move.x;
			pSpPoint->point.rect.y += pSpPoint->opParm.move.y;

			break;

		case OP_FIXED:

			break;

		default:

			if ( getReflectPoint( pMirror, &pReflectedSpPoint->point.rect, &pSpPoint->point.rect ) ) {
					iErr = -1; goto err;
			}
			break;

	 }

err:
	 
	 return iErr;

}


 int opSpRotatePoint( SP_STRUCT *pSp, SP_ROTATE_POINT *pSpPoint )
{
	 int iErr = 0;
	 SP_POINT *pCenter;
	 SP_POINT *pRotatedSpPoint;
	 
	 pCenter = ( SP_POINT * )pSpPoint->pCenterQNode->qElemMemory.m_pBuf;
	 pRotatedSpPoint = ( SP_POINT * )pSpPoint->pRotatedQNode->qElemMemory.m_pBuf;

	 if ( pCenter->status & STATUS_INVALID || pRotatedSpPoint->status & STATUS_INVALID ) 
		 return -1;

	 switch ( pSpPoint->op ) {

		case OP_MOVE:

			pSpPoint->point.rect.x += pSpPoint->opParm.move.x;
			pSpPoint->point.rect.y += pSpPoint->opParm.move.y;

			break;

		case OP_FIXED:

			break;

		default:

			if ( getRotatePoint( pCenter, &pRotatedSpPoint->point.rect, &pSpPoint->point.rect, pSpPoint->A180 ) ) {
					iErr = -1; goto err;
			}
			break;

	 }

err:
	 
	 return iErr;
 

}



 int opSpGenericSegment( SP_STRUCT *pSp, SP_SEGMENT *pSpSegment )
{
	 int iErr = -1;


	 if ( ( ( SP_POINT * )pSpSegment->pStartQNode->qElemMemory.m_pBuf )->status & STATUS_INVALID 
			|| ( ( SP_POINT * )pSpSegment->pEndQNode->qElemMemory.m_pBuf )->status & STATUS_INVALID ) 
	 {
		goto err;
	 }

	 pSpSegment->point1.rect.x = ( ( SP_POINT * )pSpSegment->pStartQNode->qElemMemory.m_pBuf )->point.rect.x;
	 pSpSegment->point1.rect.y = ( ( SP_POINT * )pSpSegment->pStartQNode->qElemMemory.m_pBuf )->point.rect.y;

	 pSpSegment->point2.rect.x = ( ( SP_POINT * )pSpSegment->pEndQNode->qElemMemory.m_pBuf )->point.rect.x;
	 pSpSegment->point2.rect.y = ( ( SP_POINT * )pSpSegment->pEndQNode->qElemMemory.m_pBuf )->point.rect.y;

	 iErr  =  0;
err:
	 return iErr;
}

  int opSpLine( SP_STRUCT *pSp, SP_LINE *pSL )
{

	 int iErr = 0;
	 SP_POINT *pSpPoint1 = NULL, *pSpPoint2 = NULL;
	 float k;

	 if ( ( ( SP_POINT * )pSL->pQNode1->qElemMemory.m_pBuf )->status & STATUS_INVALID 
			|| ( ( SP_OBJ * )pSL->pQNode2->qElemMemory.m_pBuf )->status & STATUS_INVALID ) {
		iErr = -1; goto err;
	 }

	 pSpPoint1 = ( SP_POINT * )pSL->pQNode1->qElemMemory.m_pBuf;
	 pSpPoint2 = ( SP_POINT * )pSL->pQNode2->qElemMemory.m_pBuf;
	  	
	 if ( pSpPoint1->point.rect.x == pSpPoint2->point.rect.x ) {

		 pSL->point1.rect.x = pSpPoint1->point.rect.x;
		 pSL->point1.rect.y = 0;
		 pSL->point2.rect.x = pSpPoint1->point.rect.x;
		 pSL->point2.rect.y = pSp->spHeight;

		}
	 else {

		 float tmpY;

		 k = ( pSpPoint1->point.rect.y - pSpPoint2->point.rect.y ) / ( ( float )( pSpPoint1->point.rect.x - pSpPoint2->point.rect.x ) ); 
		 pSL->point1.rect.x = 0;
		 tmpY = k * ( pSL->point1.rect.x - pSpPoint1->point.rect.x ) + pSpPoint1->point.rect.y;
		 if ( tmpY > MAX_SHORT_VALUE ) {
			 pSL->point1.rect.y = pSp->spHeight;
			 pSL->point1.rect.x = ( short )( ( pSL->point1.rect.y - pSpPoint1->point.rect.y ) / k + pSpPoint1->point.rect.x );
			}
		 else if ( tmpY < MIN_SHORT_VALUE ) {
			 pSL->point1.rect.y = 0;
			 pSL->point1.rect.x = ( short )( ( pSL->point1.rect.y - pSpPoint1->point.rect.y ) / k + pSpPoint1->point.rect.x );
			}
		 else
			 pSL->point1.rect.y = ( short )tmpY;

			
		 pSL->point2.rect.x = pSp->spWidth;
		 
		 tmpY = k * ( pSL->point2.rect.x - pSpPoint1->point.rect.x ) + pSpPoint1->point.rect.y;
		 if ( tmpY > MAX_SHORT_VALUE ) {
			 pSL->point2.rect.y = pSp->spHeight;
			 pSL->point2.rect.x = ( short )( ( pSL->point2.rect.y - pSpPoint1->point.rect.y ) / k + pSpPoint1->point.rect.x );
			}
		 else if ( tmpY < MIN_SHORT_VALUE ) {
			 pSL->point2.rect.y = 0;
			 pSL->point2.rect.x = ( short )( ( pSL->point2.rect.y - pSpPoint1->point.rect.y ) / k + pSpPoint1->point.rect.x );
			}
		 else
			 pSL->point2.rect.y = ( short )tmpY;

	 }


err:
			
	 return iErr;

}



  int opSpPerpendicularLine( SP_STRUCT *pSp, SP_PERPENDICULAR_LINE *pSPL )
{

	 int iErr = 0;
	 SP_SEGMENT *pSpSegment;
	 SP_POINT *pSpPoint, *p1, *p2;
	 float k;


	 if ( ( ( SP_POINT * )pSPL->pSpPointQNode->qElemMemory.m_pBuf )->status & STATUS_INVALID 
			|| ( ( SP_OBJ * )pSPL->pSpSegmentQNode->qElemMemory.m_pBuf )->status & STATUS_INVALID ) {
		iErr = -1; goto err;
	 }

	 pSpSegment = ( SP_SEGMENT * )pSPL->pSpSegmentQNode->qElemMemory.m_pBuf;
	 pSpPoint = ( SP_POINT * )pSPL->pSpPointQNode->qElemMemory.m_pBuf;
	 
	 p1 = ( SP_POINT * )pSpSegment->pStartQNode->qElemMemory.m_pBuf;
	 p2 = ( SP_POINT * )pSpSegment->pEndQNode->qElemMemory.m_pBuf;
	
	 if ( p1->point.rect.x == p2->point.rect.x ) {
			 pSPL->point1.rect.x = 0;
			 pSPL->point1.rect.y = pSpPoint->point.rect.y;
			 pSPL->point2.rect.x = pSp->spWidth;
			 pSPL->point2.rect.y = pSpPoint->point.rect.y;
		}
	 else if ( p1->point.rect.y == p2->point.rect.y ) {
			 pSPL->point1.rect.x = pSpPoint->point.rect.x;
			 pSPL->point1.rect.y = 0;
			 pSPL->point2.rect.x = pSpPoint->point.rect.x;
			 pSPL->point2.rect.y = pSp->spHeight;
		}
	 else {
			 float tmpY;			
			
			 k = ( p1->point.rect.y - p2->point.rect.y ) / ( ( float )( p1->point.rect.x - p2->point.rect.x ) );
			 k = ( float )( -1. / k );
		
			 pSPL->point1.rect.x = 0;
			 tmpY = k * ( pSPL->point1.rect.x - pSpPoint->point.rect.x ) + pSpPoint->point.rect.y;
			 
			 if ( tmpY > MAX_SHORT_VALUE ) {
			 
				 pSPL->point1.rect.y = pSp->spHeight;
				 pSPL->point1.rect.x = ( short )( ( pSPL->point1.rect.y - pSpPoint->point.rect.y ) / k + pSpPoint->point.rect.x );

				}
			 else if ( tmpY < MIN_SHORT_VALUE ) {
				 
				 pSPL->point1.rect.y = 0;
				 pSPL->point1.rect.x = ( short )( ( pSPL->point1.rect.y - pSpPoint->point.rect.y ) / k + pSpPoint->point.rect.x );

				}
			 else 
				 pSPL->point1.rect.y = ( short )tmpY;
				
			 pSPL->point2.rect.x = pSp->spWidth;
			 tmpY = k * ( pSPL->point2.rect.x - pSpPoint->point.rect.x ) + pSpPoint->point.rect.y;

			 
			 if ( tmpY > MAX_SHORT_VALUE ) {

				 pSPL->point2.rect.y = pSp->spHeight;
				 pSPL->point2.rect.x = ( short )( ( pSPL->point2.rect.y - pSpPoint->point.rect.y ) / k + pSpPoint->point.rect.x );

				}
			 else if ( tmpY < MIN_SHORT_VALUE ) {
			 
				 pSPL->point2.rect.y = 0;
				 pSPL->point2.rect.x = ( short )( ( pSPL->point2.rect.y - pSpPoint->point.rect.y ) / k + pSpPoint->point.rect.x );

				}
			 else
				 pSPL->point2.rect.y = ( short )tmpY; 
				 
	 }



err:
			
	 return iErr;

}

 int opSpReflectSegment( SP_STRUCT *pSp, SP_REFLECT_SEGMENT *pSpSegment )
{
 	 SP_SEGMENT *pMirror;
	 SP_SEGMENT *pReflectedSpSegment;
	 int iErr = 0;

 	 pReflectedSpSegment = ( SP_SEGMENT * )pSpSegment->pReflectedQNode->qElemMemory.m_pBuf;
	 pMirror = ( SP_SEGMENT * )pSpSegment->pMirrorQNode->qElemMemory.m_pBuf;


	 if ( pReflectedSpSegment->status & STATUS_INVALID || pMirror->status & STATUS_INVALID ) {
		 return -1;
	 }

	 switch ( pSpSegment->op ) {

		case OP_MOVE:

			pSpSegment->point1.rect.x += pSpSegment->opParm.move.x;
			pSpSegment->point1.rect.y += pSpSegment->opParm.move.y;
			pSpSegment->point2.rect.x += pSpSegment->opParm.move.x;
			pSpSegment->point2.rect.y += pSpSegment->opParm.move.y;

			break;

		case OP_FIXED:

			break;

		case OP_CONSTRAINTED_MOVE:

			pSpSegment->point1.rect.x += pSpSegment->opParm.move.x;
			pSpSegment->point1.rect.y += pSpSegment->opParm.move.y;
			pSpSegment->point2.rect.x += pSpSegment->opParm.move.x;
			pSpSegment->point2.rect.y += pSpSegment->opParm.move.y;

			break;


		default:

			if ( getReflectPoint( pMirror, &pReflectedSpSegment->point1.rect, &pSpSegment->point1.rect ) ) {
					iErr = -1; goto err;
	 		}
 
			if ( getReflectPoint( pMirror, &pReflectedSpSegment->point2.rect, &pSpSegment->point2.rect ) ) {
					iErr = -1; goto err;
			}

			break;
 
	 }

err:
	 return iErr;

}

 int opSpReflectLine( SP_STRUCT *pSp, SP_REFLECT_LINE *pSpReflectLine )
{
	 int iErr = 0;
	 SP_SEGMENT *pMirror;
	 SP_LINE *pSpLine;

	 pMirror = ( SP_SEGMENT * )pSpReflectLine->pMirrorQNode->qElemMemory.m_pBuf;
	 pSpLine = ( SP_LINE * )pSpReflectLine->pReflectedQNode->qElemMemory.m_pBuf;

	 if ( pSpLine->status & STATUS_INVALID || pMirror->status & STATUS_INVALID ) {
		 return -1;
	 }

	 if ( getReflectPoint( pMirror, &pSpLine->point1.rect, &pSpReflectLine->point1.rect ) ) {
		 iErr = -1; goto err;
	 }

	 if ( getReflectPoint( pMirror, &pSpLine->point2.rect, &pSpReflectLine->point2.rect ) ) {
		 iErr = -1; goto err;
	 }

err:

	 return 0;

}



 int opSpGenericCircle( SP_STRUCT *pSp, SP_CIRCLE *pSAB )
{
	 int iErr = 0;

	 return 0;

}


 int opSpGenericAngleBisector( SP_STRUCT *pSp, SP_ANGLE_BISECTOR *pSAB )
{
	 int iErr = 0;

	 if ( ( ( SP_POINT * )pSAB->p1->qElemMemory.m_pBuf )->status & STATUS_INVALID ||
			( ( SP_POINT * )pSAB->p2->qElemMemory.m_pBuf )->status & STATUS_INVALID ||
			( ( SP_POINT * )pSAB->p3->qElemMemory.m_pBuf )->status & STATUS_INVALID ) {
		 iErr = -1;
		 goto err;
	 }

	 if ( getRayPointForAngleBisector( ( SP_POINT * )pSAB->p1->qElemMemory.m_pBuf, 
			( SP_POINT * )pSAB->p2->qElemMemory.m_pBuf, ( SP_POINT * )pSAB->p3->qElemMemory.m_pBuf, 
			&pSAB->rayPoint ) ) {
		iErr = -1; 
		goto err;
	 }
						
err:

	return iErr;	

}

 int opSpGenericAnimator( SP_STRUCT *pSp, SP_ANIMATOR *pSA )
{

	 int iErr = 0;

	 switch ( pSA->op ) {

		case OP_NULL:

			break;

		default:

			iErr = -1;

			break;

	 }

	 return iErr;

}

 int opSpGenericRectangle( SP_STRUCT *pSp, SP_RECTANGLE *pSA )
{

	 int iErr = 0;

	 switch ( pSA->op ) {

		case OP_NULL:

			break;

		default:

			iErr = -1;

			break;

	 }

	 return iErr;

}
 
