
#ifndef   __pcCommType_defs_h__
#define  __pcCommType_defs_h__  //  {


//
#define		CONST_pcCommType_null									0

#define		CONST_pcCommType_adapter								1
#define		CONST_pcCommType_proxy									2
#define		CONST_pcCommType_computer								3
#define		CONST_pcCommType_cleanNetworkProp						4		//  2006/05/07, 用来在以上甚至更多的网络属性上传后发标志位以清理相应的属性
//
#define		CONST_pcCommType_process								11
#define		CONST_pcCommType_eventLog								12		//  2005/08/31
#define		CONST_pcCommType_usrInfo								13		//  2005/09/04
#define		CONST_pcCommType_tcpTable								14		//  2005/09/17
#define		CONST_pcCommType_udpTable								15		//  2005/09/17
#define		CONST_pcCommType_printers								16		//  2005/09/18
#define		CONST_pcCommType_processRule							17		//  2005/10/10
#define		CONST_pcCommType_processModule							18		//  2006/04/14
#define		CONST_pcCommType_windowsUpdatePolicy					19		//  2006/05/21
#define		CONST_pcCommType_registryVal							20		//  2006/07/16, 指注册表或文件等特征信息
#define		CONST_pcCommType_netFlow								21		//  2006/09/10
#define		CONST_pcCommType_netShare								22		//  2007/02/14
//
//
#define		CONST_pcCommType_switchRule								1000	//  2006/07/16, 将这些参数都统一起来
#define		CONST_pcCommType_switchPortRule							1001	//  2006/07/16, 将这些参数都统一起来
//
#define		CONST_pcCommType_pcFileMonRules							2		//  2006/07/16, 历史遗留问题，此定义不能改
#define		CONST_pcCommType_registryRule							2000	//  2006/07/16, 指注册表或文件等规则信息
#define		CONST_pcCommType_registryRuleStatus						2001	//  2006/08/02, 注册表规则的状态信息			
#define		CONST_pcCommType_queryCfgs								2002	//  2006/08/06, 取配置的请求信息
#define		CONST_pcCommType_pcProcessKnowledge						2003	//  2006/08/12, 进程知识
#define		CONST_pcCommType_pcRegistryKnowledge					2004	//  2006/08/12, 注册表知识



#endif  //  }


