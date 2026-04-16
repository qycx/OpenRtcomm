// QyRcdset.cpp : implementation file
//

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers


#include	"stdafx.h"
#include	<afxtempl.h>

#include	"qyCommon.h"
#include	"qyGuiCommon.h"
#include	"qyMcMainCommon.h"
#include	"QyRcdset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQyRcdset

IMPLEMENT_DYNAMIC(CQyRcdset, CRecordset)

CQyRcdset::CQyRcdset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CQyRcdset)
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CQyRcdset::~CQyRcdset(  )
{
	for  (  int  i = 0;  i  <  (  int  )m_nFields;  i  ++  )  {
		switch  (  m_nDataType[i]  )  {
			case  SQL_DECIMAL:
			case  SQL_NUMERIC:
			case  SQL_CHAR:
			case  SQL_VARCHAR:
				delete  (  CString  *  )m_arrayValue[i];
				break;
			case  SQL_BINARY:
			case  SQL_VARBINARY:
				delete  (  CByteArray  *  )m_arrayValue[i];
				break;
			case  SQL_LONGVARCHAR:
			case  SQL_LONGVARBINARY:
				delete  (  CLongBinary  *  )m_arrayValue[i];
				break;
			default:
				delete  m_arrayValue[i];
				break;
		}
	}
}

 int  CQyRcdset::Initialize(  void  *  pDb,  CString  sqlStr,  CString  whereStr,  CString  sortStr,  unsigned  int  nSqlFields,  QY_COLUMNINFO  *  pSqlColumns  )
{
	int					iErr	=	-1;
	void			*	pVar	=	NULL;
	
	if  (  nSqlFields  >  QY_MAXCOLS  )  {
		traceLogA(  "CQyRcdset err.l65"  );
		goto  errLabel;		
	}

	this->m_sqlStr  =  sqlStr;
	this->m_strSort  =  sortStr;
	this->m_strFilter  =  whereStr;
	this->m_pDatabase  =  (  CDatabase  *  )pDb;	
	
	for  (  m_nFields  =  0;  m_nFields  <  nSqlFields;  m_nFields  ++  )  {
		 
		 m_arrayName.Add(  pSqlColumns[m_nFields].label  );
		 //  m_nColsWidth[m_nFields]  =  ?;
	 
		 m_nDataType[m_nFields]  =  pSqlColumns[m_nFields].iDataType;

		 // data types defined in sql.h and sqlext.h
		 switch  (  m_nDataType[m_nFields]  )  {
				 case  SQL_BIT:
					   pVar  =  new  BOOL;		 
					   break;
				 case  SQL_TINYINT:
					   pVar  =  new  BYTE;
					   break;
				 case  SQL_SMALLINT:
					   pVar  =  new  int;
					   break;
				 case  SQL_INTEGER:
					   pVar  =  new  long;
					   break;
				 case  SQL_REAL:
					   pVar  =  new  float;
					   break;
				 case  SQL_FLOAT:
				 case  SQL_DOUBLE:
					   pVar  =  new  double;
					   break;
				 case  SQL_DATE:
				 case  SQL_TIME:
				 case  SQL_TIMESTAMP:
					   pVar  =  new  CTime;
					   break;
				 case  SQL_BINARY:
				 case  SQL_VARBINARY:
					   pVar  =  new  CByteArray;
					   break;
				 case  SQL_DECIMAL:
				 case  SQL_NUMERIC:
				 case  SQL_CHAR:
				 case  SQL_VARCHAR:
					   pVar  =  new  CString;
					   break;
				 case  SQL_LONGVARCHAR:
				 case  SQL_LONGVARBINARY:
					   pVar  =  new CLongBinary;
					   break;
				 default:
					     goto  errLabel;
		 }
		 m_arrayValue.Add(  pVar  );
	}
	
	iErr	=	0;

errLabel:

	return  iErr;

}

