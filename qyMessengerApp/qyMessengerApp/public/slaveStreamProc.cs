﻿using System;
using System.Collections.Generic;
using System.Text;

namespace qy
{
    partial class qyFuncs
{
		public static bool isSlaveOfMaster(int iIndex_sharedObj_slave, QY_SHARED_OBJ pSharedObj_slave, int iIndex_sharedObj_master, QY_SHARED_OBJ pSharedObj_master)
		{
			if (pSharedObj_slave.bUsed
				&& pSharedObj_master.bUsed
				&& pSharedObj_slave.var.bSlave
				&& !pSharedObj_master.var.bSlave
				&& pSharedObj_slave.var.slave.masterKey.iIndex_sharedObj == iIndex_sharedObj_master
				&& pSharedObj_slave.var.slave.masterKey.uiTranNo == pSharedObj_master.var.uiTranNo
				&& pSharedObj_master.var.master.slaveKey.iIndex_sharedObj == iIndex_sharedObj_slave
				&& pSharedObj_master.var.master.slaveKey.uiTranNo == pSharedObj_slave.var.uiTranNo)
			{
				return true;
			}

			return false;

		}

	}
}
