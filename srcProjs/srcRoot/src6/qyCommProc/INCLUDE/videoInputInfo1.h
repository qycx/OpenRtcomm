
#ifndef  __videoInputInfo1_h__
#define  __videoInputInfo1_h__		//  {

//
typedef  struct												{
				VIDEO_input_info							videoInputInfo;

				//								 //
				int											n_ok_thisSecond;

				//
				unsigned  int								uiNeedSkipped;

				//
				struct {
					DWORD									dwTickCnt_startToCalc;
					int										nTotal_toCalc;
					//
				}											toGetFps;

				//
}		VIDEO_input_info1;



#endif  //  }


