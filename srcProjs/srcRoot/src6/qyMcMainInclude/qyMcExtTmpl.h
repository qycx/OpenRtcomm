

#ifndef  __qyMcExtTmpl_h__
#define  __qyMcExtTmpl_h__	//  {

//
class  CCtxQyMc;


class QyMcExtTmpl {

public:
	struct {
		//
		CCtxQyMc* m_pQyMc;

	}		m_var;

public:
	QyMcExtTmpl();
	virtual ~QyMcExtTmpl();

	//
	virtual int getSmCfgInfo(TCHAR* cfgDirName, int cfgDirNameLen) = NULL;

};



#endif  //  }


