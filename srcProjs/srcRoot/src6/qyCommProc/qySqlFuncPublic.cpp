
#include	"stdafx.h"

// #include	<afxdb.h>
#include	"sqlucode.h"
#include	<windowsx.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyGuiCommon.h"
#include	"qyString.h"
#include	"qySqlFunc.h"


#if  0
// 2006/05/06
 CQyString  getDbValStr(  int  iDbType,  int  iDataType,  LPCTSTR  val  )
{
	CQyString	str;

	switch  (  iDbType  )  {
		    case  CONST_dbType_sqlServer:
 				  switch  (  iDataType  )  {
						  case  SQL_WCHAR:
						  case  SQL_WVARCHAR:
						  case  SQL_WLONGVARCHAR:
							    str  =  str  +  "N'"  +  val  +  "'"; 
							    break;
						  default:
							     str  =  str  +  "'"  +  val  +  "'";
				  }

				  break;
			default:
				    str  =  str  +  "'"  +  val  +  "'";
				    break;
	}

	return  str;
}
#else

// 2006/05/06
 CQyString  getDbValStr(  int  iDbType,  int  iDataType,  LPCTSTR  val  )
{
	CQyString	str;


	switch  (  iDbType  )  {
		    case  CONST_dbType_sqlServer:
 				  switch  (  iDataType  )  {
						  case  SQL_WCHAR:
						  case  SQL_WVARCHAR:
						  case  SQL_WLONGVARCHAR:
							    //  str  =  str  +  "N'"  +  val  +  "'"; 
								str  =  str  +  (char*)"N'"  +  CQyString(  val  )   +  CQyString(  (char*)"'"  ); 
							    break;
						  default:
							     str  =  str  +  (char*)"'"  +  CQyString(  val  )  +  CQyString(  (char*)"'"  );
				  }

				  break;
			default:
				    str  =  CQyString(  (char*)"'"  )  +  CQyString(  val  )  +  CQyString(  (char*)"'"  );
				    break;
	}

	return  str;
}

#endif
