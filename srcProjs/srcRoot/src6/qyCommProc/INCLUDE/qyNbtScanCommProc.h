
#ifndef  __QYNBTSCANCOMMPROC_H__
#define  __QYNBTSCANCOMMPROC_H__	/*  {  */

#ifdef  __cplusplus
extern  "C"  {
#endif



typedef  struct  __qnmNbtPcInfo_t						{
				 char									ip[15  +  1];
				 char									mac[12  +  1];
				 char									compName[16  +  1];
				 char									usrName[16  +  1];
				 unsigned  char							is_server;
}		 QNM_NBT_PCINFO;


typedef  struct  __qyNbtScanCtx_t						{

				 void							*		pParentParam;
				 void							*		pDb;
				 WCHAR									showWho[32  +  1];

				 void							*		pfOutput;

}		 QY_NBTSCAN_CTX;





#ifdef  __cplusplus
}
#endif

#endif	/*  }  */

