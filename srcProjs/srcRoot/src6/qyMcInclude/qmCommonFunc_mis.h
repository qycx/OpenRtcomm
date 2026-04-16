

#ifndef  __QMCOMMONFUNCMIS_H__
#define  __QMCOMMONFUNCMIS_H__  //  {


#define		CONST_ver_0148								"0148"		//  Õâ°æÒÔÇ°¶¼ÊÇansi, ÒÔºó¶¼ÊÇutf8¸ñÊ½µÄ
#define		CONST_qyColsStr_qyImGrpInfoTab_0148			_T(  "idStr,misServName,name,startTime,tLastModifiedTime,col0,col1,col2,col3,col4,comment0"  )


//  2017/08/14
#define		CONST_ver_0149								"0149"

//
#define		CONST_qyColsStr_qyImObjAuthTab_0149			_T(  "idStr,misServName,uiType,mac0,mac1,mac2,otherMacs,nMacs,pcName,domainName,osUsrName,messengerName,messengerPasswd,ip,iStatus,startTime,tLastModifiedTime,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,col11,col12,col13,col14,col15,col16,col17,col18,col19,col20,col21,col22,col23,col24,col25,col26,col27,col28,col29,comment0"  )
//
#define		CONST_qyColsStr_qyImObjTab_0149				_T(  "idStr,misServName,uiType,ip,detectedIp,clientVer,usLangId,uiDevType,messengerName,usRunningStatus,startTime,tLastModifiedTime,tLastGrpDeletedTime,tLastMemDeletedTime,iStatus"  )


//
#define		CONST_qyColsStr_qyImObjAuthTab				_T(  "idStr,misServName,uiType,mac0,mac1,mac2,otherMacs,nMacs,pcName,domainName,osUsrName,messengerName,messengerPasswd,ip,iRole,iStatus,startTime,tLastModifiedTime,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,col11,col12,col13,col14,col15,col16,col17,col18,col19,col20,col21,col22,col23,col24,col25,col26,col27,col28,col29,comment0"  )

//
//#define		CONST_qyColsStr_qyImAmTab					_T(  "misServName,idStr,messengerName,messengerPasswd,iPasswdType,salt,iStatus,startTime,tLastModifiedTime,comment0"  )		//  2010/01/06
#define		CONST_qyColsStr_qyImAmTab					_T(  "misServName,idStr,usAuthType,messengerName,messengerPasswd,iPasswdType,salt,iStatus,startTime,tLastModifiedTime,comment0"  )		//  2010/01/06
//
#define		CONST_qyColsStr_qyImObjRegInfoTab			_T(  "misServName,idStr,regTime,auditTime,tLastModifiedTime,tCommitTime,bOk,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,col11,col12,col13,col14,col15,col16,col17,col18,col19,col20,col21,col22,col23,col24,col25,col26,col27,col28,col29,comment0"  )



//  2014/02/03
//#define		CONST_qyColsStr_qyImGrpInfoTab_0149				_T(  "idStr,misServName,name,subtype,startTime,tLastModifiedTime,col0,col1,col2,col3,col4,comment0"  )
#define		CONST_qyColsStr_qyImGrpInfoTab				_T(  "idStr,misServName,name,subtype,idStr_creator,startTime,tLastModifiedTime,col0,col1,col2,col3,col4,comment0"  )


//
#define		CONST_qyColsStr_qyImGrpMemTab				_T(  "misServName,idStr_grp,idStr_mem,iRole,startTime,tLastModifiedTime,iStatus,comment0"  )

//
#define		CONST_qyColsStr_qyImObjTab					_T(  "idStr,misServName,uiType,ip,detectedIp,clientVer,usLangId,uiDevType,messengerName,iRole,usRunningStatus,startTime,tLastModifiedTime,tLastGrpDeletedTime,tLastMemDeletedTime,iStatus"  )

