#undef  AFX_DATA
#define AFX_DATA AFX_EXT_DATA

#ifndef _EmailProcess
#define _EmailProcess

#include "constant.h"
#include "EmailStruct.h"

class  CEmailProcess
{
public:	
	CEmailProcess();
	CEmailProcess( char *b2gTableFileName, char *g2bTableFileName );
	~CEmailProcess();
public:
	//mail process
	int ProcessHttp(unsigned char *pMailBodyBuffer,int iFileLen,FILE *file,char *pMailName,int iEmailType);
	int ProcessSmtp(unsigned char *pMailBodyBuffer,int iFileLen,FILE *file,char *pMailName,int iEmailType);

	int GetMailToBuffer(char *pMailName);
	int Compare4Digit(int digit1,int digit2,int digit3,int digit4, int digit5);
	
	int KMP_FindString(unsigned char *buf,char *token,int nb,int nt);
	void InitStruct();

	//Functions for decode
	unsigned long Base64To(unsigned char* m_pcStart);	//base64
	unsigned char decode_hex(unsigned char *streamptr);					//QP subprocess
	int DecodeQP(unsigned char *pQPBuf,int iLen);				//QP mainbody

	unsigned char GetLowByte(short sValue);
	unsigned char GetHighByte(short sValue);
	int Big2Gb(unsigned char* pBig5buffer,int iBig5Len);
	int Gb2Big(unsigned char* pBig5buffer,int iBig5Len);
	int InitBigCodeTable(char *pCodeTableName);
	int InitGBCodeTable(char *pCodeTableName);

	//2001-9-10,get type of language
	unsigned char *Str2Lower(char *pCharset);
	int GetLanguageType(int nIndex);
	int DetectLanguage(char *pCharset);

	int m_iEmailType;
	MAIL_HEAD	m_stuMailHead;
	MAIL_TAIL_1	m_stuTail01;
	MAIL_SECTOR m_stuSector;
	short *m_pBIGTable;
	short *m_pGBTable;
protected:
	char * ConvertLow2Upper(char *pSource,char *pDestion);
	int ProcessEmailSectors(unsigned char *pMailBodyBuffer,int iFileLen,int iEmailType,int iBodyStart,FILE *file);
	void WriteTailDetail(unsigned char *pTailBuffer,int iTailBufLen,FILE *file);
	void WriteSectorDetail(unsigned char *pSectorBuffer,int iSectorLen,FILE *file);
	void WriteHeaderDetail(FILE *file);
	int ProcessEmailBody(unsigned char *pMailBodyBuffer,int iFileLen, int iBodyStart,FILE *file,char *pMailName,int iEmailType);
	int GetEmailHeader(unsigned char *pMailBodyBuffer,int iHeadStart,int iBufferLen);
};
#endif

#undef  AFX_DATA
#define AFX_DATA