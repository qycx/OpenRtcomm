
#ifndef  __mtSockDebugStatusInfo_h__
#define  __mtSockDebugStatusInfo_h__	//  {


//
class  MtSockDbgStatusInfo {

public:
	struct {
		bool							bUse_head16;
		//
		bool							bNo_head14;			//  為簡化開發，需要時關掉head14
		//
		unsigned  int					maxCnt_accept_timeout;
		//
		bool							bDbgDetail_andFw;
		bool							bDbgDetail_hgFw;
		//
	}	m_var;
	
	//
	MtSockDbgStatusInfo()
	{
		memset(&m_var, 0, sizeof(m_var));
	}

	//
	virtual ~MtSockDbgStatusInfo()
	{
		return;
	}

};





#endif  //  }


