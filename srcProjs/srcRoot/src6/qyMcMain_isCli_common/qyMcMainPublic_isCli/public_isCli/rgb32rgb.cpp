

#include  "stdafx.h"


#if  0
 int  rgb24To32(  unsigned  char  *  src,  unsigned  char  *  dst,  int  iWidth,  int  iHeight  )
{
	if  (  iWidth  <=  0  ||  iHeight  <=  0  )  {
		OutputDebugString(  _T(  "rgb24ToRgb32 failed, width or height <=  0"  )  );
		return  -1;
	}
	
	int  widthBytes_src  =  (  iWidth  *  24  +  31  )  /  32  *  4;
	int  widthBytes_dst  =  iWidth  *  4;						

	int	 i,  j;	
	int  offset_src,  offset_dst;
	
	for  (  i  =  0;  i  <  iHeight;  i  ++  )  {	
		 int  m_src  =  i  *  widthBytes_src;				
		 int  m_dst  =  i  *  widthBytes_dst;

		 for  (  j  =  0;  j  <  iWidth;  j  ++  )  {		
			  offset_src  =  m_src  +  j  *  3;
			  offset_dst  =  m_dst  +  j  *  4;								

			  (  (  BYTE  *  )dst  )[offset_dst  +  0]  =  *(  (  (  BYTE  *  )src  )  +  offset_src  +  0  );				
			  (  (  BYTE  *  )dst  )[offset_dst  +  1]  =  *(  (  (  BYTE  *  )src  )  +  offset_src  +  1  );
			  (  (  BYTE  *  )dst  )[offset_dst  +  2]  =  *(  (  (  BYTE  *  )src  )  +  offset_src  +  2  );						 				
			  (  (  BYTE  *  )dst  )[offset_dst  +  3]  =  0xff;
		 }							   
	}

	return  0;
 }
#endif

  int  rgb24To32(  unsigned  char  *  src,  unsigned  char  *  dst,  int  iWidth,  int  iHeight  )
{
	if  (  iWidth  <=  0  ||  iHeight  <=  0  )  {
		OutputDebugString(  _T(  "rgb24ToRgb32 failed, width or height <=  0"  )  );
		return  -1;
	}
	
	int  widthBytes_src  =  (  iWidth  *  24  +  31  )  /  32  *  4;
	int  widthBytes_dst  =  iWidth  *  4;						

	int	 i,  j;	
	//  int  offset_src,  offset_dst;
	
	BYTE  *  pSrc  =  NULL;
	BYTE  *  pDst  =  NULL;

	for  (  j  =  iHeight  -  1;  j  >=  0;  j  --  )  {	
		 //  int  m_src  =  j  *  widthBytes_src;				
		 //  int  m_dst  =  j  *  widthBytes_dst;
		 pSrc  =  src  +  j  *  widthBytes_src  +  (  iWidth  -  1  )  *  3;				
		 pDst  =  dst  +  j  *  widthBytes_dst  +  (  iWidth  -  1  )  *  4;

		 for  (  i  =  iWidth  -  1;  i  >=  0;  i  --  )  {		
#if  0
			  //  offset_src  =  m_src  +  i  *  3;
			  //  offset_dst  =  m_dst  +  i  *  4;								

			  (  (  BYTE  *  )dst  )[offset_dst  +  0]  =  *(  (  (  BYTE  *  )src  )  +  offset_src  +  0  );				
			  (  (  BYTE  *  )dst  )[offset_dst  +  1]  =  *(  (  (  BYTE  *  )src  )  +  offset_src  +  1  );
			  (  (  BYTE  *  )dst  )[offset_dst  +  2]  =  *(  (  (  BYTE  *  )src  )  +  offset_src  +  2  );						 				
			  (  (  BYTE  *  )dst  )[offset_dst  +  3]  =  0xff;
#endif

			  pDst[3]  =  0xff;
			  pDst[2]  =  pSrc[2];
			  pDst[1]  =  pSrc[1];
			  pDst[0]  =  pSrc[0];
			  
			  pSrc  -=  3;
			  pDst  -=  4;
		 }							   
	}

	return  0;
 }




//  用来调整图像的长度，使是4的倍数，以便压缩
 int  rgb24To24(  unsigned  char  *  src,  int  w_src,  int  h_src,  unsigned  char  *  dst,  int  w_dst,  int  h_dst  )
{
#ifdef  _DEBUG
		//  OutputDebugString(  _T(  "Not finished: rgb24To24\n"  )  );
#endif

	if  (  w_src  <=  0  ||  h_src  <=  0
		||  w_dst  <=  0  ||  h_dst  <=  0  )  
	{
		OutputDebugString(  _T(  "rgb24ToRgb32 failed, width or height <=  0"  )  );
		return  -1;
	}
	//  为了不损失图像，把图像往大了调整，2014/01/29
	if  (  w_src  >  w_dst  ||  h_src  >  h_dst  )  {
		OutputDebugString(  _T(  "rgb24ToRgb32 failed, width or height err"  )  );
		return  -1;
	}
	if  (  w_src  ==  w_dst  )  {	//  宽度相等时，相当于总buffer多几行或少几行，直接改h就可以，不需要移动数据
		return  0;
	}
	
	int  widthBytes_src  =  (  w_src  *  24  +  31  )  /  32  *  4;
	int  widthBytes_dst  =  (  w_dst  *  24  +  31  )  /  32  *  4;

	int	 i,  j;	
	//  int  offset_src,  offset_dst;
	
	BYTE  *  pSrc  =  NULL;
	BYTE  *  pDst  =  NULL;

	for  (  j  =  h_src  -  1;  j  >=  0;  j  --  )  {	
		 pSrc  =  src  +  j  *  widthBytes_src;				
		 pDst  =  dst  +  j  *  widthBytes_dst;

		 //
		 pSrc  =  src  +  j  *  widthBytes_src  +  (  w_src  -  1  )  *  3;				
		 pDst  =  dst  +  j  *  widthBytes_dst  +  (  w_src  -  1  )  *  3;

		 //
		 for  (  i  =  w_src  -  1;  i  >=  0;  i  --  )  {		
			  pDst[2]  =  pSrc[2];
			  pDst[1]  =  pSrc[1];
			  pDst[0]  =  pSrc[0];

			  pSrc  -=  3;
			  pDst  -=  3;
		 }							   

	}

	return  0;
 }
