#ifndef __FLV_PACKER_H__
#define __FLV_PACKER_H__

#include "flv_def.h"

#ifdef __cplusplus
extern "C"
{
#endif

// 初始化SDK
FLVSDK_API FLVSDK_ERR_CODE FLV_CALL FLVSDK_Init();

// 反初始化SDK
FLVSDK_API FLVSDK_ERR_CODE FLV_CALL FLVSDK_UnInit();

// 创建打包器
// ret: packer id (为0表示失败)
FLVSDK_API SESSION_ID FLV_CALL FLVSDK_CreatePacker(MediaDesc* media_desc);

// 设置回调
FLVSDK_API FLVSDK_ERR_CODE FLV_CALL FLVSDK_SetFlvDataCallback(SESSION_ID packer_id,FLVDataCallback callback, void* user_data);

// 推送音视频帧
FLVSDK_API FLVSDK_ERR_CODE FLV_CALL FLVSDK_PushAVFrame(SESSION_ID packer_id, AVFrame* av_frame);

// 销毁打包器
FLVSDK_API FLVSDK_ERR_CODE FLV_CALL FLVSDK_DestroyPacker(SESSION_ID packer_id);

#ifdef __cplusplus
};
#endif

#endif //__FLV_PACKER_H__
