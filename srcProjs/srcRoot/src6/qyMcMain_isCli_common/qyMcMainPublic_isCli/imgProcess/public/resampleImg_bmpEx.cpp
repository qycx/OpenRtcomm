

#include "stdafx.h"
#include	<tchar.h>
#include	<time.h>
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

//  #include	"myresource.h"
#include	"tmpCeLib.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qmcDmoPublic.h"
#include	"qyCusResTemp.h"

#ifndef  __WINCE__
#include	"qmcVWall.h"
#endif
#include	"qmcCmdProc.h"

#include	"qyAvRecordPublic.h"
#include	"imgProcessPublic.h"
#include	"imgProcessCommon.h"
#include	"isCliHelpPublic.h"

#include	<Shlwapi.h>
#include	<math.h>

#include	"bmpExPublic.h"



//
//void bmpEx_ScaleBilinear2(long width, long height)
 int bmpEx_ScaleBilinear2_24(  unsigned  char  *  src,  int  srcWidth,  int  srcHeight,  unsigned  char  *  dst,  int  dstWidth,  int  dstHeight  )
{
	int  iErr  =  -1;

	//
	BITMAPINFOHEADER m_bih;

	int  bits  =  24;
	makeBmpInfoHeader_rgb(  bits,  srcWidth,  srcHeight,  &m_bih  );
	long m_iBpp  =  bits  /  8;
	LPBYTE m_lpData  =  src;
	
	long m_iPitch;
	{	
		long _pitch = m_bih.biWidth * m_iBpp;
		while ((_pitch & 3) != 0)
			_pitch++;
		m_iPitch  =  _pitch;
	}
	DWORD m_dwSize  =  m_iPitch  *  m_bih.biHeight;;



	//	
	long width  =  dstWidth;
	long height  =  dstHeight;



	// Check for valid bitmap
	//if (IsValid())
	{
		// Calculate scaling params
		long _width = max(1, width);
		long _height = max(1, height);
		float dx = (float)m_bih.biWidth / (float)_width;
		float dy = (float)m_bih.biHeight / (float)_height;
		long _pitch = m_iBpp * _width;
		while ((_pitch & 3) != 0)
			_pitch++;
		fixed f_dx = ftofx(dx);
		fixed f_dy = ftofx(dy);
		fixed f_1 = itofx(1);

		// Create temporary bitmap
		DWORD dwSize = _pitch * _height;
		//LPBYTE lpData = (LPBYTE)malloc(dwSize*sizeof(BYTE));
		LPBYTE  lpData  =  dst;

		// Scale bitmap
		DWORD dwDstHorizontalOffset;
		DWORD dwDstVerticalOffset = 0;
		DWORD dwDstTotalOffset;
		//
		LPDWORD lpSrcData = (LPDWORD)m_lpData;
		//
		DWORD dwSrcTotalOffset;
		LPDWORD lpDstData = (LPDWORD)lpData;
		for (long i=0; i<_height; i++)
		{
			dwDstHorizontalOffset = 0;
			for (long j=0; j<_width; j++)
			{
				// Update destination total offset
				dwDstTotalOffset = dwDstVerticalOffset + dwDstHorizontalOffset;

				// Update bitmap
				fixed f_i = itofx(i);
				fixed f_j = itofx(j);
				fixed f_a = Mulfx(f_i, f_dy);
				fixed f_b = Mulfx(f_j, f_dx);
				long m = fxtoi(f_a);
				long n = fxtoi(f_b);
				fixed f_f = f_a - itofx(m);
				fixed f_g = f_b - itofx(n);
				dwSrcTotalOffset = m*m_iPitch + n*m_iBpp;
				DWORD dwSrcTopLeft = dwSrcTotalOffset;
				DWORD dwSrcTopRight = dwSrcTotalOffset + m_iBpp;
				if (n >= m_bih.biWidth-1)
					dwSrcTopRight = dwSrcTotalOffset;
				DWORD dwSrcBottomLeft = dwSrcTotalOffset + m_iPitch;
				if (m >= m_bih.biHeight-1)
					dwSrcBottomLeft = dwSrcTotalOffset;
				DWORD dwSrcBottomRight = dwSrcTotalOffset + m_iPitch + m_iBpp;
				if ((n >= m_bih.biWidth-1) || (m >= m_bih.biHeight-1))
					dwSrcBottomRight = dwSrcTotalOffset;
				fixed f_w1 = Mulfx(f_1-f_f, f_1-f_g);
				fixed f_w2 = Mulfx(f_1-f_f, f_g);
				fixed f_w3 = Mulfx(f_f, f_1-f_g);
				fixed f_w4 = Mulfx(f_f, f_g);
				//
#if  0
				_PIXEL pixel1 = lpSrcData[dwSrcTopLeft>>2];
				_PIXEL pixel2 = lpSrcData[dwSrcTopRight>>2];
				_PIXEL pixel3 = lpSrcData[dwSrcBottomLeft>>2];
				_PIXEL pixel4 = lpSrcData[dwSrcBottomRight>>2];
#endif
				//
	#if  0
				_PIXEL pixel1 = _RGB(  src[dwSrcTopLeft  +  2],  src[dwSrcTopLeft  +  1],  src[dwSrcTopLeft  +  0]  );//lpSrcData[dwSrcTopLeft>>2];
				_PIXEL pixel2 = _RGB(  src[dwSrcTopRight  +  2],  src[dwSrcTopRight  +  1],  src[dwSrcTopRight  +  0]  );
				_PIXEL pixel3 = _RGB(  src[dwSrcBottomLeft  +  2],  src[dwSrcBottomLeft  +  1],  src[dwSrcBottomLeft  +  0]  );
				_PIXEL pixel4 = _RGB(  src[dwSrcBottomRight  +  2],  src[dwSrcBottomRight  +  1],  src[dwSrcBottomLeft  +  0]  );

				//
				fixed f_r1 = itofx(_GetRValue(pixel1));
				fixed f_r2 = itofx(_GetRValue(pixel2));
				fixed f_r3 = itofx(_GetRValue(pixel3));
				fixed f_r4 = itofx(_GetRValue(pixel4));
				fixed f_g1 = itofx(_GetGValue(pixel1));
				fixed f_g2 = itofx(_GetGValue(pixel2));
				fixed f_g3 = itofx(_GetGValue(pixel3));
				fixed f_g4 = itofx(_GetGValue(pixel4));
				fixed f_b1 = itofx(_GetBValue(pixel1));
				fixed f_b2 = itofx(_GetBValue(pixel2));
				fixed f_b3 = itofx(_GetBValue(pixel3));
				fixed f_b4 = itofx(_GetBValue(pixel4));
	#endif
				//
				//
				fixed f_r1 = itofx(  src[dwSrcTopLeft  +  2]  );		//_GetRValue(pixel1));
				fixed f_r2 = itofx(  src[dwSrcTopRight  +  2]  );		//_GetRValue(pixel2));
				fixed f_r3 = itofx(  src[dwSrcBottomLeft  +  2]  );		//_GetRValue(pixel3));
				fixed f_r4 = itofx(  src[dwSrcBottomRight  +  2]  );	//_GetRValue(pixel4));
				fixed f_g1 = itofx(  src[dwSrcTopLeft  +  1]  );		//_GetGValue(pixel1));
				fixed f_g2 = itofx(  src[dwSrcTopRight  +  1]  );		//_GetGValue(pixel2));
				fixed f_g3 = itofx(  src[dwSrcBottomLeft  +  1]  );		//_GetGValue(pixel3));
				fixed f_g4 = itofx(  src[dwSrcBottomRight  +  1]  );	//_GetGValue(pixel4));
				fixed f_b1 = itofx(  src[dwSrcTopLeft  +  0]  );		//_GetBValue(pixel1));
				fixed f_b2 = itofx(  src[dwSrcTopRight  +  0]  );		//_GetBValue(pixel2));
				fixed f_b3 = itofx(  src[dwSrcBottomLeft  +  0]  );		//_GetBValue(pixel3));
				fixed f_b4 = itofx(  src[dwSrcBottomLeft  +  0]  );		//_GetBValue(pixel4));




				//
				BYTE red = (BYTE)fxtoi(Mulfx(f_w1, f_r1) + Mulfx(f_w2, f_r2) + Mulfx(f_w3, f_r3) + Mulfx(f_w4, f_r4));
				BYTE green = (BYTE)fxtoi(Mulfx(f_w1, f_g1) + Mulfx(f_w2, f_g2) + Mulfx(f_w3, f_g3) + Mulfx(f_w4, f_g4));
				BYTE blue = (BYTE)fxtoi(Mulfx(f_w1, f_b1) + Mulfx(f_w2, f_b2) + Mulfx(f_w3, f_b3) + Mulfx(f_w4, f_b4));
#if  0
				lpDstData[dwDstTotalOffset>>2] = _RGB(red, green, blue);
#endif
				//
				dst[dwDstTotalOffset  +  0]  =  blue;
				dst[dwDstTotalOffset  +  1]  =  green;
				dst[dwDstTotalOffset  +  2]  =  red;


				// Update destination horizontal offset
				dwDstHorizontalOffset += m_iBpp;
			}

			// Update destination vertical offset
			dwDstVerticalOffset += _pitch;
		}

		// Update bitmap info
		m_iPitch = _pitch;
		m_bih.biWidth = _width;
		m_bih.biHeight = _height;
		//free(m_lpData);
		m_dwSize = dwSize;
		m_lpData = lpData;
	}

	iErr  =  0;

errLabel:
	
	return  iErr;

}





