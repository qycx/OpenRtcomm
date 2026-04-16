
#ifndef  __aisCorePublic_h__
#define  __aisCorePublic_h__	//  {



//
#define		CONST_atCommVer_null			0		//  缺省
#define		CONST_atCommVer_1				1		//  dataType为1个字节
#define		CONST_atCommVer_2				2		//  用位来区分dataType是3个bit,还是一个字节




//
#define		M_isCommVer1					(  g_iCommVer  ==  CONST_atCommVer_1  ||  g_iCommVer  ==  CONST_atCommVer_2  )


//
extern  "C"  
//
#ifdef  __DLL_aisCore__
//
__declspec(dllexport)  

#else
//
__declspec(dllimport)  

#endif
//
int g_iCommVer;



//
#endif  //  }


