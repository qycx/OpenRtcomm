
#ifndef __SKETCHPADCONSTRUCT_H__
#define __SKETCHPADCONSTRUCT_H__	/* { */

#ifdef __cplusplus
 extern "C" {
#endif


/* options of command construct */
#define CONSTRUCT_ANGLE_BISECTOR		1
#define CONSTRUCT_PERPENDICULAR_LINE	2
#define CONSTRUCT_LINE					3
#define CONSTRUCT_HYPERBOLA				4


extern int spConstructLine( SP_STRUCT *pSp );
extern int spConstructPerpendicularLine( SP_STRUCT *pSp );
extern int spConstructAngleBisector( SP_STRUCT *pSp );
extern int spConstructHyperbola( SP_STRUCT *pSp );


#ifdef __cplusplus
 }
#endif



#endif /* } __SKETCHPADCONSTRUCT_H__ */