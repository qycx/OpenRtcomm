
#include	"stdafx.h"

#include	"sp.h"

 int  makeSegment(  Q_NODE  *  pQNode_point0,  Q_NODE  *  pQNode_point1,  SP_SEGMENT  &  tmpSegment  )
{
	memset(  &tmpSegment,  0,  sizeof(  tmpSegment  )  );
	tmpSegment.type = SP_SEGMENT_TYPE;
	tmpSegment.subType = SP_GENERIC_SEGMENT_TYPE;
	tmpSegment.status = 0;
	//  tmpSegment.ucbHorizontal  =  TRUE;		
	//  tmpSegment.ucbVertical  =  TRUE;
	tmpSegment.pStartQNode  =  pQNode_point0;
	tmpSegment.pEndQNode  =  pQNode_point1;
	tmpSegment.point1.rect.y = ( ( SP_POINT * )tmpSegment.pStartQNode->qElemMemory.m_pBuf )->point.rect.y;
	tmpSegment.point1.rect.x = ( ( SP_POINT * )tmpSegment.pStartQNode->qElemMemory.m_pBuf )->point.rect.x;
	tmpSegment.point2.rect.y = ( ( SP_POINT * )tmpSegment.pEndQNode->qElemMemory.m_pBuf )->point.rect.y;
	tmpSegment.point2.rect.x = ( ( SP_POINT * )tmpSegment.pEndQNode->qElemMemory.m_pBuf )->point.rect.x;
	
	return  0;
}

 __declspec(  dllexport  )  int  newCadRectangle(  SP_STRUCT  *  pSp,  int  iX,  int  iY,  int  iW,  int  iH,  SP_RECTANGLE  &  tmpRectangle  )
{
	int					iErr			=	-1;
	int					i;
	Q_NODE			*	tmppQNode;
	SP_OBJ			*	pSpObj;
	SP_POINT			tmpSpPoint;
	SP_SEGMENT			tmpSegment;
	SP_POINT			startPoint,  endPoint;
	
	memset(  &tmpRectangle,  0,  sizeof(  tmpRectangle  )  );
	tmpRectangle.type  =  SP_RECTANGLE_TYPE;
	tmpRectangle.subType  =  0;
	tmpRectangle.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );	//  2009/10/02

	memset(  &startPoint,  0,  sizeof(  startPoint  )  );
	startPoint.type  =  SP_POINT_TYPE;
	startPoint.subType  =  SP_GENERIC_POINT_TYPE;
	startPoint.point.rect.x  =  iX;
	startPoint.point.rect.y  =  iY;

	memcpy(  &endPoint,  &startPoint,  sizeof(  endPoint  )  );
	endPoint.point.rect.x  =  iX  +  iW;
	endPoint.point.rect.y  =  iY  +  iH;

	i  =  0;
	if  (  (  tmppQNode = findNextpQNodeOfSamePlaceSpObj( pSp->pSpObjQ->front.pNext, ( SP_OBJ * )&startPoint ) ) ) {
		tmpRectangle.pQNode_points[i]  =  tmppQNode;
		memcpy(  &startPoint,  (  SP_POINT  *  )tmpRectangle.pQNode_points[i]->qElemMemory.m_pBuf,  sizeof(  startPoint  )  );
		}
	else  {
		  startPoint.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );
		  if  (  qPostMsg(  &startPoint,  sizeof(  SP_POINT  ),  pSp->pSpObjQ,  _T(  "newCadRect 7"  )))  goto  errLabel;
		  tmpRectangle.pQNode_points[i]  =  getpLastQNode(  pSp->pSpObjQ  );	
		  tmpRectangle.bOwner_points[i]  =  TRUE;
	}

	i  =  2;
	if  (  (  tmppQNode = findNextpQNodeOfSamePlaceSpObj( pSp->pSpObjQ->front.pNext, ( SP_OBJ * )&endPoint ) ) ) {
		tmpRectangle.pQNode_points[i]  =  tmppQNode;
		memcpy(  &endPoint,  (  SP_POINT  *  )tmpRectangle.pQNode_points[i]->qElemMemory.m_pBuf,  sizeof(  endPoint  )  );
		}
	else  {
		  endPoint.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );
		  if  (  qPostMsg(  &endPoint,  sizeof(  SP_POINT  ),  pSp->pSpObjQ,  _T(  "newCadRect 8"  )))  goto  errLabel;
		  tmpRectangle.pQNode_points[i]  =  getpLastQNode(  pSp->pSpObjQ  );	
		  tmpRectangle.bOwner_points[i]  =  TRUE;
	}
	i  =  1;						  
	memset(  &tmpSpPoint,  0,  sizeof(  tmpSpPoint  )  );
	tmpSpPoint.type  =  SP_POINT_TYPE;
	tmpSpPoint.subType  =  SP_GENERIC_POINT_TYPE;
	tmpSpPoint.point.rect.x  =  endPoint.point.rect.x;
	tmpSpPoint.point.rect.y  =  startPoint.point.rect.y;
	tmpSpPoint.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );
	if  (  qPostMsg(  &tmpSpPoint,  sizeof(  SP_POINT  ),  pSp->pSpObjQ,  _T( "newCadRect 3" )))  goto  errLabel;
	tmpRectangle.pQNode_points[i]  =  getpLastQNode(  pSp->pSpObjQ  );
	tmpRectangle.bOwner_points[i]  =  TRUE;
	i  =  3;
	memset(  &tmpSpPoint,  0,  sizeof(  tmpSpPoint  )  );
	tmpSpPoint.type  =  SP_POINT_TYPE;
	tmpSpPoint.subType  =  SP_GENERIC_POINT_TYPE;
	tmpSpPoint.point.rect.x  =  startPoint.point.rect.x;
	tmpSpPoint.point.rect.y  =  endPoint.point.rect.y;
	tmpSpPoint.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );
	if  (  qPostMsg(  &tmpSpPoint,  sizeof(  SP_POINT  ),  pSp->pSpObjQ,  _T(  "newCadRect 4")))  goto  errLabel;
	tmpRectangle.pQNode_points[i]  =  getpLastQNode(  pSp->pSpObjQ  );
	tmpRectangle.bOwner_points[i]  =  TRUE;

	for  (  i  =  0;  i  <  mycountof(  tmpRectangle.pQNode_points  );  i  ++  )  {
		 pSpObj  =  (  SP_OBJ  *  )tmpRectangle.pQNode_points[i]->qElemMemory.m_pBuf;					
		 _sntprintf(  pSpObj->desc,  mycountof(  pSpObj->desc  ),  _T(  "rect.point %d"  ),  i  );
	}							   

	i  =  0;
	makeSegment(  tmpRectangle.pQNode_points[i],  tmpRectangle.pQNode_points[(  i +  1  )  %  4],  tmpSegment  );
	tmpSegment.ucbHorizontal  =  TRUE;		
	tmpSegment.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );
	if  (  qPostMsg( &tmpSegment, sizeof( SP_SEGMENT ),  pSp->pSpObjQ,  _T(  "newCadRect5"  ))) goto  errLabel;
	tmpRectangle.pQNode_segments[i]  =  getpLastQNode(  pSp->pSpObjQ  );
	tmpRectangle.bOwner_segments[i]  =  TRUE;

	i  ++  ;
	makeSegment(  tmpRectangle.pQNode_points[i],  tmpRectangle.pQNode_points[(  i +  1  )  %  4],  tmpSegment  );
	tmpSegment.ucbVertical  =  TRUE;
	tmpSegment.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );
	if  (  qPostMsg(  &tmpSegment,  sizeof(  SP_SEGMENT  ),  pSp->pSpObjQ,  _T(  "newCadRect6"  )))  goto  errLabel;
	tmpRectangle.pQNode_segments[i]  =  getpLastQNode(  pSp->pSpObjQ  );
	tmpRectangle.bOwner_segments[i]  =  TRUE;

	i  ++  ;
	makeSegment(  tmpRectangle.pQNode_points[i],  tmpRectangle.pQNode_points[(  i +  1  )  %  4],  tmpSegment  );
	tmpSegment.ucbHorizontal  =  TRUE;
	tmpSegment.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );
	if ( qPostMsg( &tmpSegment, sizeof( SP_SEGMENT ),  pSp->pSpObjQ,  _T(  "newCadRectangle"  ))) goto  errLabel;
	tmpRectangle.pQNode_segments[i]  =  getpLastQNode(  pSp->pSpObjQ  );
	tmpRectangle.bOwner_segments[i]  =  TRUE;

	i  ++  ;
	makeSegment(  tmpRectangle.pQNode_points[i],  tmpRectangle.pQNode_points[(  i +  1  )  %  4],  tmpSegment  );
	tmpSegment.ucbVertical  =  TRUE;
	tmpSegment.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );
	if  (  qPostMsg(  &tmpSegment,  sizeof(  SP_SEGMENT  ),  pSp->pSpObjQ,  _T(  "newCadRect 2"  )))  goto  errLabel;
	tmpRectangle.pQNode_segments[i]  =  getpLastQNode(  pSp->pSpObjQ  );
	tmpRectangle.bOwner_segments[i]  =  TRUE;

	for  (  i  =  0;  i  <  mycountof(  tmpRectangle.pQNode_segments  );  i  ++  )  {
		 //					
		 pSpObj  =  (  SP_OBJ  *  )tmpRectangle.pQNode_segments[i]->qElemMemory.m_pBuf;					
		 _sntprintf(  pSpObj->desc,  mycountof(  pSpObj->desc  ),  _T(  "rect.seg %d"  ),  i  );
	}

	if ( ( tmppQNode = findNextpQNodeOfSamePlaceSpObj( pSp->pSpObjQ->front.pNext, ( SP_OBJ * )&tmpRectangle ) ) ) goto  errLabel;

	if  (  qPostMsg(  &tmpRectangle,  sizeof(  tmpRectangle  ),  pSp->pSpObjQ,  _T(  "newCadRect 3"  )))  goto  errLabel;

	iErr  =  0;

