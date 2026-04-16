
#pragma	once


#ifdef  _DEBUG


#define  _CRTDBG_MAP_ALLOC
#include	<stdlib.h>
#include	<crtdbg.h>


#if  0	//  d3d出错了，只好暂时关闭。2014/09/23

#ifdef _DEBUG   
#ifndef DBG_NEW      
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )      
#define new DBG_NEW   
#endif
#endif  // _DEBUG

#endif


#endif




