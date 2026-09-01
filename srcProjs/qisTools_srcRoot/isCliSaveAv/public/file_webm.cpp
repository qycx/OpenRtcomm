

#include	"stdafx.h"

#include	<stddef.h>
#include	<mmsystem.h>
#include	<dmo.h>
#include	<dsound.h>
#include	<time.h>
#include	<tchar.h>

//#include	"qyMcMainCommon.h"
//#include	"qyDynLib.h"

//#include	"qyMcMainRealTimeMediaProc.h"

//#include	"tmpCeLib.h"

//#include	"qyAvRecord.h"
//#include	"qyAvRecord_dx.h"
//#include	"qmcSound_dx.h"

//#include	"qmcVideoCapture_isCli.h"
#include	"qmOpenCommon.h"
#include	"saveAvProc.h"
#include <stdio.h>
//#include <showInfo_open.h>

typedef struct vpx_rational {
	int  num;
	int  den;
}vpx_rational_t;


static void mem_put_le16( char * mem, unsigned int val  )  {
	mem[0]  =  val;
	mem[1]  =  val >>  8;
}

static void mem_put_le32( char * mem, unsigned int val  )  {
	mem[0]  =  val;
	mem[1]  =  val >>  8;
	mem[2]  =  val >>  16;
	mem[3]  =  val >>  24;
}

//static void write_ivf_file_header( FILE * outfile, const vpx_codec_enc_cfg_t * cfg, int frame_cnt  )  
static void write_ivf_file_header( FILE * outfile, int  fourcc,  int  g_w,  int  g_h,  vpx_rational_t  g_timebase, int frame_cnt  )  
{

	char header[32];

#if  0
	if ( cfg->g_pass != VPX_RC_ONE_PASS  &&  cfg->g_pass != VPX_RC_LAST_PASS  )  
		return;
#endif

	header[0]  =  'D';
	header[1]  =  'K';
	header[2]  =  'I';
	header[3]  =  'F';
	mem_put_le16(  header + 4,  0  );			// version
	mem_put_le16(  header + 6,  32  );			// headersize
	mem_put_le32(  header + 8,  fourcc  );			// headersize
	mem_put_le16(  header + 12,  g_w  );			// 
	mem_put_le16(  header + 14,  g_h  );			// 
	mem_put_le32(  header + 16,  g_timebase.den  );			// rate
	mem_put_le32(  header + 20,  g_timebase.num  );			// scale
	mem_put_le32(  header + 24,  frame_cnt  );			// length
	mem_put_le32(  header + 28,  0  );			// 

	(void )fwrite( header, 1, 32,outfile  );
}







