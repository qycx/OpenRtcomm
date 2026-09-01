
#include	"stdafx.h"
#include	<math.h>
#include	<stddef.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"tmpCeLib.h"
#include	"qmcVideoCapture.h"
#include	"qyOpenShellCommon.h"
#include <qmcVideoCapture_isCli.h>


//  dar  =  m  /  n
 int  tmp_getDar(  int  iW_org,  int  iH_org,  int  iW,  int  iH,  int  &m_o,  int  &n_o  )
 {
	 int	maxI  =  iW_org  /  16;
	 //
	 int  iW_real;
	 int  iH_real;
	 int  m,  n;
	 //
	 int  iW_real1  =  0;
	 int  m1  =  0,  n1  =  0;
	 //

	 int  k,  kk;

	 if  (  maxI  <=  0  )  return  -1;

	 for  (  n  =  1;  n  <=  maxI;  n  ++  )  {
#if  10
		  if  (  n  !=  1  )  {
			  //  要求都是2的n次方
			  int  t;
			  for  (  t  =  n;  ;  )  {
				   if  (  t  %  2  )  break;
				   t  =  t  /  2;
			  }
			  if  (  t  !=  1  )  continue;			  
		  }
#endif
		  if  (  iW_org  %  n
			  ||  iH_org  %  n  )  
		  {
			  continue;
		  }
		  
		  //
		  k  =  iW  /  (  iW_org  /  n  );
		  if  (  (  k  *  iW_org  /  n  )  %  2
			  ||  (  k  *  iH_org  /  n  )  %  2  )  
		  {
			  k  =  k  /  2  *  2;
		  }
		  kk  =  iH  /  (  iH_org  /  n  );
		  if  (  (  kk  *  iH_org  /  n  )  %  2 
			  ||  (  kk  *  iW_org  /  n  )  %  2  )  
		  {
			  kk  =  kk  /  2  *  2;
		  }
		  //
		  m  =  min(  k,  kk  );
		  if  (  !m  )  continue;

		  iW_real  =  iW_org  /  n  *  m;
		  iH_real  =  iH_org  /  n  *  m;

		  //
		  if  (  iW_real  >  iW_real1  )  {
			  iW_real1  =  iW_real;
			  m1  =  m;
			  n1  =  n;
		  }
		  continue;
	 }

	 if  (  !m1  ||  !n1  )  return  -1;

	 m_o  =  m1;
	 n_o  =  n1;
	 return  0;
 }

 //  dar  =  m  /  n
 int  tmp_getDar_autoClip(  int  iW_org,  int  iH_org,  int  iW,  int  iH,  int  &m_o,  int  &n_o  )
 {
	 //  int	maxI  =  iW_org  /  16;
	 int	maxI  =  iW_org  /  64;
	 //
	 int  iW_real;
	 int  iH_real;
	 int  m,  n;
	 //
	 int  iW_real1  =  0;
	 int  m1  =  0,  n1  =  0;
	 //

	 //
#if  0
	 int  iH_org_bak  =  iH_org;
	 iH_org  =  iH_org  /  16;
	 if  (  iH_org  *  16  <  iH_org_bak  )  iH_org  ++  ;
	 iH_org  *=  16;
#endif

	 //
	 int  k,  kk;

	 if  (  maxI  <=  0  )  return  -1;

	 for  (  n  =  1;  n  <=  maxI;  n  ++  )  {
#if  10
		  if  (  n  !=  1  )  {
			  //  要求都是2的n次方
			  int  t;
			  for  (  t  =  n;  ;  )  {
				   if  (  t  %  2  )  break;
				   t  =  t  /  2;
			  }
			  if  (  t  !=  1  )  continue;			  
		  }
#endif
		  if  (  iW_org  %  n
			  ||  iH_org  %  n  )  
		  {
			  continue;
		  }
		  
		  //
		  k  =  iW  /  (  iW_org  /  n  );
		  if  (  k  *  iW_org  /  n  <  iW  )  k  ++  ;
		  if  (  (  k  *  iW_org  /  n  )  %  2
			  ||  (  k  *  iH_org  /  n  )  %  2  )  
		  {
			  k  =  (  k  +  1  )  /  2  *  2;
		  }
		  kk  =  iH  /  (  iH_org  /  n  );
		  if  (  kk  *  iH_org  /  n  <  iH  )  kk  ++  ;
		  if  (  (  kk  *  iH_org  /  n  )  %  2 
			  ||  (  kk  *  iW_org  /  n  )  %  2  )  
		  {
			  kk  =  (  kk  +  1  )  /  2  *  2;
		  }
		  //
		  m  =  max(  k,  kk  );
		  if  (  !m  )  continue;

		  iW_real  =  iW_org  /  n  *  m;
		  iH_real  =  iH_org  /  n  *  m;

		  //
		  if  (  !iW_real1  
			  ||  iW_real  <  iW_real1  )  
		  {
			  iW_real1  =  iW_real;
			  m1  =  m;
			  n1  =  n;
		  }
		  continue;
	 }

	 if  (  !m1  ||  !n1  )  return  -1;

	 m_o  =  m1;
	 n_o  =  n1;
	 return  0;
 }





 //  2014/04/06
  __declspec(  dllexport  )  int  myGetImageInfo(	unsigned  char  ucbFixedSize,			//  
					    unsigned  char	ucbAutoClip,											//  根据目标矩形自动裁剪，使目标矩形被充满
						unsigned  char  ucb3d,													//  3d显示用， 2014/11/14
						int  iW_org,  int  iH_org,  
						int  iX,  int  iY,  unsigned  int  iW,  unsigned  int  iH,  
						unsigned  int  *  piW_i,  unsigned  int  *  piH_i,
						int  *  piX_src_i,  int  *  piY_src_i,  
						int  *  piX_dst,  int  *  piY_dst,  unsigned  int  *  piW_dst,  unsigned  int  *  piH_dst  )
{
	TCHAR  tBuf[256];

	if  (  !piX_dst  ||  !piY_dst  ||  !piW_dst  ||  !piH_dst  )  return  -1;
	if  (  !iW_org  ||  !iH_org  )  return  -1;
	if  (  !iW  ||  !iH  )  {
		*piW_i  =  *piH_i  =  0;
		*piX_src_i  =  *piY_src_i  =  0;
		*piX_dst  =  *piY_dst  =  *piW_dst  =  *piH_dst  =  0;
		return  0;
	}

	if  (  ucbFixedSize  )  {					//  2??ü·?′ó??D?
		//
		*piW_i  =  iW_org;
		*piH_i  =  iH_org;
		//
		if  (  iW_org  >  (  int  )iW  )  *piX_dst  =  0;  
		else  *piX_dst  =  iX  +  (  iW  -  iW_org  )  /  2;
		
		if  (  iH_org  >  (  int  )iH  )  *piY_dst  =  0;  
		else  *  piY_dst  =  iY  +  (  iH  -  iH_org  )  /  2;
		//
		*piX_src_i  =  *piY_src_i  =  0;		
		//
		*piW_dst  =  iW_org;
		*piH_dst  =  iH_org;

		return  0;
	}

	BOOL	b16X9	=	FALSE;
	if  (  !ucb3d  )  {			//  3d不需要整数比例就可以缩放自如。2014/11/14
		if  (  iH_org  *  16  ==  iW_org  *  9  )  b16X9  =  TRUE;
	}

	if  (  10  &&  ucbAutoClip  )  {

		//  2014/04/11
		if  (  b16X9  )  {
			int  m,  n;
			int	nUnit  =  8;

			if  (  !tmp_getDar_autoClip(  iW_org,  iH_org,  iW,  iH,  m,  n  )  )  {
				//					
				int  iW_i,  iH_i;
				iW_i  =  iW_org  /  n  *  m;
				iH_i  =  iH_org  /  n  *  m;
				//
				*piW_i  =  iW_i;
				*piH_i  =  iH_i;
				//
				*piW_dst  =  iW  /  nUnit  *  nUnit;
				*piH_dst  =  iH  /  nUnit  *  nUnit;
				*piX_dst  =  iX  +  (  iW  -  *piW_dst  )  /  2;
				*piY_dst  =  iY  +  (  iH  -  *piH_dst  )  /  2;
				//
				*piX_src_i  =  (  iW_i  -  *piW_dst  )  /  2;
				*piY_src_i  =  (  iH_i  -  *piH_dst  )  /  2;
				//
				#ifdef  __DEBUG__
						#if  0
							traceLog(  _T(  "myGetImageInfo: %d X %d, zone %d X %d, m/n %d/%d"  ),  *piW_image,  *piH_image,  iW,  iH,  m,  n  );
						#endif
				#endif
				//
				#if  0
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "org:%dX%d, zone:(%d,%d)%dX%d. i:%dX%d, src_i:(%d,%d), dst:(%d,%d)%dX%d"  ),  iW_org,  iH_org,  iX,  iY,  iW,  iH,  *piW_i,  *piH_i,  *piX_src_i,  *piY_src_i,  *piX_dst,  *piY_dst,  *piW_dst,  *piH_dst  );
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
				#endif
				//
				return  0;		
			}
		}
		
		//
		double	ff;
		int		n;
		int		nUnit  =  8;	//  16;

		//
		*piW_dst  =  iW;
		*piH_dst  =  iH;
		//		
		if  (  iW  >=  *piW_dst  )  *piX_dst  =  iX  +  (  iW  -  *piW_dst  )  /  2;
		else  *piX_dst  =  iX;
		if  (  iH  >=  *piH_dst  )  *piY_dst  =  iY  +  (  iH  -  *piH_dst  )  /  2;
		else  *piY_dst  =  iY;

		//
		if  (  !*piH_dst  )  return  -1;
		
		//
		ff  =  *piW_dst  /  (  *piH_dst  *  1.  );
		if  (  iW_org  /  (  iH_org  *  1.  )  >  ff  )  {
			//
			*piH_i  =  *piH_dst;
			*piW_i  =  *piH_i  *  iW_org  /  (  1.0  *  iH_org  );
			
			//
			*piX_src_i  =  (  *piW_i  -  *piW_dst  )  /  2;
			*piY_src_i  =  0;

#if  0
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "src:(%d,%d)%dX%d, dst:(%d,%d)%dX%d, org:%dX%d, zone:(%d,%d)%dX%d"  ),  *piX_src,  *piY_src,  *piW_src,  *piH_src,  *piX_dst,  *piY_dst,  *piW_dst,  *piH_dst,  iW_org,  iH_org,  iX,  iY,  iW,  iH  );
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
#endif
			//
			return  0;
		}
		//
		*piW_i  =  *piW_dst;
		*piH_i  =  *piW_i  *  iH_org  /  (  1.0  *  iW_org  );
		//
		*piX_src_i  =  0;
		*piY_src_i  =  (  *piH_i  -  *piH_dst  )  /  2;

		//
