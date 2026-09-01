

#include	"stdafx.h"

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	"qyFile.h"

#include	"myresource.h"

#include	"qmcVWall.h"
//  #include	"DlgDynBmps.h"

#include	"qyCusResTemp.h"

#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"


 __declspec(  dllexport  )   BOOL  bQisExportVWall(  void  *  pCQyVWall,  void  *  pQY_IMEXPORTINFO  )
{
	 BOOL				bRet			=	FALSE;
	 QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	 CQyVWall		*  pWall  =  (  CQyVWall  *  )pCQyVWall;
	 QY_IMEXPORTINFO  *  pExportInfo  =  (  QY_IMEXPORTINFO  *  )pQY_IMEXPORTINFO;

	 CQyFile			file;
	 BOOL				bFileOpen		=	FALSE;
	 QY_DMITEM		*	pItem			=	NULL;
	 char				timeBuf[CONST_qyTimeLen  +  1];
	 char				hVerBuf[CONST_qyMaxVerLen  +  1];
	 char				buf[1024];
	 

	 if  (  !file.Open(  CString(  pExportInfo->fileName  ).GetBuffer(  0  ),  CFile::modeCreate | CFile::modeWrite  )  )  goto  errLabel;
	 bFileOpen  =  TRUE;

	 try  {
		  //  先写题头
		  file.bExportCls(  CONST_qyFileCls_file  );
		  file.bExportObj(  CONST_qyFileObj_name,  CONST_qyFileObjName_qvwBak  );
		  file.bExportObj(  CONST_qyFileObj_customId,  qyGetCustomId(  )  );
		  _snprintf(  hVerBuf,  sizeof(  hVerBuf  ),  "%04d",  atol(  CONST_qvwVer_is  )  /  100  );
		  file.bExportObj(  CONST_qyFileObj_ver,  hVerBuf  );
		  getCurTime(  timeBuf  );
		  file.bExportObj(  CONST_qyFileObj_createTime,  timeBuf  );
		  //
		  myTChar2Utf8(  pWall->m_var.title,  buf,  mycountof(  buf  )  );
		  file.bExportObj(  CONST_qyFileObj_title,  buf  );
		  //
		  file.bExportObj(  CONST_qyFileObj_comment,  "Note: Don't modify this file."  );	//  严禁修改文件内容，否则将破坏数据的正确性"  );
		  file.bExportObj(  CONST_qyFileObj_end  );

		  file.writeEndLine(  );
		  file.writeEndLine(  );
		  file.writeEndLine(  );

		  file.bExportCls(  CONST_qyFileCls_data  );

		  int  i;
		  for  (  i  =  0;  i  <  pWall->m_var.usCnt;  i  ++  )  {
			   SUB_V_WALL	*	pSubWall	=	pWall->getSubWall(  i  );
			   if  (  !pSubWall  )  goto  errLabel;
			   Q_NODE		*	pQNode;
		
			   file.bExportObj(  CONST_qyFileObj_name,  CONST_qyFileObjName_subWall  );
			   
			   myTChar2Utf8(  pSubWall->fileName_background,  buf,  mycountof(  buf  )  );
			   file.bExportObj(  CONST_qyFileObj_background,  buf  );		
			   file.bExportData(  "%s=%d,%d,%d,%d",  CONST_qyFileObj_rect_org,  pSubWall->iX_org,  pSubWall->iY_org,  pSubWall->iW_org,  pSubWall->iH_org  );
			   file.writeEndLine(  );
			   //
			   file.bExportObj(  CONST_qyFileObj_name,  CONST_qyFileObjName_cad  );
			   SP_STRUCT	*	pSp  =  (  SP_STRUCT  *  )pSubWall->pSp;
			   for  (  pQNode  =  pSp->pSpObjQ->front.pNext;  pQNode  &&  pQNode->qElemMemory.m_pBuf;  pQNode  =  pQNode->pNext  )  {
				    SP_OBJ	*	pSpObj	=	(  SP_OBJ  *  )pQNode->qElemMemory.m_pBuf;
					file.bExportData(  "%s=%d,%d,%d:",	CONST_qyFileObj_cadObj,  pSpObj->type,  pSpObj->subType,  pSpObj->uiTranNo  );
					switch  (  pSpObj->type  )  {
						    case  SP_POINT_TYPE:
								  switch  (  pSpObj->subType  )  {
										  case  SP_GENERIC_POINT_TYPE:  {
											    SP_POINT	*	pPoint  =  (  SP_POINT  *  )pSpObj;
												file.bExportData(  "%S=%d,%d:",  qyGetDesByType1(  CONST_qyPropTypeTable,  CONST_qyPropType_pos  ),  pPoint->point.rect.x,  pPoint->point.rect.y  );
												}
											    break;
										  default:
											      traceLogA(  "Not finished: bQisExportVWall: type %d, subType %d",  pSpObj->type,  pSpObj->subType  );
											      break;
								  }
								  break;
							case  SP_SEGMENT_TYPE:
								  switch  (  pSpObj->subType  )  {
										  case  SP_GENERIC_SEGMENT_TYPE:  {
											    SP_SEGMENT  *	pSegment  =  (  SP_SEGMENT  *  )pSpObj;
												SP_POINT	*	pPoint0	=	(  SP_POINT  *  )pSegment->pStartQNode->qElemMemory.m_pBuf;
												SP_POINT	*	pPoint1	=	(  SP_POINT  *  )pSegment->pEndQNode->qElemMemory.m_pBuf;
												file.bExportData(  "%S=%d,%d:",  qyGetDesByType1(  CONST_qyPropTypeTable,  CONST_qyPropType_dep  ),  pPoint0->uiTranNo,  pPoint1->uiTranNo  );  
												if  (  pSegment->ucbHorizontal  )  file.bExportData(  "%S=1:",  qyGetDesByType1(  CONST_qyPropTypeTable,  CONST_qyPropType_horz  )  );
												if  (  pSegment->ucbVertical  )  file.bExportData(  "%S=1:",  qyGetDesByType1(  CONST_qyPropTypeTable,  CONST_qyPropType_vert  )  );
												}											    
											    break;
										  default:
											      traceLogA(  "Not finished: bQisExportVWall: type %d, subType %d",  pSpObj->type,  pSpObj->subType  );
											      break;
								  }
								  break;
							case  SP_RECTANGLE_TYPE:  
								  switch  (  pSpObj->subType  )  {
										  case  SP_GENERIC_RECTANGLE_TYPE:  {
											    SP_RECTANGLE	*	pRectangle  =  (  SP_RECTANGLE  *  )pSpObj;
												SP_OBJ			*	p;
												int					j;
												buf[0]  =  0;
												for  (  j  =  0;  j  <  mycountof(  pRectangle->pQNode_points  );  j  ++  )  {
													 p  =  (  SP_OBJ  *  )pRectangle->pQNode_points[j]->qElemMemory.m_pBuf;
													 if  (  !j  )  _snprintf(  buf,  mycountof(  buf  ),  "%d",  p->uiTranNo  );
													 else  _snprintf(  buf,  mycountof(  buf  ),  "%s,%d",  buf,  p->uiTranNo  );
												}
												for  (  j  =  0;  j  <  mycountof(  pRectangle->pQNode_segments  );  j  ++  )  {
													 p  =  (  SP_OBJ  *  )pRectangle->pQNode_segments[j]->qElemMemory.m_pBuf;
													 _snprintf(  buf,  mycountof(  buf  ),  "%s,%d",  buf,  p->uiTranNo  );
												}
												file.bExportData(  "%S=%s:",  qyGetDesByType1(  CONST_qyPropTypeTable,  CONST_qyPropType_dep  ),  buf  );
												}
											    break;
										  default:
												  break;
								  }
								  break;
							default:
								    traceLogA(  "Not finished: bQisExportVWall: type %d, subType %d",  pSpObj->type,  pSpObj->subType  );
									break;
					}
					file.writeEndLine(  );
			   }
			   file.bExportObj(  CONST_qyFileObj_end  );

			   //  
			   file.bExportObj(  CONST_qyFileObj_name,  CONST_qyFileObjName_vwRules  );
			   for  (  pQNode  =  pSubWall->pRuleQ->front.pNext;  pQNode  &&  pQNode->qElemMemory.m_pBuf;  pQNode  =  pQNode->pNext  )  {
				    VW_ruleU	*	pRule	=	(  VW_ruleU  *  )pQNode->qElemMemory.m_pBuf;
					file.bExportData(  "%s=%d,%d:",	CONST_qyFileObj_vwRule,  pRule->common.uiType,  pRule->common.uiTranNo_spObj  );
					switch  (  pRule->common.uiType  )  {
							case  CONST_vwRuleType_dynBmp:
								file.bExportData(  "%S=%I64u,%d,%d:",  qyGetDesByType1(  CONST_qyPropTypeTable,  CONST_qyPropType_dynBmp  ),  pRule->dynBmp.ruleDynBmp.dynBmp.idInfo.ui64Id,  pRule->dynBmp.ruleDynBmp.dynBmp.resObj.uiObjType,  pRule->dynBmp.ruleDynBmp.dynBmp.resObj.usIndex_obj  );
								  //  2014/08/08
								  if  (  pRule->dynBmp.ruleDynBmp.ucbSaveVideo  )  {
									  file.bExportData(  "%S=1:",  qyGetDesByType1(  CONST_qyPropTypeTable,  CONST_qyPropType_save  )  );
								  }
								  break;
							case  CONST_vwRuleType_conference_imGrp:
								  file.bExportData(  "%S=%I64u",  qyGetDesByType1(  CONST_qyPropTypeTable,  CONST_qyPropType_imGrp  ),  pRule->conference_imGrp.idInfo.ui64Id  );
								  break;
							case  CONST_vwRuleType_conference_imGrpMem:
								  file.bExportData(  "%S=%I64u",  qyGetDesByType1(  CONST_qyPropTypeTable,  CONST_qyPropType_messenger  ),  pRule->conference_imGrpMem.idInfo.ui64Id  );
								  break;
							case  CONST_vwRuleType_messenger:
								  file.bExportData(  "%S=%I64u:",  qyGetDesByType1(  CONST_qyPropTypeTable,  CONST_qyPropType_messenger  ),  pRule->messenger.idInfo.ui64Id  );
								  QIS_dynBmp_info	dynBmp;
								  //  if  (  pRule->messenger.cmd.ucbViewScreen  )  
								  if  (  tmpF_bViewRemoteVideo(  &pRule->messenger.cmd,  CONST_objType_screen,  CONST_usIndex_screen0,  0  )  )  
								  {
									  memset(  &dynBmp,  0,  sizeof(  dynBmp  )  );
									  dynBmp.qisResObj.resObj.uiObjType  =  CONST_objType_screen;
									  dynBmp.qisResObj.resObj.usIndex_obj  =  0;
									  file.bExportData(  "%S=%I64u,%d,%d:",  qyGetDesByType1(  CONST_qyPropTypeTable,  CONST_qyPropType_dynBmp  ),  dynBmp.qisResObj.idInfo.ui64Id,  dynBmp.qisResObj.resObj.uiObjType,  dynBmp.qisResObj.resObj.usIndex_obj  );							  
								  }
								  //  if  (  pRule->messenger.cmd.ucbViewWebcam0  )  
								  if  (  tmpF_bViewRemoteVideo(  &pRule->messenger.cmd,  CONST_objType_webcam,  CONST_usIndex_webcam0,  0  )  )  
								  {
									  memset(  &dynBmp,  0,  sizeof(  dynBmp  )  );
									  dynBmp.qisResObj.resObj.uiObjType  =  CONST_objType_webcam;
									  dynBmp.qisResObj.resObj.usIndex_obj  =  0;
									  file.bExportData(  "%S=%I64u,%d,%d:",  qyGetDesByType1(  CONST_qyPropTypeTable,  CONST_qyPropType_dynBmp  ),  dynBmp.qisResObj.idInfo.ui64Id,  dynBmp.qisResObj.resObj.uiObjType,  dynBmp.qisResObj.resObj.usIndex_obj  );							  
								  }
								  //  if  (  pRule->messenger.cmd.ucbViewWebcam1  )  
								  if  (  tmpF_bViewRemoteVideo(  &pRule->messenger.cmd,  CONST_objType_webcam,  CONST_usIndex_webcam1,  0  )  )  
								  {
									  memset(  &dynBmp,  0,  sizeof(  dynBmp  )  );
									  dynBmp.qisResObj.resObj.uiObjType  =  CONST_objType_webcam;
									  dynBmp.qisResObj.resObj.usIndex_obj  =  1;
									  file.bExportData(  "%S=%I64u,%d,%d:",  qyGetDesByType1(  CONST_qyPropTypeTable,  CONST_qyPropType_dynBmp  ),  dynBmp.qisResObj.idInfo.ui64Id,  dynBmp.qisResObj.resObj.uiObjType,  dynBmp.qisResObj.resObj.usIndex_obj  );							  
								  }
								  //  if  (  pRule->messenger.cmd.ucbViewWebcam2  )  
								  if  (  tmpF_bViewRemoteVideo(  &pRule->messenger.cmd,  CONST_objType_webcam,  CONST_usIndex_webcam2,  0  )  )  
								  {
									  memset(  &dynBmp,  0,  sizeof(  dynBmp  )  );
									  dynBmp.qisResObj.resObj.uiObjType  =  CONST_objType_webcam;
									  dynBmp.qisResObj.resObj.usIndex_obj  =  2;
									  file.bExportData(  "%S=%I64u,%d,%d:",  qyGetDesByType1(  CONST_qyPropTypeTable,  CONST_qyPropType_dynBmp  ),  dynBmp.qisResObj.idInfo.ui64Id,  dynBmp.qisResObj.resObj.uiObjType,  dynBmp.qisResObj.resObj.usIndex_obj  );							  
								  }
								  if  (  pRule->messenger.cmd.ucbViewGps  )  {		//  gps不用存,因为有gps墙来决定的
								  }
								  break;
							case  CONST_vwRuleType_talkers:		//  2012/05/17
								  break;
							case  CONST_vwRuleType_walls:		//  2016/06/01
								  break;
							default:
								    #ifdef  __DEBUG__
										    traceLogA(  "bQisExportVWall: unknown ruleType %d",  pRule->common.uiType  );
											MACRO_qyAssert(  0,  _T(  "bQisExportVWall failed"  )  );								    
									#endif
								    break;
					}
					file.writeEndLine(  );
			   }
			   file.bExportObj(  CONST_qyFileObj_end  );
		  
			   file.bExportObj(  CONST_qyFileObj_end  );
		  }

		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bQisExportVWall failed."  )  );
		   goto  errLabel;
	}

	 bRet  =  TRUE;

errLabel:

	 if  (  bFileOpen  )  file.Close(  );

	 return  bRet;

}

