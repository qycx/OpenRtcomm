
#include	<WinSock2.h>
#include	<windows.h>
#include	<tchar.h>
#include	"qyCommon.h"
#include	"qyCommProc.h"
//  #include	"qnmCommProc.h"
#include	"qnmAssetsCommProc.h"
#include	"qyTCharCommProc.h"


 QY_DMITEM  CONST_cpuManufacturerTable[]  =
{
	{	CONST_Intel,					_T(  "Intel Corporation"  ),					_T(  "Intel"  ),		},
	{	CONST_AMD,						_T(  "Advanced Micro Devices"  ),				_T(  "AMD"  ),			},
	{	CONST_NSC,						_T(  "National Semiconductor"  ),				_T(  "NSC"  ),			},
	{	CONST_Cyrix,					_T(  "Cyrix Corp., VIA Inc."  ),				_T(  "Cyrix"  ),		},
	{	CONST_NexGen,					_T(  "NexGen Inc., Advanced Micro Devices"  ),	_T(  "NexGen"  ),		},
	{	CONST_IDT,						_T(  "IDT\\Centaur, Via Inc."  ),				_T(  "IDT"  ),			},
	{	CONST_UMC,						_T(  "United Microelectronics Corp."  ),		_T(  "UMC"  ),			},
	{	CONST_Rise,						_T(  "Rise"  ),									_T(  "Rise"  ),			},
	{	CONST_Transmeta,				_T(  "Transmeta"  ),							_T(  "Transmeta"  ),	},
	{	CONST_UnknownManufacturer,		_T(  "Unknown Manufacturer"  ),					_T(  "Unknown"  ),		},
	{	-1,								_T(  ""  ),		},
};

 QY_DMITEM  CONST_intelBrandTable[]	= 
{
	{	0x01,	_T(  "Celeron(R)" ),					},
	{	0x02,	_T(  "Pentium(R) III" ),				},
	{	0x03,	_T(  "Pentium(R) III Xeon(TM)" ),		},
	{	0x04,	_T(  "Pentium(R) III" ),				},
	{	0x06,	_T(  "Mobile Pentium(R) III - M" ),	},
	{	0x07,	_T(  "Mobile Celeron(R)" ),			},
	{	0x08,	_T(  "Pentium(R) 4" ),					},
	{	0x09,	_T(  "Pentium(R) 4" ),					},
	{	0x0A,	_T(  "Celeron(R)" ),					},
	{	0x0B,	_T(  "Xeon(TM)" ),						},
	{	0x0C,	_T(  "Xeon(TM) MP" ),					},
	{	0x0E,	_T(  "Mobile Pentium(R) 4 - M" ),		},
	{	0x0F,	_T(  "Mobile Celeron(R)" ),			},
	{	0x11,	_T(  "Mobile" ),						},
	{	0x12,	_T(  "Mobile Celeron(R) M" ),			},
	{	0x13,	_T(  "Mobile Celeron(R)" ),			},
	{	0x14,	_T(  "Celeron(R)" ),					},
	{	0x15,	_T(  "Mobile" ),						},
	{	0x16,	_T(  "Pentium(R) M" ),					},
	{	0x17,	_T(  "Mobile Celeron(R)" ),			},
	{	-1,		NULL,							},
}; 


