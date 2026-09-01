
#ifndef  __QYGUIPUBLIC_H__
#define  __QYGUIPUBLIC_H__	/* { */

#ifdef  __cplusplus
  extern  "C"  {
#endif


//  查询的配置限制  
//  #define		CONST_qyMaxQueryCols						45						//  查询的最大列数
#define		CONST_qyMaxQueryCols						64						//  2006/08/01修改，查询的最大列数
//  ListView的列配置限制
#define		DEFAULT_MAX_COLUMNS							CONST_qyMaxQueryCols	//  最多列数
#define		DEFAULT_MAX_COLUMN_NAME_LEN					20						//  列名最大长度



#if  10
typedef  struct  __qyColumnInfo_t					{
				 int								type;
				 TCHAR								label[CONST_qyMaxLabelLen  +  1];
				 int								iDataType;
				 int								fmt;
				 unsigned	short					width;
				 unsigned	char					ucLevel;
				 unsigned	short					nMaxBytes;			//	最大的字节数，0为不限
				 //
				 long								lParam;				//  2013/02/13
}		 QY_COLUMNINFO;
#endif

//  下面是控件的总体属性控制
#define		CONST_qyIdcFlgChkNotNull				(  1		 )		//  不能为空
#define		CONST_qyIdcFlgSetLimitText				(  1  <<  1	 )
#define		CONST_qyIdcFlgChkFixedLen				(  1  <<  2	 )
#define		CONST_qyIdcFlgDisabled					(  1  <<  3	 )
#define		CONST_qyIdcFlgNotFocused				(  1  <<  4  )
#define		CONST_qyIdcFlgTrim						(  1  <<  5  )
#define		CONST_qyIdcFlgHide						(  1  <<  6  )		//  隐藏
#define		CONST_qyIdcFlgNeeded					(  1  <<  7  )		//  对static来说，表示必填项; 对edit和comboBox来说，该控件无论是否隐藏都采用
#define		CONST_qyIdcFlgUnused					(  1  <<  8  )		//  该控件不使用
#define		CONST_qyIdcFlgNotForEdit				(  1  <<  9  )		//  在编辑审核中不使用，隐藏
#define		CONST_qyIdcFlgOnlyForEdit				(  1  <<  10  )		//  仅在编辑审核中使用和显示
#define		CONST_qyIdcFlgAddNullItem				(  1  <<  11  )		//  在combo中加入一条空的，以方便提供不限条件的选择，2005/02/12
#define		CONST_qyIdcFlgSearchUsingLike			(  1  <<  12  )		//  提供模糊查询，2006/05/03


//  下面是控件的输入范围限制
#define		CONST_qyIdcFlgPermitZw					(  1  <<  16  )		//  中文
#define		CONST_qyIdcFlgPermitAlpha				(  1  <<  17  )		//  英文字符
#define		CONST_qyIdcFlgPermitXdigit				(  1  <<  18  )		//  16进制数字
#define		CONST_qyIdcFlgPermitDigit				(  1  <<  19  )		//  10进制数字
#define		CONST_qyIdcFlgPermitComma				(  1  <<  20  )		//  ','
#define		CONST_qyIdcFlgPermitSemicolon			(  1  <<  21  )		//  ';'
#define		CONST_qyIdcFlgPermitSpace				(  1  <<  22  )		//  space
#define		CONST_qyIdcFlgPermitMinus				(  1  <<  23  )		//  -
#define		CONST_qyIdcFlgPermitDot					(  1  <<  24  )		//  .
#define		CONST_qyIdcFlgPermitAll					(  0xffff0000  )	//  不加限制


//  对话框编辑器中的网格对象素的因子
#define		CONST_factorOfDlgUnit					1.5
#define		CONST_multiplierOfDlgUnit				3		//  注：multiplier/divisor=factorOfDlgUnit
#define		CONST_divisorOfDlgUnit					2		//

//  控件类型
#define		CONST_qyIdcType_edit					1
#define		CONST_qyIdcType_combo					2
#define		CONST_qyIdcType_static					3
#define		CONST_qyIdcType_button					4
#define		CONST_qyIdcType_progress				5
#define		CONST_qyIdcType_ip						6
#define		CONST_qyIdcType_time					7
#define		CONST_qyIdcType_comboDesc				8		//  指项用于分类，且降序排列
#define		CONST_qyIdcType_chk						9		
#define		CONST_qyIdcType_listBox					10

extern  "C"  QY_DMITEM  CONST_qyIdcTypeTable[];



QY_IDCITEM  *	qyGetIdcItemByIdc(  QY_IDCITEM  *  pTable,  int  idc  );
QY_IDCITEM  *   qyGetIdcItemByName(  QY_IDCITEM  *  pTable,  TCHAR  *  name  );
int				qyShowHint(  LPCTSTR  fmt,  ...  );
int				qyDebugHint(  LPCTSTR  fmt,  ...  );
HRESULT			qyGetComCtlVersion(  LPDWORD  pdwMajor,  LPDWORD  pdwMinor  );

extern  QY_DMITEM  CONST_qyGrpTable[];

int  qyGetProcessGrps(  int  *  pFlg  );

#ifdef  __DEBUG__
  int  showIdcItem(  QY_IDCITEM  *  pIdcItem,  char  *  hint  );
#endif

#ifdef __cplusplus
 }
#endif

#endif /* } */


