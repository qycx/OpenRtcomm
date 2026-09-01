
#include	"stdafx.h"
#include	"qyCommon.h"
#include	"qyTCharCommProc.h"
#include	"Sms.h"
#include	"Comm.h"

// 可打印字符串转换为字节数据
// 如："C8329BFD0E01" --> {0xC8, 0x32, 0x9B, 0xFD, 0x0E, 0x01}
// 输入: pSrc - 源字符串指针
//       nSrcLength - 源字符串长度
// 输出: pDst - 目标数据指针
// 返回: 目标数据长度
 int  gsmString2Bytes(  const  unsigned  char  *  pSrc,  unsigned  char  *  pDst,  int  nSrcLength  )
{
	for (int i = 0; i < nSrcLength; i += 2)
	{
		// 输出高4位
		if ((*pSrc >= '0') && (*pSrc <= '9'))
		{
			*pDst = (*pSrc - '0') << 4;
		}
		else
		{
			*pDst = (*pSrc - 'A' + 10) << 4;
		}

		pSrc++;

		// 输出低4位
		if ((*pSrc>='0') && (*pSrc<='9'))
		{
			*pDst |= *pSrc - '0';
		}
		else
		{
			*pDst |= *pSrc - 'A' + 10;
		}

		pSrc++;
		pDst++;
	}

	// 返回目标数据长度
	return (nSrcLength / 2);
}

// 字节数据转换为可打印字符串
// 如：{0xC8, 0x32, 0x9B, 0xFD, 0x0E, 0x01} --> "C8329BFD0E01" 
// 输入: pSrc - 源数据指针
//       nSrcLength - 源数据长度
// 输出: pDst - 目标字符串指针
// 返回: 目标字符串长度
 int  gsmBytes2String(  const  unsigned  char  *  pSrc, unsigned  char  *  pDst,  int  nSrcLength  )
{
	const char tab[]="0123456789ABCDEF";	// 0x0-0xf的字符查找表

	for (int i = 0; i < nSrcLength; i++)
	{
		*pDst++ = tab[*pSrc >> 4];		// 输出高4位
		*pDst++ = tab[*pSrc & 0x0f];	// 输出低4位
		pSrc++;
	}

	// 输出字符串加个结束符
	*pDst = '\0';

	// 返回目标字符串长度
	return (nSrcLength * 2);
}

// 7bit编码
// 输入: pSrc - 源字符串指针
//       nSrcLength - 源字符串长度
// 输出: pDst - 目标编码串指针
// 返回: 目标编码串长度
int gsmEncode7bit(const char* pSrc, unsigned char* pDst, int nSrcLength)
{
	int nSrc;		// 源字符串的计数值
	int nDst;		// 目标编码串的计数值
	int nChar;		// 当前正在处理的组内字符字节的序号，范围是0-7
	unsigned char nLeft;	// 上一字节残余的数据

	// 计数值初始化
	nSrc = 0;
	nDst = 0;

	// 将源串每8个字节分为一组，压缩成7个字节
	// 循环该处理过程，直至源串被处理完
	// 如果分组不到8字节，也能正确处理
	while (nSrc < nSrcLength)
	{
		// 取源字符串的计数值的最低3位
		nChar = nSrc & 7;

		// 处理源串的每个字节
		if(nChar == 0)
		{
			// 组内第一个字节，只是保存起来，待处理下一个字节时使用
			nLeft = *pSrc;
		}
		else
		{
			// 组内其它字节，将其右边部分与残余数据相加，得到一个目标编码字节
			*pDst = (*pSrc << (8-nChar)) | nLeft;

			// 将该字节剩下的左边部分，作为残余数据保存起来
			nLeft = *pSrc >> nChar;

			// 修改目标串的指针和计数值
			pDst++;
			nDst++;
		}

		// 修改源串的指针和计数值
		pSrc++;
		nSrc++;
	}

	// 返回目标串长度
	return nDst;
}




