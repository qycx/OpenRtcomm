
#ifndef  __nvHelpPublic_h__
#define  __nvHelpPublic_h__		//  {

typedef  struct {
				int		index;
				WCHAR	name[128];
				int		major;
				int		minor;
}		 NvHelpInfo;


//
extern "C" __declspec(dllexport) int getNvHelpInfo(void* p0_reserved, int index, NvHelpInfo* p);




#endif  //   }

