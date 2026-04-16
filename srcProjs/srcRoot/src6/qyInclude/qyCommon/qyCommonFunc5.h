
#ifndef __QYCOMMONFUNC5_H__
#define __QYCOMMONFUNC5_H__	/* { */

#ifdef __cplusplus
 extern "C" {
#endif


typedef  struct  __qyReg_t		{
				 void		*	pEncCtx;
				 HKEY			hKeyRoot0;			//  2003/09/12, 取HKEY_CLASSES_ROOT,HKEY_CURRENT_CONFIG,HKEY_CURRENT_USER,等
				 //  char			rootKey[CONST_qyMaxRegKeyLen  +  1];
				 TCHAR			rootKey[CONST_qyMaxRegKeyLen  +  1];
				 
				 unsigned  int	uiType;				//  2004/08/06, RegQueryValueEx(  )调用后的值的类型
				 unsigned  int	uiDataLen;			//  2005/07/03
}		  QY_REG;

#define  isWhiteSpace(  c  )   (  (  (  unsigned  char  )(  c  )  >=  0x09  &&  (  unsigned  char  )(  c  )  <=  0x0D  )  ||  (  unsigned  char  )(  c  )  ==  0x20  )

void	resetQyBuf( QY_BUF *buf );
int		qyBufAllocData(  QY_BUF  *  buf,	 unsigned  int  n  );
void	qyBufFree(  QY_BUF  *  buf  );
int		setQyBufStr( char *str, QY_BUF *buf );
int		setQyBufStrn( char *str, QY_BUF *buf, unsigned int n );
int		setQyBufData( void * data, unsigned int n, QY_BUF * buf );
int		qyBufCpy( QY_BUF *pSrc, QY_BUF *pDst );
int		qyBufCmp( QY_BUF *buf1, QY_BUF *buf2 );
int		sscanfToQyBuf( char *buf, QY_BUF *pQyBuf );
int		debugLogQyBuf( char *name, QY_BUF *buf );

void	trim( char *buf );
void	replaceChar( unsigned char  replacedC, unsigned char replacingC, char *buf, unsigned int len );
char	*qySkipSpace( char *buf );

#define  asrGetRegCfg(  rootKey,  cfgName,  cfgVal,  size  )	qyGetRegCfg(  rootKey,  cfgName,  cfgVal,  size  )

int		qyGetRegCfg( LPCTSTR rootKey, LPCTSTR cfgName, char *cfgVal, int size );
//  int		qySetRegCfg( LPCTSTR  rootKey, LPCTSTR  cfgName, char *cfgVal );
int		qySetRegCfg( LPCTSTR  rootKey, LPCTSTR  cfgName, LPCTSTR  cfgVal );
int		qyDelRegCfg(  LPCTSTR  rootKey,  LPCTSTR  cfgName  );

int		qyStrCat( char *str1, char *str2, char *containedBuf, unsigned int bufSize );
void	qyTrim(  char  *  buf  );
#define CHECK_BUF_SIZE( str1, str2, containedBuf )	( strlen( str1 ) + strlen( str2 ) < sizeof( containedBuf ) )
int		bufToFile( char *outBuf, unsigned long size, char *fileName );
void	qyPopHint( char *sth );

void  tTrim(  TCHAR  *  buf  );
//  int		trailDir( char *dir, unsigned int size );
int  trailDir(  TCHAR  *  dir,  unsigned  int  size  );
int		qyQuoteFileName(  TCHAR  *  fileName,  unsigned  int  size  );
//  int		qyGetFileRootName(  LPSTR  pFile,  char  *  RootName,  unsigned  int  size  ); 

int  tQyStrCat(  LPCTSTR  str1,  LPCTSTR  str2,  TCHAR  *  containedBuf,  unsigned  int  bufSize  );

//  BOOL	bFileInNtfs(  char  *  file  );
BOOL	bDomainCtrl(  );
int		qyOutputResourceFile(  unsigned  short  idrData,  LPCTSTR  fileName  );
//  BOOL	bQyCopyFileEx(  char  *  srcFile,  char  *  dstFile,  unsigned  int  totalnCopies  );
BOOL	bQyCopyFileEx(  LPCTSTR  srcFile,  LPCTSTR  dstFile,  unsigned  int  totalnCopies  );

UINT  myGetWindowsDirectory(  LPTSTR lpBuffer,  UINT uSize  );
UINT  myGetSystemDirectory(  LPTSTR lpBuffer,  UINT uSize  );

//  int		qyFullLibName(  char  *  libName,  char  *  fullLibName,  unsigned  int  size  );
int		qyFullLibName(  LPCTSTR  libName,  TCHAR  *  fullLibName,  unsigned  int  size  );
//  int		qyFullWinLibName(  char  *  libName,  char  *  fullLibName,  unsigned  int  size  );
int		qyFullWinLibName(  LPCTSTR  libName,  TCHAR  *  fullLibName,  unsigned  int  size  );


int		tmpSetRegCfgEx(  QY_REG  *  pReg,  LPCTSTR  cfgName,  char  *  cfgVal,  unsigned  int  cb  ); 
int		tmpGetRegCfgEx(  QY_REG  *  pReg,  LPCTSTR  cfgName,  char  *  cfgVal,  unsigned  int  *pSize  );

//
char  *  qwmGetCfg(  char  *  input,  char  *  cfgName,  char  *  cfgVal,  unsigned  int  size  );


//  int  qyRefreshRegCfg_ucb(  char  *  rootKey,  char  *  regValName,  unsigned  char  *  pucbVal  );
int  qyRefreshRegCfg_ucb(  LPCTSTR  rootKey,  LPCTSTR  regValName,  unsigned  char  *  pucbVal  );

 
unsigned  long	qyntohl(  unsigned  long  x  );
unsigned  long	qyhtonl(  unsigned  long  x  );
unsigned  short  qyntohs(  unsigned  short  x  );
unsigned  short  qyhtons(  unsigned  short  x  );
void  qybuf2x(  char  *  s,  unsigned  long  size,  char  *  d  );
unsigned long  qyx2buf(  char  *  s,  unsigned  long  size,  char  *  d  );
char  *  qyl2x(  long l,  char * buf,  int  size  );	//  2004/10/23
int  qyx2l(  char * buf,  long  *  pL  );				//  2004/10/23


extern  QY_DMITEM  CONST_qyNullTable[];



#ifdef __cplusplus
 }
#endif

#endif /* } */