#if  0
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "src:(%d,%d)%dX%d, dst:(%d,%d)%dX%d, org:%dX%d, zone:(%d,%d)%dX%d"  ),  *piX_src,  *piY_src,  *piW_src,  *piH_src,  *piX_dst,  *piY_dst,  *piW_dst,  *piH_dst,  iW_org,  iH_org,  iX,  iY,  iW,  iH  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
#endif
		//
		return  0;
	}

	double	f;


#if  10

	if  (  b16X9  )  {
		int  m,  n;

		if  (false /*!tmp_getDar(  iW_org,  iH_org,  iW,  iH,  m,  n  )*/)  {
			//
			*piX_src_i  =  *piY_src_i  =  0;
			*piW_i  =  iW_org  /  n  *  m;
			*piH_i  =  iH_org  /  n  *  m;
			//
			*piW_dst  =  iW_org  /  n  *  m;
			*piH_dst  =  iH_org  /  n  *  m;
			*piX_dst  =  iX  +  (  iW  -  *piW_dst  )  /  2;
			*piY_dst  =  iY  +  (  iH  -  *piH_dst  )  /  2;
			//
			#ifdef  __DEBUG__
					#if  0
						traceLog(  _T(  "myGetImageInfo: %d X %d, zone %d X %d, m/n %d/%d"  ),  *piW_image,  *piH_image,  iW,  iH,  m,  n  );
					#endif
			#endif
			//
			#if  0
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "org:%dX%d, zone:(%d,%d)%dX%d. i:%dX%d, src_i:(%d,%d), dst:(%d,%d)%dX%d"  ),  
						iW_org,  iH_org,  iX,  iY,  iW,  iH,  *piW_i,  *piH_i,  *piX_src_i,  *piY_src_i,  *piX_dst,  *piY_dst,  *piW_dst,  *piH_dst  );
					//qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
					traceLog(tBuf);
			#endif
			//
			return  0;
		}
		//  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tmp_getDar failed"  )  );
	}
