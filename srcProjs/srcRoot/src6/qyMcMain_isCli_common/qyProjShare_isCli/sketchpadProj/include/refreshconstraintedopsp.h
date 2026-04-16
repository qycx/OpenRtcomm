

#ifndef __REFRESHCONSTRAINTEDOP_H__
#define __REFRESHCONSTRAINTEDOP_H__		/* { */

int refreshSpObjConstraintedOp( SP_STRUCT *pSp, Q_NODE * pQNode );

int refreshSpGenericPointConstraintOp( SP_STRUCT *pSp, Q_NODE *pConstraintQNode, Q_NODE *pQNode );
int refreshSpPointConstraintOp( SP_STRUCT *pSp, Q_NODE *pConstraintQNode, Q_NODE *pQNode );
int refreshSpIntersectPointConstraintOp( SP_STRUCT *pSp, Q_NODE *pConstraintQNode, Q_NODE *pQNode );
int refreshSpPointOnObjConstraintOp( SP_STRUCT *pSp, Q_NODE *pConstraintQNode, Q_NODE *pQNode );
int refreshSpReflectPointConstraintOp( SP_STRUCT *pSp, Q_NODE *pConstraintQNode, Q_NODE *pQNode );




#endif  /* __REFRESHCONSTRAINTEDOP_H__ defined */