//
#define		CONST_qyColsStr_qyImTaskTab					_T(  "misServName,idStr_send,senderDesc,tSendTime,uiTranNo,uiSerialNo,idStr_recv,receiverDesc,tRecvTime,usRespCode,ibReply,uiType,uiMode,subTypeStr,subject,content0,content1,content2,content3,content4,content5,content6,content7,content8,content9,txtContent0,txtContent1,txtContent2,txtContent3,txtContent4,txtContent5,txtContent6,txtContent7,txtContent8,txtContent9,ibNeedReply,tEndTime,issuer,tIssueTime,tStartTime_req,uiTranNo_req,firstTime,lastTime,iStatus,tLastModifiedTime,idStr_auditor,idStr_replyTo,iProp0,iProp1,iProp2,iProp3,iProp4,iProp5,iProp6,iProp7,iProp8,iProp9,propStr0,propStr1,propStr2,propStr3,propStr4,propStr5,propStr6,propStr7,propStr8,propStr9,comment0"  )
//
#define		CONST_qyColsStr_qyImObjRuleTab				_T(  "idStr,misServName,idStr_related,uiRuleType,usIndex,uiCmd,startTime,tLastModifiedTime,iStatus,iCol0,iCol1,iCol2,iCol3,iCol4,iCol5,iCol6,iCol7,iCol8,iCol9,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,comment0"  )
//
#define		CONST_qyColsStr_qyWebContactTab				_T(  "misServName,idStr,ucbPublic,grpDisplayName,displayName,ucbDefault,ucbImSwitchable,startTime,tLastModifiedTime,iStatus,comment0"  )
#define		CONST_qyColsStr_qyIpKnowledgeTab			_T(  "uiType,startIp,endIp,wLocation,iWeight,startTime,endTime,tLastModifiedTime,iStatus,comment0"  )
//
#define		CONST_qyColsStr_qyMessengerPhoneInfoTab		_T(  "misServName,uiDevType,wDevIdStr,messengerPasswd,idStr,iStatus,startTime,tLastModifiedTime,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,comment0"  )
#define		CONST_qyColsStr_qySmContactTab				_T(  "misServName,idStr,wDevIdStr,ucbDefaultSmServer,cusName,ucbPublic,idStr_contact,displayName,ucbDefault,ucbImSwitchable,iStatus,startTime,endTime,comment0"  )
//
#define		CONST_qyColsStr_qyPhoneGuestTab				_T(  "misServName,uiDevType,wDevIdStr,messengerPasswd,idStr_owner,iStatus,startTime,tLastModifiedTime,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,comment0"  )
#define		CONST_qyColsStr_qyImOtherRegInfoTab			_T(  "misServName,uiDevType,wDevIdStr,regTime,auditTime,tLastModifiedTime,tCommitTime,bOk,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,comment0"  )
//

#define		CONST_qyColsStr_qyDynBmpTab					_T(  "misServName,idStr,uiObjType,usIndex,name,cusname,iStatus,startTime,endTime"  )
//  #define		CONST_qyColsStr_qyDynBmpRuleTab			_T(  "misServName,idStr,idStr_visitor,uiRuleType,iStatus,startTime,endTime,comment0"  )
#define		CONST_qyColsStr_qyDynBmpRuleTab				_T(  "misServName,idStr,idStr_visitor,uiRuleCmd,iStatus,startTime,endTime,comment0"  )



//
//
#define		CONST_iDataType_time					SQL_VARCHAR
//
#define		CONST_iDataType_misServName				SQL_WVARCHAR
#define		CONST_iDataType_idStr					SQL_VARCHAR
#define		CONST_iDataType_subTypeStr				SQL_WVARCHAR
#define		CONST_iDataType_subject					SQL_WVARCHAR
#define		CONST_iDataType_content					SQL_WVARCHAR
#define		CONST_iDataType_messengerName			SQL_WVARCHAR
#define		CONST_iDataType_desc					SQL_WVARCHAR
#define		CONST_iDataType_name					SQL_WVARCHAR
//
#define		CONST_iDataType_wDevIdStr				SQL_WVARCHAR
//
#define		CONST_iDataType_model					SQL_WVARCHAR
#define		CONST_iDataType_smsc					SQL_WVARCHAR
					  




///////
//
//
//#define		CONST_uiMaxCnt_semaTrigger_mgrQ_isCli				1110
#define		CONST_uiMaxQNodes_mgrQ_isCli						1100
//
#define		CONST_uiMaxCnt_semaTrigger_mgrQ_isMgr				111
#define		CONST_uiMaxQNodes_mgrQ_isMgr						110

//
#define		CONST_uiMaxQNodes_inCacheQ_isCli					10									//  2008/04/02

//
//#define		CONST_uiMaxQNodes_inputQ_isCli						200									//  2008/04/02


