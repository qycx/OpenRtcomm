
#ifndef  __imObjHash_h__
#define  __imObjHash_h__	//  {


/////////////
typedef  struct  __hashData_imObj_t		{
				 int					iObjId;
				 int					iObjType;			 

}		 HashData_imObj;

typedef  struct  __hashData_iObjId_t	{
				 unsigned  int			uiHashIndex;
}		 HashData_iObjId;



//
#define		CONST_hashKeyType_null				0
#define		CONST_hashKeyType_imObj				1
#define		CONST_hashKeyType_iObjId			2

//
unsigned  int  imObj_hash(  HashTblElementType  *  pKey  );
BOOL  imObj_hash_bSame(  HashTblElementType  *  p0,  HashTblElementType  *  p1  );
int  imObj_hash_copy(  HashTblElementType  *  pSrc,  HashTblElementType  *  pDst  );
int  imObj_hash_free(  HashTblElementType  *  p  );



#endif

