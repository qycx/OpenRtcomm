
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MSGRMGRMODULE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MSGRMGRMODULE_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef MSGRMGRMODULE_EXPORTS
#define MSGRMGRMODULE_API __declspec(dllexport)
#else
#define MSGRMGRMODULE_API __declspec(dllimport)
#endif

// This class is exported from the msgrMgrModule.dll
class MSGRMGRMODULE_API CMsgrMgrModule {
public:
	CMsgrMgrModule(void);
	// TODO: add your methods here.
};

extern MSGRMGRMODULE_API int nMsgrMgrModule;

MSGRMGRMODULE_API int fnMsgrMgrModule(void);