/*
Note: a few characters actually count as two characters. These characters are:
{}[]~|\ and the Euro symbol: �
You can also see that in the table below in the hex column. These characters 
need to be escaped.
Below is the 7 bit default alphabet as specified by GSM 03.38. The corresponding 
ISO-8859-1 decimal codes are shown in the rightmost column. Note that the euro 
sign (�) is also included.
*/

 QY_DMITEM  CONST_gsm7bitTable[]  =
{
	{	0,	(  TCHAR  *  )64,	_T(  "COMMERCIAL AT@"  ),	},
	{	1,	(  TCHAR  *  )163,	_T(  "POUND SIGN￡"  ),		},
	{	2,	(  TCHAR  *  )36,	_T(  "DOLLAR SIGN$"  ),	},
	{	3,	(  TCHAR  *  )165,	_T(  "YEN SIGN￥"  ),	},
	{	4,	(  TCHAR  *  )232,	_T(  "LATIN SMALL LETTER E WITH GRAVEè"  ),	},
	{	5,	(  TCHAR  *  )233,	_T(  "LATIN SMALL LETTER E WITH ACUTEé"  ),	},
	{	6,	(  TCHAR  *  )249,	_T(  "LATIN SMALL LETTER U WITH GRAVEù"  ),	},
	{	7,	(  TCHAR  *  )236,	_T(  "LATIN SMALL LETTER I WITH GRAVEì"  ),	},
	{	8,	(  TCHAR  *  )242,	_T(  "LATIN SMALL LETTER O WITH GRAVEò"  ),	},
	{	9,	(  TCHAR  *  )199,	_T(  "LATIN CAPITAL LETTER C WITH CEDILLA?"  ),	},
	{	10,	(  TCHAR  *  )10,	_T(  "LINE FEED"  ),	},
	{	11,	(  TCHAR  *  )216,	_T(  "LATIN CAPITAL LETTER O WITH STROKE?"  ),	},
	{	12,	(  TCHAR  *  )248,	_T(  "LATIN SMALL LETTER O WITH STROKE?"  ),	},
	{	13,	(  TCHAR  *  )13,	_T(  "CARRIAGE RETURN"  ),	},
	{	14,	(  TCHAR  *  )197,	_T(  "LATIN CAPITAL LETTER A WITH RING ABOVE?"  ),	},
	{	15,	(  TCHAR  *  )229,	_T(  "LATIN SMALL LETTER A WITH RING ABOVE?"  ),	},
	{	16,	(  TCHAR  *  )0,	_T(  "GREEK CAPITAL LETTER DELTAΔ"  ),	},
	{	17,	(  TCHAR  *  )95,	_T(  "LOW LINE_"  ),	},
	{	18,	(  TCHAR  *  )0,	_T(  "GREEK CAPITAL LETTER PHIΦ"  ),	},
	{	19,	(  TCHAR  *  )0,	_T(  "GREEK CAPITAL LETTER GAMMAΓ"  ),	},
	{	20,	(  TCHAR  *  )0,	_T(  "GREEK CAPITAL LETTER LAMBDAΛ"  ),	},
	{	21,	(  TCHAR  *  )0,	_T(  "GREEK CAPITAL LETTER OMEGAΩ"  ),	},
	{	22,	(  TCHAR  *  )0,	_T(  "GREEK CAPITAL LETTER PIΠ"  ),	},
	{	23,	(  TCHAR  *  )0,	_T(  "GREEK CAPITAL LETTER PSIΨ"  ),	},
	{	24,	(  TCHAR  *  )0,	_T(  "GREEK CAPITAL LETTER SIGMAΣ"  ),	},
	{	25,	(  TCHAR  *  )0,	_T(  "GREEK CAPITAL LETTER THETAΘ"  ),	},
	{	26,	(  TCHAR  *  )0,	_T(  "GREEK CAPITAL LETTER XIΞ"  ),	},
	{	27,	(  TCHAR  *  )0,	_T(  "ESCAPE TO EXTENSION TABLE"  ),	},
	{	28,	(  TCHAR  *  )198,	_T(  "LATIN CAPITAL LETTER AE?"  ),	},
	{	29,	(  TCHAR  *  )230,	_T(  "LATIN SMALL LETTER AE?"  ),	},
	{	30,	(  TCHAR  *  )223,	_T(  "LATIN SMALL LETTER SHARP S {	German)?"  ),	},
	{	31,	(  TCHAR  *  )201,	_T(  "LATIN CAPITAL LETTER E WITH ACUTEé"  ),	},
	{	32,	(  TCHAR  *  )32,	_T(  "SPACE"  ),	},
	{	33,	(  TCHAR  *  )33,	_T(  "EXCLAMATION MARK!"  ),	},
	{	34,	(  TCHAR  *  )34,	_T(  "QUOTATION MARK“"  ),	},
	{	35,	(  TCHAR  *  )35,	_T(  "NUMBER SIGN#"  ),	},
	{	36,	(  TCHAR  *  )164,	_T(  "CURRENCY SIGN¤"  ),	},					//  {	ISO-8859-1)
	{	37,	(  TCHAR  *  )37,	_T(  "PERCENT SIGN%"  ),	},
	{	38,	(  TCHAR  *  )38,	_T(  "AMPERSAND&"  ),	},
	{	39,	(  TCHAR  *  )39,	_T(  "APOSTROPHE‘"  ),	},
	{	40,	(  TCHAR  *  )40,	_T(  "LEFT PARENTHESIS{	"  ),	},
	{	41,	(  TCHAR  *  )41,	_T(  "RIGHT PARENTHESIS)"  ),	},
	{	42,	(  TCHAR  *  )42,	_T(  "ASTERISK*"  ),	},
	{	43,	(  TCHAR  *  )43,	_T(  "PLUS SIGN+"  ),	},
	{	44,	(  TCHAR  *  )44,	_T(  "COMMA,"  ),	},
	{	45,	(  TCHAR  *  )45,	_T(  "HYPHEN-MINUS-"  ),	},
	{	46,	(  TCHAR  *  )46,	_T(  "FULL STOP."  ),	},
	{	47,	(  TCHAR  *  )47,	_T(  "SOLIDUS {	SLASH)/"  ),	},
	{	48,	(  TCHAR  *  )48,	_T(  "DIGIT ZERO0"  ),	},
	{	49,	(  TCHAR  *  )49,	_T(  "DIGIT ONE1"  ),	},
	{	50,	(  TCHAR  *  )50,	_T(  "DIGIT TWO2"  ),	},
	{	51,	(  TCHAR  *  )51,	_T(  "DIGIT THREE3"  ),	},
	{	52,	(  TCHAR  *  )52,	_T(  "DIGIT FOUR4"  ),	},
	{	53,	(  TCHAR  *  )53,	_T(  "DIGIT FIVE5"  ),	},
	{	54,	(  TCHAR  *  )54,	_T(  "DIGIT SIX6"  ),	},
	{	55,	(  TCHAR  *  )55,	_T(  "DIGIT SEVEN7"  ),	},
	{	56,	(  TCHAR  *  )56,	_T(  "DIGIT EIGHT8"  ),	},
	{	57,	(  TCHAR  *  )57,	_T(  "DIGIT NINE9"  ),	},
	{	58,	(  TCHAR  *  )58,	_T(  "COLON:"  ),	},
	{	59,	(  TCHAR  *  )59,	_T(  "SEMICOLON;"  ),	},
	{	60,	(  TCHAR  *  )60,	_T(  "LESS-THAN SIGN<"  ),	},
	{	61,	(  TCHAR  *  )61,	_T(  "EQUALS SIGN="  ),	},
	{	62,	(  TCHAR  *  )62,	_T(  "GREATER-THAN SIGN>"  ),	},
	{	63,	(  TCHAR  *  )63,	_T(  "QUESTION MARK?"  ),	},
	{	64,	(  TCHAR  *  )161,	_T(  "INVERTED EXCLAMATION MARK?"  ),	},
	{	65,	(  TCHAR  *  )65,	_T(  "LATIN CAPITAL LETTER AA"  ),	},
	{	66,	(  TCHAR  *  )66,	_T(  "LATIN CAPITAL LETTER BB"  ),	},
	{	67,	(  TCHAR  *  )67,	_T(  "LATIN CAPITAL LETTER CC"  ),	},
	{	68,	(  TCHAR  *  )68,	_T(  "LATIN CAPITAL LETTER DD"  ),	},
	{	69,	(  TCHAR  *  )69,	_T(  "LATIN CAPITAL LETTER EE"  ),	},
	{	70,	(  TCHAR  *  )70,	_T(  "LATIN CAPITAL LETTER FF"  ),	},
	{	71,	(  TCHAR  *  )71,	_T(  "LATIN CAPITAL LETTER GG"  ),	},
	{	72,	(  TCHAR  *  )72,	_T(  "LATIN CAPITAL LETTER HH"  ),	},
	{	73,	(  TCHAR  *  )73,	_T(  "LATIN CAPITAL LETTER II"  ),	},
	{	74,	(  TCHAR  *  )74,	_T(  "LATIN CAPITAL LETTER JJ"  ),	},
	{	75,	(  TCHAR  *  )75,	_T(  "LATIN CAPITAL LETTER KK"  ),	},
	{	76,	(  TCHAR  *  )76,	_T(  "LATIN CAPITAL LETTER LL"  ),	},
	{	77,	(  TCHAR  *  )77,	_T(  "LATIN CAPITAL LETTER MM"  ),	},
	{	78,	(  TCHAR  *  )78,	_T(  "LATIN CAPITAL LETTER NN"  ),	},
	{	79,	(  TCHAR  *  )79,	_T(  "LATIN CAPITAL LETTER OO"  ),	},
	{	80,	(  TCHAR  *  )80,	_T(  "LATIN CAPITAL LETTER PP"  ),	},
	{	81,	(  TCHAR  *  )81,	_T(  "LATIN CAPITAL LETTER QQ"  ),	},
	{	82,	(  TCHAR  *  )82,	_T(  "LATIN CAPITAL LETTER RR"  ),	},
	{	83,	(  TCHAR  *  )83,	_T(  "LATIN CAPITAL LETTER SS"  ),	},
	{	84,	(  TCHAR  *  )84,	_T(  "LATIN CAPITAL LETTER TT"  ),	},
	{	85,	(  TCHAR  *  )85,	_T(  "LATIN CAPITAL LETTER UU"  ),	},
	{	86,	(  TCHAR  *  )86,	_T(  "LATIN CAPITAL LETTER VV"  ),	},
	{	87,	(  TCHAR  *  )87,	_T(  "LATIN CAPITAL LETTER WW"  ),	},
	{	88,	(  TCHAR  *  )88,	_T(  "LATIN CAPITAL LETTER XX"  ),	},
	{	89,	(  TCHAR  *  )89,	_T(  "LATIN CAPITAL LETTER YY"  ),	},
	{	90,	(  TCHAR  *  )90,	_T(  "LATIN CAPITAL LETTER ZZ"  ),	},
	{	91,	(  TCHAR  *  )196,	_T(  "LATIN CAPITAL LETTER A WITH DIAERESIS?"  ),	},
	{	92,	(  TCHAR  *  )214,	_T(  "LATIN CAPITAL LETTER O WITH DIAERESIS?"  ),	},
	{	93,	(  TCHAR  *  )209,	_T(  "LATIN CAPITAL LETTER N WITH TILDE?"  ),	},
	{	94,	(  TCHAR  *  )220,	_T(  "LATIN CAPITAL LETTER U WITH DIAERESISü"  ),	},
	{	95,	(  TCHAR  *  )167,	_T(  "SECTION SIGN§"  ),	},
	{	96,	(  TCHAR  *  )191,	_T(  "INVERTED QUESTION MARK?"  ),	},
	{	97,	(  TCHAR  *  )97,	_T(  "LATIN SMALL LETTER Aa"  ),	},
	{	98,	(  TCHAR  *  )98,	_T(  "LATIN SMALL LETTER Bb"  ),	},
	{	99,	(  TCHAR  *  )99,	_T(  "LATIN SMALL LETTER Cc"  ),	},
	{	100,	(  TCHAR  *  )100,	_T(  "LATIN SMALL LETTER Dd"  ),	},
	{	101,	(  TCHAR  *  )101,	_T(  "LATIN SMALL LETTER Ee"  ),	},
	{	102,	(  TCHAR  *  )102,	_T(  "LATIN SMALL LETTER Ff"  ),	},
	{	103,	(  TCHAR  *  )103,	_T(  "LATIN SMALL LETTER Gg"  ),	},
	{	104,	(  TCHAR  *  )104,	_T(  "LATIN SMALL LETTER Hh"  ),	},
	{	105,	(  TCHAR  *  )105,	_T(  "LATIN SMALL LETTER Ii"  ),	},
	{	106,	(  TCHAR  *  )106,	_T(  "LATIN SMALL LETTER Jj"  ),	},
	{	107,	(  TCHAR  *  )107,	_T(  "LATIN SMALL LETTER Kk"  ),	},
	{	108,	(  TCHAR  *  )108,	_T(  "LATIN SMALL LETTER Ll"  ),	},
	{	109,	(  TCHAR  *  )109,	_T(  "LATIN SMALL LETTER Mm"  ),	},
	{	110,	(  TCHAR  *  )110,	_T(  "LATIN SMALL LETTER Nn"  ),	},
	{	111,	(  TCHAR  *  )111,	_T(  "LATIN SMALL LETTER Oo"  ),	},
	{	112,	(  TCHAR  *  )112,	_T(  "LATIN SMALL LETTER Pp"  ),	},
	{	113,	(  TCHAR  *  )113,	_T(  "LATIN SMALL LETTER Qq"  ),	},
	{	114,	(  TCHAR  *  )114,	_T(  "LATIN SMALL LETTER Rr"  ),	},
	{	115,	(  TCHAR  *  )115,	_T(  "LATIN SMALL LETTER Ss"  ),	},
	{	116,	(  TCHAR  *  )116,	_T(  "LATIN SMALL LETTER Tt"  ),	},
	{	117,	(  TCHAR  *  )117,	_T(  "LATIN SMALL LETTER Uu"  ),	},
	{	118,	(  TCHAR  *  )118,	_T(  "LATIN SMALL LETTER Vv"  ),	},
	{	119,	(  TCHAR  *  )119,	_T(  "LATIN SMALL LETTER Ww"  ),	},
	{	120,	(  TCHAR  *  )120,	_T(  "LATIN SMALL LETTER Xx"  ),	},
	{	121,	(  TCHAR  *  )121,	_T(  "LATIN SMALL LETTER Yy"  ),	},
	{	122,	(  TCHAR  *  )122,	_T(  "LATIN SMALL LETTER Zz"  ),	},
	{	123,	(  TCHAR  *  )228,	_T(  "LATIN SMALL LETTER A WITH DIAERESIS?"  ),	},
	{	124,	(  TCHAR  *  )246,	_T(  "LATIN SMALL LETTER O WITH DIAERESIS?"  ),	},
	{	125,	(  TCHAR  *  )241,	_T(  "LATIN SMALL LETTER N WITH TILDE?"  ),	},
	{	126,	(  TCHAR  *  )252,	_T(  "LATIN SMALL LETTER U WITH DIAERESISü"  ),	},
	{	127,	(  TCHAR  *  )224,	_T(  "LATIN SMALL LETTER A WITH GRAVEà"  ),	},
	{	-1,		},
};
	
 //  27		ESCAPE TO EXTENSION TABLE 
 QY_DMITEM  CONST_gsm7bitEscapeTable[]  =
{
 	{	10,	(  TCHAR  *  )12,	_T(  "FORM FEED"  ),	},
	{	20,	(  TCHAR  *  )94,	_T(  "CIRCUMFLEX ACCENT^"  ),	},
	{	40,	(  TCHAR  *  )123,	_T(  "LEFT CURLY BRACKET{"  ),	},
	{	41,	(  TCHAR  *  )125,	_T(  "RIGHT CURLY BRACKET}"  ),	},
	{	47,	(  TCHAR  *  )92,	_T(  "REVERSE SOLIDUS (BACKSLASH)\\"  ),	},
	{	60,	(  TCHAR  *  )91,	_T(  "LEFT SQUARE BRACKET["  ),	},
	{	61,	(  TCHAR  *  )126,	_T(  "TILDE~"  ),	},
	{	62,	(  TCHAR  *  )93,	_T(  "RIGHT SQUARE BRACKET]"  ),	},
	{	64,	(  TCHAR  *  )124,	_T(  "VERTICAL BAR|"  ),	},
	{	101,(  TCHAR  *  )164,	_T(  "EURO SIGN�"  ),	},				   //  (ISO-8859-15)
	{	-1,		},
};



 




