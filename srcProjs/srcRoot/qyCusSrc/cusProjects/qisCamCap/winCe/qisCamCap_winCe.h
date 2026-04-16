// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the QISCAMCAP_WINCE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// QISCAMCAP_WINCE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef QISCAMCAP_WINCE_EXPORTS
#define QISCAMCAP_WINCE_API __declspec(dllexport)
#else
#define QISCAMCAP_WINCE_API __declspec(dllimport)
#endif

// This class is exported from the qisCamCap_winCe.dll
class QISCAMCAP_WINCE_API CqisCamCap_winCe {
public:
	CqisCamCap_winCe(void);
	// TODO: add your methods here.
};

extern QISCAMCAP_WINCE_API int nqisCamCap_winCe;

QISCAMCAP_WINCE_API int fnqisCamCap_winCe(void);
