using System;
using System.Collections.Generic;
using System.Text;

//
partial class Consts
{
    //
    //public const string CONST_subDir_isCli = "isCli";
    public const string CONST_cfgFile_login_isCli = "login_isCli.cfg";
    public const string CONST_cfgFile_dbg_isCli = "dbg_isCli.cfg";


    //
    public const string CONST_cfgName_server = "server";
    public const string CONST_cfgName_usr = "usr";
    public const string CONST_cfgName_passwd = "passwd";

    //
    public const string CONST_cfgName_statusServer = "statusServer";


    //
    public const int CONST_msg_cameraOpen = 10000;

    


    //
    public const int CONST_iFgType_dlgTalk_av = 1;
    public const int CONST_iFgType_dlgTalk_av2 = 2;

    //
    public const float CONST_fz_z1 = CONST_fz_me;//1f - 0.0000001f;
    public const float CONST_fz_peer = 1f - 0.000001f;
    public const float CONST_fz_me   = 1f - 0.000002f;




}

//
namespace qy
{
    public delegate uint PF_myGetTickCount();

    public delegate int PF_myGetPid();
    public delegate int PF_myGetTid();

    //
    public delegate int PF_PostMessage(object wnd, int msgId,int wParm,int lParam);
    public delegate bool PF_IsWindow(object hWnd);
    //
    public delegate int PF_PostMessage_new(object wnd, int iWndContenType, int msgId, int wParm, int lParam);
    //
    public delegate object PF_mainWnd_getVar();
    //
    public delegate int PF_gui_procMsg(IntPtr pMsgParam);
    public delegate int PF_gui_dlgTalk_procMsg(object hTalkParam, IntPtr pMsgParam);
    //
    public delegate int PF_gui_notify_cancel();
    public delegate int PF_gui_notify_chk();
    //
    public delegate int PF_gui_notify_doCmd(ushort usOp);
    //
    public delegate int PF_mainWnd_setTimer();
    public delegate void PF_mainWnd_killTimer();

    //
    public delegate int PF_findTalker(CCtxQyMc pQyMc, MIS_CNT pMisCnt, QY_MESSENGER_ID pIdInfo, ref object phWnd);
    public delegate int PF_dlgTalk_qPostMsg(object hDlgTalk, IntPtr pQElem, uint size);

    //
    public delegate int PF_gui_displayNotification(CCtxQmc pProcInfo, IntPtr pMIS_MSG_taskStatus);

    //
    public delegate int PF_testInMain(CCtxQyMc pQyMc);

    //
    public delegate int PF_dumpData(byte[] data, int w, int h, bool bAppend, bool bFileName_haveTime, string pureFileName);
    public delegate int PF_dumpData1(IntPtr data, int len, int w, int h, bool bAppend, bool bFileName_haveTime, string pureFileName);
    public delegate int PF_dumpRgb32(byte[] data, int w, int h, string pureFileName);
    public delegate int PF_dumpRgb32_1(IntPtr data, int w, int h, string pureFileName);
    public delegate int PF_dumpBmp(object bitmap, string pureFileName);

    //
    public delegate int PF_dumpAudio_init();
    public delegate int PF_dumpAudio_exit();
    public delegate int PF_dumpAudio(IntPtr data, int size);




    //
    public delegate int PF_logd(string tag, string str);


    //
    public delegate int PF_initPolicyAvParams();  //  要在登陆后立即运行此函数. 2011/10/22
    public delegate int PF_getPolicyIsClient(CCtxQmc pProcInfo, out POLICY_isClient p);
    public delegate int PF_getPolicyAvLevel(CCtxQyMc pQyMc, uint uiCapType, uint uiSubCapType, int iCapUsage);


    //
    public delegate int PF_initVideoCapDev(object hTalk, int iWndContentType, string displayName_selected, ref BITMAPINFOHEADER pBih_suggested, CAP_procInfo_bmpCommon pCapBmp);
    public delegate int PF_exitVideoCapDev(object hTalk, int iWndContentType);
    public delegate bool PF_bGetCapturePara(object hTalk, int iWndContentType, ref QY_VIDEO_HEADER pVh_org);
    public delegate int PF_startCapture(object hTalk, int iWndContentType);
    public delegate int PF_stopCapture(object hTalk, int iWndContentType);


    //
    public delegate int PF_i420ToRgb(IntPtr yuv, object yri, int rgbBits, bool bBgr, int width, int height, bool bFlipImg);

    //
    public delegate int PF_talk_updatePlayerInfo(object hTalk, IntPtr pMsg, PLAYER_ID playerId);
    public delegate int PF_talk_addNewMsg(object hTalkParam, QY_MESSENGER_ID pIdInfo_from, Int64 tSendTime,uint uiTranNo, ushort usCode, uint uiContentType, string msg, int iTaskId,int iStatus);


    //
    public delegate int PF_loadCusModule_android();

    public delegate int PF_doDecodeVideo_mediaCodec(QY_TRANSFORM pTransform, int index_activeMems_from, IntPtr pMsgBuf);
    public delegate int PF_doEncodeVideo_mediaCodec(CAP_procInfo_bmpCommon pCapProcInfo, MIS_CNT pMisCnt, IntPtr pMsgBuf);
    public delegate int PF_doDecodeAudio_mediaCodec(QY_TRANSFORM pTransform, int index_pMems_from1, int index_activeMems_from, IntPtr pMsgBuf);

