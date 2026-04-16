

#ifndef  __QYTICK_H__
#define  __QYTICK_H__

#include "windows.h"

//  namespace  Ogre
//  {
	class  /*_OgreExport*/  CQyTick
	{
	private:
		//  clock_t			mZeroClock;
		DWORD			mStartTick;
		//
		DWORD			mStartTick_timeGetTime;		//  2012/02/07
		//
		LONGLONG		mLastTime;
		LARGE_INTEGER	mStartTime;
		LARGE_INTEGER	mFrequency;
		DWORD_PTR		mTimerMask;
	public:
		CQyTick(  );
		~CQyTick(  );

		void  reset(  );
		unsigned  long  get_mStartTick(  );
		unsigned  long  get_mStartTick_timeGetTime(  );
		unsigned  long  getMilliseconds(  );
		unsigned  long  getMicroseconds(  );
	};
//  }


//  2012/02/07
#define		M_GetTickCount_av(  tickObj  )			myGetTickCount(  NULL  )	//  (  (  tickObj  ).getMilliseconds(  )  +  (  tickObj  ).get_mStartTick(  )  )
#define		M_timeGetTime(  tickObj  )				myGetTickCount(  NULL  )	//  (  (  tickObj  ).getMilliseconds(  )  +  (  tickObj  ).get_mStartTick_timeGetTime(  )  )

#define		M_GetTickCount_audio(  tickObj  )		myGetTickCount(  NULL  )	//  timeGetTime(  )			//  GetTickCount(  )
#define		M_GetTgt_video(  tickObj  )				myGetTickCount(  NULL  )	//  timeGetTime(  )			//  GetTickCount(  )


#endif 