// 7bit解码
// 输入: pSrc - 源编码串指针
//       nSrcLength - 源编码串长度
// 输出: pDst - 目标字符串指针
// 返回: 目标字符串长度
 int  gsmDecode7bit(  const  unsigned  char  *  pSrc,  int  nSrcLength,  int  nRealDstLen,  unsigned  char  *  pDstParam,  int  nDstSize  )
{
	int						nSrc		=	0;		//  源字符串的计数值
	int						nDst		=	0;		//  目标解码串的计数值
	int						nByte		=	0;		//  当前正在处理的组内字节的序号，范围是0-6
	unsigned  char			nLeft		=	0;		//  上一字节残余的数据
	unsigned  char			buf[4096]	=	"";
	unsigned  char		*	pDst		=	buf;

	if  (  mycountof(  buf  )  *  7  <  nSrcLength  *  8  +  256  )  return  -1;		//  这个256只是让缓存大一点，没有特殊含义，2008/01/10  

	// 将源数据每7个字节分为一组，解压缩成8个字节
	// 循环该处理过程，直至源数据被处理完
	// 如果分组不到7字节，也能正确处理
	while  (  nSrc  <  nSrcLength  )  {
		   // 将源字节右边部分与残余数据相加，去掉最高位，得到一个目标解码字节
		   *pDst  =  (  (  *pSrc  <<  nByte  )  |  nLeft  )  &  0x7f;

		   //  将该字节剩下的左边部分，作为残余数据保存起来
		   nLeft  =  *pSrc  >>  (  7  -  nByte  );

		   // 修改目标串的指针和计数值
		   pDst++;
		   nDst++;

		   // 修改字节计数值
		   nByte++;

		   // 到了一组的最后一个字节
		   if  (  nByte  ==  7  )  {
			   // 额外得到一个目标解码字节
			   *pDst = nLeft;

			   // 修改目标串的指针和计数值
			   pDst++;
			   nDst++;

			   // 组内字节序号和残余数据初始化
			   nByte = 0;
			   nLeft = 0;
		
		   }

		   // 修改源串的指针和计数值
		   pSrc++;
		   nSrc++;	
	}

	// 输出字符串加个结束符
	*pDst  =  '\0';

	//  2008/01/10， 按照对照表，输出最后的字符
	int		i, index;
	BOOL	bEscaped;
	bEscaped  =  FALSE;
	for  (  i  =  0,  index  =  0;  i  <  nDst  &&  index  <  nDstSize  +  1;  i  ++  )  {
		 if  (  buf[i]  ==  27  )  {
			 bEscaped  =  TRUE;  continue;
		 }
		 //  traceLogA(  "countof(  gsm7bitTable  )  is %d",  mycountof(  CONST_gsm7bitTable  )  );
		 //	
		 if  (  !bEscaped  )  {
			 if  (  buf[i]  >=  mycountof(  CONST_gsm7bitTable  )  -  1  )  continue;
			 //
			 pDstParam[index]  =  (  unsigned  char  )CONST_gsm7bitTable[buf[i]].des;
			 }
		 else  {
			   bEscaped  =  FALSE;
			   //
               pDstParam[index]  =  (  unsigned  char  )qyGetDesByType(  CONST_gsm7bitEscapeTable,  buf[i]  );
		 }

		 //  得到的值为0，
		 if  (  pDstParam[index]  &&  pDstParam[index]  !=  -1  )  index  ++  ;
	}
	index  =  min(  index,  nRealDstLen  );		//  注意：7bit的实际长度是由发送方直接发过来的。
	pDstParam[index]  =  0;	//  结束符


	// 返回目标串长度
	return  index;
}

