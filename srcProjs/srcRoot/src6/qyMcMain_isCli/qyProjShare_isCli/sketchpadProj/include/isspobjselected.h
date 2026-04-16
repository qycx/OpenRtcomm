
#ifndef __ISSPOBJSELECTED_H__
#define __ISSPOBJSELECTED_H__ /* { */

#ifdef __cplusplus
 extern "C" {
#endif

extern BOOL isSpObjSelected( SP_OBJ *pSpObj, SP_RECT_COORD *pPoint );
extern BOOL isSpPointSelected( SP_POINT *pSpPoint, SP_RECT_COORD *pHere );
extern BOOL isSpSegmentSelected( SP_SEGMENT *pSpSegment, SP_RECT_COORD *pPoint );
extern BOOL isSpCircleSelected( SP_CIRCLE *pSpCircle, SP_RECT_COORD *pPoint );

#ifdef __cplusplus
 }
#endif



#endif /* } __ISSPOBJSELECTED_H__ defined */

