// QyFileExport.h: interface for the CQyFileExport class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QYFILEEXPORT_H__4415BF14_6035_420B_B761_4085A6160884__INCLUDED_)
#define AFX_QYFILEEXPORT_H__4415BF14_6035_420B_B761_4085A6160884__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CQyFileExport : public CFile  
{
public:
	CQyFileExport();
	virtual ~CQyFileExport();

	void  writeEndLine(  );

	BOOL  bExportCls(  char  *  clsName  );
	BOOL  bExportObj(  char  *  objName  );
	BOOL  bExportObj(  char  *  objName,  int  objContent  );
	BOOL  bExportObj(  char  *  objName,  char  *  objContent  );
	BOOL  bExportData(  char  *  fmt,  ...  );
	
	BOOL  bExportSqlQuery(  void  *  pDb,  char  *  objName,  char  *  sqlStr  );

	
};

#endif // !defined(AFX_QYFILEEXPORT_H__4415BF14_6035_420B_B761_4085A6160884__INCLUDED_)

