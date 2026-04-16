
#ifndef  __QNMCUSTOMER_H__
#define  __QNMCUSTOMER_H__	/*  {  */

#ifdef  __cplusplus
  extern  "C"  {
#endif


#define		CONST_qyCustomId_null					0			//  通用,  清扬创新
//
#define		CONST_qyCustomId_shhg					1001		//  
//
#define		CONST_qyCustomId_zjga					1101		//	
//
#define		CONST_qyCustomId_general				1200		//	
//
#define		CONST_qyCustomId_business				1250		//  企业版客户端
//
#define		CONST_qyCustomId_bjyz					1300		//  
//
#define		CONST_qyCustomId_hzj					1310		//  。		//  2018/10/23
#define		CONST_qyCustomId_hbwj					1311		//  		//  2018/12/14

#define		CONST_qyCustomId_cqyt					1400		// 长庆油田  20240103

#define		CONST_qyCustomId_jkcs					1500		// 监控传输 //20240906



//
typedef  struct  __qyCustomFieldInfo_t  {
				 int								id;
				 char								name[64];
				 unsigned  short					usLen;
				 unsigned  short					usType;
				 unsigned  short					usMaxBytes;
}		 QY_CUSTOM_FIELDINFO;


//  通用的注册信息
typedef  struct  __generalRegInfo_t						{
				 /*
				 char								cm[20  +  1];		//  处名	8-10个中文字
				 char								ks[12  +  1];		//  科室		6个中文字
				 char								yhxm[64  +  1];		//  用户姓名	
				 char								lxdh[64  +  1];		//  联系电话
				 char								sbxh[64  +  1];		//  设备型号	例如Hp vl 420 dt
				 char								sydd[64  +  1];		//  使用地点	**大楼1901室
				 char								jqlx[64  +  1];		//  机器类型	微机、便携机、其他
				 char								zyyt[64  +  1];		//  主要用途	办公
				 char								yhlx[32  +  1];		//  用户类型	本单位用户、外单位临时用户
				 char								lsyhdwmc[64  +  1];	//  临时单位用户名称
				 */
				 char								unused;
}		 GENERAL_REG_INFO;	

 //  注册信息
typedef  struct  __shhgRegInfo_t					{
				 /*
				 char								gm[20  +  1];		//  关(处)名	8-10个中文字
				 char								ks[12  +  1];		//  科室		6个中文字
				 char								yhxm[64  +  1];		//  用户姓名	
				 char								lxdh[64  +  1];		//  联系电话
				 char								sbxh[64  +  1];		//  设备型号	例如Hp vl 420 dt
				 char								sbxlh[64  +  1];	//  设备序列号	如Cn23408431
				 char								gcbh[64  +  1];		//  关产编号	103aba2002
				 char								sydd[64  +  1];		//  使用地点	**大楼1901室
				 char								jqlx[64  +  1];		//  机器类型	微机、便携机、其他
				 char								zyyt[64  +  1];		//  主要用途	办公
				 char								yhlx[32  +  1];		//  用户类型	本单位用户、外单位临时用户
				 char								lsyhdwmc[64  +  1];	//  临时用户单位名称
				 */
				 char								unused;
}		 SHHG_REG_INFO;



#define		DEFAULT_qyCustomInfo_hint1				"使用人请填写下表(*表必填项)"
#define		DEFAULT_qyCustomInfo_hint2				"请您在2003年 月 日前完成上表登记，过期将无法登录网络"


 //  注册界面定制信息， 
typedef  struct  __qrtCustomInfo_t					{
				 TCHAR			*					title;			//  登记表题头
				 TCHAR			*					hint1;			//  使用人登录时填写下表
				 TCHAR			*					hint2;			//	请您在2003年 月 日前完成上表登记，过期将无法登录网络
				 TCHAR			*					wndTitle;		//	窗口题头
				 //  unsigned  short					usWidthForEdit,  usHeightForEdit;
}		 QRT_CUSTOM_INFO;		
 


#define		DEFAULT_regToolAppName					qyGetDesByType1(  CONST_qyRegToolAppNameTable,  CONST_qyCustomId_null  )

extern  QY_DMITEM	CONST_qyMcAppNameTable[];
extern  QY_DMITEM	CONST_qyRegToolAppNameTable[];
extern  QY_DMITEM	CONST_qyMcAppNameTable_netMc2[];


char  *			qnmDevelopTimestamp(  );
//  char  *			qyGetQyMcAppName(  );
TCHAR  *			qyGetRegToolAppName(  );



#ifdef  __cplusplus
  }
#endif


#endif  /*  }  */

