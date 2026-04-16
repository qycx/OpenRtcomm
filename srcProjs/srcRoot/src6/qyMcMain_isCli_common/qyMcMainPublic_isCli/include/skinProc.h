
#ifndef  __skinProc_h__
#define  __skinProc_h__   //  {

//
//#define  __USE_skin__


// HitTest Constants
#define DHT_CLOSE		0x01
#define DHT_CAPTION		0x02
#define DHT_MIN			0x03
#define DHT_MAX			0x04


//
#define LIGHT_COLOR		250
#define DARK_COLOR		100


//
typedef  struct  __skinProc_t  {
        int				i;

            RECT m_rcClose, m_rcMax, m_rcMin;
    DWORD m_LastHit;
    DWORD m_ButtonDown;

    TCHAR  title[128];

}		SKIN_proc;




#endif  //  }


