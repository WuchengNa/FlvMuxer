#ifndef __FLV_PACKER_H__
#define __FLV_PACKER_H__

#include "flv_def.h"

#ifdef __cplusplus
extern "C"
{
#endif

FLVSDK_API int FLC_CALL FLVSDK_Init();

FLVSDK_API int FLC_CALL FLVSDK_UnInit();

FLVSDK_API int FLC_CALL FLVSDK_CreatePacker();

FLVSDK_API int FLC_CALL FLVSDK_PushAVFrame();

FLVSDK_API int FLC_CALL FLVSDK_DestroyPacker();

#ifdef __cplusplus
};
#endif

#endif //__FLV_PACKER_H__
