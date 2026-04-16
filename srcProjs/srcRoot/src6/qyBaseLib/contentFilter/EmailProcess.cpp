
#include	"qyPrecomp.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<windows.h>
#include	<tchar.h>

#include	"EmailProcess.h"
#include	<io.h>
#include	<sys/types.h>
#include	"commonfunc.h"
//#include	<unistd.h>

#include	"charset.h"
#include	"vardefine.h"

extern void cfZeroMemory( void *dst, unsigned long len );


CEmailProcess::CEmailProcess()
{
	InitStruct();
	InitBigCodeTable("D:\\B2Gtable.txt");
	InitGBCodeTable("D:\\G2BTable.txt");
}

// added by asr.
CEmailProcess::CEmailProcess( char *b2gTableFileName, char *g2bTableFileName )
{
	InitStruct( );
	InitBigCodeTable( b2gTableFileName );
	InitGBCodeTable( g2bTableFileName );
}

CEmailProcess::~CEmailProcess()
{
	delete(m_pBIGTable);
	delete(m_pGBTable);
}

//inhere functions for this class
//KMP find arithmetic
int CEmailProcess::KMP_FindString(unsigned char *buf,char *token, int nb, int nt)
{
   int *next;
   int i,in,ib;

   if((next = (int *)malloc(sizeof(int) *nt)) == NULL)
     return -1;

	next[0] = -1;
	for(i = 1;i < nt;i ++)
	{
		in = next[i-1];
		for(;;)
		{
			if(in == -1||token[in] == token[i-1])
			{
				next[i] = in + 1;
				break;
			}
			else
				in = next[in];
		}
	}

	for(i = 1;i < nt;i ++)
	{
		{
			if(next[i] > -1 &&token[next[i]] == token[i])
				next[i] = next[next[i]];
			else
				break;
		}
	}

	in = ib = 0;
	while(in < nt&&ib < nb)
	{
		if(in == -1||buf[ib] == token[in])
			ib ++,in ++;
		else
			in = next[in];
	}

	free(next);
	if(in == nt)
		return (ib - nt);
	else
		return -1;
}

unsigned long CEmailProcess::Base64To(unsigned char *m_pcStart)
{
	static unsigned char m_cShedul[256];
	unsigned int m_iCount=0;

    for(m_iCount='A';m_iCount<='Z';m_iCount++)
		 m_cShedul[m_iCount]=m_iCount-'A';	
	for(m_iCount='a';m_iCount<='z';m_iCount++)	
		 m_cShedul[m_iCount]=('Z'-'A'+1)+m_iCount-'a';	
	for(m_iCount='0';m_iCount<='9';m_iCount++)	
		 m_cShedul[m_iCount]=('Z'-'A'+1)*2+m_iCount-'0';	
		 m_cShedul['+']=62;	
         m_cShedul['/']=63;

	unsigned char m_cOddTemp,m_cEvenTemp;       //two temporarys for exchange

	unsigned long m_iTotalLen=0;       //original length
	unsigned long m_iAscLen=0;
	unsigned long m_iChinaLen=0;

	unsigned char* m_pcNowPos=NULL;                  //locate old array
	unsigned char* m_pcNewPos=NULL;                  //locate new array

	m_pcNowPos=(unsigned char*)m_pcStart;
	m_pcNewPos=m_pcNowPos;
	m_iTotalLen=0;

	while((*m_pcNowPos)!='\0')
	{
		if(*m_pcNowPos==0x0d)//
		{
			m_pcNowPos+=2;
			continue;
		}
		if(*m_pcNowPos==0x0a)
		{
			m_pcNowPos++;
			continue;
		}
		if(*m_pcNowPos!='=')
			*m_pcNewPos=m_cShedul[*m_pcNowPos];
		else
			*m_pcNewPos=*m_pcNowPos;               //
		m_pcNowPos++;
		m_pcNewPos++;
		m_iTotalLen++;
	}
	*m_pcNewPos='\0';
//////////////////////////////////////////////////////////////
	m_pcNewPos=(unsigned char*)m_pcStart;
	m_pcNowPos=(unsigned char*)m_pcStart;
	m_iChinaLen=0;
	m_iAscLen=0;

	if(m_iTotalLen > 4)
	{for(m_iCount=0;m_iCount<(unsigned int)(m_iTotalLen/FOURBYTE-1);m_iCount++)
	{

/////////////////////////creat the one 8bit/////////////////// 
		m_cOddTemp=*m_pcNowPos;
		m_cEvenTemp=*(m_pcNowPos+1);
		m_cOddTemp <<= 2;		//xx xx xx --
		m_cEvenTemp >>= 4;      //xx -- -- --
		m_cEvenTemp &=0x03;
		m_cOddTemp |= m_cEvenTemp;
		(*m_pcNewPos) = m_cOddTemp;	//m_cOddTemp is the result

		if(*m_pcNewPos>=128)
			m_iChinaLen++;
		else m_iAscLen++;

		m_pcNewPos++;

////////////////////creat the second 8bit////////////////////////////////////
		m_cEvenTemp=*(m_pcNowPos+1);
		m_cOddTemp=*(m_pcNowPos+2);
		m_cEvenTemp <<= 4;
		m_cOddTemp >>= 2;
		m_cOddTemp &=0x0f;
		m_cEvenTemp|= m_cOddTemp;
		*m_pcNewPos=m_cEvenTemp;		//m_cEvenTemp is the result

		if(*m_pcNewPos>=128)
			m_iChinaLen++;
		else m_iAscLen++;

		m_pcNewPos++;		
//////////////////////////creat the third 8bit//////////////////////////////
		m_cOddTemp=*(m_pcNowPos+2);
		m_cEvenTemp=*(m_pcNowPos+3);
		m_cOddTemp <<= 6;
		m_cEvenTemp &=0x3f;
		m_cOddTemp |= m_cEvenTemp;
		*m_pcNewPos=m_cOddTemp;			//m_cOddTemp is the result

		if(*m_pcNewPos>=128)
			m_iChinaLen++;
		else m_iAscLen++;

		m_pcNewPos++;

		m_pcNowPos+=FOURBYTE;
	}
	}
/////////////////////////////////////////////////////////////////////////
	m_cOddTemp=*m_pcNowPos;	
	m_cEvenTemp=*(m_pcNowPos+1);	
	m_cOddTemp <<= 2;	
	m_cEvenTemp >>= 4;	
	m_cEvenTemp &=0x03;	
	m_cOddTemp |= m_cEvenTemp;	
	*m_pcNewPos = m_cOddTemp;

	if(*m_pcNewPos>=128)
		m_iChinaLen++;
	else m_iAscLen++;
	m_pcNewPos++;
	
	if(*(m_pcNowPos+2)=='=')
	{
		*m_pcNewPos='\0';
		m_iTotalLen=m_iChinaLen/2+m_iAscLen;

		return(m_iChinaLen+m_iAscLen);
	}
	
	m_cEvenTemp=*(m_pcNowPos+1);	
	m_cOddTemp=*(m_pcNowPos+2);	
	m_cEvenTemp <<= 4;	
	m_cOddTemp >>= 2;	
	m_cOddTemp &= 0x0f;	
	m_cEvenTemp |=m_cOddTemp;	
	*m_pcNewPos = m_cEvenTemp;
	if(*m_pcNewPos>=128)
		m_iChinaLen++;
	else m_iAscLen++;

	m_pcNewPos++;
		
	if(*(m_pcNowPos+3)=='=')
	{
		*m_pcNewPos='\0';
		m_iTotalLen=m_iChinaLen/2+m_iAscLen;

			return(m_iChinaLen+m_iAscLen);
	}

	m_cOddTemp=*(m_pcNowPos+2);	
	m_cEvenTemp=*(m_pcNowPos+3);	
	m_cOddTemp <<= 6;	
	m_cEvenTemp &= 0x3f;	
	m_cOddTemp |= m_cEvenTemp;	
	*m_pcNewPos = m_cOddTemp;
	if(*m_pcNewPos>=128)
		m_iChinaLen++;
	else m_iAscLen++;
	m_pcNewPos++;

    *m_pcNewPos='\0';
    m_iTotalLen=m_iChinaLen/2+m_iAscLen;

	return(m_iChinaLen+m_iAscLen);		
}

