
#ifndef  __QYSNMPCOMMPROC_H__
#define  __QYSNMPCOMMPROC_H__	/*  {  */

#define		CONST_defSnmpVer								"v1"
#define		CONST_defCommunityRo							"public"
#define		CONST_defCommunityRw							"private"
//


#define		CONST_enterpriseId_reserved						0		//	other
#define		CONST_enterpriseId_ibm							2
#define		CONST_enterpriseId_unix							4
#define		CONST_enterpriseId_acc							5
#define		CONST_enterpriseId_cisco						9
#define		CONST_enterpriseId_hp							11
#define		CONST_enterpriseId_xylogics						15		//  Xylogics
#define		CONST_enterpriseId_wellfleet					18
#define		CONST_enterpriseId_novell						23		//  Novell
#define		CONST_enterpriseId_hughes						26		//  Hughes LAN Systems
#define		CONST_enterpriseId_sco							32		//  Santa Cruz Operation
#define		CONST_enterpriseId_dec							36		//  DEC
#define		CONST_enterpriseId_sun							42
#define		CONST_enterpriseId_3com							43
#define		CONST_enterpriseId_synOptics					45		//  Bay  ?  SynOptics
#define		CONST_enterpriseId_cabletron					52		//	cabletron Systems
#define		CONST_enterpriseId_mips							57		//  MIPS 
#define		CONST_enterpriseId_tgv							58		//  TGV
#define		CONST_enterpriseId_siliconGraphics				59
#define		CONST_enterpriseId_apple						63		//  Apple 
#define		CONST_enterpriseId_gandalf						64		//  Gandalf
#define		CONST_enterpriseId_Lannet						81		//  Lannet Company
#define		CONST_enterpriseId_rnd							89		//  RND
#define		CONST_enterpriseId_nokia						94		//  Nokia
#define		CONST_enterpriseId_allenBradely					95		//  Allen-Bradely Company
#define		CONST_enterpriseId_sigma						97		//  Sigma Network Systems, Inc.
#define		CONST_enterpriseId_snmpResearch					99		//  SNMP Research
#define		CONST_enterpriseId_microcom						102		//  Microcom
#define		CONST_enterpriseId_processSoftware				105		//  Process Software Corporation
#define		CONST_enterpriseId_dgUx							106		//  DG/UX : EMC Data General Division
#define		CONST_enterpriseId_emulex						108		//  Emulex Corporation
#define		CONST_enterpriseId_Synernetics					114		//  3com  ?  Synernetics, Inc.
#define		CONST_enterpriseId_hitachi						116		//  Hitachi, Ltd.
#define		CONST_enterpriseId_telebit						117		//  Telebit
#define		CONST_enterpriseId_nec							119		//  NEC Corporation
#define		CONST_enterpriseId_sony							122		//  Sony
#define		CONST_enterpriseId_tektronix					128		//  Tektronix, Inc.
#define		CONST_enterpriseId_frontier						141		//  Frontier Software Development
#define		CONST_enterpriseId_case							144		//  Case Communications
#define		CONST_enterpriseId_develcon						151		//  Develcon
#define		CONST_enterpriseId_dupont						159		//  Dupont EOP
#define		CONST_enterpriseId_motorola						161		//  Motorola
#define		CONST_enterpriseId_shiva						166		//  Shiva Corporation
#define		CONST_enterpriseId_xlnt							168		//  Xlnt Designs INC (XDI)
#define		CONST_enterpriseId_dLink						171
#define		CONST_enterpriseId_adcKentrox					181		//  ADC Kentrox
#define		CONST_enterpriseId_ericsson						193		//  Ericsson Business CommunicationsDavid Partain
#define		CONST_enterpriseId_smc							202		//  SMC
#define		CONST_enterpriseId_allied						207		//  Allied Telesis, Inc.
#define		CONST_enterpriseId_netWorth						215		//  NetWorth
#define		CONST_enterpriseId_siemens_fujitsu				231		//  Fujitsu Siemens Computers
#define		CONST_enterpriseId_compaq						232		//  Compaq
#define		CONST_enterpriseId_samsung						236		//  Samsung Group
#define		CONST_enterpriseId_lantronix					244		//  Lantronix
#define		CONST_enterpriseId_xerox						253		//  Xerox
#define		CONST_enterpriseId_matsushita					258		//  Xerox  ?  Matsushita Electric Industrial Co., Ltd.
#define		CONST_enterpriseId_accton						259		//  Accton
#define		CONST_enterpriseId_3comStarTek					260		//  3Com STARTEK : Star-Tek, Inc.
#define		CONST_enterpriseId_fuji							297		//  Fuji Xerox Co., Ltd.
#define		CONST_enterpriseId_asante						298		//  Asante Technology
#define		CONST_enterpriseId_farallon						304		//  Farallon Computing, Inc.
#define		CONST_enterpriseId_livingston					307		//  Livingston Enterprises, Inc.
#define		CONST_enterpriseId_microsoft					311
#define		CONST_enterpriseId_apc							318		//  American Power Conversion Corp.
#define		CONST_enterpriseId_digi							332		//  Digi International
#define		CONST_enterpriseId_intel						343
#define		CONST_enterpriseId_axis							368		//  Axis Communications AB
#define		CONST_enterpriseId_3com_Axon					370		//  3COM/Axon
#define		CONST_enterpriseId_symbol						388		//  Symbol Technologies, Inc.
#define		CONST_enterpriseId_utstarcom					429		//  UTStarcom Incorporated
#define		CONST_enterpriseId_3com_Sync					485		//  Sync Research, Inc.  
#define		CONST_enterpriseId_ascend						529		//  Ascend Communications Inc.
#define		CONST_enterpriseId_equinox						544		//  Equinox Systems, Inc.
#define		CONST_enterpriseId_3com_Sonix					559		//  Sonix Communications, Ltd.
#define		CONST_enterpriseId_northernTelecom				562
#define		CONST_enterpriseId_Lexmark						641		//  Lexmark International
#define		CONST_enterpriseId_eastern						644		//  Eastern Research Inc.
#define		CONST_enterpriseId_microplex					649		//  Microplex Systems Ltd.
#define		CONST_enterpriseId_adtran						664		//  Adtran
#define		CONST_enterpriseId_dell							674		//  Dell Computer Corporation
#define		CONST_enterpriseId_zeroOne						722		//  Zero-One Technologies, Ltd.
#define		CONST_enterpriseId_alcatel_xylan				800		//  Alcatel : Xylan Corp.
#define		CONST_enterpriseId_zyxel						890		//  ZyXEL Communications Corp.
#define		CONST_enterpriseId_tosiba						961		//  Tokyo Electric Co., Ltd.
#define		CONST_enterpriseId_emc							1139	//  EMC Corp
#define		CONST_enterpriseId_fluke						1226	//  Forte Networks Inc.
#define		CONST_enterpriseId_epson						1248	//  SEIKO EPSON CORPORATION
#define		CONST_enterpriseId_linux						1575	//  linux : Technical University of Braunschweig
#define		CONST_enterpriseId_canon						1602	//  CANON Inc.
#define		CONST_enterpriseId_lucent						1751	//  Lucent Technologies
#define		CONST_enterpriseId_alteon						1872	//  Alteon Networks, Inc.
#define		CONST_enterpriseId_siemens						1887	//  Siemens Switzerland Ltd.
#define		CONST_enterpriseId_extremeNetworks				1916	//  Extreme Networks
#define		CONST_enterpriseId_foundry						1991	//  Foundry Networks, Inc.
#define		CONST_enterpriseId_huawei						2011
#define		CONST_enterpriseId_ucDavis						2021	//  U.C. Davis, ECE Dept. Tom
#define		CONST_enterpriseId_efi							2136	//  Electronics For Imaging, Inc.
#define		CONST_enterpriseId_nortel_rapidCity				2272	//  nortel : Rapid City Communication
#define		CONST_enterpriseId_lancom						2356	//  LANCOM Systems
#define		CONST_enterpriseId_konica						2364	//  Konica Corporation
#define		CONST_enterpriseId_sharp						2385	//  SHARP Corporation
#define		CONST_enterpriseId_brother						2435	//  Brother Industries, Ltd.
#define		CONST_enterpriseId_minolta						2590	//  Minolta Co., Ltd.
#define		CONST_enterpriseId_thomson						2863	//  Thomson Inc.
#define		CONST_enterpriseId_alcatel_packet				3003	//  Packet Engines Inc.
#define		CONST_enterpriseId_ericssonWireless				3657	//  Ericsson Wireless LAN Systems
#define		CONST_enterpriseId_WRI							3807	//	Wuhan Research Institute of Posts and Telecommunications
#define		CONST_enterpriseId_Netgear						4526	//  Netgear
#define		CONST_enterpriseId_maxtor						4693	//  Maxtor Corp.,
#define		CONST_enterpriseId_star							4881	//  star
#define		CONST_enterpriseId_enterasys					5624	//  Enterasys Networks
#define		CONST_enterpriseId_netSys						5689	//  Net & Sys Co., Ltd
#define		CONST_enterpriseId_gigalink						5917	//  Gigalink
#define		CONST_enterpriseId_quantum						6411	//  Quantum Corp - Snap Division
#define		CONST_enterpriseId_alcatel						6486	//  Alcatel
#define		CONST_enterpriseId_avaya						6889	//  Avaya Communication
#define		CONST_enterpriseId_netSnmp						8072	//  net-snmp
#define		CONST_enterpriseId_harbour						8212	
#define		CONST_enterpriseId_sonicwall					8714	//  iNOC, Inc.
#define		CONST_enterpriseId_wuhanTIT						9952	//  topsec : WuhanTIT
#define		CONST_enterpriseId_neesus						10227	//  Neesus Datacom
#define		CONST_enterpriseId_bitway						13157	//  Tsinghua Unisplendour Bitway Networking Technology Co.,Ltd.



