
#include	"stdafx.h"
#include	"sp.h"


 char debugStr[1024];

 int printInfo( char *fmt, ... )
{
 	va_list args;

	static int i = 0;
	
	va_start(args,fmt);

	sprintf( debugStr, "%d: ", i );
	
	_vsnprintf( debugStr, sizeof( debugStr )-strlen( debugStr )-1, fmt, args );
	debugStr[sizeof( debugStr ) - 1] = 0;
	
	i ++;

	va_end(args);

	return 0;

}

 int printQ( GENERIC_Q *pQ )
{
	 
	 int iErr = 0;

#ifdef __SP_DEBUG__
	
	 SP_OBJ *pSpObj;
	 Q_NODE *pQNode;

	 debugLog( "printQ():starts..." );
	
	 for ( pQNode = pQ->front.pNext; pQNode; pQNode = pQNode->pNext ) {
	
		 pSpObj = ( SP_OBJ * )pQNode->qElemMemory.m_pBuf;
		 printSpObj( pSpObj );

	 }

	 debugLog( "printQ():ends." );

#endif

	 return iErr;

}

 int printSelectedQ( GENERIC_Q *pQ )
{

#ifdef __SP_DEBUG__

	 Q_NODE *pQNode;
	 SP_OBJ *pSpObj;

	 debugLog( "printSelectedQ:1" );
	 for ( pQNode = pQ->front.pNext; pQNode; pQNode = pQNode->pNext ) {
		 pSpObj = ( SP_OBJ * )( ( SP_SELECT_Q_ELEM * )pQNode->qElemMemory.m_pBuf )->pQNode->qElemMemory.m_pBuf;
		 printSpObj( pSpObj );
	 }
	
	 debugLog( "printSelectedQ:2" );

#endif

	 return 0;

}

 extern char *showSpObjStatus( BYTE status );

 int printSpObj( void *p )
{

#ifdef __SP_DEBUG__

	 char buf[1024];
	 SP_OBJ *pSpObj = (  SP_OBJ  *  )p;

	 
	 sprintf( buf, "type=[%s],op=[%s],opParm=(%d,%d),status=[%s]", 
		 showSpObjType( pSpObj->type, pSpObj->subType ), showSpObjOp( pSpObj->op ), pSpObj->opParm.move.x, pSpObj->opParm.move.y, showSpObjStatus( pSpObj->status ) );
	 
	 switch ( pSpObj->type ) {
	
		case SP_POINT_TYPE:
		
			sprintf( buf, "%s:pos (%d,%d)", buf, ( ( SP_POINT * )pSpObj )->point.rect.x, ( ( SP_POINT * )pSpObj )->point.rect.y );
			
			break;

		default:
			
			break;
	 
	 }
	 debugLog( "%s", buf );

	 spShowInfo( buf );

#endif

	 return 0;

}

 char *showSpObjType( BYTE type, BYTE subType )
{
	 static char buf[1024];

	 strcpy( buf, "" );

	 switch ( type ) {

		case SP_POINT_TYPE:

			if ( subType == SP_GENERIC_POINT_TYPE ) 
				strcat( buf, "SP_GENERIC_POINT_TYPE" );
			else if ( subType == SP_INTERSECT_POINT_TYPE )
				strcat( buf, "SP_INTERSECT_POINT_TYPE" );
			else if ( subType == SP_POINT_ON_OBJ_TYPE )
				strcat( buf, "SP_POINT_ON_OBJ_TYPE" );
			else if ( subType == SP_REFLECT_POINT_TYPE )
				strcat( buf, "SP_REFLECT_POINT_TYPE" );
			else 
				strcat( buf, "SP_POINT:subType error" );

			break;
			
		case SP_SEGMENT_TYPE:

			if ( subType == SP_GENERIC_SEGMENT_TYPE )
				strcat( buf, "SP_GENERIC_SEGMENT_TYPE" );
			else if ( subType == SP_LINE_TYPE )
				strcat( buf, "SP_LINE_TYPE" );
			else if ( subType == SP_PERPENDICULAR_LINE_TYPE )
				strcat( buf, "SP_PERPENDICULAR_LINE_TYPE" );
			else if ( subType == SP_REFLECT_SEGMENT_TYPE )
				strcat( buf, "SP_REFLECT_SEGMENT_TYPE" );
			else if ( subType == SP_REFLECT_LINE_TYPE )
				strcat( buf, "SP_REFLECT_LINE_TYPE" );
			else 
				strcat( buf, " SP_SEMGNET:subType error" );

			break;

		case SP_CIRCLE_TYPE:

			if ( subType == SP_GENERIC_CIRCLE_TYPE )
				strcat( buf, "SP_GENERIC_CIRCLE_TYPE" );
			else if ( subType == SP_3POINTS_CIRCLE_TYPE )
				strcat( buf, "SP_3POINTS_CIRCLE_TYPE" );
			else if ( subType == SP_CENTER_AND_RADIUS_CIRCLE_TYPE )
				strcat( buf, "SP_CENTER_AND_RADIUS_CIRCLE_TYPE" );
			else
				strcat( buf, "SP_CIRCLE:subType error" );

			break;

		
		case SP_ANGLE_BISECTOR_TYPE:

			if ( subType == SP_GENERIC_ANGLE_BISECTOR_TYPE )
				strcat( buf, "SP_GENERIC_ANGLE_BISECTOR_TYPE" );
			else 
				strcat( buf, "SP_BISECTOR:subType error" );

			break;

		case SP_ANIMATOR_TYPE:

			if ( subType == SP_GENERIC_ANIMATOR_TYPE )
				strcat( buf, "SP_GENERIV_ANIMATOR_TYPE" );
			else
				strcat( buf, "SP_ANIMATOR:subType error" );

			break;

		case  SP_RECTANGLE_TYPE:
			  strcat(  buf,  "SP_RECTANGLE"  );
			  break;
		default:

			strcat( buf, "type error" );

			break;

	 }


	 return buf;

}

 char *showSpObjStatus( BYTE status )
{
	 static char buf[1024];

	 strcpy( buf, "" );

	 if ( status & STATUS_SELECTED ) strcat( buf, "selected" );
	 if ( status & STATUS_OPED ) strcat( buf, " & oped" );
	 if ( status & STATUS_INVALID ) strcat( buf, " & invalid" );
	 if ( status & STATUS_DELETED ) strcat( buf, " & deleted" );
	 if ( status & STATUS_ANIMATED ) strcat( buf, " & STATUS_ANIMATED" );

	 
	 return buf;

}

 char *showSpObjOp( BYTE op )
{
	 static char buf[1024];
	 
	 strcpy(buf, "" );

	 switch ( op ) {
		 
		case OP_NULL: 
			strcat( buf, "OP_NULL" );
			break;
		case OP_DELETE:
			strcat( buf, "OP_DELETE" );
			break;
		case OP_DRAW_A_RGN:
			strcat( buf, "OP_DRAW_A_RGN" );
			break;
		case OP_MOVE:
			strcat( buf, "OP_MOVE" );
			break;
		case OP_FIXED:
			strcat( buf, "OP_FIXED" );
			break;
		case OP_CREATE_A_POINT:
			strcat( buf, "OP_CREATE_A_POINT" );
			break;
		case OP_CREATE_A_SEGMENT:
			strcat( buf, "OP_CREATE_A_SEGMENT" );
			break;
		case OP_CREATE_A_CIRCLE:
			strcat( buf, "OP_CREATE_A_CIRCLE" );
			break;
		case OP_CREATE_A_MEMO:
			strcat( buf, "OP_CREATE_A_MEMO" );
			break;
		case OP_HELP:
			strcat( buf, "OP_HELP" );
			break;
		case OP_ANIMATE:
			strcat( buf, "OP_ANIMATE" );
			break;
		case OP_PATH:
			strcat( buf, "OP_PATH" );
			break;
		case OP_CHECK:
			strcat( buf, "OP_CHECK" );
			break;
		case OP_REFRESH_CONSTRAINT:
			strcat( buf, "OP_REFRESH_CONSTRAINT" );
			break;
		case OP_CONSTRAINTED_MOVE:
			strcat( buf, "OP_CONSTRAINTED_MOVE" );
			break;
		default:
			strcat( buf, "NO_OP" );
			break;

	 }

	
	 return buf;
}