int CEmailProcess::Compare4Digit(int digit1, int digit2, int digit3, int digit4, int digit5)
{
	int iRet = digit1;
	if(iRet < digit2)
		iRet = digit2;
	if(iRet < digit3)
		iRet = digit3;
	if(iRet < digit4)
		iRet = digit4;
	if(iRet < digit5)
		iRet = digit5;

	return iRet;
}


int CEmailProcess::GetMailToBuffer(char *pMailName)
{
	int iRet = 0;
	FILE *file;
	unsigned char *pMailHeadBuffer;
	unsigned char *pMailBodyBuffer;
	int iFileLen;
	int fd;
	int iTmpMailType;
	int iFill = 0x0a0d0a0d;
//	int iAbadonFlag = 0;
	file = fopen(pMailName,"rb+");
	printf("\nIn email Process!");
	if(file != NULL)
	{
		fd = fileno(file);	
		lseek(fd,0L,SEEK_END);
		iFileLen = lseek(fd, 0L, SEEK_CUR);
		
		pMailHeadBuffer = new unsigned char[FILE_START_POS+1];
		pMailHeadBuffer[FILE_START_POS] = '\0';
		lseek(fd,0L,SEEK_SET);
		read(fd,pMailHeadBuffer,FILE_START_POS);

		pMailBodyBuffer = new unsigned char[iFileLen-FILE_START_POS+4+1];
		pMailBodyBuffer[iFileLen-FILE_START_POS+4] = '\0';
		lseek(fd,FILE_START_POS,SEEK_SET);
		read(fd,pMailBodyBuffer,iFileLen-FILE_START_POS);			
		memcpy(pMailBodyBuffer+iFileLen-FILE_START_POS,&iFill,4);
      
		//zwj
//	    iAbadonFlag = PreTreat((char *)pMailHeadBuffer,(char *)pMailBodyBuffer,iFileLen - FILE_START_POS);
//		if(iAbadonFlag != 1)
		{
			int iSwitch = 0; 
			memcpy(&iSwitch,pMailHeadBuffer + 55,1);
			switch(iSwitch)
			{
			case 0:		//Http process
				iTmpMailType = 0;
				ProcessHttp(pMailBodyBuffer,iFileLen-FILE_START_POS,file,pMailName,iTmpMailType);
				break;
			case 1:		//Smtp process
				iTmpMailType = 1;
				iRet = ProcessSmtp(pMailBodyBuffer,iFileLen-FILE_START_POS+4,file,pMailName,iTmpMailType);
				break;
			case 2:		//Pop3 process
				iTmpMailType = 2;
				iRet = ProcessSmtp(pMailBodyBuffer,iFileLen-FILE_START_POS+4,file,pMailName,iTmpMailType);
				break;
			case 3:		//Ftp process
				break;
			}
		}
		
		////////////////////////////////////
		fclose(file);
		delete(pMailHeadBuffer);
		delete(pMailBodyBuffer);		

//		if(iRet == -1 || iAbadonFlag == 1)
		if(iRet == -1 )
		{
			remove(pMailName);
			printf("\nThis email is illeagal,Delete it!");
		}
	}
	else
		printf("\nOpen Mail %s Failed!\n\n",pMailName);

  return iRet;
}

int CEmailProcess::ProcessHttp(unsigned char *pMailBodyBuffer,int iFileLen,FILE *file,char *pMailName,int iEmailType)
{
	char *pTypeToken[] = 
	{
		"<HTML>",
		"</HTML>"
	};
	static int iTypeToken[2];
	char *strHttpHeadToken = "charset=";

	int iHttpHeadTokenPos;
	int iCharsetLen = 0;
	int i = 0;

	for(i = 0;i < 2;i ++)
	{
		iTypeToken[i] = KMP_FindString(pMailBodyBuffer,
				pTypeToken[i],iFileLen,
				strlen(pTypeToken[i]));	
	}
	if(iTypeToken[0] != -1 && iTypeToken[1] != -1)
	{
		iHttpHeadTokenPos = KMP_FindString(pMailBodyBuffer,
				strHttpHeadToken,iFileLen,
				strlen(strHttpHeadToken));	
				
		char pCueMessage[256];
		int  iLanguageType = 0;
		
		if(iHttpHeadTokenPos != -1)
		{
			printf("\nReady to processe encode of HTTP:%s!",pMailName);	
			while(*(pMailBodyBuffer + iHttpHeadTokenPos+iCharsetLen) !=  0x22)
				iCharsetLen ++;

			strcpy(pCueMessage,"\nThis Html is ");
			switch(*(pMailBodyBuffer + iHttpHeadTokenPos + 8))
			{
			case 'g':
				strcat(pCueMessage,"GB encode");
				break;
			case 'G':
				strcat(pCueMessage,"GB encode");
				break;
			case 'b':
				strcat(pCueMessage,"Big5 encode");
				Big2Gb(pMailBodyBuffer,iFileLen);
				printf("\nBig5 encode has decoded!");
				break;
			case 'B':
				strcat(pCueMessage,"Big5 encode");
				Big2Gb(pMailBodyBuffer,iFileLen);
				printf("\nBig5 encode has decoded!");
				break;
			default:
				break;
			}

			char *buf = new char[iCharsetLen + 1];
			buf[iCharsetLen] = '\0';
			memcpy(buf,pMailBodyBuffer + iHttpHeadTokenPos,iCharsetLen);

			iLanguageType = DetectLanguage(buf);
			delete(buf);

			if(iLanguageType > 10 && iLanguageType < 20)
				iLanguageType = 2;
			if(iLanguageType > 20 && iLanguageType < 30)
				iLanguageType = 3;
			if(iLanguageType > 30 && iLanguageType < 40)
				iLanguageType = 4;
			if(iLanguageType == 41)
				iLanguageType = 1;
			fseek(file,68,SEEK_SET);
			fwrite(&iLanguageType,1,1,file);
		}	

		fseek(file,0L,SEEK_END);
		m_stuMailHead.wTail01StartPos = ftell(file);
		m_stuMailHead.wTail01TotalCount = iFileLen;
		fwrite(pMailBodyBuffer,sizeof(unsigned char),iFileLen,file);

		fseek(file,163,SEEK_SET);
		fwrite(&m_stuMailHead.wTail01TotalCount,1,4,file);
		fwrite(&m_stuMailHead.wTail01StartPos,1,4,file);

		printf("\nProcesse HTTP :%s! over",pMailName);	
	}
	return 0;
}

