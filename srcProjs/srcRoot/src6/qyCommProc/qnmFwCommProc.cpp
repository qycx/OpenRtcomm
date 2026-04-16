
#include	"stdafx.h"

#include	<windows.h>
#include	<stddef.h>
#include	<stdlib.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmAssetsCommProc.h"
#include	"qnmFwCommProc.h"
#include	<tchar.h>
#include	"qySyncCommProc.h"


 //  从一个'\0'结尾的字符串中替换（过滤）某个字符为空格，并对有size长度限制的情况将最后的字节截空
 //  size为(  unsigned  int  )-1时，表对size不作限制
 extern  "C"  int  fwReplaceChrInStr(  char  c,  char  *  str,  unsigned  int  size  )
{	 
	 if  (  !str  ||  !size  )  return  0;		//  2006/06/28修正，增加了size为0时的条件处理
	 if  (  size  !=  -1  &&  size  )  str[size  -  1]  =  '\0';
	 for  (  ;  *str;  str  ++  )  if  (  *str  ==  c  )  *str  =  ' ';
	 return  0;
}



 //  cnt为(  unsigned  int  )-1时，表明对cnt不作限制
 extern  "C"  int  filterStr2Display(  TCHAR  *  str,  unsigned  int  cnt  )
{
	 if  (  !str  ||  !cnt  )  return  0;	
	 if  (  cnt  !=  -1  &&  cnt  )  str[cnt  -  1]  =  _T(  '\0'  );	//  2006/06/28, 这里截尾了
	 for  (  ;  *str;  str  ++  )  {
		  if  (  !_istascii(  *str  )  )  continue;
		  if  (  _istalpha(  *str  )  )  continue;
		  if  (  _istdigit(  *str  )  )  continue;
		  if  (  _tcschr(  _T(  " ~`!@#$%^&*()_-+=\\|[]{};:<>,./\"?"  ),  *str  )  )  continue;
		  *str  =  _T(  ' '  );
	 }
	 return  0;
}


 //  2008/12/03. 注意：这里是不截尾的
 extern  "C"  int  fwFilterBuf(  char  *  strSearch,  char  *  buf,  unsigned  int  cnt  )
{
	unsigned  int		i;

	if  (  !strSearch  ||  !buf  ||  !cnt  )  return  0;
	for  (  i  =  0;  i  <  cnt;  i  ++  )  {
		 if  (  strchr(  strSearch,  buf[i]  )  )  buf[i]  =  ' ';  
	}
	return  0;
}


 //  2008/12/03。不截尾
 extern  "C"  int  fwFilterTBuf(  TCHAR  *  strSearch,  TCHAR  *  tBuf,  unsigned  int  cnt  )
{
	unsigned  int		i;

	if  (  !strSearch  ||  !tBuf  ||  !cnt  )  return  0;
	for  (  i  =  0;  i  <  cnt;  i  ++  )  {
		 if  (  _tcschr(  strSearch,  tBuf[i]  )  )  tBuf[i]  =  ' ';  
	}
	return  0;
}


 //  字符串中有特殊字符，比如 ''', 在入库时就会出错
 //  为了避免这个问题，将特殊字符转成{字符编码}。字符编码是字符的网络字节顺序的unicode值。或者ascii值。对'{'或者'}'也这么转换
 //  在人工输入后立即转换，在通信和数据库存储时都不需要考虑这个问题了。
 //  在显示时再转换出来。
 //  这样的处理效率就高了，因为中间运算不需要考虑了。最多为了防止攻击，直接过滤掉特殊字符就可以了。
 //	 特殊的字符包括	''', '"', '[', ']', '^', '\', '%', '{', '}', '@'
 //  通配符都要转换
 //  选择 '{' 和 '}' 是因为这对符号在sql 中没有特殊含义
 //  2008/12/01

