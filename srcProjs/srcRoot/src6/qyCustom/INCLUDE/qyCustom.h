

#ifndef  __QYCUSTOM_H__
#define	 __QYCUSTOM_H__		/*  {  */


#ifndef  __QYPRECUSTOM_H__
  #error	"qyPreCustom.h must included before this file"
#endif


	//  #define	 __ZJST__												//  
	//  #define  __HZSJ__												//  
    #define  __OTHER__													//  
	//  #define  __SUPPORT_AUTOLOGON__									//  2006/01/07
	#define		__NOTSUPPORT_REMOTEDESKTOP__							//  2006/02/25,#define  __NOTSUPPORT_REMOTEDESKTOP__	// 	qwmHelp3.dll,qwmRd.dll,qwmRdHelp.dll,32009/01/17
	//	#define		__NOTSUPPORT_PCMON__								//  2006/03/04
	//	#define		__NOTSUPPORT_FILEMON__								//  2006/03/25

	//  
	#define		__TEST_ONLY__											//  2014/10/15  
	
	//  is
			//  #define			__SUPPORT_CUSMODULE_gsmModem__					//  2008/02/16

#ifdef  __isCli__

			#if  1  //def  __DEBUG__
					#define			__SUPPORT_CUSMODULE_compress__				//  2010/04/28
			#endif

			#if	 1
					#define			__SUPPORT_CUSMODULE_camCap__				//  2010/07/26
			#endif
			#if  1
					#define			__SUPPORT_CUSMODULE_ipp__					//  2011/07/31
			#endif
			#if  1
					#define			__SUPPORT_CUSMODULE_mediaSdk__				//  2011/11/25

			#endif

			#if  1
					#define			__SUPPORT_CUSMODULE_nv__					//  2012/06/17

					#define			__USE_ippToDecCuda__
			#endif

			#if  1
					#define			__SUPPORT_CUSMODULE_amf__					//  2015/04/30

			#endif



			#if  0
					//
					#define			__SUPPORT_CUSMODULE_vorbis__				//  2015/02/13
			#endif
					//
					#define			__SUPPORT_CUSMODULE_vp8__					//  2014/07/18


			//  
			//  #define				__USE_msAec__

