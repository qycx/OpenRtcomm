
#ifndef  __comPortCfg_h__
#define  __comPortCfg_h__	//  {

//
//  2014/08/06
#define			MAX_idInfos_allowed								10

//
//  2012/08/01
typedef  struct  __comPortCfg_t									{
				 //  
				 int											iPtzType;									//  2015/09/20
				 //
				 int											m_pelcoType;
				 int											m_nAddr;
				 //

				 unsigned  int									portNo;
				 //
				 int											m_rate;
				 int											m_parity;
				 int											m_dataBit;
				 int											m_stopBit;
				 //
				 //  
				 QY_MESSENGER_ID								idInfos_allowed[MAX_idInfos_allowed];		//  5

				 //
				 TCHAR											tHint[255  +  1];							//  2012/08/12

				 //
				 BOOL											bCfgInited;

}		 COM_PORT_cfg;





#endif  //  }

