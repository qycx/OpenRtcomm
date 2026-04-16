
#ifndef __SKETCHPADPROC_H__
#define __SKETCHPADPROC_H__ /* { */

#ifdef __cplusplus
 extern "C" {
#endif


__declspec(  dllexport  )  int spProcLButtonDown( SP_STRUCT *pSp, SP_RECT_COORD *pPoint, unsigned int iFlags );
__declspec(  dllexport  )  int spProcLButtonUp( SP_STRUCT *pSp, SP_RECT_COORD *pPoint, unsigned int iFlags );
__declspec(  dllexport  )  int spProcMouseMove( SP_STRUCT *pSp, SP_RECT_COORD *pPoint, unsigned int iFlags );
extern int spProcConstruct( SP_STRUCT *pSp, int option );
extern int spProcTransform( SP_STRUCT *pSp, int option );
__declspec(  dllexport  )  int spProcKeyDelete( SP_STRUCT *pSp, unsigned int iFlags );
extern int spProcDisCmd( SP_STRUCT *pSp, int option );




#ifdef __cplusplus
 }
#endif

#endif /* } __SKETCHPADPROC_H__ defined */

