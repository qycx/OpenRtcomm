
#ifndef __SPTRANSFORM_H__
#define __SPTRANSFORM_H__ / * { */

#define MARK_CENTER				1
#define MARK_MIRROR				2

#define TRANSLATE_TRANSFORM		3
#define ROTATE_TRANSFORM		4
#define DILATE_TRANSFORM		5
#define REFLECT_TRANSFORM		6



 extern int spMarkCenter( SP_STRUCT *pSp );
 extern int spMarkMirror( SP_STRUCT *pSp );

 extern int spTranslateTransform( SP_STRUCT *pSp );
 extern int spRotateTransform( SP_STRUCT *pSp );
 extern int spDilateTransform( SP_STRUCT *pSp );
 extern int spReflectTransform( SP_STRUCT *pSp );

 extern "C" int getRotateParm( short *pA180 );




#endif /* } __SPTRANSFORM_H__ defined */