BOOL  bQisImportCad(  CQyFile  &  file,  CQyVWall  *  pWall  )
{
	BOOL				bRet	=	FALSE;
	char				objName[256];
	char				buf[2048];
	SP_OBJ				spObj;
	SP_STRUCT	*		pSp		=	(  SP_STRUCT  *  )pWall->getCurSp(  );
	int					i;
	int					j;
	
	while  (  TRUE  )  {
		   if  (  !file.bGetNextLine(  objName,  mycountof(  objName  ),  buf,  mycountof(  buf  )  )  )  goto  errLabel;
		   if  (  !_stricmp(  objName,  CONST_qyFileObj_end  )  )  break;

		   QY_props		props;
		   memset(  &props,  0,  sizeof(  props  )  );

		   if  (  !_stricmp(  objName,  CONST_qyFileObj_cadObj  )  ){
			   char  *  p,  *  p1;
			   memset(  &spObj,  0,  sizeof(  spObj  )  );
			   spObj.type  =  atol(  buf  );
			   if  (  !(  p1  =  strchr(  buf,  ','  )  )  )  continue;
			   p1  ++  ;
			   spObj.subType  =  atol(  p1  );
			   if  (  !(  p1  =  strchr(  p1,  ','  )  )  )  continue;
			   p1  ++  ;
			   spObj.uiTranNo  =  atol(  p1  );
			   if  (  !(  p  =  strchr(  p1,  ':'  )  )  )  continue;
			   p  ++  ;

			   switch  (  spObj.type  )  {
					   case  SP_POINT_TYPE:
						     switch  (  spObj.subType  )  {
									 case  SP_GENERIC_POINT_TYPE:  {
										   SP_POINT		spPoint;
										   memset(  &spPoint,  0,  sizeof(  spPoint  )  );
										   memcpy(  &spPoint,  &spObj,  sizeof(  spObj  )  );
										   if  (  myGetProps_vw(  p,  &props  )  )  goto  errLabel;
										   if  (  !props.usCnt  )  goto  errLabel;
										   if  (  props.mems[0].uiType  !=  CONST_qyPropType_pos  )  goto  errLabel;
										   spPoint.point.rect.x  =  props.mems[0].u.pos.coord.x;
										   spPoint.point.rect.y  =  props.mems[0].u.pos.coord.y;
										   if  (  qPostMsg(  &spPoint,  sizeof(  spPoint  ),  pSp->pSpObjQ,  _T(  "bQisImporgCad"  )))  goto  errLabel;
										   }
										   break;
									 default:
											 break;
							 }
						     break;
					   case  SP_SEGMENT_TYPE:
						     switch  (  spObj.subType  )  {
								     case  SP_GENERIC_SEGMENT_TYPE:  {
										   SP_SEGMENT	spSegment;
										   memset(  &spSegment,  0,  sizeof(  spSegment  )  );
										   memcpy(  &spSegment,  &spObj,  sizeof(  spObj  )  );
										   //
										   if  (  myGetProps_vw(  p,  &props  )  )  goto  errLabel;
										   if  (  !props.usCnt  )  goto  errLabel;
										   for  (  i  =  0;  i  <  props.usCnt;  i  ++  )  {
											    switch  (  props.mems[i].uiType  )  {
														case  CONST_qyPropType_horz:
															  spSegment.ucbHorizontal  =  TRUE;
															  break;
														case  CONST_qyPropType_vert:
															  spSegment.ucbVertical  =  TRUE;
															  break;
													    case  CONST_qyPropType_dep:
															  if  (  props.mems[i].u.dep.usCnt  !=  2 )  goto  errLabel;
															  spSegment.pStartQNode  =  findSpQNode(  pSp,  props.mems[i].u.dep.uiTranNo_spObjs[0]  );
															  spSegment.pEndQNode  =  findSpQNode(  pSp,  props.mems[i].u.dep.uiTranNo_spObjs[1]  );
															  break;
														default:
																break;
												}
										   }
										   if  (  !spSegment.pStartQNode  ||  !spSegment.pEndQNode  )  goto  errLabel;
										   if  (  qPostMsg(  &spSegment,  sizeof(  spSegment  ),  pSp->pSpObjQ,  _T(  "bQisImportCad 1" )))  goto  errLabel;
										   //
										   }
										   break;
									 default:
											break;
							 }

						     break;
					   case  SP_RECTANGLE_TYPE:
						     switch  (  spObj.subType  )  {
								     case  SP_GENERIC_RECTANGLE_TYPE:  {
										   SP_RECTANGLE  spRectangle;
										   memset(  &spRectangle,  0,  sizeof(  spRectangle  )  );
										   memcpy(  &spRectangle,  &spObj,  sizeof(  spObj  )  );
										   //
										   if  (  myGetProps_vw(  p,  &props  )  )  goto  errLabel;

										   if  (  !props.usCnt  )  goto  errLabel;
										   for  (  i  =  0;  i  <  props.usCnt;  i  ++  )  {
											    switch  (  props.mems[i].uiType  )  {
													    case  CONST_qyPropType_dep:
															  if  (  props.mems[i].u.dep.usCnt  !=  8  )  goto  errLabel;
															  for  (  j  =  0;  j  <  4;  j  ++  )  {
																   spRectangle.pQNode_points[j]  =  findSpQNode(  pSp,  props.mems[i].u.dep.uiTranNo_spObjs[j]  );
															  }
															  for  (  j  =  4;  j  <  8;  j  ++  )  {
																   spRectangle.pQNode_segments[j  -  4]  =  findSpQNode(  pSp,  props.mems[i].u.dep.uiTranNo_spObjs[j]  );															
															  }

															  break;
														default:
																break;
												}
										   }
										   for  (  i  =  0;  i  <  mycountof(  spRectangle.pQNode_points  );  i  ++  )  {
											    if  (  !spRectangle.pQNode_points[i]  )  goto  errLabel;
										   }
										   for  (  i  =  0;  i  <  mycountof(  spRectangle.pQNode_segments  );  i  ++  )  {
											    if  (  !spRectangle.pQNode_segments[i]  )  goto  errLabel;
										   }
										   if  (  qPostMsg(  &spRectangle,  sizeof(  spRectangle  ),  pSp->pSpObjQ,  _T(  "bQisImporgCad 2"  )))  goto  errLabel;
									       }
										   break;
									 default:
										     break;
							 }
							 break;
					   default:						       
							   break;
			   }

			   continue;
		   }

	}

	Q_NODE	*	pQNode;
	pSp->uiTranNo  =  0;
	for  (  pQNode  =  pSp->pSpObjQ->front.pNext;  pQNode  &&  pQNode->qElemMemory.m_pBuf;  pQNode  =  pQNode->pNext  )  {
		 SP_OBJ  *  pSpObj  =  (  SP_OBJ  *  )pQNode->qElemMemory.m_pBuf;
		 pSp->uiTranNo  =  max(  pSp->uiTranNo,  pSpObj->uiTranNo  );		 
	}
	pSp->uiTranNo  ++  ;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


 BOOL  bQisImportVwRules(  CQyFile  &  file,  CQyVWall  *  pWall  )
{
	BOOL				bRet		=	FALSE;
	char				objName[256];
	char				buf[2048];
	VW_ruleU			rule;
	SUB_V_WALL	*		pSubWall	=	pWall->getCurSubWall(  );
	SP_STRUCT	*		pSp			=	(  SP_STRUCT  *  )pWall->getCurSp(  );
	int  i;

	
	while  (  TRUE  )  {
		   if  (  !file.bGetNextLine(  objName,  mycountof(  objName  ),  buf,  mycountof(  buf  )  )  )  goto  errLabel;
		   if  (  !_stricmp(  objName,  CONST_qyFileObj_end  )  )  break;

		   QY_props		props;
		   memset(  &props,  0,  sizeof(  props  )  );

		   if  (  !_stricmp(  objName,  CONST_qyFileObj_vwRule  )  ){
			   char  *  p,  *  p1;
			   memset(  &rule,  0,  sizeof(  rule  )  );
			   rule.common.uiType  =  atol(  buf  );
			   if  (  !(  p1  =  strchr(  buf,  ','  )  )  )  continue;
			   p1  ++  ;
			   rule.common.uiTranNo_spObj  =  atol(  p1  );
			   if  (  !(  p  =  strchr(  p1,  ':'  )  )  )  continue;
			   p  ++  ;

			   if  (  !findSpQNode(  pSp,  rule.common.uiTranNo_spObj  )  )  goto  errLabel;

			   switch  (  rule.common.uiType  )  {
					   case  CONST_vwRuleType_dynBmp:
						     if  (  myGetProps_vw(  p,  &props  )  )  goto  errLabel;
							 if  (  !props.usCnt  )  goto  errLabel;
							 if  (  props.mems[0].uiType  !=  CONST_qyPropType_dynBmp  )  goto  errLabel;
							 
							 rule.dynBmp.ruleDynBmp.dynBmp.idInfo.ui64Id  =  props.mems[0].u.dynBmp.idInfo.ui64Id;
							 rule.dynBmp.ruleDynBmp.dynBmp.resObj.uiObjType  =  props.mems[0].u.dynBmp.uiObjType;
							 rule.dynBmp.ruleDynBmp.dynBmp.resObj.usIndex_obj  =  props.mems[0].u.dynBmp.usIndex_obj;

							 //  2014/08/08
							 for  (  i  =  1;  i  <  props.usCnt;  i  ++  )  {
								  switch  (  props.mems[i].uiType  )  {
										  case  CONST_qyPropType_save:
											    rule.dynBmp.ruleDynBmp.ucbSaveVideo  =  TRUE;											    
											    break;
										  default:
												  break;
								  }
							 }						

							 //
							 if  (  qPostMsg(  &rule,  sizeof(  rule  ),  pSubWall->pRuleQ,  _T(  "bQisImporgVwRules"  )))  goto  errLabel;
						     break;
					   case  CONST_vwRuleType_conference_imGrp:
						     if  (  myGetProps_vw(  p,  &props  )  )  goto  errLabel;
							 if  (  !props.usCnt  )  goto  errLabel;
							 if  (  props.mems[0].uiType  !=  CONST_qyPropType_imGrp  )  goto  errLabel;
							 
							 rule.conference_imGrp.idInfo.ui64Id  =  props.mems[0].u.imGrp.idInfo.ui64Id;
						
							 if  (  qPostMsg(  &rule,  sizeof(  rule  ),  pSubWall->pRuleQ,  _T(  "bQisImporgVWRules 3"  )))  goto  errLabel;
						     break;
					   case  CONST_vwRuleType_conference_imGrpMem:
						     if  (  myGetProps_vw(  p,  &props  )  )  goto  errLabel;
							 if  (  !props.usCnt  )  goto  errLabel;
							 if  (  props.mems[0].uiType  !=  CONST_qyPropType_messenger  )  goto  errLabel;
							 
							 rule.conference_imGrpMem.idInfo.ui64Id  =  props.mems[0].u.messenger.idInfo.ui64Id;
						
							 if  (  qPostMsg(  &rule,  sizeof(  rule  ),  pSubWall->pRuleQ,  _T(  "bQisImporgVwRules 3"  )))  goto  errLabel;
						     break;
					   case  CONST_vwRuleType_talkers:	//  2012/04/10
						     if  (  qPostMsg(  &rule,  sizeof(  rule  ),  pSubWall->pRuleQ,  _T(  "bQisImportVwRules 4"  )))  goto  errLabel;
						     break;
					   case  CONST_vwRuleType_walls:	//  2016/06/01
						     if  (  qPostMsg(  &rule,  sizeof(  rule  ),  pSubWall->pRuleQ,  _T(  "bQisImportVwRules 5"  )))  goto  errLabel;
						     break;						     
					   case  CONST_vwRuleType_messenger:
						     if  (  myGetProps_vw(  p,  &props  )  )  goto  errLabel;
							 if  (  !props.usCnt  )  goto  errLabel;
							 if  (  props.mems[0].uiType  !=  CONST_qyPropType_messenger  )  goto  errLabel;
							 
							 rule.messenger.idInfo.ui64Id  =  props.mems[0].u.messenger.idInfo.ui64Id;

							 for  (  i  =  1;  i  <  props.usCnt;  i  ++  )  {
								  switch  (  props.mems[i].uiType  )  {
										  case  CONST_qyPropType_dynBmp:
											    QIS_dynBmp_info	dynBmp;
												memset(  &dynBmp,  0,  sizeof(  dynBmp  )  );
												dynBmp.qisResObj.idInfo.ui64Id  =  props.mems[i].u.dynBmp.idInfo.ui64Id;
												dynBmp.qisResObj.resObj.uiObjType  =  props.mems[i].u.dynBmp.uiObjType;
												dynBmp.qisResObj.resObj.usIndex_obj  =  props.mems[i].u.dynBmp.usIndex_obj;
												if  (  dynBmp.qisResObj.resObj.uiObjType  ==  CONST_objType_screen  )  {
													//  rule.messenger.cmd.ucbViewScreen  =  TRUE;
													tmpF_setViewRemoteVideo(  CONST_objType_screen,  CONST_usIndex_screen0,  FALSE,  TRUE,  &rule.messenger.cmd  );
													}
												else  if  (  dynBmp.qisResObj.resObj.uiObjType  ==  CONST_objType_webcam  )  {
													      switch  (  dynBmp.qisResObj.resObj.usIndex_obj  )  {
																  case  0:
																	     //  rule.messenger.cmd.ucbViewWebcam0  =  TRUE;
																	     tmpF_setViewRemoteVideo(  CONST_objType_webcam,  CONST_usIndex_webcam0,  FALSE,  TRUE,  &rule.messenger.cmd  );
																		 break;
																  case  1:
																	     //  rule.messenger.cmd.ucbViewWebcam1  =  TRUE;
																	     tmpF_setViewRemoteVideo(  CONST_objType_webcam,  CONST_usIndex_webcam1,  FALSE,  TRUE,  &rule.messenger.cmd  );
																	     break;
																  case  2:
																	     //  rule.messenger.cmd.ucbViewWebcam2  =  TRUE;
																	     tmpF_setViewRemoteVideo(  CONST_objType_webcam,  CONST_usIndex_webcam2,  FALSE,  TRUE,  &rule.messenger.cmd  );
																		 break;
																  default:
																		 break;
														  }
												}
											    break;
										  default:
												  break;
								  }
							 }
						
							 if  (  qPostMsg(  &rule,  sizeof(  rule  ),  pSubWall->pRuleQ,  _T(  "bQisImportVwRules 6"  )))  goto  errLabel;
						     break;
					   default:		
							   #ifdef  __DEBUG__
									   traceLog(  _T(  "bQisImportVwRules, unknown type %d"  ),  rule.common.uiType  );
									   MACRO_qyAssert(  0,  _T(  "bQisImportVwRules"  )  );
							   #endif
							   break;
			   }
		   }

	}

	bRet  =  TRUE;
errLabel:
	return  bRet;
}



 BOOL  bQisImportSubWall(  CQyFile  &  file,  CQyVWall  *  pWall  )
{
	BOOL				bRet	=	FALSE;
	char				objName[256];
	char				buf[2048];
	SUB_V_WALL		*	pSubWall	=	pWall->getCurSubWall(  );

	while  (  TRUE  )  {
		   if  (  !file.bGetNextLine(  objName,  mycountof(  objName  ),  buf,  mycountof(  buf  )  )  )  goto  errLabel;
		   if  (  !_stricmp(  objName,  CONST_qyFileObj_end  )  )  break;

		   if  (  !_stricmp(  objName,  CONST_qyFileObj_background  )  )  {
			   myUtf82TChar(  buf,  pSubWall->fileName_background,  mycountof(  pSubWall->fileName_background  )  );
			   continue;
		   }
		   //  2011/10/18
		   if  (  !_stricmp(  objName,  CONST_qyFileObj_rect_org  )  )  {
			   char  *  p1;
			   pSubWall->iX_org  =  atol(  buf  );
			   if  (  !(  p1  =  strchr(  buf,  ','  )  )  )  continue;
			   p1  ++  ;
			   pSubWall->iY_org  =  atol(  p1  );
			   if  (  !(  p1  =  strchr(  p1,  ','  )  )  )  continue;
			   p1  ++  ;
			   pSubWall->iW_org  =  atol(  p1  );
			   if  (  !(  p1  =  strchr(  p1,  ','  )  )  )  continue;
			   p1  ++  ;
			   pSubWall->iH_org  =  atol(  p1  );
			   continue;
		   }


		   if  (  !_stricmp(  objName,  CONST_qyFileObj_name  )  ){
			   if  (  !_stricmp(  buf,  CONST_qyFileObjName_cad  )  ){
				   if  (  !bQisImportCad(  file,  pWall  )  )  goto  errLabel;
				   continue;
			   }
			   if  (  !_stricmp(  buf,  CONST_qyFileObjName_vwRules  )  )  {
				   if  (  !bQisImportVwRules(  file,  pWall  )  )  goto  errLabel;
				   continue;
			   }
		   }

	}

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


  __declspec(  dllexport  )  BOOL  bQisImportVWall(  void  *  pQY_IMEXPORTINFO,  void  *  pCQyVWall  )
{
	 BOOL				bRet			=		FALSE;
	 QY_MC			*	pQyMc			=		QY_GET_GBUF(  );
	 QY_IMEXPORTINFO  *  pImportInfo	=	(  QY_IMEXPORTINFO  *  )pQY_IMEXPORTINFO;
	 CQyVWall  *  pWall  =  (  CQyVWall  *  )pCQyVWall;


	 CQyFile			file;
	 BOOL				bFileOpen		=		FALSE;
	 char				ver[32  +  1];
	 char				objName[256];
	 char				buf[2048];
	 
	 //
	 if  (  !file.Open(  CString(  pImportInfo->fileName  ).GetBuffer(  0  ),  CFile::modeRead  )  )  goto  errLabel;
	 bFileOpen  =  TRUE;

	 //
	 try  {
		  BOOL  bFileOk  =  FALSE;
		  while  (  TRUE  )  {
			     if  (  !file.bGetNextLine(  objName,  mycountof(  objName  ),  buf,  mycountof(  buf  )  )  )  goto  errLabel;
				 
			     if  (  !_stricmp(  objName,  CONST_qyFileObj_end  )  )  break;
				 
				 if  (  !_stricmp(  objName,  CONST_qyFileObj_name  )  )  {
					 if  (  _stricmp(  buf,  CONST_qyFileObjName_qvwBak  )  )  goto  errLabel;
					 bFileOk  =  TRUE;
				 }
				 if  (  !_stricmp(  objName,  CONST_qyFileObj_ver  )  )  {
					 _snprintf(  ver,  mycountof(  ver  ),  "%s",  buf  );
				 }
				 if  (  !_stricmp(  objName,  CONST_qyFileObj_title  )  )  {
					 myUtf82TChar(  buf,  pWall->m_var.title,  mycountof(  pWall->m_var.title  )  );
				 }
		  }
		  if  (  !bFileOk  )  goto  errLabel;

		  SUB_V_WALL		*	pSubWall		=		pWall->getCurSubWall(  );
		  pWall->resetSubWall(  pWall->m_var.curSpIndex  );

		  while  (  TRUE  )  {
			     if  (  !file.bGetNextLine(  objName,  mycountof(  objName  ),  buf,  sizeof(  buf  )  )  )  goto  errLabel;
				 
				 if  (  !_stricmp(  objName,  CONST_qyFileObj_end  )  )  break;
				 
				 if  (  !_stricmp(  objName,  CONST_qyFileObj_name  )  )  {
					 if  (  !_stricmp(  buf,  CONST_qyFileObjName_subWall  )  )  {
						 if  (  !bQisImportSubWall(  file,  pWall  )  )  goto  errLabel;
						 continue;
					 }


				 }

		  }

		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bQnmImportBakData failed."  )  );
		   goto  errLabel;
	}

	 bRet  =  TRUE;

errLabel:
	 
	 if  (  bFileOpen  )  file.Close(  );

	 return  bRet;
}