CString CQyRcdset::GetDefaultConnect()
{
	traceLogA(  "Pay more attention, CQyRcdset::GetDefaultConnect(  )  called."  );
	return _T("ODBC;DSN=");		
}

CString CQyRcdset::GetDefaultSQL()
{
	traceLogA(  "Pay more attention, CQyRcdset::GetDefaultSQL(  )  called."  );
	return _T("");
}

void CQyRcdset::DoFieldExchange(CFieldExchange* pFX)
{
	int		iErr	=	-1;
	//{{AFX_FIELD_MAP(CQyRcdset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	//}}AFX_FIELD_MAP

	for  (  int  i  =  0;  i  <  (  int  )m_nFields;  i  ++  )  {
		switch  (  m_nDataType[i]  )  {
			case  SQL_BIT:
				RFX_Bool(  pFX,  m_arrayName[i],  *( ( BOOL * )m_arrayValue[i]  )  );
				break;
			case  SQL_TINYINT:
				RFX_Byte(  pFX, m_arrayName[i],  *( ( BYTE * )m_arrayValue[i]  )  );
				break;
			case  SQL_SMALLINT:
				RFX_Int(  pFX,  m_arrayName[i],  *( ( int * )m_arrayValue[i]  )	 );
				break;
			case  SQL_INTEGER:
				RFX_Long(  pFX,  m_arrayName[i],  *( ( long * )m_arrayValue[i]  )  );
				break;
			case  SQL_REAL:
				RFX_Single(  pFX,  m_arrayName[i],  *( ( float * )m_arrayValue[i]  )  );
				break;
			case  SQL_FLOAT:
			case  SQL_DOUBLE:
				RFX_Double(  pFX,  m_arrayName[i],  *( ( double * )m_arrayValue[i]  )  );
				break;
			case  SQL_DATE:
			case  SQL_TIME:
			case  SQL_TIMESTAMP:
				RFX_Date(  pFX,  m_arrayName[i],  *( ( CTime * )m_arrayValue[i]  )  );
				break;
			case  SQL_BINARY:
			case  SQL_VARBINARY:
				RFX_Binary(  pFX,  m_arrayName[i],  *( ( CByteArray * )m_arrayValue[i]  )  );
				break;
			case  SQL_DECIMAL:
			case  SQL_NUMERIC:
			case  SQL_CHAR:
			case  SQL_VARCHAR:
				//  RFX_Text(  pFX,  m_arrayName[i],  *( ( CString * )m_arrayValue[i]  )  );
				RFX_Text(  pFX,  m_arrayName[i],  *( ( CString * )m_arrayValue[i]  ),  1024  );		//  2006/05/01, 当某些字段长度可能超过255，故增加了这个最大交换长度
				break;
			case  SQL_LONGVARCHAR:
			case  SQL_LONGVARBINARY:
				RFX_LongBinary(  pFX,  m_arrayName[i],  *( ( CLongBinary * )m_arrayValue[i]  )  );
				break;
			default:
				goto  errLabel;
		}
	}

		iErr  =  0;

errLabel:

		return;

}


/////////////////////////////////////////////////////////////////////////////
// CQyRcdset diagnostics

#ifdef _DEBUG
void CQyRcdset::AssertValid() const
{
	CRecordset::AssertValid();
}

void CQyRcdset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


 void  CQyRcdset::SetFilter(  CString  whereStr  )
{	 
	CWaitCursor wait;

	m_strFilter  =  whereStr;

	if  (  !IsOpen(  )  )  Open(  CRecordset::snapshot,  this->m_sqlStr  );
	Requery(  );

	// update record counts
	while  (  !IsEOF(  )  )  MoveNext(  );

}



 void CQyRcdset::SetSort(  CString  sortStr  )
{
	// convenience function to set the SQL sort for the query

	m_strSort  =  sortStr;
	if  (  IsOpen(  )  )  {
		CWaitCursor  wait;
		Requery(  );

		// update record counts
		while  (  !IsEOF(  )  )  MoveNext(  );

	}

}