int CEmailProcess::ProcessSmtp(unsigned char *pMailBodyBuffer,int iFileLen,FILE *file,char *pMailName,int iEmailType)
{
	int iHeadStart	   = 0;	//Pos of Email header 
	int iBodyStart	   = 0; //define pos of email body
	int iEvelopeindex  = 0;

	char *strPOP3Token = "Received:";
	int  iPOP3Token = 0;

	char *strEvelopeToken[] = 
	{	
		"HELO",		//0:start pos
    	"MAIL",		//1:reverse path
        "RCPT",		//2:forward path
        "DATA"		//3:data
	};
	int iEvelopePos[4],iEvelopeLen[4];

	//define information of Evelope	
	for(iEvelopeindex = 0;iEvelopeindex < 4;iEvelopeindex ++)
	{
		iEvelopePos[iEvelopeindex] = 0;
		iEvelopeLen[iEvelopeindex] = 0;
	}
	
	//Stage 1:Process email head
	//First detect the type of email(SMTP or POP3),
	//
	switch(iEmailType)
	{
	case 1:
		printf("\nReady to processe evelope of SMTP email:%s!",pMailName);	
		for(iEvelopeindex = 1;iEvelopeindex < 4;iEvelopeindex ++)	
		{
			iEvelopePos[iEvelopeindex] = KMP_FindString(pMailBodyBuffer+iEvelopePos[iEvelopeindex-1],
				strEvelopeToken[iEvelopeindex],SEARCH_LENGTH,
				strlen(strEvelopeToken[iEvelopeindex]));	
			
			if(iEvelopePos[iEvelopeindex] != -1)		
				iEvelopePos[iEvelopeindex] += iEvelopePos[iEvelopeindex-1];			
		}

		printf("\n %s:%X---%s:%X---%s:%X",strEvelopeToken[0],iEvelopePos[0],
		                                      strEvelopeToken[1],iEvelopePos[1],
				                              strEvelopeToken[2],iEvelopePos[2]);

		if(iEvelopePos[3] != -1)
		{
			iEvelopeLen[1] = iEvelopePos[2] - iEvelopePos[1];
			iEvelopeLen[2] = iEvelopePos[3] - iEvelopePos[2];

			//To get exact mail from position
			int j = 0;
			static int iTmpStartPos[3],iTmpEndPos[3];
			for(int i = 1;i < 3;i ++)
			{
				for(j = 0;j < iEvelopeLen[i];j ++)
				{
					if(*(pMailBodyBuffer+iEvelopePos[i] + j) == '<')
						iTmpStartPos[i] = iEvelopePos[i] + j +1;										
					
					if(*(pMailBodyBuffer+iEvelopePos[i] + j) == '>')
							iTmpEndPos[i] = iEvelopePos[i] + j - 1; 	
				}
			}

			//
			m_stuMailHead.wMailFromPos = iTmpStartPos[1];
			m_stuMailHead.wMailFromLen = iTmpEndPos[1] - iTmpStartPos[1]+1;
			m_stuMailHead.wRcptToPos   = iTmpStartPos[2];
			m_stuMailHead.wRcptToLen   = iTmpEndPos[2] - iTmpStartPos[2]+1;

			iHeadStart = iEvelopePos[2] + iEvelopeLen[2];

			if(iHeadStart < 0)
				iHeadStart = 0;		

			if(*(pMailBodyBuffer+iEvelopePos[2]-2) == 0x0d)
				m_iEmailType = EMAIL_TYPE_GENERAL_W;	//windows|0d 0a	
			else
			{
				if(*(pMailBodyBuffer+iEvelopePos[2]-1) == 0x0a)
					m_iEmailType = EMAIL_TYPE_GENERAL_U;	//unix	 |0a	
				else
					m_iEmailType = EMAIL_TYPE_DELETE;
			}
			iBodyStart = GetEmailHeader(pMailBodyBuffer,iHeadStart,iFileLen-FILE_START_POS-iHeadStart);
		}
		else
			m_iEmailType = EMAIL_TYPE_DELETE;
		break;
	case 2:
		printf("\nReady to processe evelope of POP3 email:%s!",pMailName);	
		iPOP3Token = KMP_FindString(pMailBodyBuffer,strPOP3Token,SEARCH_LENGTH,strlen(strPOP3Token));
		if(iPOP3Token == -1)
		{
			m_iEmailType = EMAIL_TYPE_PASSWD;
			iBodyStart = 0;
		}
		else
		{
			iHeadStart = iPOP3Token;

			if(*(pMailBodyBuffer+iPOP3Token-2) == 0x0d)
				m_iEmailType = EMAIL_TYPE_GENERAL_W;	//windows|0d 0a	
			else
			{
				if(*(pMailBodyBuffer+iPOP3Token-1) == 0x0a)
					m_iEmailType = EMAIL_TYPE_GENERAL_U;	//unix	 |0a	
				else
					m_iEmailType = EMAIL_TYPE_DELETE;
			}

			iBodyStart = GetEmailHeader(pMailBodyBuffer,iHeadStart,iFileLen-FILE_START_POS-iHeadStart);
		}
		break;
	}
	printf("\n Email:%s Header has been processed!",pMailName);	

	//Stage 2:Process email body
	//locate every item of content-type and others
	switch(m_iEmailType)
	{
	case EMAIL_TYPE_PASSWD:
		ProcessEmailBody(pMailBodyBuffer,iFileLen+4,0,file,pMailName,EMAIL_TYPE_PASSWD);
		break;
	case EMAIL_TYPE_GENERAL_W:
		ProcessEmailBody(pMailBodyBuffer,iFileLen,iBodyStart,file,pMailName,EMAIL_TYPE_GENERAL_W);
		break;
	case EMAIL_TYPE_GENERAL_U:
		ProcessEmailBody(pMailBodyBuffer,iFileLen,iBodyStart,file,pMailName,EMAIL_TYPE_GENERAL_U);
		break;
	case EMAIL_TYPE_DELETE:
		return -1;
		break;
	}
		
	return 0;
}

void CEmailProcess::InitStruct()
{
	cfZeroMemory(&m_stuTail01,sizeof(m_stuTail01));
	cfZeroMemory(&m_stuSector,sizeof(m_stuSector));
	cfZeroMemory(&m_stuMailHead,0xBD);
}

unsigned char CEmailProcess::decode_hex(unsigned char *streamptr)
{
   unsigned char result = 0;
   unsigned char blivit;

   blivit = *streamptr++;
   if ( blivit >= 'a' ) blivit -= ' ';
   if ( blivit > '9' ) blivit -= 0x07;

   result = blivit & 0x0F;
   result <<= 4;

   blivit = *streamptr++;
   if ( blivit >= 'a' ) blivit -= ' ';
   if ( blivit > '9' ) blivit -= 0x07;

   result |= blivit & 0x0F;

   return result;
}

int  CEmailProcess::DecodeQP(unsigned char *pQPBuf,int iLen)
{
	int iState = 0;
	int index = 0;
	int iBufLen = 0;
	int j = 0;
	unsigned char buf[3];
	unsigned char *pNewBuf = new unsigned char[iLen+1];
	pNewBuf[iLen] = '\0';

	while(*(pQPBuf+j) != '\0')
	{
		switch(iState)
		{
		case 0:
			if ( *(pQPBuf+j) == '=' ) 
				iState = 1;
			else
			{
				if(*(pQPBuf+j) != 0x0a)
				{
					memcpy(pNewBuf+iBufLen, pQPBuf+j,1);					
					iBufLen ++;
				}
			}
			break;
		case 1:
			if ( *(pQPBuf+j) == 0x0d )
					iState = 0;
			else 
			{
				if ( ( (*(pQPBuf+j) < '0') || (*(pQPBuf+j) > '9') ) &&
					( (*(pQPBuf+j) < 'A') || (*(pQPBuf+j) > 'F') ) &&
					( (*(pQPBuf+j) < 'a') || (*(pQPBuf+j) > 'f') ) )
				{
					unsigned char cFill = '=';
					memcpy(pNewBuf+iBufLen,&cFill  ,1);
					if ( index != 0 ) 
						memcpy(pNewBuf,&buf[0],1);
					memcpy(pNewBuf,pQPBuf+j,1);
					iBufLen ++;
					iState = 0;
				}
				else 
				{
					if ( index < 1 )
						buf[index++] = *(pQPBuf+j);						
					else
					{
						buf[index++] = *(pQPBuf+j);
						*(pQPBuf+j) = decode_hex( buf );
						memcpy(pNewBuf+iBufLen,pQPBuf+j,1);
						iBufLen ++;
						index = 0;
						iState = 0;
					}
				}
			}
			break;
		}
		j ++;		
	}

	cfZeroMemory(pQPBuf,iLen-iBufLen);
	memcpy(pQPBuf,pNewBuf,iBufLen);

	delete(pNewBuf);

	return iBufLen;
}

