
#include	"stdafx.h"

#include <stdio.h>
#include <cuda_runtime.h>


//
#include	"nvHelpPublic.h"
#include <string>
#include "../../../../../qyOpen/include/tmpDefs_open.h"



extern "C" __declspec(dllexport) int getNvHelpInfo(void* p0_reserved, int index, NvHelpInfo* p)
{
	if (!p)  return  -1;
	memset(p, 0, sizeof(*p));


    cudaDeviceProp prop;
    cudaError_t err = cudaGetDeviceProperties(&prop, 0); // 获取设备0的属性

    if (err != cudaSuccess) {
        printf("CUDA错误: %s\n", cudaGetErrorString(err));
        return 1;
    }

    // 获取计算能力主版本号和次版本号
    int major = prop.major;
    int minor = prop.minor;

    printf("GPU: %s\n", prop.name);
    printf("CUDA 计算能力: %d.%d\n", major, minor);

    //    
    std::string name = prop.name;
    std::wstring wstr;
    wstr.assign(name.begin(), name.end());

    lstrcpyn(p->name, wstr.c_str(), mycountof(p->name));
    p->major = prop.major;
    p->minor = prop.minor;





	//
	return  0;
}


#if  0
int main() {
    cudaDeviceProp prop;
    cudaError_t err = cudaGetDeviceProperties(&prop, 0); // 获取设备0的属性

    if (err != cudaSuccess) {
        printf("CUDA错误: %s\n", cudaGetErrorString(err));
        return 1;
    }

    // 获取计算能力主版本号和次版本号
    int major = prop.major;
    int minor = prop.minor;

    printf("GPU: %s\n", prop.name);
    printf("CUDA 计算能力: %d.%d\n", major, minor);

    // 根据计算能力判断推荐的SDK版本
    if (major >= 9) { // 计算能力 9.0+ (Hopper, Blackwell)
        printf("架构较新，建议使用: Video Codec SDK 13.1\n");
    }
    else if (major >= 8) { // 计算能力 8.x (Ampere, Ada)
        if (minor >= 9) { // 8.9 (Ada Lovelace)
            printf("Ada Lovelace架构，建议使用: Video Codec SDK 13.1\n");
        }
        else {
            printf("Ampere架构，可使用: Video Codec SDK 13.1 或 11.1.5\n");
        }
    }
    else if (major >= 7) { // 计算能力 7.x (Volta, Turing)
        printf("Turing/Volta架构，可使用: Video Codec SDK 13.1 或 11.1.5\n");
    }
    else if (major >= 6) { // 计算能力 6.x (Pascal)
        printf("Pascal架构，建议优先尝试: Video Codec SDK 13.1\n");
    }
    else if (major >= 5) { // 计算能力 5.x (Maxwell)
        printf("Maxwell架构，建议使用: Video Codec SDK 11.1.5\n");
    }
    else {
        printf("架构较老，建议使用: Video Codec SDK 11.1.5 或更早版本\n");
    }

    return 0;
}
#endif 