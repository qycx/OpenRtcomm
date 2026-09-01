

#ifndef __SKETCHPADOBJ_H__
#define __SKETCHPADOBJ_H__ /* { */

#ifdef __cplusplus
 extern "C" {
#endif


#define SP_INVALID_TYPE							0
#define SP_POINT_TYPE							1
#define SP_SEGMENT_TYPE							2
#define SP_CIRCLE_TYPE							3
#define SP_GENERIC_TYPE							4
#define SP_ANGLE_BISECTOR_TYPE					5
#define SP_ANIMATOR_TYPE						6
#define SP_RECTANGLE_TYPE						7				//  2009/09/26

#define TOTAL_TYPES_OF_SP_OBJ					8

/* subTypes of SP_POINT_TYPE */

#define SP_GENERIC_POINT_TYPE					0
#define SP_INTERSECT_POINT_TYPE					1
#define SP_POINT_ON_OBJ_TYPE					2
#define SP_REFLECT_POINT_TYPE					3
#define SP_ROTATE_POINT_TYPE					4

#define TOTAL_SUB_TYPES_OF_SP_POINT				5

/* subTypes of SP_SEGMENT */

#define SP_GENERIC_SEGMENT_TYPE					0			// that means, two points gived to construct a segment 
#define SP_LINE_TYPE							1
#define SP_PERPENDICULAR_LINE_TYPE				2	
#define SP_REFLECT_SEGMENT_TYPE					3
#define SP_REFLECT_LINE_TYPE					4

#define TOTAL_SUB_TYPES_OF_SP_SEGMENT			5

/* subTypes of SP_CIRCLE_TYPE */
#define SP_GENERIC_CIRCLE_TYPE					0
#define SP_3POINTS_CIRCLE_TYPE					1
#define SP_CENTER_AND_RADIUS_CIRCLE_TYPE		2
#define SP_REFLECT_CIRCLE_TYPE					3

#define TOTAL_SUB_TYPES_OF_SP_CIRCLE			4

/* subTypes of SP_ANGLE_BISECTOR_TYPE */

#define SP_GENERIC_ANGLE_BISECTOR_TYPE			0

#define TOTAL_SUB_TYPES_OF_SP_ANGLE_BISECTOR	1

/* subTypes of SP_ANIMATOR_TYPE */
#define SP_GENERIC_ANIMATOR_TYPE				0

#define TOTAL_SUB_TYPES_OF_SP_ANIMATOR			1

//  2009/10/01
#define  SP_GENERIC_RECTANGLE_TYPE				0

#define  TOTAL_SUB_TYPES_OF_SP_RECTANGLE		1

#define TOTAL_SUB_TYPES_OF_SP_OBJ							\
			(	TOTAL_SUB_TYPES_OF_SP_POINT +				\
				TOTAL_SUB_TYPES_OF_SP_SEGMENT +				\
				TOTAL_SUB_TYPES_OF_SP_CIRCLE +				\
				TOTAL_SUB_TYPES_OF_SP_ANGLE_BISECTOR +		\
				TOTAL_SUB_TYPES_OF_SP_ANIMATOR  +			\
				TOTAL_SUB_TYPES_OF_SP_RECTANGLE				)

typedef  struct  __sp_rect_coord_t	{
				 short				x;
				 short				y;
}		 SP_RECT_COORD;

typedef  struct  __sp_polar_coord_t {
				 short				r;
				 short				a;
}		 SP_POLAR_COORD;

typedef  union  __sp_coord_t		{
				SP_RECT_COORD		rect;
				SP_POLAR_COORD		polar;
}		 SP_COORD;


typedef  struct  __sp_op_parm_t		{
				int					iFlg;				//  2009/09/28
				SP_RECT_COORD		move;
}		 SP_OP_PARM;

typedef  struct  __sp_move_tran_parm_t	{
				 SP_RECT_COORD			lastPlace;		/* refer to mouse */
				 SP_RECT_COORD			curPlace;		/* refer to mouse */
}		 SP_MOVE_TRAN_PARM;


typedef  struct  __spDriver_t  {
				 Q_NODE *pDriverQNode;
				 Q_NODE *pConstraintQNode;
}		 SP_DRIVER;


typedef  struct  __spParm_t  {
				 //  Q_NODE *pQNode;
}		 SP_PARM;


/**/
#define  SP_OBJ_COMMON_MEMS						\
			BYTE			type;				\
			BYTE			subType;			\
			BYTE			status;				\
			unsigned  int	uiTranNo;			\
			TCHAR			desc[32];			\
			BYTE			op;					\
			SP_OP_PARM		opParm;				\
												\
			SP_DRIVER		driver;
			

/**/


typedef  struct  __sp_obj_t  {
				 SP_OBJ_COMMON_MEMS	
}		 SP_OBJ;


typedef  struct  __sp_point_t  {
				 SP_OBJ_COMMON_MEMS
				 SP_COORD point;	
}		 SP_POINT;


typedef  struct  __sp_intersect_point_t  {
				 SP_OBJ_COMMON_MEMS
				 SP_COORD point;
	
				 Q_NODE *pQNode1;	/* the 2 qNode ptr contain 2 objs that intersect */
				 Q_NODE *pQNode2;

				 short posParm;		/* for point at the intersection of the segments */
									/*		posParm is not used */
									/* for of a segment and a circle, posParm refers to angle */
									/* for of circles, refers to direction */

}		 SP_INTERSECT_POINT;


typedef  struct  __sp_point_on_object_t  {
				 SP_OBJ_COMMON_MEMS
				 SP_COORD point;

				 Q_NODE *pObjQNode;
				 short posParm;		/* on a segment, it means distance from the first point */
									/* on a circle, it means polar angle */

}		 SP_POINT_ON_OBJ;


typedef  struct  __sp_reflect_point_t  {
				 SP_OBJ_COMMON_MEMS
				 SP_COORD point;

				 Q_NODE *pMirrorQNode;
				 Q_NODE *pReflectedQNode;
	
}		 SP_REFLECT_POINT;


typedef  struct  __sp_rotate_point_t  {
				 SP_OBJ_COMMON_MEMS
				 SP_COORD point;

				 Q_NODE *pCenterQNode;
				 Q_NODE *pRotatedQNode;

				 short A180;	/* angle degree represented by 180 */

}		 SP_ROTATE_POINT;


typedef  struct  __sp_segment_t  {
				 SP_OBJ_COMMON_MEMS

				 /* point1,point2 not used now */
				 SP_COORD		point1;
				 SP_COORD		point2;
				 /* point1,point2 not used now */

				 Q_NODE		*	pStartQNode;
				 Q_NODE		*	pEndQNode;
				 BOOL			bOwner_pStartQNode;
				 BOOL			bOwner_pEndQNode;

				 unsigned  char	 ucbHorizontal;				//  2009/09/25
				 unsigned  char  ucbVertical;				//  2009/09/25
	
}		 SP_SEGMENT;


typedef  struct  __sp_line_t  {
				 SP_OBJ_COMMON_MEMS

				 SP_COORD point1;
				 SP_COORD point2;

				 Q_NODE *pQNode1;
				 Q_NODE *pQNode2;
	
}		 SP_LINE;


typedef  struct  __sp_perpendicular_line_t  {
				 SP_OBJ_COMMON_MEMS
				 SP_COORD point1;
				 SP_COORD point2;

				 Q_NODE *pSpPointQNode;
				 Q_NODE *pSpSegmentQNode;

}		 SP_PERPENDICULAR_LINE;

typedef  struct  __sp_reflected_segment_t  {
				 SP_OBJ_COMMON_MEMS
				 SP_COORD point1;
				 SP_COORD point2;

				 Q_NODE *pMirrorQNode;
				 Q_NODE *pReflectedQNode;
		
}		 SP_REFLECT_SEGMENT;


typedef  struct  __sp_reflected_line_t  {
				 SP_OBJ_COMMON_MEMS
				 SP_COORD point1;
				 SP_COORD point2;

				 Q_NODE *pMirrorQNode;
				 Q_NODE *pReflectedQNode;
		
}		 SP_REFLECT_LINE;





typedef  struct  __sp_circle_t {
				 SP_OBJ_COMMON_MEMS
	
				 Q_NODE		*	pCenterQNode;			/* point at center */
				 Q_NODE		*	pCircleQNode;			/* point on circle */
				 BOOL			bOwner_pCenterQNode;
				 BOOL			bOwner_pCircleQNode;
		
}		 SP_CIRCLE;

typedef  struct  __sp_3points_circle_t  {
				 SP_OBJ_COMMON_MEMS
	
				 Q_NODE *pCenterQNode;	/* point at center */
				 Q_NODE *pCircleQNode1;	/* point on circle */
				 Q_NODE *pCircleQNode2;	/* point on circle */
				 Q_NODE *pCircleQNode3;	/* point on circle */
		
}		 SP_3POINTS_CIRCLE;

typedef  struct  __sp_center_and_radius_circle_t  {
				 SP_OBJ_COMMON_MEMS
	
				 Q_NODE *pCenterQNode;	/* point at center */
				 short r;
	
}		 SP_CENTER_AND_RADIUS_CIRCLE;

//  2009/09/26
typedef  struct  __sp_rectangle_t  {
				 SP_OBJ_COMMON_MEMS

				 /* point1,point2 not used now */
				 //  SP_COORD		point0;
				 //  SP_COORD		point1;
				 /* point1,point2 not used now */

				 Q_NODE		*	pQNode_points[4];
				 BOOL			bOwner_points[4];
	
				 Q_NODE		*	pQNode_segments[4];
				 BOOL			bOwner_segments[4];

}		 SP_RECTANGLE;


//
typedef struct __sp_angle_bisector_t {

	SP_OBJ_COMMON_MEMS
	
	Q_NODE *p1, *p2, *p3;
	SP_RECT_COORD rayPoint;	/* used to draw a ray from p2, rayPoint is a forwarder */
		
} SP_ANGLE_BISECTOR;


typedef struct __sp_hyperbola_t {

	SP_OBJ_COMMON_MEMS

	Q_NODE *pFocus1, *pFocus2, *p3;
	short a, b;

} SP_HYPERBOLA;


typedef struct __sp_animated_point_t {

	Q_NODE *pPointQNode;
	Q_NODE *pPathQNode;
	char v;
	BYTE status;

	SP_MOVE_TRAN_PARM parm;

} SP_ANIMATED_POINT;


typedef struct __sp_animator_t {
	
	SP_OBJ_COMMON_MEMS
	
	SP_ANIMATED_POINT sAP[SP_MAX_ANIMATED_POINT];

} SP_ANIMATOR;




typedef union __sp_tran_parm_t {

	SP_MOVE_TRAN_PARM move;

	struct {
		SP_RECT_COORD firstCorner;
	} drawARgn;

} SP_TRAN_PARM;

typedef  struct  __sp_select_q_elem_t  {
				 Q_NODE				*	pQNode;
}		 SP_SELECT_Q_ELEM;

typedef  struct  __spOpedQElem_t		{
				 Q_NODE				*	pQNode;
}		 SP_OPED_Q_ELEM;

typedef  struct  __sp_struct_t			{

				 unsigned  short		spWidth;
				 unsigned  short		spHeight;

				 GENERIC_Q			*	pSpObjQ;
				 GENERIC_Q			*	pNewSpObjQ;
				 GENERIC_Q			*	pSelectedSpObjQ;

				 GENERIC_Q			*	pOpedSpObjQ;				//  added to store temporary info 

				 unsigned  char			sysStatus;

				 unsigned  char			errNo;
				 unsigned  char			tranType; 
	
				 Q_NODE				*	pCenterQNode;
				 Q_NODE				*	pMirrorQNode;

				 Q_NODE				*	curpProcQNode;

				 BYTE					op;
				 BYTE					isPreOped;

				 SP_TRAN_PARM			tranParm;
		
				 TCHAR					info[SP_MAX_INFO_LEN+1];
	
				 BOOL					isCaptured;
				 BOOL					isCapturedForAnimation;
				 
				 //
				 BOOL					bHideAll;					//  2009/
	
				 //
				 unsigned  char			ucbEditable;				//  2018/07/05

				 //
				 long					uiTranNo;					//  2009/10/02

}		 SP_STRUCT;


#ifdef __cplusplus
 }
#endif




#endif /* } __SKETCHPADOBJ_H__ */