//  #define		CONST_uiMaxCnt_semaTrigger_toSendQ_256				40									//  2008/05/23
#define		CONST_uiMaxQNodes_toSendQ_256						20									//  2008/05/23
//
//  #define		CONST_uiMaxCnt_semaTrigger_toSendQ_xp				50									//  2008/05/23
#define		CONST_uiMaxQNodes_toSendQ_xp						40									//  2008/05/23
//
//  #define		CONST_uiMaxCnt_semaTrigger_toSendQ					140									//  2008/05/23
#define		CONST_uiMaxQNodes_toSendQ							120									//  2008/05/23
#define		CONST_uiQNodes_warningInterval_toSendQ				10									//  200811/22

//  #define		CONST_uiMaxCnt_semaTrigger_outputQ_256				20
#define		CONST_uiMaxQNodes_outputQ_256						10
//
//  #define		CONST_uiMaxCnt_semaTrigger_outputQ_xp				40									//  Êý¾ÝÓÐµÄ¿ÉÒÔÍ¨¹ýtoSendQÈ»ºóÔÙ·¢ËÍ£¬ÓÐµÄÍ¨¹ýoutputQÖ±½Ó·¢ËÍ 2008/10/29
#define		CONST_uiMaxQNodes_outputQ_xp						30
//
//  #define		CONST_uiMaxCnt_semaTrigger_outputQ					80									//  Êý¾ÝÓÐµÄ¿ÉÒÔÍ¨¹ýtoSendQÈ»ºóÔÙ·¢ËÍ£¬ÓÐµÄÍ¨¹ýoutputQÖ±½Ó·¢ËÍ 2008/10/29
#define		CONST_uiMaxQNodes_outputQ							60

//
#define		CONST_uiMaxCnt_semaTrigger_workQ					210
#define		CONST_uiMaxQNodes_workQ								200
//
#define		CONST_uiMaxCnt_semaTrigger_displayQ					620
#define		CONST_uiMaxQNodes_displayQ							600
//
#define		CONST_uiMaxCnt_semaTrigger_schedulerQ				310
#define		CONST_uiMaxQNodes_schedulerQ						300
//
#define		CONST_uiMaxCnt_semaTrigger_robotQ					210									//  2007/07/04
#define		CONST_uiMaxQNodes_robotQ							200


//
#define		CONST_uiQNodes_warningInterval_mediaQ				10									//  2008/03/21				


//
#define		CONST_uiMaxQNodes_playSoundQ_256					CONST_uiMaxQNodes_playSoundQ		//  2008/03/15
#define		CONST_uiMaxQNodes_playVideoQ_256					30									//  2012/11/09
#define		CONST_uiMaxQNodes_displayVideoQ_256					30									//  2012/11/09
//
#define		CONST_uiMaxQNodes_playSoundQ						100		//  2017/10/14	//  60									//  2008/03/15
#define		CONST_uiMaxQNodes_playVideoQ						120		//  150							//  2009/05/05
#define		CONST_uiMaxQNodes_displayVideoQ						60									//  2009/07/25

//
#define		CONST_uiMaxQNodes_transformQ_256					CONST_uiMaxQNodes_transformQ		//  2008/05/12
#define		CONST_uiMaxQNodes_transformQ						200									//  120									//  2016/08/29	//  100									//  2008/05/12

//
#define		CONST_uiMaxQNodes_saveQ								1000								//  2024/10/21

//
#define		CONST_uiMaxQNodes_mixQ								15

//  
#define		CONST_uiMaxQNodes_aecQ								15

//
#define		CONST_uiMaxQNodes_appQ								100									//  2017/01/29
//  
#define		CONST_uiMaxQNodes_vppQ								100									//  2011/12/04

#define		CONST_uiMaxQNodes_toSaveIcQ_256					CONST_uiMaxQNodes_toSaveIcQ		
#define		CONST_uiMaxQNodes_toSaveIcQ						100	

//
#define		CONST_uiMaxQNodes_toShareAudioQ_256					CONST_uiMaxQNodes_toShareAudioQ		//  2011/01/21
#define		CONST_uiMaxQNodes_toShareAudioQ						100									//  2011/01/21
#define		CONST_uiMaxQNodes_toShareVideoQ_256					CONST_uiMaxQNodes_toShareVideoQ		//  2011/01/21
#define		CONST_uiMaxQNodes_toShareVideoQ						100									//  2011/01/21