//  设备类型定义
#define		CONST_netDevType_null							0
#define		CONST_netDevType_pc								1
#define		CONST_netDevType_2switch						2
#define		CONST_netDevType_3switch						3
#define		CONST_netDevType_router							4

#define		CONST_win2kp_oid								"1.3.6.1.4.1.311.1.1.3.1.1"

	//IANAifType.mib
	#define		CONST_ifType_other							1
	#define		CONST_ifType_regular1822					2
	#define		CONST_ifType_hdh1822						3
	#define		CONST_ifType_ddnX25							4
	#define		CONST_ifType_rfc877X25						5
	#define		CONST_ifType_ethernetCsmacd					6
	#define		CONST_ifType_iso88023Csmacd					7			//  Deprecated via RFC-draft-ietf-hubmib-etherif-mib-v3  ethernetCsmacd (6) should be used instead
	#define		CONST_ifType_iso88024TokenBus				8
	#define		CONST_ifType_iso88025TokenRing				9
	#define		CONST_ifType_iso88026Man					10
	#define		CONST_ifType_starLan						11			//  Deprecated via RFC-draft-ietf-hubmib-etherif-mib-v3  ethernetCsmacd (6) should be used instead
	#define		CONST_ifType_proteon10Mbit					12
	#define		CONST_ifType_proteon80Mbit					13
	#define		CONST_ifType_hyperchannel					14
	#define		CONST_ifType_fddi							15
	#define		CONST_ifType_lapb							16
	#define		CONST_ifType_sdlc							17
	#define		CONST_ifType_ds1							18
	#define		CONST_ifType_e1								19
	#define		CONST_ifType_basicISDN						20
	#define		CONST_ifType_primaryISDN					21
	#define		CONST_ifType_propPointToPointSerial			22
	#define		CONST_ifType_ppp							23
	#define		CONST_ifType_softwareLoopback				24
	#define		CONST_ifType_eon							25
	#define		CONST_ifType_ethernet3Mbit					26
	#define		CONST_ifType_nsip							27
	#define		CONST_ifType_slip							28
	#define		CONST_ifType_ultra							29
	#define		CONST_ifType_ds3							30
	#define		CONST_ifType_sip							31
	#define		CONST_ifType_frameRelay						32
    #define		CONST_ifType_rs232					        33
    #define		CONST_ifType_para						    34			//  parallel-port
	#define		CONST_ifType_arcnet						    35			//  arcnet
	#define		CONST_ifType_arcnetPlus				        36			//  arcnet plus
	#define		CONST_ifType_atm					        37          //  ATM cells
	#define		CONST_ifType_miox25				            38
	#define		CONST_ifType_sonet					        39          //  SONET or SDH 
	#define		CONST_ifType_x25ple					        40
	#define		CONST_ifType_iso88022llc					41
	#define		CONST_ifType_localTalk						42
	#define		CONST_ifType_smdsDxi						43
	#define		CONST_ifType_frameRelayService				44			//  FRNETSERV-MIB
	#define		CONST_ifType_v35							45
	#define		CONST_ifType_hssi							46
	#define		CONST_ifType_hippi							47
	#define		CONST_ifType_modem							48          //  Generic modem
	#define		CONST_ifType_aal5							49          //  AAL5 over ATM
	#define		CONST_ifType_sonetPath						50
	#define		CONST_ifType_sonetVT						51
	#define		CONST_ifType_smdsIcip						52			//  SMDS InterCarrier Interface
	#define		CONST_ifType_propVirtual					53			//  proprietary virtual/internal
	#define		CONST_ifType_propMultiplexor				54			//  proprietary multiplexing
	#define		CONST_ifType_ieee80212						55			//  100BaseVG
	#define		CONST_ifType_fibreChannel					56			//  Fibre Channel
	#define		CONST_ifType_hippiInterface					57			//  HIPPI interfaces     
	#define		CONST_ifType_frameRelayInterconnect         58			//  Obsolete use either
	#define		CONST_ifType_aflane8023						59			//  ATM Emulated LAN for 802.3
	#define		CONST_ifType_aflane8025						60			//  ATM Emulated LAN for 802.5
	#define		CONST_ifType_cctEmul						61			//  ATM Emulated circuit          
	#define		CONST_ifType_fastEther						62			//  Obsoleted via RFC-draft-ietf-hubmib-etherif-mib-v3  ethernetCsmacd              6) should be used instead
	#define		CONST_ifType_isdn							63          //  ISDN and X.25           
	#define		CONST_ifType_v11							64          //  CCITT V.11/X.21             
	#define		CONST_ifType_v36							65          //  CCITT V.36                  
	#define		CONST_ifType_g703at64k						66			//  CCITT G703 at 64Kbps
	#define		CONST_ifType_g703at2mb						67			//  Obsolete see DS1-MIB
	#define		CONST_ifType_qllc							68          //  SNA QLLC	#define		CONST_ifType_ 
	#define		CONST_ifType_fastEtherFX					69			//  Obsoleted via RFC-draft-ietf-hubmib-etherif-mib-v3  ethernetCsmacd              6) should be used instead
	#define		CONST_ifType_channel						70			//  channel	#define		CONST_ifType_  
	#define		CONST_ifType_ieee80211						71			//  radio spread spectrum       
	#define		CONST_ifType_ibm370parChan					72			//  IBM System 360/370 OEMI Channel
	#define		CONST_ifType_escon							73          //  IBM Enterprise Systems Connection
	#define		CONST_ifType_dlsw							74          //  Data Link Switching
	#define		CONST_ifType_isdns							75          //  ISDN S/T interface
	#define		CONST_ifType_isdnu							76          //  ISDN U interface
	#define		CONST_ifType_lapd							77          //  Link Access Protocol D
	#define		CONST_ifType_ipSwitch						78			//  IP Switching Objects
	#define		CONST_ifType_rsrb							79          //  Remote Source Route Bridging
	#define		CONST_ifType_atmLogical						80			//  ATM Logical Port
	#define		CONST_ifType_ds0							81          //  Digital Signal Level 0
	#define		CONST_ifType_ds0Bundle						82			//  group of ds0s on the same ds1
	#define		CONST_ifType_bsc							83          //  Bisynchronous Protocol
	#define		CONST_ifType_async							84          //  Asynchronous Protocol
	#define		CONST_ifType_cnr							85          //  Combat Net Radio
	#define		CONST_ifType_iso88025Dtr					86			//  ISO 802.5r DTR
	#define		CONST_ifType_eplrs							87          //  Ext Pos Loc Report Sys
	#define		CONST_ifType_arap							88          //  Appletalk Remote Access Protocol
	#define		CONST_ifType_propCnls						89			//  Proprietary Connectionless Protocol
	#define		CONST_ifType_hostPad						90			//  CCITT-ITU X.29 PAD Protocol
	#define		CONST_ifType_termPad						91			//  CCITT-ITU X.3 PAD Facility
	#define		CONST_ifType_frameRelayMPI					92			//  Multiproto Interconnect over FR
	#define		CONST_ifType_x213							93          //  CCITT-ITU X213
	#define		CONST_ifType_adsl							94          //  Asymmetric Digital Subscriber Loop
	#define		CONST_ifType_radsl							95          //  Rate-Adapt. Digital Subscriber Loop
	#define		CONST_ifType_sdsl							96          //  Symmetric Digital Subscriber Loop
	#define		CONST_ifType_vdsl							97          //  Very H-Speed Digital Subscrib. Loop
	#define		CONST_ifType_iso88025CRFPInt				98			//  ISO 802.5 CRFP
	#define		CONST_ifType_myrinet						99			//  Myricom Myrinet
	#define		CONST_ifType_voiceEM						100			//  voice recEive and transMit
	#define		CONST_ifType_voiceFXO						101			//  voice Foreign Exchange Office
	#define		CONST_ifType_voiceFXS						102			//  voice Foreign Exchange Station
	#define		CONST_ifType_voiceEncap						103			//  voice encapsulation
	#define		CONST_ifType_voiceOverIp					104			//  voice over IP encapsulation
	#define		CONST_ifType_atmDxi							105			//  ATM DXI
	#define		CONST_ifType_atmFuni						106			//  ATM FUNI
	#define		CONST_ifType_atmIma							107			//  ATM IMA	#define		CONST_ifType_
	#define		CONST_ifType_pppMultilinkBundle             108			//  PPP Multilink Bundle
	#define		CONST_ifType_ipOverCdlc						109			//  IBM ipOverCdlc
	#define		CONST_ifType_ipOverClaw						110			//  IBM Common Link Access to Workstn
	#define		CONST_ifType_stackToStack					111			//  IBM stackToStack
	#define		CONST_ifType_virtualIpAddress				112			//  IBM VIPA
	#define		CONST_ifType_mpc							113         //  IBM multi-protocol channel support
	#define		CONST_ifType_ipOverAtm						114			//  IBM ipOverAtm
	#define		CONST_ifType_iso88025Fiber					115			//  ISO 802.5j Fiber Token Ring
	#define		CONST_ifType_tdlc							116			//  IBM twinaxial data link control
	#define		CONST_ifType_gigabitEthernet				117			//  Obsoleted via RFC-draft-ietf-hubmib-etherif-mib-v3  ethernetCsmacd              6) should be used instead
	#define		CONST_ifType_hdlc							118         //  HDLC
	#define		CONST_ifType_lapf							119			//  LAP F
	#define		CONST_ifType_v37							120			//  V.37
	#define		CONST_ifType_x25mlp							121			//  Multi-Link Protocol
	#define		CONST_ifType_x25huntGroup					122			//  X25 Hunt Group
	#define		CONST_ifType_trasnpHdlc						123			//  Transp HDLC
	#define		CONST_ifType_interleave						124			//  Interleave channel
	#define		CONST_ifType_fast							125         //  Fast channel
	#define		CONST_ifType_ip								126			//  IP              for APPN HPR in IP networks)
	#define		CONST_ifType_docsCableMaclayer              127			//  CATV Mac Layer
	#define		CONST_ifType_docsCableDownstream            128			//  CATV Downstream interface
	#define		CONST_ifType_docsCableUpstream              129			//  CATV Upstream interface
	#define		CONST_ifType_a12MppSwitch					130			//  Avalon Parallel Processor
	#define		CONST_ifType_tunnel							131			//  Encapsulation interface
	#define		CONST_ifType_coffee							132			//  coffee pot
	#define		CONST_ifType_ces							133         //  Circuit Emulation Service
	#define		CONST_ifType_atmSubInterface				134			//  ATM Sub Interface
	#define		CONST_ifType_l2vlan							135			//  Layer 2 Virtual LAN using 802.1Q
	#define		CONST_ifType_l3ipvlan						136			//  Layer 3 Virtual LAN using IP
	#define		CONST_ifType_l3ipxvlan						137			//  Layer 3 Virtual LAN using IPX
	#define		CONST_ifType_digitalPowerline				138			//  IP over Power Lines	
	#define		CONST_ifType_mediaMailOverIp				139			//  Multimedia Mail over IP
	#define		CONST_ifType_dtm							140			//  Dynamic syncronous Transfer Mode
	#define		CONST_ifType_dcn							141			//  Data Communications Network
	#define		CONST_ifType_ipForward						142			//  IP Forwarding Interface
	#define		CONST_ifType_msdsl							143			//  Multi-rate Symmetric DSL
	#define		CONST_ifType_ieee1394						144			//  IEEE1394 High Performance Serial Bus
	#define		CONST_ifType_ifGsn							145			//  HIPPI-6400 
	#define		CONST_ifType_dvbRccMacLayer					146			//  DVB-RCC MAC Layer
	#define		CONST_ifType_dvbRccDownstream				147			//  DVB-RCC Downstream Channel
	#define		CONST_ifType_dvbRccUpstream					148			//  DVB-RCC Upstream Channel
	#define		CONST_ifType_atmVirtual						149			//  ATM Virtual Interface
	#define		CONST_ifType_mplsTunnel						150			//  MPLS Tunnel Virtual Interface
	#define		CONST_ifType_srp							151			//  Spatial Reuse Protocol	
	#define		CONST_ifType_voiceOverAtm					152			//  Voice Over ATM
	#define		CONST_ifType_voiceOverFrameRelay            153			//  Voice Over Frame Relay 
	#define		CONST_ifType_idsl							154			//  Digital Subscriber Loop over ISDN
	#define		CONST_ifType_compositeLink					155			//  Avici Composite Link Interface
	#define		CONST_ifType_ss7SigLink						156			//  SS7 Signaling Link 
	#define		CONST_ifType_propWirelessP2P				157			//  Prop. P2P wireless interface
	#define		CONST_ifType_frForward						158			//  Frame Forward Interface
	#define		CONST_ifType_rfc1483						159			//  Multiprotocol over ATM AAL5
	#define		CONST_ifType_usb							160			//  USB Interface
	#define		CONST_ifType_ieee8023adLag					161			//  IEEE 802.3ad Link Aggregate
	#define		CONST_ifType_bgppolicyaccounting            162			//  BGP Policy Accounting
	#define		CONST_ifType_frf16MfrBundle					163			//  FRF .16 Multilink Frame Relay 
	#define		CONST_ifType_h323Gatekeeper					164			//  H323 Gatekeeper
	#define		CONST_ifType_h323Proxy						165			//  H323 Voice and Video Proxy
	#define		CONST_ifType_mpls							166			//  MPLS	#define		CONST_ifType_
	#define		CONST_ifType_mfSigLink						167			//  Multi-frequency signaling link
	#define		CONST_ifType_hdsl2							168			//  High Bit-Rate DSL - 2nd generation
	#define		CONST_ifType_shdsl							169			//  Multirate HDSL2
	#define		CONST_ifType_ds1FDL							170			//  Facility Data Link 4Kbps on a DS1
	#define		CONST_ifType_pos							171			//  Packet over SONET/SDH Interface
	#define		CONST_ifType_dvbAsiIn						172			//  DVB-ASI Input
	#define		CONST_ifType_dvbAsiOut						173			//  DVB-ASI Output 
	#define		CONST_ifType_plc							174			//  Power Line Communtications
	#define		CONST_ifType_nfas							175			//  Non Facility Associated Signaling
	#define		CONST_ifType_tr008							176			//  TR008
	#define		CONST_ifType_gr303RDT						177			//  Remote Digital Terminal
	#define		CONST_ifType_gr303IDT						178			//  Integrated Digital Terminal
	#define		CONST_ifType_isup							179			//  ISUP
	#define		CONST_ifType_propDocsWirelessMaclayer       180			//  prop/Maclayer
	#define		CONST_ifType_propDocsWirelessDownstream     181			//  prop/Downstream
	#define		CONST_ifType_propDocsWirelessUpstream       182			//  prop/Upstream
	#define		CONST_ifType_hiperlan2						183			//  HIPERLAN Type 2 Radio Interface
	#define		CONST_ifType_propBWAp2Mp					184			//  PropBroadbandWirelessAccesspt2multipt
	#define		CONST_ifType_sonetOverheadChannel           185			//  SONET Overhead Channel
	#define		CONST_ifType_digitalWrapperOverheadChannel  186			//  Digital Wrapper
	#define		CONST_ifType_aal2							187			//  ATM adaptation layer 2
	#define		CONST_ifType_radioMAC						188			//  MAC layer over radio links
	#define		CONST_ifType_atmRadio						189			//  ATM over radio links   
	#define		CONST_ifType_imt							190			//  Inter Machine Trunks
	#define		CONST_ifType_mvl							191			//  Multiple Virtual Lines DSL
	#define		CONST_ifType_reachDSL						192			//  Long Reach DSL
	#define		CONST_ifType_frDlciEndPt					193			//  Frame Relay DLCI End Point
	#define		CONST_ifType_atmVciEndPt					194			//  ATM VCI End Point
	#define		CONST_ifType_opticalChannel					195			//  Optical Channel
	#define		CONST_ifType_opticalTransport				196			//  Optical Transport
	#define		CONST_ifType_propAtm						197			//  Proprietary ATM       
	#define		CONST_ifType_voiceOverCable					198			//  Voice Over Cable Interface
	#define		CONST_ifType_infiniband						199			//  Infiniband
	#define		CONST_ifType_teLink							200			//  TE Link
	#define		CONST_ifType_q2931							201			//  Q.2931
	#define		CONST_ifType_virtualTg						202			//  Virtual Trunk Group
	#define		CONST_ifType_sipTg							203			//  SIP Trunk Group
	#define		CONST_ifType_sipSig							204			//  SIP Signaling   
	#define		CONST_ifType_docsCableUpstreamChannel       205			//  CATV Upstream Channel
	#define		CONST_ifType_econet							206			//  Acorn Econet
	#define		CONST_ifType_pon155							207			//  FSAN 155Mb Symetrical PON interface
	#define		CONST_ifType_pon622							208			//  FSAN622Mb Symetrical PON interface
	#define		CONST_ifType_bridge							209			//  Transparent bridge interface
	#define		CONST_ifType_linegroup						210			//  Interface common to multiple lines	#define		CONST_ifType_
	#define		CONST_ifType_voiceEMFGD						211			//  voice E&M Feature Group D
	#define		CONST_ifType_voiceFGDEANA					212			//  voice FGD Exchange Access North American
	#define		CONST_ifType_voiceDID						213			//  voice Direct Inward Dialing
	#define		CONST_ifType_mpegTransport					214			//  MPEG transport interface
	#define		CONST_ifType_sixToFour						215			//  6to4 interface
	#define		CONST_ifType_gtp							216			//  GTP              GPRS Tunneling Protocol)
	#define		CONST_ifType_pdnEtherLoop1					217			//  Paradyne EtherLoop 1
	#define		CONST_ifType_pdnEtherLoop2					218			//  Paradyne EtherLoop 2
	#define		CONST_ifType_opticalChannelGroup            219			//  Optical Channel Group
	#define		CONST_ifType_homepna						220			//  HomePNA ITU-T G.989			#define		CONST_ifType_
	#define		CONST_ifType_gfp							221			//  Generic Framing Procedure              GFP)
	#define		CONST_ifType_ciscoISLvlan					222			//  Layer 2 Virtual LAN using Cisco ISL
	#define		CONST_ifType_actelisMetaLOOP				223			//  Acteleis proprietary MetaLOOP High Speed Link 
	#define		CONST_ifType_fcipLink						224			//  FCIP Link 






	#define		CONST_vlanType_ethernet						1
	#define		CONST_vlanType_fddi							2
	#define		CONST_vlanType_tokenRing					3
	#define		CONST_vlanType_fddiNet						4
	#define		CONST_vlanType_trNet						5
	#define		CONST_vlanType_deprecated					6

	#define		CONST_ciscoNetworkProtocolType_ip					1
	#define		CONST_ciscoNetworkProtocolType_decnet				2
	#define		CONST_ciscoNetworkProtocolType_pup					3
	#define		CONST_ciscoNetworkProtocolType_chaos				4
	#define		CONST_ciscoNetworkProtocolType_xns					5
	#define		CONST_ciscoNetworkProtocolType_x121					6
	#define		CONST_ciscoNetworkProtocolType_appletalk			7
	#define		CONST_ciscoNetworkProtocolType_clns					8
	#define		CONST_ciscoNetworkProtocolType_lat					9
	#define		CONST_ciscoNetworkProtocolType_vines				10
	#define		CONST_ciscoNetworkProtocolType_cons					11
	#define		CONST_ciscoNetworkProtocolType_apollo				12
	#define		CONST_ciscoNetworkProtocolType_stun					13
	#define		CONST_ciscoNetworkProtocolType_novell				14
	#define		CONST_ciscoNetworkProtocolType_qllc					15
	#define		CONST_ciscoNetworkProtocolType_snapshot				16
	#define		CONST_ciscoNetworkProtocolType_atmIlmi				17
	#define		CONST_ciscoNetworkProtocolType_bstun				18
	#define		CONST_ciscoNetworkProtocolType_x25pvc				19
	#define		CONST_ciscoNetworkProtocolType_unknown				65535



