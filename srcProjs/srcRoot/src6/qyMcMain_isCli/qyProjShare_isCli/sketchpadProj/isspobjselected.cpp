
#include	"stdafx.h"
#include	"sp.h"


 BOOL isSpObjSelected( SP_OBJ *pSpObj, SP_RECT_COORD *pPoint )
{
	 BOOL bRet = FALSE;

	 switch ( pSpObj->type ) {

		case SP_POINT_TYPE:

			if ( isSpPointSelected( ( SP_POINT * )pSpObj, pPoint ) == TRUE ) bRet = TRUE;
			
			break;

		case SP_SEGMENT_TYPE:

			if ( isSpSegmentSelected( ( SP_SEGMENT * )pSpObj, pPoint ) == TRUE ) bRet = TRUE;

			break;

		case SP_CIRCLE_TYPE:

			if ( isSpCircleSelected( ( SP_CIRCLE * )pSpObj, pPoint ) == TRUE ) bRet = TRUE;

			break;

		default:

			break;

	 } /* end of switch() */

	 return bRet;

}

 BOOL isSpPointSelected( SP_POINT *pSpPoint, SP_RECT_COORD *pHere )
{
	 if ( abs( pSpPoint->point.rect.x - pHere->x ) <= SP_POINT_RANGE 
		 && abs( pSpPoint->point.rect.y - pHere->y ) <= SP_POINT_RANGE )
		 return TRUE;
	 return FALSE;

}

 BOOL isSpSegmentSelected( SP_SEGMENT *pSpSegment, SP_RECT_COORD *pPoint )
{
	 float d;
	 int iErr = 0;

	 switch ( pSpSegment->subType ) {

		case SP_GENERIC_SEGMENT_TYPE:
		case SP_REFLECT_SEGMENT_TYPE:

			d = getDOfPointFromSegment( pPoint, 
						&pSpSegment->point1.rect,
						&pSpSegment->point2.rect );
	 		if ( d < 0 ) {
					iErr = -1; break;
			}
	
			break;

		case SP_LINE_TYPE: {

				SP_LINE *p = ( SP_LINE * )pSpSegment;
			
				d = getDOfPointFromSegment( pPoint, 
					&p->point1.rect,
					&p->point2.rect );
	 			if ( d < 0 ) {
						iErr = -1; break;
				}
	
			}

			break;


		case SP_PERPENDICULAR_LINE_TYPE: {

				SP_PERPENDICULAR_LINE *p = ( SP_PERPENDICULAR_LINE * )pSpSegment;
			
				d = getDOfPointFromSegment( pPoint, 
					&p->point1.rect,
					&p->point2.rect );
	 			if ( d < 0 ) {
						iErr = -1; break;
				}
	
			}

			break;

		default:

			iErr = -1;

			break;

	 }

	 if ( iErr ) goto err;
	
err:

	 if ( iErr ) return FALSE;

	 if ( d < SP_SEGMENT_RANGE ) return TRUE;
	
	 return FALSE;

}

 BOOL isSpCircleSelected( SP_CIRCLE *pSpCircle, SP_RECT_COORD *pPoint )
{
	 float d,r;

	 r = ( float )getDOf2SpPoints( ( SP_POINT * )pSpCircle->pCenterQNode->qElemMemory.m_pBuf, ( SP_POINT * )pSpCircle->pCircleQNode->qElemMemory.m_pBuf );
	 d = ( float )getDOf2Points( &( ( SP_POINT * )pSpCircle->pCenterQNode->qElemMemory.m_pBuf )->point.rect, pPoint );

	 if ( ( unsigned int )fabs( r - d ) < SP_CIRCLE_RANGE ) return TRUE;
	
	 return FALSE;

}
