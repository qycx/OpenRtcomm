#include  "stdafx.h"
//#include  "yuntai.h"
#include  "myButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef  THIS_FILE
static char THIS_FILE[]  =  __FILE__;
#endif

CMyButton::CMyButton()
{
	m_nFlag  =  0;
	m_text  =  _T(  ""  );
}

CMyButton::~CMyButton()
{
}

BEGIN_MESSAGE_MAP(  CMyButton,  CButton  )
END_MESSAGE_MAP()

/////////////////////////////////////////////////
//  CMyButton message handlers

void  CMyButton::DrawItem(  LPDRAWITEMSTRUCT  lpDrawItemStruct  )
{
	//  画按钮边线,flag=0凸,flag=1凹
	CDC  dc;
	dc.Attach(  lpDrawItemStruct->hDC  );

	CRect  rect(  lpDrawItemStruct->rcItem  );
	rect.right--;
	rect.bottom--;

	CPen  *  oldpen;
	UINT  color1,color2;

	if  (  m_nFlag  ==  0  )
	{
		//两种状态的颜色处理
		color1  =  COLOR_BTNHILIGHT;	// 按钮高度颜色
		color2  =  COLOR_BTNSHADOW;		// 按钮阴影颜色
	}
	else
	{
		color1  =  COLOR_BTNSHADOW;
		color2  =  COLOR_BTNHILIGHT;
	}

	CPen  pen1(  PS_SOLID,  1,  ::GetSysColor(  color1  )  );
	CPen  pen2(  PS_SOLID,  1,  ::GetSysColor(  color2  )  );
	dc.SelectStockObject(  NULL_BRUSH  );

	oldpen  =  dc.SelectObject(  &pen1  );

	/*
	dc.MoveTo(  rect.right,  rect.top  );	//  画按钮边亮线

	dc.LineTo(  rect.left,  rect.top  );
	dc.LineTo(  rect.left,  rect.bottom  );

	dc.SelectObject(  &pen2  );				//  画按钮边暗线
	dc.MoveTo(  rect.right,  rect.top  );

	dc.LineTo(  rect.right,  rect.bottom  );
	dc.LineTo(  rect.left,  rect.bottom  );
	*/
	
	if  (  m_nFlag  ==  1  )
	{
		dc.SelectStockObject(  BLACK_PEN  );		//  画按钮边黑线
		::DrawEdge(  dc.GetSafeHdc(  ),  &rect,  EDGE_SUNKEN,  BF_RECT  );
	}
	else  
	{
		CBrush  brush(  COLORREF(  RGB(  215,215,215  )  )  );
		::FillRect(  dc.GetSafeHdc(  ),  &rect,  (  HBRUSH  )(  brush.GetSafeHandle(  )  )  );
		::DrawEdge(  dc.GetSafeHdc(  ),  &rect,  EDGE_ETCHED,  BF_RECT  );
	}

	dc.SetBkMode(  TRANSPARENT  );
	::DrawText(  dc.GetSafeHdc(  ),  m_text,  m_text.GetLength(  ),  &rect,  DT_CENTER | DT_VCENTER | DT_SINGLELINE  );

	dc.SelectObject(  oldpen  );
	DeleteObject(  pen1  );
	DeleteObject(  pen2  );
}