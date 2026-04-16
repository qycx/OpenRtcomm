

#ifndef  __saveAvProc_h__
#define  __saveAvProc_h__	//  {

//
#include	"qmOpenCommon.h"
//#include	"qnmCommProc_is_open.h"


//////////
#include	"qvcfDefs.h"
#include	"saveAvProc_open.h"





//
int  doFileHead_webm(  LPCTSTR  fileName,  int  iFourcc,  SAVE_av_procInfo  *  pSave  );
int  doFileEnd_webm(  int  iFourcc,  SAVE_av_procInfo  *  pSave  );
int  doFileFlush(  LPCTSTR  fileName,  SAVE_av_procInfo  *  pSave  );

int  doFileHead_h264(  LPCTSTR  fileName,  int  iFourcc,  SAVE_av_procInfo  *  pSave  );
int  doFileEnd_h264(  int  iFourcc,  SAVE_av_procInfo  *  pSave  );

int  doFileHead_qvcf(  void  *  pTransform,  LPCTSTR  fileName,  int  iFourcc,  SAVE_av_procInfo  *  pSave,  void  *  pCTX_mc_saveAv  );
int  doFileEnd_qvcf(  int  iFourcc,  SAVE_av_procInfo  *  pSave  );



//
char  *  qvcfVer(  );
int  qvcf_write_fileHeader(  char  *  ver,  char  *  buf,  unsigned  int  *puiSize,  FILE  *  fp  );
int  qvcf_write_streamInfo(  VCF_streamInfo_common  *  p,  char  *  buf,  unsigned  int  *puiSize,  FILE  *  fp  );




#endif  //  }


