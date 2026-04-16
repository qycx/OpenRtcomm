

#ifndef __QYMCMAINTEMP_H__
#define __QYMCMAINTEMP_H__	/* { */


#ifdef __DEBUG__	//  __DEBUG__ must be defined to make all below valid!


#define	 QY_MC_MAX_URL_MON_CNT		50		// URL监视窗中可配置的最大URL监视数
#define  QY_MC_MAX_KEY_MON_CNT		50		// 关键字监视窗中可配置的最大关键字监视数


extern  "C"  int		qyX2C(  char * xBuf  );
extern  "C"  char  *	qyC2X(  char c,  char * xBuf,  int size  );
extern  "C"  char  *	qyBuf2X(  char  *  buf,  unsigned  int  len,  char  *  xBuf  );
extern  "C"  char  *	qyX2Buf(  char  *  xBuf,  char  *  buf,  unsigned  int  len  );


#endif		//  __DEBUG__ must be defined to make all above valid!

#endif /* } */