#endif


	//
	f  =  iW_org  /  (  iH_org  *  1.  );
	if  (  f  *  iH  >  iW  )  {				//  ì??-
#if  0
		int  tmp_iH  =  iW  /  f;
		//
		if  (  !ucb3d  )  {  //  2016/01/23
			tmp_iH  =  tmp_iH  /  4  *  4;
		}
		//
		*piX_src_i  =  *piY_src_i  =  0;		
		*piH_i  =  tmp_iH;			//  iW  /  f;
		*piW_i  =  tmp_iH  *  f;	//  iW;
#endif
		int  tmp_iW  =  iW;
		if  (  !ucb3d  )  {
			tmp_iW  =  tmp_iW  /  4  *  4;
		}
		//
		*piX_src_i  =  *piY_src_i  =  0;		
		*piW_i  =  tmp_iW;
		*piH_i  =  tmp_iW  /  f;			//  iW  /  f;
		//
		*piW_dst  =  *piW_i;	//  iW;
		*piH_dst  =  *piH_i;	//  (  int  )(  iW  /  f  );
		*piX_dst  =  iX;
		*piY_dst  =  (  int  )(  iY  +  (  iH  -  *piH_dst  )  /  2.  );
#if  0
		_sntprintf(tBuf, mycountof(tBuf), _T("org2:%dX%d, zone:(%d,%d)%dX%d. i:%dX%d, src_i:(%d,%d), dst:(%d,%d)%dX%d"), 
			iW_org, iH_org, iX, iY, iW, iH, *piW_i, *piH_i, *piX_src_i, *piY_src_i, *piX_dst, *piY_dst, *piW_dst, *piH_dst);
		//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), _T("IsClient"), 0, _T(""), _T(""), _T("%s"), tBuf);
		traceLog(tBuf);
#endif
		return  0;
	}

	//
	*piX_src_i  =  *piY_src_i  =  0;				
	*piH_i  =  iH;
	*piW_i  =  iH  *  f;
	//  ì??í
	*piH_dst  =  iH;
	*piW_dst  =  (  int  )(  iH  *  f  );
	*piY_dst  =  iY;
	*piX_dst  =  (  int  )(  iX  +  (  iW  -  *piW_dst  )  /  2.  );

	return  0;
}



//  2014/11/14
  __declspec(  dllexport  )  int  myGetImageInfo_2d(	unsigned  char  ucbFixedSize,			//  
					    unsigned  char	ucbAutoClip,											//  根据目标矩形自动裁剪，使目标矩形被充满
						int  iW_org,  int  iH_org,  
						int  iX,  int  iY,  unsigned  int  iW,  unsigned  int  iH,  
						unsigned  int  *  piW_i,  unsigned  int  *  piH_i,
						int  *  piX_src_i,  int  *  piY_src_i,  
						int  *  piX_dst,  int  *  piY_dst,  unsigned  int  *  piW_dst,  unsigned  int  *  piH_dst  )
  {
	  unsigned  char  ucb3d  =  FALSE;

	  //
	  return  myGetImageInfo(  ucbFixedSize,						//  
					    ucbAutoClip,									//  根据目标矩形自动裁剪，使目标矩形被充满
						ucb3d,											//  2014/11/14
						iW_org,  iH_org,  
						iX,  iY,  iW,  iH,  
						piW_i,  piH_i,
						piX_src_i,  piY_src_i,  
						piX_dst,  piY_dst,  piW_dst,  piH_dst  );

  }

