
#include	"stdafx.h"
#include	<stddef.h>
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"ctxQmc.h"



BOOL  b_tttbbbMac(  QY_MC  *  pQyMc  )
{
	BOOL  bTttbbbMac  =  FALSE;

	QY_MC  *  pQM  =  pQyMc;
	if  (  !pQM  )  return  FALSE;
			 
	QY_DMITEM  CONST_tttbbbMacsTable[]  =	
	{
			 {	0,	(  TCHAR  *  )"64006a6a932a",	},			//  r&a
			 {	0,	(  TCHAR  *  )"989096c85a3c",	},			//  tj-dell-t1700
			 {	0,	(  TCHAR  *  )"1866da0c26f4",	},			//  tj-dell-t3620
			 {	0,	(  TCHAR  *  )"64006a6a8ef7",	},			//  bj-dell-t1700
			 {	0,	(  TCHAR  *  )"8CDCD429B073",	},			//  bj-hp-z230
			 {	0,	(  TCHAR  *  )"18037332E6F1",	},			//  bj-dell-t1700
			 {	0,	(  TCHAR  *  )"2C4138602466",	},			//  bj-6B11
			 {	0,	(  TCHAR  *  )"A0B3CC456248",	},			//  bj-dv6-7045
			 {	0,	(  TCHAR  *  )"64006A453555",	},			//  hn-laoyuan
			 {	0,	(  TCHAR  *  )"94DE80328D21",	},			//  hn-ziyouren
			 {	0,	(  TCHAR  *  )"902B3452ADF5",	},			//  hn-qinghui

			 {	-1,	},		 
	};

		 
	//	
	QWM_MACS_INFO  macsInfo;		
	getQwmMacs(  &pQM->env,  &macsInfo  );
		 
		 
	//	
	int  i;
	QY_DMITEM  *  pItem;		
	for  (  pItem  =  CONST_tttbbbMacsTable;  pItem->type  !=  -1;  pItem  ++  )  {
			  if  (  bTttbbbMac  )  break;
			  for  (  i  =  0;  i  <  macsInfo.nMacs;  i  ++  )  {			  
				   if  (  !macsInfo.macs[i][0]  )  continue;
				   if  (  !_stricmp(  (  char  *  )macsInfo.macs[i],  (  char  *  )pItem->des  )  )  {
					   bTttbbbMac  =  TRUE;
					   break;
				   }
			  }
		 
	}


	return  bTttbbbMac;
}


//




