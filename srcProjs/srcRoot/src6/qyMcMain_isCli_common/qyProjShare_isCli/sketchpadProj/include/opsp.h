
#ifndef __CONSTRAINSKETCHPAD_H__
#define __CONSTRAINSKETCHPAD_H__ /* { */

#ifdef __cplusplus
 extern "C" {
#endif



__declspec(  dllexport  )   int opSp( SP_STRUCT *pSp );
extern int opSpObj( SP_STRUCT *pSp, SP_OBJ *pSpObj );

extern int opNull( SP_STRUCT *pSp, SP_OBJ *pSpObj );

/* op functions of points */
extern int opSpGenericPoint( SP_STRUCT *pSp, SP_POINT *pSpPoint );
extern int opSpIntersectPoint( SP_STRUCT *pSp, SP_INTERSECT_POINT *pSpPoint );
extern int opSpPointOnObj( SP_STRUCT *pSp, SP_POINT_ON_OBJ *pSpPoint );
extern int opSpReflectPoint( SP_STRUCT *pSp, SP_REFLECT_POINT *pSpPoint );
extern int opSpRotatePoint( SP_STRUCT *pSp, SP_ROTATE_POINT *pSpPoint );


/* op functions of segments */
extern int opSpGenericSegment( SP_STRUCT *pSp, SP_SEGMENT *pSpSegment );
extern int opSpLine( SP_STRUCT *pSp, SP_LINE *pSpLine );
extern int opSpPerpendicularLine( SP_STRUCT *pSp, SP_PERPENDICULAR_LINE *pSPL );
extern int opSpReflectSegment( SP_STRUCT *pSp, SP_REFLECT_SEGMENT *pSpReflectSegment );
extern int opSpReflectLine( SP_STRUCT *pSp, SP_REFLECT_LINE *pSpReflectLine );


/* op functions of circles */
extern int opSpGenericCircle( SP_STRUCT *pSp, SP_CIRCLE *pSAB );

/* op functions of misc objs */
extern int opSpGenericAngleBisector( SP_STRUCT *pSp, SP_ANGLE_BISECTOR *pSAB );

/* op functions of animators */
extern int opSpGenericAnimator( SP_STRUCT *pSp, SP_ANIMATOR *pSA );

extern int opSpGenericRectangle( SP_STRUCT *pSp, SP_RECTANGLE *pSA );

typedef int ( *OP_FUNC )( SP_STRUCT *pSp, void *pSpObj );
 
extern OP_FUNC getOpFunc( BYTE type, BYTE subType );


#ifdef __cplusplus
 }
#endif

#endif /* } __CONSTRAINSKETCHPAD_H__ defined */

