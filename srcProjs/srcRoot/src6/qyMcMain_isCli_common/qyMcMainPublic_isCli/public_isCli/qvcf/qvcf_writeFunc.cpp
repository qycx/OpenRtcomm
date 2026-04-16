

#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
//  #include	"myfourcc.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"

#include	"qmcVideoCapture_rtsp.h"
#include	"qmcCopyData.h"
#include	"rtspUsrData.h"
#include	"qmcCfg.h"

#include	"qvcfDefs.h"

//
//  *pptr指向下一个空间，而不是输出串
 //  *pSize为剩余的字节数，不是一共得到了多少 
int  mem_put_16(  unsigned  short  sVal,  char  **  pptr_usable,  unsigned  int  *  pSize_usable  )
{
	unsigned  short  tmp_s  =  qyhtons(  sVal  );
	int  len  =  2;
	if  (  *pSize_usable  <  len  )  return  -1;
	memcpy(  *pptr_usable,  &tmp_s,  sizeof(  tmp_s  )  );  *pptr_usable  +=  len;  *pSize_usable  -=  len;
	return  0;
}
int  mem_put_32(  unsigned  long  lVal,  char  **  pptr_usable,  unsigned  int  *  pSize_usable  )
{
	unsigned  long  tmp_l  =  qyhtonl(  lVal  );
	int  len  =  4;
	if  (  *pSize_usable  <  len  )  return  -1;
	memcpy(  *pptr_usable,  &tmp_l,  sizeof(  tmp_l  )  );  *pptr_usable  +=  len;  *pSize_usable  -=  len;
	return  0;
}
int  mem_put_64(  unsigned  __int64  ui64Val,  char  **  pptr_usable,  unsigned  int  *  pSize_usable  )
{
	unsigned  __int64  tmp_l64  =  qyhtonl64(  ui64Val  );
	int  len  =  8;
	if  (  *pSize_usable  <  len  )  return  -1;
	memcpy(  *pptr_usable,  &tmp_l64,  sizeof(  tmp_l64  )  );  *pptr_usable  +=  len;  *pSize_usable  -=  len;
	return  0;
}
int  mem_put_data(  unsigned  char  *  data,  unsigned  int  len,  char  **  pptr_usable,  unsigned  int  *  pSize_usable  )
{
	if  (  *pSize_usable  <  len  )  return  -1;
	memcpy(  *pptr_usable,  data,  len  );  *pptr_usable  +=  len;  *pSize_usable  -=  len;
	return  0;
}





//
int  qvcf_write_fileHeader(  char  *  ver,  char  *  buf,  unsigned  int  *puiSize,  FILE  *  fp  )
{
	int  iErr  =  -1;

	//
	int  headerSize  =  CONST_vcfFile_headerSize;

	if  (  *puiSize  <  headerSize  )  return  -1;

	//
	char  *  ptr  =  buf;
	unsigned  int  size_left  =  *puiSize;

	buf[0]  =  'Q';
	buf[1]  =  'V';
	buf[2]  =  'C';
	buf[3]  =  'F';
	//
	ptr  +=  4;
	size_left  -=  4;
	//
	memcpy(  ptr,  ver,  4  );
	ptr  +=  4;
	size_left  -=  4;	
	//
	if  (  mem_put_16(  headerSize,  &ptr,  &size_left  )  )  goto  errLabel;
	//
	int  len  =  *puiSize  -  size_left;
	memset(  ptr,  0,  headerSize  -  len  );

	*puiSize  =  headerSize;

	//
	fwrite(  buf,  headerSize,  1,  fp  );

	iErr  =  0;

errLabel:

	return  0;
}

