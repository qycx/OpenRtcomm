
#include	"stdafx.h"
#include	"sp.h"

 /* opSp() is used to operate on pSpSelectedQ, but others functions called by or related to it */
 /* is operate on pSpObjQ,MUST pay attention to this difference		*/
 /* */

 int  postToOpedQ(  Q_NODE  *  pQNode,  SP_STRUCT  *  pSp  )
{
	SP_OPED_Q_ELEM	mem;
	memset(  &mem,  0,  sizeof(  mem  )  );
	mem.pQNode  =  pQNode;
	return  qPostMsg(  &mem,  sizeof(  mem  ),  pSp->pOpedSpObjQ, _T(  "postToOpedQ"  ));
}

 int  preOpSp(  SP_STRUCT  *  pSp  )
{
	 int			iErr	=	-1;
	 Q_NODE		*	pQNode;
	 SP_PARM		parm;
	 SP_OP_PARM		tmpOpParm;

	 switch  (  pSp->op  )  {
			 case  OP_MOVE:
				   memset(  &tmpOpParm,  0, sizeof(  tmpOpParm  )  );
				   tmpOpParm.iFlg  =  (  CONST_opFlg_x  |  CONST_opFlg_y  );
				   tmpOpParm.move.x = pSp->tranParm.move.curPlace.x - pSp->tranParm.move.lastPlace.x;
				   tmpOpParm.move.y = pSp->tranParm.move.curPlace.y - pSp->tranParm.move.lastPlace.y;

				   for  (  pQNode = pSp->pSelectedSpObjQ->pRear; pQNode  &&  pQNode->qElemMemory.m_pBuf; pQNode = pQNode->pPrev ) {			
					    SP_OBJ  *  pSpObj  =  ( SP_OBJ * )( ( SP_SELECT_Q_ELEM * )pQNode->qElemMemory.m_pBuf )->pQNode->qElemMemory.m_pBuf;
						memset( &pSpObj->driver, 0, sizeof( pSpObj->driver ) );
						pSpObj->op = pSp->op;
						memcpy(  &pSpObj->opParm, &tmpOpParm, sizeof( SP_OP_PARM ) );
				   }

				   for  (  pQNode  =  pSp->pSpObjQ->front.pNext;  ;  )  {
					    for  (  ;  pQNode;  pQNode  =  pQNode->pNext  ) {
							 if ( preOpSpObj( pSp, pQNode , ( ( SP_OBJ * )pQNode->qElemMemory.m_pBuf )->op, &( ( SP_OBJ * )pQNode->qElemMemory.m_pBuf )->opParm, &( ( SP_OBJ * )pQNode->qElemMemory.m_pBuf )->driver, &parm ) ) {
								 traceLogA(  "preOpSp: preOpSpObj failed. objType %d",  (  (  SP_OBJ  *  )pQNode->qElemMemory.m_pBuf  )->type  );
								 goto  errLabel;
							 }
						}
						
						if  (  isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
						 
						SP_OPED_Q_ELEM				mem;
						unsigned  int				len	=	sizeof(  mem  );
						if  (  qGetMsg(  pSp->pOpedSpObjQ,  &mem,  &len  )  )  goto  errLabel;
						pQNode = mem.pQNode; 					

				   }
				
				   //  printQ( pSp->pSpObjQ );
											 
				   break;

			 case  OP_DELETE:

				   for ( pQNode = pSp->pSelectedSpObjQ->front.pNext; pQNode  &&  pQNode->qElemMemory.m_pBuf; pQNode = pQNode->pNext )  {
					   SP_OBJ  *  pSpObj  =  (  SP_OBJ  *  )(  (  SP_SELECT_Q_ELEM  *  )pQNode->qElemMemory.m_pBuf  )->pQNode->qElemMemory.m_pBuf;
					   pSpObj->op  =  OP_DELETE;
				   }

				   for  (  pQNode = pSp->pSpObjQ->front.pNext;  ;  )  {
					    for  (  ;  pQNode;  pQNode = pQNode->pNext  )  {							
							 if ( preOpSpObj( pSp, pQNode, (  (  SP_OBJ  *  )pQNode->qElemMemory.m_pBuf  )->op, NULL, NULL, NULL ) ) goto  errLabel;
						}

						if  (  isQEmpty(  pSp->pOpedSpObjQ  )  )  break;

						SP_OPED_Q_ELEM				mem;
						unsigned  int				len	=	sizeof(  mem  );
						if  (  qGetMsg(  pSp->pOpedSpObjQ,  &mem,  &len  )  )  goto  errLabel;
						pQNode = mem.pQNode; 					
				   }
		 
				   break;

			 case  OP_ANIMATE: {

				   int i;
				   SP_ANIMATOR *pSA;
			
				   pQNode = pSp->curpProcQNode;
				   pSA = ( SP_ANIMATOR * )pSp->curpProcQNode->qElemMemory.m_pBuf;
			
				   for  (  i = 0; pSA->sAP[i].pPointQNode && pSA->sAP[i].pPathQNode; i ++ ) {
					    if  (  preOpSpPoint( pSp, pSA->sAP[i].pPointQNode, pSp->op, NULL, NULL, &parm ) ) {
							spShowInfo( "point can't be moved freely" );
							goto  errLabel;
						}
				   }

				   for  (  i = 0; pSA->sAP[i].pPathQNode; i ++ )  {  
					    if ( preOpSpObj( pSp, pSA->sAP[i].pPathQNode, OP_PATH, NULL, NULL, &parm ) ) {
							spShowInfo( "path can't be moved during animation" );
							goto  errLabel;
						}			
				   }
		
				   }

				   break;

			 default:			
				    goto  errLabel;
					break;
	 }

	 iErr  =  0;

errLabel: 

	 if ( iErr ) {
		 for ( pQNode = pSp->pSpObjQ->front.pNext; pQNode; pQNode = pQNode->pNext )
			 ( ( SP_OBJ * )pQNode->qElemMemory.m_pBuf )->status = 0;
	 }

	 return iErr;

}


 /* pay attention here, flag is used to show the object is to selected manually, */
 /* or is processed because of relation */
 
 int  preOpSpObj( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm )
{
	 SP_OBJ	*	pSpObj	=	(  SP_OBJ  *  )pQNodeParm->qElemMemory.m_pBuf;
	 //  traceLogA(  "preOpSpObj: %S",  pSpObj->desc  );

	 switch  ( pSpObj->type ) {
			 case  SP_POINT_TYPE:
				   return  preOpSpPoint( pSp, pQNodeParm, op, pOpParm, pDriver, pParm );
			 case  SP_SEGMENT_TYPE:
				   return  preOpSpSegment( pSp, pQNodeParm, op, pOpParm, pDriver, pParm );			
			 case  SP_CIRCLE_TYPE:
				   return  preOpSpCircle( pSp, pQNodeParm, op, pOpParm, pDriver, pParm );			
			 case  SP_ANIMATOR_TYPE:
				   return  preOpSpAnimator( pSp, pQNodeParm, op, pOpParm, pDriver, pParm );
			 case  SP_RECTANGLE_TYPE:
				   return  preOpSpRectangle(  pSp,  pQNodeParm,  op,  pOpParm,  pDriver,  pParm  );
			 default:
				     break;
	 }

	 return  -1;

}


  int preOpSpPoint( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm )
{
	 
	 switch ( ( ( SP_POINT * )pQNodeParm->qElemMemory.m_pBuf )->subType ) {

		case SP_GENERIC_POINT_TYPE:

			return preOpSpGenericPoint( pSp, pQNodeParm, op, pOpParm, pDriver, pParm );

		case SP_POINT_ON_OBJ_TYPE:

			return preOpSpPointOnObj( pSp, pQNodeParm, op, pOpParm, pDriver, pParm );

		case SP_INTERSECT_POINT_TYPE: 
				
			return preOpSpIntersectPoint( pSp, pQNodeParm, op, pOpParm, pDriver, pParm );

		case SP_REFLECT_POINT_TYPE:

			return preOpSpReflectPoint( pSp, pQNodeParm, op, pOpParm, pDriver, pParm );

		case SP_ROTATE_POINT_TYPE:

			return preOpSpRotatePoint( pSp, pQNodeParm, op, pOpParm, pDriver, pParm );


		default:

			break;

	 }

	return -1;

}


 int preOpSpGenericPoint( SP_STRUCT *pSp, Q_NODE *pQNode, BYTE op,  SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm )
{
	 int				iErr			=	-1;
	 SP_POINT		*	pSpPoint		=	NULL;
	 SP_OP_PARM			tmpDriverOpParm;

	 pSpPoint  =  ( SP_POINT * )pQNode->qElemMemory.m_pBuf;
	 
	 switch  (  op  )  {
			 case  OP_NULL:
				   break;
			 case  OP_MOVE:

				   if  (  setSpObjOpMove( pSp,  pQNode, op, pOpParm, pDriver, pParm )  )  goto  errLabel;			
				
				   break;
			 case  OP_FIXED:
				   if ( getDriverOpParm( pSp, pDriver->pDriverQNode, &tmpDriverOpParm ) ) goto  errLabel;
				   
				   if  (  !CAN_OP_FIXED( pSpPoint, pDriver, OP_FIXED, NULL )  )  {
					   if ( !CAN_OP_MOVE( pSpPoint, pDriver, OP_MOVE, NULL ) ) goto  errLabel;
					   					
					   if ( CHECK_OP_MOVE( pSpPoint, pDriver, OP_MOVE, NULL ) )  goto  errLabel;
					   
					   if ( setSpObjOpMove( pSp,  pQNode, OP_MOVE, &tmpDriverOpParm, pDriver, pParm ) ) goto  errLabel;
					   
					   break;		
				   }

				   if  (  !CHECK_OP_FIXED( pSpPoint, pDriver, OP_FIXED, NULL )  )  {
					   if  (  setSpObjOpFixed( pQNode, OP_FIXED, NULL, pDriver, pParm  )  )  goto  errLabel;		
				   }
				   break;
			 case  OP_CONSTRAINTED_MOVE:
				   if ( getDriverOpParm( pSp, pDriver->pDriverQNode, &tmpDriverOpParm ) ) goto  errLabel;
				   
				   if  ( !CAN_OP_CONSTRAINTED_MOVE( pSpPoint, pDriver, op, pOpParm ) ) {
					   if ( !CAN_OP_MOVE( pSpPoint, pDriver, op, &tmpDriverOpParm ) ) goto  errLabel;
					   					
					   if ( CHECK_OP_MOVE( pSpPoint, pDriver, OP_MOVE, NULL ) )  goto  errLabel;
					   					
					   if ( setSpObjOpMove( pSp,  pQNode, OP_MOVE, &tmpDriverOpParm, pDriver, pParm ) ) goto  errLabel;
					   					
					   break;			
				   }

				   if  (  !CHECK_OP_CONSTRAINTED_MOVE( pSpPoint, pDriver, op, NULL ) ) { 
					   if  (  setSpObjOpConstraintedMove( pQNode, op, pOpParm, pDriver, pParm )  ) goto  errLabel;		
				   }
				   break;
			 case  OP_REFRESH_CONSTRAINTED_OP:
				   goto  errLabel;
				   break;
			 case  OP_DELETE:
				   break;
			 case  OP_ANIMATE:
				   goto  errLabel;
				   break;
			 default:
				    goto  errLabel;
					break;	 
	 }
	
	 iErr  =  0;
errLabel:
	 if  (  iErr  )  {
		 traceLogA(  "preOpSpGenericPoint failed"  );
	 }
	 return iErr;

}


 int preOpSpPointOnObj( SP_STRUCT *pSp, Q_NODE *pQNode, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm )
{
	 int iErr = 0;
	 SP_POINT_ON_OBJ *pSpPoint;

	 pSpPoint = ( SP_POINT_ON_OBJ * )pQNode->qElemMemory.m_pBuf;

	 switch ( op ) {

		case OP_NULL:

			break;

		case OP_MOVE:

			if ( !CHECK_OP_MOVE( pSpPoint, pDriver, op, NULL ) ) {
					if ( setSpObjOpMove( pSp,  pQNode, op, pOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
			}

			break;

		case OP_CONSTRAINTED_MOVE:

			if ( !CHECK_OP_CONSTRAINTED_MOVE( pSpPoint, pDriver, op, NULL ) ) {
					if ( setSpObjOpConstraintedMove( pQNode, op, pOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
			}
			
			break;

		case   OP_DELETE:

			if ( ( ( SP_OBJ * )pSpPoint->pObjQNode->qElemMemory.m_pBuf )->op == op )
				pSpPoint->op = OP_DELETE;
			
			break;

		case OP_ANIMATE:

			iErr = -1;			

			break;

		default:

			iErr = -1;

			break;

	 }
	
	 return iErr;

}



 int preOpSpIntersectPoint( SP_STRUCT *pSp, Q_NODE *pQNode, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm )
{
	 SP_INTERSECT_POINT *pSpPoint;
	 SP_OBJ *pSpObj1, *pSpObj2;
	 int iErr = 0;
	 
	 pSpPoint = ( SP_INTERSECT_POINT * )pQNode->qElemMemory.m_pBuf;
	 pSpObj1 = ( SP_OBJ * )pSpPoint->pQNode1->qElemMemory.m_pBuf;
	 pSpObj2 = ( SP_OBJ * )pSpPoint->pQNode2->qElemMemory.m_pBuf;

	 switch ( op ) {

		case OP_NULL:

			break;

		case OP_MOVE:

			if ( pSpObj1->op != op || pSpObj1->driver.pDriverQNode != pDriver->pDriverQNode ) {
				if ( preOpSpObj( pSp, pSpPoint->pQNode1, op, pOpParm, pDriver, pParm ) ) {
					iErr = -1; break;
				}
				//  if ( pParm->pQNode ) break;
				if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
			}
			if ( pSpObj2->op != op || pSpObj2->driver.pDriverQNode != pDriver->pDriverQNode ) {
				if ( preOpSpObj( pSp, pSpPoint->pQNode2, op, pOpParm, pDriver, pParm ) ) {
					iErr = -1; break;
				}
				//  if ( pParm->pQNode ) break;
				if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
			}

			if ( pSpPoint->op == OP_NULL ) {
					memcpy( &pSpPoint->driver, pDriver, sizeof( SP_DRIVER ) );
					pSpPoint->op = OP_MOVE;
					break;
			}

			if ( pSpPoint->driver.pDriverQNode != pDriver->pDriverQNode ) {
					iErr = -1; break;
			}

			if ( pSpPoint->op == op ) break;

			pSpPoint->op = op;

			//  pParm->pQNode = pQNode;			
			postToOpedQ(  pQNode,  pSp  );

			break;


		case OP_CONSTRAINTED_MOVE: {

			SP_DRIVER tmpDriver;

			tmpDriver.pDriverQNode = pDriver->pDriverQNode;
			tmpDriver.pConstraintQNode = pQNode;

			if ( pSpObj1->op != op || pSpObj1->driver.pDriverQNode != pDriver->pDriverQNode || pSpObj1->driver.pConstraintQNode != pQNode ) {

					if ( preOpSpObj( pSp, pSpPoint->pQNode1, op, pOpParm, &tmpDriver, pParm ) ) {
							iErr = -1; break;
					}

					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;

			}

			if ( pSpObj2->op != op || pSpObj2->driver.pDriverQNode != pDriver->pDriverQNode || pSpObj2->driver.pConstraintQNode != pQNode ) {

					if ( preOpSpObj( pSp, pSpPoint->pQNode2, op, pOpParm, &tmpDriver, pParm ) ) {
							iErr = -1; break;
					}

					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;

			}

			if ( pSpPoint->op == OP_NULL ) {

					pSpPoint->op = op;
					memcpy( &pSpPoint->driver, pDriver, sizeof( SP_DRIVER ) );
					break;

			}

			if ( pSpPoint->driver.pDriverQNode != pDriver->pDriverQNode ) {
					iErr = -1; break;
			}

			if ( pSpPoint->op == op && pSpPoint->driver.pConstraintQNode == pDriver->pConstraintQNode ) break;
					
			pSpPoint->op = OP_MOVE;

			//  pParm->pQNode = pQNode;
			postToOpedQ(  pQNode,  pSp  );

			}

			break;
		
		case OP_DELETE:

			if ( pSpObj1->op == op ) {
					pSpPoint->op = op; break;
			}

			if ( pSpObj2->op == op ) {
					pSpPoint->op = op; break;
			}
			
			break;

		case OP_ANIMATE:

			iErr = -1;

			break;

		default:

			iErr = -1;

	 }
	
	 return iErr;

}



 int preOpSpReflectPoint( SP_STRUCT *pSp, Q_NODE *pQNode, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm )
{
	 SP_REFLECT_POINT *pSpPoint;
	 SP_SEGMENT *pMirror;
	 SP_POINT *pReflectedSpPoint;
	 int iErr = 0;
	 SP_OP_PARM tmpOpParm, tmpDriverOpParm;
	 SP_RECT_COORD tmpPoint, tmpReflectedPoint;


	 pSpPoint = ( SP_REFLECT_POINT * )pQNode->qElemMemory.m_pBuf;
	 pMirror = ( SP_SEGMENT * )pSpPoint->pMirrorQNode->qElemMemory.m_pBuf;
	 pReflectedSpPoint = ( SP_POINT * )pSpPoint->pReflectedQNode->qElemMemory.m_pBuf;

	 switch ( op ) {

		case OP_NULL:

			break;

		case OP_MOVE:

			tmpPoint.x = pSpPoint->point.rect.x + pOpParm->move.x;
			tmpPoint.y = pSpPoint->point.rect.y + pOpParm->move.y;

			if ( getReflectPoint( pMirror, &tmpPoint, &tmpReflectedPoint ) ) {
					iErr = -1; break;
			}

			tmpOpParm.move.x = tmpReflectedPoint.x - pReflectedSpPoint->point.rect.x;
			tmpOpParm.move.y = tmpReflectedPoint.y - pReflectedSpPoint->point.rect.y;

			if ( !CAN_OP_FIXED( pMirror, pDriver, OP_FIXED, NULL )
				|| !CAN_OP_CONSTRAINTED_MOVE( pReflectedSpPoint, pDriver, OP_CONSTRAINTED_MOVE, &tmpOpParm ) ) {
					if ( !CAN_OP_MOVE( pMirror, pDriver, OP_MOVE, NULL ) ) {
							iErr = -1; break;
					}
					if ( !CHECK_OP_MOVE( pMirror, pDriver, OP_MOVE, NULL ) ) {
							if ( preOpSpSegment( pSp, pSpPoint->pMirrorQNode, OP_MOVE, pOpParm, pDriver, pParm ) ) {
									iErr = -1; break;
							}
							//  if ( pParm->pQNode ) break;
							if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
					}
					if ( !CAN_OP_MOVE( pReflectedSpPoint, pDriver, OP_MOVE, NULL ) ) {
							iErr = -1; break;
					}
					if ( !CHECK_OP_MOVE( pReflectedSpPoint, pDriver, OP_MOVE, NULL ) ) {
							if ( preOpSpPoint( pSp, pSpPoint->pReflectedQNode, OP_MOVE, pOpParm, pDriver, pParm ) ) {
									iErr = -1; break;
							}
							//  if ( pParm->pQNode ) break;
							if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
					}
					if ( !CAN_OP_MOVE( pSpPoint, pDriver, OP_MOVE, NULL ) ) {
							iErr = -1; break;
					}
					if ( !CHECK_OP_MOVE( pSpPoint, pDriver, OP_MOVE, NULL ) ) {
							if ( setSpObjOpMove( pSp,  pQNode, OP_MOVE, pOpParm, pDriver, pParm ) ) {
									iErr = -1; break;
							}
					}

					break;

			}

			if ( !CHECK_OP_FIXED( pMirror, pDriver, OP_FIXED, NULL ) ) {

					if ( preOpSpSegment( pSp, pSpPoint->pMirrorQNode, OP_FIXED, NULL, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;

			}



			if ( !CHECK_OP_CONSTRAINTED_MOVE( pReflectedSpPoint, pDriver, OP_CONSTRAINTED_MOVE, &tmpOpParm ) ) {
					
					if ( preOpSpPoint( pSp, pSpPoint->pReflectedQNode, OP_CONSTRAINTED_MOVE, &tmpOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
			}

			if ( !CHECK_OP_MOVE( pSpPoint, pDriver, OP_MOVE, NULL ) ) {
					if ( setSpObjOpMove( pSp,  pQNode, op, pOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					
			}
				
			break;

		case OP_FIXED:

			iErr = -1;
			break;


		case OP_CONSTRAINTED_MOVE:

			if ( getDriverOpParm( pSp, pDriver->pDriverQNode, &tmpDriverOpParm ) ) {
					return -1;
			}

			tmpPoint.x = pSpPoint->point.rect.x + pOpParm->move.x;
			tmpPoint.y = pSpPoint->point.rect.y + pOpParm->move.y;

			if ( getReflectPoint( pMirror, &tmpPoint, &tmpReflectedPoint ) ) {
					iErr = -1; break;
			}

			tmpOpParm.move.x = tmpReflectedPoint.x - pReflectedSpPoint->point.rect.x;
			tmpOpParm.move.y = tmpReflectedPoint.y - pReflectedSpPoint->point.rect.y;

			if ( !CAN_OP_FIXED( pMirror, pDriver, OP_FIXED, NULL )
				|| !CAN_OP_CONSTRAINTED_MOVE( pReflectedSpPoint, pDriver, OP_CONSTRAINTED_MOVE, &tmpOpParm )
				|| !CAN_OP_CONSTRAINTED_MOVE( pSpPoint, pDriver, OP_CONSTRAINTED_MOVE, pOpParm ) ) {
					if ( !CAN_OP_MOVE( pSpPoint, pDriver, OP_MOVE, NULL ) ) {
							iErr = -1; break;
					}
					if ( CHECK_OP_MOVE( pSpPoint, pDriver, OP_MOVE, NULL ) ) {
							iErr = -1; break;
					}
					if ( setSpObjOpMove( pSp,  pQNode, OP_MOVE, &tmpOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					//  if ( !pParm->pQNode ) pParm->pQNode = pQNode;
					postToOpedQ(  pQNode,  pSp  );					
					break;

			}

			if ( !CHECK_OP_FIXED( pMirror, pDriver, OP_FIXED, NULL ) ) {

					if ( preOpSpSegment( pSp, pSpPoint->pMirrorQNode, OP_FIXED, NULL, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;

			}



			if ( !CHECK_OP_CONSTRAINTED_MOVE( pReflectedSpPoint, pDriver, OP_CONSTRAINTED_MOVE, &tmpOpParm ) ) {
					
					if ( preOpSpPoint( pSp, pSpPoint->pReflectedQNode, OP_CONSTRAINTED_MOVE, &tmpOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
			}

			if ( !CHECK_OP_CONSTRAINTED_MOVE( pSpPoint, pDriver, OP_MOVE, pOpParm ) ) {
					if ( setSpObjOpConstraintedMove( pQNode, op, pOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					
			}
				
			break;


		default:

			iErr = -1;
			break;

	 }


	 return iErr;

}

 int preOpSpRotatePoint( SP_STRUCT *pSp, Q_NODE *pQNode, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm )
{
	 int iErr = 0;
	 SP_ROTATE_POINT *pSpPoint;
	 SP_POINT *pCenter;
	 SP_POINT *pRotatedSpPoint;
	 SP_OP_PARM tmpOpParm, tmpDriverOpParm;
	 SP_RECT_COORD tmpPoint, tmpRotatedPoint;

	 pSpPoint = ( SP_ROTATE_POINT * )pQNode->qElemMemory.m_pBuf;
	 pCenter = ( SP_POINT * )pSpPoint->pCenterQNode->qElemMemory.m_pBuf;
	 pRotatedSpPoint = ( SP_POINT * )pSpPoint->pRotatedQNode->qElemMemory.m_pBuf;

	 switch ( op ) {

		case OP_NULL:

			break;

		case OP_MOVE:

			tmpPoint.x = pSpPoint->point.rect.x + pOpParm->move.x;
			tmpPoint.y = pSpPoint->point.rect.y + pOpParm->move.y;

			if ( getRotatePoint( pCenter, &tmpPoint, &tmpRotatedPoint, ( short )-pSpPoint->A180 ) ) {
					iErr = -1; break;
			}

			tmpOpParm.move.x = tmpRotatedPoint.x - pRotatedSpPoint->point.rect.x;
			tmpOpParm.move.y = tmpRotatedPoint.y - pRotatedSpPoint->point.rect.y;

			if ( !CAN_OP_FIXED( pCenter, pDriver, OP_FIXED, NULL )
				|| !CAN_OP_CONSTRAINTED_MOVE( pRotatedSpPoint, pDriver, OP_CONSTRAINTED_MOVE, &tmpOpParm ) ) {
					if ( !CAN_OP_MOVE( pCenter, pDriver, OP_MOVE, NULL ) ) {
							iErr = -1; break;
					}
					if ( !CHECK_OP_MOVE( pCenter, pDriver, OP_MOVE, NULL ) ) {
							if ( preOpSpPoint( pSp, pSpPoint->pCenterQNode, OP_MOVE, pOpParm, pDriver, pParm ) ) {
									iErr = -1; break;
							}
							//  if ( pParm->pQNode ) break;
							if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
					}
					if ( !CAN_OP_MOVE( pRotatedSpPoint, pDriver, OP_MOVE, NULL ) ) {
							iErr = -1; break;
					}
					if ( !CHECK_OP_MOVE( pRotatedSpPoint, pDriver, OP_MOVE, NULL ) ) {
							if ( preOpSpPoint( pSp, pSpPoint->pRotatedQNode, OP_MOVE, pOpParm, pDriver, pParm ) ) {
									iErr = -1; break;
							}
							//  if ( pParm->pQNode ) break;
							if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
					}
					if ( !CAN_OP_MOVE( pSpPoint, pDriver, OP_MOVE, NULL ) ) {
							iErr = -1; break;
					}
					if ( !CHECK_OP_MOVE( pSpPoint, pDriver, OP_MOVE, NULL ) ) {
							if ( setSpObjOpMove(  pSp,  pQNode, OP_MOVE, pOpParm, pDriver, pParm ) ) {
									iErr = -1; break;
							}
					}

					break;

			}

			if ( !CHECK_OP_FIXED( pCenter, pDriver, OP_FIXED, NULL ) ) {

					if ( preOpSpPoint( pSp, pSpPoint->pCenterQNode, OP_FIXED, NULL, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;

			}

			if ( !CHECK_OP_CONSTRAINTED_MOVE( pRotatedSpPoint, pDriver, OP_CONSTRAINTED_MOVE, &tmpOpParm ) ) {
					
					if ( preOpSpPoint( pSp, pSpPoint->pRotatedQNode, OP_CONSTRAINTED_MOVE, &tmpOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
			}

			if ( !CHECK_OP_MOVE( pSpPoint, pDriver, OP_MOVE, NULL ) ) {
					if ( setSpObjOpMove(  pSp,  pQNode, op, pOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					
			}
				
			break;

		case OP_FIXED:

			iErr = -1; 
			
			break;

		case OP_CONSTRAINTED_MOVE: 

			if ( getDriverOpParm( pSp, pDriver->pDriverQNode, &tmpDriverOpParm ) ) {
					return -1;
			}

			tmpPoint.x = pSpPoint->point.rect.x + pOpParm->move.x;
			tmpPoint.y = pSpPoint->point.rect.y + pOpParm->move.y;

			if ( getRotatePoint( pCenter, &tmpPoint, &tmpRotatedPoint, ( short )-pSpPoint->A180 ) ) {
					iErr = -1; break;
			}

			tmpOpParm.move.x = tmpRotatedPoint.x - pRotatedSpPoint->point.rect.x;
			tmpOpParm.move.y = tmpRotatedPoint.y - pRotatedSpPoint->point.rect.y;

			if ( !CAN_OP_FIXED( pCenter, pDriver, OP_FIXED, NULL )
				|| !CAN_OP_CONSTRAINTED_MOVE( pRotatedSpPoint, pDriver, OP_CONSTRAINTED_MOVE, &tmpOpParm )
				|| !CAN_OP_CONSTRAINTED_MOVE( pSpPoint, pDriver, OP_CONSTRAINTED_MOVE, pOpParm ) ) {
					if ( !CAN_OP_MOVE( pSpPoint, pDriver, OP_MOVE, NULL ) ) {
							iErr = -1; break;
					}
					if ( CHECK_OP_MOVE( pSpPoint, pDriver, OP_MOVE, NULL ) ) {
							iErr = -1; break;
					}
					if ( setSpObjOpMove(  pSp,  pQNode, OP_MOVE, &tmpOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}

					//  if ( !pParm->pQNode ) pParm->pQNode = pQNode;
					postToOpedQ(  pQNode,  pSp  );
					
					break;

			}

			if ( !CHECK_OP_FIXED( pCenter, pDriver, OP_FIXED, NULL ) ) {

					if ( preOpSpPoint( pSp, pSpPoint->pCenterQNode, OP_FIXED, NULL, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;

			}

			if ( !CHECK_OP_CONSTRAINTED_MOVE( pRotatedSpPoint, pDriver, OP_CONSTRAINTED_MOVE, &tmpOpParm ) ) {
					
					if ( preOpSpPoint( pSp, pSpPoint->pRotatedQNode, OP_CONSTRAINTED_MOVE, &tmpOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
			}

			if ( !CHECK_OP_CONSTRAINTED_MOVE( pSpPoint, pDriver, OP_MOVE, pOpParm ) ) {
					if ( setSpObjOpConstraintedMove( pQNode, op, pOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					
			}
				
			break;


		default:

			iErr = -1;

			break;

		}


	 return iErr;

}


 


 int preOpSpSegment( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm )
{
	 int	iErr		=	-1;
	 BYTE	subType;						

	 subType  =  ( ( SP_SEGMENT * )pQNodeParm->qElemMemory.m_pBuf )->subType;

	 switch  (  subType ) {
		
			 case  SP_GENERIC_SEGMENT_TYPE:
				   return  preOpSpGenericSegment( pSp, pQNodeParm, op, pOpParm, pDriver, pParm );
				   break;

			 case  SP_LINE_TYPE:
				   return  preOpSpLine( pSp, pQNodeParm, op, pOpParm, pDriver, pParm );
				   break;

			 case  SP_PERPENDICULAR_LINE_TYPE:
				   return  preOpSpPerpendicularLine( pSp, pQNodeParm, op, pOpParm, pDriver, pParm );
				   break;

			 case  SP_REFLECT_SEGMENT_TYPE:
				   return  preOpSpReflectSegment( pSp, pQNodeParm, op, pOpParm, pDriver, pParm );
				   break;

			 case  SP_REFLECT_LINE_TYPE:
				   return  preOpSpReflectLine( pSp, pQNodeParm, op, pOpParm, pDriver, pParm );
				   break;
			 default:
  				     traceLogA(  "Not finished: preOpSpSegment: subType %d",  (  int  )subType  );
				     goto  errLabel;
					 break;
	 }

errLabel:
	 return iErr;

}


 int preOpSpGenericSegment( SP_STRUCT *pSp, Q_NODE *pQNode, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm )
{
	 int				iErr				=	-1;
	 SP_SEGMENT		*	pSpSegment			=	NULL;
	 SP_POINT		*	pSpObj1				=	NULL;
	 SP_POINT		*	pSpObj2				=	NULL;
	 SP_OP_PARM			tmpDriverOpParm;

	 pSpSegment = ( SP_SEGMENT * )pQNode->qElemMemory.m_pBuf;
	 if  (  pSpSegment->type  !=  SP_SEGMENT_TYPE  ||  pSpSegment->subType  !=  SP_GENERIC_SEGMENT_TYPE  )  return  -1;
	 pSpObj1 = ( SP_POINT * )pSpSegment->pStartQNode->qElemMemory.m_pBuf;
	 pSpObj2 = ( SP_POINT * )pSpSegment->pEndQNode->qElemMemory.m_pBuf;

	 switch  (  op  )  {

			 case  OP_NULL:
				   if  (  pSpObj1->op  ==  OP_DELETE  ||  pSpObj2->op  ==  OP_DELETE  )  {			
					   if  (  pSpSegment->bOwner_pStartQNode  &&  pSpObj1->op  !=  OP_DELETE  )  {
						   pSpObj1->op  =  OP_DELETE;
						   if  (  postToOpedQ(  pSpSegment->pStartQNode,  pSp  )  )  goto  errLabel;
					   }
					   if  (  pSpSegment->bOwner_pEndQNode  &&  pSpObj2->op  !=  OP_DELETE  )  {
						   pSpObj2->op  =  OP_DELETE;
						   if  (  postToOpedQ(  pSpSegment->pEndQNode,  pSp  )  )  goto  errLabel;
					   }
					   pSpSegment->op  =  OP_DELETE;
					   if  (  postToOpedQ(  pQNode,  pSp  )  )  goto  errLabel;				
					   break;
				   }
				   if  (  pSpObj1->op  ==  OP_MOVE  ||  pSpObj2->op  ==  OP_MOVE  )  {			
					   if  (  pSpSegment->ucbHorizontal  )  {
						   BOOL	 bDetermined_y1	=	FALSE;
						   BOOL  bDetermined_y2 =	FALSE;
						   int  y1  =  pSpObj1->point.rect.y;
						   int  y2  =  pSpObj2->point.rect.y;

						   if  (  pSpObj1->op  ==  OP_MOVE  &&  (  pSpObj1->opParm.iFlg  &  CONST_opFlg_y  )  )  {
							   y1  +=  pSpObj1->opParm.move.y;
							   bDetermined_y1  =  TRUE;
						   }
						   if  (  pSpObj2->op  ==  OP_MOVE  &&  (  pSpObj2->opParm.iFlg  &  CONST_opFlg_y  )  )  {
							   y2  +=  pSpObj2->opParm.move.y;
							   bDetermined_y2  =  TRUE;
						   }
						   if  (  y1  !=  y2  )  {
							   if  (  bDetermined_y1  &&  bDetermined_y2  )  goto  errLabel;

							   //
							   memset(  &tmpDriverOpParm,  0,  sizeof(  tmpDriverOpParm  )  );
							   tmpDriverOpParm.iFlg  =  CONST_opFlg_y;  
							   
							   if  (  bDetermined_y2  )  {
								   tmpDriverOpParm.move.y  =  y2  -  y1;
								   if  (  preOpSpPoint(  pSp,  pSpSegment->pStartQNode,  OP_MOVE,  &tmpDriverOpParm,  pDriver,  pParm  )  )  {
									   traceLogA(  "preOpSpGenericSegment.preOpSpPoint failed. horizoltal, spObj1"  );
									   goto  errLabel;		
								   }						
							   }
							   if  (  bDetermined_y1  )  {
								   tmpDriverOpParm.move.y  =  y1  -  y2;
								   if  (  preOpSpPoint(  pSp,  pSpSegment->pEndQNode,  OP_MOVE,  &tmpDriverOpParm,  pDriver,  pParm  )  )  {									
									   traceLogA(  "preOpSpGenericSegment.preOpSpPoint failed. horizoltal, spObj2"  );									
									   goto  errLabel;
								   }
							   }
						   }
							}
					   else  if  (  pSpSegment->ucbVertical  )  {
								 BOOL  bDetermined_x1	=	FALSE;
								 BOOL  bDetermined_x2	=	FALSE;
								 int  x1  =  pSpObj1->point.rect.x;
								 int  x2  =  pSpObj2->point.rect.x;

								 if  (  pSpObj1->op  ==  OP_MOVE  &&  (  pSpObj1->opParm.iFlg  &  CONST_opFlg_x  )  )  {
									 x1  +=  pSpObj1->opParm.move.x;
									 bDetermined_x1  =  TRUE;
								 }
								 if  (  pSpObj2->op  ==  OP_MOVE  &&  (  pSpObj2->opParm.iFlg  &  CONST_opFlg_x  )  )  {
									 x2  +=  pSpObj2->opParm.move.x;
									 bDetermined_x2  =  TRUE;
								 }
								 if  (  x1  !=  x2  )  {
									 if  (  bDetermined_x1  &&  bDetermined_x2  )  goto  errLabel;

									 memset(  &tmpDriverOpParm,  0,  sizeof(  tmpDriverOpParm  )  );
									 tmpDriverOpParm.iFlg  =  CONST_opFlg_x;
									 if  (  bDetermined_x2  )  {
										 tmpDriverOpParm.move.x  =  x2  -  x1;
										 if  (  preOpSpPoint(  pSp,  pSpSegment->pStartQNode,  OP_MOVE,  &tmpDriverOpParm,  pDriver,  pParm  )  )  {
											 traceLogA(  "preOpSpGenericSegment.preOpSpPoint failed. vertical, spObj1"  );
											 goto  errLabel;							
										 }
									 }
									 if  (  bDetermined_x1  )  {
										 tmpDriverOpParm.move.x  =  x1  -  x2;
										 if  (  preOpSpPoint(  pSp,  pSpSegment->pEndQNode,  OP_MOVE,  &tmpDriverOpParm,  pDriver,  pParm  )  )  {
											 traceLogA(  "preSpGenericSegment.preOpSpPoint failed. vertical, spObj2"  );
											 goto  errLabel;
										 }
									 }						   
								 }					   
					   }
					   break;
				   }
				   break;
			 case  OP_MOVE:
			       if  (  !CAN_OP_MOVE( pSpObj1, pDriver, OP_MOVE, pOpParm  )  )  goto  errLabel;				   
				   if  (  !CHECK_OP_MOVE( pSpObj1, pDriver, op, NULL )  )  {
					   if ( preOpSpPoint( pSp, pSpSegment->pStartQNode, op, pOpParm, pDriver, pParm ) ) goto  errLabel;
				   }			
				   if  (  !CAN_OP_MOVE( pSpObj2, pDriver, OP_MOVE, pOpParm ) ) goto  errLabel;	
				   if  (  !CHECK_OP_MOVE( pSpObj2, pDriver, op, NULL )  )  {
					   if ( preOpSpPoint( pSp, pSpSegment->pEndQNode, op, pOpParm, pDriver, pParm ) )  goto  errLabel;					   
				   }
				   //
				   pSpSegment->op  =  OP_NULL;
				   break;

			 case  OP_FIXED:
				   if  (  getDriverOpParm( pSp, pDriver->pDriverQNode, &tmpDriverOpParm ) ) goto  errLabel;
				   
				   if ( !CAN_OP_FIXED( pSpObj1, pDriver, OP_FIXED, NULL ) 
					   || !CAN_OP_FIXED( pSpObj2, pDriver, OP_FIXED, NULL )
						   || !CAN_OP_FIXED( pSpSegment, pDriver, OP_FIXED, NULL ) ) 
				   {			
					   if  (  !CAN_OP_MOVE( pSpSegment, pDriver, OP_MOVE, &tmpDriverOpParm ) )  goto  errLabel;
					   					
					   if  (  CHECK_OP_MOVE( pSpSegment, pDriver, OP_MOVE, NULL ) )  goto  errLabel;
					   					
					   if ( setSpObjOpMove(  pSp,  pQNode, OP_MOVE, &tmpDriverOpParm, pDriver, pParm ) )  goto  errLabel;
				
					   //  if ( !pParm->pQNode ) pParm->pQNode = pQNode;
					   postToOpedQ(  pQNode,  pSp  );

					   break;
				   }
			
				   if  (  !CHECK_OP_FIXED( pSpObj1, pDriver, OP_FIXED, NULL )  )  {
					   if ( preOpSpObj( pSp, pSpSegment->pStartQNode, op, pOpParm, pDriver, pParm ) )  goto  errLabel;					
					   //  if ( pParm->pQNode ) break;			
					   if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
				   }
				   if  (  !CHECK_OP_FIXED( pSpObj2, pDriver, OP_FIXED, NULL )  )  {
					   if ( preOpSpObj( pSp, pSpSegment->pEndQNode, op, pOpParm, pDriver, pParm ) )  goto  errLabel; 				
					   //  if ( pParm->pQNode ) break;			
					   if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
				   }
				   if  (  !CHECK_OP_FIXED( pSpSegment, pDriver, op, NULL )  )  {
					   if ( setSpObjOpFixed( pQNode, op, pOpParm, pDriver, pParm ) )  goto  errLabel;		
				   }			
				   break;
			 case  OP_CONSTRAINTED_MOVE: 
				   if ( getDriverOpParm( pSp, pDriver->pDriverQNode, &tmpDriverOpParm ) ) goto  errLabel;
				   
				   if ( !CAN_OP_CONSTRAINTED_MOVE( pSpObj1, pDriver, OP_CONSTRAINTED_MOVE, pOpParm ) 
					   || !CAN_OP_CONSTRAINTED_MOVE( pSpObj2, pDriver, OP_CONSTRAINTED_MOVE, pOpParm ) 
						   || !CAN_OP_CONSTRAINTED_MOVE( pSpSegment, pDriver, OP_CONSTRAINTED_MOVE, pOpParm ) ) 
				   {			
					   if ( !CAN_OP_MOVE( pSpSegment, pDriver, OP_MOVE, pOpParm ) ) goto  errLabel;
					   					
					   if ( CHECK_OP_MOVE( pSpSegment, pDriver, OP_MOVE, NULL ) ) goto  errLabel;
					   					
					   if ( setSpObjOpMove(  pSp,  pQNode, OP_MOVE, &tmpDriverOpParm, pDriver, pParm ) ) goto  errLabel;
					   
					   //  if ( !pParm->pQNode ) pParm->pQNode = pQNode;
					   postToOpedQ(  pQNode,  pSp  );
					
					   break;
				   }
								
				   if ( !CHECK_OP_CONSTRAINTED_MOVE( pSpObj1, pDriver, OP_CONSTRAINTED_MOVE, NULL ) ) {
					   if ( preOpSpObj( pSp, pSpSegment->pStartQNode, OP_CONSTRAINTED_MOVE, pOpParm, pDriver, pParm ) ) goto  errLabel;
					   //  if ( pParm->pQNode ) break;			
					   if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
				   }
				   if ( !CHECK_OP_CONSTRAINTED_MOVE( pSpObj2, pDriver, OP_CONSTRAINTED_MOVE, NULL ) ) {
					   if ( preOpSpObj( pSp, pSpSegment->pEndQNode, OP_CONSTRAINTED_MOVE, pOpParm, pDriver, pParm ) ) goto  errLabel;					   
					   //  if ( pParm->pQNode ) break;								   					   
					   if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
				   }
				   if ( !CHECK_OP_CONSTRAINTED_MOVE( pSpSegment, pDriver, op, NULL ) ) {
					   if ( setSpObjOpConstraintedMove( pQNode, op, pOpParm, pDriver, pParm ) ) goto  errLabel;			
				   }
					
				   break;		
			 case  OP_DELETE:
				   if  (  pSpSegment->bOwner_pStartQNode  &&  pSpObj1->op  !=  OP_DELETE  )  {
					   pSpObj1->op  =  OP_DELETE;
					   if  (  postToOpedQ(  pSpSegment->pStartQNode,  pSp  )  )  goto  errLabel;
				   }
				   if  (  pSpSegment->bOwner_pEndQNode  &&  pSpObj2->op  !=  OP_DELETE  )  {
					   pSpObj2->op  =  OP_DELETE;
					   if  (  postToOpedQ(  pSpSegment->pEndQNode,  pSp  )  )  goto  errLabel;
				   }
				   if  (  pSpSegment->op  !=  OP_DELETE  )  {
					   pSpSegment->op  =  OP_DELETE;
					   if  (  postToOpedQ(  pQNode,  pSp  )  )  goto  errLabel;				
				   }
				   break;

			 case  OP_PATH:
				   goto  errLabel;
				   break;

			 default:
					goto  errLabel;
					break;	 
	 }

	 iErr  =  0;
errLabel:

	 if  (  iErr  )  {
		 traceLogA(  "preOpSpGenericSegment failed."  );
	 }

	 return iErr;
}


 int preOpSpLine( SP_STRUCT *pSp, Q_NODE *pQNode, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm )
{
	 int iErr = 0;
	 SP_LINE *pSpLine;
	 SP_OBJ *pSpObj1, *pSpObj2;

	 pSpLine = ( SP_LINE * )pQNode->qElemMemory.m_pBuf;
	 pSpObj1 = ( SP_OBJ * )pSpLine->pQNode1->qElemMemory.m_pBuf; 
	 pSpObj2 = ( SP_OBJ * )pSpLine->pQNode2->qElemMemory.m_pBuf; 
	 
	 switch ( op ) {

		case OP_NULL:

			break;
		
		case OP_MOVE:
			
			if ( pDriver->pDriverQNode != pSpObj1->driver.pDriverQNode || pSpObj1->op != op ) {
					if ( preOpSpPoint( pSp, pSpLine->pQNode1, op, pOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
			}
			if ( pDriver->pDriverQNode != pSpObj2->driver.pDriverQNode || pSpObj2->op != op ) {
					if ( preOpSpPoint( pSp, pSpLine->pQNode2, op, pOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
			}

			if ( pSpLine->op == OP_NULL ) {
					memcpy( &pSpLine->driver, pDriver, sizeof( SP_DRIVER ) );
					pSpLine->op = op;
					break;
			}

			if ( pSpLine->driver.pDriverQNode != pDriver->pDriverQNode ) {
					iErr = -1; break;
			}

			if ( pSpLine->op == op ) break;

			pSpLine->op = OP_MOVE;

			//  pParm->pQNode = pQNode;
			postToOpedQ(  pQNode,  pSp  );
			
			break;

		case OP_CONSTRAINTED_MOVE: {

			SP_DRIVER tmpDriver;

			tmpDriver.pDriverQNode = pDriver->pDriverQNode;
			tmpDriver.pConstraintQNode = pQNode;

			if ( pDriver->pDriverQNode != pSpObj1->driver.pDriverQNode || pQNode != pSpObj1->driver.pConstraintQNode || pSpObj1->op != op ) {
					if ( preOpSpPoint( pSp, pSpLine->pQNode1, op, pOpParm, &tmpDriver, pParm ) ) {
							iErr = -1; break;
					}
					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
			}
			if ( pDriver->pDriverQNode != pSpObj2->driver.pDriverQNode || pQNode != pSpObj2->driver.pConstraintQNode || pSpObj2->op != op ) {
					if ( preOpSpPoint( pSp, pSpLine->pQNode2, op, pOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
			}

			if ( pSpLine->op == OP_NULL ) {
					pSpLine->op = op;
					memcpy( &pSpLine->driver, pDriver, sizeof( SP_DRIVER ) );
					break;
			}

			if ( pSpLine->driver.pDriverQNode != pDriver->pDriverQNode ) {
					iErr = -1; break;
			}

			if ( pSpLine->op == op && pSpLine->driver.pConstraintQNode == pDriver->pConstraintQNode ) break;

			pSpLine->op = OP_MOVE;

			//  pParm->pQNode = pQNode;
			postToOpedQ(  pQNode,  pSp  );
			
			}

			break;		

		case OP_DELETE:

			if ( pSpObj1->op == OP_DELETE || pSpObj2->op == OP_DELETE ) {
					pSpLine->op = OP_DELETE;
			}

			break;

		case OP_PATH:

			iErr = -1;

			break;

		default:

			iErr = -1;

			break;
	 
	 }

	 return iErr;



}



 int preOpSpPerpendicularLine( SP_STRUCT *pSp, Q_NODE *pQNode, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm )
{
	 int iErr = 0;
	 SP_PERPENDICULAR_LINE *pSPL;
	 SP_OBJ *pSpObj1;

	 pSPL = ( SP_PERPENDICULAR_LINE * )pQNode->qElemMemory.m_pBuf;
	 pSpObj1 = ( SP_OBJ * )pSPL->pSpPointQNode->qElemMemory.m_pBuf;


	 switch ( op ) {

		case OP_NULL:

			break;
		
		case OP_MOVE:
			
			if ( pSpObj1->driver.pDriverQNode != pDriver->pDriverQNode || pSpObj1->op != op ) {
					if ( preOpSpPoint( pSp, pSPL->pSpPointQNode, op, pOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
			}
			
			if ( pSPL->op == OP_NULL ) {
					memcpy( &pSPL->driver, pDriver, sizeof( SP_DRIVER ) );
					pSPL->op = op;
					break;
			}

			if ( pDriver->pDriverQNode != pSPL->driver.pDriverQNode ) {
					iErr = -1; break;
			}

			if ( pSPL->op == op ) break;
			
			pSPL->op = OP_MOVE;

			//  pParm->pQNode = pQNode;
			postToOpedQ(  pQNode,  pSp  );
			
			break;

		case OP_CONSTRAINTED_MOVE: {

			SP_DRIVER tmpDriver;

			tmpDriver.pDriverQNode = pDriver->pDriverQNode;
			tmpDriver.pConstraintQNode = pQNode;

			if ( pSpObj1->driver.pDriverQNode != pDriver->pDriverQNode || pSpObj1->driver.pConstraintQNode != pDriver->pConstraintQNode || pSpObj1->op != op ) {
					if ( preOpSpPoint( pSp, pSPL->pSpPointQNode, op, pOpParm, &tmpDriver, pParm ) ) {
							iErr = -1; break;
					}
					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
			}
			
			if ( pSPL->op == OP_NULL ) {
					memcpy( &pSPL->driver, pDriver, sizeof( SP_DRIVER ) );
					pSPL->op = op;
					break;
			}

			if ( pDriver->pDriverQNode != pSPL->driver.pDriverQNode ) {
					iErr = -1; break;
			}

			if ( pSPL->op == op && pSPL->driver.pConstraintQNode != pDriver->pConstraintQNode ) break;
			
			pSPL->op = OP_MOVE;

			//  pParm->pQNode = pQNode;
			postToOpedQ(  pQNode,  pSp  );

			}
			
			break;
	
		case OP_DELETE:

			if ( ( ( SP_POINT * )pSPL->pSpPointQNode->qElemMemory.m_pBuf )->op == OP_DELETE
				|| ( ( SP_POINT * )pSPL->pSpSegmentQNode->qElemMemory.m_pBuf )->op == OP_DELETE ) {
					pSPL->op = OP_DELETE;	
			}

			break;

		case OP_PATH:

			iErr = -1;

			break;

		default:

			iErr = -1;

			break;
	 
	 }

	 return iErr;


}

 int preOpSpReflectSegment( SP_STRUCT *pSp, Q_NODE *pQNode, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm )
{
 	 int iErr = 0;
	 SP_REFLECT_SEGMENT *pSpSegment;
	 SP_SEGMENT *pMirror;
	 SP_SEGMENT *pReflectedSpSegment;
	 SP_RECT_COORD tmpPoint, tmpReflectedPoint;
	 SP_OP_PARM tmpOpParm, tmpDriverOpParm;

	 pSpSegment = ( SP_REFLECT_SEGMENT * )pQNode->qElemMemory.m_pBuf;
	 pMirror = ( SP_SEGMENT * )pSpSegment->pMirrorQNode->qElemMemory.m_pBuf;
	 pReflectedSpSegment = ( SP_SEGMENT * )pSpSegment->pReflectedQNode->qElemMemory.m_pBuf;

	 switch ( op ) {

		case OP_NULL:

			break;

		case OP_MOVE:

			tmpPoint.x = pSpSegment->point1.rect.x + pOpParm->move.x;
			tmpPoint.y = pSpSegment->point1.rect.y + pOpParm->move.y;

			if ( getReflectPoint( pMirror, &tmpPoint, &tmpReflectedPoint ) ) {
					iErr = -1; break;
			}

			tmpOpParm.move.x = tmpReflectedPoint.x - pReflectedSpSegment->point1.rect.x;
			tmpOpParm.move.y = tmpReflectedPoint.y - pReflectedSpSegment->point1.rect.y;

			if ( !CAN_OP_FIXED( pMirror, pDriver, OP_FIXED, NULL )
				|| !CAN_OP_CONSTRAINTED_MOVE( pReflectedSpSegment, pDriver, OP_CONSTRAINTED_MOVE, &tmpOpParm ) ) {
					if ( !CAN_OP_MOVE( pMirror, pDriver, OP_MOVE, NULL ) ) {
							iErr = -1; break;
					}
					if ( !CHECK_OP_MOVE( pMirror, pDriver, OP_MOVE, NULL ) ) {
							if ( preOpSpSegment( pSp, pSpSegment->pMirrorQNode, OP_MOVE, pOpParm, pDriver, pParm ) ) {
									iErr = -1; break;
							}
							//  if ( pParm->pQNode ) break;
							if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
					}
					if ( !CAN_OP_MOVE( pReflectedSpSegment, pDriver, OP_MOVE, NULL ) ) {
							iErr = -1; break;
					}
					if ( !CHECK_OP_MOVE( pReflectedSpSegment, pDriver, OP_MOVE, NULL ) ) {
							if ( preOpSpObj( pSp, pSpSegment->pReflectedQNode, OP_MOVE, pOpParm, pDriver, pParm ) ) {
									iErr = -1; break;
							}
							//  if ( pParm->pQNode ) break;
							if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
					}
					if ( !CAN_OP_MOVE( pSpSegment, pDriver, OP_MOVE, NULL ) ) {
							iErr = -1; break;
					}
					if ( !CHECK_OP_MOVE( pSpSegment, pDriver, OP_MOVE, NULL ) ) {
							if ( setSpObjOpMove(  pSp,  pQNode, OP_MOVE, pOpParm, pDriver, pParm ) ) {
									iErr = -1; break;
							}
					}

					break;

			}

			if ( !CHECK_OP_FIXED( pMirror, pDriver, OP_FIXED, NULL ) ) {

					if ( preOpSpSegment( pSp, pSpSegment->pMirrorQNode, OP_FIXED, NULL, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
			}

			if ( !CHECK_OP_CONSTRAINTED_MOVE( pReflectedSpSegment, pDriver, OP_CONSTRAINTED_MOVE, &tmpOpParm ) ) {
					
					if ( preOpSpSegment( pSp, pSpSegment->pReflectedQNode, OP_CONSTRAINTED_MOVE, &tmpOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
			}

			if ( !CHECK_OP_MOVE( pSpSegment, pDriver, OP_MOVE, NULL ) ) {
					if ( setSpObjOpMove(  pSp,  pQNode, op, pOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					
			}
				
			break;

		case OP_FIXED:

			if ( getDriverOpParm( pSp, pDriver->pDriverQNode, &tmpDriverOpParm ) ) {
					return -1;
			}

			if ( !CAN_OP_FIXED( pMirror, pDriver, OP_FIXED, NULL ) 
				|| !CAN_OP_FIXED( pReflectedSpSegment, pDriver, OP_FIXED, NULL )
				|| !CAN_OP_FIXED( pSpSegment, pDriver, OP_FIXED, NULL ) ) {
					if ( !CAN_OP_MOVE( pSpSegment, pDriver, OP_MOVE, &tmpDriverOpParm ) ) {
							iErr = -1; break;
					}
					if ( CHECK_OP_MOVE( pSpSegment, pDriver, OP_MOVE, NULL ) ) {
							iErr = -1; break;
					}
					if ( setSpObjOpMove(  pSp,  pQNode, OP_MOVE, &tmpDriverOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					//  if ( !pParm->pQNode ) pParm->pQNode = pQNode;
					postToOpedQ(  pQNode,  pSp  );

					break;
			}
			
			if ( !CHECK_OP_FIXED( pMirror, pDriver, OP_FIXED, NULL ) ) {
					if ( preOpSpObj( pSp, pSpSegment->pMirrorQNode, op, pOpParm, pDriver, pParm ) ) {
									iErr = -1; break;
					}
					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
			}
			if ( !CHECK_OP_FIXED( pReflectedSpSegment, pDriver, OP_FIXED, NULL ) ) {
					if ( preOpSpObj( pSp, pSpSegment->pReflectedQNode, op, pOpParm, pDriver, pParm ) ) {
									iErr = -1; break;
					}
					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
			}
			if ( !CHECK_OP_FIXED( pSpSegment, pDriver, op, NULL ) ) {
					if ( setSpObjOpFixed( pQNode, op, pOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
			}
			
			break;

		case OP_CONSTRAINTED_MOVE: 

			if ( getDriverOpParm( pSp, pDriver->pDriverQNode, &tmpDriverOpParm ) ) {
					return -1;
			}

			tmpPoint.x = pSpSegment->point1.rect.x + pOpParm->move.x;
			tmpPoint.y = pSpSegment->point1.rect.y + pOpParm->move.y;

			if ( getReflectPoint( pMirror, &tmpPoint, &tmpReflectedPoint ) ) {
					iErr = -1; break;
			}

			tmpOpParm.move.x = tmpReflectedPoint.x - pReflectedSpSegment->point1.rect.x;
			tmpOpParm.move.y = tmpReflectedPoint.y - pReflectedSpSegment->point1.rect.y;

			if ( !CAN_OP_FIXED( pMirror, pDriver, OP_FIXED, NULL )
				|| !CAN_OP_CONSTRAINTED_MOVE( pReflectedSpSegment, pDriver, OP_CONSTRAINTED_MOVE, &tmpOpParm )
				|| !CAN_OP_CONSTRAINTED_MOVE( pSpSegment, pDriver, OP_CONSTRAINTED_MOVE, pOpParm ) ) {
					if ( !CAN_OP_MOVE( pSpSegment, pDriver, OP_MOVE, NULL ) ) {
							iErr = -1; break;
					}
					if ( CHECK_OP_MOVE( pSpSegment, pDriver, OP_MOVE, NULL ) ) {
							iErr = -1; break;
					}
					if ( setSpObjOpMove(  pSp,  pQNode, OP_MOVE, &tmpDriverOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					//  if ( !pParm->pQNode ) pParm->pQNode = pQNode;
					postToOpedQ(  pQNode,  pSp  );
					
					break;

			}

			if ( !CHECK_OP_FIXED( pMirror, pDriver, OP_FIXED, NULL ) ) {

					if ( preOpSpSegment( pSp, pSpSegment->pMirrorQNode, OP_FIXED, NULL, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
			}


			if ( !CHECK_OP_CONSTRAINTED_MOVE( pReflectedSpSegment, pDriver, OP_CONSTRAINTED_MOVE, &tmpOpParm ) ) {
					
					if ( preOpSpObj( pSp, pSpSegment->pReflectedQNode, OP_CONSTRAINTED_MOVE, &tmpOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					//  if ( pParm->pQNode ) break;
					if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;
			}

			if ( !CHECK_OP_CONSTRAINTED_MOVE( pSpSegment, pDriver, OP_MOVE, pOpParm ) ) {
					if ( setSpObjOpConstraintedMove( pQNode, op, pOpParm, pDriver, pParm ) ) {
							iErr = -1; break;
					}
					
			}
				
			break;
		
		case OP_DELETE:

			if ( pMirror->op == OP_DELETE || pReflectedSpSegment->op == OP_DELETE )
					pSpSegment->op = OP_DELETE;
			break;

		case OP_PATH:

			iErr = -1;
			
			break;

		default:

			iErr = -1;

			break;
	 
	 }

	 return iErr;


}


 int preOpSpReflectLine( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm )
{

	 return 0;

}


 int preOpSpCircle( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm )
{
	 int iErr = 0;
	 SP_CIRCLE *pSpCircle;

	 pSpCircle = ( SP_CIRCLE * )pQNodeParm->qElemMemory.m_pBuf;

	 switch ( pSpCircle->subType ) {

		case SP_GENERIC_CIRCLE_TYPE:

			iErr = preOpSpGenericCircle( pSp, pQNodeParm, op, pOpParm, pDriver, pParm );

			break;

		default:

			iErr = -1;
			break;

	 }

	 return iErr;

}


 int  preOpSpGenericCircle( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm )
{
	 int				iErr		=		-1;
	 SP_CIRCLE		*	pSpCircle	=		NULL;
	 SP_POINT		*	pSpObj1				=	NULL;
	 SP_POINT		*	pSpObj2				=	NULL;

	 pSpCircle  =  ( SP_CIRCLE * )pQNodeParm->qElemMemory.m_pBuf;
	 if  (  pSpCircle->type  !=  SP_CIRCLE_TYPE  ||  pSpCircle->subType  !=  SP_GENERIC_CIRCLE_TYPE  )  return  -1;
	 pSpObj1 = ( SP_POINT * )pSpCircle->pCenterQNode->qElemMemory.m_pBuf;
	 pSpObj2 = ( SP_POINT * )pSpCircle->pCircleQNode->qElemMemory.m_pBuf;

	 switch  (  op  )  {
			 case  OP_NULL:
				   if  (  pSpObj1->op  ==  OP_DELETE  ||  pSpObj2->op  ==  OP_DELETE  )  {			
					   if  (  pSpCircle->bOwner_pCenterQNode  &&  pSpObj1->op  !=  OP_DELETE  )  {
						   pSpObj1->op  =  OP_DELETE;
						   if  (  postToOpedQ(  pSpCircle->pCenterQNode,  pSp  )  )  goto  errLabel;
					   }
					   if  (  pSpCircle->bOwner_pCircleQNode  &&  pSpObj2->op  !=  OP_DELETE  )  {
						   pSpObj2->op  =  OP_DELETE;
						   if  (  postToOpedQ(  pSpCircle->pCircleQNode,  pSp  )  )  goto  errLabel;
					   }
					   pSpCircle->op  =  OP_DELETE;
					   if  (  postToOpedQ(  pQNodeParm,  pSp  )  )  goto  errLabel;				
					   break;
				   }
				   break;
			 case  OP_CHECK:
				   if  (  pSpCircle->op == OP_MOVE ) {	
					   SP_OBJ  *  pSpObj = ( SP_OBJ * )pSpCircle->pCenterQNode->qElemMemory.m_pBuf;
					   if  (  pSpObj->op != op ) {
						   if  (  preOpSpPoint( pSp, pSpCircle->pCenterQNode, pSpCircle->op, pOpParm, pDriver, pParm ) ) goto  errLabel;
						   if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;				
					   }
					   pSpObj = ( SP_OBJ * )pSpCircle->pCircleQNode->qElemMemory.m_pBuf;
					   if  (  pSpObj->op != op ) {
						   if  (  preOpSpPoint( pSp, pSpCircle->pCircleQNode, pSpCircle->op, pOpParm, pDriver, pParm )  )  goto  errLabel;
						   if  (  !isQEmpty(  pSp->pOpedSpObjQ  )  )  break;				
					   }			
				   }
				   break;
			 case  OP_MOVE:
				   if  (  preOpSpPoint( pSp, pSpCircle->pCenterQNode, op, pOpParm, pDriver, pParm ) 
					   ||  preOpSpPoint( pSp, pSpCircle->pCircleQNode, op, pOpParm, pDriver, pParm ) ) 
				   {
						logErr( "preOpSpSegment():preOpSpPoint() failed" );
						goto  errLabel;						
				   }
				   pSpCircle->status |= STATUS_PROCED;
				   break;
			 case  OP_REFRESH_CONSTRAINT:
				   break;
			 case  OP_DELETE:
				   if  (  pSpCircle->bOwner_pCenterQNode  &&  pSpObj1->op  !=  OP_DELETE  )  {
					   pSpObj1->op  =  OP_DELETE;
					   if  (  postToOpedQ(  pSpCircle->pCenterQNode,  pSp  )  )  goto  errLabel;
				   }
				   if  (  pSpCircle->bOwner_pCircleQNode  &&  pSpObj2->op  !=  OP_DELETE  )  {
					   pSpObj2->op  =  OP_DELETE;
					   if  (  postToOpedQ(  pSpCircle->pCircleQNode,  pSp  )  )  goto  errLabel;
				   }
				   if  (  pSpCircle->op  !=  OP_DELETE  )  {
					   pSpCircle->op  =  OP_DELETE;
					   if  (  postToOpedQ(  pQNodeParm,  pSp  )  )  goto  errLabel;				
				   }
				   break;
			 default:
				     goto  errLabel;
					 break;
	 }

	 iErr  =  0;
errLabel:
	 return iErr;
}

 int preOpSpAnimator( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm )
{
	 int iErr = 0;
	 SP_ANIMATOR *pSpAnimator;

	 pSpAnimator = ( SP_ANIMATOR * )pQNodeParm->qElemMemory.m_pBuf;

	 switch ( op ) {
	
		case OP_MOVE:
			/* do sth to move */
			break;

		case OP_ANIMATE:

			break;

		default:

			iErr = -1;
			break;

	 }


	 return iErr;

}

 int preOpSpGenericRectangle( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm )
{
	int					iErr		=	-1;
	SP_RECTANGLE	*	pRectangle;
	int					i;
	SP_OBJ			*	pSpObj;
	BOOL				bDeleted	=	FALSE;

	pRectangle  =  (  SP_RECTANGLE  *  )pQNodeParm->qElemMemory.m_pBuf;

	switch  (  op  )  {
			case  OP_NULL:
				  for  (  i  =  0;  i  <  mycountof(  pRectangle->pQNode_points  );  i  ++  )  {
					   pSpObj  =  (  SP_OBJ  *  )pRectangle->pQNode_points[i]->qElemMemory.m_pBuf;
					   if  (  pSpObj->op  ==  OP_DELETE  )  {
						   bDeleted  =  TRUE;  
						   break;
					   }
				  }
				  if  (  !bDeleted  )  {
					  for  (  i  =  0;  i  <  mycountof(  pRectangle->pQNode_points  );  i  ++  )  {
						   pSpObj  =  (  SP_OBJ  *  )pRectangle->pQNode_segments[i]->qElemMemory.m_pBuf;
						   if  (  pSpObj->op  ==  OP_DELETE  )  {
							   bDeleted  =  TRUE;  
							   break;
						   }
					  }
				  }
				  if  (  bDeleted  )  {
					  for  (  i  =  0;  i  <  mycountof(  pRectangle->pQNode_points  );  i  ++  )  {
						   pSpObj  =  (  SP_OBJ  *  )pRectangle->pQNode_points[i]->qElemMemory.m_pBuf;
						   if  (  pRectangle->bOwner_points[i]  &&  pSpObj->op  !=  OP_DELETE  )  {
							   pSpObj->op  =  OP_DELETE;
							   postToOpedQ(  pRectangle->pQNode_points[i],  pSp  );
						   }
					  }
					  for  (  i  =  0;  i  <  mycountof(  pRectangle->pQNode_segments  );  i  ++  )  {
						   pSpObj  =  (  SP_OBJ  *  )pRectangle->pQNode_segments[i]->qElemMemory.m_pBuf;
						   if  (  pRectangle->bOwner_segments[i]  &&  pSpObj->op  !=  OP_DELETE  )  {
							   pSpObj->op  =  OP_DELETE;
							   postToOpedQ(  pRectangle->pQNode_segments[i],  pSp  );
						   }
					  }
					  pRectangle->op  =  OP_DELETE;
					  postToOpedQ(  pQNodeParm,  pSp  );
				  }
				  break;
			case  OP_MOVE:
				  break;
			case  OP_DELETE:
				  break;
			default:
					goto  errLabel;
	}

	iErr  =  0;
	
errLabel:

	return  iErr;
}

 int preOpSpRectangle( SP_STRUCT *pSp, Q_NODE *pQNodeParm, BYTE op, SP_OP_PARM *pOpParm, SP_DRIVER *pDriver, SP_PARM *pParm )
{
	 int	iErr		=	-1;
	 BYTE	subType;						

	 subType  =  ( ( SP_RECTANGLE * )pQNodeParm->qElemMemory.m_pBuf )->subType;

	 switch  (  subType ) {
		
			 case  0:
				   return  preOpSpGenericRectangle( pSp, pQNodeParm, op, pOpParm, pDriver, pParm );
				   break;
			 default:
					break;
	 }
	 return  -1;
 }
