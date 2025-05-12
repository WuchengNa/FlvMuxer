#pragma once

#include "common/common.h"
#include "util/block_queue.h"

class FLVSession;
typedef std::shared_ptr<FLVSession>  FLVSessionPtr;

class FLVSession
{
    public:
        FLVSession(SESSION_ID id);
        ~FLVSession();
        static FLVSessionPtr Create(SESSION_ID id)
        {
            return std::make_shared<FLVSession>(id);
        }

        void SetSessionDesc(const MediaDesc& media_desc);

        void SetCallback(FLVCallBackFunc cb);
        
        bool Start();
        void Stop();

        void PushAVFrame(const AVFrame& av_frame);
    
        SESSION_ID GetSessionId() const;

    private:
        SESSION_ID session_id_;
        bool is_running_;

        FLVCallBackFunc cb_;
        BlockQueue<AVFrame> av_frame_queue_;
        std::vector<FLVTag> flv_tags_list_;

};