errLabel:
	return  iErr;
}


 __declspec(  dllexport  )  int spProcLButtonDown( SP_STRUCT *pSp, SP_RECT_COORD *pPoint, unsigned int iFlags )
{
	int		iErr	=	-1;
	int		i;

	debugLog( "spProcLButtonDown()" );
	 
	switch  (  pSp->tranType  )  {
		    case  CREATE_OBJS_TRAN:
				  logErr( "Serious error: CREATE_OBJS_TRAN has been started" );
				  return  -1;
			case  NO_TRAN:
				  if  (  pSp->sysStatus == STATUS_CREATE_A_POINT ) {				
					  SP_POINT tmpPoint;
	
					  memset(  &tmpPoint,  0,  sizeof(  tmpPoint  )  );

					  if ( pPoint->x < 0 || pPoint->x > pSp->spWidth 
						  || pPoint->y < 0 || pPoint->y > pSp->spHeight ) 
					  {					
						  logErr( "spProcLButtonDown():pPoint error" );				
						  goto  errLabel;
					  }
								
					  if ( initTran( pSp, CREATE_OBJS_TRAN ) ) goto  errLabel;
					  
					  emptyGenericQ( pSp->pSelectedSpObjQ );
				
					  tmpPoint.type = SP_POINT_TYPE;
					  tmpPoint.point.rect.x = pPoint->x;
					  tmpPoint.point.rect.y = pPoint->y;
					  tmpPoint.status = 0;
					  tmpPoint.subType = SP_GENERIC_POINT_TYPE;	
					  tmpPoint.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );	//  2009/10/02

					  if ( qPostMsg( &tmpPoint, sizeof( SP_POINT ),  pSp->pNewSpObjQ,  _T(  "spProcLButtonDown 20"  ))) {
						  pSp->errNo = -1; break;	
					  }						
					  }
				  else  if  (  pSp->sysStatus == STATUS_CREATE_A_SEGMENT ) {
					        SP_POINT		tmpPoint;	
							SP_SEGMENT		tmpSegment;
							Q_NODE		*	pQNode		=	NULL;

							memset(  &tmpPoint,  0,  sizeof(  tmpPoint  )  );
							memset(  &tmpSegment,  0,  sizeof(  tmpSegment  )  );

							if ( pPoint->x < 0 || pPoint->x > pSp->spWidth 
								|| pPoint->y < 0 || pPoint->y > pSp->spHeight ) 
							{
								logErr( "spProcLButtonDown():pPoint error" );
								goto  errLabel;
							}
				
							if ( initTran( pSp, CREATE_OBJS_TRAN ) ) goto  errLabel;
							
							emptyGenericQ( pSp->pSelectedSpObjQ );

							tmpPoint.type = SP_POINT_TYPE;
							tmpPoint.point.rect.x = pPoint->x;
							tmpPoint.point.rect.y = pPoint->y;
							tmpPoint.status = 0;
							tmpPoint.subType = SP_GENERIC_POINT_TYPE;
							tmpPoint.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );

							/* try to identify the first point in queue */
							/* but always to new the second point in queue */
							if ( ( pQNode = findNextpQNodeOfSamePlaceSpObj( pSp->pSpObjQ->front.pNext, ( SP_OBJ * )&tmpPoint ) ) ) {
								tmpSegment.pStartQNode = pQNode;
								}
							else {
								 if ( qPostMsg( &tmpPoint, sizeof( SP_POINT ),  pSp->pNewSpObjQ,  _T(  "spProcLButtonDown 10"  ))) goto  errLabel;
								 tmpSegment.pStartQNode = getpLastQNode( pSp->pNewSpObjQ );
								 tmpSegment.bOwner_pStartQNode  =  TRUE;
							}			

							tmpPoint.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );
							if ( qPostMsg( &tmpPoint, sizeof( SP_POINT ),  pSp->pNewSpObjQ,  _T(  "spProcLButtonDown 11"  ))) goto  errLabel;
							tmpSegment.pEndQNode = getpLastQNode( pSp->pNewSpObjQ );
				
							tmpSegment.type = SP_SEGMENT_TYPE;
							tmpSegment.subType = SP_GENERIC_SEGMENT_TYPE;
							tmpSegment.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );
							tmpSegment.status = 0;
							tmpSegment.point1.rect.y = ( ( SP_POINT * )tmpSegment.pStartQNode->qElemMemory.m_pBuf )->point.rect.y;
							tmpSegment.point1.rect.x = ( ( SP_POINT * )tmpSegment.pStartQNode->qElemMemory.m_pBuf )->point.rect.x;
							tmpSegment.point2.rect.y = ( ( SP_POINT * )tmpSegment.pEndQNode->qElemMemory.m_pBuf )->point.rect.y;
							tmpSegment.point2.rect.x = ( ( SP_POINT * )tmpSegment.pEndQNode->qElemMemory.m_pBuf )->point.rect.x;

							if ( qPostMsg( &tmpSegment, sizeof( SP_SEGMENT ),  pSp->pNewSpObjQ,  _T(  "spProcLButtonDown 11"  ))) {
								pSp->errNo = -1; break;
							}							
							}
				  else  if  (  pSp->sysStatus  ==  STATUS_CREATE_A_CIRCLE  )  {
							SP_POINT		tmpPoint;
							SP_CIRCLE		tmpCircle;
							Q_NODE		*	pQNode		=	NULL;

							memset(  &tmpPoint,  0,  sizeof(  tmpPoint  )  );
							memset(  &tmpCircle,  0,  sizeof(  tmpCircle  )  );

							if ( pPoint->x < 0 || pPoint->x > pSp->spWidth 
								|| pPoint->y < 0 || pPoint->y > pSp->spHeight ) 
							{							
								logErr( "spProcLButtonDown():pPoint error" );
								goto  errLabel;
							}

							if ( initTran( pSp, CREATE_OBJS_TRAN ) ) goto  errLabel;
							
							emptyGenericQ( pSp->pSelectedSpObjQ );

							tmpPoint.type = SP_POINT_TYPE;
							tmpPoint.point.rect.x = pPoint->x;
							tmpPoint.point.rect.y = pPoint->y;
							tmpPoint.status = 0;
							tmpPoint.subType = SP_GENERIC_POINT_TYPE;
							tmpPoint.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );

							if ( ( pQNode = findNextpQNodeOfSamePlaceSpObj( pSp->pSpObjQ->front.pNext, ( SP_OBJ * )&tmpPoint ) ) ) {
								tmpCircle.pCenterQNode = pQNode;
								}
							else {
								if ( qPostMsg( &tmpPoint, sizeof( SP_POINT ),  pSp->pNewSpObjQ,  _T("spProcLButtonDown 11"))) goto  errLabel;
								tmpCircle.pCenterQNode = getpLastQNode( pSp->pNewSpObjQ );
								tmpCircle.bOwner_pCenterQNode  =  TRUE;
							}		

							tmpPoint.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );
							if ( qPostMsg( &tmpPoint, sizeof( SP_POINT ),  pSp->pNewSpObjQ,  _T(  "spProcLButtonDown 12"  ))) goto  errLabel;
							tmpCircle.pCircleQNode = getpLastQNode( pSp->pNewSpObjQ );
				
							tmpCircle.type = SP_CIRCLE_TYPE;
							tmpCircle.subType = SP_GENERIC_CIRCLE_TYPE;
							tmpCircle.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );
							tmpCircle.status = 0;
							if ( qPostMsg( &tmpCircle, sizeof( SP_CIRCLE ),  pSp->pNewSpObjQ,  _T(  "spProcLButtonDown 6"  ))) {
								pSp->errNo = -1; break;
							}

						  }
				  else  if  (  pSp->sysStatus  ==  STATUS_CREATE_A_RECTANGLE  )  {	
					        SP_POINT		tmpPoint;
							SP_RECTANGLE	tmpRectangle;
							Q_NODE		*	pQNode		=	NULL;

							memset(  &tmpPoint,  0,  sizeof(  tmpPoint  )  );
							memset(  &tmpRectangle,  0,  sizeof(  tmpRectangle  )  );

							if ( pPoint->x < 0 || pPoint->x > pSp->spWidth 
								|| pPoint->y < 0 || pPoint->y > pSp->spHeight ) 
							{
								logErr( "spProcLButtonDown():pPoint error" );
								goto  errLabel;
							}
				
							if ( initTran( pSp, CREATE_OBJS_TRAN ) )  goto  errLabel;
							
							emptyGenericQ( pSp->pSelectedSpObjQ );
					
							tmpPoint.type = SP_POINT_TYPE;
							tmpPoint.point.rect.x = pPoint->x;
							tmpPoint.point.rect.y = pPoint->y;
							tmpPoint.status = 0;
							tmpPoint.subType = SP_GENERIC_POINT_TYPE;

							i  =  0;
							if ( qPostMsg( &tmpPoint, sizeof( SP_POINT ),  pSp->pNewSpObjQ,  _T(  "spProcLButtonDown 5"  ))) goto  errLabel;
							tmpRectangle.pQNode_points[i] = getpLastQNode( pSp->pNewSpObjQ );							
							i  ++  ;
							if ( qPostMsg( &tmpPoint, sizeof( SP_POINT ),  pSp->pNewSpObjQ,  _T(  "spProcLButtonDown 4"))) goto  errLabel;
							tmpRectangle.pQNode_points[i]  =  getpLastQNode( pSp->pNewSpObjQ );				
							i  ++  ;
							if ( qPostMsg( &tmpPoint, sizeof( SP_POINT ),  pSp->pNewSpObjQ,  _T(  "spProcLButtonDown 3"  ))) goto  errLabel;
							tmpRectangle.pQNode_points[i]  =  getpLastQNode( pSp->pNewSpObjQ );
							i  ++  ;
							if ( qPostMsg( &tmpPoint, sizeof( SP_POINT ),  pSp->pNewSpObjQ,  _T(  "spProcLButtonDown 2"  ))) goto  errLabel;
							tmpRectangle.pQNode_points[i]  =  getpLastQNode( pSp->pNewSpObjQ );


							//
							SP_SEGMENT		tmpSegment;

							i  =  0;
							makeSegment(  tmpRectangle.pQNode_points[i],  tmpRectangle.pQNode_points[(  i +  1  )  %  4],  tmpSegment  );
							tmpSegment.ucbHorizontal  =  TRUE;
							if ( qPostMsg( &tmpSegment, sizeof( SP_SEGMENT ),  pSp->pNewSpObjQ,  _T(  "spProcLButtonDown 7"  ))) goto  errLabel;
							tmpRectangle.pQNode_segments[i]  =  getpLastQNode(  pSp->pNewSpObjQ  );

							i  ++  ;
							makeSegment(  tmpRectangle.pQNode_points[i],  tmpRectangle.pQNode_points[(  i +  1  )  %  4],  tmpSegment  );
							tmpSegment.ucbVertical  =  TRUE;
							if  (  qPostMsg(  &tmpSegment,  sizeof(  SP_SEGMENT  ),  pSp->pNewSpObjQ,  _T(  "spProcLButtonDown 8"  )))  goto  errLabel;
							tmpRectangle.pQNode_segments[i]  =  getpLastQNode(  pSp->pNewSpObjQ  );

							i  ++  ;
							makeSegment(  tmpRectangle.pQNode_points[i],  tmpRectangle.pQNode_points[(  i +  1  )  %  4],  tmpSegment  );
							tmpSegment.ucbHorizontal  =  TRUE;
							if ( qPostMsg( &tmpSegment, sizeof( SP_SEGMENT ),  pSp->pNewSpObjQ,  _T(  "spProcLButtonDown 8"  ))) goto  errLabel;
							tmpRectangle.pQNode_segments[i]  =  getpLastQNode(  pSp->pNewSpObjQ  );

							i  ++  ;
							makeSegment(  tmpRectangle.pQNode_points[i],  tmpRectangle.pQNode_points[(  i +  1  )  %  4],  tmpSegment  );
							tmpSegment.ucbVertical  =  TRUE;
							if  (  qPostMsg(  &tmpSegment,  sizeof(  SP_SEGMENT  ),  pSp->pNewSpObjQ,  _T(  "spProcLButtonDown 9"  )))  goto  errLabel;
							tmpRectangle.pQNode_segments[i]  =  getpLastQNode(  pSp->pNewSpObjQ  );

							//
							tmpRectangle.type  =  SP_RECTANGLE_TYPE;
							tmpRectangle.subType  =  0;
							if  (  qPostMsg(  &tmpRectangle,  sizeof(  tmpRectangle  ),  pSp->pNewSpObjQ,  _T(  "spProcLButtonDown 1")))  goto  errLabel;

						  }
				  else  if  (  pSp->sysStatus  ==  STATUS_SELECT  )  {
							Q_NODE	*	pQNode		=	NULL;
							Q_NODE	*	tmppQNode	=	NULL;

							if ( pPoint->x < 0 || pPoint->x > pSp->spWidth 
								|| pPoint->y < 0 || pPoint->y > pSp->spHeight ) 
							{						
								logErr( "spProcLButtonDown():pPoint error" );
								goto  errLabel;
							}

							if ( ( pQNode = findNextpQNodeSelected( pSp->pSpObjQ->front.pNext, pPoint ) ) ) {
						
								if ( initTran( pSp, MOVE_OBJS_TRAN ) )  goto  errLabel;
								

								pSp->tranParm.move.curPlace.x = pSp->tranParm.move.lastPlace.x = pPoint->x;
								pSp->tranParm.move.curPlace.y = pSp->tranParm.move.lastPlace.y = pPoint->y;
					
								for ( tmppQNode = pSp->pSelectedSpObjQ->front.pNext; tmppQNode; tmppQNode = tmppQNode->pNext )
									if ( ( Q_NODE * )( ( Q_NODE * )tmppQNode->qElemMemory.m_pBuf )->qElemMemory.m_pBuf == pQNode ) break;
						
								if ( !tmppQNode ) {
								
									SP_SELECT_Q_ELEM tmpSelectQElem;

									if ( !( iFlags & MK_CONTROL ) ) emptyGenericQ( pSp->pSelectedSpObjQ );
								
									tmpSelectQElem.pQNode = pQNode;
								
									if ( qPostMsg( &tmpSelectQElem, sizeof( SP_SELECT_Q_ELEM ),  pSp->pSelectedSpObjQ,  _T(  "spProcLButtonDown 2"  ))) goto  errLabel;
					
								} 
								}
							else  {
								  if ( initTran( pSp, DRAW_A_RGN_TRAN ) ) goto  errLabel;
								  			
								  pSp->tranParm.drawARgn.firstCorner.x = pPoint->x;
								  pSp->tranParm.drawARgn.firstCorner.y = pPoint->y;
					
								  emptyGenericQ( pSp->pSelectedSpObjQ );

								  /* many codes must added here */
							}
			
				  }

				  break;	/* end of case CREATE_OBJS_TRAN */


		case  DISCMD_ANIMATE_TRAN:
			  restoreLastQNode( pSp->pSpObjQ );
			  exitTran( pSp );		
			  break;

		default:
				pSp->errNo = -1;
				break;
		
	} /* end of switch */

	if  ( pSp->errNo ) goto errLabel;

	iErr  =  0;