/*
typedef  struct  __qySnmpArg_t					{

				 char							ver[8  +  1];			//  v1 v2c v3
				 char							community[128  +  1];
				 char							usm[128  +  1];
				 char							authMethod[32  +  1];
				 char							authStr[128  +  1];
				 char							privMethod[32  +  1];
				 char							privStr[128  +  1];
				 char							engineId[128  +  1];
 
}		 QY_SNMP_ARG;
*/
#define		QY_SNMP_ARG		QY_SNMPOBJPOLICY_RCD		//  2003/11/09修改

typedef  struct  __qySnmpPolicyGrpRcd_t			{
		
				 char							name[64  +  1];
				 char							snmpVer[32  +  1];
				 char							getCommunity[255  +  1];
				 char							setCommunity[255  +  1];
				 char							usmName[255  +  1];
				 char							securityLevel[8  +  1];				//  0 表noAuthPriv, 
																					//	1 表authNoPriv,
																					//	2 表authPriv
				 char							authMethod[32  +  1];
				 char							authStr[128  +  1];
				 char							privMethod[32  +  1];
				 char							privStr[128  +  1];
				 char							engineId[128  +  1];

}		 QY_SNMPPOLICYGRP_RCD;

typedef  struct  __qySnmpObjPolicyRcd_t			{

				 char							ip[15  +  1];
				 TCHAR							cusName[64  +  1];
				 TCHAR							grpName[64  +  1];
				 char							snmpVer[32  +  1];
				 char							getCommunity[255  +  1];
				 char							setCommunity[255  +  1];
				 char							usmName[255  +  1];
				 char							securityLevel[8  +  1];		//  0 表noAuthPriv, 
																			//	1 表authNoPriv,
																			//	2 表authPriv
				 char							authMethod[32  +  1];
				 char							authStr[128  +  1];
				 char							privMethod[32  +  1];
				 char							privStr[128  +  1];
				 char							engineId[128  +  1];

				 char							col0[255  +  1];
				 char							col1[255  +  1];
				 char							col2[255  +  1];
				 char							col3[255  +  1];
				 char							col4[255  +  1];
				 char							comment[255  +  1];

}		 QY_SNMPOBJPOLICY_RCD;