//  流头.sym 1 + lineType 2 + idInfo 8  +  tranNo 4 + mediaType 1  +  detaType  2  +  a waveformat +  extra data
//  流头.sym 1 + lineType 2 + idInfo 8  +  tranNo 4 + mediaType 1  +  detaType  2  +  v bih +  extra data
//  流头.sym 1 + lineType 2 + idInfo 8  +  tranNo 4 + mediaType 1  +  detaType  2  +  len  2 + spspps
//  流头.sym 1 + lineType 2 + idInfo 8  +  tranNo 4 + mediaType 1  +  detaType  2  +  len  2 + useName

//  201505/09
int  qvcf_write_streamInfo(  VCF_streamInfo_common  *  p,  char  *  buf,  unsigned  int  *puiSize,  FILE  *  fp  )
{
	int  iErr  =  -1;
	char  *  ptr  =  buf;

	//
	memcpy(  p->lineSym,  CONST_vcfLine_sym,  CONST_vcfLine_symLen  );
	p->usLineType  =  CONST_vcfLineType_streamInfo;


	if  (  *puiSize  <  CONST_vcfLineCommon_len  )  goto  errLabel;

	//
	ptr  =  buf  +  CONST_vcfLineCommon_len;
	unsigned  int  size_left_lineHeaderData  =  *puiSize  -  CONST_vcfLineCommon_len;
	
	
	if  (  mem_put_64(  p->idInfo.ui64Id,  &ptr,  &size_left_lineHeaderData  )  )  goto  errLabel;
	if  (  mem_put_32(  p->uiTranNo,  &ptr,  &size_left_lineHeaderData  )  )  goto  errLabel;
	if  (  mem_put_data(  &p->ucMediaType,  1,  &ptr,  &size_left_lineHeaderData  )  )  goto  errLabel;
	if  (  mem_put_16(  p->usDataType,  &ptr,  &size_left_lineHeaderData  )  )  goto  errLabel;


	switch  (  p->usDataType  )  {
			case  CONST_vcfDataType_ucCompressors:  {
				  VCF_streamInfo_ucCompressors  *  pVsc  =  (  VCF_streamInfo_ucCompressors  *  )p;
				  int  tmpLen  =  sizeof(  pVsc->ucCompressors  );
				  if  (  mem_put_data(  (  unsigned  char  *  )&pVsc->ucCompressors,  tmpLen,  &ptr,  &size_left_lineHeaderData  )  )  goto  errLabel;

				  }
				  break;
			case  CONST_vcfDataType_ah:  {
				  VCF_streamInfo_ah  *  pVsa  =  (  VCF_streamInfo_ah  *  )p;
				  QY_AUDIO_HEADER  ah  =  pVsa->ah;
				  int  tmpLen  =  qyhtonAudioHeader(  &ah  );
				  if  (  mem_put_data(  (  unsigned  char  *  )&ah,  tmpLen,  &ptr,  &size_left_lineHeaderData  )  )  goto  errLabel;

				  }
				  break;
			case  CONST_vcfDataType_vh:  {
				  VCF_streamInfo_vh  *  pVsv  =  (  VCF_streamInfo_vh  *  )p;
				  QY_VIDEO_HEADER  vh  =  pVsv->vh;
				  int  tmpLen  =  qyhtonVideoHeader(  &vh  );
				  if  (  mem_put_data(  (  unsigned  char  *  )&vh,  tmpLen,  &ptr,  &size_left_lineHeaderData  )  )  goto  errLabel;
				  }
				  break;		
			case  CONST_vcfDataType_spsPps:  {
				  VCF_streamInfo_spsPps  *  pVss  =  (  VCF_streamInfo_spsPps  *  )p;
				  VH_stream  vs  =  pVss->vh_stream;
				  char  spsPps[512]  =  "";
				  unsigned  int  spsPpsLen  =  sizeof(  spsPps  );
				  if  (  makeSpsPps(  &vs,  spsPps,  &spsPpsLen  )  )  goto  errLabel;
				  if  (  mem_put_data(  (  unsigned  char  *  )spsPps,  spsPpsLen,  &ptr,  &size_left_lineHeaderData  )  )  goto  errLabel;

				  }
				  break;		
			case  CONST_vcfDataType_usrName:  {
				  }
				  break;		
			default:			
				  break;
	}

	int  lineHeaderData_len  =  *puiSize  -  CONST_vcfLineCommon_len  -  size_left_lineHeaderData;
	//
	ptr  =  buf;
	unsigned  int  size_left  =  CONST_vcfLineCommon_len;
	
	//
	memcpy(  ptr,  CONST_vcfLine_sym,   CONST_vcfLine_symLen  );		ptr  +=  CONST_vcfLine_symLen;  size_left  -=  CONST_vcfLine_symLen;
	//
	if  (  mem_put_16(  p->usLineType,  &ptr,  &size_left  )  )  goto  errLabel;
	if  (  mem_put_16(  lineHeaderData_len,  &ptr,  &size_left  )  )  goto  errLabel;

	//
	int  len  =  lineHeaderData_len  +  CONST_vcfLineCommon_len;
	fwrite(  buf,  len,  1,  fp  );


	iErr  =  0;
errLabel:
	
	return  iErr;

}

