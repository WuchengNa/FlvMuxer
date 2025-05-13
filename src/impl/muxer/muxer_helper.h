#pragma once

#include "common/common.h"
#include <vector>
#include <memory>

//push avframe to flv tag
// convert flv tag to binary
class FLVMuxerHelper
{
private:
    /* data */
    std::shared_ptr<FLVHeader> flv_header_;
    uint32_t previous_tag_size_ = 0 ; // size of the previous tag header + data
public:
    FLVMuxerHelper();
    ~FLVMuxerHelper();
    
    void SetHeader(const MediaDesc& media_desc);
    std::shared_ptr<FLVHeader> GetHeader() const { return flv_header_; }

    bool GenerateFlvTag(const AVFrame& av_frame, FLVTag& flv_tag);

private:
    bool generateFlvTagHeader(const AVFrame& av_frame, FLVTagHeader& tag_header);
    bool generateFlvTagBody(const AVFrame& av_frame, FLVTag& flv_tag);
};