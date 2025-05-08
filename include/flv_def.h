#ifndef __FLV_DEF_H__
#define __FLV_DEF_H__

#ifdef _WIN32
# ifdef FLVSDK_EXPORT
#   define FLVSDK_API extern "C" __declspec(dllexport)
# else
#   define FLVSDK_API extern "C" __declspec(dllimport)
# endif
#define FLC_CALL __stdcall
#elif defined(__linux__)
#ifdef FLVSDK_EXPORT
#   define FLVSDK_API extern "C" __attribute__((visibility("default")))
#else
#   define FLVSDK_API extern "C" __attribute__((visibility("hidden")))
#endif
#define FLC_CALL
#endif

#define FLV_CODE_OK 1
#define FLV_CODE_ERR 0

#endif //__FLV_DEF_H__