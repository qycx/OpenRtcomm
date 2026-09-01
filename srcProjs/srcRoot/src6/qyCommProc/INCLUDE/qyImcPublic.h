
#ifndef __QYIMCPUBLIC_H__
#define __QYIMCPUBLIC_H__	/* { */


 // 监视类别
/*
#define		QY_IMC_TYPE_INVALID					0
#define		QY_IMC_TYPE_SQ						1				// 色情
#define		QY_IMC_TYPE_FD						2				// 反动
#define		QY_IMC_TYPE_BL						3				// 暴力
*/

#define		QIM_POLICYTYPELEN					2


typedef  struct  __qimPolicyTypeItem_t  {
				 char	*	dm;
				 char	*	des;
}		 QIM_POLICYTYPEITEM;

#define		CONST_imPolicyFlg_jz				0x1						//  禁止位
#define		CONST_imPolicyFlg_jl				0x2						//  记录位
#define		CONST_bmPolicyFlg_jl				0x1						//  禁止位


extern		QIM_DMITEM							CONST_imPolicyTable[];
extern		QIM_DMITEM							CONST_bmPolicyTable[];


#define		CONST_imPolicyDefault				CONST_imPolicyTable[0]
#define		CONST_bmPolicyDefault				CONST_bmPolicyTable[0]

#define		CONST_imPolicy_qyKeyTypeDefault		CONST_imPolicyTable[1]
#define		CONST_bmPolicy_qyKeyTypeDefault		CONST_bmPolicyTable[1]


//  策略描述
typedef  struct  __qyImcPolicyRcd_t  {
				 char				imPolicy[2  +  1];
				 char				bmPolicy[2  +  1];
				 unsigned  char		keyTypeCode;
				 char				keyTypeName[QIM_KEYTYPENAMELEN  +  1];
}		 QY_IMCPOLICY_RCD;




char  *  qimServiceTypeStr(  char * serviceType  );
char  *  qimServiceTypeFromStr(  char  *  str  );
char  *  imPolicyStr(  char * policyType  );
char  *  imPolicyFromStr(  char * str  );
char  *  bmPolicyStr(  char * policyType  );
char  *  bmPolicyFromStr(  char * str  );






#endif /* } */