#if	1	//  def __SP_DEBUG__

 BOOL CHECK_OP_NULL( void *pSpObj, SP_DRIVER *pDriver, BYTE op, SP_OP_PARM *pOpParm )						
{
	 return ( ( ( SP_OBJ * )( pSpObj ) )->op == ( op ) );
}

 BOOL CHECK_OP_FIXED( void *pSpObj, SP_DRIVER *pDriver, BYTE op, SP_OP_PARM *pOpParm )						
{
	 return ( ( ( SP_OBJ * )( pSpObj ) )->op == ( op ) );
}

 BOOL CAN_OP_FIXED( void *pSpObj, SP_DRIVER *pDriver, BYTE op, SP_OP_PARM *pOpParm )
{
	return ( ( ( SP_OBJ * )pSpObj )->op == OP_NULL || ( ( SP_OBJ * )pSpObj )->op == OP_FIXED );
}

 BOOL CHECK_OP_MOVE( void *pSpObj, SP_DRIVER *pDriver, BYTE op, SP_OP_PARM *pOpParm )
{
	 return ( ( ( SP_OBJ * )pSpObj )->op == op );
}

 BOOL CAN_OP_MOVE( void *pSpObj, SP_DRIVER *pDriver, BYTE op, SP_OP_PARM *pOpParm )
{
	 return ( ( ( SP_OBJ * )pSpObj )->op == OP_NULL 
		 || ( ( SP_OBJ * )pSpObj )->driver.pDriverQNode == pDriver->pDriverQNode );
	
 }

 BOOL CHECK_OP_CONSTRAINTED_MOVE( void *pSpObj, SP_DRIVER *pDriver, BYTE op, SP_OP_PARM *pOpParm )
{
	 return ( ( ( SP_OBJ * )pSpObj )->op == op );

}

 BOOL CAN_OP_CONSTRAINTED_MOVE( void *pSpObj, SP_DRIVER *pDriver, BYTE op, SP_OP_PARM *pOpParm )
{
	 if ( ( ( SP_OBJ * )pSpObj )->op == OP_NULL ) return TRUE;
	 if ( ( ( SP_OBJ * )pSpObj )->driver.pDriverQNode == pDriver->pDriverQNode 
		 && ( ( SP_OBJ * )pSpObj )->op == OP_CONSTRAINTED_MOVE 
		 && fabs( (  float  )( ( SP_OBJ * )pSpObj )->opParm.move.x - pOpParm->move.x ) < SP_OP_PARM_RANGE
		 && fabs( (  float  )( ( SP_OBJ * )pSpObj )->opParm.move.y - pOpParm->move.y ) < SP_OP_PARM_RANGE ) {
			return TRUE;
	 }

	 return FALSE;

}



#endif