//
#define		CONST_uiMaxQNodes_toShareVideo_postQ				100									//  2011/12/06

//
#define		CONST_uiMaxQNodes_dispatchQ							100									//  2009/06/17

//
#define		CONST_uiMaxQNodes_talkerThreadQ						100									//  2016/03/15
//
#define		CONST_uiMaxQNodes_shareDynBmpsQ						100									//  2016/03/15


//
#define		CONST_uiMaxQNodes_processQ_robot					300									//  2007/07/04
#define		CONST_uiMaxQNodes_processQ_media					310									//  2008/03/15

#define		CONST_uiMaxQNodes_outputQ_toMix_audio_256			30									//  2008/05/23
//
#define		CONST_uiMaxQNodes_outputQ_toMix_audio_xp			50									//  2008/05/23
//
#define		CONST_uiMaxQNodes_outputQ_toMix_audio				256									//  2017/10/14	//  80									//  2008/05/23

#define		CONST_uiMaxQNodes_outputQ_toMosaic_video			256									//  2010/09/18

//
#define		CONST_uiMaxQNodes_guestQ							5000								//  2008/01/18
#define		CONST_uiMaxQNodes_guestQ_ce							0									//  2010/04/15
//
#if  0
#ifdef  __DEBUG__
	    #define		CONST_uiMaxQNodes_phoneMsgrQ				15									//  2008/01/18
#else
	    #define		CONST_uiMaxQNodes_phoneMsgrQ				15000								//  2008/01/18
#endif
#define		CONST_uiMaxQNodes_phoneMsgrQ_ce						0									//  2010/04/15
#endif

#define		CONST_uiMaxQNodes_dynBmpQ							256									//  2009/09/05

#define		CONST_uiMaxQNodes_tmpGrpMemQ						5000								//  2008/01/22

//
#if  0
	#define	CONST_uiMaxQNodes_talkingFriendQ					100									//  
#endif
#define		CONST_uiMaxQNodes_talkingFriendQ					1000								//  2012/05/07

//  #define		CONST_uiMaxQNodes_recentFriendQ					200									//  
#define		CONST_uiMaxQNodes_recentFriendQ						5000								//  2014/02/11. 当messenger很多时，比如几千点时，需要本参数大一点，否则在线状态无法尽快获取


//
//#define		DEFAULT_uiSizePerSnd_file_avExists				(  64  *  1024  )					//  2014/07/13 
//#define		DEFAULT_uiSizePerSnd_file_noAv					(  128  *  1024  )					//  2014/07/13 
#define		DEFAULT_uiSizePerSnd_file_avExists					(  900  *  1024  )					//  2014/07/13 
#define		DEFAULT_uiSizePerSnd_file_noAv						(  900  *  1024  )					//  2014/07/13 
//
#define		MIN_uiSizePerSnd_file								(  256  *  1024  )	


//
#define		MIN_uiSizePerSnd_media								(  62  *  1024  )					//  2008/04/01
#define		MAX_uiSizePerSnd_media								(  CONST_dataBufSize_iocp  -  1024  )	//  2008/04/01

//  
//#define		DEFAULT_uiSizePerSnd_media_isMgr					(  128  *  1024  )					//  2011/02/13
#define		DEFAULT_uiSizePerSnd_media_isMgr					(  512  *  1024  )					//  2011/02/13
//#define		DEFAULT_uiSizePerSnd_media_isCli					(  128  *  1024  )					//  
#define		DEFAULT_uiSizePerSnd_media_isCli					(  512  *  1024  )					//  

//
#define		DEFAULT_usNeedShowFrameInfoIntervalInS				(  30  )							//  

#define		MAX_ucSeconds_perFrame								5									//  
//  #define		DEFAULT_usFps_toShareBmp							5									//  
//



#define		MAX_usFps_toShareBmp								60									//  2011/12/10


//
#define		MAX_uiMinTimeInMsOfAudioDataPlaying					1600								//  2009/06/14
#define		MIN_uiMinTimeInMsOfAudioDataPlaying					100

#define		MAX_uiAudioDataAddedToPlayEveryTime					2000								//  2009/06/14
#define		MIN_uiAudioDataAddedToPlayEveryTime					80				

#define		MAX_uiNotifyIntervalInMs_needMoreAudioData			200									//  
#define		MIN_uiNotifyIntervalInMs_needMoreAudioData			40			