// 8bit编码
// 输入: pSrc - 源字符串指针
//       nSrcLength - 源字符串长度
// 输出: pDst - 目标编码串指针
// 返回: 目标编码串长度
int gsmEncode8bit(const char* pSrc, unsigned char* pDst, int nSrcLength)
{
	// 简单复制
	memcpy(pDst, pSrc, nSrcLength);

	return nSrcLength;
}

// 8bit解码
// 输入: pSrc - 源编码串指针
//       nSrcLength -  源编码串长度
// 输出: pDst -  目标字符串指针
// 返回: 目标字符串长度
int gsmDecode8bit(const unsigned char* pSrc, char* pDst, int nSrcLength)
{
	// 简单复制
	memcpy(pDst, pSrc, nSrcLength);

	// 输出字符串加个结束符
	*pDst = '\0';

	return nSrcLength;
}

// UCS2编码
// 输入: pSrc - 源字符串指针
//       nSrcLength - 源字符串长度
// 输出: pDst - 目标编码串指针
// 返回: 目标编码串长度
 int  gsmEncodeUcs2(  TP_UDH_concatenatedSm  *  pUdh,  LPCTSTR  pSrc, int  nSrcLen,  unsigned  char  *  pDst,  unsigned  int  nDstSize  )
{
	int					iErr					=	-1;
	unsigned  int		nUdhLenInBytes			=	0;
	unsigned  int		nDstLenInBytes			=	0;		// UNICODE宽字符数目
	int					i;
	
	if  (  !pUdh  ||  !pSrc  )  return  -1;
	
	if  (  pUdh->ucMaxNum  )  {
		nUdhLenInBytes  =  pUdh->ucUDHL  +  1;
	}

	if  (  nUdhLenInBytes  +  2  *  nSrcLen  >=  nDstSize  )  goto  errLabel;

	if  (  nUdhLenInBytes  )  {
					*  pDst  =  pUdh->ucUDHL;
		pDst  ++  ;	*  pDst  =  pUdh->ucIEI;
		pDst  ++  ;	*  pDst  =  pUdh->ucIEIDL;
		pDst  ++  ;	*  pDst  =  pUdh->ucRefrenceNo;
		pDst  ++  ;	*  pDst  =  pUdh->ucMaxNum;
		pDst  ++  ;	*  pDst  =  pUdh->ucSeqNo;
		pDst  ++  ;

	}	

	// 高低字节对调，输出
	for  (  i=0; i<nSrcLen; i++)  {
		 *pDst++ = pSrc[i] >> 8;		// 先输出高位字节
		 *pDst++ = pSrc[i] & 0xff;		// 后输出低位字节
	}
	nDstLenInBytes  =  nUdhLenInBytes  +  2  *  nSrcLen;
	*pDst  =  0;

	iErr  =  0;
errLabel:
	// 返回目标编码串长度
	return  iErr  ?  iErr  :  nDstLenInBytes;
}

