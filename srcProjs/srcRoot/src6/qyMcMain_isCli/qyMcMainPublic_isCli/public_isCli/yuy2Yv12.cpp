
#include	"stdafx.h"
#include	<tchar.h>
//#include	"qyMcMainCommon.h"

#include	"colorSpaceFunc.h"




 int  yuy2ToYv12(  char  *  inBuff,  char  *  outBuff,  int  width,  int  height  )
{
#ifdef  __SUPPORT_qyMc_ipp__
		QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
		
		if  (  pQyMc->cusModules.pIpp  
			&&  pQyMc->cusModules.pIpp->compress.mgr.pf_yuy2ToYv12  )
		{
			//  2011/12/10
			return  pQyMc->cusModules.pIpp->compress.mgr.pf_yuy2ToYv12(  inBuff,  outBuff,  width,  height  );									
		}
#endif

	int  i = 0, j= 0, k = 0;
	int  VOffset  =  width  *  height;
	int  UOffset  =  (  width  *  height  )  *  5  /  4;
	int  UVSize  =  (  width  *  height  )  /  4;
	int  line1  =  0,  line2  =  0;
	int  m  =  0,  n  =  0;
	int  y  =  0,  u  =  0,  v  =  0;

	u  =  UOffset;
	v  =  VOffset;

	for  (  i  =  0,  j  =  1;  i  <  height;  i += 2, j += 2  ){
		 /*  Input Buffer Pointer Indexes  */
		 line1  =  i  *  width  *  2;
		 line2  =  j  *  width  *  2;

		 /*  Output Buffer Pointer Indexes  */
		 m  =  width  *  y;
		 y  =  y  +  1;
		 n  =  width  *  y;
		 y  =  y  +  1;

		 /*  Scan  2 lines at a time  */
		 for  (  k  =  0;  k  <  width  *  2;  k +=  4  ){
			  unsigned  char  Y1,  Y2,  U,  V;
			  unsigned  char  Y3,  Y4,  U2,  V2;

			  /*  Read Input Buffer*/
			  Y1  =  inBuff[line1  ++  ];
			  U  =  inBuff[line1  ++  ];
			  Y2  =  inBuff[line1  ++  ];
			  V  =  inBuff[line1  ++  ];

			  Y3  =  inBuff[line2  ++  ];
			  U2  =  inBuff[line2  ++  ];
			  Y4  =  inBuff[line2  ++  ];
			  V2  =  inBuff[line2  ++  ];

			  /*  Write  Output Buffer  */
			  outBuff[m  ++]  =  Y1;
			  outBuff[m  ++]  =  Y2;

			  outBuff[n  ++]  =  Y3;
			  outBuff[n  ++]  =  Y4;

			  outBuff[u ++]  =  (  U  +  U2  )  /  2;
			  outBuff[v ++]  =  (  V  +  V2  )  /  2;
		 }
	}
 	return  0;
}


