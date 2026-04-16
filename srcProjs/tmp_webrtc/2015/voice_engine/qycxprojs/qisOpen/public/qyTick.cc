
//#include	"stdafx.h"

#include	"webrtc\voice_engine\qycxprojs\qisOpen\include\qisPrecomp.h"

#include	<windows.h>
#include	<assert.h>
#include	<tchar.h>
#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif
	#include	<mmreg.h>
	#include	<MSAcm.h>
#endif
#include	<WinSock2.h>

#if  0
#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qyCommProc.h"
#endif

#include	"qmOpenCommon.h"

#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyq2.h"				//  2009/05/13

#if  0
#include	"qnmCommProc.h"
#include	"qnmCommProc_mis.h"
#include	"qyWmComm_is.h"
#endif

#include	"qyTick.h"



//
CQyTick::CQyTick(  )
		:mTimerMask(  0  )
{
	reset(  );
}

CQyTick::~CQyTick(  )
{
}

void  CQyTick::reset(  )
{
	//  Get the current process core mask
	DWORD_PTR  procMask;
	DWORD_PTR  sysMask;
	GetProcessAffinityMask(  GetCurrentProcess(  ),  &procMask,  &sysMask  );

	//  If procMask is 0, consider there is only one core available
	//  (  using 0 as procMask will cause an infinite loop below  )
	if  (  procMask  ==  0  )  procMask  =  1;

	//  Find the lowest core that this process uses
	if  (  mTimerMask  ==  0  )  {
		mTimerMask  =  1;
		while(  (  mTimerMask  &  procMask  )  ==  0  )  mTimerMask  <<=  1;
	}

	HANDLE  thread  =  GetCurrentThread(  );

	//  Set affinity th the first core
	DWORD_PTR oldMask = SetThreadAffinityMask(  thread,  mTimerMask  );

	//  Get the constant frequency
	QueryPerformanceFrequency(  &mFrequency  );

	//  Query the timer
	QueryPerformanceCounter(  &mStartTime  );
	mStartTick  =  GetTickCount(  );
	//  2012/02/07
	mStartTick_timeGetTime  =  timeGetTime(  );

	//  Reset affinity
	SetThreadAffinityMask(  thread, oldMask  );

	mLastTime  =  0;
	//  mZeroClock  =  clock(  );
}


unsigned  long  CQyTick::get_mStartTick(  )
{
	return  this->mStartTick;
}

unsigned  long  CQyTick::get_mStartTick_timeGetTime(  )
{
	return  this->mStartTick_timeGetTime;
}


unsigned long CQyTick::getMilliseconds(  )
{
	LARGE_INTEGER  curTime;
	HANDLE  thread  =  GetCurrentThread(  );

	//  Set affinity th the first core
	DWORD_PTR oldMask  =  SetThreadAffinityMask(  thread,  mTimerMask  );

	// Query the timer 
	QueryPerformanceCounter(  &curTime );

	//  Reset affinity
	SetThreadAffinityMask(  thread,  oldMask  );

	LONGLONG  newTime  =  curTime.QuadPart  -  mStartTime.QuadPart;

	//  scale by 1000 for milliseconds
	unsigned long newTicks  =  (  unsigned long  )  (  1000  *  newTime  /  mFrequency.QuadPart  );

	//  detect and compensate for performance counter leaps
	// ( surprisingly common,  see Microsoft KB:Q274323 )
	unsigned long check  =  GetTickCount(  )  -  mStartTick;
	signed long msecoff  =  (  signed  long  )  (  newTicks  -  check  );
	if  (  msecoff  <  -100  ||  msecoff  >  100  )  {
		//  we must keep the timer running forward:)
		LONGLONG adjust  =  min(  msecoff  *  mFrequency.QuadPart  /  1000,  newTime  -  mLastTime  );
		mStartTime.QuadPart  +=  adjust;
		newTime  -=  adjust;

		//  Re-calculate milliseconds
		newTicks  =  (  unsigned long  ) (  1000  *  newTime  /  mFrequency.QuadPart  );
	}

	//  Record last time for adjust
	mLastTime  =  newTime;
	return  newTicks;
}

unsigned  long CQyTick::getMicroseconds(  )
{
	LARGE_INTEGER  curTime;

	HANDLE  thread  =  GetCurrentThread(  );

	//  Set affinity th the first core
	DWORD_PTR  oldMask  =  SetThreadAffinityMask(  thread,  mTimerMask  );

	//  Query  the timer
	QueryPerformanceCounter(  &curTime  );

	//  Reset  affinity
	SetThreadAffinityMask(  thread,  oldMask  );

	LONGLONG  newTime  =  curTime.QuadPart  -  mStartTime.QuadPart;

	//  get milliseconds to check against GetTickCount
	unsigned long newTicks  =  (  unsigned long  ) (  1000 * newTime  /  mFrequency.QuadPart  );

	//  detect and compensate for performance counter leaps
	// ( surprisingly common,  see Microsoft KB:Q274323 )
	unsigned long check  =  GetTickCount(  )  -  mStartTick;
	signed long msecoff  =  (  signed  long  )  (  newTicks  -  check  );
	if  (  msecoff  <  -100  ||  msecoff  >  100  )  {
		//  we must keep the timer running forward:)
		LONGLONG adjust  =  min(  msecoff  *  mFrequency.QuadPart  /  1000,  newTime  -  mLastTime  );
		mStartTime.QuadPart  +=  adjust;
		newTime  -=  adjust;
	}

	//  Record last time for adjust
	mLastTime  =  newTime;

	//  scale by 1000000 for microseconds
	unsigned long newMicro  =  (  unsigned long  )  (  1000000  *  newTime  /  mFrequency.QuadPart  );
	return  newMicro;
}