
#include	"stdafx.h"
#include	"sp.h"


 int spDisCmdAnimate( SP_STRUCT *pSp )
{

	 Q_NODE *pQNode;
	 SP_ANIMATED_POINT tmpSpAnimatedPoint;
	 SP_ANIMATOR tmpSpAnimator, *pSpAnimator;
	 int nSAPs = 0, sAPIndex = 0;
	 SP_OBJ *pSpObj;
	 int iErr = 0, i = 0;

	 memset( &tmpSpAnimatedPoint, 0, sizeof( SP_ANIMATED_POINT ) );
	 memset( &tmpSpAnimator, 0, sizeof( SP_ANIMATOR ) );
	 tmpSpAnimator.type = SP_ANIMATOR_TYPE;
	 tmpSpAnimator.subType = SP_GENERIC_ANIMATOR_TYPE;
	 
	 if ( qPostMsg( &tmpSpAnimator, sizeof( tmpSpAnimator ),  pSp->pSpObjQ,  _T(  "spDiscmdAnimate"  ))) {
			iErr = -1; goto err;
	 }

	 pSpAnimator = (  SP_ANIMATOR  *  )getpLastQNode( pSp->pSpObjQ )->qElemMemory.m_pBuf;

	 for ( pQNode = pSp->pSelectedSpObjQ->front.pNext; pQNode; pQNode = pQNode->pNext ) {
		 pSpObj = ( SP_OBJ * )( ( SP_SELECT_Q_ELEM * )pQNode->qElemMemory.m_pBuf )->pQNode->qElemMemory.m_pBuf;
		 if ( pSpObj->type == SP_POINT_TYPE ) {
			 if ( nSAPs >= ( sizeof( pSpAnimator->sAP ) / sizeof ( SP_ANIMATED_POINT ) ) ) {
				 iErr = -1;
				 spShowInfo( "Only as many as %d points can be animated simultaneously on as many as %d paths", 
					 ( sizeof( pSpAnimator->sAP ) / sizeof ( SP_ANIMATED_POINT ) ),
					 ( sizeof( pSpAnimator->sAP ) / sizeof ( SP_ANIMATED_POINT ) ) );
				 goto err;
			 }
			 pSpAnimator->sAP[nSAPs].pPointQNode = ( ( SP_SELECT_Q_ELEM * )pQNode->qElemMemory.m_pBuf )->pQNode;
			 /* pay attention here,v of SAP must be processed */
			 pSpAnimator->sAP[nSAPs].v = 3;
			 nSAPs ++;
			}
		 else { 
			 if ( pSpObj->type != SP_SEGMENT_TYPE
						&& pSpObj->type != SP_CIRCLE_TYPE ) {
					spShowInfo( "A path may be a segment, ray, line, circle, arc, arc segment or sector, polygon interior, or locus of a point." );
					iErr = -1;
					goto err;
				}
			 else {
				 if ( sAPIndex >= ( sizeof( pSpAnimator->sAP ) / sizeof ( SP_ANIMATED_POINT ) ) ) {
						iErr = -1;
						spShowInfo( "Only as many as %d points can be animated simultaneously on as many as %d paths", 
							( sizeof( pSpAnimator->sAP ) / sizeof ( SP_ANIMATED_POINT ) ),
							( sizeof( pSpAnimator->sAP ) / sizeof ( SP_ANIMATED_POINT ) ) );
						goto err;
			 	 }
					
				 for ( i = sAPIndex; pSpAnimator->sAP[i].pPointQNode; i ++ )			
						pSpAnimator->sAP[i].pPathQNode = ( ( SP_SELECT_Q_ELEM * )pQNode->qElemMemory.m_pBuf )->pQNode;
			}
		 
		 }
	 
	 } /* end of for( ; ; ) */

	 pSp->curpProcQNode = getpLastQNode( pSp->pSpObjQ );
	 pSp->op = OP_ANIMATE;
	 if ( preOpSp( pSp ) ) {
			iErr = -1; goto err;
	 }
	 if ( opSp( pSp ) ) {
			iErr = -1; goto err;
	 }

err:

			 return iErr;

}


 int spDisCmdTimer( SP_STRUCT *pSp )
{

	 int iErr = 0;
	 static int i = 0;


	 switch ( pSp->tranType ) {

	 case DISCMD_ANIMATE_TRAN: {
			
				/* move every animated point and refresh all others */
				/* every point can be animated indepedently and sequently */

				spShowInfo( "spDisCmdTimer():animated %d times", i );
				i++;

				pSp->op = OP_ANIMATE;
				opSp( pSp );

			}

			break;

		default:

			iErr = -1;

			break;

	 }

	 return iErr;


}




 int animateToPath( SP_STRUCT *pSp, SP_ANIMATED_POINT *pSAP )
{
	 int iErr = 0;
	 SP_RECT_COORD point;
	 SP_MOVE_TRAN_PARM tmpMoveParm;
	 SP_PARM parm;

	 if ( getNearestPointOnPath( (  SP_POINT  *  )pSAP->pPointQNode->qElemMemory.m_pBuf, (  SP_OBJ  *  )pSAP->pPathQNode->qElemMemory.m_pBuf, &point ) ) {
			iErr = -1; goto err;
	 }

	 tmpMoveParm.curPlace.x = point.x;
	 tmpMoveParm.curPlace.y = point.y;
	 tmpMoveParm.lastPlace.x = ( ( SP_POINT * )pSAP->pPointQNode->qElemMemory.m_pBuf )->point.rect.x;
	 tmpMoveParm.lastPlace.y = ( ( SP_POINT * )pSAP->pPointQNode->qElemMemory.m_pBuf )->point.rect.y;
			
	 if ( preOpSpPoint( pSp, pSAP->pPointQNode, OP_MOVE, NULL, NULL, &parm ) ) { iErr = -1; goto err; }
	 //if ( opSpPoint( pSp->pSpObjQ, pSAP->pPointQNode->pQElem, OP_MOVE, ( SP_TRAN_PARM * )&tmpMoveParm ) ) { iErr = -1; goto err; }
	 if ( opSpObj( pSp, (  SP_OBJ  *  )pSAP->pPointQNode->qElemMemory.m_pBuf ) ) { iErr = -1; goto err; }
					

err:

	 return iErr;

}

 int animateOnPath( SP_STRUCT *pSp, SP_ANIMATED_POINT *pSAP )
{
	 SP_RECT_COORD point;
	 int iErr = 0;
	 SP_MOVE_TRAN_PARM tmpMoveParm;
	 SP_PARM parm;
	 SP_OP_PARM tmpOpParm;

	 tmpMoveParm.lastPlace.x = ( ( SP_POINT * )pSAP->pPointQNode->qElemMemory.m_pBuf )->point.rect.x;
	 tmpMoveParm.lastPlace.y = ( ( SP_POINT * )pSAP->pPointQNode->qElemMemory.m_pBuf )->point.rect.y;
	 

	 if ( getNextPosOnPath( pSAP, &point ) ) {
		 iErr = -1; goto err;
	 }

	 tmpMoveParm.curPlace.x = point.x;
	 tmpMoveParm.curPlace.y = point.y;
	 tmpOpParm.move.x = tmpMoveParm.curPlace.x - tmpMoveParm.lastPlace.x;
	 tmpOpParm.move.y = tmpMoveParm.curPlace.y - tmpMoveParm.lastPlace.y;

	 if ( preOpSpPoint( pSp, pSAP->pPointQNode, OP_MOVE, &tmpOpParm, NULL, &parm ) ) {
		 iErr = -1; goto err;
	 }
	 //if ( opSpPoint( pSp->pSpObjQ, pSAP->pPointQNode->pQElem, OP_MOVE, ( SP_TRAN_PARM * )&tmpMoveParm ) ) { iErr = -1; goto err; }
	 if ( opSpObj( pSp, (  SP_OBJ  *  )pSAP->pPointQNode->qElemMemory.m_pBuf ) ) { iErr = -1; goto err; }

	
err:
	 return iErr;

}


 int getNextPosOnPath( SP_ANIMATED_POINT *pSAP, SP_RECT_COORD *pPoint )
{
	 int iErr = 0;

	 switch ( ( ( SP_OBJ * )pSAP->pPathQNode->qElemMemory.m_pBuf )->type ) {

		case SP_SEGMENT_TYPE:
			getNextPosOnSegment( pSAP, pPoint );
			break;
		default:
			iErr = -1;
			break;
	 }

	 return 0;


}

 int getNextPosOnSegment( SP_ANIMATED_POINT *pSAP, SP_RECT_COORD *pPoint )
{
	 SP_RECT_COORD *p1, *p2;
	 float d12, d1p;
	 
	 
	 p1 = &( ( SP_POINT * )( ( SP_SEGMENT * )pSAP->pPathQNode->qElemMemory.m_pBuf )->pStartQNode->qElemMemory.m_pBuf )->point.rect;
	 p2 = &( ( SP_POINT * )( ( SP_SEGMENT * )pSAP->pPathQNode->qElemMemory.m_pBuf )->pEndQNode->qElemMemory.m_pBuf )->point.rect;
	 pPoint->x = ( ( SP_POINT * )pSAP->pPointQNode->qElemMemory.m_pBuf )->point.rect.x;
	 pPoint->y = ( ( SP_POINT * )pSAP->pPointQNode->qElemMemory.m_pBuf )->point.rect.y;
	 
	 d12 = ( float )getDOf2Points( p1, p2 );
	 if ( d12 < SP_POINT_RANGE ) return -1;

	 d1p = ( float )getDOf2Points( p1, pPoint );
	 d1p += ( int )pSAP->v;

	 if ( d1p < 0 || d1p > d12 ) { pSAP->v = -1 * pSAP->v; return 0; }
	 	 
	 pPoint->y = ( short )( d1p / ( float )d12 * ( p2->y - p1->y ) ) + p1->y;
	 pPoint->x = ( short )( d1p / ( float )d12 * ( p2->x - p1->x ) )+ p1->x;

	 return 0;


}
