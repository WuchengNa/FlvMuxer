#include "flv_session.h"
#include "flv_session_mrg.h"
#include "util/util.h"

FLVSessionMrg::FLVSessionMrg(){

}

FLVSessionMrg::~FLVSessionMrg(){

}

uint32_t FLVSessionMrg::CreateSession(MediaDesc* media_desc){
    auto session_id = GetRandUniqueId();
    auto session = FLVSession::Create(session_id);
    session->SetSessionDesc(*media_desc);
    addSession(session);
    return session_id;
}

void FLVSessionMrg::DestroySession(SESSION_ID id){
    removeSession(id);
}

uint32_t FLVSessionMrg::SetCallback(SESSION_ID id, FLVCallBackFunc cb)
{
    auto session = getSession(id);
    if(session != nullptr)
        session->SetCallback(cb);
    return 0;
}

uint32_t FLVSessionMrg::PushAVFrame(SESSION_ID id,const AVFrame& frame){
    auto session = getSession(id);
    if(session != nullptr)
        session->PushAVFrame(frame);
    return 0;
}

SESSION_ID FLVSessionMrg::addSession(FLVSessionPtr session){
    SESSION_ID id = session->GetSessionId();
    std::lock_guard<std::mutex> lock(session_mutex_);
    session_map_[id] = session;
    return id;
}

SESSION_ID FLVSessionMrg::removeSession(SESSION_ID id){
    std::lock_guard<std::mutex> lock(session_mutex_);
    auto it = session_map_.find(id);
    if (it == session_map_.end()) {
        return 0;
    }
    SESSION_ID ret = it->second->GetSessionId();
    session_map_.erase(it);
    return ret;
}

FLVSessionPtr FLVSessionMrg::getSession(SESSION_ID id){
    std::lock_guard<std::mutex> lock(session_mutex_);
    auto it = session_map_.find(id);
    if (it == session_map_.end()) {
        return nullptr;
    }
    return session_map_[id];
}