// UCS2解码
// 输入: pSrc - 源编码串指针
//       nSrcLength -  源编码串长度
// 输出: pDst -  目标字符串指针
// 返回: 目标字符串长度
 int  gsmDecodeUcs2(  const  unsigned  char  *  pSrc,  unsigned  int  nSrcLength,  TCHAR  *  pDst,  unsigned  int  nDstSize  )
{
	int		nDstLength		=	0;				//  UNICODE宽字符数目
	WCHAR	wBuf[256]		=	_T(  ""  );		//  UNICODE串缓冲区
	int		i				=	0;

	if  (  nSrcLength  /  2  +  1  >=  mycountof(  wBuf  )  )  return  -1;

	// 高低字节对调，拼成UNICODE
	for  (  i  =  0;  i  <  (  int  )(  nSrcLength  /  2  );  i  ++  )  {
		 wBuf[i] = *pSrc++ << 8;	// 先高位字节
		 wBuf[i] |= *pSrc++;		// 后低位字节
	}
	wBuf[i]  =  0;

	lstrcpyn(  pDst,  wBuf,  nDstSize  );

	// 返回目标字符串长度
	return  nDstLength;
}

// 正常顺序的字符串转换为两两颠倒的字符串，若长度为奇数，补'F'凑成偶数
// 如："8613851872468" --> "683158812764F8"
// 输入: pSrc - 源字符串指针
//       nSrcLength - 源字符串长度
// 输出: pDst - 目标字符串指针
// 返回: 目标字符串长度
 int  gsmInvertNumbers(  const  unsigned  char  *  pSrc,  unsigned  char  *  pDst,  int  nSrcLength  )
{
	int nDstLength;		// 目标字符串长度
	char ch;			// 用于保存一个字符

	// 复制串长度
	nDstLength = nSrcLength;

	// 两两颠倒
	for(int i=0; i<nSrcLength;i+=2)
	{
		ch = *pSrc++;		// 保存先出现的字符
		*pDst++ = *pSrc++;	// 复制后出现的字符
		*pDst++ = ch;		// 复制先出现的字符
	}

	// 源串长度是奇数吗？
	if(nSrcLength & 1)
	{
		*(pDst-2) = 'F';	// 补'F'
		nDstLength++;		// 目标串长度加1
	}

	// 输出字符串加个结束符
	*pDst = '\0';

	// 返回目标字符串长度
	return nDstLength;
}

