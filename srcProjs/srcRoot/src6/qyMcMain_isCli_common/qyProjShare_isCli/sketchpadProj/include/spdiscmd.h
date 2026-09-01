
#ifndef __SPDISCMD_H__
#define __SPDISCMD_H__ /* { */


#ifdef __cplusplus
 extern "C" {
#endif

/* options of command display */
#define DISCMD_ANIMATE	1


extern int spDisCmdAnimate( SP_STRUCT *pSp );
extern int spDisCmdTimer( SP_STRUCT *pSp );
extern int getNextPosOnSegment( SP_ANIMATED_POINT *pSAP, SP_RECT_COORD *pPoint );
extern int animateToPath( SP_STRUCT *pSp, SP_ANIMATED_POINT *pSAP );
extern int animateOnPath( SP_STRUCT *pSp, SP_ANIMATED_POINT *pSAP );

extern int getNextPosOnPath( SP_ANIMATED_POINT *pSAP, SP_RECT_COORD *pPoint );



#ifdef __cplusplus
 }
#endif

#endif /* } __SPDISCMD_H__ defined */

