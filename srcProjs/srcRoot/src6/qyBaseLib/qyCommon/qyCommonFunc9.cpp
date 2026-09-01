
#include	<WinSock2.h>
#include	<windows.h>
#include	"qyCommon.h"


 extern  "C"  unsigned  long  qyhtonl(  unsigned  long  x  )
{
	 unsigned  char	buf[4];

	 buf[0]  =  (  unsigned  char  )(  (  x  &  0xff000000  )  >>  24   );
	 buf[1]  =  (  unsigned  char  )(  (  x  &    0xff0000  )  >>  16  );
	 buf[2]  =  (  unsigned  char  )(  (  x  &      0xff00  )  >>  8  );
	 buf[3]  =  (  unsigned  char  )(  (  x  &        0xff  )  );

	 return  *(  unsigned  long  *  )buf;
}

 extern  "C"  unsigned  long  qyntohl(  unsigned  long  x  )
{
	 unsigned  long			lRet;
	 unsigned  char	buf[4];

	 memcpy(  buf,  &x,  4  );
	 lRet  =  (  buf[0]  <<  24  )  +  (  buf[1]  <<  16  )  +  (  buf[2]  <<  8  )  +  buf[3];

	 return  lRet;
}

 extern  "C"  unsigned  short  qyhtons(  unsigned  short  x  )
{
	 unsigned  char	buf[2];

	 buf[0]  =  (  unsigned  char  )(  (  x  &  0xff00  )  >>  8  );
	 buf[1]  =  (  unsigned  char  )(  (  x  &    0xff  )  );
	 
	 return  *(  unsigned  short  *  )buf;
}

 extern  "C"  unsigned  short  qyntohs(  unsigned  short  x  )
{
	 unsigned  short	usRet;
	 unsigned  char		buf[2];

	 memcpy(  buf,  &x,  2  );
	 usRet  =  (  buf[0]  <<  8  )  +  (  buf[1]  );

	 return  usRet;
}


 extern  "C"  int  qyhexdigit2(  char  ch  )					 
{
   if (ch >= '0' && ch <= '9') return ch - '0';
   if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
   if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
   return -1;
}


 //  返回转换后的字节数
 extern  "C"  unsigned  long  qyx2buf(  char  *  s,  unsigned  long  size,  char  *  d  )
{
   register  unsigned  count  =  0;
   register  int  lo,  hi;

   if  (  size  >  1  ) 
	   do  {
           hi  =  qyhexdigit2(  *s++  );
     	   if  (  hi  <  0  )  break;
      	   lo  =  qyhexdigit2(  *s++  );
      	   if  (  lo  <  0  )  break;
      	   *d++  =  (hi << 4) | lo;
      	   count  ++  ;
   	   }  while  (  2  *  count  +  1  <  size  );
   return  count;
}


 extern  "C"  void  qybuf2x(  char  *  s,  unsigned  long  size,  char  *  d  )
{
	 static  char  c[16]  =  {  '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',
		 'a',  'b',  'c',  'd',  'e',  'f',  };

	 for  (  ;  size  >  0;   size  --  )  {
		  *d  =  c[  (  ( unsigned  char  )*s  )  >>  4  ];
		  *( d  +  1  )  =  c[  (  ( unsigned  char  )*s  )  &  0x0f  ];
		  s  ++  ;  d  +=  2;			
	 }

}


 //  long转化为xStr
 extern  "C"  char  *  qyl2x(  long l,  char * buf,  int  size  )
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
 extern  "C"  int  qyx2l(  char * buf,  long  *  pL  )
{
	 long					lRet;
	 int					i;
	 
	 for  (  i  =  0;  i  <  8;  i  ++  )  {
		  if  (  !qyIsXdigit(  buf[i]  )  )  return  -1;
	 }

	 if  (  qyx2buf(  buf,  8,  (  char  *  )&lRet  )  !=  4  )  return  -1;
	 	 
	 
	 *pL  =  qyntohl(  lRet  );
	 	 
	 return  0;

}

