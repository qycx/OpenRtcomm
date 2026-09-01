
#pragma once

#include <vector>
#include <string>


bool SaveBMP(
    const std::wstring& filename,
    const unsigned char* data,
    int width,
    int height);