//  2014/04/06
__declspec(  dllexport  )  int  getCapImagesFunc(  unsigned  char  ucbAutoClip,  unsigned  char  ucb3d,  int  iX_desc,  int  iY_desc,  int  iW_desc,  int  iH_desc,  PARAM_getCapImages  *  pParam,  CAP_images_head  *  pImgsHead,  CAP_IMAGE  *  pImgMems,  int  uiSize_pImgMem,  unsigned  int  uiMaxCnt_imgMems  )
{
	 int					iErr	=	-1;
	 int					i;
	 CAP_IMAGE			*	pImg;
	 int					cnt;
	 int					iRows;
	 int  iX,  iY,  iW,  iH;
	 //	
	 unsigned  int  iW_i,  iH_i;
	 int  iX_src_i,  iY_src_i;
	 int  iX_dst,  iY_dst;					
	 unsigned  int  iW_dst,  iH_dst;
	 
	 //
	 if  (  !pParam  )  return  -1;

	 //
	 cnt  =  0;
	 for  (  i  =  0;  i  <  uiMaxCnt_imgMems;  i  ++  )  {
		  pImg  =  (  CAP_IMAGE  *  )(  (  (  char  *  )pImgMems  )  +  i  *  uiSize_pImgMem  );	//  &pImages->mems[i];
		  if  (  pImg->iW_org  &&  pImg->iH_org  
			  &&  pImg->iTaskId  )  
		  {
			  cnt  ++  ;
		  }
	 }
	 pImgsHead->usCnt  =  (  unsigned  short  )cnt;


	 //  2013/08/18
	 if  (  cnt  ==  2  )  {
		 iRows  =  1;

		 int					index  =  0;	 

		 for  (  i  =  0,index = 0;  i  <  uiMaxCnt_imgMems  &&  index  <  cnt;  i  ++  )  {
				pImg =  (  CAP_IMAGE  *  )(  (  (  char  *  )pImgMems  )  +  i  *  uiSize_pImgMem  );	//&pImages->mems[i];
				if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;

				iW  =  iW_desc  /  2.0;
				iH  =  iH_desc;
				iX  =  iX_desc  +  index  *  iW;
				iY  =  iY_desc;
				
				//
				myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  pImg->iW_org,  pImg->iH_org,  iX,  iY,  iW,  iH,
									&iW_i,  &iH_i,  &iX_src_i,  &iY_src_i, 
									  &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );
								
				if  (  pImg->iW_i  !=  iW_i
					||  pImg->iH_i  !=  iH_i
					||  pImg->iX_src_i  !=  iX_src_i
					||  pImg->iY_src_i  !=  iY_src_i
					||  pImg->iX_dst  !=  iX_dst				
					||  pImg->iY_dst  !=  iY_dst
					||  pImg->iW_dst  !=  iW_dst
					||  pImg->iH_dst  !=  iH_dst
					)				
				{
						  pImg->bResized  =  TRUE;
						  
						  //
						  pImg->iW_i  =  iW_i;
						  pImg->iH_i  =  iH_i;
						  pImg->iX_src_i  =  iX_src_i;
						  pImg->iY_src_i  =  iY_src_i;
						  //
						  pImg->iX_dst  =  iX_dst;				  
						  pImg->iY_dst  =  iY_dst;
						  pImg->iW_dst  =  iW_dst;
						  pImg->iH_dst  =  iH_dst;					  
				}
				//  traceLog(  _T(  "case is  2, index is %d,  pImg  iX  %d, iY %d, iW %d,iH %d"  ),  cnt,  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iH  );
				
				//
				index  ++  ;
		 }

		 //
		 iErr  =  0;  goto  errLabel;
	 }
	 if  (  cnt  ==  3  )  {
		 iRows  =  2;
		 int  index  =  0,  iRow  =  0,  iCol  =  0;  
		 //int  iX,  iY,  iW,  iH;
		 
		 for  (  i  =  0,index = 0;  i  <  uiMaxCnt_imgMems  &&  index  <  cnt;  i  ++  )  {
				pImg =  (  CAP_IMAGE  *  )(  (  (  char  *  )pImgMems  )  +  i  *  uiSize_pImgMem  );	//  &pImages->mems[i];
				if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;
#if 0  //  2014/04/25
				switch  (  index  )  {
						case  0:
							   iW  =  iW_desc  /  2.0;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc  +  iW_desc  /  4.0;
							   iY  =  iY_desc;
							   break;
						case  1:
							   iW  =  iW_desc  /  2.0;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc;
							   iY  =  iY_desc  +  iH_desc  /  2.0;
							   break;
						case  2:
							   iW  =  iW_desc  /  2.0;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc  +  iW_desc  /  2.0;
							   iY  =  iY_desc  +  iH_desc  /  2.0;
							   break;
						default:
								goto  errLabel;
				}
#else
				int  iW_left  =  iW_desc  *  0.5;
				switch  (  index  )  {
						case  0:
							   iW  =  iW_left;
							   iH  =  iH_desc;
							   iX  =  iX_desc;
							   iY  =  iY_desc;
							   break;
						case  1:
							   iW  =  iW_desc  -  iW_left;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc  +  iW_left;
							   iY  =  iY_desc;
							   break;
						case  2:
							   iW  =  iW_desc  -  iW_left;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc  +  iW_left;
							   iY  =  iY_desc  +  iH_desc  /  2.0;
							   break;
						default:
								goto  errLabel;
				}

#endif
#if  0
				//				
				int  iX_dst,  iY_dst;					
				unsigned  int  iW_dst,  iH_dst;
#endif
				
				myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  pImg->iW_org,  pImg->iH_org,  iX,  iY,  iW,  iH,  
									&iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,									  
									  &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );				

				if  (  pImg->iW_i  !=  iW_i
					||  pImg->iH_i  !=  iH_i
					||  pImg->iX_src_i  !=  iX_src_i
					||  pImg->iY_src_i  !=  iY_src_i
					||  pImg->iX_dst  !=  iX_dst				
					||  pImg->iY_dst  !=  iY_dst
					||  pImg->iW_dst  !=  iW_dst
					||  pImg->iH_dst  !=  iH_dst
					)				
				{
						  pImg->bResized  =  TRUE;
						  
						  //
						  pImg->iW_i  =  iW_i;
						  pImg->iH_i  =  iH_i;
						  pImg->iX_src_i  =  iX_src_i;
						  pImg->iY_src_i  =  iY_src_i;
						  //
						  pImg->iX_dst  =  iX_dst;				  
						  pImg->iY_dst  =  iY_dst;
						  pImg->iW_dst  =  iW_dst;
						  pImg->iH_dst  =  iH_dst;					  
				}

				//  traceLog(  _T(  "case is  3, index is %d,  pImg  iX  %d, iY %d, iW %d,iH %d"  ),  index,  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iH  );
				
				index  ++  ;
		 }

		 iErr  =  0;  goto  errLabel;
	 }

