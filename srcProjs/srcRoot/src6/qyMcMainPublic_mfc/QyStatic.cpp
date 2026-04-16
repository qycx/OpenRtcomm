// QyStatic.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qymc.h"
#include	"QyStatic.h"
#include	".\qystatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQyStatic

CQyStatic::CQyStatic()
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CQyStatic::~CQyStatic()
{
}


BEGIN_MESSAGE_MAP(CQyStatic, CStatic)
	//{{AFX_MSG_MAP(CQyStatic)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQyStatic message handlers

void CQyStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()

	//  QY_WMBUF_COMM			wmBuf;
	CWnd			*		pParent		=	GetParent(  );
	
	if  (  m_var.pf_OnPaint  )  {
		m_var.pf_OnPaint(  pParent,  this,  &dc  );		
	}

	//  traceLogA(  "CQyStatic::OnPaint(  )"  );

}
