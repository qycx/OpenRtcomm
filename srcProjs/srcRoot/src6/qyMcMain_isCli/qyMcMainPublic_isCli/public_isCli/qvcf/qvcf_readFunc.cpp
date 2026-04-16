
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


//  *pptr指向下一个空间，而不是输出串
 //  *pSize为剩余的字节数，不是一共得到了多少 
int  mem_get_16(  char  **  pptr_usable,  unsigned  int  *  pSize_usable,  unsigned  short  *  psVal  )
{
	unsigned  short  tmp_s  =  0;
	int  len  =  2;
	if  (  *pSize_usable  <  len  )  return  -1;
	memcpy(  &tmp_s,  *pptr_usable,  sizeof(  tmp_s  )  );  *pptr_usable  +=  len;  *pSize_usable  -=  len;
	*psVal  =  qyntohs(  tmp_s  );
	return  0;
}

int  mem_get_32(  char  **  pptr_usable,  unsigned  int  *  pSize_usable,  unsigned  long  *plVal  )
{
	unsigned  long  tmp_l  =  0;
	int  len  =  4;
	if  (  *pSize_usable  <  len  )  return  -1;
	memcpy(  &tmp_l,  *pptr_usable,  sizeof(  tmp_l  )  );  *pptr_usable  +=  len;  *pSize_usable  -=  len;
	*plVal  =  qyntohl(  tmp_l  );
	return  0;
}
int  mem_get_64(  char  **  pptr_usable,  unsigned  int  *  pSize_usable,  unsigned  __int64  *pui64Val  )
{
	unsigned  __int64  tmp_l64  =  0;
	int  len  =  8;
	if  (  *pSize_usable  <  len  )  return  -1;
	memcpy(  &tmp_l64,  *pptr_usable,  sizeof(  tmp_l64  )  );  *pptr_usable  +=  len;  *pSize_usable  -=  len;
	*pui64Val  =  qyntohl64(  tmp_l64  );
	return  0;
}
int  mem_get_data(  char  **  pptr_usable,  unsigned  int  *  pSize_usable,  unsigned  int  readLen,  unsigned  char  *  data  )
{
	if  (  *pSize_usable  <  readLen  )  return  -1;
	memcpy(  data,  *pptr_usable,  readLen  );  *pptr_usable  +=  readLen;  *pSize_usable  -=  readLen;
	return  0;
}





//
int  qvcf_read_fileHeader(  FILE  *  fp,  VCF_file_header  *  p    )
{
	int  iErr  =  -1;
	char  buf[128];
	
	fseek(  fp,  0,  SEEK_SET  );

	int  len  =  CONST_vcfFile_symLen  +  CONST_vcfFile_verLen  +  2;

	if  (  fread(  buf,  len,  1,  fp  )  !=  1  )  goto  errLabel;
	//
	char* ptr; ptr = buf;
	unsigned  int  size_left; size_left = len;
	memcpy(  p->sym,  ptr,  CONST_vcfFile_symLen  );  ptr  +=  CONST_vcfFile_symLen;  size_left  -=  CONST_vcfFile_symLen;
	p->sym[CONST_vcfFile_symLen]  =  0;
	if  (  _strnicmp(  p->sym,  CONST_vcfFile_sym,  CONST_vcfFile_symLen  )  )  goto  errLabel;
	//
	memcpy(  p->ver,  ptr,  CONST_vcfFile_verLen  );  ptr  +=  CONST_vcfFile_verLen;  size_left  -=  CONST_vcfFile_verLen;
	p->ver[CONST_vcfFile_verLen]  =  0;
	//
	if  (  mem_get_16(  &ptr,  &size_left,  &p->usHeaderSize  )  )  goto  errLabel;
	//
	if  (  p->usHeaderSize  !=  CONST_vcfFile_headerSize  )  goto  errLabel;
	//
	int  tmpLen; tmpLen = p->usHeaderSize - len;
	if  (  fread(  buf,  tmpLen,  1,  fp  )  !=  1  )  goto  errLabel;

	iErr  =  0;

errLabel:
	
	return  iErr;
}

//
int  qvcf_readLineCommon(  FILE  *  fp,  VCF_line_common  *  p  )
{
	int		iErr  =  -1;
	char  buf[CONST_vcfLineCommon_len];
	int  len;

	if  (  fread(  buf,  CONST_vcfLineCommon_len,  1,  fp  )  !=  1  )  goto  errLabel;
	char* ptr; ptr = buf;
	unsigned  int  size_left; size_left = CONST_vcfLineCommon_len;
	if  (  mem_get_data(  &ptr,  &size_left,  CONST_vcfLine_symLen,  p->lineSym  )  )  goto  errLabel;
	if  (  memcmp(  p->lineSym,  CONST_vcfLine_sym,  CONST_vcfLine_symLen  )  )  goto  errLabel;

	//
	if  (  mem_get_16(  &ptr,  &size_left,  &p->usLineType  )  )  goto  errLabel;
	if  (  mem_get_16(  &ptr,  &size_left,  &p->usHeaderDataLen  )  )  goto  errLabel;


	iErr  =  0;
errLabel:
	return  iErr;

}

