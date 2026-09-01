// QyFile.h: interface for the CQyFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QYFILE_H__9DC3D177_E4D3_450F_B08E_4E79282B239D__INCLUDED_)
#define AFX_QYFILE_H__9DC3D177_E4D3_450F_B08E_4E79282B239D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//  数据文件格式：
//
//		[数据文件信息]
//		obj=
//		cstm=
//		ver=
//		objEnd
//
//		[数据区]
//		obj=qyPcRegInfoTab
//		
//		objEnd
//		obj=qyPcTab
//
//		objEnd
//

#define		CONST_qyFileCls_file					"File"					//  数据文件信息"			//  文件类
#define		CONST_qyFileCls_data					"Data"					//  数据区"				//  数据类

#define		CONST_qyFileObj_customId				"cstm"					//  定制号，文件类
#define		CONST_qyFileObj_ver						"ver"					//  版本号, 文件类
#define		CONST_qyFileObj_createTime				"createTime"			//  CONST_qyFileCls_*实体名, 通用
#define		CONST_qyFileObj_title					"title"					//  2009/10/07
#define		CONST_qyFileObj_comment					"comment"				//  CONST_qyFileCls_*实体名, 通用

#define		CONST_qyFileObj_name					"obj"					//  CONST_qyFileCls_*实体名, 通用
#define		CONST_qyFileObj_end						"objEnd"				//  

//  #define		CONST_qyFileObjName_qrgBak				"qrg"				//  注册信息备份,  文件类
//  #define		CONST_qyFileObjName_qbhBak				"qbh"

#define		CONST_qyFileObj_background				"background"			//  2009/10/07


#define		CONST_qyMaxExportCols					150
#define		CONST_maxQyFileLineLen					16384

#define		CONST_replaceStr_comma					"g7gsdfh"		//  这两个代替串里不能出现','和'\n'
#define		CONST_replaceStr_newLine				"g4gadxh"
#define		CONST_replaceStr_singleQuatotation		"g3gasxh"		//  2006/04/25



class CQyFile : public CFile  
{
public:
	CQyFile();
	virtual ~CQyFile();

	struct				{
	}					m_var;


	void		writeEndLine(  );
	char	*	gets(  char  *  string,  unsigned  int  n  );
	WCHAR	*	gets(  WCHAR  *  string,  unsigned  int  n  );	//  2006/04/30

	BOOL		bFindObj(  char  *  objName,  char  *  objContent  );
	BOOL		bGetObjData(  char  *  objName,  char  *  data,  unsigned  int  size  );
	BOOL		bGetNextLine(  char  *  objName,  unsigned  int  objNameSize,  char  *  data,  unsigned  int  size  );

	BOOL		bExportCls(  char  *  clsName  );
	BOOL		bExportObj(  char  *  objName  );
	BOOL		bExportObj(  char  *  objName,  int  objContent  );
	BOOL		bExportObj(  char  *  objName,  char  *  objContent  );
	BOOL		bExportData(  char  *  fmt,  ...  );
	
	BOOL		bExportSqlQuery(  void  *  pDb,  int  iDbType,  char  *  objName,  char  *  sqlStr  );
	BOOL		bImportSqlTable(  void  *  pDb,  int  iDbType,  char  *  tableName,  char  *  colsStr,  unsigned  char  ucbUtf8  );

};


#endif // !defined(AFX_QYFILE_H__9DC3D177_E4D3_450F_B08E_4E79282B239D__INCLUDED_)


