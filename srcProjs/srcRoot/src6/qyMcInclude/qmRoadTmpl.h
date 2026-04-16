
#ifndef  __qmRoadTmpl_h__
#define  __qmRoadTmpl_h__	//  {

//  2015/02/08



//
class  CQmRoadTmpl  {

public:
	CQmRoadTmpl(  );
	virtual  ~CQmRoadTmpl(  );

public:
	int					m_iCtxType;
	TCHAR				who_showInfo[64  +  1];		

	//
	virtual  BOOL  bGetLongProperty(  int  propId,  long  *  pVal  )  {  return  FALSE;  }
	virtual  BOOL  bSetLongProperty(  int  propId,  long  val  )  {  return  FALSE;  }
	//
	virtual  BOOL  bGetStrProperty(  int  propId,  TCHAR  *  tBuf,  int  tBufCnt  )  {  return  FALSE;  }
	virtual  BOOL  bSetStrProperty(  int  propId,  LPCTSTR  val  )  {  return  FALSE;  }


};




#endif  //  }


