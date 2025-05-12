#pragma once
#include <map>
#include <memory>
#include <mutex>
#include <functional>

#include "flv_def.h"
#include "flv_session.h"

class FLVSessionMrg;
typedef std::unique_ptr<FLVSessionMrg> FLVSessionMrgPtr;

static FLVSessionMrgPtr g_flv_session_mrg;
static std::mutex g_flv_session_mrg_mutex;

//singleton
class FLVSessionMrg
{
public:
    ~FLVSessionMrg();

    static FLVSessionMrg& GetInstance()
    {
        if(g_flv_session_mrg == nullptr)
        {   
            std::lock_guard<std::mutex> lock(g_flv_session_mrg_mutex);
            if(g_flv_session_mrg == nullptr)
            {
                g_flv_session_mrg.reset(new FLVSessionMrg());
            }
         }
        return *g_flv_session_mrg;
    };
    
    uint32_t CreateSession(MediaDesc* media_desc);
    
    void DestroySession(SESSION_ID id);

    uint32_t SetCallback(SESSION_ID id, FLVCallBackFunc cb);
    
    uint32_t PushAVFrame(SESSION_ID id,const AVFrame& frame);
    
private:
    FLVSessionMrg();

    SESSION_ID addSession(FLVSessionPtr session);
    SESSION_ID removeSession(SESSION_ID id);
    FLVSessionPtr getSession(SESSION_ID id);


private:
    std::mutex session_mutex_;
    std::map<SESSION_ID, FLVSessionPtr> session_map_;
    /* data */

};
