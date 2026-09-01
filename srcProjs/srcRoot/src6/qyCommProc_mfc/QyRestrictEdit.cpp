// QyRestrictEdit.cpp : implementation file
//

#include "stdafx.h"
// #include "qyMc.h"
#include	<afxwin.h>         // MFC core and standard components
#include	<afxext.h>         // MFC extensions
#include	<afxcview.h>
#include	<afxdisp.h>        // MFC Automation classes

#include	"qyCommon.h"
#include	"qyGuiCommonEx.h"
#include	"QyRestrictEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQyRestrictEdit

CQyRestrictEdit::CQyRestrictEdit()
{
	memset(  &var,  0,  sizeof(  var  )  );
}

CQyRestrictEdit::CQyRestrictEdit(  int  type  )
{
	memset(  &var,  0,  sizeof(  var  )  );
	var.type  =  type;
}


CQyRestrictEdit::~CQyRestrictEdit()
{
}

 int  CQyRestrictEdit::setType(  int  type  )
{
	 var.type  =  type;
	 return  0;
}

 int  CQyRestrictEdit::setType(  int  type,  int  flg,  QY_INPUT_HOOKPROC  inputProc  )
{
	 var.type  =  type;
	 var.flg  =  flg;
	 var.inputProc  =  inputProc;
	 
	 return  0;
}

BEGIN_MESSAGE_MAP(CQyRestrictEdit, CEdit)
	//{{AFX_MSG_MAP(CQyRestrictEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQyRestrictEdit message handlers

void CQyRestrictEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if  (  !var.type  )  {
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		return;
	}

	switch  (  var.type  )  {
			case  QY_EDITTYPE_UINT:
				  OnUINTChar(  nChar,  nRepCnt,  nFlags  );
				  return;
			case  CONST_qyEditType_custom:
				  OnCustomChar(  nChar,  nRepCnt,  nFlags  );
				  return;
			default:
				break;
	}

	return;

}

void  CQyRestrictEdit::OnUINTChar(  UINT  nChar,  UINT  nRepCnt,  UINT  nFlags  )
{
	if  (  nChar  ==  8  )  {
		CEdit::OnChar(  nChar,  nRepCnt,  nFlags  );
		return;
	}

	if  (  isdigit(  nChar  )  )  {
		CEdit::OnChar(  nChar,  nRepCnt,  nFlags  );
		return;
	}

	MessageBeep(  0xFFFFFFFF  );

	return;
}

 extern  "C"  BOOL  myIsAlpha(  unsigned  int  c  )		//  2006/06/29,  原来的	qyIsAlpha写的有错
{
	 if  (  (  (  c   >=  'A'  )  &&  (  c  <=  'Z'  )  )  ||  (  (  c   >=  'a'  )  &&  (  c  <=  'z'  )  )  )
		 return  1;
	 return  0;
}

 extern  "C"  int  myIsSpace(  unsigned  int  c  )
{
	if  (  (  c  >=  0x09  &&  c  <=  0x0d  )  ||  c  ==  0x20  )
		return  1;
	return  0;
}

void  CQyRestrictEdit::OnCustomChar(  UINT  nChar,  UINT  nRepCnt,  UINT  nFlags  )
{
	if  (  nChar  ==  8  )  {
		CEdit::OnChar(  nChar,  nRepCnt,  nFlags  );
		return;
	}

	if  (  !__isascii(  nChar  )  )  {
		if  (  var.flg  &  CONST_qyIdcFlgPermitZw  )  {
			CEdit::OnChar(  nChar,  nRepCnt,  nFlags  );
			return;
		}
	}	
	if  (  myIsAlpha(  nChar  )  )  {
		if  (  var.flg  &  CONST_qyIdcFlgPermitAlpha  )  {
			CEdit::OnChar(  nChar,  nRepCnt,  nFlags  );
			return;
		}
	}
	if  (  nChar  <=  '9'  &&  nChar  >=  '0'  )  {
		if  (  var.flg  &  CONST_qyIdcFlgPermitDigit  )  {
			CEdit::OnChar(  nChar,  nRepCnt,  nFlags  );
			return;
		}
	}
	if  (  (  nChar  <=  '9'  &&  nChar  >=  '0'  )  
		||  (  nChar  >=  'a'  &&  nChar  <=  'f'  )  
			||  (  nChar  >=  'A'  &&  nChar  <=  'F'  )  )  
	{
		if  (  var.flg  &  CONST_qyIdcFlgPermitXdigit  )  {
			CEdit::OnChar(  nChar,  nRepCnt,  nFlags  );
			return;
		}
	}
	if  (  nChar  ==  ','  )  {
		if  (  var.flg  &  CONST_qyIdcFlgPermitComma  )  {
			CEdit::OnChar(  nChar,  nRepCnt,  nFlags  );
			return;
		}
	}
	if  (  nChar  ==  ';'  )  {
		if  (  var.flg  &  CONST_qyIdcFlgPermitSemicolon  )  {
			CEdit::OnChar(  nChar,  nRepCnt,  nFlags  );
			return;
		}
	}
	if  (  myIsSpace(  nChar  )  )  {
		if  (  var.flg  &  CONST_qyIdcFlgPermitSpace  )  {
			CEdit::OnChar(  nChar,  nRepCnt,  nFlags  );
			return;
		}
	}
	if  (  nChar  ==  '-'  )  {
		if  (  var.flg  &  CONST_qyIdcFlgPermitMinus  )  {
			CEdit::OnChar(  nChar,  nRepCnt,  nFlags  );
			return;
		}
	}
	if  (  nChar  ==  '.'  )  {		//  2005/09/14
		if  (  var.flg  &  CONST_qyIdcFlgPermitDot  )  {
			CEdit::OnChar(  nChar,  nRepCnt,  nFlags  );
			return;
		}
	}

	MessageBeep(  0xFFFFFFFF  );

	return;
		
}


