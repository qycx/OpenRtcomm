// QnmsModuleDaemon.h: interface for the CQnmsModuleDaemon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QNMSMODULEDAEMON_H__F49130EE_F5F1_4605_9074_18001B18516E__INCLUDED_)
#define AFX_QNMSMODULEDAEMON_H__F49130EE_F5F1_4605_9074_18001B18516E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CQnmsModuleDaemon : public CQyGenericDaemon  
{
public:
	QY_NMS_DAEMON	var;
public:
	CQnmsModuleDaemon();
	virtual ~CQnmsModuleDaemon();

};

#endif // !defined(AFX_QNMSMODULEDAEMON_H__F49130EE_F5F1_4605_9074_18001B18516E__INCLUDED_)
