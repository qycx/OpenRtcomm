
#ifndef  __ancTaskAvOutput_confCli_h__
#define  __ancTaskAvOutput_confCli_h__	//  {

//
#include	"ancTaskAvOutput.h"

//
typedef  struct  __taskMuxStream_confCli_t {
				 int  iTaskId;
				 MuxStreamOutputQ	muxStreamOutputQ;
}		 TaskMuxStream_confCli;


//
#define		MAX_taskAvs_confCli			5

//
//  支持多个任务. 用iTaskId区分
//

//
class CAncTaskAvOutput_confCli :public CAncTaskAvOutput {

public:
	struct {
		//
		TaskMuxStream_confCli			taskMuxStreams[MAX_taskAvs_confCli];
		//
	}  m_var;

public:
	CAncTaskAvOutput_confCli();
	virtual ~CAncTaskAvOutput_confCli();


	//
	TaskMuxStream_confCli* getTaskMuxStreamBySth(int  iTaskId);


	//
	virtual MuxStreamOutputQ* getMuxStreamOutputQ(int  iTaskId,  int muxStreamIndex);

	//
	virtual int init(int  iTaskId, int  nMuxStreams);
	virtual int exit(int  iTaskId);

};



#endif  //  }