#define		MAX_uiMinTimeInMsToPlay								10000								//  2012/01/27
#define		MAX_uiMaxTimeInMsToPlay								64000								//  2009/06/03

#define		MAX_uiMaxTimeInMsToBeRemoved						64000								//  2009/06/03



//////////////////////


#define		MAX_failures_frames_perSecond						5									//  ÌáÉýÖ¡ËÙµÄ×î¶à¿ÉÔÊÐíÊ§°Ü´ÎÊý
//
#define		MAX_ucTimeoutInS_showFrameInfoResp					30									//  ÏÂ´«Ö¡ËÙÐÅÏ¢µÄÏìÓ¦×îÐ¡³¬Ê±,²»ÄÜµÍÓÚ´ËÖµ


//
#define		CONST_usIntervalInS_getIntervalParams				30									//  È¡²ÎÊýÅäÖÃ£¬ 30
#define		CONST_usIntervalInS_refreshRecentFriends			20									//  Ë¢ÐÂ×î½üÁªÏµÈË×´Ì¬µÄ¼ä¸ô, 20
#define		CONST_usIntervalInS_refreshContactList				120									//  Ë¢ÐÂÁªÏµÈËÃûµ¥µÄ¼ä¸ô, 120

//
#define		CONST_usIntervalInS_tryToReg						30									//  2007/07/31
#define		CONST_usIntervalInS_tryToSndDevInfo					30									//  2007/08/03

//
#define		CONST_mutexName_guiProcessQ							_T(  "qyIsGProcQ"  )

#if  0
#define		CONST_mutexName_guiGuiQ								_T(  "qyIsGGuiQ"  )
#define		CONST_maxQNodes_guiGuiQ								30
#endif

#define		CONST_mutexName_gpsQ								_T(  "qGpsQ"  )						//  2012/04/20
#define		CONST_maxQNodes_gpsQ								50


#define		DEFAULT_maxDisplayedElemsPerWnd						5000								//  2007/06/09
//
#define		DEFAULT_maxDisplayedWnds							50									//  2007/06/10
//
#define		DEFAULT_maxDisplayedTasksInDlgTalk					100									//  dlgTalk, 2007/06/26


#define		DEFAULT_iTimeoutInMs_channelIdle_others				10000								//  2009/02/25
//#define		DEFAULT_iTimeoutInMs_channelIdle_recv_others		30000								//  2011/01/31
#define		DEFAULT_iTimeoutInMs_channelIdle_recv_talk			300000								//  2011/01/31

//
//  2009/12/21
//#define		CONST_qmCmdLine_av									_T(  "av"  )
//#define		CONST_qmCmdLine_mediaFile							_T(  "mediaFile"  )

//
#define		CONST_qmCmdLine_mcu									_T(  "mcu="  )

//  
#define		CONST_qmCmdLine_server								_T(  "server="  )
#define		CONST_qmCmdLine_port								_T(  "port="  )

//
#define		CONST_qmCmdLine_user								_T(  "u="  )
#define		CONST_qmCmdLine_passwd								_T(  "p="  )


//  2014/02/09
#define		CONST_qmCmdLine_sym_appObjPrefix					_T(  "qm="  )

//  2015/02/02
#define		CONST_qmCmdLine_sym_tn								_T(  "tn="  )

//  2015/02/17
#define		CONST_qmCmdLine_sym_tag								_T(  "tag="  )

//  2015/10/04
#define		CONST_qmCmdLine_pktResType_suggested				_T(  "prt="  )

//  2015/04/28
#define		CONST_qmCmdLine_sym_noDvt							_T(  "noDvt"  )
//  2015/10/28
#define		CONST_qmCmdLine_sym_noEvt							_T(  "noEvt"  )

//  2016/04/26
#define		CONST_qmCmdLine_sym_dbgDvt							_T(  "dbgDvt"  )
#define		CONST_qmCmdLine_sym_dbgEvt							_T(  "dbgEvt"  )
//
#define		CONST_qmCmdLine_sym_dbgOnvif						_T(  "dbgOnvif"  )



//
#define		CONST_qmCmdLine_confServer							_T(  "confServer="  )

//
#define		CONST_qmCmdLine_fileServer							_T(  "fileServer="  )


