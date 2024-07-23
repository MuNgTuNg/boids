#pragma once

namespace shb{
enum Platform{
    PLATFORM_UNDEFINED,
    PLATFORM_WIN32,
    PLATFORM_WIN64,
    PLATFORM_LINUX,
    NUM_PLATFORMS
};

#if defined(_WIN32)
#define CURRENT_PLATFORM PLATFORM_WIN32

#elif defined(_WIN64)
#define CURRENT_PLATFORM PLATFORM_WIN64

#elif defined(__linux__)
#define CURRENT_PLATFORM PLATFORM_LINUX

#else 
#define CURRENT_PLATFORM PLATFORM_UNDEFINED

#endif

}//namespace shb