unsigned char CEmailProcess::GetHighByte(short sValue)
{
	return ((unsigned char) (((short) (sValue) >> 8) & 0xFF)) ;
}

unsigned char CEmailProcess::GetLowByte(short sValue)
{
	return ((unsigned char) (sValue)) ;
}

int CEmailProcess::Big2Gb(unsigned char *pBig5buffer, int iBig5Len)
{	
	unsigned char* DestSTR=new unsigned char[iBig5Len+1];
	int i=0;
	do
	{
		// is English 是英文字符
		if(pBig5buffer[i]<0xA1||(pBig5buffer[i+1]<0x40)) 
		{
			DestSTR[i]=pBig5buffer[i];
			i++;
		}
		else //是BIG5的汉字码
		{
			DestSTR[i+1]=GetHighByte(m_pBIGTable[(pBig5buffer[i]-0xA1)*0xBF+pBig5buffer[i+1]-0x40]);
			DestSTR[i]  =GetLowByte(m_pBIGTable[(pBig5buffer[i]-0xA1)*0xBF+pBig5buffer[i+1]-0x40]);
			i+=2;
		}
	}while(i<iBig5Len);			

	memcpy(pBig5buffer,DestSTR,iBig5Len);
	
	delete(DestSTR);	

	return iBig5Len;
}

int CEmailProcess::Gb2Big(unsigned char* pGBbuffer,int iGBLen)
{
	unsigned char* DestSTR=new unsigned char[iGBLen+1];
	int i=0;
	
	do
	{
		// is English 是英文字符
		if(pGBbuffer[i]<0xA1||(pGBbuffer[i+1]<0xA1)) 
		{
			DestSTR[i]=pGBbuffer[i];
			i++;
		}
		else
		{
			if(pGBbuffer[i]>0xA1&&pGBbuffer[i]<0xB0) //是GB2312的汉字码
			{
				DestSTR[i+1]=GetHighByte(m_pGBTable[(pGBbuffer[i]-0xA1)*0x5E + pGBbuffer[i+1]-0xA1]);
				DestSTR[i]=GetLowByte(m_pGBTable[(pGBbuffer[i]-0xA1)*0x5E + pGBbuffer[i+1]-0xA1]);
				i+=2;
			}
			else
			{
				DestSTR[i+1]=GetHighByte(m_pGBTable[(pGBbuffer[i]-0xA7)*0x5E + pGBbuffer[i+1]-0xA1]);
				DestSTR[i]=GetLowByte(m_pGBTable[(pGBbuffer[i]-0xA7)*0x5E + pGBbuffer[i+1]-0xA1]);
				i+=2;
			}
		}
	}while(i<iGBLen);

	memcpy(pGBbuffer,DestSTR,iGBLen);
	
	delete(DestSTR);	
	return iGBLen;
}

int CEmailProcess::InitBigCodeTable(char *pCodeTableName)
{	
	FILE *file;
	file = fopen(pCodeTableName,"rb+");

	int fd = fileno(file);

	lseek(fd,0L,SEEK_END);
	int iFileLen = lseek(fd, 0L, SEEK_CUR);

	m_pBIGTable = new short[iFileLen];	
	fseek(file,0L,SEEK_SET);
	fread(m_pBIGTable,1,iFileLen,file);
	fclose(file);

	return 0;
}

int CEmailProcess::InitGBCodeTable(char *pCodeTableName)
{	
	FILE *file;
	file = fopen(pCodeTableName,"rb+");
	int fd = fileno(file);	
	lseek(fd,0L,SEEK_END);
	int iFileLen = lseek(fd, 0L, SEEK_CUR);

	m_pGBTable = new short[iFileLen];	
	fseek(file,0L,SEEK_SET);
	fread(m_pGBTable,1,iFileLen,file);
	fclose(file);

	return 0;
}

int CEmailProcess::GetEmailHeader(unsigned char *pMailBodyBuffer,int iHeadStart,int iBufferLen)
{
	int iHeaderIndex = 0;
	int iHeaderSecterIndex = 0;
	int i = 0;
	//define information of header
	char *strHeadersToken[] = 
	{
		"\nFrom:",
		"\nTo:",
		"\nSubject:",
		"\nDate:",
		"\nMIME-Version:",
	};

	char *strHeadersTokenUpper[] = 
	{
		"\nFROM:",
		"\nTO:",
		"\nSUBJECT",
		"\nDATE:",
		"\nMIME-VERSION:",
	};
	int iHeadersPos[5],iHeadersLen[5];

	for(iHeaderIndex = 0;iHeaderIndex < 5;iHeaderIndex ++)
	{
		iHeadersPos[iHeaderIndex] = 0;
		iHeadersLen[iHeaderIndex] = 0;
	}
	
	//2.1 get the pos of every header element
	for(iHeaderIndex = 0;iHeaderIndex < 5;iHeaderIndex ++)
	{
		iHeadersPos[iHeaderIndex]  = KMP_FindString(pMailBodyBuffer+iHeadStart,strHeadersToken[iHeaderIndex],
											iBufferLen,
											strlen(strHeadersToken[iHeaderIndex]));
		if(iHeadersPos[iHeaderIndex] != -1)
			iHeadersPos[iHeaderIndex] += iHeadStart+strlen(strHeadersToken[iHeaderIndex]);
		else
		{
			iHeadersPos[iHeaderIndex]  = KMP_FindString(pMailBodyBuffer+iHeadStart,strHeadersTokenUpper[iHeaderIndex],
											iBufferLen,
											strlen(strHeadersTokenUpper[iHeaderIndex]))+iHeadStart+strlen(strHeadersToken[iHeaderIndex]);
		}
	}

	//2.2 get the length of every header element 
	for(iHeaderIndex = 0;iHeaderIndex < 5;iHeaderIndex ++)
	{
		while(!(*(pMailBodyBuffer+iHeadersPos[iHeaderIndex]+iHeaderSecterIndex+1) == 0x0a &&  *(pMailBodyBuffer+iHeadersPos[iHeaderIndex]+iHeaderSecterIndex+2) != 0x09 ) ||
			  !(*(pMailBodyBuffer+iHeadersPos[iHeaderIndex]+iHeaderSecterIndex+1) == 0x0a &&  *(pMailBodyBuffer+iHeadersPos[iHeaderIndex]+iHeaderSecterIndex+2) != 0x20 )   )
			  iHeaderSecterIndex ++;	
		iHeadersLen[iHeaderIndex] = iHeaderSecterIndex;
		iHeaderSecterIndex = 0;
	}


	m_stuMailHead.wFromPos		= iHeadersPos[0];
	m_stuMailHead.wFromLen		= iHeadersLen[0];

	int j = 0;
	int k = 0;
	int iEmailMiddle = 0;
	int iEmailStartPos = 0;
	int iEmailEndPos = 0;
	int iMiddle = 0;
	for(j = 0;j < m_stuMailHead.wFromLen;j ++)
	{
		if(*(pMailBodyBuffer + m_stuMailHead.wFromPos + j) == '@' )
		{
			iEmailMiddle = j;
			for(k = iEmailMiddle;k >= 0;k --)
			{
				if(*(pMailBodyBuffer + m_stuMailHead.wFromPos + k) == '<' ||
				   *(pMailBodyBuffer + m_stuMailHead.wFromPos + k) == 0x20 )
				{
					iEmailStartPos = m_stuMailHead.wFromPos + k+1;
					break;
				}
			}			
			iMiddle = iEmailStartPos;
			break;
		}
	}				

	for(j = iHeadersLen[i]-1;j >= 0;j --)
	{
		if( (*(pMailBodyBuffer + iHeadersPos[i] + j) >= 'A' && *(pMailBodyBuffer + iHeadersPos[i] + j) <= 'Z') ||
			(*(pMailBodyBuffer + iHeadersPos[i] + j) >= 'a' && *(pMailBodyBuffer + iHeadersPos[i] + j) <= 'z') )				
		{
			iEmailEndPos = iHeadersPos[0] + j;
			break;			
		}
	}		
	m_stuMailHead.wFromPos      = iMiddle;
	m_stuMailHead.wFromLen		= iEmailEndPos - iMiddle + 1;
	m_stuMailHead.wToPos		= iHeadersPos[1];
	m_stuMailHead.wToLen		= iHeadersLen[1];
	m_stuMailHead.wSubjectPos	= iHeadersPos[2];
	m_stuMailHead.wSubjectLen	= iHeadersLen[2];

	//Operation over
	
	int iHeadersMax = iHeadersPos[0];
	int iHeadersMaxIndex = 0;
	for(i = 1;i < 5;i ++)
	{
		if(iHeadersMax < iHeadersPos[i])
		{
			iHeadersMax = iHeadersPos[i];
			iHeadersMaxIndex = i;
		}
	}
	//Get start position of mail body
	int iBodyStart = iHeadersMax + iHeadersLen[iHeadersMaxIndex] - 1;

	return iBodyStart;
}

