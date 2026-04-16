
#include	"stdafx.h"
#include	"sp.h"


 BOOL isSamePlaceSpObj( SP_OBJ *pSpObj1, SP_OBJ *pSpObj2 )
{
	 switch ( pSpObj1->type ) {
		case SP_POINT_TYPE:
			return isSamePlaceSpPoint( ( SP_POINT * )pSpObj1, ( SP_POINT * )pSpObj2 );
		case SP_SEGMENT_TYPE:
			return isSamePlaceSpSegment( ( SP_SEGMENT * )pSpObj1, ( SP_SEGMENT * )pSpObj2 );
		case SP_CIRCLE_TYPE:
			return isSamePlaceSpCircle( ( SP_CIRCLE * )pSpObj1, ( SP_CIRCLE * )pSpObj2 );
		default:
			break;
	 }

	 return FALSE;
}
 

 BOOL isSamePlaceSpPoint( SP_POINT *pSpPoint1, SP_POINT *pSpPoint2 )
{
	 if ( abs( pSpPoint1->point.rect.x - pSpPoint2->point.rect.x ) <= SP_POINT_RANGE 
		 &&  abs( pSpPoint1->point.rect.y - pSpPoint2->point.rect.y ) <= SP_POINT_RANGE )
		 return TRUE;
	 return FALSE;

}
 

 BOOL isSamePlaceSpSegment( SP_SEGMENT *pSpSegment1, SP_SEGMENT *pSpSegment2 )
{
	 
	 if ( pSpSegment1->subType != pSpSegment2->subType ) return FALSE;
	 
	 switch ( pSpSegment1->subType ) {

		case SP_GENERIC_SEGMENT_TYPE:
	 
			if ( ( isSamePlaceSpPoint( ( SP_POINT * )pSpSegment1->pStartQNode->qElemMemory.m_pBuf,
						( SP_POINT * )pSpSegment2->pStartQNode->qElemMemory.m_pBuf )
					&& isSamePlaceSpPoint( ( SP_POINT * )pSpSegment1->pEndQNode->qElemMemory.m_pBuf,
						( SP_POINT * )pSpSegment2->pEndQNode->qElemMemory.m_pBuf ) )
				|| ( isSamePlaceSpPoint( ( SP_POINT * )pSpSegment1->pStartQNode->qElemMemory.m_pBuf,
						( SP_POINT * )pSpSegment2->pEndQNode->qElemMemory.m_pBuf )
					&& isSamePlaceSpPoint( ( SP_POINT * )pSpSegment1->pEndQNode->qElemMemory.m_pBuf,
					( SP_POINT * )pSpSegment2->pStartQNode->qElemMemory.m_pBuf ) ) ) {
				return TRUE;
			}
			
			break;

		case SP_LINE_TYPE: {

				SP_LINE *pSL1, *pSL2;

				pSL1 = ( SP_LINE * )pSpSegment1;
				pSL2 = ( SP_LINE * )pSpSegment2;

			
				if ( ( getDOf2Points( &pSL1->point1.rect, &pSL2->point1.rect ) < SP_POINT_RANGE
							&& getDOf2Points( &pSL1->point2.rect, &pSL2->point2.rect ) < SP_POINT_RANGE )
					|| ( getDOf2Points( &pSL1->point1.rect, &pSL2->point2.rect ) < SP_POINT_RANGE
							&& getDOf2Points( &pSL1->point2.rect, &pSL2->point1.rect ) < SP_POINT_RANGE ) ) {
					return TRUE;
				}			
			}

			break;

		case SP_PERPENDICULAR_LINE_TYPE: {

				SP_PERPENDICULAR_LINE *pSPL1, *pSPL2;

				pSPL1 = ( SP_PERPENDICULAR_LINE * )pSpSegment1;
				pSPL2 = ( SP_PERPENDICULAR_LINE * )pSpSegment2;

				if ( isSamePlaceSpPoint( ( SP_POINT * )pSPL1->pSpPointQNode->qElemMemory.m_pBuf, ( SP_POINT * )pSPL2->pSpPointQNode->qElemMemory.m_pBuf ) 
						&& isSamePlaceSpSegment( ( SP_SEGMENT * )pSPL1->pSpSegmentQNode->qElemMemory.m_pBuf, ( SP_SEGMENT * )pSPL2->pSpSegmentQNode->qElemMemory.m_pBuf ) ) {
					return TRUE;
				}
			
			}

			break;

		default:

			break;

	 }



	 return FALSE;

}

 BOOL isSamePlaceSpCircle( SP_CIRCLE *pSpCircle1, SP_CIRCLE *pSpCircle2 )
{
	 
	  
	 if ( isSamePlaceSpPoint( ( SP_POINT * )pSpCircle1->pCenterQNode->qElemMemory.m_pBuf,
				( SP_POINT * )pSpCircle2->pCenterQNode->qElemMemory.m_pBuf ) ) {

			float r1, r2;

			r1 = ( float ) getDOf2SpPoints( ( SP_POINT * )pSpCircle1->pCenterQNode->qElemMemory.m_pBuf,( SP_POINT * )pSpCircle1->pCircleQNode->qElemMemory.m_pBuf );
			r2 = ( float ) getDOf2SpPoints( ( SP_POINT * )pSpCircle2->pCenterQNode->qElemMemory.m_pBuf,( SP_POINT * )pSpCircle2->pCircleQNode->qElemMemory.m_pBuf );
			if ( ( unsigned int )( fabs( r1 - r2 ) )< SP_CIRCLE_RANGE ) 
				return TRUE;
	 }
	 return FALSE;

}

