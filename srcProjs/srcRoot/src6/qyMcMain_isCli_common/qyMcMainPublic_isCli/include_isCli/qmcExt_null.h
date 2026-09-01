
#ifndef  __qmcExt_null_h__
#define  __qmcExt_null_h__		//  {

#include	"qmcExtTmpl.h"


class QmcExt_null : public QmcExtTmpl {

public:
	QmcExt_null() {};
	virtual ~QmcExt_null() {};

	//
	virtual atbool bQyMcLogon_post(void* p0) {
		return  true;
	}
	virtual void qyMcLogoff_pre(void* p0)
	{
		return;
	}


	//
	virtual int doAnHgData(AnHgData* p) {
		return  0;
	}

};




//
#endif  //  }