int CEmailProcess::ProcessEmailBody(unsigned char *pMailBodyBuffer, int iFileLen, int iBodyStart,FILE *file, char *pMailName,int iEmailType)
{
	unsigned char *pBlockBuffer;
	if(iEmailType == EMAIL_TYPE_PASSWD)	//if this mail contain password and username
	{
		WriteSectorDetail(pMailBodyBuffer,iFileLen,file);
		
		m_stuMailHead.wTail01TotalCount = 1;	
		fseek(file,0L,SEEK_END);
		m_stuMailHead.wTail01StartPos = ftell(file);

		pBlockBuffer = new unsigned char[60+1];
		pBlockBuffer[60] = '\0';
		cfZeroMemory(pBlockBuffer,60);

		m_stuTail01.wStructSize		= 60;
		m_stuTail01.byBlockType		= 1;		
		m_stuTail01.dwTextOffset	=  0;
		m_stuTail01.dwBlockOffset	= 0;
		m_stuTail01.dwBlockSize		= iFileLen;		
		m_stuTail01.dwDecodedSize	= iFileLen;			

		memcpy(pBlockBuffer,&m_stuTail01.wStructSize,2);
		memcpy(pBlockBuffer+2,&m_stuTail01.byBlockType,2);
		memcpy(pBlockBuffer+28,&m_stuTail01.dwTextOffset,4);
		memcpy(pBlockBuffer+32,&m_stuTail01.dwBlockOffset,4);
		memcpy(pBlockBuffer+36,&m_stuTail01.dwBlockSize,4);
		memcpy(pBlockBuffer+40,&m_stuTail01.dwDecodedPos,4);
		memcpy(pBlockBuffer+44,&m_stuTail01.dwDecodedSize,4);
		
		WriteTailDetail(pBlockBuffer,60,file);
		WriteHeaderDetail(file);
		delete(pBlockBuffer);
	}
	else		//if this mail contain attachments and context
	{
		ProcessEmailSectors(pMailBodyBuffer,iFileLen,iEmailType,iBodyStart,file);
		WriteHeaderDetail(file);
	}
	
	return 0;
}

void CEmailProcess::WriteHeaderDetail(FILE *file)
{
	printf("\nReady to write fille head struct!");

	fseek(file,142,SEEK_SET);
	fwrite(&m_stuMailHead.wMailFromPos,1,2,file);	
	fwrite(&m_stuMailHead.wMailFromLen,1,2,file);	
	fwrite(&m_stuMailHead.wRcptToPos,1,2,file);	
	fwrite(&m_stuMailHead.wRcptToLen,1,2,file);	
	fwrite(&m_stuMailHead.wFromPos,1,2,file);	
	fwrite(&m_stuMailHead.wFromLen,1,2,file);	
	fwrite(&m_stuMailHead.wToPos,1,2,file);	
	fwrite(&m_stuMailHead.wToLen,1,2,file);	
	fwrite(&m_stuMailHead.wSubjectPos,1,2,file);	
	fwrite(&m_stuMailHead.wSubjectLen,1,2,file);	
	fseek(file,163,SEEK_SET);
	fwrite(&m_stuMailHead.wTail01TotalCount,1,4,file);
	fwrite(&m_stuMailHead.wTail01StartPos,1,4,file);

	printf("\nEmail head has been written!");
}

void CEmailProcess::WriteSectorDetail(unsigned char *pSectorBuffer, int iSectorLen,FILE *file)
{
	fseek(file,0L,SEEK_END);		
	m_stuTail01.dwDecodedPos	= ftell(file);		  
	fwrite(pSectorBuffer,sizeof(unsigned char),iSectorLen,file);
}

void CEmailProcess::WriteTailDetail(unsigned char *pTailBuffer, int iTailBufLen, FILE *file)
{
	fseek(file,0L,SEEK_END);		
	fwrite(pTailBuffer,sizeof(unsigned char),iTailBufLen,file);
}

