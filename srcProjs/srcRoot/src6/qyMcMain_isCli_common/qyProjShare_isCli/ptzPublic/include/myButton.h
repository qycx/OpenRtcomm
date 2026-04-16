#if  _MSC_VER  >  1000
#pragma once
#endif	//  _MSC_VER  >  1000
//  MyButton.h : header file


//  CMyButton window
class CMyButton : public CButton
{
public:
	CMyButton();

public:
	int  m_nFlag;
	CString  m_text;

public:
	virtual void DrawItem(  LPDRAWITEMSTRUCT  lpDrawItemStruct  );

public:
	virtual ~CMyButton();

protected:
	DECLARE_MESSAGE_MAP(  )

};