//  2005/03/05
typedef  struct  __qySnmpObjRuleRcd_t			{
				 int							id;
				 int							iType;							//  规则类型
				 char							switchMac[12  +  1];
				 int							iPortIfIndex;
				 int							ibDirectConn;					//  是否接入层交换机, 2005/03/05
				 //  int							ibDownPortIfMacChanged;		
				 int							ibDownPortIfMacNew;				//  是否阻止端口如果mac的接入新增时, 2005/03/05
				 int							ibDownPortIfMacChangePort;		//  更换端口,  2006/04/28
				 int							ibNotLogIfMacChanged;			//  是否记录,  2006/04/28
				 unsigned  int					warnPercentOfBandWithFactor;	//  用CONST_fakedFactor_percentOfBand放大的参数			
				 //  int							iProcType;						//  处理动作
				 int							ibDownPortIfWarnSpeed;			//  流量报警时是否阻断端口，2006/05/29
				 //  char						comment0[255  +  1];
}		 QY_SNMPOBJRULE_RCD;


typedef  struct  __qnmConflictConnRcd_t			{
				 int							id;
				 int							iType;
				 char							switchMac[12  +  1];
				 char							connectedMac[12  +  1];
				 int							iPortIfIndex;
				 char							firstTime[14  +  1];
				 unsigned  char					ucbLocked;
				 //  int						iFlg;
				 //  char							comment0[255  +  1];
}		 QNM_CONFLICTCONN_RCD;
							