#define STORE_CLASSICAL_NAME(x)	_sntprintf(  processorName,  size,  _T(  "%s %s"  ), processorName,  myStr2TChar(  x,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  )  )	  
 extern "C"  BOOL  bGetCpuName(  int  ChipManufacturer,  int  Type,  int  Family,  int  Model,  int  iRevision,  int  iCache,  int  ExtendedFamily,  BOOL  HasMMX,  BOOL  SupportsMP,  unsigned  int  uiBrandId,  char  *  processorNameParam,  unsigned  int  sizeParam  )
{
	BOOL			bRet	=	FALSE;
	QY_DMITEM	*	pItem	=	NULL;
	TCHAR			processorName[256]	=	_T(  ""  );
	unsigned  int	size				=	sizeof(  processorName  )  /  sizeof(  processorName[0]  );
	TCHAR			tBuf[512];
	char			buf[256];

	if  (  !processorNameParam  ||  !sizeParam  )  return  FALSE;
	processorNameParam[0]  =  0;

	if  (  !(  pItem  =  qyGetDmItemByType(  CONST_cpuManufacturerTable,  ChipManufacturer,  0  )  )  )  goto  errLabel;
	_sntprintf(  processorName,  size,  _T(  "%s"  ),  (  pItem->pData  ?  pItem->pData  :  _T(  ""  )  )  );

	// Start by decided which manufacturer we are using....
	switch  (  ChipManufacturer  )  {
			case  CONST_Intel:
				  // Check the family / model / revision to determine the CPU ID.
				  switch  (  Family  )  {
						  case  3:
							    switch  (  Model  )  {
									    case  0:  STORE_CLASSICAL_NAME(  "80386 DX"  );  break;
										case  2:  STORE_CLASSICAL_NAME(  "80386 SX/CX"  );  break;
										case  4:  STORE_CLASSICAL_NAME(  "80386 SL"  );  break;
										default:  STORE_CLASSICAL_NAME(  "80386"  );  break;
								}
								break;
						  case  4:
							    switch  (  Model  )  {
									    case  0:  STORE_CLASSICAL_NAME(  "80486 DX-25/33"  );  break;
										case  1:  STORE_CLASSICAL_NAME(  "80486 DX-50"  );  break;
										case  2:  STORE_CLASSICAL_NAME(  "80486 SX"  );  break;
										case  3:  STORE_CLASSICAL_NAME(  "80486 DX2"  );  break;
										case  4:  STORE_CLASSICAL_NAME(  "80486 SL"  );  break;
										case  5:  STORE_CLASSICAL_NAME(  "80486 SX2" );  break;
										case  7:  STORE_CLASSICAL_NAME(  "80486 DX2 Enhanced"  );  break;
										case  8:  STORE_CLASSICAL_NAME(  "80486 DX4"  );  break;
										case  9:  STORE_CLASSICAL_NAME(  "80486 DX4 Enhanced"  );  break;
										default:  STORE_CLASSICAL_NAME(  "80486"  );  break;
								}
								break;
						  case  5:
							    switch  (  Model  )  {
									    case  0:  STORE_CLASSICAL_NAME("P5 A-Step Pentium");  break;
										case  1:  if  (  Type  ==  0  )  STORE_CLASSICAL_NAME(  "P5 Pentium"  ); 
											      else  STORE_CLASSICAL_NAME(  "P5 Pentium OverDrive"  );
												  break;
										case  2:  if  (  Type  ==  0  )  STORE_CLASSICAL_NAME(  "P54C Pentium"  ); 
											      else  STORE_CLASSICAL_NAME(  "P54C Pentium OverDrive"  );
												  break;											      
										case  3:  STORE_CLASSICAL_NAME(  "P24T Pentium OverDrive"  );  break;
										case  4:  if  (  Type  ==  0  )  STORE_CLASSICAL_NAME(  "P55C Pentium MMX"  );
												  else  STORE_CLASSICAL_NAME(  "P55C Pentium MMX OverDrive"  );
												  break;
										case  7:  STORE_CLASSICAL_NAME(  "P54C Pentium"  );  break;
										case  8:  STORE_CLASSICAL_NAME (  "P55C(0.25) Pentium"  );  break;
										default:  STORE_CLASSICAL_NAME (  "Pentium"  );  break;
								}
								break;
						  case  6:
						 	    switch  (  Model  )  {
								   	    case  0:  STORE_CLASSICAL_NAME(  "P6 A-Step Pentium Pro"  ); break;
									    case  1:  STORE_CLASSICAL_NAME(  "P6 Pentium Pro"  ); break;
									    case  3:  STORE_CLASSICAL_NAME(  "Pentium II(0.28)"  ); break;
									    case  5:  
											  switch  (  iCache  )  { 	
													  case  0x40:  STORE_CLASSICAL_NAME(  "Celeron"  );  break;
													  case  0x41:  STORE_CLASSICAL_NAME(  "Celeron/128"  );  break;
													  case  0x42:
													  case  0x43:
													  case  0x82:
													  case  0x83:  STORE_CLASSICAL_NAME(  "Pentium II"  );  break;
													  case  0x44:
													  case  0x45:
													  case  0x84:
													  case  0x85:  STORE_CLASSICAL_NAME(  "Pentium II Xeon"  );  break;
											  }
											  break;
										case  6:  if  (  !HasMMX  )  STORE_CLASSICAL_NAME(  "Celeron"  );  
											      else  STORE_CLASSICAL_NAME(  "Celeron MMX"  );
												  break;														 //  "Pentium II With On-Die L2 Cache"
									    case  7:																 //  "Pentium III(0.25)"
									    case  8:																 //  "Pentium III(0.18) With 256 KB On-Die L2 Cache "
											  switch  (  iCache  )  {
													  case  0x40:  STORE_CLASSICAL_NAME(  "Celeron"  );  break;
													  case  0x41:  STORE_CLASSICAL_NAME(  "Celeron/128"  );  break;
													  case  0x42:
													  case  0x43:
													  case  0x82:
													  case  0x83:  STORE_CLASSICAL_NAME(  "Pentium III"  );  break;
													  case  0x44:
													  case  0x45:
													  case  0x84:
													  case  0x85:  STORE_CLASSICAL_NAME(  "Pentium III Xeon"  );  break;
											  }
											  break;
									    case  0xa:  STORE_CLASSICAL_NAME(  "Pentium III Xeon-A"	 );  break;		 //  "Pentium III(0.18) With 1 Or 2 MB On-Die L2 Cache "
									    case  0xb:  STORE_CLASSICAL_NAME(  "Pentium III(0.13) With 256 Or 512 KB On-Die L2 Cache "  ); break;
									    default:  STORE_CLASSICAL_NAME(  "P6"  );  break;
								}
							    break;
						  case  7:  STORE_CLASSICAL_NAME(  "Merced(IA-64)"  );  break;
						  case  0xf:  	// Check the extended family bits...
							    if  (  uiBrandId  )  {	//  2006/01/16加入了对uiBrandId的判断
									myTChar2Str(  qyGetDesByType1(  CONST_intelBrandTable,  uiBrandId  ),  buf,  sizeof(  buf  )  );
									STORE_CLASSICAL_NAME(  buf  );
									}
								else  {
									  switch  (  ExtendedFamily  )  {
											  case  0:
													  switch  (  Model  )  {
															  case  0:  STORE_CLASSICAL_NAME(  "Pentium IV(0.18)"  );  break;
															  case  1:  STORE_CLASSICAL_NAME(  "Pentium IV (0.18)"  );  break;
															  case  2:  STORE_CLASSICAL_NAME(  "Pentium IV (0.13)"  );  break;
															  default:  STORE_CLASSICAL_NAME(  "Unknown Pentium 4 family"  );  break;
											  		  }
											  		  break;
											  case  1:  STORE_CLASSICAL_NAME(  "Intel McKinley (IA-64)"  );  break;
									  }
								}
								break;
						default:  STORE_CLASSICAL_NAME(  "Unknown family"  );  break;
				  }
				  break;
			case  CONST_AMD:
				  // Check the family / model / revision to determine the CPU ID.
			      switch  (  Family  )  {
						  case  4:
							    switch  (  Model  )  {
										case  3:  STORE_CLASSICAL_NAME(  "80486 DX2"  );  break;
										case  7:  STORE_CLASSICAL_NAME(  "80486DX2 WriteBack"  );  break;
										case  8:  STORE_CLASSICAL_NAME(  "80486DX4"  );  break;
										case  9:  STORE_CLASSICAL_NAME(  "80486DX4 WriteBack"  );  break;
										case  0xe:  STORE_CLASSICAL_NAME(  "5x86"  );  break;
										case  0xf:  STORE_CLASSICAL_NAME(  "5x86WB"  );  break;
										default:  STORE_CLASSICAL_NAME(  "Unknown 80486 family"  );  break;
								}
								break;
						  case  5:
							    switch  (  Model  )  {
								        case  0:  STORE_CLASSICAL_NAME ("SSA5 (PR75, PR90, PR100)"); break;
										case  1:  STORE_CLASSICAL_NAME ("5k86 (PR120, PR133)"); break;
										case  2:  STORE_CLASSICAL_NAME ("5k86 (PR166)"); break;
										case  3:  STORE_CLASSICAL_NAME ("5k86 (PR200)"); break;
										case  6:  STORE_CLASSICAL_NAME ("K6 (0.30 )"); break;
										case  7:  STORE_CLASSICAL_NAME ("K6 (0.25 )"); break;
										case  8:  STORE_CLASSICAL_NAME ("K6-2"); break;
										case  9:  STORE_CLASSICAL_NAME ("K6-III"); break;
										case  0xd:  STORE_CLASSICAL_NAME ("K6-2+ or K6-III+ (0.18 )"); break;
										default:  STORE_CLASSICAL_NAME ("Unknown 80586 family"); return false;
								}
								break;
						  case  6:
							    switch  (  Model  )  {
										case  1:  STORE_CLASSICAL_NAME ("Athlon (0.25 )"); break;
										case  2:  STORE_CLASSICAL_NAME ("Athlon (0.18 )"); break;
										case  3:  STORE_CLASSICAL_NAME ("Duron (SF core)"); break;
										case  4:  STORE_CLASSICAL_NAME ("Athlon (Thunderbird core)"); break;
										case  6:  STORE_CLASSICAL_NAME ("Athlon (Palomino core)"); break;
										case  7:  STORE_CLASSICAL_NAME ("Duron (Morgan core)"); break;
										case  8: 
											  if  (  SupportsMP  )  STORE_CLASSICAL_NAME(  "Athlon MP (Thoroughbred core)"  ); 
											  else  STORE_CLASSICAL_NAME(  "Athlon XP (Thoroughbred core)"  );
											  break;
										default:  STORE_CLASSICAL_NAME ("Unknown K7 family");  break;
								}
								break;
						  default:  STORE_CLASSICAL_NAME(  "Unknown AMD family"  );  break;
				  }
				  break;
		    case  CONST_Transmeta:
				  switch  (  Family  )  {	
						  case  5:
							    switch  (  Model  )  {
										case  4:  STORE_CLASSICAL_NAME(  "Crusoe TM3x00 and TM5x00"  );  break;
										default:  STORE_CLASSICAL_NAME(  "Unknown Crusoe family"  );  break;
								}
								break;
						  default:  STORE_CLASSICAL_NAME ("Unknown Transmeta family");  break;
				  }
				  break;
			case  CONST_Rise:
				  switch  (  Family  )  {	
						  case  5:
							    switch  (  Model  )  {
										case  0:  STORE_CLASSICAL_NAME(  "mP6(0.25)"  ); break;
										case  2:  STORE_CLASSICAL_NAME ("mP6 (0.18 )"); break;
										default: STORE_CLASSICAL_NAME ("Unknown Rise family"); break;
								}
								break;
						  default:  STORE_CLASSICAL_NAME ("Unknown Rise family");  break;
				  }
				  break;
		    case  CONST_UMC:
				  switch  (  Family  )  {	
						  case  4:
							    switch  (  Model  )  {
								        case  1: STORE_CLASSICAL_NAME ("U5D"); break;
										case  2: STORE_CLASSICAL_NAME ("U5S"); break;
										default: STORE_CLASSICAL_NAME ("Unknown UMC family");  break;
								}
								break;
						  default:  STORE_CLASSICAL_NAME ("Unknown UMC family");  break;
				  }
				  break;
			case  CONST_IDT:
				  switch  (  Family  )  {	
						  case  5:
							    switch  (  Model  )  {
										case  4:  STORE_CLASSICAL_NAME(  "C6"  ); break;
										case  8: STORE_CLASSICAL_NAME ("C2"); break;
										case  9: STORE_CLASSICAL_NAME ("C3"); break;
										default: STORE_CLASSICAL_NAME ("Unknown IDT\\Centaur family");  break;
								}
								break;
						  case  6:
							    switch  (  Model  )  {
								        case  6:  STORE_CLASSICAL_NAME ("VIA Cyrix III - Samuel"); break;
										default:  STORE_CLASSICAL_NAME ("Unknown IDT\\Centaur family");  break;
								}
								break;
						  default:  STORE_CLASSICAL_NAME ("Unknown IDT\\Centaur family");  break;
				  }
				  break;
		    case  CONST_Cyrix:
				  switch  (  Family  )  {	
				          case  4:
							    switch  (  Model  )  {
										case  4: STORE_CLASSICAL_NAME ("MediaGX GX, GXm"); break;
										case  9: STORE_CLASSICAL_NAME ("5x86"); break;
										default: STORE_CLASSICAL_NAME ("Unknown Cx5x86 family");  break;
								}
								break;
						  case  5:
							    switch  (  Model  )  {
									    case  2:  STORE_CLASSICAL_NAME ("Cx6x86"); break;
										case  4: STORE_CLASSICAL_NAME ("MediaGX GXm"); break;
										default: STORE_CLASSICAL_NAME ("Unknown Cx6x86 family");  break;
								}
								break;
						  case  6:
							    switch  (  Model  )  {
										case  0: STORE_CLASSICAL_NAME ("6x86MX"); break;
										case  5: STORE_CLASSICAL_NAME ("Cyrix M2 Core"); break;
										case  6: STORE_CLASSICAL_NAME ("WinChip C5A Core"); break;
										case  7: STORE_CLASSICAL_NAME ("WinChip C5B\\C5C Core"); break;
										case  8: STORE_CLASSICAL_NAME ("WinChip C5C-T Core"); break;
										default: STORE_CLASSICAL_NAME ("Unknown 6x86MX\\Cyrix III family"); break;
								}
								break;
						  default:  STORE_CLASSICAL_NAME(  "Unknown family"  );  break;
				  }
				  break;
		    case  CONST_NexGen:
				  switch  (  Family  )  {
				          case  5:
							    switch  (  Model  )  {
								        case  0: STORE_CLASSICAL_NAME ("Nx586 or Nx586FPU"); break;
										default: STORE_CLASSICAL_NAME ("Unknown NexGen family"); break;
								}
								break;
						  default:  STORE_CLASSICAL_NAME ("Unknown family"); break;
				  }
				  break;
			case  CONST_NSC:  STORE_CLASSICAL_NAME(  "Cx486SLC \\ DLC \\ Cx486S A-Step"  );  break;
			default:
				  // We cannot identify the processor.
				  STORE_CLASSICAL_NAME ("Unknown family");  break;
	}
	bRet  =  TRUE;

errLabel:
	if  (  bRet  )  myTChar2Str(  processorName,  processorNameParam,  sizeParam  );
	return  bRet;
}

