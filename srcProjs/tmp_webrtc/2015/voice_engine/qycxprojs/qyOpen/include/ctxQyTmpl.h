
#ifndef  __ctxQyTmpl_h__
#define  __ctxQyTmpl_h__	//  {

//  2015/02/08
#define		CONST_ctxType_null		0
//
#define		CONST_ctxType_qmc		100
#define		CONST_ctxType_dvt		101
#define		CONST_ctxType_evt		102
//
#define		CONST_ctxType_qmd		150



//
class  CCtxQyTmpl  {

public:
	CCtxQyTmpl(  );
	virtual  ~CCtxQyTmpl(  );

public:
	int					m_iCtxType;
	TCHAR				who_showInfo[64  +  1];		

	//
	virtual  BOOL  bGetLongProperty(  int  propId,  long  *  pVal  )  {  return  FALSE;  }
	virtual  BOOL  bSetLongProperty(  int  propId,  long  val  )  {  return  FALSE;  }
	//
	virtual  BOOL  bGetStrProperty(  int  propId,  TCHAR  *  tBuf,  int  tBufCnt  )  {  return  FALSE;  }
	virtual  BOOL  bSetStrProperty(  int  propId,  LPCTSTR  val  )  {  return  FALSE;  }

	//  2017/02/20
	virtual  void  *  getPtrProperty(  int  propId  )  {  return  NULL;  }
	virtual  BOOL  bSetPtrProperty(  int  propId,  void  *  ptr  )  {  return  FALSE;  }


};




#endif  //  }