//
#ifdef  __DEBUG__
		//  2015/07/18. 用test=跟个号，来区分不同的运行路径，调试用
		#define		CONST_qmCmdLine_sym_test					_T(  "test="  )

#endif


//
typedef  struct  __tranInfo_mis_t								{
				 //
				 unsigned  int									uiMaxSendMsgs;						//  2011/01/23
				 //
				 unsigned  int									nNodes_processed;					//  messenger->iocp
				 time_t											tNow;
				 unsigned  int									uiTranNo;
				 unsigned  int									uiCliIndex;
				 void								*			pQMem;

				 BOOL											bNeedRemoveMsg;						//  2008/04/02, daemon doMisMgr_sendFinished(  ) remove
				 BOOL											bNotResendMsg;						//  2008/05/15, media rtMedia, msg
				 //
				 MIS_MSGU							*			pMsg_o;								//  sendFinished buf
				 //
				 TCHAR											whereBuf_showInfo[64];				//  2015/09/04

				 //
				 int											cnt_tmpHandler_doMisMgr_sendFinished;

				 //
				 struct			{
					int											nNodes_outputQ2;
					bool										bCs;
					//
					DWORD										dwTickCnt_7523;
					DWORD										dwTickCnt_7564;
					DWORD										dwTickCnt_7638;
					//
					int											cnt;

					//
					bool										bDbg;

					//
					QY_MESSENGER_ID								idInfo;
					int											tn;
					DWORD										dwTickCnt_before_q2GetMsg;

					//
					struct										{
						DWORD									dwTickCnt_6787;
						unsigned  int							uiMsgType;
						//
						int										grp_usCnt;
						//
					}											tmpHandler_doMisMgr_sendFinished;

				 }												dbg;

}		 TRAN_INFO_MIS; 










//  BOOL  bGetMessengerAuthRcdBySth(  void  *  pDbParam,  int  iDbType,  QY_imAm_RCD  *  pImAm,  POLICY_imAuthCond  *  pAuthCond,  QY_COMM_AUTHINFO_MIS  *  pAuthInfo,  int  iRcdId,  QY_MESSENGERAUTH_RCD  *  pObj  );
BOOL  bGetMessengerAuthRcdBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  POLICY_imAuthCond  *  pAuthCond,  QY_COMM_AUTHINFO_MIS  *  pAuthInfo,  int  iRcdId,  QY_MESSENGERAUTH_RCD  *  pObj  );
BOOL  bGetMessengerAuthTmpRcdBySth(  void  *  pDbParam,  int  iDbType,  POLICY_imAuthCond  *  pAuthCond,  QY_COMM_AUTHINFO_MIS  *  pAuthInfo,  QY_MESSENGERAUTHTMP_RCD  *  pObj  );
//  BOOL  bGetImAmRcdBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  LPCTSTR  messengerName,  int  id,  QY_imAm_RCD  *  pObj  );

int  putNewMessengerIntoTmpTab(  void  *  pLicenseCtx,  void  *  pDbParam,  int  iDbType,  POLICY_imAuthCond  *  pAuthCond,  QY_COMM_AUTHINFO_MIS  *  pAuthInfo,  unsigned  int  uiObjType  );
// 
//  int  auditNewMessenger(  void  *  pReserved,  QY_MESSENGER_ID  *  pLastIdInfo,  void  *  pLicenseCtx,  void  *  pDb,  int  iDbType,  POLICY_imAuthCond  *  pAuthCond,  QY_MESSENGERAUTHTMP_RCD  *  pNewMessenger  );
int  auditNewImGrp(  void  *  pReserved,  QY_MESSENGER_ID  *  pLastIdInfo,  void  *  pLicenseCtx,  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo  );

//  2012/01/30
//  int  insertImObj(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_INFO  *  pObj  );
//  int  updateImObj(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_INFO  *  pObj,  int  iRcdId  );

//
//  BOOL  bGetMeInfoBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_INFO  *  pObj  );
//  BOOL  bGetMessengerInfoBySth(  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  QY_MESSENGER_INFO  *  pObjParam,  QY_MESSENGER_REGINFO  *  pRegInfo,  QY_MESSENGER_REGINFO  *  pRegInfoInTab1,  QY_MESSENGER_phoneInfo  *  pPhoneInfo  );		//  2008/12/28ÐÞ¸Ä
//  BOOL  bGetMessengerRegInfoBySth(  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  pTabName,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  QY_MESSENGER_REGINFO  *  pRegInfo  );		//2008/12/28
//  BOOL  bGetImOtherRegInfoBySth(  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  pTabName,  MSGR_ADDR  *  pAddr,  int  iRcdId,  QY_MESSENGER_REGINFO  *  pRegInfo  );	//  2008/12/28

