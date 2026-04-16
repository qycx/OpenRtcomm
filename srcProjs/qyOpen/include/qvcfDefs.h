

#ifndef  __qvcfDefs_h__
#define  __qvcfDefs_h__	//  {


//  2015/05/09. 用自己的格式来存储.
//  文件头:	QVCF + ver 4 + headerSize 2 + sth
//  流头:	sym 2 + lineType 2 + lineHeaderDataLen  2  +  idInfo 8  +  tranNo 4 + mediaType 1  +  detaType  2  +  a waveformat +  extra data
//  流头:	sym 2 + lineType 2 + lineHeaderDataLen  2  +  idInfo 8  +  tranNo 4 + mediaType 1  +  detaType  2  +  v bih +  extra data
//  流头:	sym 2 + lineType 2 + lineHeaderDataLen  2  +  idInfo 8  +  tranNo 4 + mediaType 1  +  detaType  2  +  spspps
//  流头:	sym 2 + lineType 2 + lineHeaderDataLen  2  +  idInfo 8  +  tranNo 4 + mediaType 1  +  detaType  2  +  usrName
//  帧头:	sym 2 + lineType 2 + lineHeaderDataLen  2  +  idInfo 8  +  tranNo 4 + mediaType 1  +  timestamp 8  +  pts 4 + len 4 
//  帧内容：数据
//  注：
//  文件头中，headerSize指整个头的长度（包含QVCF)
//  其他的都是  lineHeaderCommon + lineHeaderData 
//  帧内容的长度由帧头的len决定，不包含在lineHeaderDataLen里
//	sym表示一行的起头，起分隔符的作用。
//  lineType表示这一行的类型，是流头，还是帧
//  lineHeaderDataLen表示跟在lineHeaderDataLen后的header data的长度.
//  mediaType表示是音频还是视频
//  注2：以网络字节顺序存储
//  ver: vwfVer(  )
//

//
#define		CONST_vcfFile_sym				"qvcf"
#define		CONST_vcfFile_symLen			4
#define		CONST_vcfFile_verLen			4

//
#define		CONST_vcfFile_headerSize		32

//
typedef  struct  __vcf_fileHeader_t			{
				 char						sym[CONST_vcfFile_symLen  +  1];
				 char						ver[CONST_vcfFile_verLen  +  1];
				 unsigned  short			usHeaderSize;
}		 VCF_file_header;




//
#define		CONST_vcfLine_sym					"vc"
#define		CONST_vcfLine_symLen				2
//
#define		CONST_vcfLineType_streamInfo		1
#define		CONST_vcfLineType_frame				2
//
#define		CONST_vcfMediaType_a				CONST_mediumType_audio		//  1
#define		CONST_vcfMediaType_v				CONST_mediumType_video		//  2
#define		CONST_vcfMediaType_usrData			CONST_mediumType_usrData	//  3

//
#define		CONST_vcfDataType_ah				1
//
#define		CONST_vcfDataType_vh				10
#define		CONST_vcfDataType_spsPps			11
//
#define		CONST_vcfDataType_ucCompressors		20
//
#define		CONST_vcfDataType_usrName			100


//
#define		M_vcfLine_commonMems				unsigned  char  lineSym[2];  unsigned  short  usLineType;  unsigned  short  usHeaderDataLen;			

#define		CONST_vcfLineCommon_len				6

//
#define		M_vcfStreamInfo_commonMems			M_vcfLine_commonMems	\
				 QY_MESSENGER_ID				idInfo;					\
				 unsigned  int					uiTranNo;				\
				 unsigned  char					ucMediaType;			\
				 unsigned  short				usDataType;


//
typedef  struct  __vcfLine_common_t				{
				 M_vcfLine_commonMems
}		 VCF_line_common;
//
typedef  struct  __vcfStreamInfo_common_t		{
				 M_vcfStreamInfo_commonMems
}		 VCF_streamInfo_common;

//
typedef  struct  __vcfStreamInfo_ucCompressors_t	{
				 M_vcfStreamInfo_commonMems
				 //
				 unsigned  char  ucCompressors;
}		 VCF_streamInfo_ucCompressors;

//  2015/05/09
typedef  struct  __vcfStreamInfo_ah_t			{
				 M_vcfStreamInfo_commonMems
				 QY_AUDIO_HEADER				ah;
}		 VCF_streamInfo_ah;

//  2015/05/09
typedef  struct  __vcfStreamInfo_vh_t			{
				 M_vcfStreamInfo_commonMems
				 QY_VIDEO_HEADER				vh;
}		 VCF_streamInfo_vh;


//  spspps
typedef  struct  __vcfStreamInfo_spsPps_t		{
				 M_vcfStreamInfo_commonMems
				 VH_stream											vh_stream;											//  2014/02/25				 
}		 VCF_streamInfo_spsPps;


typedef  union  __vcfStreamInfoU_t				{
				VCF_streamInfo_common			common;
				VCF_streamInfo_ucCompressors	ucCompressors;
				VCF_streamInfo_ah				ah;
				VCF_streamInfo_vh				vh;
				VCF_streamInfo_spsPps			spsPps;
}		 VCF_streamInfo_u;

//
//  帧头:	sym 2 + lineType 2 + lineHeaderDataLen  2  +  idInfo 8  +  tranNo 4 + mediaType 1  +  timestamp 8  +  uiSampleTimeInMs  4  +  pts 4 + len 4 
typedef  struct  __vcfFrameHeader_t				{
				 M_vcfLine_commonMems
				 QY_MESSENGER_ID				idInfo;					
				 unsigned  int					uiTranNo;				
				 unsigned  char					ucMediaType;			
				 time_t							timestamp;
				 unsigned  int					uiSampleTimeInMs;
				 unsigned  int					uiPts;
				 unsigned  int					uiLen;
}		 VCF_frame_header;



int  qvcf_write_fileHeader(  char  *  ver,  char  *  buf,  unsigned  int  *puiSize,  FILE  *  fp  );
int  qvcf_write_streamInfo(  VCF_streamInfo_common  *  p,  char  *  buf,  unsigned  int  *puiSize,  FILE  *  fp  );
int  qvcf_write_frameInfo(  VCF_frame_header  *  p,  char  *  data,  unsigned  int  dataLen,  char  *  buf,  unsigned  int  *puiSize,  FILE  *  fp  );

//
int  qvcf_read_fileHeader(  FILE  *  fp,  VCF_file_header  *  p    );
int  qvcf_readLineCommon(  FILE  *  fp,  VCF_line_common  *  p  );
int  qvcf_read_streamInfo(  FILE  *  fp,  VCF_line_common  *  pLineCommon,  char  *  buf,  unsigned  int  uiSize,  VCF_streamInfo_common  *  p  );
int  qvcf_read_frame(  FILE  *  fp,  VCF_line_common  *  pLineCommon,  VCF_frame_header  *  p,  char  *  buf,  unsigned  int  *puiSize  );


#endif  //  }



