
#ifndef  __QNMCUSTOMCOMM_H__
#define  __QNMCUSTOMCOMM_H__	/*  {  */

//  此文件为定制信息通信和存储用
//  界面定制在qnmCustomGui.h中

//  下面的表中，表中项的次序指向存储顺序
//  每项的type表在输入中的存储顺序，des表存储项名字, 当type取值CONST_nullColId时，表该列不存储


#define		CONST_nullColId						99999

extern  QY_DMITEM  *  gpEventRegColsTable;		//  注册信息需要被摘取到qyPcEventTab中的部分。
extern  QY_DMITEM  *  gpRegEventRegColsTable;	//  产生注册事件的注册信息
extern  QY_DMITEM  *  gpRasEventDesColsTable;

extern  "C"  QY_DMITEM		CONST_regInfo2DbTable[];

//	extern  "C"  int  qnmSetPtrs(  QNM_REG_INFO  *  pRegInfo,  QNM_FIELD  fields[CONST_qnmMaxRegFields]  );
extern  "C"  int  qnmSetPtrs(  QY_DMITEM  *  pFiledIdTable,  QNM_REG_INFO  *  pRegInfo1,  QNM_FIELD  fields[CONST_qnmMaxRegFields]  );
extern  "C"  int  qnmSetFieldIdInRegInfo(  QNM_REG_INFO  *  pRegInfo  );
extern  "C"  int  getRegIndexByFieldId(  unsigned  int  uiFieldId  );
extern  "C"  int  getRegDbIndexByFieldId(  unsigned  int  uiFieldId  );
extern  "C"  int  getEventDbIndexByFieldId(  unsigned  int  uiFieldId  );




#endif  /*  }  */

