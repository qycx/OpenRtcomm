

#ifndef  __QYCOMMONFUNC7_H__
#define  __QYCOMMONFUNC7_H__	/*  {  */

#ifdef  __cplusplus
  extern  "C"  {
#endif


int  safeStrCpy( char *strIn, char *strOut, unsigned int size );
void  safeStrnCpy( char *strIn, char *strOut, unsigned int size );
void  safeTcsnCpy(  LPCTSTR  strIn,  TCHAR  *  strOut,  unsigned  int  size  );
char  *  qyStrStr(  const  char  *  string,  const  char  *  strCharSet  );

//  int  qyGetFileSize(  char * fileName );
int  qyGetFileSize(  LPCTSTR fileName );
char  *  qyStatusStr(  unsigned  char  ucStatus,  char  *  buf,  int  size  );


#define		safeStrNCpy(  strIn,  strOut,  size  )		safeStrnCpy(  strIn,  strOut,  size  )

extern  HINSTANCE  ghDll_InetMib1;


int  qyInitSnmp( HINSTANCE *pInst );
void  qyExitSnmp( HINSTANCE * pInst );
int  qyGetMac( unsigned char *macAddr );
BOOL  bQyMacFound(  unsigned  char  *  macAddr  );
int  getQwmMacsBySnmp(  QWM_MACS_INFO  *  pMacsInfo  );
//  void  getQwmSortedMacs(  QWM_MACS_INFO  *  pMacsInfo  );


#ifdef __cplusplus
 }
#endif

#endif /* } */

