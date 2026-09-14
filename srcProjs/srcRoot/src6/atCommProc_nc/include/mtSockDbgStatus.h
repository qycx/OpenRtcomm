
#ifndef  __mtSockDebugStatusInfo_h__
#define  __mtSockDebugStatusInfo_h__	//  {


//
class  MtSockDbgStatus {

public:
		
	//
	bool							bNo_head14{};			//  為簡化開發，需要時關掉head14
	//
	unsigned  int					maxCnt_accept_timeout{};

	//
	bool							bDbgDetail_socket{};


	//
	bool							bDbgDetail_andFw{};
	bool							bDbgDetail_hgFw{};
	//

	//
	MtSockDbgStatus()
	{
	
	}

	//
	virtual ~MtSockDbgStatus()
	{
		return;
	}

};





#endif  //  }