//  2010/08/13
//  BOOL  bGetImObjRuleRcdBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem  *  pMem,  int  iRcdId,  QY_imObjRule_rcd  *  pRcd  );
//  BOOL  bGetImObjRulesReq(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  QY_MESSENGER_ID	*	pIdInfo_related,  LPCTSTR  condPart,  unsigned  short  usMaxMemsPerSnd,  REFRESH_imObjRules_req  *  pReq  );

//
//  BOOL	bGetMessengerPhoneInfoBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  unsigned  int  uiDevType,  LPCTSTR  wDevIdStr,  QY_MESSENGER_ID  *  pIdInfo,  int  id,  QY_MESSENGER_phoneInfo  *  pRcd  );
//
BOOL  bGetMessengerPcInfoBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  QY_MESSENGER_PCINFO  *  pRcd  );
__declspec(  dllexport  )  int  recoverMessenger(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QY_MESSENGER_INFO  *  pObj,  QY_MESSENGER_REGINFO  *  pRegInfo,  time_t tLastModifiedTime,  BOOL  bLog,  GENERIC_Q  *  pLogQ  );

//  2010/08/16
__declspec(  dllexport  )  int  recoverImObjRules(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRules_req	*	pReq,  time_t  tLastModifiedTime  );

 
//  
 __declspec(  dllexport  )  int  recoverImGrp(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime,  BOOL  bNoGrpName  );


//  BOOL  bGetImGrpMemBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo_grp,  QY_MESSENGER_ID  *  pIdInfo_mem,  int  iRcdId,  IM_GRP_MEM  *  pRcd  );

BOOL  bGetCustomerServiceObjRcdBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  CUSTOMER_serviceObj_rcd  *  pRcd  );
BOOL  bGetWebContactRcdBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  WEB_CONTACT_RCD  *  pRcd  );

 __declspec(  dllexport  )  int  recoverImGrpMem(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  time_t  tLastModifiedTime  );

//
__declspec(  dllexport  )  int  enumImTasks(  void  *  pDb,  int  iDbType,  BOOL  bHisTab,  LPCTSTR  misServName,  LPCTSTR  whereClause,  PF_commonHandler  pf,  void  *  p0,  void  *  p1,  unsigned  int  *puiRcdCnt,  IM_TASK_RCD  *  pTaskRcd  );
//  BOOL  bGetImTaskRcdBySth(  void  *  pDb,  int  iDbType,  BOOL  bHisTab,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  time_t  tSendTime,  unsigned  int  uiTranNo,  int  id,  IM_TASK_RCD  *  pRcd  );

//  BOOL  bGetImMsgRcdBySth(  void  *  pDbParam,  int  iDbType,  int  id,  IM_MSG_RCD  *  pObj  );


//  int  qisRegUsrInfo(  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QY_MESSENGER_INFO  *  pMessengerInfo,  QY_MESSENGER_REGINFO  *  pRegInfo,  BOOL  bLogReRegEvent  );	//  2008/12/28
int  qisRegUsrInfoInTab(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QY_MESSENGER_INFO  *  pMessengerInfo,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  tabName  );	//  2008/12/28

//  int  recoverMessengerPhoneInfo(  void  *  pDb,  int  iDbType,  MSGR_ADDR  *  pAddr,  void  *  p1  );
//
//  int  qisRegOtherInfoInTab(  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  MSGR_ADDR  *  pAddr,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  tabName  );
//


BOOL  bGetQyVDevComRcdBySth(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  WCHAR  *  wDevIdStr,  int  id,  QY_VDEVCOM_RCD  *  pRcd  );
BOOL  bGetQySmContactRcdBySth(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  WCHAR  *  wDevIdStr,  unsigned  char  ucbDefaultSmServer,  int  id,  QY_SMCONTACT_RCD  *  pRcd  );

//  BOOL  bGetQyDynBmpRcdBySth(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  uiObjType,  unsigned  short  usIndex,  int  id,  QY_dynBmp_RCD  *  pRcd  );
BOOL  bGetQyDynBmpRuleRcdBySth(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  QY_MESSENGER_ID  *  pIdInfo_visitor,  int  id,  QY_dynBmpRule_RCD  *  pRcd  );