// 两两颠倒的字符串转换为正常顺序的字符串
// 如："683158812764F8" --> "8613851872468"
// 输入: pSrc - 源字符串指针
//       nSrcLength - 源字符串长度
// 输出: pDst - 目标字符串指针
// 返回: 目标字符串长度
int gsmSerializeNumbers(const char* pSrc, char* pDst, int nSrcLength)
{
	int nDstLength;		// 目标字符串长度
	char ch;			// 用于保存一个字符

	// 复制串长度
	nDstLength = nSrcLength;

	// 两两颠倒
	for(int i=0; i<nSrcLength;i+=2)
	{
		ch = *pSrc++;		// 保存先出现的字符
		*pDst++ = *pSrc++;	// 复制后出现的字符
		*pDst++ = ch;		// 复制先出现的字符
	}

	// 最后的字符是'F'吗？
	if(*(pDst-1) == 'F')
	{
		pDst--;
		nDstLength--;		// 目标字符串长度减1
	}

	// 输出字符串加个结束符
	*pDst = '\0';

	// 返回目标字符串长度
	return nDstLength;
}



// PDU编码，用于编制、发送短消息
// 输入: pSrc - 源PDU参数指针
// 输出: pDst - 目标PDU串指针
// 返回: 目标PDU串长度
 int  gsmEncodePdu(  SM_PARAM  *  pSrc,  unsigned  char  *  pDst,  unsigned  int  nDstSize  )
{
	int				iErr					=	-1;
	int				nLength;							//  内部用的串长度
	int				nDstLength;							//  目标PDU串长度
	unsigned char	buf[256]				=	"";		//  内部用的缓冲区
	unsigned  int	nSent					=	0;
	TCHAR			TP_UD[256  +  1]		=	_T(  ""  );
	char			TP_UD_utf8[256  +  1]	=	"";		//  对7BIT等编码，需要用utf8来进行处理
	//
	unsigned  char	ucUDHL					=	0;
	unsigned  int	uiMaxCharsPerSend		=	CONST_maxCharsPerSend_UCS2;		



	// SMSC地址信息段
	nLength = strlen(pSrc->SCA);											//  SMSC地址字符串的长度	
	buf[0] = (char)((nLength & 1) == 0 ? nLength : nLength + 1) / 2 + 1;	//  SMSC地址信息长度
	buf[1] = 0x91;															//  固定: 用国际格式号码
	nDstLength = gsmBytes2String(buf, pDst, 2);								//  转换2个字节到目标PDU串
	nDstLength += gsmInvertNumbers(  (  const  unsigned  char  *  )pSrc->SCA, &pDst[nDstLength], nLength);	//  转换SMSC号码到目标PDU串

	//  pSrc
	if  (  !pSrc->tpUdhU.concatenatedSm.ucMaxNum  )  {
		nLength  =  lstrlen(  pSrc->TP_UD  );
		if  (  nLength  >  CONST_maxCharsPerSend_UCS2  )  {
			ucUDHL					=	5;
			uiMaxCharsPerSend		=	CONST_maxCharsPerSend_UCS2  -  (  ucUDHL  +  1  )  /  2;		//  这个6是一个UDH加上表示长度的字节
			unsigned  int	uiMaxNum				=	nLength  /  uiMaxCharsPerSend  +  1;
			static  unsigned  char  sucRefrenceNo	=	0;
			//
			if  (  uiMaxNum  >  255  )  uiMaxNum  =  255;
			pSrc->tpUdhU.concatenatedSm.ucMaxNum  =  (  unsigned  char  )uiMaxNum;
			pSrc->tpUdhU.concatenatedSm.ucUDHL  =  ucUDHL;
			pSrc->tpUdhU.concatenatedSm.ucIEI  =  0;
			pSrc->tpUdhU.concatenatedSm.ucIEIDL  =  3;
			pSrc->tpUdhU.concatenatedSm.ucRefrenceNo  =  (  sucRefrenceNo  ++  );  
		}
	}
	if  (  pSrc->tpUdhU.concatenatedSm.ucMaxNum  )  {
		ucUDHL					=	5;
		uiMaxCharsPerSend		=	CONST_maxCharsPerSend_UCS2  -  (  ucUDHL  +  1  )  /  2;		//  这个6是一个UDH加上表示长度的字节
		nSent  =  pSrc->tpUdhU.concatenatedSm.ucSeqNo  *  uiMaxCharsPerSend;
		//
		pSrc->tpUdhU.concatenatedSm.ucSeqNo  ++  ;
		if  (  pSrc->tpUdhU.concatenatedSm.ucSeqNo  >  pSrc->tpUdhU.concatenatedSm.ucMaxNum  )  goto  errLabel;	//  早已发完了，这里说明控制出错了
	}
	

	//  TPDU段基本参数、目标地址等
	nLength = strlen(pSrc->TPA);	//  TP-DA地址字符串的长度
	buf[0] = pSrc->tpUdhU.concatenatedSm.ucMaxNum  ?  0x51  :  0x11;					//  是发送短信(TP-MTI=01)，TP-VP用相对格式(TP-VPF=10)
	buf[1] = 0;						//  TP-MR=0
	buf[2] = (char)nLength;			//  目标地址数字个数(TP-DA地址字符串真实长度)
	buf[3] = 0x91;					//  固定: 用国际格式号码
	nDstLength += gsmBytes2String(buf, &pDst[nDstLength], 4);				//  转换4个字节到目标PDU串
	nDstLength += gsmInvertNumbers(  (  const  unsigned  char  *  )pSrc->TPA, &pDst[nDstLength], nLength);	//  转换TP-DA到目标PDU串

	lstrcpyn(  TP_UD,  pSrc->TP_UD  +  nSent,  min(  uiMaxCharsPerSend  +  1,  mycountof(  TP_UD  )  )  );
	if  (  !myTChar2Utf8(  TP_UD,  TP_UD_utf8,  mycountof(  TP_UD_utf8  )  )  )  goto  errLabel;

	traceLogA(  "gsmEncodePdu: 将发送[%S]",  TP_UD  );

	// TPDU段协议标识、编码方式、用户信息等
	nLength = strlen(  TP_UD_utf8  );	// 用户信息字符串的长度
	buf[0] = pSrc->TP_PID;				// 协议标识(TP-PID)
	buf[1] = pSrc->TP_DCS;				// 用户信息编码方式(TP-DCS)
	buf[2] = 0;							// 有效期(TP-VP)为5分钟
	if  (  pSrc->TP_DCS == GSM_7BIT)  {
		// 7-bit编码方式
		buf[3] = nLength;			// 编码前长度
		nLength = gsmEncode7bit(  TP_UD_utf8, &buf[4], nLength+1) + 4;	// 转换TP-DA到目标PDU串
		}
	else  if  (  pSrc->TP_DCS == GSM_UCS2)  {
			  nLength  =  lstrlen(  TP_UD  );
			  // UCS2编码方式
			  buf[3] = gsmEncodeUcs2(  &pSrc->tpUdhU.concatenatedSm,  TP_UD, nLength,  &buf[4],  mycountof(  buf  )  -  4  );	// 转换TP-DA到目标PDU串
			  nLength = buf[3] + 4;		// nLength等于该段数据长度
			}
	else  {
		  // 8-bit编码方式
		  buf[3] = gsmEncode8bit(  TP_UD_utf8, &buf[4], nLength);	// 转换TP-DA到目标PDU串
		  nLength = buf[3] + 4;		// nLength等于该段数据长度
	}
	nDstLength += gsmBytes2String(buf, &pDst[nDstLength], nLength);		// 转换该段数据到目标PDU串

	iErr  =  0;
errLabel:
	// 返回目标字符串长度
	return  iErr  ?  iErr  :  nDstLength;
}

