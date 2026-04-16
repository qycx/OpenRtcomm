
#ifndef  __ancCommProc_defs_h__
#define  __ancCommProc_defs_h__		//  {

//
#include	"myTypes_basic.h"





#ifndef  __USE_atCommVer_1_old_proto__


//
// 普通的cfgId都定义在4100之后，重要的cfgId定义<4096之前(12bits).
//#define		CONST_ancCfgId_base_common							4096		//  1000
#define		CONST_ancCfgId_base_common								4100		//  1000


//
// 普通的commType定义在4000之后，重要的在之前。最重要的<256
#define		CONST_ancCommType_base									4000


/////////////////  这里定义重要的cfgId. < 4096

#define		CONST_ancCfgId_null										0		//  
#define		CONST_ancCfgId_start									1		//  (  CONST_qnmCfgId_base_common  +  100  )
#define		CONST_ancCfgId_mem										2		//  (  CONST_qnmCfgId_base_common  +  101  )				//  2007/08/05, 只用在小而快的数据包。一般的包的成员要使用CONST_imCommType_mem
//
#define		CONST_ancCfgId_messengerId_from							3		//  (  CONST_qnmCfgId_base_common  +  2640  )				//  2007/11/29
#define		CONST_ancCfgId_messengerId_to							4		//  (  CONST_qnmCfgId_base_common  +  2641  )				//  2007/11/29
#define		CONST_ancCfgId_uiMsgRouteId								5		//  (  CONST_qnmCfgId_base_common  +  2650  )				//  2008/05/27
#define		CONST_ancCfgId_messengerId								6		//  (  CONST_qnmCfgId_base_common  +  2500  )

//
#define		CONST_ancCfgId_uiTranNo_openAudioDev					20		//  (  CONST_qnmCfgId_base_common  +  4051  )				//  
#define		CONST_ancCfgId_usCnt									21		//  (  CONST_qnmCfgId_base_common  +  2101  )				//  2007/08/01
//
#define		CONST_ancCfgId_uiSampleTimeInMs							22		//  (  CONST_qnmCfgId_base_common  +  4054  )				//  2009/05/04
#define		CONST_ancCfgId_uiPts									23		//  (  CONST_qnmCfgId_base_common  +  4057  )				//  2015/01/15
#define		CONST_ancCfgId_uiLen									24		//  (  CONST_qnmCfgId_base_common  +  2110  )				//  2008/10/30
#define		CONST_ancCfgId_rawData									25		//  (  CONST_qnmCfgId_base_common  +  3508  )				//  2008/03/23
#define		CONST_ancCfgId_usElapseInMs_fromLastPkt					26

//
#define		CONST_ancCfgId_uiTranNo_openVideoDev					30		// 	(  CONST_qnmCfgId_base_common  +  4050  )				//  
#define		CONST_ancCfgId_ucbKeyFrame								31		//  (  CONST_qnmCfgId_base_common  +  4058  )

//
#define		CONST_ancCfgId_conf_ui64Id								40		


/////这里定义普通的cfgId.  CONST_ancCfgId_base_common  +  n



//
// communication data type
//////////////////////// 这里定义中最重要的ancCommType. <256
//
#define		CONST_ancCommType_msgRoute								1
#define		CONST_ancCommType_mem									2		//  (  CONST_imCommType_base  +  102  )		//  
//
#define		CONST_ancCommType_transferAudioData						4		//  (  CONST_imCommType_base  +  411  )		//  2008/04/16, 
#define		CONST_ancCommType_transferVideoData						5		//  (  CONST_imCommType_base  +  407  )		//  2008/03/15, 



//  这里定义重要的ancCommType  < 4000


/////////////// 这里定义普通的ancCommType. CONST_ancCommType_base  +  n

//
#else


//
#define		CONST_ancCfgId_null										0		//  



//
#define		CONST_ancCfgId_base_common								1000

#define		CONST_ancCommType_base									3000







//////////////////////////////////////
#define		CONST_ancCfgId_start								(  CONST_ancCfgId_base_common  +  100  )
#define		CONST_ancCfgId_mem									(  CONST_ancCfgId_base_common  +  101  )				//  2007/08/05, 只用在小而快的数据包。一般的包的成员要使用CONST_imCommType_mem

//
#define		CONST_ancCfgId_usCnt								(  CONST_qnmCfgId_base_common  +  2101  )				//  2007/08/01

#define		CONST_ancCfgId_uiLen									(  CONST_qnmCfgId_base_common  +  2110  )				//  2008/10/30

//
#define		CONST_ancCfgId_messengerId_from						(  CONST_qnmCfgId_base_common  +  2640  )				//  2007/11/29
#define		CONST_ancCfgId_messengerId_to						(  CONST_qnmCfgId_base_common  +  2641  )				//  2007/11/29
#define		CONST_ancCfgId_uiMsgRouteId							(  CONST_qnmCfgId_base_common  +  2650  )				//  2008/05/27
#define		CONST_ancCfgId_messengerId							(  CONST_qnmCfgId_base_common  +  2500  )


//
#define		CONST_ancCfgId_uiTranNo_openAudioDev				(  CONST_qnmCfgId_base_common  +  4051  )				//  

#define		CONST_ancCfgId_uiSampleTimeInMs						(  CONST_qnmCfgId_base_common  +  4054  )				//  2009/05/04
//
#define		CONST_ancCfgId_uiTranNo_openVideoDev					(  CONST_qnmCfgId_base_common  +  4050  )				//  
#define		CONST_ancCfgId_ucbKeyFrame								(  CONST_qnmCfgId_base_common  +  4058  )

#define		CONST_ancCfgId_rawData									(  CONST_qnmCfgId_base_common  +  3508  )				//  2008/03/23

#define		CONST_ancCfgId_uiPts									(  CONST_qnmCfgId_base_common  +  4057  )				//  2015/01/15





/////////////////////////
//
#define		CONST_ancCommType_msgRoute								(  CONST_imCommType_base  +  4  )		//  2007/11/29
//
#define		CONST_ancCommType_mem									(  CONST_imCommType_base  +  102  )		//  

//
#define		CONST_ancCommType_transferAudioData						(  CONST_imCommType_base  +  411  )		//  2008/04/16, 
#define		CONST_ancCommType_transferVideoData						(  CONST_imCommType_base  +  407  )		//  2008/03/15, 


//
#endif 


//  注意，这里是cfgId的定义. 是字段的定义
#define		CONST_qnmCfgId_base_common								CONST_ancCfgId_base_common	


//  注意，这里是commType的定义，是小段数据流的定义
#define		CONST_imCommType_base									CONST_ancCommType_base


//
#define		CONST_iWaitTimeInMs_rtMedia		1000
#define		CONST_iWaitTimeInMs_media		1000



//
#endif  //  }



