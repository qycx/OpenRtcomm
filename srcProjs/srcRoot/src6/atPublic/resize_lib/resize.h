#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <NvInfer.h>
#include <cuda_runtime.h>
#include<opencv2/opencv.hpp>
using namespace nvinfer1;
using namespace std;
#define DLL_EXPORTS
#ifdef DLL_EXPORTS
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif
// --- SRTensorRT 核心推理类 (简化版) ---
 class DLLAPI SRTensorRT {
private:
    int last_w = 0, last_h = 0;

    string input_path;
    string output_path;
    // 输入：144P (256x144)
    int INPUT_W = 0;
    int INPUT_H = 0;
    // 输出：4x 缩放 (1024x576)
    int OUTPUT_W = INPUT_W;
    int OUTPUT_H = INPUT_H;
    size_t input_elements = (size_t)INPUT_W * INPUT_H * 3;
    size_t output_elements = (size_t)OUTPUT_W * OUTPUT_H * 3;

    // --- 宏定义：方便检查 CUDA API 调用错误 ---
#define CHECK_CUDA(call) { if((call) != cudaSuccess) { cerr << "CUDA Error: " << #call << " failed." << endl; exit(1); } }

// --- ILogger: 用于接收 TensorRT 的日志信息 ---
    class Logger : public ILogger {
    public:
        void log(Severity severity, const char* msg) noexcept override {
            // 在实际应用中，只显示严重错误或警告
            if (severity <= Severity::kWARNING) {
                cout << "[TRT Log] " << msg << endl;
            }
        }
    };

    // --- I/O Utility 函数 ---

    // 读取原始 RGB 文件到主机 float 缓冲区并归一化
    bool read_and_normalize_rgb(uchar* input_data, float* host_buffer, size_t input_size_elements);
       

    // 将主机 float 缓冲区数据写回原始 RGB 文件 (反归一化)
    void write_denormalized_rgb(const string& filename, float* host_buffer, size_t output_size_elements, uchar*& out_buf);

    int ratio = 2;
    IRuntime* runtime_ = nullptr;
    ICudaEngine* engine_ = nullptr;
    IExecutionContext* context_ = nullptr;
    void* buffers_[2]; // 0: Input, 1: Output
    // 核心推理方法：输入和输出都是 CPU 主机内存
    void infer(float* input_host_buffer, float* output_host_buffer, size_t input_size_bytes, size_t output_size_bytes, uchar*& out_buf);

public:

    void aiResize_init(const string& engine_path, int input_w,int input_h, int output_w, int output_h);
    void aiResize_do(int ori_w, int ori_h,uchar* input_data, int& out_w, int& out_h, uchar*& out_buf);
    void aiResize_exit();
};





