
#ifndef  __QYIMCSNDOBJS_H__
#define  __QYIMCSNDOBJS_H__	/*  {  */

enum  ENUM_QYSNDOBJS {
		Emem_qyImcLog,
		Emem_qyGuestLog,
};

#define  QM_SNDPOLICYTYPE_B2P	1

typedef  struct  __qmB2pSndPolicy_t  {
		 char	 time[14];
}		 QM_B2P_SNDPOLICY;


typedef  struct  __qmSndPolicy_t  {
		 int	 type;

		 union		{
			 QM_B2P_SNDPOLICY	b2p;
		 }			u;

}		 QM_SNDPOLICY;





#endif	/*  }  */