#define		CONST_escapeChars	"'\"[]^\\%{}@"

 //  cnt为(  unsigned  int  )-1时，表明对cnt不作限制
 extern  "C"  int  escapeTStr(  TCHAR  *  str,  unsigned  int  cnt  )
{
	int					iErr	=	-1;
	TCHAR			*	pIn;
	TCHAR			*	pOut;
	TCHAR			*	inBuf	=	NULL;
    unsigned  int		nOut	=	0;

	if  (  !str  ||  !cnt  )  return  0;

	if  (  cnt  ==  -1  )  cnt  =  lstrlen(  str  )  +  1;	//  当cnt为-1时，是当作一个以０结尾的字符串的
	else  str[cnt  -  1]  =  0;								//  确保0结尾

	//
	pIn  =  str;
	pOut  =  str;
	for  (  ;  *pIn  &&  nOut  <  cnt  -  1;  pIn  ++  )  {
		 if  (  !_tcschr(  _T(  CONST_escapeChars  ),  *pIn  )  )  {		//  如果不是要转义的
			 if  (  !inBuf  )  {								//  如果输入串没有转移到inBuf中的话
				 pOut  ++  ;
				 nOut  ++  ;
				 continue;						
			 }
			 *pOut  =  *pIn;
			 pOut  ++  ;
			 nOut  ++  ;
			 continue;
		 }
		 if  (  !inBuf  )  {									//  因为要转义,所以将输入串转移到inBuf中
			 int  nLeft  =  cnt  -  (  pIn  -  str  );
			 nLeft  =  nLeft  *  sizeof(  TCHAR  );
             if  (  !(  inBuf  =  (  TCHAR  *  )mymalloc(  nLeft  )  )  )  goto  errLabel;
			 memcpy(  inBuf,  pIn,  nLeft  );
			 pIn  =  inBuf;
		 }
		 if  (  *pIn  <  256  )  {
			 if  (  cnt  -  1  -  nOut  <  4  )  break;
			 _sntprintf(  pOut,  4,  _T(  "{%02x}"  ),  (  unsigned  char  )*pIn  );
			 pOut  +=  4;
			 nOut  +=  4;
			 continue;
		 }
		 if  (  cnt  -  1  -  nOut  <  6  )  break;			//  不能容纳了,所以中断
		 _sntprintf(  pOut,  6,  _T(  "{%04x}"  ),  (  TCHAR  )qyhtons(  *pIn  )  );
		 pOut  +=  6;
		 nOut  +=  6;
		 continue;
	}
	str[nOut]  =  0;

	iErr  =  0;
errLabel:
	if  (  inBuf  )  free(  inBuf  );
	return  iErr;
}


 extern  "C"  int  unescapeTStr(  TCHAR  *  str,  unsigned  int  cnt  )
{
	int					iErr	=	-1;
	TCHAR			*	pIn;
	TCHAR			*	pOut;
    unsigned  int		nOut	=	0;
	TCHAR			*	p;
	TCHAR			*	p1;

	if  (  !str  ||  !cnt  )  return  0;

	if  (  cnt  ==  -1  )  cnt  =  lstrlen(  str  )  +  1;	//  当cnt为-1时，是当作一个以０结尾的字符串的
	else  str[cnt  -  1]  =  0;								//  确保0结尾
	
	//
	pIn  =  str;
	pOut  =  str;
	for  (  ;  *pIn  &&  nOut  <  cnt  -  1;  )  {
		if  (  *pIn  !=  '{'  )  {
			if  (  *pOut  !=  *pIn  )  *pOut  =  *pIn;
			 pOut  ++  ;
			 nOut  ++  ;
			 pIn  ++  ;
			 continue;
		 }
		 //
		 if  (  !(  p1  =  _tcschr(  pIn,  '}'  )  )  )  break;

		 if  (  p1  -  pIn  <=  4  )  {
             *pOut  =  (  TCHAR  )_tcstol(  pIn  +  1,  &p,  16  );
			 }
		 else  {
			   *pOut  =  (  TCHAR  )qyntohs(  (  TCHAR  )_tcstol(  pIn  +  1,  &p,  16  )  );		
		 }
		 
		 pOut  ++  ;
		 nOut  ++  ;

		 pIn  =  p1  +  1;

		 continue;
	}
	str[nOut]  =  0;

	iErr  =  0;
//  errLabel:
	return  iErr;
}