int  postImMsg2Log_isMgr(  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo_send,  LPCTSTR  senderDesc,  time_t  tSendTime,  unsigned  int  uiTranNo,  QY_MESSENGER_ID  *  pIdInfo_recv,  LPCTSTR  receiverDesc,  unsigned  int  uiContentType,  LPCTSTR  content,  LPCTSTR  txtContent,  time_t  tRecvTime,  GENERIC_Q  *  pLogQ  );
__declspec(  dllexport  )  int  postImMsg2Log_isClient(  MIS_MSGU  *  pMsg,  int  lenInBytes_msg  );

__declspec(  dllexport  )  int  logImMsg(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  void  *  pDBManager,  QY_DMITEM  *  pFieldIdTable,  IM_MSG_RCD  *  pRcd  );
#ifdef  __WINCE__
		int  logImMsg_ce(  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  IM_MSG_RCD  *  pRcd  );
#endif


int  postEvent2Log_is(  LPCTSTR  misServName,  long  lEventType,  char  *  detectedIp,  char  *  ip,  QY_MESSENGER_ID  *  pIdInfo,  QIS_EVENT  *  pEventInput,  GENERIC_Q  *  pLogQ  );
//  BOOL  bLogEventFunc_is(  void  *  pDb,  int  iDbType,  QIS_EVENT  *  pEvent  );
__declspec(  dllexport  )  int  logEvent_is(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_MESSENGER_INFO  *  pMessengerInfo,  QIS_EVENT  *  pEvent  );



//  GUI
__declspec(dllexport)void  dlgTalk_PostNcDestroy(  void  *pm_var_param  );

//  2012/05/12
int  tryToTalkToMessenger(HWND  hParent, void* pMSGR_ADDR, int  iTalkUsage, int iTalkSubtype, BOOL  bActivateWnd, HWND  hVWall, int  iWndContentType_hVWall, HWND* phWnd);

//  
int  tryToTalkToMessenger_id(HWND hParent, unsigned  __int64  ui64Id,  int  iTalkSubtype,  BOOL  bActivateWnd,  HWND  hVWall,  int  iWndContentType_hVWall,  HWND	*	phWnd  );

//
int  tryToTalkToMessenger_any(HWND hParent, unsigned  __int64  ui64Id,  int  iTalkSubtype,  BOOL  bNeedNotShowWnd,  BOOL  bActivateWnd,  HWND  *  phWnd  );

//  2016/09/08
 int  doApplyForPlayer(  QY_MC  *  pQyMc,  HWND  hMainWnd,  MIS_MSGU  *  pMsg  );
 int  myWaitForQThread_infinite(  QY_qThreadProcInfo_common  *  pQThread,  LPCTSTR  hint  );


//
int  old_doSth_afterInitDlgTalk(  HWND  hDlgTalk,  int  iWndContentType  );
int  doSth_afterInitDlgMsgTool(  QY_MC  *  pQyMc,  HWND  hDlgMsgTool,  int  iWndContentType  );

 
//
__declspec(  dllexport  )  int  broadcastRecorderStatus(  void  *  pQyMcParam  );


//
int  closeAllConversations(  LPVOID  pQyMcParameter,  BOOL  *  pbConversationExists  );

int  setModalWnd(  QY_MC  *  pQyMc,  HWND  hDlg  );
int  setModalWnd_func(  QY_MC  *  pQyMc,  HWND  hDlg,  BOOL  bFileDialog  );


BOOL bDlgTalkAbove(  HWND hWnd  );
  //BOOL bDlgTalkAbove_wall(  HWND  hDlgWalls,  HWND hWnd  );

BOOL  bMainWndAbove( QY_MC  *  pQyMc, HWND  hWnd  );

extern  "C"  int  qyShowHint1(  HWND  hWnd,  LPCTSTR  fmt,  ...  );

//
__declspec(  dllexport  )  int  delPcSth(  void  *  pDb,  LPCTSTR  hint,  LPCTSTR  tabName,  LPCTSTR  whereClause  );
__declspec(  dllexport  )  int  delImObj(  void  *  pDb,  int  iDbType,  BOOL  bClient,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  );






#endif  //  }