//  201505/09
int  qvcf_write_frameInfo(  VCF_frame_header  *  p,  char  *  data,  unsigned  int  dataLen,  char  *  buf,  unsigned  int  *puiSize,  FILE  *  fp  )
{	
	int  iErr  =  -1;
	char  *  ptr  =  buf;

	//
	memcpy(  p->lineSym,  CONST_vcfLine_sym,  CONST_vcfLine_symLen  );
	p->usLineType  =  CONST_vcfLineType_frame;
	p->uiLen  =  dataLen;

	if  (  *puiSize  <  CONST_vcfLineCommon_len  )  goto  errLabel;

	//
	ptr  =  buf  +  CONST_vcfLineCommon_len;
	unsigned  int  size_left_lineHeaderData  =  *puiSize  -  CONST_vcfLineCommon_len;
	
	
	if  (  mem_put_64(  p->idInfo.ui64Id,  &ptr,  &size_left_lineHeaderData  )  )  goto  errLabel;
	if  (  mem_put_32(  p->uiTranNo,  &ptr,  &size_left_lineHeaderData  )  )  goto  errLabel;
	if  (  mem_put_data(  &p->ucMediaType,  1,  &ptr,  &size_left_lineHeaderData  )  )  goto  errLabel;
	if  (  mem_put_64(  p->timestamp,  &ptr,  &size_left_lineHeaderData  )  )  goto  errLabel;
	if  (  mem_put_32(  p->uiSampleTimeInMs,  &ptr,  &size_left_lineHeaderData  )  )  goto  errLabel;

	if  (  mem_put_32(  p->uiPts,  &ptr,  &size_left_lineHeaderData  )  )  goto  errLabel;
	
	if  (  mem_put_32(  p->uiLen,  &ptr,  &size_left_lineHeaderData  )  )  goto  errLabel;

	//
		int  lineHeaderData_len  =  *puiSize  -  CONST_vcfLineCommon_len  -  size_left_lineHeaderData;
	//
	ptr  =  buf;
	unsigned  int  size_left  =  CONST_vcfLineCommon_len;
	
	//
	memcpy(  ptr,  CONST_vcfLine_sym,   CONST_vcfLine_symLen  );		ptr  +=  CONST_vcfLine_symLen;  size_left  -=  CONST_vcfLine_symLen;
	//
	if  (  mem_put_16(  p->usLineType,  &ptr,  &size_left  )  )  goto  errLabel;
	if  (  mem_put_16(  lineHeaderData_len,  &ptr,  &size_left  )  )  goto  errLabel;

	//
	int  len  =  lineHeaderData_len  +  CONST_vcfLineCommon_len;
	fwrite(  buf,  len,  1,  fp  );


	iErr  =  0;
errLabel:
	
	return  iErr;

}



