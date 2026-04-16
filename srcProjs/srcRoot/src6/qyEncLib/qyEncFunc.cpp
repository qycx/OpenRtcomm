
// testDes.cpp : Defines the entry point for the console application.
//

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


// static unsigned char cbc_key [8]={0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef};
// static unsigned char cbc2_key[8]={0xf0,0xe1,0xd2,0xc3,0xb4,0xa5,0x96,0x87};
// static unsigned char cbc3_key[8]={0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
// static unsigned char cbc_iv  [8]={0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};

static  unsigned  char  cbc_key[8]		=  {0x93,0xb1,0x53,0x10,0xe0,0x9a,0x4a,0x1a};
static  unsigned  char  cbc2_key[8]		=  {0x85,0x99,0x0d,0xb8,0x22,0xd4,0x98,0x4b};
static  unsigned  char  cbc3_key[8]		=  {0xa4,0xb3,0xe5,0xcf,0xd8,0xbf,0x43,0x41};
static  unsigned  char  cbc_iv[8]		=  {0x83,0x2e,0xb8,0x8d,0xcd,0x6d,0x95,0xc7};

static  des_key_schedule  ks,  ks2,  ks3;

static  char  cbc_data[40]  =  "7654321 Now is the time for }";

 extern  "C"  int  initQyEnc(  void  *  pEncCtx  )
{
	int	 iErr  =  -1;
	int  j  =  0;
	QY_ENC_CTX	*	pCtx	=	(  QY_ENC_CTX  *  )pEncCtx;

	//  if  (  pCtx->type  ==  CONST_qyEncType_qnm  )  {
	// 		return  initQnmEnc(  pEncCtx  );
	//  }

	if  (  (  j  =  des_key_sched(  (  C_Block  *  )cbc_key,  ks  )  )  !=  0  )  {
		printf(  "Key error %d\n",  j  );
		goto  errLabel;
	}
	if  (  (  j  =  des_key_sched(  (  C_Block  *  )cbc2_key,  ks2  ) )  !=  0  )  {
		printf(  "Key error %d\n",  j  );
		goto  errLabel;
	}
	if  (  (  j  =  des_key_sched(  (  C_Block  *  )cbc3_key,  ks3  )  )  !=  0  )  {
		printf(  "Key error %d\n",  j  );
		goto  errLabel;
	}

	iErr   =   0;
	
errLabel:

	return  iErr;

}

 extern  "C"  void  exitQyEnc(  void  *  pEncCtx  )
{
	QY_ENC_CTX	*	pCtx	=	(  QY_ENC_CTX  *  )pEncCtx;

	//  if  (  pCtx->type  ==  CONST_qyEncType_qnm  )  {
	//		exitQnmEnc(  pEncCtx  );	return;
	//  }

	 return;
}


 extern  "C"  int  qyEnc(  void  *  pEncCtx,  char  *  input,  unsigned  int  inputSize,  char  *  output,  unsigned  int  *  pOutputSize  )
{
	 des_cblock		iv3;

	 if  (  !input  ||  !output  ||  inputSize  %  8  )  return  -1;
	 if  (  inputSize  >  *  pOutputSize  )  return   -1;

	 memcpy(  iv3,  cbc_iv,  sizeof(  cbc_iv  )  );
	 des_ede3_cbc_encrypt(  (  C_Block  *  )input,  (  C_Block  *  )output,  inputSize,  ks,  ks2,  ks3,  (  C_Block  *  )iv3,  DES_ENCRYPT  );
	 *pOutputSize  =  inputSize;

	 return  0;
	 
}

 extern  "C"  int  qyDec(  void  *  pEncCtx,  char  *  input,  unsigned  int  inputSize,  char  *  output,  unsigned  int  *  pOutputSize  )
{
	 des_cblock		iv3;

	 if  (  !input  ||  !output  ||  inputSize  %  8  )  return  -1;
	 if  (  inputSize  >  *  pOutputSize  )  return   -1;

	 memcpy(  iv3,  cbc_iv,  sizeof(  cbc_iv  )  );
	 des_ede3_cbc_encrypt(  (  C_Block  *  )input,  (  C_Block  *  )output,  inputSize,  ks,  ks2,  ks3,  (  C_Block  *  )iv3,  DES_DECRYPT  );
	 *pOutputSize  =  inputSize;

	 return  0;
	 
}


   
 int  testMain(int argc, char* argv[])
{
	unsigned  int i,j,err=0;
	// des_cblock in,out,outin,iv3;
	unsigned char cbc_in[40];
	unsigned char cbc_out[40];
	unsigned char cbc_decBuf[40];
	BOOL	bQyDesInited  =  FALSE;
	

	if  (  initQyEnc(  NULL  )  )  goto  errLabel;
	bQyDesInited  =  TRUE;

	memset(cbc_out,0,40);
	memset(cbc_in,0,40);
	i=strlen((char *)cbc_data)+1;
	i=((i+7)/8)*8;

	i   =   40;

	/*
	memcpy(iv3,cbc_iv,sizeof(cbc_iv));
	des_ede3_cbc_encrypt((C_Block *)cbc_data,(C_Block *)cbc_out,
		i,ks,ks2,ks3,(C_Block *)iv3,DES_ENCRYPT);

	memcpy(iv3,cbc_iv,sizeof(cbc_iv));
	des_ede3_cbc_encrypt((C_Block *)cbc_out,(C_Block *)cbc_decBuf, i,ks,ks2,ks3,(C_Block *)iv3,DES_DECRYPT  );
	*/
	j  =  i;
	if  (  qyEnc(  NULL,  cbc_data,  i,  (  char  *  )cbc_out,  &j  )  )  goto  errLabel;
	i  =  j;
	if  (  qyDec(  NULL,  (  char  *  )cbc_out,  j,  (  char  *  )cbc_decBuf,  &i  )  )  goto  errLabel;

errLabel:

	if  (  bQyDesInited  )  exitQyEnc(  NULL  );
	
#ifndef  __WINCE__
   _CrtDumpMemoryLeaks( );
#endif

	return 0;
}
