
#include	"stdafx.h"

#include	<windowsx.h>
#include	<winsock2.h>
#include	<vfw.h>


#include	"qmCommon.h"
#include	"qmCaProc.h"
#include <myCmdParams_open.h>
#include <hgCommProc.h>
#include	"qmHgProc.h"




//
#define	CONST_mbFlg_gk		0b00001111
#define	CONST_mbFlg_nb		0b01001011
#define CONST_mbFlg_mm		0b10000111
#define CONST_mbFlg_jm		0b11000011


//
unsigned  char  myGetMbFlg(int  iMeetingLevel)
{
	unsigned  char  ucFlg = 0;
	switch (iMeetingLevel) {
	case  CONST_meetingLevel_gk:
		ucFlg = CONST_mbFlg_gk;
		break;
	case  CONST_meetingLevel_nb:
		ucFlg = CONST_mbFlg_nb;
		break;
	case  CONST_meetingLevel_mm:
		ucFlg = CONST_mbFlg_mm;
		break;
	case  CONST_meetingLevel_jm:
		ucFlg = CONST_mbFlg_jm;
		break;
	default:
		break;
	}

	return  ucFlg;
}