//
#if  10
int  qvcf_read_streamInfo(  FILE  *  fp,  VCF_line_common  *  pLineCommon,  char  *  buf,  unsigned  int  uiSize,  VCF_streamInfo_common  *  p  )
{
	int  iErr  =  -1;
	char  *  ptr  =  buf;

	if  (  uiSize  <  pLineCommon->usHeaderDataLen  )  {
#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "qvcf_read_streamInfo failed, bufSize < usHeaderDataLen"  )  );
#endif
		return  -1;
	}

	
	if  (  fread(  buf,  pLineCommon->usHeaderDataLen,  1,  fp  )  !=  1  )  goto  errLabel;
	
	//
	ptr  =  buf;
	unsigned  int  size_left_lineHeaderData; size_left_lineHeaderData = pLineCommon->usHeaderDataLen;
	
	//
	if  (  mem_get_64(  &ptr,  &size_left_lineHeaderData,  &p->idInfo.ui64Id  )  )  goto  errLabel;
	if  (  mem_get_32(  &ptr,  &size_left_lineHeaderData,  (  unsigned  long  *  )&p->uiTranNo  )  )  goto  errLabel;
	if  (  mem_get_data(  &ptr,  &size_left_lineHeaderData,  1,  &p->ucMediaType  )  )  goto  errLabel;
	if  (  mem_get_16(  &ptr,  &size_left_lineHeaderData,  &p->usDataType  )  )  goto  errLabel;

	//
	unsigned  char  tmpBuf[512]; tmpBuf[0] = 0;// = "";
	unsigned  int  tmpBufSize; tmpBufSize = sizeof(tmpBuf);
	
	//
	switch  (  p->usDataType  )  {
			case  CONST_vcfDataType_ucCompressors:  
				  if  (  p->ucMediaType  ==  CONST_vcfMediaType_a  )  {
					  VCF_streamInfo_ucCompressors  *  pVsc  =  (  VCF_streamInfo_ucCompressors  *  )p;
				  
					  //
					  int  tmpLen  =  size_left_lineHeaderData;
					  if  (  tmpLen  >  tmpBufSize  )  goto  errLabel;
					  if  (  mem_get_data(  &ptr,  &size_left_lineHeaderData,  tmpLen,  tmpBuf  )  )  goto  errLabel;
					  pVsc->ucCompressors  =  tmpBuf[0];
					  }
				  else  if  (   p->ucMediaType  ==  CONST_vcfMediaType_v  )  {
							VCF_streamInfo_ucCompressors  *  pVsc  =  (  VCF_streamInfo_ucCompressors  *  )p;
				  
							//					
							int  tmpLen  =  size_left_lineHeaderData;
							if  (  tmpLen  >  tmpBufSize  )  goto  errLabel;
							if  (  mem_get_data(  &ptr,  &size_left_lineHeaderData,  tmpLen,  tmpBuf  )  )  goto  errLabel;
							pVsc->ucCompressors  =  tmpBuf[0];
							}
				  else  {
#ifdef  __DEBUG__
					  traceLog((TCHAR*)  _T(  "qvcf_read_streamInfo err. unprocessed dataType"  )  );
#endif
				  }
				  break;
			case  CONST_vcfDataType_ah:  {
				  VCF_streamInfo_ah  *  pVsa  =  (  VCF_streamInfo_ah  *  )p;
				  
				  //
				  int  tmpLen  =  size_left_lineHeaderData;
				  if  (  tmpLen  >  tmpBufSize  )  goto  errLabel;
				  if  (  mem_get_data(  &ptr,  &size_left_lineHeaderData,  tmpLen,  tmpBuf  )  )  goto  errLabel;
				  memcpy(  &pVsa->ah,  tmpBuf,  sizeof(  pVsa->ah  )  );
				  //
				  tmpLen  =  qyntohAudioHeader(  &pVsa->ah  );
				  //
				  int  ii  =  1;
				  }
				  break;
			case  CONST_vcfDataType_vh:  {
				  VCF_streamInfo_vh  *  pVsv  =  (  VCF_streamInfo_vh  *  )p;
				  //
				  int  tmpLen  =  size_left_lineHeaderData;
				  if  (  tmpLen  >  tmpBufSize  )  goto  errLabel;
				  if  (  mem_get_data(  &ptr,  &size_left_lineHeaderData,  tmpLen,  tmpBuf  )  )  goto  errLabel;
				  memcpy(  &pVsv->vh,  tmpBuf,  sizeof(  pVsv->vh  )  );

				  //
				  tmpLen  =  qyntohVideoHeader(  &pVsv->vh  );
				  }
				  break;		
			case  CONST_vcfDataType_spsPps:  {
				  VCF_streamInfo_spsPps  *  pVss  =  (  VCF_streamInfo_spsPps  *  )p;
				  VH_stream  vs  =  pVss->vh_stream;
				  //
				  int  spsPpsLen  =  size_left_lineHeaderData;
				  if  (  spsPpsLen  >  tmpBufSize  )  goto  errLabel;
				  if  (  mem_get_data(  &ptr,  &size_left_lineHeaderData,  spsPpsLen,  tmpBuf  )  )  goto  errLabel;
				  				  					  
				  //  2017/10/09
				  int  iFourcc  =  pVss->vh_stream.dwFourcc;
				  //
				  VH_stream  *  pVh_stream  =  &pVss->vh_stream;					
				  unsigned  int  spsLen  =  sizeof(  pVh_stream->mems[0].spsPps  );
				  unsigned  int  ppsLen  =  sizeof(  pVh_stream->mems[1].spsPps  );
				  if  (  parseSpsPps(  iFourcc,  (  char  *  )  tmpBuf,  spsPpsLen,  pVh_stream->mems[0].spsPps,  &spsLen,  pVh_stream->mems[1].spsPps,  &ppsLen,  NULL,  NULL  )  )  goto  errLabel;
				  pVh_stream->mems[0].usLen  =  spsLen;
				  pVh_stream->mems[1].usLen  =  ppsLen;
				  pVh_stream->usCnt  =  2;

				  }
				  break;		
			case  CONST_vcfDataType_usrName:  {
				  }
				  break;		
			default:		
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "unprocessed dataType"  )  );
				  #endif
				  break;
	}


	iErr  =  0;
