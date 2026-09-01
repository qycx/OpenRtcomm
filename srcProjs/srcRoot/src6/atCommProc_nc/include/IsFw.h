
#ifndef  __isFw_h__
#define  __isFw_h__	//  {


#include	"isFwPublic.h"
#include	"IsFw.h"

//
class IsFw {
	//
public:
	struct {
		//
		int				iFwType;
		//
		char			mtxName[128];
		//
		AndIsFwCfg		cfg;
		//
		long			lSyncCnt;

		//
	}		m_var;

	//
public:
	IsFw();
	~IsFw();


	//
	int		init();
	int		exit();
	//
	int		refreshCfg();

	//

};




//
#endif 
