

#ifndef  __QMSTR_H__
#define  __QMSTR_H__

#ifndef  CONST_resId_is_qmStr_start
	#define	CONST_resId_is_qmStr_start		91000				//  2011/08/14. //  这个区间专门定义一些daemon和gui共用的resId. 定义和qmStr.h要保持一致
	#define	CONST_resId_is_qmStr_end		95000

#endif

 //  这里专门定义一些daemon和gui共用的resId. 定义和qnmResDefs.h要保持一致
 enum  enumResIds_is_internal               // Declare enum type Days
{
	//  CONST_resId_is_qmStr_start	=	91000,				//  2011/08/14. //  这个区间专门定义一些daemon和gui共用的resId. 定义和qmStr.h要保持一致
	
#if  0
	CONST_resId_qyAppAvLevel_mini  =  CONST_resId_is_qmStr_start  +  1,
	CONST_resId_qyAppAvLevel_basic,
	CONST_resId_qyAppAvLevel_standard,
	CONST_resId_qyAppAvLevel_high,
	CONST_resId_qyAppAvLevel_top,
#endif

	//
	CONST_resId_subSystemId_basic  =  CONST_resId_is_qmStr_start  +  10,
	CONST_resId_subSystemId_standard,

	//  CONST_resId_is_qmStr_end  =  95000,
};

extern  LPCTSTR		CONST_str_serviceExits;






#endif  