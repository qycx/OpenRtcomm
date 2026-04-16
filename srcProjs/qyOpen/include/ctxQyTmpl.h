
#ifndef  __ctxQyTmpl_h__
#define  __ctxQyTmpl_h__	//  {

//  2015/02/08
#define		CONST_ctxType_null				0
//
#define		CONST_ctxType_qmc				100
#define		CONST_ctxType_dvt				101
#define		CONST_ctxType_evt				102
//
#define		CONST_ctxType_qmd				150
#define		CONST_ctxType_qyStatus			160


//
#define		CONST_ctxSubtype_null			0
//
#define		CONST_ctxSubtype_qmcSm			100
#define		CONST_ctxSubtype_qmcMfc			101		//		
#define		CONST_ctxSubtype_qmcQt			102		//



//
class  CCtxQyTmpl  {

public:
	CCtxQyTmpl(  );
	virtual  ~CCtxQyTmpl(  );

public:
	int					m_iCtxType;
	//
	int					m_iCtxSubtype;		//  2023/05/03
	//
	TCHAR				who_showInfo[64  +  1];		

	//
	virtual  BOOL  bGetLongProperty(  int  propId,  long  *  pVal  )  {  return  FALSE;  }
	virtual  BOOL  bSetLongProperty(  int  propId,  long  val  )  {  return  FALSE;  }
	//
	virtual  BOOL  bGetStrProperty(  int  propId,  TCHAR  *  tBuf,  int  tBufCnt  )  {  return  FALSE;  }
	virtual  BOOL  bSetStrProperty(  int  propId,  LPCTSTR  val  )  {  return  FALSE;  }


};




#endif  //  }