// PDU解码，用于接收、阅读短消息
// 输入: pSrc - 源PDU串指针
// 输出: pDst - 目标PDU参数指针
// 返回: 用户信息串长度
 int  gsmDecodePdu(  const  unsigned  char  *  pSrc,  SM_PARAM  *  pDst  )
{
	int						iErr					=	-1;
	int						nDstLength;							//  目标PDU串长度
	unsigned  char			tmp;								//  内部用的临时字节变量
	unsigned  char			buf[256]				=	"";		//  内部用的缓冲区
	FIRST_OCTET_deliver  *  pFirstOctet				=	NULL;
	char					TP_UD_buf[4096  +  1]	=	"";		//  对7BIT等编码，


	// SMSC地址信息段
	gsmString2Bytes(pSrc, &tmp, 2);					// 取长度
	tmp = (tmp - 1) * 2;							// SMSC号码串长度
	pSrc += 4;		// 指针后移，忽略了SMSC地址格式
	gsmSerializeNumbers(  (  const  char  *  )pSrc, pDst->SCA, tmp);		// 转换SMSC号码到目标PDU串
	pSrc += tmp;	// 指针后移

	// TPDU段基本参数
	gsmString2Bytes(pSrc, &tmp, 2);	// 取基本参数
	traceLogA(  "fistOctet is %d byte",  sizeof(  pDst->firstOctet  )  );
	memcpy(  &pDst->firstOctet,  &tmp,  sizeof(  pDst->firstOctet  )  );
	pFirstOctet  =  (  FIRST_OCTET_deliver  *  )&pDst->firstOctet;
	//
	pSrc += 2;		// 指针后移

	// 取回复号码
	gsmString2Bytes(pSrc, &tmp, 2);	// 取长度
	if(tmp & 1) tmp += 1;	// 调整奇偶性
	pSrc += 4;			// 指针后移，忽略了回复地址(TP-RA)格式
	gsmSerializeNumbers(  (  const  char  *  )pSrc, pDst->TPA, tmp);	// 取TP-RA号码
	pSrc += tmp;		// 指针后移

	// TPDU段协议标识、编码方式、用户信息等
	gsmString2Bytes(pSrc, (unsigned char*)&pDst->TP_PID, 2);	// 取协议标识(TP-PID)
	pSrc += 2;		// 指针后移
	gsmString2Bytes(pSrc, (unsigned char*)&pDst->TP_DCS, 2);	// 取编码方式(TP-DCS)
	pSrc += 2;		// 指针后移
	gsmSerializeNumbers(  (  const  char  *  )pSrc, pDst->TP_SCTS, 14);				// 服务时间戳字符串(TP_SCTS) 
	pSrc += 14;		// 指针后移
	gsmString2Bytes(pSrc, &tmp, 2);								// 用户信息长度(TP-UDL)
	pSrc += 2;		// 指针后移
	if  (  pDst->TP_DCS == GSM_7BIT  )  {
		// 7-bit解码
		nDstLength = gsmString2Bytes(pSrc, buf, tmp & 7 ? (int)tmp * 7 / 4 + 2 : (int)tmp * 7 / 4);		//  格式转换
		gsmDecode7bit(  buf, nDstLength, tmp,  (  unsigned  char  *  )TP_UD_buf,  mycountof(  TP_UD_buf  )  );		//  转换到TP-DU
		//
		myUtf82TChar(  TP_UD_buf,  pDst->TP_UD,  mycountof(  pDst->TP_UD  )  );
		//
		nDstLength = tmp;
		}
	else  if  (  pDst->TP_DCS == GSM_UCS2  )  {
			  // UCS2解码
			  nDstLength = gsmString2Bytes(pSrc, buf, tmp * 2);			// 格式转换
			  nDstLength = gsmDecodeUcs2(  buf,  nDstLength,  pDst->TP_UD,  mycountof(  pDst->TP_UD  )  );	// 转换到TP-DU
			}
	else  {
		  // 8-bit解码
		  nDstLength = gsmString2Bytes(pSrc, buf, tmp * 2);			// 格式转换
		  nDstLength = gsmDecode8bit(buf, TP_UD_buf, nDstLength);	// 转换到TP-DU
		  //
		  myUtf82TChar(  TP_UD_buf,  pDst->TP_UD,  mycountof(  pDst->TP_UD  )  );
	}

	// 返回目标字符串长度
	return  nDstLength;
}


