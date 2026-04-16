
#include	<WinSock2.h>
#include	<windows.h>
#include	"qyCommon.h"

 extern  "C"  char  *  qyC2X(  char c,  char * xBuf,  int size  )
{

	 if  (  size  <  2  )  return  NULL;
	 if  (  size  >  2  )  sprintf(  xBuf,  "%02x",  (  unsigned  char  )c  );
	 else	{
		 char	tmpBuf[3];  
		 sprintf(  tmpBuf,  "%02x",  (  unsigned  char  )c  );

		 memcpy(  xBuf,  tmpBuf,  2  );
	 }
	 return  xBuf;
}

 extern  "C"  int  qyX2C(  char * xBuf  )
{
	 unsigned  long	l;
	 
	 if  (  !isxdigit(  xBuf[0]  )  ||  !isxdigit(  xBuf[1]  )  )  return  -1;
	 if  (  sscanf( xBuf,  "%02x",  &l  )  !=  1  )  return  -1;
	 
	 return  (  int  )(  unsigned  char  )l;
	 
}


  // 将buf中数据转化成%02x的方式, xBuf必须有大于2*len的容量
 extern  "C"  char  *  qyBuf2X(  char  *  buf,  unsigned  int  len,  char  *  xBuf  )
{	 
	 xBuf[0]  =  0;
	 for  (  unsigned  int  i  =  0;  i  <  len;  i  ++  )  {
		  sprintf(  xBuf,  "%s%02x",  xBuf,  (  unsigned  char  )buf[i]  );
	 }
	 return  xBuf;
}

 // qyBuf2X的逆形式
 extern  "C"  char  *  qyX2Buf(  char  *  xBuf,  char  *  buf,  unsigned  int  len  )
{
	 for  (  unsigned  int  i  =  0;  i  <  len;  i  ++  )  {
		  if  (  sscanf( &xBuf[2 * i],  "%02x",  (  unsigned  char  *  )&buf[i]  )  !=  1  )  return  NULL;
	 }
	 return  buf;
}

 //  long转化为xStr
 char  *  qyL2XStr(  long l,  char * buf,  int  size  )
{
	 unsigned  char	 *	p  =  (  unsigned  char  *  )&l;

	 if  (  size  <  8  )  return  NULL;
	 
	 l  =  qyhtonl(  l  );
	 if  (  size  >  8  )  {
		 sprintf(  buf,  "%02x%02x%02x%02x",  p[0],  p[1],  p[2],  p[3]  );
		}
	 else  {
		 char  tmpBuf[9];
		 sprintf(  tmpBuf,  "%02x%02x%02x%02x",  p[0],  p[1],  p[2],  p[3]  );
		 memcpy(  buf,  tmpBuf,  8  );
	 }
	 
	 return  buf;

}
 
 //  xStr转化为long
 //  此函数须保证输入的正确性，否则有误
 int  qyXStr2L(  char * buf,  long  *  pL  )
{
	 long					lRet;
	 unsigned	char	*	p  =  (  unsigned  char  *  )&lRet;
	 int					i;
	 unsigned  long			l[4];

	 for  (  i  =  0;  i  <  8;  i  ++  )  {
		  if  (  !isxdigit(  buf[i]  )  )  return  -1;
	 }

	 if  (  sscanf(  buf,  "%02x%02x%02x%02x",  &l[0],  &l[1],  &l[2],  &l[3]  )  != 4   )  return  -1;
	 	 
	 for  (  i  =  0;  i  <  4;  i  ++  )  p[i]  =  (  unsigned  char  )l[i];

	 *pL  =  qyntohl(  lRet  );
	 	 
	 return  0;

}


