
#ifndef  __qmcPublic_qt_h__
#define  __qmcPublic_qt_h__  //  {


#ifdef UNICODE  
#define QStringToTCHAR(x)     (wchar_t*) x.utf16()  
#define PQStringToTCHAR(x)    (wchar_t*) x->utf16()  
#define TCHARToQString(x)     QString::fromUtf16((x))  
#define TCHARToQStringN(x,y)  QString::fromUtf16((x),(y))  
#else  
#define QStringToTCHAR(x)     x.local8Bit().constData()  
#define PQStringToTCHAR(x)    x->local8Bit().constData()  
#define TCHARToQString(x)     QString::fromLocal8Bit((x))  
#define TCHARToQStringN(x,y)  QString::fromLocal8Bit((x),(y))  
#endif


//
//int doMcClientLogonOK(void* pQmcLogin, char* m_server, LPTSTR m_name, LPTSTR m_passwd, char* ca_sendData, int ca_sendDataLen);
void qyMcLogoff();


#endif  //  }