// 发送短消息，仅发送命令，不读取应答
// 输入: pSrc - 源PDU参数指针
 int  gsmSendMessage(  HANDLE  hComm,  SM_PARAM  *  pSrc  )
{
	int				nPduLength;					// PDU串长度
	unsigned  char	nSmscLength;				// SMSC串长度
	int				nLength;					// 串口收到的数据长度
	char			cmd[16];					// 命令串
	char			pdu[512]		=	"";		// PDU串
	char			ans[128];					// 应答串

	nPduLength  =  gsmEncodePdu(  pSrc,  (  unsigned  char  *  )pdu,  mycountof(  pdu  )  );	// 根据PDU参数，编码PDU串
	strcat(pdu, "\x01a");		// 以Ctrl-Z结束

	gsmString2Bytes(  (  const  unsigned  char  *  )pdu, &nSmscLength, 2);	// 取PDU串中的SMSC信息长度
	nSmscLength++;		// 加上长度字节本身

	// 命令中的长度，不包括SMSC信息长度，以数据字节计
	sprintf(cmd, "AT+CMGS=%d\r", nPduLength / 2 - nSmscLength);	// 生成命令

//	TRACE("%s", cmd);
//	TRACE("%s\n", pdu);

	writeComm(  hComm,  cmd, strlen(cmd));	// 先输出命令串

	nLength = readComm(  hComm,  ans, 128);	// 读应答数据

	// 根据能否找到"\r\n> "决定成功与否
	if(nLength == 4 && strncmp(ans, "\r\n> ", 4) == 0)
	{
		return writeComm(  hComm,  pdu, strlen(pdu));		// 得到肯定回答，继续输出PDU串
	}

	return 0;
}

// 读取短消息，仅发送命令，不读取应答
// 用+CMGL代替+CMGR，可一次性读出全部短消息
int gsmReadMessageList(  HANDLE  hComm  )
{
	return writeComm(  hComm,  "AT+CMGL\r", 8);
}

// 删除短消息，仅发送命令，不读取应答
// 输入: index - 短消息序号，1-255
int gsmDeleteMessage(  HANDLE  hComm,  int index)
{
	char cmd[16];		// 命令串

	sprintf(cmd, "AT+CMGD=%d\r", index);	// 生成命令

	// 输出命令串
	return writeComm(  hComm,  cmd, strlen(cmd));
}

// 读取GSM MODEM的应答，可能是一部分
// 输出: pBuff - 接收应答缓冲区
// 返回: GSM MODEM的应答状态, GSM_WAIT/GSM_OK/GSM_ERR
// 备注: 可能需要多次调用才能完成读取一次应答，首次调用时应将pBuff初始化
int gsmGetResponse(HANDLE  hComm,  SM_BUFF* pBuff)
{
	int nLength;		// 串口收到的数据长度
	int nState;

	// 从串口读数据，追加到缓冲区尾部
	nLength = readComm(  hComm,  &pBuff->data[pBuff->len], 128);	
	pBuff->len += nLength;

	// 确定GSM MODEM的应答状态
	nState = GSM_WAIT;
	if ((nLength > 0) && (pBuff->len >= 4))
	{
		if (strncmp(&pBuff->data[pBuff->len - 4], "OK\r\n", 4) == 0)  nState = GSM_OK;
		else if (strstr(pBuff->data, "+CMS ERROR") != NULL) nState = GSM_ERR;
	}

	return nState;
}

// 从列表中解析出全部短消息
// 输入: pBuff - 短消息列表缓冲区
// 输出: pMsg - 短消息缓冲区
// 返回: 短消息条数
int gsmParseMessageList(SM_PARAM* pMsg, SM_BUFF* pBuff)
{
	int nMsg;			// 短消息计数值
	char* ptr;			// 内部用的数据指针

	nMsg = 0;
	ptr = pBuff->data;

	// 循环读取每一条短消息, 以"+CMGL:"开头
	while((ptr = strstr(ptr, "+CMGL:")) != NULL)
	{
		ptr += 6;		// 跳过"+CMGL:", 定位到序号
		sscanf(ptr, "%d", &pMsg->index);	// 读取序号
//		TRACE("  index=%d\n",pMsg->index);

		ptr = strstr(ptr, "\r\n");	// 找下一行
		if (ptr != NULL)
		{
			ptr += 2;		// 跳过"\r\n", 定位到PDU
			
			gsmDecodePdu(  (  const  unsigned  char  *  )ptr, pMsg);	// PDU串解码

			pMsg++;		// 准备读下一条短消息
			nMsg++;		// 短消息计数加1
		}
	}

	return nMsg;
}