#define		MACRO_snmpObjRcdMems																		\
				int								iIpForwarding;					/*  1 路由器，2 非路由器	*/	\
				unsigned  char					ucbBridge;						/*  是否桥					*/	\
				unsigned  char					ucbHost;						/*  是否主机				*/	\
				TCHAR							sysDescr[1024  +  1];			/*  概述					*/	\
				int								iMaker;													\
				TCHAR							maker[128  +  1];				/*  厂商					*/	\
				TCHAR							productName[128  +  1];			/*  产品名字				*/	\
				long							lNetDevType;					/*  设备类型				*/	\
				char							ip[15  +  1];					/*  ip						*/	\
				char							mac[12  +  1];					/*  mac						*/	\
				unsigned  int					uiIfNumber;						/*  端口数					*/	\
				int								iManagementDomainLocalMode;		/*  vtp client 1, server 2, transparent 3, 2004/06/06加  */		\
				int								iCpsGlobalMaxSecureAddress;		/*							*/	\
				int								iCpsGlobalTotalSecureAddress;	/*							*/	\
				unsigned  char					ucbCpsGlobalPortSecurityEnable;	/*							*/	\
				long							lStatus;						/*  设备状态				*/	\
				TCHAR							cusName[64  +  1];				/*  别名					*/	\
				TCHAR							place[255  +  1];				/*  使用地点				*/	\
				char							firstTime[14  +  1];			/*  最先扫描到的时间		*/	\
				char							lastTime[14  +  1];				/*  最新扫描到的时间		*/	\
				char							auditTime[14  +  1];			/*  审核时间，2004/04/09	*/
										



