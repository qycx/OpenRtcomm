

#ifndef  __ancTaskOutput_av_h__
#define  __ancTaskOutput_av_h__		//  {

//
#include	"myTypes.h"
#include	"ancTaskOutput.h"
#include	"muxStreamOutput.h"




// taskAv 的输出管理类
//
class  CAncTaskAvOutput :public CAncTaskOutput
{
public:
	struct {
		//
		//void * pTaskAv;

	}  m_var;
public:
	CAncTaskAvOutput();
	virtual ~CAncTaskAvOutput();

	//
	virtual MuxStreamOutputQ* getMuxStreamOutputQ(int  iTaskId,  int muxStreamIndex)  = mynull;

	//
	virtual int init(int  iTaskId,  int  nMuxStreams)  =  mynull;
	virtual int exit(int  iTaskId ) = mynull;

};




//
#endif  //  }


