
#include	"qyPrecomp.h"

#ifndef  __WINCE__
		 #include	<crtdbg.h>
#endif

#define  BOOL	int
#define  TRUE	1
#define  FALSE	0

#if defined(WIN32) || defined(WIN16) || defined(WINDOWS)
#ifndef MSDOS
#define MSDOS
#endif
#endif

#include	<stdio.h>
#include	<stdlib.h>
#ifndef		MSDOS
	//  #include	<unistd.h>
#else
	#include	<io.h>
#endif

#include	<string.h> 
#include	"des.h"
#include	"qyEncCommon.h"
#include	"qyCommon\\qyCommonFunc8.h"
//  #include	"qyLicense.h"

/*
unsigned  char  DEFAULT_cpuKey2[8]		=  {  (  unsigned  char  )0xbf,  (  unsigned  char  )0x7c,  (  unsigned  char  )0x43,  (  unsigned  char  )0xe0,  (  unsigned  char  )0xad,  (  unsigned  char  )0xbe,  (  unsigned  char  )0x0,  (  unsigned  char  )0x5d  };
unsigned  char  DEFAULT_cpuKey3[8]		=  {  (  unsigned  char  )0x88,  (  unsigned  char  )0x4b,  (  unsigned  char  )0xb8,  (  unsigned  char  )0x81,  (  unsigned  char  )0x30,  (  unsigned  char  )0xa1,  (  unsigned  char  )0xf0,  (  unsigned  char  )0x54  };
unsigned  char  DEFAULT_macKey1[8]		=  {  (  unsigned  char  )0x1e,  (  unsigned  char  )0x5b,  (  unsigned  char  )0x64,  (  unsigned  char  )0x9c,  (  unsigned  char  )0x5c,  (  unsigned  char  )0x15,  (  unsigned  char  )0x28,  (  unsigned  char  )0xf4  };
unsigned  char  DEFAULT_macKey2[8]		=  {  (  unsigned  char  )0x1e,  (  unsigned  char  )0x5b,  (  unsigned  char  )0x64,  (  unsigned  char  )0x9c,  (  unsigned  char  )0x5c,  (  unsigned  char  )0x15,  (  unsigned  char  )0x28,  (  unsigned  char  )0xf4  };
unsigned  char  DEFAULT_macKey3[8]		=  {  (  unsigned  char  )0x1e,  (  unsigned  char  )0x5b,  (  unsigned  char  )0x64,  (  unsigned  char  )0x9c,  (  unsigned  char  )0x5c,  (  unsigned  char  )0x15,  (  unsigned  char  )0x28,  (  unsigned  char  )0xf4  };
*/
static  unsigned  char  DEFAULT_licenseKey1[8]	=  {  (  unsigned  char  )0xac,  (  unsigned  char  )0x4b,  (  unsigned  char  )0x45,  (  unsigned  char  )0xa3,  (  unsigned  char  )0x2f,  (  unsigned  char  )0x7f,  (  unsigned  char  )0x22,  (  unsigned  char  )0xcd  };
static  unsigned  char  DEFAULT_licenseKey2[8]	=  {  (  unsigned  char  )0xec,  (  unsigned  char  )0xf1,  (  unsigned  char  )0x41,  (  unsigned  char  )0xa5,  (  unsigned  char  )0xbb,  (  unsigned  char  )0xb4,  (  unsigned  char  )0xd,  (  unsigned  char  )0xc0  };
static  unsigned  char  DEFAULT_licenseKey3[8]	=  {  (  unsigned  char  )0x58,  (  unsigned  char  )0x32,  (  unsigned  char  )0x46,  (  unsigned  char  )0x97,  (  unsigned  char  )0x37,  (  unsigned  char  )0x6f,  (  unsigned  char  )0xa3,  (  unsigned  char  )0xd2  };
//  static  unsigned  char  DEFAULT_commKey1[8]		=  {  (  unsigned  char  )0x72,  (  unsigned  char  )0xfa,  (  unsigned  char  )0x4e,  (  unsigned  char  )0xb3,  (  unsigned  char  )0xb3,  (  unsigned  char  )0x39,  (  unsigned  char  )0xca,  (  unsigned  char  )0x4a  };

static  unsigned  char  DEFAULT_commKey1[8]		=  {  0x72,  0xfa,  0x4e,  0xb3,  0xb3,  0x39,  0xca,  0x4a  };

static  des_key_schedule  ks,  ks2,  ks3;