/*
typedef  struct  __qySnmpObjRcd_t				{

				 MACRO_snmpObjRcdMems
					
}		 QY_SNMPOBJ_RCD;
*/


#define		CONST_portStatus_up					1
#define		CONST_portStatus_down				2
#define		CONST_portStatus_test				3		



typedef  struct  __qySwitchPortRcd_t			{
				 char							switchMac[12  +  1];				//
				 int							iPortIfIndex;						//  switchMac,portIfIndex
				 char							portIfDescr[255  +  1];		
				 int							iPortIfType;
				 int							iPortIfSpeedInK;					//  
				 char							portIfPhysAddress[32  +  1];		//  
				 int							iPortIfAdminStatus;					//  1 up, 2 down, 3 test	
				 int							iPortIfOperStatus;					//  1 up, 2 down, 3 test
				 
				 //  int						iPortIfInOctets;					//  
				 //  int						iPortIfOutOctets;					//  
				 __int64						i64PortIfInOctets;					//  2011/02/15
				 __int64						i64PortIfOutOctets;					//  
					int							iTimeInSecondOfGettingInOctets;		//  
					int							iTimeInSecondOfGettingOutOctets;	//  

				 int							iPortIfInSpeedInK;					//  
				 int							iPortIfOutSpeedInK;					//  
				 int							iBridgePort;
				 long							lVlanId;
				 //  char						vlanName[255  +  1];				//  暂时不用
				 int							iVmVlanType;						//  static 1, dynamic 2, multiVlan 3, 2004/06/06
				 char							firstTime[14  +  1];				//  最先扫描到的时间
				 char							lastTime[14  +  1];					//  最新扫描到的时间
				 //  char						comment[255  +  1];

				 
				 //  2006/04/28
				 QY_SNMPOBJRULE_RCD				rule;	

				 //  以下为处理变量，非数据库成员, 2005/03/06
				 //
				 unsigned  short				nNewConns;
				 unsigned  short				nConnModifieds;
				 unsigned  short				nConflictConnModifieds;				//  有冲突的联接变更指不包括回到原位的联接变更
				 unsigned  short				nWarnSpeed;							//  流量报警次数, 先判断一次，需要时过5秒再判断一次, 2006/05/30
}		 QY_SWITCHPORT_RCD;


