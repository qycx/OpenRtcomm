
#ifndef  __myPLayAudioData_h__
#define  __myPlayAudioData_h__	//  {





//  2009/05/19
struct  __myPlayAudioData_t								{
				 unsigned  int										uiType;
				 
				 //  
				 long												lPktId_getNewPkt;						//  2015/02/13.???????. ???????
				 
				 //
				 TRANSFER_AUDIO_dataMemHead							head;

				 //
				 unsigned  int										uiSize_dec;								//  2016/12/10
				 QY_AUDIO_HEADER									ah;										//  2016/12/06

				 //  char									*		pBuf;									//  2009/12/12
				 QY_MEMORY											memory;									//  2010/04/23

				 //
				 //char												buf[1];

};











#endif  //  }