errLabel:
	
	if  (  iErr  ||  pSp->errNo  )  {
		exitTran(  pSp  );
	}

	return  iErr;
}

 __declspec(  dllexport  )  int spProcLButtonUp( SP_STRUCT *pSp, SP_RECT_COORD *pPoint, unsigned int iFlags )
{
	 int	iErr	=	-1;
	 int	i		=	0;
	 
	 debugLog( "spProcLButtonUp()" );

	 switch  (  pSp->tranType  )  {
			 case  NO_TRAN:
				   break;
			 case  CREATE_OBJS_TRAN:
				   if  (  pSp->sysStatus == STATUS_CREATE_A_POINT ) {
					   SP_POINT tmpPoint;
					   SP_SELECT_Q_ELEM tmpSelectQElem;
			
					   if ( pPoint->x < 0 || pPoint->x > pSp->spWidth 						
						   || pPoint->y < 0 || pPoint->y > pSp->spHeight ) 
					   {
						   goto  errLabel;
					   }
					
					   tmpPoint.point.rect.x = pPoint->x;
					   tmpPoint.point.rect.y = pPoint->y;
					   tmpPoint.type = SP_POINT_TYPE;
					
					   if ( tryToChangeNewSpPointSubType( pSp->pSpObjQ, pSp->pNewSpObjQ, &tmpPoint ) ) goto  errLabel;
					
					   /* creating a point succeeded */
					   link2Q( pSp->pNewSpObjQ, pSp->pSpObjQ );

					   tmpSelectQElem.pQNode = getpLastQNode( pSp->pSpObjQ );
					   if ( qPostMsg( &tmpSelectQElem, sizeof( SP_SELECT_Q_ELEM ),  pSp->pSelectedSpObjQ,  _T(  "spProcLButtonUp 3"  ))) goto  errLabel;
		
				   }
				else  if  (  pSp->sysStatus == STATUS_CREATE_A_SEGMENT ) {
						  Q_NODE *pLastQNode, *tmppQNode;
						  SP_POINT *pStartPoint, *pEndPoint;
						  SP_SEGMENT *pSpSegment;
						  SP_SELECT_Q_ELEM tmpSelectQElem;
						
						  if  (  pPoint->x < 0 || pPoint->x > pSp->spWidth 
							  || pPoint->y < 0 || pPoint->y > pSp->spHeight ) 
						  {
							  goto  errLabel;							  
						  }

						  pLastQNode = getpLastQNode( pSp->pNewSpObjQ );
						  pSpSegment = (  SP_SEGMENT  *  )pLastQNode->qElemMemory.m_pBuf;
				
						  pStartPoint = ( SP_POINT * )( ( SP_SEGMENT * )pLastQNode->qElemMemory.m_pBuf )->pStartQNode->qElemMemory.m_pBuf;
						  pEndPoint = ( SP_POINT * )( ( SP_SEGMENT * )pLastQNode->qElemMemory.m_pBuf )->pEndQNode->qElemMemory.m_pBuf;
			
						  if ( isSamePlaceSpPoint( pStartPoint, pEndPoint ) ) goto  errLabel;
								
						  if ( ( tmppQNode = findNextpQNodeOfSamePlaceSpObj( pSp->pSpObjQ->front.pNext, ( SP_OBJ * )pEndPoint ) ) ) {
							  removeAQNode( pSp->pNewSpObjQ, ( ( SP_SEGMENT * )pLastQNode->qElemMemory.m_pBuf )->pEndQNode );
							  ( ( SP_SEGMENT * )pLastQNode->qElemMemory.m_pBuf )->pEndQNode = tmppQNode;
							  }
						  else  {
							    pSpSegment->bOwner_pEndQNode  =  TRUE;
						  }

						  if ( ( tmppQNode = findNextpQNodeOfSamePlaceSpObj( pSp->pSpObjQ->front.pNext, ( SP_OBJ * )pSpSegment ) ) ) goto  errLabel;
						  
						  link2Q( pSp->pNewSpObjQ, pSp->pSpObjQ );

						  tmpSelectQElem.pQNode = getpLastQNode( pSp->pSpObjQ );
						  if ( qPostMsg( &tmpSelectQElem, sizeof( SP_SELECT_Q_ELEM ),  pSp->pSelectedSpObjQ,  _T(  "spProcLButtonUp 12"  ))) goto  errLabel;
				
						  /* creating a segment succeeded */
					}
				else  if  (  pSp->sysStatus == STATUS_CREATE_A_CIRCLE ) {
						  Q_NODE *pLastQNode, *tmppQNode;
						  SP_POINT *pCenterPoint, *pCirclePoint;
						  SP_CIRCLE *pSpCircle;
						  SP_SELECT_Q_ELEM tmpSelectQElem;
						
						  if ( pPoint->x < 0 || pPoint->x > pSp->spWidth 
							  || pPoint->y < 0 || pPoint->y > pSp->spHeight ) 
						  {
							  goto  errLabel;
						  }

						  pLastQNode = getpLastQNode( pSp->pNewSpObjQ );
						  pSpCircle = (  SP_CIRCLE  *  )pLastQNode->qElemMemory.m_pBuf;
									
						  pCenterPoint = ( SP_POINT * )( ( SP_CIRCLE * )pLastQNode->qElemMemory.m_pBuf )->pCenterQNode->qElemMemory.m_pBuf;
						  pCirclePoint = ( SP_POINT * )( ( SP_CIRCLE * )pLastQNode->qElemMemory.m_pBuf )->pCircleQNode->qElemMemory.m_pBuf;
			
						  if ( isSamePlaceSpPoint( pCenterPoint, pCirclePoint ) ) goto  errLabel;
					
						  if ( ( tmppQNode = findNextpQNodeOfSamePlaceSpObj( pSp->pSpObjQ->front.pNext, ( SP_OBJ * )pCirclePoint ) ) ) {
							  removeAQNode( pSp->pSpObjQ, ( ( SP_CIRCLE * )pLastQNode->qElemMemory.m_pBuf )->pCircleQNode );
							  ( ( SP_CIRCLE * )pLastQNode->qElemMemory.m_pBuf )->pCircleQNode = tmppQNode;
							}
						  else  {
							    pSpCircle->bOwner_pCircleQNode  =  TRUE;
						  }

						  if ( ( tmppQNode = findNextpQNodeOfSamePlaceSpObj( pSp->pSpObjQ->front.pNext, ( SP_OBJ * )pSpCircle ) ) ) goto  errLabel;

						  link2Q( pSp->pNewSpObjQ, pSp->pSpObjQ );
						  /* creating a circle succeeded */
						  tmpSelectQElem.pQNode = getpLastQNode( pSp->pSpObjQ );
								
						  if ( qPostMsg( &tmpSelectQElem, sizeof( SP_SELECT_Q_ELEM ),  pSp->pSelectedSpObjQ,  _T(  "spProcLButtonUp 14"  ))) goto  errLabel;
					  
						}		
				else  if  (  pSp->sysStatus == STATUS_CREATE_A_RECTANGLE ) {
						  SP_RECTANGLE		*		pSpRectangle	=	NULL;
						  Q_NODE			*		pLastQNode		=	NULL;
						  Q_NODE			*		tmppQNode		=	NULL;
						  SP_POINT			*		pStartPoint		=	NULL;
						  SP_POINT			*		pEndPoint		=	NULL;
						  SP_POINT					tmpSpPoint;
						  SP_SEGMENT				tmpSegment;
						  SP_RECTANGLE				tmpRectangle;
						  SP_SELECT_Q_ELEM			tmpSelectQElem;
						  SP_OBJ			*		pSpObj			=	NULL;  
						
						  if ( pPoint->x < 0 || pPoint->x > pSp->spWidth 
							  || pPoint->y < 0 || pPoint->y > pSp->spHeight ) 
						  {
							  goto  errLabel;
						  }

						  pLastQNode = getpLastQNode( pSp->pNewSpObjQ );
						  pSpRectangle = (  SP_RECTANGLE  *  )pLastQNode->qElemMemory.m_pBuf;
				
						  pStartPoint = ( SP_POINT * )pSpRectangle->pQNode_points[0]->qElemMemory.m_pBuf;
						  pEndPoint = ( SP_POINT * )pSpRectangle->pQNode_points[2]->qElemMemory.m_pBuf;
			

						  if ( isSamePlaceSpPoint( pStartPoint, pEndPoint ) ) goto  errLabel;
	
						  memset(  &tmpRectangle,  0,  sizeof(  tmpRectangle  )  );
						  tmpRectangle.type  =  SP_RECTANGLE_TYPE;
						  tmpRectangle.subType  =  0;
						  tmpRectangle.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );	//  2009/10/02

						  i  =  0;
						  if  (  (  tmppQNode = findNextpQNodeOfSamePlaceSpObj( pSp->pSpObjQ->front.pNext, ( SP_OBJ * )pStartPoint ) ) ) {
							  tmpRectangle.pQNode_points[i]  =  tmppQNode;
							  pStartPoint  =  (  SP_POINT  *  )tmpRectangle.pQNode_points[i]->qElemMemory.m_pBuf;
							  }
						  else  {
							    pStartPoint->uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );
							    if  (  qPostMsg(  pStartPoint,  sizeof(  SP_POINT  ),  pSp->pSpObjQ,  _T(  "spProcLButtonUP 5"  )))  goto  errLabel;
								tmpRectangle.pQNode_points[i]  =  getpLastQNode(  pSp->pSpObjQ  );	
								tmpRectangle.bOwner_points[i]  =  TRUE;
						  }
						  i  =  2;
						  if  (  (  tmppQNode = findNextpQNodeOfSamePlaceSpObj( pSp->pSpObjQ->front.pNext, ( SP_OBJ * )pEndPoint ) ) ) {
							  tmpRectangle.pQNode_points[i]  =  tmppQNode;
							  pEndPoint  =  (  SP_POINT  *  )tmpRectangle.pQNode_points[i]->qElemMemory.m_pBuf;
							  }
						  else  {
							    pEndPoint->uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );
							    if  (  qPostMsg(  pEndPoint,  sizeof(  SP_POINT  ),  pSp->pSpObjQ,  _T(  "spProcLButtonUp 6" )))  goto  errLabel;
								tmpRectangle.pQNode_points[i]  =  getpLastQNode(  pSp->pSpObjQ  );	
								tmpRectangle.bOwner_points[i]  =  TRUE;
						  }
						  i  =  1;						  
						  memcpy(  &tmpSpPoint,  pSpRectangle->pQNode_points[i]->qElemMemory.m_pBuf,  sizeof(  tmpSpPoint  )  );
						  tmpSpPoint.point.rect.x  =  pEndPoint->point.rect.x;
						  tmpSpPoint.point.rect.y  =  pStartPoint->point.rect.y;
						  tmpSpPoint.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );
						  if  (  qPostMsg(  &tmpSpPoint,  sizeof(  SP_POINT  ),  pSp->pSpObjQ,  _T(  "spProcLButtonUp 8"  )))  goto  errLabel;
						  tmpRectangle.pQNode_points[i]  =  getpLastQNode(  pSp->pSpObjQ  );
						  tmpRectangle.bOwner_points[i]  =  TRUE;
						  i  =  3;
						  memcpy(  &tmpSpPoint,  pSpRectangle->pQNode_points[i]->qElemMemory.m_pBuf,  sizeof(  tmpSpPoint  )  );
						  tmpSpPoint.point.rect.x  =  pStartPoint->point.rect.x;
						  tmpSpPoint.point.rect.y  =  pEndPoint->point.rect.y;
						  tmpSpPoint.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );
						  if  (  qPostMsg(  &tmpSpPoint,  sizeof(  SP_POINT  ),  pSp->pSpObjQ,  _T(  "spProcLButtonUP 9"  )))  goto  errLabel;
						  tmpRectangle.pQNode_points[i]  =  getpLastQNode(  pSp->pSpObjQ  );
						  tmpRectangle.bOwner_points[i]  =  TRUE;

						  for  (  i  =  0;  i  <  mycountof(  tmpRectangle.pQNode_points  );  i  ++  )  {
							   pSpObj  =  (  SP_OBJ  *  )tmpRectangle.pQNode_points[i]->qElemMemory.m_pBuf;					
							   _sntprintf(  pSpObj->desc,  mycountof(  pSpObj->desc  ),  _T(  "rect.point %d"  ),  i  );
						  }							   

						  i  =  0;
						  makeSegment(  tmpRectangle.pQNode_points[i],  tmpRectangle.pQNode_points[(  i +  1  )  %  4],  tmpSegment  );
						  tmpSegment.ucbHorizontal  =  TRUE;		
						  tmpSegment.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );
						  if  (  qPostMsg( &tmpSegment, sizeof( SP_SEGMENT ),  pSp->pSpObjQ,  _T(  "spProcLButtonUP 3"  ))) goto  errLabel;
						  tmpRectangle.pQNode_segments[i]  =  getpLastQNode(  pSp->pSpObjQ  );
						  tmpRectangle.bOwner_segments[i]  =  TRUE;

						  i  ++  ;
						  makeSegment(  tmpRectangle.pQNode_points[i],  tmpRectangle.pQNode_points[(  i +  1  )  %  4],  tmpSegment  );
						  tmpSegment.ucbVertical  =  TRUE;
						  tmpSegment.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );
						  if  (  qPostMsg(  &tmpSegment,  sizeof(  SP_SEGMENT  ),  pSp->pSpObjQ,  _T(  "spProcLButtonUp 4"  )))  goto  errLabel;
						  tmpRectangle.pQNode_segments[i]  =  getpLastQNode(  pSp->pSpObjQ  );
						  tmpRectangle.bOwner_segments[i]  =  TRUE;

						  i  ++  ;
						  makeSegment(  tmpRectangle.pQNode_points[i],  tmpRectangle.pQNode_points[(  i +  1  )  %  4],  tmpSegment  );
						  tmpSegment.ucbHorizontal  =  TRUE;
						  tmpSegment.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );
						  if ( qPostMsg( &tmpSegment, sizeof( SP_SEGMENT ),  pSp->pSpObjQ,  _T(  "spProcLButtonUP 10"  ))) goto  errLabel;
						  tmpRectangle.pQNode_segments[i]  =  getpLastQNode(  pSp->pSpObjQ  );
						  tmpRectangle.bOwner_segments[i]  =  TRUE;

						  i  ++  ;
						  makeSegment(  tmpRectangle.pQNode_points[i],  tmpRectangle.pQNode_points[(  i +  1  )  %  4],  tmpSegment  );
						  tmpSegment.ucbVertical  =  TRUE;
						  tmpSegment.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSp->uiTranNo  );
						  if  (  qPostMsg(  &tmpSegment,  sizeof(  SP_SEGMENT  ),  pSp->pSpObjQ,  _T(  "spProcLButtonUp"  )))  goto  errLabel;
						  tmpRectangle.pQNode_segments[i]  =  getpLastQNode(  pSp->pSpObjQ  );
						  tmpRectangle.bOwner_segments[i]  =  TRUE;

						  for  (  i  =  0;  i  <  mycountof(  tmpRectangle.pQNode_segments  );  i  ++  )  {
							   //					
							   pSpObj  =  (  SP_OBJ  *  )tmpRectangle.pQNode_segments[i]->qElemMemory.m_pBuf;					
							   _sntprintf(  pSpObj->desc,  mycountof(  pSpObj->desc  ),  _T(  "rect.seg %d"  ),  i  );
						  }

						  if ( ( tmppQNode = findNextpQNodeOfSamePlaceSpObj( pSp->pSpObjQ->front.pNext, ( SP_OBJ * )&tmpRectangle ) ) ) goto  errLabel;

						  if  (  qPostMsg(  &tmpRectangle,  sizeof(  tmpRectangle  ),  pSp->pSpObjQ,  _T(  "spProcLButtonUp 1"  )))  goto  errLabel;

						  tmppQNode  =  getpLastQNode(  pSp->pSpObjQ  );
						  pSpObj  =  (  SP_OBJ  *  )tmppQNode->qElemMemory.m_pBuf;					
						  _sntprintf(  pSpObj->desc,  mycountof(  pSpObj->desc  ),  _T(  "rect"  )  );

						  tmpSelectQElem.pQNode = getpLastQNode( pSp->pSpObjQ );								
						  if ( qPostMsg( &tmpSelectQElem, sizeof( SP_SELECT_Q_ELEM ),  pSp->pSelectedSpObjQ,  _T(  "spProcLButtonUp2"  ))) goto  errLabel;
						
						  /* creating a segment succeeded */
					}
				else {
					 goto  errLabel;
				}
						
				break;
		  case  MOVE_OBJS_TRAN:
			    if ( pSp->sysStatus == STATUS_SELECT ) {
					if ( pPoint->x < 0 || pPoint->x > pSp->spWidth 
						|| pPoint->y < 0 || pPoint->y > pSp->spHeight ) 
					{
						logErr( "spProcLButtonDown():pPoint error" );
						goto  errLabel;
					}
					}
				else {
					 goto  errLabel;
				}
				break;

		  default:
				 pSp->errNo = -1;
				 break;
	 
	 }

	 if ( pSp->errNo ) goto errLabel; 

	 iErr  =  0;