#endif
			//
			#if  0
				#define			__SUPPORT_CUS_sampleGrabber__					//  2010/05/30
				#define			__SUPPORT_CUS_nullRenderer__					//  2011/09/02	
			#endif


			#ifndef  WIN32_PLATFORM_QMSP
					 #define			__SUPPORT_acmToDec__								//  2010/06/27
			#endif

			//
			#ifdef  __WINCE__
				#define			__SUPPORT_waveformFirst__							//  2010/06/24
			#endif

			//
			#define			__SUPPORT_getUsrPasswdFromIni__						//  2010/07/28

			#ifdef  __DEBUG__


			#endif

			//  2010/09/18

			//  #define		__SUPPORT_cfgPreviewPin__							//  2011/09/03

			//  2011/02/06
			#ifdef  __APP_qyMc__


					#define		__SUPPORT_HTMLEDIT__							//  对支持htmlEdit的，要定义这个宏
					#define		__SUPPORT_dlgDesktopsMon__						
					#define		__SUPPORT_MULTILOGON__							//  支持多客户端同时登录
					//  #define		__SUPPORT_SERV__								//  server版本
					#define		__SUPPORT_CFGWMV__								//  dlgTalkProc支持dlgCfgWmv.cpp
					#define		__SUPPORT_DLGPROGRESS__							//  dlgTalkProc支持dlgProgress.cpp
					#define		__SUPPORT_remoteAssist__						//  支持远程协助

					//  #define		__SUPPORT_dlgWalls__							//  2012/04/02

					#define		__SUPPORT_dlgInstantAssistant_mfc__				//  2011/03/07

					#define		__SUPPORT_dlgNotification__						//  2011/03/18
					#define		__SUPPORT_wndMenu__

					//#define		__SUPPORT_shareDynBmps__						//  2011/10/15

					#define		__SUPPORT_chooseADevice__						//  2011/10/24

					//
				    #ifdef  __DEBUG__
							#if  10
								#define		__SUPPORT_multiTalkersToInput__			//  2012/05/02. 支持多个输入talker窗口
							#endif
							#if  0
								#define		__TEST_showTalkerShadowMgrFirst__		//  2012/05/03. 在启动影子前,先让mgr显示.这个标志很不合理,仅为测试用
							#endif
					#endif

					//
					#if  0
								#define		__TEST_useXyAsLngLat__					//  2012/05/15. 为了测试方便,假装xy就等于经纬度
					#endif

					//
					#ifndef  __isCli__

							 #define		__SUPPORT_SECCHK__						//  对支持安检的，要定义这个宏
							 #define		__SUPPORT_childFrmMenu__			

					#endif

					//
					#ifdef		__isCli__											//  2012/07/11. 

								#define		__NOTSUPPORT_MULTIDOC__					//  2012/07/16

								#ifndef  __noMfc__
								#endif

								#ifdef  __noMfc__
										#define		__USE_qyMessengerHelp__

										#define		__NOTSUPPORT_qyFile__

								#endif


					#endif

			#endif

			#ifdef  __APP_qyMc_touchscreen__									//  2011/02/06

					#ifndef  __noMfc__

							 #define		__SUPPORT_HTMLEDIT__							//  对支持htmlEdit的，要定义这个宏
							 #define		__SUPPORT_dlgDesktopsMon__
							 #define		__SUPPORT_MULTILOGON__							//  支持多客户端同时登录
							 //  #define		__NOTSUPPORT_DB__
							 #define		__NOTSUPPORT_MULTIDOC__							//  2011/02/07
							 //  #define		__NOTSUPPORT_testLocalAv__						//  2011/02/08
							 //  #define		__SUPPORT_dlgWalls__							//  2011/02/28
							 //  #define		__NOTSUPPORT_qyFile__							//  2011/03/07

							 #define		__SUPPORT_dlgInstantAssistant_mfc__				//  2011/03/07

							 #define		__SUPPORT_dlgNotification__						//  2011/03/18

							 #define		__NOTSUPPORT_dblClk__							//  2011/03/26

							 #ifdef  __X64__
									 //  #define		__NOTSUPPORT_DB__						//  2011/07/10, 为64位不支持数据库作测试
							 #endif

					#endif

					#ifdef  __noMfc__										//  2013/06/18
							#define		__SUPPORT_HTMLEDIT__							//  对支持htmlEdit的，要定义这个宏

							#define		__NOTSUPPORT_MULTIDOC__							//  2011/02/07
							#define		__NOTSUPPORT_qyFile__
							#define		__SUPPORT_MULTILOGON__							//  支持多客户端同时登录

							#define		__SUPPORT_dlgNotification__						//  2011/03/18

							#define		__NOTSUPPORT_dblClk__							//  2011/03/26

							//
							#define		__USE_qyMessengerHelp__							//  2016/10/15


					#endif

			#endif


			#ifdef  __DLL_qyMessenger_help__									//  2013/07/24
					#define		__NOTSUPPORT_MULTIDOC__							//  2011/02/07

					#define		__SUPPORT_remoteAssist__						//  支持远程协助

			#endif


			#ifdef  __DLL_isCliHelp__
					#define		__SUPPORT_HTMLEDIT__							//  对支持htmlEdit的，要定义这个宏
					#define		__SUPPORT_dlgInstantAssistant_mfc__
					#define		__SUPPORT_dlgDesktopsMon__
					//#define		__SUPPORT_shareDynBmps__						//  2013/07/01

					#define		__SUPPORT_remoteAssist__						//  支持远程协助

			#endif

			//  2015/07/03
			#ifdef  __DLL_qmdCliHelp__

							#define		__NOTSUPPORT_MULTIDOC__							//  2011/02/07
							#define		__NOTSUPPORT_qyFile__
							#define		__SUPPORT_MULTILOGON__							//  支持多客户端同时登录

							#define		__SUPPORT_dlgNotification__						//  2011/03/18

							#define		__NOTSUPPORT_dblClk__							//  2011/03/26

							//
							#undef		__SUPPORT_CUSMODULE_nv__						//  2012/06/17

							//
							#define		__NOTSUPPORT_d3d__								//  2016/09/08

			#endif


			#ifdef  __APP_QRT__
					#define		__SUPPORT_SECCHK__								//  对支持安检的，要定义这个宏
			#endif

			#ifdef  __X64__	
					#undef		__SUPPORT_waveformFirst__						//  64位，不能用waveform. 2011/07/10
			#endif

			#ifdef  __WINCE__													//  2011/02/06
					#define		__NOTSUPPORT_DB__
					#define		__NOTSUPPORT_MULTIDOC__							//  2011/02/07
					#define		__NOTSUPPORT_qyAvRecord__						//  2011/02/08
					#define		__NOTSUPPORT_testLocalAv__						//  2011/02/08
					#define		__NOTSUPPORT_qyFile__							//  2011/03/07
			#endif


			//
			#define		__SUPPORT_qyMc_ipp__									//  2011/12/10




#define		CONST_maxSecChkDjCnt							100				//  
//
#define		CONST_djTool_perCnt								20				//  djTool.exe


#endif  /*  }  */


