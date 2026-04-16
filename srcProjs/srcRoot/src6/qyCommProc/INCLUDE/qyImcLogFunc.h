
#ifndef  __QYIMCLOGFUNC_H__
#define  __QYIMCLOGFUNC_H__	 /*  {  */

#ifdef  __cplusplus
 extern "C" {
#endif



#define		QIM_MAXNAMELEN							64
#define		QIM_FULLNAMELEN							128
#define		QIM_MAXURLPROCEDLEN						1024
#define		QIM_MAXURLLOGLEN						128
#define		QIM_MAXTITLELOGLEN						20
#define		QIM_MAXKEYLOGLEN						64
#define		QIM_KEYTYPENAMELEN						8
#define		QIM_MAXCONTEXTLOGLEN					QY_CF_MAX_CONTEXT_LEN


	 
typedef  struct  __qimLogRcdX_t {
				 unsigned  char		type;									//  记录类型，如：普通、警告、严重
				 unsigned  char		time[14 + 1];
				 QY_BUF				url;
				 unsigned  char		result;									//  结果，如：禁止、记录、通过
				 QY_BUF				title;
				 QY_BUF				key;
				 unsigned  char		keyTypeName[QIM_KEYTYPENAMELEN + 1];	//  关键字类别，如：色情、游戏、证券、暴力、赌博、反动等
				 QY_BUF				context;
				 unsigned  char		mac[12 + 1];							//  mac.
																			//   ---	old members above
				 char				serviceType[2 + 1];			
				 char				detail[100 + 1];
																			//  以上在客户端生成
				 char				barId[10 + 1];
				 char				ip[12 + 1];
				 char				pcId[4 + 1];
				 int				id;										//  库中自动生成
}		QIM_LOGRCDX;



#define		QIM_MAXLOGLEN		2 + 1 +									\
								14 + 1 +								\
								8 + QIM_MAXURLLOGLEN + 1 +				\
								2 + 1 +									\
								8 + QIM_MAXTITLELOGLEN + 1 +			\
								8 + QIM_MAXKEYLOGLEN + 1 +				\
								QIM_KEYTYPENAMELEN + 1 +				\
								8 + QIM_MAXCONTEXTLOGLEN + 1 +			\
								12 +									\
								1 +										\
								64		// 此项为防越界而设

#define		QIM_MAXLOGFMTLEN	128
#define		QY_IMCLOGFMT		"%02x|%014s%|%08x%s|%02x|%08x%s|%08x%s|% 8s|%08x%s|%012s\n"



int		qyImcCreateLogRcd( unsigned char cType, char *url, unsigned char result, char *title, char *key, char * keyTypeName, char *context, char *mac, QIM_LOGRCDX *pLogRcd );
void	qyImcFreeLogRcd( QIM_LOGRCDX *pLogRcd );
int		qyImcLogInfo( void *pLogContext, void *p );
int		qyImcCfCallback( void *pCfInfoParam, void *p2 );
int		getNextQyImcLogRcd( FILE *fp, QIM_LOGRCDX *pLogRcd );
void	showQyImcLogRcd(  QIM_LOGRCDX  *  pLogRcd  );


int		qmPreSetupDict(  void  *  pCfFileParam,  FILE  *  fp,  void  *  pOpStructParam  );
int		qmGetPhrase(  void  *  pCfFileParam,  FILE  *  fp,  char  *  keyBuf,  unsigned  int  len,  int  *  lang,  int  *  lTypeInfo,  int  *  level  );



#ifdef __cplusplus
 }
#endif


#endif /* } */


