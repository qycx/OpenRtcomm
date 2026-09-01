

#ifndef __ASRTEMP_H__
#define __ASRTEMP_H__	/* { */

#ifdef __cplusplus
 extern "C" {
#endif


#ifdef  __DEBUG__
  int	testInitQwmHookInMain( );
  int	testInitQwmHook(  );
#endif

#ifdef  __TEST__
  int	testQwmHook(  );
  int	testQwmRetrieveCfg(  QY_W_MON  *  pQwm  );
#endif


#ifdef __cplusplus
 }
#endif

#endif /* } */

