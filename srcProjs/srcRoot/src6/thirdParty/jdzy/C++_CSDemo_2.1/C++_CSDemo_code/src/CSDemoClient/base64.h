
#ifndef __BASE64_H__
#define __BASE64_H__

#if (defined __GNUC__)||(defined LINUX)
#include "JITInterface.h"
#else
#include <tchar.h>
#endif
#include <memory>

#define BASE64_FLAG_NONE	0
#define BASE64_FLAG_NOPAD	1
#define BASE64_FLAG_CRLF	2

class CBase64
{
public:
	TCHAR *					Encode(const void *pBuffer, unsigned long nBufferSize, unsigned long dwFlags = BASE64_FLAG_NONE, unsigned long dwLineLenFlags = 64);
	unsigned char *			Decode(const TCHAR *lpszSource, unsigned long *pnResultLen);
	static unsigned long	GetEncodeRequiredLength(unsigned long nSrcLen, unsigned long dwFlags = BASE64_FLAG_NONE, unsigned long dwLineLenFlags = 64);

private:
	std::auto_ptr<TCHAR>			m_apEncoded;
	std::auto_ptr<unsigned char>	m_apDecoded;
};


#ifdef _MSC_VER
inline TCHAR * CBase64::Encode(const void *pBuffer, unsigned long nBufferSize, unsigned long dwFlags, unsigned long dwLineLenFlags)
{
	static const char s_chBase64EncodingTable[64] = {
	_T('A'), _T('B'), _T('C'), _T('D'), _T('E'), _T('F'), _T('G'), _T('H'), _T('I'), _T('J'), _T('K'), _T('L'), _T('M'), _T('N'), _T('O'), _T('P'), _T('Q'),
	_T('R'), _T('S'), _T('T'), _T('U'), _T('V'), _T('W'), _T('X'), _T('Y'), _T('Z'), _T('a'), _T('b'), _T('c'), _T('d'), _T('e'), _T('f'), _T('g'),	_T('h'),
	_T('i'), _T('j'), _T('k'), _T('l'), _T('m'), _T('n'), _T('o'), _T('p'), _T('q'), _T('r'), _T('s'), _T('t'), _T('u'), _T('v'), _T('w'), _T('x'), _T('y'),
	_T('z'), _T('0'), _T('1'), _T('2'), _T('3'), _T('4'), _T('5'), _T('6'), _T('7'), _T('8'), _T('9'), _T('+'), _T('/') };

	const unsigned char *pbSrcData = (unsigned char *)pBuffer;

	if (!pbSrcData || (nBufferSize == 0))
	{
		return NULL;
	}

	int nRequiredLen = 0;
	{
		__int64 nSrcLen4 = static_cast<__int64>(nBufferSize)*4;
		nRequiredLen = static_cast<int>(nSrcLen4 / 3);

		if ((dwFlags & BASE64_FLAG_NOPAD) == 0)
			nRequiredLen += nBufferSize % 3;

		int nCRLFs = nRequiredLen / dwLineLenFlags + 1;
		int nOnLastLine = nRequiredLen % dwLineLenFlags;

		if (nOnLastLine)
		{
			if (nOnLastLine % 4)
				nRequiredLen += 4-(nOnLastLine % 4);
		}

		nCRLFs *= 2;

		if ((dwFlags & BASE64_FLAG_CRLF) != 0)
			nRequiredLen += nCRLFs;
	}

	if (nRequiredLen == 0)
	{
		return NULL;
	}

	nRequiredLen++;
	
	m_apEncoded.reset(new TCHAR[nRequiredLen]);
	memset(m_apEncoded.get(), 0, nRequiredLen * sizeof(TCHAR));
	TCHAR *pszDest = m_apEncoded.get();

	int nWritten( 0 );
	int nLen1( (nBufferSize/3)*4 );
	int nLen2( nLen1/dwLineLenFlags );
	int nLen3( dwLineLenFlags / 4 );

	for (int i=0; i<=nLen2; i++)
	{
		if (i==nLen2)
			nLen3 = (nLen1%dwLineLenFlags)/4;

		for (int j=0; j<nLen3; j++)
		{
			unsigned long dwCurr(0);
			for (int n=0; n<3; n++)
			{
				dwCurr |= *pbSrcData++;
				dwCurr <<= 8;
			}
			for (int k=0; k<4; k++)
			{
				unsigned char b = (unsigned char)(dwCurr>>26);
				*pszDest++ = s_chBase64EncodingTable[b];
				dwCurr <<= 6;
			}
		}
		nWritten+= nLen3*4;

		if ((dwFlags & BASE64_FLAG_CRLF)!=0)
		{
			*pszDest++ = _T('\r');
			*pszDest++ = _T('\n');
			nWritten+= 2;
		}
	}

	if (nWritten && (dwFlags & BASE64_FLAG_CRLF)!=0)
	{
		pszDest-= 2;
		nWritten -= 2;
	}

	nLen2 = (nBufferSize%3) ? (nBufferSize%3 + 1) : 0;
	if (nLen2)
	{
		unsigned long dwCurr(0);
		for (unsigned long n=0; n<3; n++)
		{
			if (n<(nBufferSize%3))
				dwCurr |= *pbSrcData++;
			dwCurr <<= 8;
		}
		for (int k=0; k<nLen2; k++)
		{
			unsigned char b = (unsigned char)(dwCurr>>26);
			*pszDest++ = s_chBase64EncodingTable[b];
			dwCurr <<= 6;
		}
		nWritten+= nLen2;
		if ((dwFlags & BASE64_FLAG_NOPAD)==0)
		{
			nLen3 = nLen2 ? 4-nLen2 : 0;
			for (int j=0; j<nLen3; j++)
			{
				*pszDest++ = _T('=');
			}
			nWritten+= nLen3;
		}
	}

	m_apEncoded.get()[nWritten] = 0;

    // 去掉整64倍以后还有回车换行的问题
    if( nWritten>3 )
    {
        TCHAR* pszTemp = m_apEncoded.get();

        // 指向字符串结尾
        pszTemp += nWritten;

        // 指向最后一个字符
        pszTemp--;

        TCHAR* pszTemp1 = pszTemp;

        // 指向倒数第二个字符
        pszTemp1--;

        if( *pszTemp == _T('\n') && *pszTemp1 == _T('\r') )
        {
            *pszTemp = '\0';
            *pszTemp1 = '\0';
        }
    }


	return m_apEncoded.get();
}

