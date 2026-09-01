


#ifndef  __showInfo_open_h__
#define  __showInfo_open_h__	//  {

//
#ifdef  __cplusplus
  extern  "C"  {
#endif



//
__declspec(  dllexport  )  int  set_who_showInfo(  LPCTSTR  name  );
__declspec(  dllexport  )  int  showInfo_open0(  void  *  p0,  LPCTSTR  tWhere,  LPCTSTR  hint  );
__declspec(  dllexport  )  int  showInfo2_open(  void  *  p0,  LPCTSTR  tWhere,  LPCTSTR  hint0,  LPCTSTR  hint1  );


//
 __declspec(  dllexport  )  int  qyShowInfo1(  int  iShowType,  unsigned  int  *  puiStep,  char  *  clientIp,  LPCWSTR  who_from,  LPCWSTR  who_to,  LPCWSTR  where,  LPCWSTR  doStr,  LPCWSTR  fmt,  ...  );


//
#ifdef  __cplusplus
  }
#endif



#endif  //  }


