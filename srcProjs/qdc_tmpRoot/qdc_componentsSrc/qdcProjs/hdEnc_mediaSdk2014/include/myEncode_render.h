
#ifndef  __myDecode_render_h__
#define  __myDecode_render_h__	//  {

//
#include	"tmp_decode_render.h"

//
BOOL  bShowRenderWnd(  );


class  CMyEncodeD3DRender:public  CDecodeD3DRender  
{
public:
	CMyEncodeD3DRender(  );
	~CMyEncodeD3DRender(  );

	//
	virtual mfxStatus Init(sWindowParams pWParams);

};



#endif  //  }


