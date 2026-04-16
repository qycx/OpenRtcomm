
#include	<windows.h>
#include	"myd3des.h"
#include	"qyEncCommon.h"
#include	"memory.h"


unsigned  char  DEFAULT_qnmKey[8]			=  {  (  unsigned  char  )0x8a,  (  unsigned  char  )0x02,  (  unsigned  char  )0x4f,  (  unsigned  char  )0xbf,  (  unsigned  char  )0x0e,  (  unsigned  char  )0x40,  (  unsigned  char  )0x2c,  (  unsigned  char  )0x5e  };
unsigned  char  DEFAULT_qnmUpdateKey[8]		=  {  (  unsigned  char  )0xac,  (  unsigned  char  )0x86,  (  unsigned  char  )0x6a,  (  unsigned  char  )0x29,  (  unsigned  char  )0xa3,  (  unsigned  char  )0x4f,  (  unsigned  char  )0x58,  (  unsigned  char  )0x47  };
unsigned  char  DEFAULT_qnmQuitKey[8]		=  {  (  unsigned  char  )0x81,  (  unsigned  char  )0x4d,  (  unsigned  char  )0xd4,  (  unsigned  char  )0x4e,  (  unsigned  char  )0x67,  (  unsigned  char  )0x03,  (  unsigned  char  )0xc2,  (  unsigned  char  )0x17  };
unsigned  char  DEFAULT_qnmCommKey[8]		=  {  (  unsigned  char  )0xb3,  (  unsigned  char  )0xb3,  (  unsigned  char  )0x6e,  (  unsigned  char  )0xc4,  (  unsigned  char  )0x17,  (  unsigned  char  )0x1f,  (  unsigned  char  )0x97,  (  unsigned  char  )0xfe  };


 extern  "C"  int  initQnmEnc(  void  *  pEncCtx,  void  *  pUpdateEncCtx,  void  *  pQuitEncCtx,  void  *  pCommEncCtx  )
{
	 int			iErr  =  -1;
	 QY_ENC_CTX  *  pCtx  =  (  QY_ENC_CTX  *  )pEncCtx;
	 
	 if  (  !pCtx  )  goto  errLabel;
	 des_key(  &pCtx->u.des,  DEFAULT_qnmKey  );
	 if  (  pCommEncCtx  )  {
		 (  (  QY_ENC_CTX  *  )pCommEncCtx  )->type  =  CONST_qyEncType_qwm;
		 des_key(  &(  (  QY_ENC_CTX  *  )pCommEncCtx  )->u.des,  DEFAULT_qnmCommKey  );			//  2004/01/02
	 }

	 iErr  =  0;

errLabel:

	 return  iErr;

}

 extern  "C"  void  exitQnmEnc(  void  *  pEncCtx,  void  *  pUpdateEncCtx,  void  *  pQuitEncCtx,  void  *  pCommEncCtx  )
{
	 QY_ENC_CTX  *  pCtx  =  (  QY_ENC_CTX  *  )pEncCtx;

	 return;
}

 //  2010/05/07
 extern  "C"  int  qnmEncStr(  void  *  pEncCtx,  char  *  input,  char  *  output,  unsigned  int  *  pOutputSize  )  
{
	 QY_ENC_CTX  *  pCtx  =  (  QY_ENC_CTX  *  )pEncCtx;
	 unsigned  int	len;
	 unsigned  int  outputLen;
	 	 	 
	 if  (  !input  ||  !input[0]  ||  !output  )  return  -1;

	 len  =  strlen(  input  )  +  1;
	 if  (  len  %  8  )  outputLen  =  (  (  len  /  8  )  +  1  )  *  8;
	 else  outputLen  =  len;

	 if  (  outputLen  >  *pOutputSize  )  return  -1;
	 strcpy(  output,  input  );

	 des_enc(  &pCtx->u.des,  (  unsigned  char  *  )output,  outputLen  /  8  );
	 *pOutputSize  =  outputLen;

	 return  0;
	 
}


 extern  "C"  int  qnmEncData(  void  *  pEncCtx,  char  *  input,  unsigned  int  inputLen,  char  *  output,  unsigned  int  *  pOutputSize  )
{
	 QY_ENC_CTX  *  pCtx  =  (  QY_ENC_CTX  *  )pEncCtx;
	 unsigned  int	len;
	 unsigned  int  outputLen;
	 	 	 
	 if  (  !inputLen  )  return  0;
	 if  (  !input  ||  !output  )  return  -1;

	 len  =  inputLen  +  4;
	 if  (  len  %  8  )  outputLen  =  (  (  len  /  8  )  +  1  )  *  8;
	 else  outputLen  =  len;

	 if  (  outputLen  >  *pOutputSize  )  return  -1;
	 memcpy(  output,  (  char  *  )&inputLen,  sizeof(  inputLen  )  );
	 memcpy(  output  +  sizeof(  inputLen  ),  input,  inputLen  );

	 des_enc(  &pCtx->u.des,  (  unsigned  char  *  )output,  outputLen  /  8  );
	 *pOutputSize  =  outputLen;

	 return  0;

}

 extern  "C"  int  qnmDecData(  void  *  pEncCtx,  char  *  input,  unsigned  int  inputSize,  char  *  output,  unsigned  int  *  pOutputSize  )
{
	 QY_ENC_CTX  *  pCtx  =  (  QY_ENC_CTX  *  )pEncCtx;
	 unsigned  long  len;

	 if  (  !input  ||  !output  ||  inputSize  %  8  )  return  -1;
	 
	 des_dec(  &pCtx->u.des,  (  unsigned  char  *  )input,  inputSize  /  8  );
	 memcpy(  (  char  *  )&len,  input,  4  );
	 if  (  len  >  inputSize  -  4 )  return  -1;
	 if  (  *pOutputSize  <  len  )  return  -1;	//  2004/01/03加入对输入长度的校验
	 memcpy(  output,  input  +  4,  len  );
	 *pOutputSize  =  len;

	 return  0;

}


 
 extern  "C"  int  qnmDec(  void  *  pEncCtx,  char  *  input,  unsigned  int  inputSize,  char  *  output,  unsigned  int  *  pOutputSize  )
{
	 QY_ENC_CTX  *  pCtx  =  (  QY_ENC_CTX  *  )pEncCtx;

	 if  (  !input  ||  !output  ||  inputSize  %  8  )  return  -1;
	 if  (  inputSize  >  *pOutputSize  )  return   -1;

	 des_dec(  &pCtx->u.des,  (  unsigned  char  *  )input,  inputSize  /  8  );
	 memcpy(  output,  input,  inputSize  );
	 *pOutputSize  =  inputSize;

	 return  0;
	 
}