#if  0   //  1竖 + 4平分
	 if  (  cnt  ==  5  )  {
		 iRows  =  2;
		 int  index  =  0,  iRow  =  0,  iCol  =  0;  
		 //int  iX,  iY,  iW,  iH;
		 
		 for  (  i  =  0,index = 0;  i  <  uiMaxCnt_imgMems,  index  <  cnt;  i  ++  )  {
				pImg =  (  CAP_IMAGE  *  )(  (  (  char  *  )pImgMems  )  +  i  *  uiSize_pImgMem  );	//  &pImages->mems[i];
				if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;

				int  iW_left  =  iW_desc  *  0.33;
				switch  (  index  )  {
						case  0:
							   iW  =  iW_left;
							   iH  =  iH_desc;
							   iX  =  iX_desc;
							   iY  =  iY_desc;
							   break;
						case  1:
							   iW  =  (  iW_desc  -  iW_left  )  / 2.;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc  +  iW_left;
							   iY  =  iY_desc;
							   break;
						case  2:
							   iW  =  (  iW_desc  -  iW_left  )  / 2.;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc  +  iW_left  +  iW;
							   iY  =  iY_desc;
							   break;
						case  3:
							   iW  =  (  iW_desc  -  iW_left  )  /  2.;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc  +  iW_left;
							   iY  =  iY_desc  +  iH_desc  /  2.0;
							   break;
						case  4:
							   iW  =  (  iW_desc  -  iW_left  )  /  2.;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc  +  iW_left  +  iW;
							   iY  =  iY_desc  +  iH_desc  /  2.0;
							   break;
						default:
								goto  errLabel;
				}
				
				myGetImageInfo_2d(  0,  ucbAutoClip,  pImg->iW_org,  pImg->iH_org,  iX,  iY,  iW,  iH,  
									&iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,									  
									  &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );				

				if  (  pImg->iW_i  !=  iW_i
					||  pImg->iH_i  !=  iH_i
					||  pImg->iX_src_i  !=  iX_src_i
					||  pImg->iY_src_i  !=  iY_src_i
					||  pImg->iX_dst  !=  iX_dst				
					||  pImg->iY_dst  !=  iY_dst
					||  pImg->iW_dst  !=  iW_dst
					||  pImg->iH_dst  !=  iH_dst
					)				
				{
						  pImg->bResized  =  TRUE;
						  
						  //
						  pImg->iW_i  =  iW_i;
						  pImg->iH_i  =  iH_i;
						  pImg->iX_src_i  =  iX_src_i;
						  pImg->iY_src_i  =  iY_src_i;
						  //
						  pImg->iX_dst  =  iX_dst;				  
						  pImg->iY_dst  =  iY_dst;
						  pImg->iW_dst  =  iW_dst;
						  pImg->iH_dst  =  iH_dst;					  
				}

				//  traceLog(  _T(  "case is  3, index is %d,  pImg  iX  %d, iY %d, iW %d,iH %d"  ),  index,  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iH  );
				
				index  ++  ;
		 }

		 iErr  =  0;  goto  errLabel;
	 }
#else
	 	 //  2015/06/20,上二下三的对称方案 替代了左二右三的方案
	 if  (  cnt  ==  5  )  {
		 iRows  =  2;
		 int  index  =  0,  iRow  =  0,  iCol  =  0;  
		 
		 for  (  i  =  0,index = 0;  i  <  uiMaxCnt_imgMems  &&  index  <  cnt;  i  ++  )  {
				pImg =  (  CAP_IMAGE  *  )(  (  (  char  *  )pImgMems  )  +  i  *  uiSize_pImgMem  );	//  &pImages->mems[i];
				if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;

				int  iW_half  =  iW_desc  *  0.5;
				int  iH_half  =  iH_desc  *  0.5;
				int  iW_average  =  iW_desc  *  0.33;
				//int  iH_average  =  iH_desc  *  0.33;
					 
				switch  (  index  )  {
						case  0:
							   iW  =  iW_half;
							   iH  =  iH_half;
							   iX  =  iX_desc;
							   iY  =  iY_desc;
							   break;
						case  1:
							   iW  =  iW_half;
							   iH  =  iH_half;
							   iX  =  iX_desc + iW_half;
							   iY  =  iY_desc;
							   break;
						case  2:
							   iW  =  iW_average;
							   iH  =  iH_half;
							   iX  =  iX_desc;
							   iY  =  iY_desc + iH_half;
							   break;
						case  3:
							   iW  =  iW_average;
							   iH  =  iH_half;
							   iX  =  iX_desc + iW_average;
							   iY  =  iY_desc + iH_half;
							   break;
						case  4:
							   iW  =  iW_average;
							   iH  =  iH_half;
							   iX  =  iX_desc + iW_average * 2;
							   iY  =  iY_desc + iH_half;
							   break;

						default:
								goto  errLabel;
				}
				
				myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  pImg->iW_org,  pImg->iH_org,  iX,  iY,  iW,  iH,  
									&iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,									  
									  &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );				

				if  (  pImg->iW_i  !=  iW_i
					||  pImg->iH_i  !=  iH_i
					||  pImg->iX_src_i  !=  iX_src_i
					||  pImg->iY_src_i  !=  iY_src_i
					||  pImg->iX_dst  !=  iX_dst				
					||  pImg->iY_dst  !=  iY_dst
					||  pImg->iW_dst  !=  iW_dst
					||  pImg->iH_dst  !=  iH_dst
					)				
				{
						  pImg->bResized  =  TRUE;
						  
						  //
						  pImg->iW_i  =  iW_i;
						  pImg->iH_i  =  iH_i;
						  pImg->iX_src_i  =  iX_src_i;
						  pImg->iY_src_i  =  iY_src_i;
						  //
						  pImg->iX_dst  =  iX_dst;				  
						  pImg->iY_dst  =  iY_dst;
						  pImg->iW_dst  =  iW_dst;
						  pImg->iH_dst  =  iH_dst;					  
				}

				//  traceLog(  _T(  "case is  3, index is %d,  pImg  iX  %d, iY %d, iW %d,iH %d"  ),  index,  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iH  );
				
				index  ++  ;
		 }

		 iErr  =  0;  goto  errLabel;
	 }

