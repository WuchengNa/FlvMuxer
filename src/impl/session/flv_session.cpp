#include "flv_session.h"
#include <thread>

FLVSession::FLVSession(SESSION_ID id) : session_id_(id)
{
    Start();
}

FLVSession::~FLVSession()
{
    Stop();
}

void FLVSession::SetSessionDesc(const MediaDesc &media_desc)
{
}

void FLVSession::SetCallback(FLVCallBackFunc cb)
{
    cb_ = cb;
}

bool FLVSession::Start()
{
    is_running_ = true;
    std::thread([this]() {
        while (is_running_) {
            if (!av_frame_queue_.empty()) {
                auto av_frame = av_frame_queue_.pop();
                // Process the AV frame to FLV tag

                // callback flv data
                void* data = nullptr;
                size_t size = 0;
                cb_(session_id_, (char*)data, size);
            }
        }
    }).detach();
    return true;
}

void FLVSession::Stop()
{
}

void FLVSession::PushAVFrame(const AVFrame &av_frame)
{
    av_frame_queue_.push(av_frame); 
}

SESSION_ID FLVSession::GetSessionId() const
{
    return session_id_;
}
