
#include	"stdafx.h"

#include	<windows.h>
#include	<tchar.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommProc.h"
#include	"tmpCeLib.h"

 extern  "C"  TCHAR  *  qyGetDesByType(  QY_DMITEM  *  pTable,  long  type  )
{
	 int	i;

	 if  (  !pTable  )  return  NULL;			//  2005/02/08

	 for  (  i  =  0;  pTable[i].type  !=  -1;  i  ++  )  {
		  if  (  pTable[i].type  ==  type  )  return const_cast<TCHAR*>(pTable[i].des);		  
	 }
	 return  NULL; 
	 
}

 //  该函数专门为提供显示用，防止返回NULL导致指针错误
 extern  "C"  TCHAR  *  qyGetDesByType1(  QY_DMITEM  *  pTable,  long  type  )
{
	 TCHAR	*	p	=	NULL;
	 return  (TCHAR*)(  (  p  =  qyGetDesByType(  pTable,  type  )  )  ?  p  :  _T(  ""  )  );
} 

 extern  "C"  int  qyGetTypeByDes(  QY_DMITEM  *  pTable,  LPCTSTR  des  )
{
	 int	i;

	 if  (  !pTable  )  return  -1;			//  2005/02/08

	 for  (  i  =  0;  pTable[i].type  !=  -1;  i  ++  )  {
		  if  (  !lstrcmpi(  des,  pTable[i].des  )  )  return  pTable[i].type;
	 }
	 return  -1;
}

 //  pTable中输入的不仅可以是QY_DMITEM的指针，还可以是类QY_DMITEM的指针，大小在uiItemSize中指定
 //  当uiItemSize为0时，指输入的就是QY_DMITEM的指针, 2004/08/07
 extern  "C"  QY_DMITEM  *  qyGetDmItemByType(  QY_DMITEM  *  pTable,  long  type,  unsigned  int  uiItemSize  )
{
	 if  (  !pTable  )  return  NULL;

	 if  (  !uiItemSize  )  uiItemSize  =  sizeof(  QY_DMITEM  );

	 for  (  ;  pTable->type  !=  -1;  pTable  =  (  QY_DMITEM  *  )(  (  (  char  *  )pTable  )  +  uiItemSize  )  )  {
		  if  (  pTable->type  ==  type  )  return  pTable;		  
	 }
	 return  NULL; 
	 
}

 //  pTable中输入的不仅可以是QY_DMITEM的指针，还可以是类QY_DMITEM的指针，大小在uiItemSize中指定
 //  当uiItemSize为0时，指输入的就是QY_DMITEM的指针, 2004/08/07
 extern  "C"  QY_DMITEM  *  qyGetDmItemByDes(  QY_DMITEM  *  pTable,  LPCTSTR  des,  unsigned  int  uiItemSize  )
{	 
	 if  (  !pTable  ||  !des  )  return  NULL;

	 if  (  !uiItemSize  )  uiItemSize  =  sizeof(  QY_DMITEM  );

	 for  (  ;  pTable->type  !=  -1  &&  pTable->des;  pTable  =  (  QY_DMITEM  *  )(  (  (  char  *  )pTable  )  +  uiItemSize  )  )  {
		  if  (  !lstrcmpi(  des,  pTable->des  )  )  return  pTable;
	 }
	 return  NULL; 
}


 extern  "C"  int  getnItems(  QY_DMITEM  *  pTable  )
{
	int		i	=	0;
	for  (  ;  pTable->type  !=  -1;  pTable  ++  )  i  ++  ;
	return  i;
}



 extern  "C"  QY_IDCITEM  *  qyGetIdcItemByIdc(  QY_IDCITEM  *  pTable,  int  idc  )
{
	 if  (  !pTable  )  return  NULL;	//  2005/02/08

	 for  (  ;  pTable->idc  !=  -1;  pTable  ++  )  {
		  if  (  pTable->idc  ==  idc  )  return  pTable;
	 }
	 return  NULL;
}

 extern  "C"  QY_IDCITEM  *  qyGetIdcItemByName(  QY_IDCITEM  *  pTable,  TCHAR  *  name  )
{
	 if  (  !pTable  )  return  NULL;	//  2005/02/08

	 for  (  ;  pTable->idc  !=  -1;  pTable  ++  )  {
		  if  (  !lstrcmpi(  name,  pTable->name  )  )  return  pTable;
	 }
	 return  NULL;
}