errLabel: 

	 if ( iErr  ||  pSp->errNo ) {
		emptyGenericQ( pSp->pSelectedSpObjQ );		
	 }

	 exitTran( pSp );

	 return  iErr;
}


 __declspec(  dllexport  )  int  spProcMouseMove(  SP_STRUCT  *  pSp,  SP_RECT_COORD  *  pPoint,  unsigned  int  iFlags  )
{
	int			iErr	=	-1;
	int			i;

	#ifdef  __SP_DEBUG__
			debugLog( "spProcMouseMove()" );
	#endif
	
	switch  (  pSp->tranType  )  {
			case  NO_TRAN:
				  break;	
			case  CREATE_OBJS_TRAN:
				  if  (  pSp->sysStatus == STATUS_CREATE_A_POINT  )  {
					  Q_NODE *pPointQNode;
					  SP_POINT *pSpPoint;
					
					  if ( pPoint->x < 0 || pPoint->x > pSp->spWidth 
						  || pPoint->y < 0 || pPoint->y > pSp->spHeight ) 
					  {
						  goto  errLabel;
					  }
					  pPointQNode = getpLastQNode( pSp->pNewSpObjQ );
					  pSpPoint = ( SP_POINT * )pPointQNode->qElemMemory.m_pBuf;
					  pSpPoint->point.rect.x = pPoint->x;
					  pSpPoint->point.rect.y = pPoint->y;
					  }
				  else  if  (  pSp->sysStatus == STATUS_CREATE_A_SEGMENT ) {
						    Q_NODE *pSegmentNode;
							SP_SEGMENT *pSpSegment;
			
							if  (  pPoint->x < 0 || pPoint->x > pSp->spWidth 
								|| pPoint->y < 0 || pPoint->y > pSp->spHeight ) 
							{
								goto  errLabel;
							}

							pSegmentNode = getpLastQNode( pSp->pNewSpObjQ );
							pSpSegment = (  SP_SEGMENT  *  )pSegmentNode->qElemMemory.m_pBuf;

							( ( SP_POINT *)( ( Q_NODE * )pSpSegment->pEndQNode )->qElemMemory.m_pBuf )->point.rect.x = pPoint->x;
							( ( SP_POINT *)( ( Q_NODE * )pSpSegment->pEndQNode )->qElemMemory.m_pBuf )->point.rect.y = pPoint->y;
							pSpSegment->point2.rect.x = pPoint->x;
							pSpSegment->point2.rect.y = pPoint->y;
		
					  } /* end of STATUS_CREATE_A_SEGMENT */
				  else  if  (  pSp->sysStatus == STATUS_CREATE_A_CIRCLE ) {			
					        Q_NODE *pCircleNode;
							SP_CIRCLE *pSpCircle;
			
							if  (  pPoint->x < 0 || pPoint->x > pSp->spWidth 
								||  pPoint->y < 0 || pPoint->y > pSp->spHeight ) 					
							{
								goto  errLabel;
							}

							pCircleNode = getpLastQNode( pSp->pNewSpObjQ );
							pSpCircle = (  SP_CIRCLE  *  )pCircleNode->qElemMemory.m_pBuf;

							( ( SP_POINT *)( ( Q_NODE * )pSpCircle->pCircleQNode )->qElemMemory.m_pBuf )->point.rect.x = pPoint->x;
							( ( SP_POINT *)( ( Q_NODE * )pSpCircle->pCircleQNode )->qElemMemory.m_pBuf )->point.rect.y = pPoint->y;
			
					  } /* end of STATUS_CREATE_A_CIRCLE */
				  else  if  (  pSp->sysStatus  ==  STATUS_CREATE_A_RECTANGLE  )  {
						    Q_NODE *pQNode;
							SP_RECTANGLE *pSpRectangle;
			
							if  (  pPoint->x < 0 || pPoint->x > pSp->spWidth 
								||  pPoint->y < 0 || pPoint->y > pSp->spHeight ) 
							{
								goto  errLabel;
							}

							pQNode = getpLastQNode( pSp->pNewSpObjQ );
							pSpRectangle = (  SP_RECTANGLE  *  )pQNode->qElemMemory.m_pBuf;

							SP_SEGMENT	*	pSpSegment;
							i  =  0;
							pSpSegment  =  (  SP_SEGMENT  *  )pSpRectangle->pQNode_segments[i]->qElemMemory.m_pBuf;					
							if  (  pSpSegment->ucbHorizontal  )  {
								( ( SP_POINT *)( ( Q_NODE * )pSpSegment->pEndQNode )->qElemMemory.m_pBuf )->point.rect.x = pPoint->x;
								//  ( ( SP_POINT *)( ( Q_NODE * )pSpSegment->pEndQNode )->qElemMemory.m_pBuf )->point.rect.y = pPoint->y;
								pSpSegment->point2.rect.x = pPoint->x;
								//  pSpSegment->point2.rect.y = pPoint->y;
							}
							i  ++  ;
							pSpSegment  =  (  SP_SEGMENT  *  )pSpRectangle->pQNode_segments[i]->qElemMemory.m_pBuf;					
							if  (  pSpSegment->ucbVertical  )  {		
								( ( SP_POINT *)( ( Q_NODE * )pSpSegment->pEndQNode )->qElemMemory.m_pBuf )->point.rect.x = pPoint->x;						
								( ( SP_POINT *)( ( Q_NODE * )pSpSegment->pEndQNode )->qElemMemory.m_pBuf )->point.rect.y = pPoint->y;
								pSpSegment->point1.rect.x  =  (  (  SP_POINT  *  )pSpSegment->pStartQNode->qElemMemory.m_pBuf  )->point.rect.x;
								pSpSegment->point1.rect.y  =  (  (  SP_POINT  *  )pSpSegment->pStartQNode->qElemMemory.m_pBuf  )->point.rect.y;
								pSpSegment->point2.rect.x  =  pPoint->x;
								pSpSegment->point2.rect.y = pPoint->y;						     
							}
							i  ++  ;
							pSpSegment  =  (  SP_SEGMENT  *  )pSpRectangle->pQNode_segments[i]->qElemMemory.m_pBuf;					
							if  (  pSpSegment->ucbHorizontal  )  {
								//  ( ( SP_POINT *)( ( Q_NODE * )pSpSegment->pEndQNode )->qElemMemory.m_pBuf )->point.rect.x = pPoint->x;
								( ( SP_POINT *)( ( Q_NODE * )pSpSegment->pEndQNode )->qElemMemory.m_pBuf )->point.rect.y = pPoint->y;
								pSpSegment->point1.rect.x  =  (  (  SP_POINT  *  )pSpSegment->pStartQNode->qElemMemory.m_pBuf  )->point.rect.x;
								pSpSegment->point1.rect.y  =  (  (  SP_POINT  *  )pSpSegment->pStartQNode->qElemMemory.m_pBuf  )->point.rect.y;
								//  pSpSegment->point2.rect.x = pPoint->x;
								pSpSegment->point2.rect.y = pPoint->y;
							}
							i  ++  ;
							pSpSegment  =  (  SP_SEGMENT  *  )pSpRectangle->pQNode_segments[i]->qElemMemory.m_pBuf;
							if  (  pSpSegment->ucbVertical  )  {
								pSpSegment->point1.rect.x  =  (  (  SP_POINT  *  )pSpSegment->pStartQNode->qElemMemory.m_pBuf  )->point.rect.x;
								pSpSegment->point1.rect.y  =  (  (  SP_POINT  *  )pSpSegment->pStartQNode->qElemMemory.m_pBuf  )->point.rect.y;
							}
					
					  }
				  else {
					   goto  errLabel;
				  }

				  break;

			case  MOVE_OBJS_TRAN:
				  debugLog( "case MOVE_OBJS_TRAN:" );

				  if  (  pSp->sysStatus == STATUS_SELECT ) {
			
					  if  (  pPoint->x < 0 || pPoint->x > pSp->spWidth 			
						  ||  pPoint->y < 0 || pPoint->y > pSp->spHeight  ) 
					  {
						  goto  errLabel;						  
					  }
			
					  pSp->op = OP_MOVE;
					  pSp->tranParm.move.curPlace.x = pPoint->x;
					  pSp->tranParm.move.curPlace.y = pPoint->y;
					
					  if  (  preOpSp(  pSp  )  )  {
						  traceLogA(  "spProcMouseMove: preOpSp failed"  );
						  goto  errLabel;
					  }
					  		
					  #ifdef  __DEBUG__
							  printQ( pSp->pSpObjQ );
					  #endif
					
					  if ( opSp( pSp ) ) { 
						  debugLog( "opSp() failed" ); 
						  goto  errLabel;
					  }

					  resetOpSp( pSp );
					
					  pSp->tranParm.move.lastPlace.x = pPoint->x;
					  pSp->tranParm.move.lastPlace.y = pPoint->y;
					}
				  else  {					   
					    debugLog( "status = %d", pSp->sysStatus );
						goto  errLabel;			
				  }

				  debugLog( "case MOVE_OBJS_TRAN: break" );
				  break;

			case  DRAW_A_RGN_TRAN:
				  break;
			default:
				   goto  errLabel;
				   break;
 

	 } /* end of switch */

	 if ( pSp->errNo ) goto errLabel; 

	 iErr  =  0;

errLabel: 

	 if ( iErr  ||  pSp->errNo ) {
		 exitTran( pSp );
		 emptyGenericQ( pSp->pSelectedSpObjQ );
	 }
	 return  iErr;

}


 int spProcDisCmd( SP_STRUCT *pSp, int option )
{

	 switch ( pSp->tranType ) {

		case NO_TRAN:

			if ( pSp->sysStatus == STATUS_SELECT ) {

					switch ( option ) {

						case DISCMD_ANIMATE:

							if ( initTran( pSp, DISCMD_ANIMATE_TRAN ) ) {
								pSp->errNo = -1; break;
							}

							if ( spDisCmdAnimate( pSp ) ) {
								pSp->errNo = -1; break;
							}

							
							break;
					
						default:
						
							pSp->errNo = -1; 
							break;
					}

					if ( pSp->errNo ) break;

				}
			else {
				pSp->errNo = -1; break;
			}

			break;

		default:

			pSp->errNo = -1; break;

	 }

/* err: */

	 if ( pSp->errNo ) {
		 exitTran( pSp );
		 return -1;
	 }
	
	 return 0;

}


 int spProcConstruct( SP_STRUCT *pSp, int option )
{

	 switch ( pSp->tranType ) {

		case NO_TRAN:

			if ( pSp->sysStatus ==STATUS_CONSTRUCT ) {

					switch ( option ) {

						case CONSTRUCT_LINE:

							if ( initTran( pSp, CONSTRUCT_TRAN ) ) {
								pSp->errNo = -1; break;
							}
			
							if ( spConstructLine( pSp ) ) {
									pSp->errNo = -1; break;
							}

							break;
					
						case CONSTRUCT_PERPENDICULAR_LINE:

							if ( initTran( pSp, CONSTRUCT_TRAN ) ) {
								pSp->errNo = -1; break;
							}
			
							if ( spConstructPerpendicularLine( pSp ) ) {
									pSp->errNo = -1; break;
							}

							break;

						case CONSTRUCT_ANGLE_BISECTOR: 

							if ( initTran( pSp, CONSTRUCT_TRAN ) ) {
								pSp->errNo = -1; break;
							}
			
							if ( spConstructAngleBisector( pSp ) ) {
									pSp->errNo = -1; break;
							}
									
							break;

						case CONSTRUCT_HYPERBOLA: 

							if ( initTran( pSp, CONSTRUCT_TRAN ) ) {
								pSp->errNo = -1; break;
							}
			
							if ( spConstructHyperbola( pSp ) ) {
									pSp->errNo = -1; break;
							}
									
							break;

		
						default:
							
							pSp->errNo = -1;

							break;
								
					} /* end of switch ( option ) */
					
					if ( pSp->errNo ) break;
				
			} /* end of case STATUS_CONSTRUCT */

			else {

					pSp->errNo = -1;
					break;
			} 

			break; 

		default:

			pSp->errNo = -1;
			
			break;

	 } /* end of switch ( pSp->tranType ) */


/* err: */
	 
	 exitTran( pSp );

	 return 0;

}	

 int spProcTransform( SP_STRUCT *pSp, int option )
{
	 int iErr = 0;

	 switch ( option ) {
	 
		case MARK_CENTER:

			if ( spMarkCenter( pSp ) ) {
				
				iErr = -1; break;
			
			}

			break;

		case MARK_MIRROR:

			if ( spMarkMirror( pSp ) ) {

				iErr = -1; break;

			}

			break;	

		case TRANSLATE_TRANSFORM:

			if ( spTranslateTransform( pSp ) ) {

					iErr = -1; break;

			}

			break;
	
		case ROTATE_TRANSFORM:

			if ( spRotateTransform( pSp ) ) {

				iErr = -1; break;

			}

			break;

		case DILATE_TRANSFORM:

			if ( spDilateTransform( pSp ) ) {

				iErr = -1; break;

			}

			break;

		case REFLECT_TRANSFORM:

			if ( spReflectTransform( pSp ) ) {

				iErr = -1; break;

			}

			break;

		default:

			pSp->errNo = -1;

			iErr = -1;

			break;

	 }
	 
	 return iErr;

}


 __declspec(  dllexport  )  int  spProcKeyDelete(  SP_STRUCT  *  pSp,  unsigned  int  iFlags  )
{
	 int		iErr	=	-1;
	 Q_NODE	*	pQNode;

	 switch  (  pSp->tranType  )  {
			 case  NO_TRAN:
				   if ( !( pQNode = pSp->pSelectedSpObjQ->front.pNext ) ) break;

				   if ( initTran( pSp, DELETE_TRAN ) ) goto  errLabel;
				   
				   pSp->op = OP_DELETE;
				   if ( preOpSp( pSp ) ) goto  errLabel;
				   if ( opSp( pSp ) ) goto  errLabel;
		
				   break;

		default:

				goto  errLabel;
				break;

	 }

	 iErr  =  0;

errLabel:

	 exitTran( pSp );

	 return  iErr;

}
 

 
 
