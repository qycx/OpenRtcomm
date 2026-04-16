

#ifndef  __QYENCFUNC_H__
#define  __QYENCFUNC_H__	/*  {  */


#ifdef  __cplusplus
 extern  "C"  {
#endif

#include	"myd3des.h"


typedef  struct  __qyEncCtx_t  {

				 unsigned  int	type;	
	
				 union  {
					 des_ctx	des;
				 }				u;

}		 QY_ENC_CTX;


#define		CONST_qyEncType_null				0
#define		CONST_qyEncType_des					1
#define		CONST_qyEncType_qnm					2		//  ≤ª”√
#define		CONST_qyEncType_qwm					3		//  2004/01/02
#define		CONST_qyEncType_rsa					4		//  2008/06/09
#define		CONST_qyEncType_rsa1				5		//  

//
#define		CONST_qyEncType_aes256				100



//
int  initQyEnc(  void  *  pEncCtx  );
void  exitQyEnc(  void  *  pEncCtx  );
int  qyEnc(  void  *  pEncCtx,  char  *  input,  unsigned  int  inputSize,  char  *  output,  unsigned  int  *  pOutputSize  );
int  qyDec(  void  *  pEncCtx,  char  *  input,  unsigned  int  inputSize,  char  *  output,  unsigned  int  *  pOutputSize  );
int  initQnmEnc(  void  *  pEncCtx,  void  *  pUpdateEncCtx,  void  *  pQuitEncCtx,  void  *  pCommEncCtx  );
void  exitQnmEnc(  void  *  pEncCtx,  void  *  pUpdateEncCtx,  void  *  pQuitEncCtx,  void  *  pCommEncCtx  );
int  qnmDec(  void  *  pEncCtx,  char  *  input,  unsigned  int  inputSize,  char  *  output,  unsigned  int  *  pOutputSize  );
int  qnmEncStr(  void  *  pEncCtx,  char  *  input,  char  *  output,  unsigned  int  *  pOutputSize  );
int  qnmEncData(  void  *  pEncCtx,  char  *  input,  unsigned  int  inputLen,  char  *  output,  unsigned  int  *  pOutputSize  );
int  qnmDecData(  void  *  pEncCtx,  char  *  input,  unsigned  int  inputSize,  char  *  output,  unsigned  int  *  pOutputSize  );


int  initLicenseEnc(  void  *  pEncCtx  );
void  exitLicenseEnc(  void  *  pEncCtx  );
int  licenseEnc(  void  *  pEncCtx,  char  *  input,  unsigned  int  inputSize,  char  * output,  unsigned  int  *  pOutputSize  );
int  licenseDec(  void  *  pEncCtx,  char  *  input,  unsigned  int  inputSize,  char  *  output,  unsigned  int  *  pOutputSize  );

int  testLicenseMain(  char  *  input,  int  inputLen,  char  * chkNum,  unsigned int *  chkNumLen  );
int  decProc(  char  *  inputEnc,  int inputEncLen,  char * output,  unsigned int *pOutputLen  );
int  testMain(  );


unsigned  long  hex2( char  *  d,  char  *  s,  unsigned  long  size  );


void  qySrand(unsigned int seed);
int  qyRand(  void  );
int  testRand( );
void  qyFakeBuf(  char  *  input,  unsigned  int  size,  char  *  output  );
int  qyUnfakeBuf(  char  *  input,  unsigned  int  size,  char  *  output  );





#ifdef  __cplusplus
 }
#endif


#endif  /*  }  */