typedef  struct  __qyVlanRcd_t					{
				 long							id;
				 char							name[255  +  1];
				 long							lStatus;
				 long							lType;
				 //  char							comment[255  +  1];
}		 QY_VLAN_RCD;


typedef  struct  __qySnmpRcdIpMac_t				{
				 unsigned  long					ulIp;
				 char							mac[12  +  1];
}		 QY_SNMPRCD_IPMAC;

typedef  struct  __qySnmpRcdMacBport_t			{
				 char							mac[12  +  1];
				 unsigned  long					ulBport;
}		 QY_SNMPRCD_MACBPORT;

typedef  struct  __qySnmpRcdIpIfIndex_t			{
				 unsigned  long					ulIp;
				 int							iIfIndex;
}		 QY_SNMPRCD_IPIFINDEX;

typedef  struct  __qySnmpRcdSecurMac_t			{
				 int							iIfIndex;
				 char							mac[12  +  1];
				 int							iVal;
}		 QY_SNMPRCD_SECUREMAC;


//  建与switchPort相关联的设备信息的表
typedef  struct  __qySwitchConnectedDevRcd_t	{
				 char							switchMac[12  +  1];	
				 int							iPortIfIndex;
				 long							lDeviceIndex;
				 long							lAddressType;
				 char							address[255  +  1];			
				 char							version[255  +  1];
				 char							devicePortDescr[255  +  1];
				 char							platform[255  +  1];
				 char							firstTime[14  +  1];		//  最先扫描到的时间
				 char							lastTime[14  +  1];			//  最新扫描到的时间									
				 char							comment[255  +  1];
}		 QY_SWITCHCONNECTEDDEV_RCD;