#endif


	 //  2015/06/20
	 if  (  cnt  ==  6  )  {
		 iRows  =  2;
		 int  index  =  0,  iRow  =  0,  iCol  =  0;  
		 
		 for  (  i  =  0,index = 0;  i  <  uiMaxCnt_imgMems  &&  index  <  cnt;  i  ++  )  {
				pImg =  (  CAP_IMAGE  *  )(  (  (  char  *  )pImgMems  )  +  i  *  uiSize_pImgMem  );	//  &pImages->mems[i];
				if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;

				int  iW_average  =  iW_desc  *  0.33;
				int  iH_half  =  iH_desc  /  2.0;
					 
				switch  (  index  )  {
						case  0:
							   iW  =  iW_average;
							   iH  =  iH_half;
							   iX  =  iX_desc;
							   iY  =  iY_desc;
							   break;
						case  1:
							   iW  =  iW_average;
							   iH  =  iH_half;
							   iX  =  iX_desc + iW_average;
							   iY  =  iY_desc;
							   break;
						case  2:
							   iW  =  iW_average;
							   iH  =  iH_half;
							   iX  =  iX_desc  +  iW_average * 2.0;
							   iY  =  iY_desc;
							   break;
						case  3:
							   iW  =  iW_average;
							   iH  =  iH_half;
							   iX  =  iX_desc;
							   iY  =  iY_desc  +  iH_half;
							   break;
						case  4:
							   iW  =  iW_average;
							   iH  =  iH_half;
							   iX  =  iX_desc + iW_average;
							   iY  =  iY_desc + iH_half;
							   break;
						case  5:
							   iW  =  iW_average;
							   iH  =  iH_half;
							   iX  =  iX_desc + iW_average  *  2.0;
							   iY  =  iY_desc + iH_half;
							   break;

						default:
								goto  errLabel;
				}
				
				myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  pImg->iW_org,  pImg->iH_org,  iX,  iY,  iW,  iH,  
									&iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,									  
									  &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );				

				if  (  pImg->iW_i  !=  iW_i
					||  pImg->iH_i  !=  iH_i
					||  pImg->iX_src_i  !=  iX_src_i
					||  pImg->iY_src_i  !=  iY_src_i
					||  pImg->iX_dst  !=  iX_dst				
					||  pImg->iY_dst  !=  iY_dst
					||  pImg->iW_dst  !=  iW_dst
					||  pImg->iH_dst  !=  iH_dst
					)				
				{
						  pImg->bResized  =  TRUE;
						  
						  //
						  pImg->iW_i  =  iW_i;
						  pImg->iH_i  =  iH_i;
						  pImg->iX_src_i  =  iX_src_i;
						  pImg->iY_src_i  =  iY_src_i;
						  //
						  pImg->iX_dst  =  iX_dst;				  
						  pImg->iY_dst  =  iY_dst;
						  pImg->iW_dst  =  iW_dst;
						  pImg->iH_dst  =  iH_dst;					  
				}

				//  traceLog(  _T(  "case is  3, index is %d,  pImg  iX  %d, iY %d, iW %d,iH %d"  ),  index,  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iH  );
				
				index  ++  ;
		 }

		 iErr  =  0;  goto  errLabel;
	 }

	 //  2015/06/20,三列上四下三的方案被否决了。下面采用三列左四右三的方案
	 if  (  cnt  ==  7  )  {
		 iRows  =  3;
		 int  index  =  0,  iRow  =  0,  iCol  =  0;  
		 
		 for  (  i  =  0,index = 0;  i  <  uiMaxCnt_imgMems  &&  index  <  cnt;  i  ++  )  {
				pImg =  (  CAP_IMAGE  *  )(  (  (  char  *  )pImgMems  )  +  i  *  uiSize_pImgMem  );	//  &pImages->mems[i];
				if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;

				int  iW_average  =  iW_desc  *  0.33;
				int  iH_average  =  iH_desc  *  0.33;
				int  iW_half  =  iW_desc  *  0.5;
				int  iH_half  =  iH_desc  *  0.5;
					 
				switch  (  index  )  {
						case  0:
							   iW  =  iW_average;
							   iH  =  iH_half;
							   iX  =  iX_desc;
							   iY  =  iY_desc;
							   break;
						case  1:
							   iW  =  iW_average;
							   iH  =  iH_half;
							   iX  =  iX_desc + iW_average;
							   iY  =  iY_desc;
							   break;
						case  2:
							   iW  =  iW_average;
							   iH  =  iH_half;
							   iX  =  iX_desc;
							   iY  =  iY_desc + iH_half;
							   break;
						case  3:
							   iW  =  iW_average;
							   iH  =  iH_half;
							   iX  =  iX_desc + iW_average;
							   iY  =  iY_desc + iH_half;
							   break;
						case  4:
							   iW  =  iW_average;
							   iH  =  iH_average;
							   iX  =  iX_desc + iW_average * 2;
							   iY  =  iY_desc + iH_average * 0;
							   break;
						case  5:
							   iW  =  iW_average;
							   iH  =  iH_average;
							   iX  =  iX_desc + iW_average * 2;
							   iY  =  iY_desc + iH_average * 1;
							   break;
						case  6:
							   iW  =  iW_average;
							   iH  =  iH_average;
							   iX  =  iX_desc + iW_average * 2;
							   iY  =  iY_desc + iH_average * 2;
							   break;

						default:
								goto  errLabel;
				}
				
				myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  pImg->iW_org,  pImg->iH_org,  iX,  iY,  iW,  iH,  
									&iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,									  
									  &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );				

				if  (  pImg->iW_i  !=  iW_i
					||  pImg->iH_i  !=  iH_i
					||  pImg->iX_src_i  !=  iX_src_i
					||  pImg->iY_src_i  !=  iY_src_i
					||  pImg->iX_dst  !=  iX_dst				
					||  pImg->iY_dst  !=  iY_dst
					||  pImg->iW_dst  !=  iW_dst
					||  pImg->iH_dst  !=  iH_dst
					)				
				{
						  pImg->bResized  =  TRUE;
						  
						  //
						  pImg->iW_i  =  iW_i;
						  pImg->iH_i  =  iH_i;
						  pImg->iX_src_i  =  iX_src_i;
						  pImg->iY_src_i  =  iY_src_i;
						  //
						  pImg->iX_dst  =  iX_dst;				  
						  pImg->iY_dst  =  iY_dst;
						  pImg->iW_dst  =  iW_dst;
						  pImg->iH_dst  =  iH_dst;					  
				}

				//  traceLog(  _T(  "case is  3, index is %d,  pImg  iX  %d, iY %d, iW %d,iH %d"  ),  index,  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iH  );
				
				index  ++  ;
		 }

		 iErr  =  0;  goto  errLabel;
	 }

	 //  2015/06/20，上二下三下三的方案被否决了，下面采用左2右3右3的3列方案
	 if  (  cnt  ==  8  )  {
		 iRows  =  3;
		 int  index  =  0,  iRow  =  0,  iCol  =  0;  
		 
		 for  (  i  =  0,index = 0;  i  <  uiMaxCnt_imgMems  &&  index  <  cnt;  i  ++  )  {
				pImg =  (  CAP_IMAGE  *  )(  (  (  char  *  )pImgMems  )  +  i  *  uiSize_pImgMem  );	//  &pImages->mems[i];
				if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;

				int  iW_average  =  iW_desc  *  0.33;
				int  iH_average  =  iH_desc  *  0.33;
				int  iW_half  =  iW_desc  *  0.5;
				int  iH_half  =  iH_desc  *  0.5;
					 
				switch  (  index  )  {
						case  0:							//  1st column
							   iW  =  iW_average;
							   iH  =  iH_half;
							   iX  =  iX_desc;
							   iY  =  iY_desc;
							   break;
						case  1:
							   iW  =  iW_average;
							   iH  =  iH_half;
							   iX  =  iX_desc;
							   iY  =  iY_desc + iH_half;
							   break;
						case  2:							//  2nd column
							   iW  =  iW_average;
							   iH  =  iH_average;
							   iX  =  iX_desc + iW_average;
							   iY  =  iY_desc + iH_average  *  0;
							   break;
						case  3:
							   iW  =  iW_average;
							   iH  =  iH_average;
							   iX  =  iX_desc + iW_average;
							   iY  =  iY_desc + iH_average  *  1;
							   break;
						case  4:
							   iW  =  iW_average;
							   iH  =  iH_average;
							   iX  =  iX_desc + iW_average;
							   iY  =  iY_desc + iH_average  *  2;
							   break;
						case  5:							//  3rd column
							   iW  =  iW_average;
							   iH  =  iH_average;
							   iX  =  iX_desc + iW_average  *  2;
							   iY  =  iY_desc + iH_average  *  0;
							   break;
						case  6:
							   iW  =  iW_average;
							   iH  =  iH_average;
							   iX  =  iX_desc + iW_average  *  2;
							   iY  =  iY_desc + iH_average  *  1;
							   break;
						case  7:
							   iW  =  iW_average;
							   iH  =  iH_average;
							   iX  =  iX_desc + iW_average  *  2;
							   iY  =  iY_desc + iH_average  *  2;
							   break;

						default:
								goto  errLabel;
				}
				
				myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  pImg->iW_org,  pImg->iH_org,  iX,  iY,  iW,  iH,  
									&iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,									  
									  &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );				

				if  (  pImg->iW_i  !=  iW_i
					||  pImg->iH_i  !=  iH_i
					||  pImg->iX_src_i  !=  iX_src_i
					||  pImg->iY_src_i  !=  iY_src_i
					||  pImg->iX_dst  !=  iX_dst				
					||  pImg->iY_dst  !=  iY_dst
					||  pImg->iW_dst  !=  iW_dst
					||  pImg->iH_dst  !=  iH_dst
					)				
				{
						  pImg->bResized  =  TRUE;
						  
						  //
						  pImg->iW_i  =  iW_i;
						  pImg->iH_i  =  iH_i;
						  pImg->iX_src_i  =  iX_src_i;
						  pImg->iY_src_i  =  iY_src_i;
						  //
						  pImg->iX_dst  =  iX_dst;				  
						  pImg->iY_dst  =  iY_dst;
						  pImg->iW_dst  =  iW_dst;
						  pImg->iH_dst  =  iH_dst;					  
				}

				//  traceLog(  _T(  "case is  3, index is %d,  pImg  iX  %d, iY %d, iW %d,iH %d"  ),  index,  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iH  );
				
				index  ++  ;
		 }

		 iErr  =  0;  goto  errLabel;
	 }


	 //
	 if  (  cnt  )  {
		 iRows  =  (  int  )sqrt(  (  double  )cnt  );
		 if  (  iRows  *  iRows  <  cnt  )  iRows  ++  ;
		 //

		 cnt  =  0;
		 for  (  i  =  0;  i  <  uiMaxCnt_imgMems;  i  ++  )  {
			  pImg  =  (  CAP_IMAGE  *  )(  (  (  char  *  )pImgMems  )  +  i  *  uiSize_pImgMem  );	//  &pImages->mems[i];
			  if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;

			  int  iRow,  iCol;
			  iRow  =  cnt  %  iRows;
			  iCol  =  cnt  /  iRows;

			  //  int  iX,  iY;
			  iX  =  iX_desc  +  (  int  )(  iRow  *  iW_desc  /  (  float  )iRows  );
			  iY  =  iY_desc  +  (  int  )(  iCol  *  iH_desc  /  (  float  )iRows  );

#if  0
			  int  iX_src,  iY_src;
			  unsigned  int  iW_src,  iH_src;
			  int  iX_dst,  iY_dst;
			  unsigned  int  iW_dst,  iH_dst;
#endif

			  myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  pImg->iW_org,  pImg->iH_org,  iX,  iY,  iW_desc  /  iRows,  iH_desc  /  iRows,  
				  &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
				  &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );
			  
			  if  (  pImg->iW_i  !=  iW_i
					||  pImg->iH_i  !=  iH_i
					||  pImg->iX_src_i  !=  iX_src_i
					||  pImg->iY_src_i  !=  iY_src_i
					||  pImg->iX_dst  !=  iX_dst				
					||  pImg->iY_dst  !=  iY_dst
					||  pImg->iW_dst  !=  iW_dst
					||  pImg->iH_dst  !=  iH_dst
					)				
				{
						  pImg->bResized  =  TRUE;
						  
						  //
						  pImg->iW_i  =  iW_i;
						  pImg->iH_i  =  iH_i;
						  pImg->iX_src_i  =  iX_src_i;
						  pImg->iY_src_i  =  iY_src_i;
						  //
						  pImg->iX_dst  =  iX_dst;				  
						  pImg->iY_dst  =  iY_dst;
						  pImg->iW_dst  =  iW_dst;
						  pImg->iH_dst  =  iH_dst;					  
				}

			  cnt  ++  ;
		 }
	 }

	 iErr  =  0;
