// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the QISCAMCAP_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// QISCAMCAP_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef QISCAMCAP_EXPORTS
#define QISCAMCAP_API __declspec(dllexport)
#else
#define QISCAMCAP_API __declspec(dllimport)
#endif

// This class is exported from the qisCamCap.dll
class QISCAMCAP_API CqisCamCap {
public:
	CqisCamCap(void);
	// TODO: add your methods here.
};

extern QISCAMCAP_API int nqisCamCap;

QISCAMCAP_API int fnqisCamCap(void);
