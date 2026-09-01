

#include <windows.h>
#include <string.h>
#include "commonSock.h"
#include "asrObjs.h"
#include "asrComm.h"

/*
 extern "C" int asrTellService( void *pAsrSockParam, void *pAsrServiceInfoParam )
{
	ASR_COMM_HEAD aCH;
	ASR_COMM_RESP_HEAD aCRH;

	aCH.cmd = ASR_CMD_TELL_SERVICE;
	aCH.u.tellService.serviceId = ASR_SERVICE_RAS_MONITORING;

	if ( asrSend( pAsrSockParam, ( char * )&aCH, sizeof( aCH ), DEFAULT_ASR_SEND_TIMEOUT ) )
		return -1;
	if ( asrRecvX( pAsrSockParam, ( char * )&aCRH, sizeof( aCRH ), DEFAULT_ASR_RECV_TIMEOUT ) )
		return -1;
	if ( memcmp( aCRH.respCode, ASR_RC_OK, lstrlen( ASR_RC_OK ) ) ) 
		return -1;
	return 0;

}



 extern "C" int asrQueryService( void *pAsrSockParam, void *pAsrServiceInfoParam, int *pLen )
{
	ASR_COMM_HEAD aCH;
	ASR_COMM_RESP_HEAD aCRH;
	ASR_SERVICE_INFO *pAsrServiceInfo = ( ASR_SERVICE_INFO * )pAsrServiceInfoParam;
	int cb;

	aCH.cmd = ASR_CMD_QUERY_SERVICE;
	
	if ( asrSend( pAsrSockParam, ( char * )&aCH, sizeof( aCH ), DEFAULT_ASR_SEND_TIMEOUT ) )
		return -1;
	cb = sizeof( aCRH );
	if ( asrRecv( pAsrSockParam, ( char * )&aCRH, &cb, DEFAULT_ASR_RECV_TIMEOUT ) )
		return -1;
	if ( memcmp( aCRH.respCode, ASR_RC_OK, lstrlen( ASR_RC_OK ) ) ) return -1;

	pAsrServiceInfo->serviceId = aCRH.u.queryService.serviceId;

	return 0;	

}

*/