inline unsigned char * CBase64::Decode(const TCHAR *lpszSource, unsigned long *pnResultLen)
{

#define DECODE_BASE64_CHAR(x)	(((x >= _T('A')) && (x <= _T('Z'))) ? (x - _T('A')) : (((x >= _T('a')) && (x <= _T('z'))) ? (x - _T('a') + 26) : (((x >= _T('0')) && (x <= _T('9'))) ? (x - _T('0') + 52) : ((x == _T('+')) ? 62 : ((x == _T('/')) ? 63 : -1)))))

	// walk the source buffer
	// each four character sequence is converted to 3 bytes
	// CRLFs and =, and any characters not in the encoding table
	// are skiped

	if (lpszSource == NULL || pnResultLen == NULL)
	{
		return NULL;
	}

	unsigned long nSrcLen = (unsigned long)_tcslen(lpszSource);
	if (nSrcLen == 0)
	{
		return NULL;
	}

	const TCHAR *szSrc = lpszSource;

	
	m_apDecoded.reset(new unsigned char[nSrcLen]);
	memset(m_apDecoded.get(), 0, nSrcLen);
	unsigned char *pbDest = m_apDecoded.get();

	const TCHAR *szSrcEnd = szSrc + nSrcLen;
	unsigned long nWritten = 0;

	bool bOverflow = (pbDest == NULL) ? true : false;

	while (szSrc < szSrcEnd &&(*szSrc) != 0)
	{
		unsigned long dwCurr = 0;
		int i;
		int nBits = 0;
		for (i=0; i<4; i++)
		{
			if (szSrc >= szSrcEnd)
				break;
			int nCh = DECODE_BASE64_CHAR(*szSrc);
			szSrc++;
			if (nCh == -1)
			{
				// skip this char
				i--;
				continue;
			}
			dwCurr <<= 6;
			dwCurr |= nCh;
			nBits += 6;
		}

		if(!bOverflow && nWritten + (nBits/8) > nSrcLen)
			bOverflow = true;

		// dwCurr has the 3 bytes to write to the output buffer
		// left to right
		dwCurr <<= 24-nBits;
		for (i=0; i<nBits/8; i++)
		{
			if(!bOverflow)
			{
				*pbDest = (unsigned char) ((dwCurr & 0x00ff0000) >> 16);
				pbDest++;
			}
			dwCurr <<= 8;
			nWritten++;
		}

	}

	*pnResultLen = nWritten;

	if(bOverflow)
	{
		return NULL;
	}

	return m_apDecoded.get();
}
#else
inline TCHAR * CBase64::Encode(const void *pBuffer, unsigned long nBufferSize, unsigned long dwFlags, unsigned long dwLineLenFlags)
{
	static const char s_chBase64EncodingTable[64] = {
	_T('A'), _T('B'), _T('C'), _T('D'), _T('E'), _T('F'), _T('G'), _T('H'), _T('I'), _T('J'), _T('K'), _T('L'), _T('M'), _T('N'), _T('O'), _T('P'), _T('Q'),
	_T('R'), _T('S'), _T('T'), _T('U'), _T('V'), _T('W'), _T('X'), _T('Y'), _T('Z'), _T('a'), _T('b'), _T('c'), _T('d'), _T('e'), _T('f'), _T('g'),	_T('h'),
	_T('i'), _T('j'), _T('k'), _T('l'), _T('m'), _T('n'), _T('o'), _T('p'), _T('q'), _T('r'), _T('s'), _T('t'), _T('u'), _T('v'), _T('w'), _T('x'), _T('y'),
	_T('z'), _T('0'), _T('1'), _T('2'), _T('3'), _T('4'), _T('5'), _T('6'), _T('7'), _T('8'), _T('9'), _T('+'), _T('/') };

	const unsigned char *pbSrcData = (unsigned char *)pBuffer;

	if (!pbSrcData || (nBufferSize == 0))
	{
		return NULL;
	}

	int nRequiredLen = 0;
	{

#ifdef _MSC_VER
		__int64 nSrcLen4 = static_cast<__int64>(nBufferSize)*4;
		nRequiredLen = static_cast<int>(nSrcLen4 / 3);
#else
		__int64 nSrcLen4 = (__int64)(nBufferSize) * 4;
		nRequiredLen = (int)(nSrcLen4 / 3);
#endif

		if ((dwFlags & BASE64_FLAG_NOPAD) == 0)
			nRequiredLen += nBufferSize % 3;

		int nCRLFs = nRequiredLen / dwLineLenFlags + 1;
		int nOnLastLine = nRequiredLen % dwLineLenFlags;

		if (nOnLastLine)
		{
			if (nOnLastLine % 4)
				nRequiredLen += 4-(nOnLastLine % 4);
		}

		nCRLFs *= 2;

		if ((dwFlags & BASE64_FLAG_CRLF) != 0)
			nRequiredLen += nCRLFs;
	}

	if (nRequiredLen == 0)
	{
		return NULL;
	}

	nRequiredLen++;
	
	m_apEncoded.reset(new TCHAR[nRequiredLen]);
	memset(m_apEncoded.get(), 0, nRequiredLen * sizeof(TCHAR));
	TCHAR *pszDest = m_apEncoded.get();

	int nWritten( 0 );
	int nLen1( (nBufferSize/3)*4 );
	int nLen2( nLen1/dwLineLenFlags );
	int nLen3( dwLineLenFlags / 4 );

	for (int i=0; i<=nLen2; i++)
	{
		if (i==nLen2)
			nLen3 = (nLen1%dwLineLenFlags)/4;

		for (int j=0; j<nLen3; j++)
		{
			unsigned int dwCurr(0);
			for (int n=0; n<3; n++)
			{
				dwCurr |= *pbSrcData++;
				dwCurr <<= 8;
			}
			for (int k=0; k<4; k++)
			{
				unsigned char b = (unsigned char)(dwCurr>>26);
				*pszDest++ = s_chBase64EncodingTable[b];
				dwCurr <<= 6;
			}
		}
		nWritten+= nLen3*4;

		if ((dwFlags & BASE64_FLAG_CRLF)!=0)
		{
			*pszDest++ = _T('\r');
			*pszDest++ = _T('\n');
			nWritten+= 2;
		}
	}

	if (nWritten && (dwFlags & BASE64_FLAG_CRLF)!=0)
	{
		pszDest-= 2;
		nWritten -= 2;
	}

	nLen2 = (nBufferSize%3) ? (nBufferSize%3 + 1) : 0;
	if (nLen2)
	{
		unsigned int dwCurr(0);
		for (unsigned int n=0; n<3; n++)
		{
			if (n<(nBufferSize%3))
				dwCurr |= *pbSrcData++;
			dwCurr <<= 8;
		}
		for (int k=0; k<nLen2; k++)
		{
			unsigned char b = (unsigned char)(dwCurr>>26);
			*pszDest++ = s_chBase64EncodingTable[b];
			dwCurr <<= 6;
		}
		nWritten+= nLen2;
		if ((dwFlags & BASE64_FLAG_NOPAD)==0)
		{
			nLen3 = nLen2 ? 4-nLen2 : 0;
			for (int j=0; j<nLen3; j++)
			{
				*pszDest++ = _T('=');
			}
			nWritten+= nLen3;
		}
	}

	m_apEncoded.get()[nWritten] = 0;

    // 去掉整64倍以后还有回车换行的问题
    if( nWritten>3 )
    {
        TCHAR* pszTemp = m_apEncoded.get();

        // 指向字符串结尾
        pszTemp += nWritten;

        // 指向最后一个字符
        pszTemp--;

        TCHAR* pszTemp1 = pszTemp;

        // 指向倒数第二个字符
        pszTemp1--;

        if( *pszTemp == _T('\n') && *pszTemp1 == _T('\r') )
        {
            *pszTemp = '\0';
            *pszTemp1 = '\0';
        }
    }


	return m_apEncoded.get();
}

