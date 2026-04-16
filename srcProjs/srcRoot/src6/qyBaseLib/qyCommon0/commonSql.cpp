

/*
int getsysstatus(Env *penv)
{
		
	char buf[500];
	int iret=-1;

	SQLINTEGER   cb1,cb2,cb3,cb4,cb5;
	SQLHSTMT      hstmt;
	SQLRETURN      retcode;
	
	
	SQLAllocHandle(SQL_HANDLE_STMT, penv->pdb->m_hdbc,&hstmt);

	CString sqlbuf;
	
	sqlbuf=CString("SELECT SysOn,StepNo,StartTime,RestartFlag,Operator from ")+SysStatusTab;

	retcode = SQLExecDirect(hstmt,
            (unsigned char *)(LPCTSTR)sqlbuf,SQL_NTS);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		SQLBindCol(hstmt, 1, SQL_CHAR,penv->sysstatustab.SysOn,sizeof(penv->sysstatustab.SysOn), &cb1);
		SQLBindCol(hstmt, 2, SQL_INTEGER,&penv->sysstatustab.StepNo,0, &cb2);
		SQLBindCol(hstmt, 3, SQL_CHAR,penv->sysstatustab.StartTime,sizeof(penv->sysstatustab.StartTime), &cb3);
		SQLBindCol(hstmt, 4, SQL_CHAR,penv->sysstatustab.RestartFlag,sizeof(penv->sysstatustab.RestartFlag), &cb4);
		SQLBindCol(hstmt, 5, SQL_CHAR,penv->sysstatustab.Operator,sizeof(penv->sysstatustab.Operator), &cb5);
		retcode = SQLFetch(hstmt);
		if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
			sprintf(buf,"sqlfetch error");
			AfxMessageBox(buf);
			}
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO){
			iret=0;
			} 
		
		}
		
	
	SQLFreeHandle(SQL_HANDLE_STMT,hstmt);

	return iret;

}
*/


