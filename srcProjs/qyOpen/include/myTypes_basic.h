
#ifndef  __myTypes_basic_h__
#define  __myTypes_basic_h__	//  {



//
#define  __USE_myTypes__


#ifdef  __USE_myTypes__


//
typedef  unsigned char		byte;
typedef  unsigned short		ushort;
typedef  unsigned int		uint;

//
//#define     __USE_atbyte_short__    

//
//#define			__USE_atCommVer_1__		//  



//
//
#ifdef  __USE_atCommVer_1__
		#define		__USE_atCommVer_1_old_proto__ 
#endif 



//
#ifdef  __USE_atbyte_short__
typedef  unsigned  short     atbyte;
#else 
typedef  unsigned  char     atbyte;
#endif 

//
typedef  long long          myint64;
typedef unsigned  long long myuint64;


//
#endif




#endif  //  }



