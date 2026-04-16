
#ifndef __SKETCHPADDISPLAY_H__
#define __SKETCHPADDISPLAY_H__ /* { */

#ifdef __cplusplus
 extern "C" {
#endif

typedef  struct  __display_dev_t		{	
				 void				*	pSp;
				
				 HDC					hDc;

				 //
				 unsigned  char			ucbFullScreen;		//  2018/07/05
	
}		 DISPLAY_DEV;

__declspec(  dllexport  )  int spDisplay( DISPLAY_DEV *pDisplayDev, SP_STRUCT *pSp );
extern int spDisplayObj( DISPLAY_DEV *pDisplayDev, SP_OBJ *pSpObj, int flag );
extern int spDisplayPoint( DISPLAY_DEV *pDisplayDev, SP_POINT *pSpPoint, int flag );
extern int spDisplaySegment( DISPLAY_DEV *pDisplayDev, SP_SEGMENT *pSegment, int flag );
extern int spDisplayCircle( DISPLAY_DEV *pDisplayDev, SP_CIRCLE *pCircle, int flag );
extern int spDisplayAngleBisector( DISPLAY_DEV *pDisplayDev, SP_ANGLE_BISECTOR *pSAB, int flag );


#ifdef __cplusplus
 }
#endif


#endif /* } __SKETCHPADDISPLAY_H__ */