int CEmailProcess::ProcessEmailSectors(unsigned char *pMailBodyBuffer, int iFileLen, int iEmailType,int iBodyStart, FILE *file)
{
	int i = 0;
	int iBodyType = 0;
	int iIndexSector = 0;
	int iEncodChar = 0;

	char *strBlockToken[] = 
	{
		"Content-Type:",
		"-Encoding:", 		
		"harset=",		
		"name=",	
		"orient text",	
		"orient block",	
		"decoded block"	,
	};

	for(i = 1;i < TOKEN_ARRAY_LEN;i ++)
	{
		m_stuSector.iPosContentType[i] = KMP_FindString(
			pMailBodyBuffer+iBodyStart+m_stuSector.iPosContentType[i-1]+1,
			strBlockToken[0],
			iFileLen-FILE_START_POS-iBodyStart-m_stuSector.iPosContentType[i-1]-1,
			strlen(strBlockToken[0]));				
			
		
		//1 is to avoid finding the same position
		if(m_stuSector.iPosContentType[i] != -1)			
			m_stuSector.iPosContentType[i] += m_stuSector.iPosContentType[i-1]+1;
		else
		{
			if(i == 1)
			{
				iBodyType = 1;			
				m_stuSector.iSectorCounter = 1;
				m_stuSector.iPosContentType[1] = iBodyStart;												
				m_stuSector.iPosContentType[2] = iFileLen;
			}
			else
			{
				iBodyType = 2;			
				m_stuSector.iSectorCounter = i - 1;
				m_stuSector.iPosContentType[i] = iFileLen;
				for(int k = 1;k < i;k ++)
					m_stuSector.iPosContentType[k] = iBodyStart+m_stuSector.iPosContentType[k];					
			}				
			break;
		}
	}
	
	switch(iBodyType)
	{
	case 1:
		m_stuSector.iSectorCounter = 1;
		printf("\nThere are No Content-Type in mail");		 
		break;
	case 2:
		printf("\nThere are %d Content-Type in mail ",
			m_stuSector.iSectorCounter);		    
		break;
	}

	printf("\n  Ready to process every sector!");		

	//Action 1:Get length of content-type and sector
	for(iIndexSector = 1;iIndexSector <= m_stuSector.iSectorCounter;iIndexSector ++)
	{
		int iBlockIndex = 0;
		int iFlag = 0;
		while(iBlockIndex < m_stuSector.iPosContentType[iIndexSector + 1] - 
			m_stuSector.iPosContentType[iIndexSector])
		{
			if(iEmailType == EMAIL_TYPE_GENERAL_W)
			{						
				if(*(pMailBodyBuffer+m_stuSector.iPosContentType[iIndexSector]+
					iBlockIndex  ) == 0x0d &&
					*(pMailBodyBuffer+m_stuSector.iPosContentType[iIndexSector]+
					iBlockIndex+1) == 0x0a &&
					*(pMailBodyBuffer+m_stuSector.iPosContentType[iIndexSector]+
					iBlockIndex+2) == 0x0d &&
					*(pMailBodyBuffer+m_stuSector.iPosContentType[iIndexSector]+
					iBlockIndex+3) == 0x0a )
				{
					iFlag = 1;
					m_stuSector.iLenSector[iIndexSector] = iBlockIndex;
					break;
				}
			}
			else
			{					
				if(*(pMailBodyBuffer+m_stuSector.iPosContentType[iIndexSector]+
					iBlockIndex)   == 0x0a &&
					*(pMailBodyBuffer+m_stuSector.iPosContentType[iIndexSector]+
					iBlockIndex+1) == 0x0a)
				{
					iFlag = 1;
					m_stuSector.iLenSector[iIndexSector] = iBlockIndex;
					break;
				}
			}
			iBlockIndex ++;
		}			
		
		if(iFlag == 0)
			m_stuSector.iLenSector[iIndexSector] =
			m_stuSector.iPosContentType[iIndexSector + 1] - 
			m_stuSector.iPosContentType[iIndexSector];	

		for(int iIndexContent = 0;iIndexContent < m_stuSector.iLenSector[iIndexSector];iIndexContent ++)
		{
			if(*(pMailBodyBuffer+m_stuSector.iPosContentType[iIndexSector]
				+iIndexContent) == 0x0a ||
				*(pMailBodyBuffer+m_stuSector.iPosContentType[iIndexSector] 
				+iIndexContent) == ';')
			{
				m_stuSector.iLenContentType[iIndexSector] = iIndexContent;
				break;
			}
		}																
		printf("\n  Index:%d---Postion:%X---Sector len:%d---Content len:%d",
			iIndexSector,
			m_stuSector.iPosContentType[iIndexSector],
			m_stuSector.iLenSector[iIndexSector],
			m_stuSector.iLenContentType[iIndexSector]);
	}
	
	//////////Action 1 Over!///////////////////////

	//Action 2:Get position and length of charset,encoding and filename
	static int iEncodCharPos[4],iEncodCharLen[4];
	for(iIndexSector = 1;iIndexSector <= m_stuSector.iSectorCounter;iIndexSector ++)
	{
		for(iEncodChar = 1;iEncodChar < 4;iEncodChar ++)
		{
			iEncodCharPos[iEncodChar] = KMP_FindString(
				pMailBodyBuffer+m_stuSector.iPosContentType[iIndexSector]-BACK_LENGTH,
				strBlockToken[iEncodChar],
				m_stuSector.iLenSector[iIndexSector] + BACK_LENGTH,
				strlen(strBlockToken[iEncodChar]));		
			if(iEncodCharPos[iEncodChar] != -1)
				iEncodCharPos[iEncodChar] += m_stuSector.iPosContentType[iIndexSector]-BACK_LENGTH;
			else
			{
				char *pDestion = new char[strlen(strBlockToken[iEncodChar]) + 1];
				pDestion[strlen(strBlockToken[iEncodChar])] = '\0';
				iEncodCharPos[iEncodChar] = KMP_FindString(
					pMailBodyBuffer+m_stuSector.iPosContentType[iIndexSector]-BACK_LENGTH,
					ConvertLow2Upper(strBlockToken[iEncodChar],pDestion),
					m_stuSector.iLenSector[iIndexSector] + BACK_LENGTH,
					strlen(strBlockToken[iEncodChar]));	

				delete(pDestion);
				if(iEncodCharPos[iEncodChar] != -1)
					iEncodCharPos[iEncodChar] += m_stuSector.iPosContentType[iIndexSector]-BACK_LENGTH;					
			}
			
			int iIndexTmp = 0;
			while(iIndexTmp < m_stuSector.iLenSector[iIndexSector])
			{
				if(*(pMailBodyBuffer+iEncodCharPos[iEncodChar]+iIndexTmp) == 0x0a)
				{
					if(iEmailType == EMAIL_TYPE_GENERAL_W)
						iEncodCharLen[iEncodChar] = iIndexTmp - 1;
					else
						iEncodCharLen[iEncodChar] = iIndexTmp;// - 1;

					break;
				}
				iIndexTmp ++;
			}

			switch(iEncodChar)
			{
			case 1:
				m_stuSector.iPosEncoding[iIndexSector] = iEncodCharPos[iEncodChar];
				m_stuSector.iLenEncoding[iIndexSector] = iEncodCharLen[iEncodChar];
				break;
			case 2:
				m_stuSector.iPosCharset[iIndexSector] = iEncodCharPos[iEncodChar];
				m_stuSector.iLenCharset[iIndexSector] = iEncodCharLen[iEncodChar];
				break;
			case 3:
				m_stuSector.iPosFileName[iIndexSector] = iEncodCharPos[iEncodChar];
				m_stuSector.iLenFileName[iIndexSector] = iEncodCharLen[iEncodChar];
				break;			
			}
		}
	}

	//////////Action 2 Over!///////////////////////
	
	//Action 3:Process every sector(context and attachment)
	int iTmpSectorCount = m_stuSector.iSectorCounter;
	for(iIndexSector = 1;iIndexSector <= iTmpSectorCount ;iIndexSector ++)
	{
		if(m_stuSector.iPosFileName[iIndexSector] == -1 )	//context
		{			
			if(*(pMailBodyBuffer + m_stuSector.iPosContentType[iIndexSector] +14) == 'm' ||
			   *(pMailBodyBuffer + m_stuSector.iPosContentType[iIndexSector] +14) == 'M')
			{
				m_stuSector.iSectorType[iIndexSector] = 2;	//if content-type = multipart/mixed;
				m_stuSector.iSectorCounter --;
			}
			else
			{
				m_stuSector.iSectorType[iIndexSector] = 0;
				char pCueMessage[256];
				strcpy(pCueMessage,"context ");
				m_stuSector.iPosOriBlock[iIndexSector] = 
							m_stuSector.iPosContentType[iIndexSector] + 
							m_stuSector.iLenSector[iIndexSector];
				m_stuSector.iLenOriBlock[iIndexSector] = 
							m_stuSector.iPosContentType[iIndexSector + 1] - 
							m_stuSector.iPosOriBlock[iIndexSector];
		
				//fill struct and write to mail
				unsigned char *buf = new unsigned char[m_stuSector.iLenOriBlock[iIndexSector] + 1];
				buf[m_stuSector.iLenOriBlock[iIndexSector]] = '\0';
				int iOffset = iFileLen - m_stuSector.iPosOriBlock[iIndexSector] -									 
					m_stuSector.iLenOriBlock[iIndexSector];
				
				if(iOffset >=0)						
					memcpy(buf,pMailBodyBuffer +m_stuSector.iPosOriBlock[iIndexSector],
					m_stuSector.iLenOriBlock[iIndexSector]);
				else
					memcpy(buf,pMailBodyBuffer +m_stuSector.iPosOriBlock[iIndexSector],
											m_stuSector.iLenOriBlock[iIndexSector]+iOffset);

				if(*(pMailBodyBuffer + m_stuSector.iPosEncoding[iIndexSector] +11) == 'q' ||
					*(pMailBodyBuffer + m_stuSector.iPosEncoding[iIndexSector] +11) == 'Q')
				{
					//				printf("\n  To decode QP block!");
					m_stuSector.iLenDecBlock[iIndexSector] = DecodeQP(buf,m_stuSector.iLenOriBlock[iIndexSector]);
					strcat(pCueMessage,"QP Encode---");
					//				printf("\n  QP block decoded!");									
				}
				else
				{
					if(*(pMailBodyBuffer + m_stuSector.iPosEncoding[iIndexSector] +11) == 'b' ||
						*(pMailBodyBuffer + m_stuSector.iPosEncoding[iIndexSector] +11) == 'B')
					{
						m_stuSector.iLenDecBlock[iIndexSector] = Base64To(buf);		 
						strcat(pCueMessage,"Base64 Encode---");
					}
					else
					{
						m_stuSector.iLenDecBlock[iIndexSector] = m_stuSector.iLenOriBlock[iIndexSector];
						strcat(pCueMessage,"No Encode---");
					}
				}

				if(*(pMailBodyBuffer + m_stuSector.iPosCharset[iIndexSector] +8) == 'b' ||
					*(pMailBodyBuffer + m_stuSector.iPosCharset[iIndexSector] +8) == 'B')
				{
					Big2Gb(buf,m_stuSector.iLenDecBlock[iIndexSector]);				
					strcat(pCueMessage,"Big5 Charset");
				}
				else			
					strcat(pCueMessage,"GB Charset");

				if(m_stuSector.iPosCharset[iIndexSector] != -1)
				{
					char *nbuf = new char[m_stuSector.iLenCharset[iIndexSector] + 1];
					nbuf[m_stuSector.iLenCharset[iIndexSector]] = '\0';
					memcpy(nbuf,pMailBodyBuffer + m_stuSector.iPosCharset[iIndexSector],
												 m_stuSector.iLenCharset[iIndexSector]);
	
					m_stuSector.iLanguageType[iIndexSector] = DetectLanguage(nbuf);
					delete(nbuf);

					if(m_stuSector.iLanguageType[iIndexSector] > 10 && m_stuSector.iLanguageType[iIndexSector] < 20)
						m_stuSector.iLanguageType[iIndexSector] = 2;
					if(m_stuSector.iLanguageType[iIndexSector] > 20 && m_stuSector.iLanguageType[iIndexSector] < 30)
						m_stuSector.iLanguageType[iIndexSector] = 3;
					if(m_stuSector.iLanguageType[iIndexSector] > 30 && m_stuSector.iLanguageType[iIndexSector] < 40)
						m_stuSector.iLanguageType[iIndexSector] = 4;
					if(m_stuSector.iLanguageType[iIndexSector] == 41)
						m_stuSector.iLanguageType[iIndexSector] = 1;
				}
				else
					m_stuSector.iLanguageType[iIndexSector] = 0;										

				printf("\nThis sector is %s",pCueMessage);
				fseek(file,0L,SEEK_END);
				m_stuSector.iPosDecBlock[iIndexSector] = ftell(file);
				fwrite(buf,sizeof(unsigned char),m_stuSector.iLenDecBlock[iIndexSector],file);
				delete(buf);			
			}
		}
		else		//attachment
		{
			m_stuSector.iSectorType[iIndexSector] = 1;
			if(*(pMailBodyBuffer + m_stuSector.iPosEncoding[iIndexSector] +11) == 'b' ||
				*(pMailBodyBuffer + m_stuSector.iPosEncoding[iIndexSector] +11) == 'B')
			{
				char pCueMessage[256];

				//To get original and decoded position of base64 block
				if(iEmailType == EMAIL_TYPE_GENERAL_W)
					m_stuSector.iPosOriBlock[iIndexSector] = 
									m_stuSector.iPosContentType[iIndexSector] + 
									m_stuSector.iLenSector[iIndexSector] + 4;
				else
					m_stuSector.iPosOriBlock[iIndexSector] = 
									m_stuSector.iPosContentType[iIndexSector] + 
									m_stuSector.iLenSector[iIndexSector] + 2;

				int iIndexBase64 = 0;
				int iBlockSpaceFlag = -1;
				while(iIndexBase64 < m_stuSector.iPosContentType[iIndexSector + 1] - 
						   m_stuSector.iPosOriBlock[iIndexSector])
				{
					if(iEmailType == EMAIL_TYPE_GENERAL_W)
					{
						if(*(pMailBodyBuffer+m_stuSector.iPosOriBlock[iIndexSector]+iIndexBase64)
							== 0x0d &&
							*(pMailBodyBuffer+m_stuSector.iPosOriBlock[iIndexSector]+iIndexBase64+1)
							== 0x0a &&
							*(pMailBodyBuffer+m_stuSector.iPosOriBlock[iIndexSector]+iIndexBase64+2)
							== 0x0d &&
							*(pMailBodyBuffer+m_stuSector.iPosOriBlock[iIndexSector]+iIndexBase64+3)
							== 0x0a )
						{
							iBlockSpaceFlag = 1;
							m_stuSector.iLenOriBlock[iIndexSector] = iIndexBase64;
							break;
						}
					}
					else
					{
						if(*(pMailBodyBuffer+m_stuSector.iPosOriBlock[iIndexSector]+iIndexBase64)
							== 0x0a &&
							*(pMailBodyBuffer+m_stuSector.iPosOriBlock[iIndexSector]+iIndexBase64+1)
							== 0x0a)
						{				
							iBlockSpaceFlag = 1;
							m_stuSector.iLenOriBlock[iIndexSector] = iIndexBase64;
							break;
						}					
					}
					iIndexBase64 ++;
				}

				if(iBlockSpaceFlag == -1)
					m_stuSector.iLenOriBlock[iIndexSector] = m_stuSector.iPosContentType[iIndexSector + 1] - 
																	m_stuSector.iPosOriBlock[iIndexSector];

				unsigned char *buf = new unsigned char[m_stuSector.iLenOriBlock[iIndexSector] + 1];
				buf[m_stuSector.iLenOriBlock[iIndexSector]] = '\0';
				int iOffset = iFileLen - m_stuSector.iPosOriBlock[iIndexSector] -
									 m_stuSector.iLenOriBlock[iIndexSector];
				if(iOffset >0)						
					memcpy(buf,pMailBodyBuffer +m_stuSector.iPosOriBlock[iIndexSector],
											m_stuSector.iLenOriBlock[iIndexSector]);
				else
					memcpy(buf,pMailBodyBuffer +m_stuSector.iPosOriBlock[iIndexSector],
											m_stuSector.iLenOriBlock[iIndexSector]+iOffset);

				//decode base64
				m_stuSector.iLenDecBlock[iIndexSector] = Base64To(buf);		 
				strcpy(pCueMessage,"Attachment---Base64 Encode");

				printf("\nThis sector is %s",pCueMessage);
				fseek(file,0L,SEEK_END);
				m_stuSector.iPosDecBlock[iIndexSector] = ftell(file);
				fwrite(buf,sizeof(unsigned char),m_stuSector.iLenDecBlock[iIndexSector],file);
				delete(buf);			
			}
			else
			{
				if(*(pMailBodyBuffer + m_stuSector.iPosEncoding[iIndexSector] +11) == 'q' ||
					*(pMailBodyBuffer + m_stuSector.iPosEncoding[iIndexSector] +11) == 'Q')
				{
					char pCueMessage[256];
					m_stuSector.iPosOriBlock[iIndexSector] = 
									m_stuSector.iPosContentType[iIndexSector] + 
                                    m_stuSector.iLenSector[iIndexSector];
					m_stuSector.iLenOriBlock[iIndexSector] = 
									m_stuSector.iPosContentType[iIndexSector + 1] - 
									m_stuSector.iPosOriBlock[iIndexSector];
					
					//fill struct and write to mail
					unsigned char *buf = new unsigned char[m_stuSector.iLenOriBlock[iIndexSector] + 1];
					buf[m_stuSector.iLenOriBlock[iIndexSector]] = '\0';
					int iOffset = iFileLen - m_stuSector.iPosOriBlock[iIndexSector] -
									 m_stuSector.iLenOriBlock[iIndexSector];									 

					if(iOffset >0)						
						memcpy(buf,pMailBodyBuffer +m_stuSector.iPosOriBlock[iIndexSector],
											m_stuSector.iLenOriBlock[iIndexSector]);
					else
						memcpy(buf,pMailBodyBuffer +m_stuSector.iPosOriBlock[iIndexSector],
											m_stuSector.iLenOriBlock[iIndexSector]+iOffset);

					m_stuSector.iLenDecBlock[iIndexSector] = DecodeQP(buf,m_stuSector.iLenOriBlock[iIndexSector]);
					strcpy(pCueMessage,"Attachment---QP Encode");
					printf("\nThis sector is %s",pCueMessage);
					fseek(file,0L,SEEK_END);
					m_stuSector.iPosDecBlock[iIndexSector] = ftell(file);
					fwrite(buf,sizeof(unsigned char),m_stuSector.iLenDecBlock[iIndexSector],file);
					delete(buf);			
				}
				else
				{
					unsigned char *buf = new unsigned char[m_stuSector.iLenOriBlock[iIndexSector] + 1];
					buf[m_stuSector.iLenOriBlock[iIndexSector]] = '\0';
					int iOffset = iFileLen - m_stuSector.iPosOriBlock[iIndexSector] -
									 m_stuSector.iLenOriBlock[iIndexSector];		

					if(iOffset >0)						
						memcpy(buf,pMailBodyBuffer +m_stuSector.iPosOriBlock[iIndexSector],
											m_stuSector.iLenOriBlock[iIndexSector]);
					else
						memcpy(buf,pMailBodyBuffer +m_stuSector.iPosOriBlock[iIndexSector],
											m_stuSector.iLenOriBlock[iIndexSector]+iOffset);

					m_stuSector.iLenDecBlock[iIndexSector] = m_stuSector.iLenOriBlock[iIndexSector];
					fseek(file,0L,SEEK_END);
					m_stuSector.iPosDecBlock[iIndexSector] = ftell(file);
					fwrite(buf,sizeof(unsigned char),m_stuSector.iLenDecBlock[iIndexSector],file);
					delete(buf);			
				}
			}
		}
	}
	//////////Action 3 Over!///////////////////////

	//Action 4:Fill memory of every sector
	fseek(file,0L,SEEK_END);			
	m_stuMailHead.wTail01StartPos = ftell(file);		
	m_stuMailHead.wTail01TotalCount = m_stuSector.iSectorCounter;
	
	unsigned char *pTailBlockBuffer = new unsigned char[m_stuSector.iSectorCounter * 60 + 1];
	pTailBlockBuffer[m_stuSector.iSectorCounter * 60] = '\0';
	int iTmpBlockIndex = 0;
	for(iIndexSector = 1;iIndexSector <= iTmpSectorCount;iIndexSector ++)
	{
		if(m_stuSector.iSectorType[iIndexSector] != 2)
		{
			iTmpBlockIndex ++;
			unsigned char cFillArray[60];
			cfZeroMemory(cFillArray,60); 
			int iTmpStructSize = 60;
			memcpy(cFillArray,&iTmpStructSize,2);
			memcpy(cFillArray+2,&m_stuSector.iSectorType[iIndexSector],2);
			memcpy(cFillArray+4,&m_stuSector.iPosContentType[iIndexSector],4);
			memcpy(cFillArray+8,&m_stuSector.iLenContentType[iIndexSector],4);
			memcpy(cFillArray+12,&m_stuSector.iPosCharset[iIndexSector],4);
			memcpy(cFillArray+16,&m_stuSector.iLenCharset[iIndexSector],4);
			memcpy(cFillArray+20,&m_stuSector.iPosFileName[iIndexSector],4);
			memcpy(cFillArray+24,&m_stuSector.iLenFileName[iIndexSector],4);
			memcpy(cFillArray+28,&m_stuSector.iPosOriBlock[iIndexSector],4);
			memcpy(cFillArray+32,&m_stuSector.iPosOriBlock[iIndexSector],4);
			memcpy(cFillArray+36,&m_stuSector.iLenOriBlock[iIndexSector],4);
			memcpy(cFillArray+40,&m_stuSector.iPosDecBlock[iIndexSector],4);
			memcpy(cFillArray+44,&m_stuSector.iLenDecBlock[iIndexSector],4);
			memcpy(cFillArray+48,&m_stuSector.iLanguageType[iIndexSector],1);
		
			memcpy(pTailBlockBuffer+(iTmpBlockIndex-1)*60,cFillArray,60);									
		}
	}	

	fseek(file,0L,SEEK_END);
	fwrite(pTailBlockBuffer,sizeof(unsigned char),m_stuSector.iSectorCounter*60,file);
	delete(pTailBlockBuffer);

	return 0;
}

