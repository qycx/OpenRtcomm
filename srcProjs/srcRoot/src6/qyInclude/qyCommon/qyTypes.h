
#ifndef __QYTYPES_H__
#define __QYTYPES_H__	/* { */

typedef  short  int  INT2;
typedef  int  INT4;

//  typedef  unsigned  char  UCHAR;
typedef  unsigned  short  int  UINT2;	/* UINT2 defines a two byte word */
typedef  unsigned  long  int  UINT4;	/* UINT4 defines a four byte word */

// QY_BUF的长度为data申请的内存大小，故对string, len为strlen() + 1;
// QY_BUF的资源类型.
#define		QY_BUF_MAN_FREE				1
#define		QY_BUF_AUTO_FREE			2


//
#include	"qyTypes_open.h"

//
#if  0
//
typedef  struct  __qyBuf_t				{
				 UINT4					resourceType;		// 资源类型
				 UINT4					len;
				 unsigned  char		*	data;	
}		 QY_BUF;

//
typedef  struct  __qyStr_t				{
				 UINT4					len;
				 UINT4					resourceType;
				 unsigned  char		*	szData;
}		 QY_STR;

//
#endif 

// 资源类型取值
#define		BUF_DYN_ALLOCATED			1	
#define		BUF_STATIC					2

typedef  DWORD  (  WINAPI  *  QY_THREADPROC  )(  LPVOID lpParameter  );




typedef  struct  __qyIdcItem_t						{
				 long								idc;				//	控件ID
				 LONG_PTR							idcType;			//  long								idcType;			//  idc的类型
				 TCHAR			*					des;				//  对edit表示初始值; 对comboBox表示初始选项的type值,  使用-1表不操作,  或者由程序员来定义操作
				 LONG_PTR  /*long*/					lIdc, rIdc;			//  左边的idc, 右边的idc
				 //  QY_DMITEM		*					pTable;				//  comboBox的初始化值; 对checkBox, 此项可用于表示对数据库的查询分类
				 int								iResIdTable;		//  2005/11/15, 将上面的table指针改为resId表示的table,可以在使用时方便一些
				 long								maxBytes;			//  对edit输入字节数限制; 对checkBox, 0表unchecked,  非0表checked
				 long								x, y, w, h;			//  x, y表左上点的坐标
				 long								flg;
				 TCHAR			*					sqlColName;			//  对查询，标志该控件代表的列名
				 TCHAR			*					name;				//	提供字段名字,  <!-- 原先的备注被替换  -->	//  char			*					comment;			//	提供调试用的注释
				 unsigned  int						uiCommSeqNo;		//  传输顺序,  从0起，2003年0404添加
				 unsigned  int						uiFieldId;			//  2005/02/06, 字段ID，可以用在注册信息的识别上
				 unsigned  char						ucLevel;			//  2005/02/06, 单位级别，syr为0，bm为1，dw为2, bb为3，zb为4...，共5级
																		//				也可以用在资产标号上，编号0，编号1，遍号2等
																		//				ucLevel靠uiFieldId来区分类别
}		 QY_IDCITEM;
 

typedef  struct  __qyVarPair_t  {
				 char				*	name;
				 char				*	val;
}		 QY_VAR_PAIR;


#ifdef  __cplusplus
  extern  "C"  {
#endif
	
TCHAR  *  qyGetDesByType(  QY_DMITEM  *  pTable,  long  type  );
TCHAR  *  qyGetDesByType1(  QY_DMITEM  *  pTable,  long  type  );
int  qyGetTypeByDes(  QY_DMITEM  *  pTable,  LPCTSTR  des  );
QY_DMITEM  *  qyGetDmItemByType(  QY_DMITEM  *  pTable,  long  type,  unsigned  int  uiItemSize  );
QY_DMITEM  *  qyGetDmItemByDes(  QY_DMITEM  *  pTable,  LPCTSTR  des,  unsigned  int  uiItemSize  );
int  getnItems(  QY_DMITEM  *  pTable  );

#ifdef  __cplusplus
  }
#endif

#endif /* } */