static  char  cbc_data[40]  =  "7654321 Now is the time for }";			//  切记：需要更换。

 extern  "C"  int  initLicenseEnc(  void  *  pEncCtx  )
{
	int	 iErr  =  -1;
	int  j  =  0;
	QY_ENC_CTX	*	pCtx	=	(  QY_ENC_CTX  *  )pEncCtx;

	//  if  (  pCtx->type  ==  CONST_qyEncType_qnm  )  {
	// 		return  initQnmEnc(  pEncCtx  );
	//  }

	if  (  (  j  =  des_key_sched(  (  C_Block  *  )DEFAULT_licenseKey1,  ks  )  )  !=  0  )  {
		printf(  "Key error %d\n",  j  );
		goto  errLabel;
	}
	if  (  (  j  =  des_key_sched(  (  C_Block  *  )DEFAULT_licenseKey2,  ks2  ) )  !=  0  )  {
		printf(  "Key error %d\n",  j  );
		goto  errLabel;
	}
	if  (  (  j  =  des_key_sched(  (  C_Block  *  )DEFAULT_licenseKey3,  ks3  )  )  !=  0  )  {
		printf(  "Key error %d\n",  j  );
		goto  errLabel;
	}

	iErr   =   0;
	
errLabel:

	return  iErr;

}
 extern  "C"  void  exitLicenseEnc(  void  *  pEncCtx  )
{
	QY_ENC_CTX	*	pCtx	=	(  QY_ENC_CTX  *  )pEncCtx;
	return;
}


 extern  "C"  int  licenseEnc(  void  *  pEncCtx,  char  *  input,  unsigned  int  inputSize,  char  *  output,  unsigned  int  *  pOutputSize  )
{
	 des_cblock		iv3;

	 if  (  !input  ||  !output  ||  inputSize  %  8  )  return  -1;
	 if  (  inputSize  >  *  pOutputSize  )  return   -1;

	 memcpy(  iv3,  DEFAULT_commKey1,  sizeof(  DEFAULT_commKey1  )  );
	 des_ede3_cbc_encrypt(  (  C_Block  *  )input,  (  C_Block  *  )output,  inputSize,  ks,  ks2,  ks3,  (  C_Block  *  )iv3,  DES_ENCRYPT  );
	 *pOutputSize  =  inputSize;

	 return  0;
	 
}

 extern  "C"  int  licenseDec(  void  *  pEncCtx,  char  *  input,  unsigned  int  inputSize,  char  *  output,  unsigned  int  *  pOutputSize  )
{
	 des_cblock		iv3;

	 if  (  !input  ||  !output  ||  inputSize  %  8  )  return  -1;
	 if  (  inputSize  >  *  pOutputSize  )  return   -1;

	 memcpy(  iv3,  DEFAULT_commKey1,  sizeof(  DEFAULT_commKey1  )  );
	 des_ede3_cbc_encrypt(  (  C_Block  *  )input,  (  C_Block  *  )output,  inputSize,  ks,  ks2,  ks3,  (  C_Block  *  )iv3,  DES_DECRYPT  );
	 *pOutputSize  =  inputSize;

	 return  0;
	 
}


 extern  "C"  int  testLicenseMain(  char  *  input,  int  inputLen,  char  * chkNum,  unsigned int * chkNumLen  )
{
	 int			iErr		=  -1;
	unsigned  int i,j,err=0;
	// des_cblock in,out,outin,iv3;
	// unsigned char cbc_in[40];
	unsigned char cbc_out[256]		=  "";
	unsigned char cbc_decBuf[256]	=  "";
	BOOL	bLicenseDesInited  =  FALSE;

	if  (  initLicenseEnc(  NULL  )  )  goto  errLabel;
	bLicenseDesInited  =  TRUE;

	memset(  cbc_out,  0,  sizeof(  cbc_out  )  );
	//  memset(cbc_in,0,40);
	//  i=strlen((char *)DEFAULT_commKey1)+1;
	//  i=((i+7)/8)*8;

	//  i   =   40;

	i  =  ( (  inputLen  +  7 ) / 8 ) * 8;

	j  =  i;
	if  (  licenseEnc(  NULL,  input,  i,  (  char  *  )cbc_out,  &j  )  )  goto  errLabel;
	i  =  j;
	if  (  licenseDec(  NULL,  (  char  *  )cbc_out,  j,  (  char  *  )cbc_decBuf,  &i  )  )  goto  errLabel;

	qyBuf2X(  ( char * )&cbc_out,  i,  chkNum  );

	*chkNumLen  =  2 * i;

	iErr  = 0;
errLabel:

	if  (  bLicenseDesInited  )  exitLicenseEnc(  NULL  );
	
   //  _CrtDumpMemoryLeaks( );
   
   return iErr;
}

 extern  "C"  int  decProc(  char  * inputEnc,  int  inputEncLen,  char  *  output,  unsigned int * pOutputLen  )
{
	 int				iRet					=  -1;
	 BOOL				bDes3Inited				=  FALSE;
	 char				outputDec[256]			=  "";
	 char				realBuf[256]			=  "";
	 unsigned  int		i,  j,  len;

	 memset(  realBuf,  0,  sizeof(  realBuf  )  );
	 if (  initLicenseEnc(  NULL  )  )  goto  errLabel;
	 bDes3Inited		=		TRUE;

	 qyX2Buf(  inputEnc,  realBuf,  sizeof( realBuf )  );
	 len				=  strlen(  inputEnc ) / 2;
	 
	 i  =  (  ( len + 7  ) / 8  )  *  8;
	 j  =  i;

	 if (  licenseDec(  NULL,  realBuf,  i,  outputDec,  &j  )  )  goto  errLabel; 
	 if (  !strstr(  outputDec,  "I love you:"  ) 
		   ||  !strstr(  outputDec,  "I love every people!"  )  )  goto  errLabel;
	 memset(  realBuf,  0,  sizeof(  realBuf )  );
	 memcpy(  realBuf,  outputDec + sizeof(  "I love you:"  ) - 1,  strlen( outputDec ) + 2 - sizeof(  "I love you:"  ) - sizeof( "I love every people!"  )  );

	 memcpy(  output,  realBuf, 256 );
	 *pOutputLen  =  strlen( output );


	 iRet  =  0;
errLabel:
	 if (  bDes3Inited  )  exitLicenseEnc(  NULL  );
	 return  iRet;
}




