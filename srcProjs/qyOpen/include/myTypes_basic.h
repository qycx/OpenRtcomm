
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
//#define			__USE_atCommVer_1__		//  
//
//#define				__USE_atCommVer_2__		//  
//
#define			__USE_atCommVer_3__			//  


//
//#define	__USE_old_commService__


//
//
#ifdef  __USE_atCommVer_1__
		#define		__USE_atCommVer_1_old_proto__ 
#endif 

//
#ifdef  __USE_atCommVer_2__
		#define		__USE_atCommVer_2_old_proto__
#endif 



//
//
typedef  unsigned  char     atbyte;

//
typedef  unsigned  char		atbool;


//
typedef  long long          myint64;
typedef unsigned  long long myuint64;



//
#endif




#endif  //  }



