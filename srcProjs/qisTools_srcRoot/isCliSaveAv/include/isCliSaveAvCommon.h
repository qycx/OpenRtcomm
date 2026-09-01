

#ifndef  __isCliSaveAvCommon_h__
#define  __isCliSaveAvCommon_h__	//  {

#include	<tchar.h>
#include	<mmreg.h>



//
#include	"qmOpenCommon.h"
#include	"saveAvProc_open.h"




//
typedef  struct  __aStreamMem_t		{
				 QY_MESSENGER_ID	idInfo;
				 unsigned  int		tn_openAvDev;
				 //
				 FILE* fp;

				 //
				 DWORD				dwTickCnt_lastWrite;

				 bool  flag;

				 long startTime;
				 unsigned  int firstTime;
				 long count;
				 long diff;

				 char     fileNamePure[256];

				 //
#define		CONST_bufSize_a_cacheBuf		4  *  1000  *  1000
				 //
				 struct {
					 char					buf[CONST_bufSize_a_cacheBuf];
					 int					bufSize;
					 int					uiLen;
				 }							cache;

				 //
}		 AStreamMem;

//
#define		MAX_aStreamMems			50

//
typedef  struct  _aStreams_t		{
				 AStreamMem			mems[MAX_aStreamMems];	
}		 AStreams;


//
typedef  struct				{
	
	//
	SAVE_av_procInfo		common;

	//
	struct {
		AStreams			aStreams;
	}						audio;
	//
	struct					{
		TCHAR				vFileName[256];
		FILE			*	fp;
		
		//
		TCHAR				fileName[256];
		char                fileNamePure[256];
		time_t				tStartToSave;

		long            startTime;
		long            firstTime;
		long            count;

		bool  flag;

		//
#define		CONST_bufSize_v_cacheBuf		8  *  1000  *  1000
		//
		struct {
			char				buf[CONST_bufSize_v_cacheBuf];
			int					bufSize;
			int					uiLen;
		}						cache;

		//
	}						video;

	//
}  mySAVE_av_procInfo;


//
int mixFiles(mySAVE_av_procInfo* pSave, TCHAR* tmpDir, TCHAR* mixFileName);




//
#endif  //  }


