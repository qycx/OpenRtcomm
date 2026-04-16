

#ifndef  __MYDECPIPELINE__
#define  __MYDECPIPELINE__		//  {


//
#define		CHECK_POINTER		MSDK_CHECK_POINTER
#define		CHECK_ERROR			MSDK_CHECK_ERROR
#define		ZERO_MEMORY			MSDK_ZERO_MEMORY
#define		CHECK_NOT_EQUAL		MSDK_CHECK_NOT_EQUAL
#define		CHECK_RESULT		MSDK_CHECK_RESULT
#define		ALIGN16				MSDK_ALIGN16
#define		ALIGN32				MSDK_ALIGN32
#define		BREAK_ON_ERROR		MSDK_BREAK_ON_ERROR
#define		INVALID_SURF_IDX	MSDK_INVALID_SURF_IDX
#define		CHECK_RESULT_SAFE	MSDK_CHECK_RESULT_SAFE
#define		IGNORE_MFX_STS		MSDK_IGNORE_MFX_STS
#define		SAFE_DELETE			MSDK_SAFE_DELETE
#define		SAFE_RELEASE		MSDK_SAFE_RELEASE
#define		WAIT_INTERVAL		MSDK_WAIT_INTERVAL
#define		SAFE_DELETE_ARRAY	MSDK_SAFE_DELETE_ARRAY
#define		MAX					MSDK_MAX




//
#include	"pipeline_decode.h"


//
class CMyDecPipeline : public CDecodingPipeline
{
public:

    CMyDecPipeline();
    virtual ~CMyDecPipeline();

	//
	sInputParams							m_params;   // input parameters from command line

	//
	struct									{
		void						*		pQdcObjInfo;		//  2014/03/29

		//
		BOOL								bDone_init0;
		BOOL								bDone_InitMfxParams_func;
		BOOL								bDone_init1;

		//  2015/09/29
		PKTS_sharedTexInfo_forYuvWriter		pkts_sharedTexInfo;

		
	}										m_var;

	
	
	virtual mfxStatus Init(sInputParams *pParams);


	//
	virtual mfxStatus InitMfxParams(sInputParams *pParams);

	//
	virtual mfxStatus CreateHWDevice();


	//  2015/01/17
	virtual mfxStatus DeliverOutput(mfxFrameSurface1* frame);



	//
	mfxStatus  myRun(  void  * pQdcObjInfo  );
	
};



#endif