errLabel:

	return  iErr;
}


//
//
//int  getVal_bCapImagesSame(  CAP_IMAGES  *  pImgs1,  CAP_IMAGES  *  pImgs1_int,  CAP_IMAGES  *  pImgs2,  bool  bBreakIfNotSame,  BOOL  *  pbVal  )
bool  isSame_capImages(CAP_IMAGES* pImgs1, CAP_IMAGES* pImgs1_int, CAP_IMAGES* pImgs2, bool  bBreakIfNotSame)
{
	int  iErr = -1;
	BOOL  bSame = FALSE;
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();

	if (!pImgs1 || !pImgs1_int || !pImgs2)  return  false;

	CAP_IMAGES& capImages = *pImgs1_int;

	memset(&capImages, 0, sizeof(capImages));


	//
	CAP_IMAGES  tmp_imgs;
	tmp_imgs = *pImgs2;
	int  i;
	for (i = 0; i < mycountof(tmp_imgs.mems); i++) {
		tmp_imgs.mems[i].bResized = false;
	}
	pImgs2 = &tmp_imgs;


	//
	CAP_IMAGES* pImages = pImgs1;
	int  j;
	for (j = 0; j < mycountof(pImages->mems); j++) {
		CAP_image* pCapImg = &pImages->mems[j];
		//
		BOOL  bImgExists = FALSE;

		//
		//if  (  pImages->locations[j].rect.iW  )  bImgExists  =  TRUE;

		//
		if (!bImgExists) {

			//	
			if (pCapImg->iW_org
				&& pCapImg->iH_org
				&& pCapImg->iTaskId
				&& isPlayerIndexValid(pProcInfo, pCapImg->playerId.index_player))
			{
				bImgExists = TRUE;
			}
		}

		//
		if (!bImgExists)  continue;

		//
		CAP_IMAGE* pImg = &capImages.mems[capImages.head.usCnt];
		memcpy(pImg, pCapImg, sizeof(pImg[0]));
		//
		pImg->dwTickCnt_lastDrawing = 0;
		pImg->bNeedUpdated_doPost_drawCapImages = FALSE;
		//
		capImages.head.usCnt++;
	}
	//  2016/02/24
	capImages.head.ts_images = pImgs2->head.ts_images;
	//
	if (!memcmp(&capImages, pImgs2, sizeof(capImages))) {
		bSame = TRUE;
	}

	//
#ifdef  __DEBUG__
	if (!bSame) {
		int  ii;
		ii = 0;
		//
		if (bBreakIfNotSame) {
			int  ii = 0;
		}
		//
		if (memcmp(&capImages.head, &pImgs2->head, sizeof(capImages.head))) {
			ii = 1;
		}
		//
#if  0
		if (memcmp(&capImages.locations, &pImgs2->locations, sizeof(capImages.locations))) {
			ii = 2;
		}
#endif
		//
		if (memcmp(&capImages.mems, &pImgs2->mems, sizeof(capImages.mems))) {
			ii = 3;
			//
			int  i;
			for (i = 0; i < mycountof(capImages.mems); i++) {
				if (memcmp(&capImages.mems[i], &pImgs2->mems[i], sizeof(capImages.mems[i]))) {
					ii = 4;
				}
			}
		}
	}
#endif


	iErr = 0;

errLabel:

	if (!iErr) {
		//if  (  pbVal  )  *pbVal  =  bSame;
		return  bSame;
	}

	return  false;
}