//  建与switchPort相关联的主机信息的表
typedef  struct  __qySwitchConnectedPcRcd_t		{
				 char							connectedMac[12  +  1];		//	connectedMac构成键值
				 char							connectedIp[15  +  1];		//
				 char							switchMac[12  +  1];		//
				 int							iPortIfIndex;				//
				 char							firstTime[14  +  1];		//  最先扫描到的时间
				 char							lastTime[14  +  1];			//  最新扫描到的时间									
				 char							auditTime[14  +  1];		//  审核时间，2004/04/09
				 unsigned  char					ucbDirectConn;				//  是否直接接入
				 char							comment[255  +  1];			//
}		 QY_SWITCHCONNECTEDPC_RCD;


typedef  struct  __qySwitchIfPortSecurityRcd_t	{
				 char							switchMac[12  +  1];
				 int							iPortIfIndex;
				 unsigned  char					ucbCpsIfPortSecurityEnable;
				 int							iCpsIfPortSecurityStatus;	//  secureup(1), securedown(2), shutdown(3)
				 int							iCpsIfMaxSecureMacAddr;
				 int							iCpsIfCurrentSecureMacAddrCount;
				 int							iCpsIfViolationAction;		//  shutdown(1), dropNotify(2), drop(3) 
				 char							lastTime[14  +  1];			//  最新扫描到的时间
				 char							comment0[255  +  1];
}		 QY_SWITCHIFPORTSECURITY_RCD;


typedef  struct  __qySwitchSecureMacRcd_t		{
				 char							switchMac[12  +  1];
				 int							iPortIfIndex;
				 char							secureMac[12  +  1];
				 int							iCpsSecureMacAddrType;		//  static(1), dynamic(2)
				 int							iCpsSecureMacAddrRowStatus;	//  active(1), notInService(2), notReady(3), createAndGo(4), createAndWait(5), destroy(6)
				 char							lastTime[14  +  1];			//  最新扫描到的时间
				 char							comment0[255  +  1];
}		 QY_SWITCHSECUREMAC_RCD;



//  下面限定了最多端口数的限制
#define		CONST_maxSwitchPorts				1024
#define		CONST_maxVlans						128
#define		CONST_maxConnectedDevs				128

//  snmp对象结构

typedef  struct  __qySnmpObjHead_t				{		//  该头结构为用于某些简化的设备处理结构
				 int							iType;	//  务必与下面的结构一致
				 MACRO_snmpObjRcdMems
}		 QY_SNMPOBJ_HEAD;

typedef  struct  __qySnmpObj_t					{		//  务必与上面的结构一致
				 int							iType;
				 MACRO_snmpObjRcdMems
				 //
 				 QY_SWITCHPORT_RCD				ports[CONST_maxSwitchPorts];
				 char							sysStartTime[14  +  1];				//  启动时间
				 unsigned  short				usConnectedDevs;
				 QY_SWITCHCONNECTEDDEV_RCD		connectedDevs[CONST_maxConnectedDevs];
				 //
				 QY_SNMPOBJRULE_RCD				rule;								//  2005/03/07加
				 //
				 unsigned  short				usWarnSpeedPorts;					//  2006/05/30, 报警端口数
				 
}		 QY_SNMP_OBJ;


typedef  struct  __qySwitch_t					{
				 QY_SNMP_OBJ					common;
				 unsigned  short				usVlans;
				 QY_VLAN_RCD					vlans[CONST_maxVlans];
}		 QY_SWITCH;


//  以下是对交换机等网络设备的操作命令
#define		CONST_snmpOpCmd_null										0
#define		CONST_snmpOpCmd_refresh										1		//  刷新
#define		CONST_snmpOpCmd_willAttack									2		//  阻断某端口
#define		CONST_snmpOpCmd_stopWillAttack								3		//  停止阻断(或开放)某端口
//  #define		CONST_snmpOpCmd_beStaticAccessMode						4		//  设置静态访问模式
#define		CONST_snmpOpCmd_beStaticAccessModeAndEnableIfPortSecurity	5		//  设置静态访问模式并启用端口绑定
#define		CONST_snmpOpCmd_disableIfPortSecurity						6		//  停用端口绑定
#define		CONST_snmpOpCmd_setCpsIfMaxSecureMacAddr					7
#define		CONST_snmpOpCmd_secureMac									8
#define		CONST_snmpOpCmd_cancelSecureMac								9
#define		CONST_snmpOpCmd_monFlow										10		//  监控流量
#define		CONST_snmpOpCmd_monIfFlow									11		//  监控端口的流量


//  以下是交换机状态
#define		CONST_snmpObjStatus_online									0		
#define		CONST_snmpObjStatus_offline									1


/////
#define		CONST_vlanTrunkPortDynamicState_on							1
#define		CONST_vlanTrunkPortDynamicState_off							2
#define		CONST_vlanTrunkPortDynamicState_desirable					3
#define		CONST_vlanTrunkPortDynamicState_auto						4
#define		CONST_vlanTrunkPortDynamicState_onNoNegotiate				5

#define		CONST_snmpTrue												1
#define		CONST_snmpFalse												2

//
#define		CONST_managementDomainLocalMode_client						1
#define		CONST_managementDomainLocalMode_server						2
#define		CONST_managementDomainLocalMode_transparent					3


//  将下列标识放在产品型号前，则库中的productName不包含厂家名，要入数据库，切勿修改
#define		CONST_snmpOemSym											"   "




#endif  /*  }  */




