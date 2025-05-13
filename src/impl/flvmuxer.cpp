#include "flvmuxer.h"
#include "session/flv_session_mrg.h"


FLVSDK_API FLVSDK_ERR_CODE FLV_CALL FLVSDK_Init()
{
    FLVSessionMrg::GetInstance();
    return FLV_CODE_OK;
}

FLVSDK_API FLVSDK_ERR_CODE FLV_CALL FLVSDK_UnInit()
{
    return FLV_CODE_OK;
}

FLVSDK_API SESSION_ID FLV_CALL  FLVSDK_CreatePacker(MediaDesc* media_desc)
{  
    return FLVSessionMrg::GetInstance().CreateSession(media_desc);  
}

FLVSDK_API FLVSDK_ERR_CODE FLV_CALL  FLVSDK_SetFlvDataCallback(SESSION_ID packer_id,FLVDataCallback callback, void* user_data)
{
    auto callback_func =
    [callback,user_data] (SESSION_ID packer_id, char* data, int size) {
        callback(packer_id,data,size,user_data);
    };
   return FLVSessionMrg::GetInstance().SetCallback(packer_id, callback_func);
}

FLVSDK_API FLVSDK_ERR_CODE FLV_CALL FLVSDK_PushAVFrame(SESSION_ID packer_id, AVFrame* av_frame)
{
    return FLVSessionMrg::GetInstance().PushAVFrame(packer_id, *av_frame);
}

FLVSDK_API FLVSDK_ERR_CODE FLV_CALL FLVSDK_DestroyPacker(SESSION_ID packer_id)
{
    FLVSessionMrg::GetInstance().DestroySession(packer_id);
    return FLV_CODE_OK;

}