inline unsigned char * CBase64::Decode(const TCHAR *lpszSource, unsigned long *pnResultLen)
{

#define DECODE_BASE64_CHAR(x)	(((x >= _T('A')) && (x <= _T('Z'))) ? (x - _T('A')) : (((x >= _T('a')) && (x <= _T('z'))) ? (x - _T('a') + 26) : (((x >= _T('0')) && (x <= _T('9'))) ? (x - _T('0') + 52) : ((x == _T('+')) ? 62 : ((x == _T('/')) ? 63 : -1)))))

	// walk the source buffer
	// each four character sequence is converted to 3 bytes
	// CRLFs and =, and any characters not in the encoding table
	// are skiped

	if (lpszSource == NULL || pnResultLen == NULL)
	{
		return NULL;
	}

	unsigned long nSrcLen = (unsigned long)_tcslen(lpszSource);
	if (nSrcLen == 0)
	{
		return NULL;
	}

	const TCHAR *szSrc = lpszSource;

	
	m_apDecoded.reset(new unsigned char[nSrcLen]);
	memset(m_apDecoded.get(), 0, nSrcLen);
	unsigned char *pbDest = m_apDecoded.get();

	const TCHAR *szSrcEnd = szSrc + nSrcLen;
	unsigned long nWritten = 0;

	bool bOverflow = (pbDest == NULL) ? true : false;

	while (szSrc < szSrcEnd &&(*szSrc) != 0)
	{
		unsigned int dwCurr = 0;
		int i;
		int nBits = 0;
		for (i=0; i<4; i++)
		{
			if (szSrc >= szSrcEnd)
				break;
			int nCh = DECODE_BASE64_CHAR(*szSrc);
			szSrc++;
			if (nCh == -1)
			{
				// skip this char
				i--;
				continue;
			}
			dwCurr <<= 6;
			dwCurr |= nCh;
			nBits += 6;
		}

		if(!bOverflow && nWritten + (nBits/8) > nSrcLen)
			bOverflow = true;

		// dwCurr has the 3 bytes to write to the output buffer
		// left to right
		dwCurr <<= 24-nBits;
		for (i=0; i<nBits/8; i++)
		{
			if(!bOverflow)
			{
				*pbDest = (unsigned char) ((dwCurr & 0x00ff0000) >> 16);
				pbDest++;
			}
			dwCurr <<= 8;
			nWritten++;
		}

	}

	*pnResultLen = nWritten;

	if(bOverflow)
	{
		return NULL;
	}

	return m_apDecoded.get();
}

#endif

inline unsigned long CBase64::GetEncodeRequiredLength(unsigned long nSrcLen, unsigned long dwFlags, unsigned long dwLineLenFlags)
{
#ifdef _MSC_VER
	__int64 nSrcLen4=static_cast<__int64>(nSrcLen)*4;

	unsigned long nRet = static_cast<unsigned long>(nSrcLen4/3);
#else
	__int64 nSrcLen4 = (__int64)(nSrcLen)*4;
	unsigned long nRet = (unsigned long)(nSrcLen4 / 3);
#endif

	if ((dwFlags & BASE64_FLAG_NOPAD) == 0)
		nRet += nSrcLen % 3;

	unsigned long nCRLFs = nRet / dwLineLenFlags + 1;
	unsigned long nOnLastLine = nRet % dwLineLenFlags;

	if (nOnLastLine)
	{
		if (nOnLastLine % 4)
			nRet += 4-(nOnLastLine % 4);
	}

	nCRLFs *= 2;

	if ((dwFlags & BASE64_FLAG_CRLF) != 0)
		nRet += nCRLFs;

	return nRet;
}

#endif
