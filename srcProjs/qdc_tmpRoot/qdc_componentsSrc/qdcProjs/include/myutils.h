

#ifndef  __MYUTILS_H__
#define  __MYUTILS_H__

#include	"sample_utils.h"
#include	"sample_defs.h"
//
#include	"qdcOpenCommon.h"

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
class  CMySmplYUVReader;

//
typedef  struct  {
				CMySmplYUVReader			*	p;
				mfxFrameSurface1			*	pSurface;
}		 PARAM_CMySmplYUVReader_myLoadNextFrame_msdk;


//
typedef  int  (  *PF_CMySmplYUVReader_myLoadNextFrame_msdk  )(  void  *  pPipeline,  unsigned  short  usPktResType,  void  *  p0_pInput,  void  *  p1_uiInputSize,  PARAM_CMySmplYUVReader_myLoadNextFrame_msdk  *  pParam  );



//  2012/08/24
class CMySmplYUVReader:public CSmplYUVReader
{
public:
	CMySmplYUVReader(  );

	//virtual mfxStatus Init(const msdk_char *strFileName, const mfxU32 ColorFormat, const mfxU32 numViews, std::vector<msdk_char*> srcFileBuff);
    virtual mfxStatus Init(std::list<msdk_string> inputs, mfxU32 ColorFormat, bool shouldShiftP010=false);
	mfxStatus myLoadNextFrame(  BYTE  *  pInput,  unsigned  int  uiInputSize,  mfxFrameSurface1* pSurface);
	virtual mfxStatus LoadNextFrame(mfxFrameSurface1* pSurface);
	virtual void Close();

	//
	struct												{
		void										*	m_pQdcObjInfoParam;
		//
		PF_CMySmplYUVReader_myLoadNextFrame_msdk		pf_CMySmplYUVReader_myLoadNextFrame_msdk;
		void										*	pPipeline;
		
		//
		long											old_lPktId;

		//
		BYTE										*	m_pInput;	
		unsigned  int									m_uiInputSize;
	}													m_var;
};

class CMySmplBitstreamWriter:public CSmplBitstreamWriter
{
public :
	CMySmplBitstreamWriter(  );
	virtual ~CMySmplBitstreamWriter();


    virtual mfxStatus Init(  void  *  pQdcObjInfoParam  );
	virtual mfxStatus Init(const msdk_char *strFileName);
    virtual mfxStatus WriteNextFrame(mfxBitstream *pMfxBitstream, bool isPrint = true);
	virtual void Close();

	//
#if  0
	struct							{
		void				*		m_pQdcObjInfoParam;
		
		//
		void				*		pPkt;
		unsigned  int				size_pPkt;

	}								m_var;
#endif
	BitstreamWriter_var				m_var;

};

//
class CMySmplBitstreamReader:public CSmplBitstreamReader	//  CH264FrameReader
{
public :

	CMySmplBitstreamReader(  );

    virtual void      Close();
    virtual mfxStatus Init(const TCHAR *strFileName);
    virtual mfxStatus ReadNextFrame(  mfxBitstream *pBS);

	//
	mfxStatus ReadNextFrame_func(  mfxBitstream *pBS);

	//
	struct					{

		struct				{
			BYTE  *			pInput;
			unsigned  int	uiInputSize;
			//BOOL			bFinished;
		}					inputInfo;		//  每次使用时，在函数decompressVideo进入时，要设置，函数退出时 ，要清除，避免被使用失效地址

		//  2014/03/24
		void			*	m_pQdcObjInfoParam;

		//
		long				old_lPktId;		//  用来防止getNextPkt出错，得到的是重复包


	}						m_var;
};


class CMySmplYUVWriter:public CSmplYUVWriter
{
public :

	CMySmplYUVWriter(  );

    virtual void      Close();
	virtual mfxStatus Init(const msdk_char *strFileName, const mfxU32 numViews);
    virtual mfxStatus WriteNextFrame(mfxFrameSurface1 *pSurface);

	//
	mfxStatus WriteNextFrame_pre();
	mfxStatus WriteNextFrame0(mfxFrameSurface1 *pSurface);
	mfxStatus WriteNextFrame1();


	//
	YUVWriter_var					m_var;

	//  int  qdcOutput(  char  *  pOutput,  unsigned  int  uiOutputSize  );


};


//////////////



//
int  qdcFindOutputIndex(  void  *  pQdcObjInfoParam  );
int  qdcOutput(  void  *  pQdcObjInfoParam,  int  outputIndex,  char  *  pOutput,  unsigned  int  uiOutputSize  );
int  tmp_showInfo(  TCHAR  *  hint  );


 //
 BOOL  bTransformFuncsOk(  QDC_OBJ_INFO  *  pQdcObjInfo  );

#endif