    //
    public delegate int PF_stopLocalAudioRecorder(CCtxQmc pProcInfo, int index_sharedObj, int nTries);

    public delegate int PF_startPlayAudio_android(QY_PLAYER pPlayerParam);
    public delegate int PF_stopPlayAudio_android(QY_PLAYER pPlayerParam);

    public delegate int PF_startPlayVideo_android(QY_PLAYER pPlayerParam);
    public delegate int PF_stopPlayVideo_android(QY_PLAYER pPlayerParam);


    public delegate int PF_readDbgCfg(ref string m_statusServer);

    //
    public delegate int PF_new_DLG_TALK_videoConference(int index_taskInfo);
    public delegate void PF_free_DLG_TALK_videoConference(ref int obj_videoConference);
    public delegate DLG_TALK_videoConference PF_getVideoConference(int obj_videoConference);

    //
    public delegate int PF_new_QMC_taskData(int index_taskInfo,int taskDataType);
    public delegate void PF_free_QMC_taskData(ref int obj_taskData);
    public delegate QMC_taskData_common PF_getTaskData(int obj_taskData);


    //
    public static class GuiShare
    {
            public static PF_myGetTickCount pf_myGetTickCount;
            public static PF_myGetPid pf_myGetPid;
            public static PF_myGetTid pf_myGetTid;
            //
            public static PF_PostMessage pf_PostMessage;
            public static PF_IsWindow pf_IsWindow;
            //
            public static PF_PostMessage_new pf_PostMessage_new;
            //
            public static PF_mainWnd_getVar pf_mainWnd_getVar;
            //
            public static PF_gui_procMsg pf_gui_procMsg;
            public static PF_gui_dlgTalk_procMsg pf_gui_dlgTalk_procMsg;
            //
            public static PF_gui_notify_cancel pf_gui_notify_cancel;
            public static PF_gui_notify_chk pf_gui_notify_chk;
            //
            public static PF_gui_notify_doCmd pf_gui_notify_doCmd;
            //
            public static PF_mainWnd_setTimer pf_mainWnd_setTimer;
            public static PF_mainWnd_killTimer pf_mainWnd_killTimer;

            //
            public static PF_findTalker pf_findTalker;
            public static PF_dlgTalk_qPostMsg pf_dlgTalk_qPostMsg;

            //
            public static PF_gui_displayNotification pf_gui_displayNotification;

        //
        public static PF_testInMain pf_testInMain;

        //
        public static PF_dumpData pf_dumpData;
        public static PF_dumpData1 pf_dumpData1;
        public static PF_dumpRgb32 pf_dumpRgb32;
        public static PF_dumpRgb32_1 pf_dumpRgb32_1;
        public static PF_dumpBmp pf_dumpBmp;

        //
        public static PF_dumpAudio_init pf_dumpAudio_init;
        public static PF_dumpAudio_exit pf_dumpAudio_exit;
        public static PF_dumpAudio pf_dumpAudio;

        //
        public static PF_logd pf_logd;

        //
        public static PF_initPolicyAvParams pf_initPolicyAvParams;
        public static PF_getPolicyIsClient pf_getPolicyIsClient;
        public static PF_getPolicyAvLevel pf_getPolicyAvLevel;

        //
        public static PF_initVideoCapDev pf_initVideoCapDev;
        public static PF_exitVideoCapDev pf_exitVideoCapDev;
        public static PF_bGetCapturePara pf_bGetCapturePara;
        public static PF_startCapture pf_startCapture;
        public static PF_stopCapture pf_stopCapture;


        //
        public static PF_i420ToRgb pf_i420ToRgb;

        //
        public static PF_talk_updatePlayerInfo pf_talk_updatePlayerInfo;
        public static PF_talk_addNewMsg pf_talk_addNewMsg;


        //
        public static PF_loadCusModule_android pf_loadCusModule_android;
        public static PF_doDecodeVideo_mediaCodec pf_doDecodeVideo_mediaCodec;
        public static PF_doEncodeVideo_mediaCodec pf_doEncodeVideo_mediaCodec;
        public static PF_doDecodeAudio_mediaCodec pf_doDecodeAudio_MediaCodec;

        //
        public static PF_stopLocalAudioRecorder pf_stopLocalAudioRecorder;
        public static PF_startPlayAudio_android pf_startPlayAudio_android;
        public static PF_stopPlayAudio_android pf_stopPlayAudio_android;

        public static PF_startPlayVideo_android pf_startPlayVideo_android;
        public static PF_stopPlayVideo_android pf_stopPlayVideo_android;

        //
        public static PF_readDbgCfg pf_readDbgCfg;

        //
        public static PF_new_DLG_TALK_videoConference pf_new_DLG_TALK_videoConference;
        public static PF_free_DLG_TALK_videoConference pf_free_DLG_TALK_videoConference;          
        public static PF_getVideoConference pf_getVideoConference;

        //
        public static PF_new_QMC_taskData pf_new_QMC_taskData;
        public static PF_free_QMC_taskData pf_free_QMC_taskData;
        public static PF_getTaskData pf_getTaskData;

        //
    };




}