char *CEmailProcess::ConvertLow2Upper(char *pSource,char *pDestion)
{
	int i = 0;
		
	while(*(pSource+i) != '\0')
	{
		*(pDestion+i) = *(pSource+i);
		if(*(pSource+i) <= 122 && *(pSource+i) >= 97)
			*(pDestion+i) -= 32;
		i ++;
	}	

	return pDestion;
}

unsigned char *CEmailProcess::Str2Lower(char *pCharset)
{
	int i = 0;
	while(pCharset[i] != '\0')
	{
		if(pCharset[i] >= 'A' && pCharset[i] <= 'Z')
			pCharset[i] = pCharset[i] + 32;
		i ++;
	}

//	printf("\n%s",pCharset);
	return (unsigned char*)pCharset;
}

int CEmailProcess::GetLanguageType(int nIndex)
{
	if(nIndex >= 0 && nIndex <= 2)
	{
		printf("GB code");
		return 11;
	}
	if(nIndex == 4 ||nIndex == 3)
	{
		printf("Big5 code");
		return 12;
	}
	if(nIndex == 5)
	{
		printf("hz-gb-2312  code");
		return 13;
	}
	if(nIndex == 6)
	{
		printf("iso-2022-cn code");
		return 14;
	}
	if(nIndex == 7)
	{
		printf(" iso-2022-cn-ext code");
		return 15;
	}
	if(nIndex == 9 ||nIndex == 8)
	{
		printf("jis code");
		return 21;
	}
	if(nIndex == 11 ||nIndex == 10)
	{
		printf("shift-JIS code");
		return 22;
	}
	if(nIndex == 13 ||nIndex == 12)
	{
		printf("ksc code");
		return 31;
	}
	if(nIndex == 14)
	{
		printf("iso-2022-kr code");
		return 32;
	}
	if(nIndex == 16 ||nIndex == 15)
	{
		printf("iso-8859-1 code");
		return 41;
	}

	printf("other code");
	return 0;
}

int CEmailProcess::DetectLanguage(char *pCharset)
{
	int i = 0;
	unsigned char *buf = new unsigned char[strlen(pCharset) + 1];
	buf[strlen(pCharset)] = '\0';
	Str2Lower(pCharset);
	memcpy(buf,pCharset,strlen(pCharset));
	for(i = 0;i < LANGUAGE_CODE_NUMBER;i ++)
	{		
		if(KMP_FindString(buf,pLanguageToken[i],strlen(pCharset),strlen(pLanguageToken[i])) != -1)
			break;
	}

	delete(buf);
	return GetLanguageType(i);
}
