#include "flv_packer.h"
#include "flv_def.h"

// #define LOG_INFO(X) std::cout << X << std::endl

FLVSDK_API int FLC_CALL FLVSDK_Init()
{
    // LOG_INFO("[API] FLVSDK_Init");
    return FLV_CODE_OK;
}

FLVSDK_API int FLC_CALL FLVSDK_UnInit()
{
    // LOG_INFO("[API] FLVSDK_UnInit");
    return FLV_CODE_OK;
}

FLVSDK_API int FLC_CALL FLVSDK_CreatePacker()
{
    // LOG_INFO("[API] FLVSDK_CreatePacker");
    return FLV_CODE_OK;
}

FLVSDK_API int FLC_CALL FLVSDK_PushAVFrame()
{
    // LOG_INFO("[API] FLVSDK_PushAVFrame");
    return FLV_CODE_OK;
}

FLVSDK_API int FLC_CALL FLVSDK_DestroyPacker()
{
    // LOG_INFO("[API] FLVSDK_DestroyPacker");
    return FLV_CODE_OK;

}
