

#ifndef  __parseCmdLine_open_h__
#define  __parseCmdLine_open_h__	//  {

typedef  struct  __qmcAppParams_common_t	{

		 //  appObjPrefix= "qm"  +  iSeqNoSelected_appObjPrefix. 2014/02/10
		 TCHAR											appObjPrefix[32];
		 //
		 int											iSeqNoSelected_appObjPrefix;	//  
		 //  2015/02/01
		 int											tn_cliPipe;						//  2015/02/02

}	 QmcAppParams_common;


//
 int  parseCmdLine_open(  LPCTSTR  pCmdLine,  QmcAppParams_common  *  pParams  );


#endif  //  }

