

#ifndef  __ctxQyMcTmpl_h__
#define  __ctxQyMcTmpl_h__	//  {

//
#include	"ctxQyTmpl.h"

//
class  CCtxQyMcTmpl: public  CCtxQyTmpl
{
public:
	CCtxQyMcTmpl(  );
	virtual  ~CCtxQyMcTmpl(  );

	//
	virtual  int  setModalWnd_func(  HWND  hDlg,  BOOL  bFileDialog  )  =  NULL;

	//  2017/12/24
	virtual  int  yv12ToRgb24( unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  )  =  NULL;

};




#endif  //  }

