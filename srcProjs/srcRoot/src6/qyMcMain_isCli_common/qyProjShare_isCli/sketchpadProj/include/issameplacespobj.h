
#ifndef __ISSAMEPLACESPOBJ_H__
#define __ISSAMEPLACESPOBJ_H__ /* { */


#ifdef __cplusplus
 extern "C" {
#endif

extern BOOL isSamePlaceSpObj( SP_OBJ *pSpObj1, SP_OBJ *pSpObj2 );
extern BOOL isSamePlaceSpPoint( SP_POINT *pSpPoint1, SP_POINT *pSpPoint2 );
extern BOOL isSamePlaceSpSegment( SP_SEGMENT *pSpSegment1, SP_SEGMENT *pSpSegment2 );
extern BOOL isSamePlaceSpCircle( SP_CIRCLE *pSpCircle1, SP_CIRCLE *pSpCircle2 );


#ifdef __cplusplus
 }
#endif

#endif /* } __ISSAMEPLACESPOBJ_H__ defined */ 
