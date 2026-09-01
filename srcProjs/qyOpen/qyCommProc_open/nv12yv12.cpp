
#include		"stdafx.h"
#if defined(  __APP_qyMc__  )  ||  defined(  __APP_touchscreen__  )  
			#include	"qyMcMainCommon.h"
#else
			#include	<windows.h>
#endif
#include		<tchar.h>

#if 0
//  convert NV12(Y plane, interlaced UV  bytes)  to YV12(Y plane,  V plane,  U plane)
void nv12ToYv12( int width, int height, void * src, void * dst  )
{
	int planeSizeY  =  width * height;
	int planeSizeUV  =  planeSizeY / 2;
	int planeUOffset  =  planeSizeUV  / 2;
	int i  =  0;
	unsigned char  * srcPtr  =  (  unsigned char * )src;
	unsigned char  * dstPtr  =  (  unsigned char * )dst;
	unsigned char  * dstPtrV  =  (  unsigned char * )dst + planeSizeY;
	unsigned char  * dstPtrU  =  (  unsigned char * )dst + planeSizeY + planeUOffset;

	//  copy the entire Y plane
	memcpy(  dstPtr,  src,  planeSizeY  );

	//  deinterlace the UV data
	for (  i = planeSizeY; i < ( planeSizeY + planeSizeUV  );  i  = i + 2 )
	{
		*dstPtrV ++  =  srcPtr[i + 1];
		*dstPtrU ++  =  srcPtr[i];
	}
}

//  convert YV12(Y plane,  V plane,  U plane)  to NV12(Y plane, interlaced UV  bytes)
void yv12ToNv12( int width, int height, void * src, void * dst  )
{
	int planeSizeY  =  width * height;
	int planeSizeUV  =  planeSizeY / 2;
	int planeUOffset  =  planeSizeUV  / 2;
	int i  =  0;
	unsigned char  * srcPtr  =  (  unsigned char * )src;
	unsigned char  * dstPtr  =  (  unsigned char * )dst;
	unsigned char  * srcPtrV  =  (  unsigned char * )src + planeSizeY;
	unsigned char  * srcPtrU  =  (  unsigned char * )src + planeSizeY + planeUOffset;

	//  copy the entire Y plane
	memcpy(  dstPtr,  src,  planeSizeY  );

	//  deinterlace the UV data
	for (  i = planeSizeY; i < ( planeSizeY + planeSizeUV  );  i  = i + 2 )
	{
		dstPtr[i + 1]  =  *srcPtrV++;
		dstPtr[i]  =  *srcPtrU++;
	}
}
#endif