errLabel:
	
	return  iErr;

}
#endif


//  帧头:	sym 2 + lineType 2 + lineHeaderDataLen  2  +  idInfo 8  +  tranNo 4 + mediaType 1  +  timestamp 8  +  uiSampleTimeInMs  4  +  pts 4 + len 4 
 int  qvcf_read_frame(  FILE  *  fp,  VCF_line_common  *  pLineCommon,  VCF_frame_header  *  p,  char  *  buf,  unsigned  int  *puiSize  )
{
	int  iErr  =  -1;
	char  *  ptr  =  buf;

	if  (  *puiSize  <  pLineCommon->usHeaderDataLen  )  {
#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "qvcf_read_streamInfo failed, bufSize < usHeaderDataLen"  )  );
#endif
		return  -1;
	}

	
	if  (  fread(  buf,  pLineCommon->usHeaderDataLen,  1,  fp  )  !=  1  )  goto  errLabel;
	
	//
	ptr  =  buf;
	unsigned  int  size_left_lineHeaderData; size_left_lineHeaderData = pLineCommon->usHeaderDataLen;
	
	//
	if  (  mem_get_64(  &ptr,  &size_left_lineHeaderData,  &p->idInfo.ui64Id  )  )  goto  errLabel;
	if  (  mem_get_32(  &ptr,  &size_left_lineHeaderData,  (  unsigned  long  *  )&p->uiTranNo  )  )  goto  errLabel;
	if  (  mem_get_data(  &ptr,  &size_left_lineHeaderData,  1,  &p->ucMediaType  )  )  goto  errLabel;
	unsigned  __int64  tmpl64; tmpl64 = 0;
	if  (  mem_get_64(  &ptr,  &size_left_lineHeaderData,  &tmpl64  )  )  goto  errLabel;
	p->timestamp  =  tmpl64;
	if  (  mem_get_32(  &ptr,  &size_left_lineHeaderData,  (  unsigned  long  *  )&p->uiSampleTimeInMs  )  )  goto  errLabel;
	if  (  mem_get_32(  &ptr,  &size_left_lineHeaderData,  (  unsigned  long  *  )&p->uiPts  )  )  goto  errLabel;
	if  (  mem_get_32(  &ptr,  &size_left_lineHeaderData,  (  unsigned  long  *  )&p->uiLen  )  )  goto  errLabel;
	//
	if  (  *puiSize  <  p->uiLen  )  goto  errLabel;
	//
	if  (  fread(  buf,  p->uiLen,  1,  fp  )  !=  1  )  goto  errLabel;
	
	//
	*puiSize  =  p->uiLen;

	iErr  =  0;
errLabel:
	
	return  iErr;

}
