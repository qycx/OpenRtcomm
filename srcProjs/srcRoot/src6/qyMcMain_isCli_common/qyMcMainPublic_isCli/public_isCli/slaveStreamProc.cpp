
#include	"stdafx.h"
#include	<math.h>
#include	<stddef.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"tmpCeLib.h"
//
#include	"qyOpenShellCommon.h"
#include	"qmcSharedObj.h"




//
 BOOL  isSlaveOfMaster(  int  iIndex_sharedObj_slave,  QY_SHARED_OBJ  *  pSharedObj_slave,  int  iIndex_sharedObj_master,  QY_SHARED_OBJ  *  pSharedObj_master  )
{
	if  (  pSharedObj_slave->bUsed  
		&&  pSharedObj_master->bUsed
		&&  pSharedObj_slave->bSlave
		&&  !pSharedObj_master->bSlave
		&&  pSharedObj_slave->slave.masterKey.iIndex_sharedObj  ==  iIndex_sharedObj_master
		&&  pSharedObj_slave->slave.masterKey.uiTranNo  ==  pSharedObj_master->uiTranNo
		&&  pSharedObj_master->master.slaveKey.iIndex_sharedObj  ==  iIndex_sharedObj_slave
		&&  pSharedObj_master->master.slaveKey.uiTranNo  ==  pSharedObj_slave->uiTranNo  )
	{
		return  TRUE;
	}
	
	return  FALSE;

 }


 