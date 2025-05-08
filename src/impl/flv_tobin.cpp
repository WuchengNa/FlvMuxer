#include "common/common.h"
#include <memory.h>

static const uint8_t FLV_HEADER_SIZE = 9; // FLV header size in bytes
static const uint8_t FLV_TAG_HEADER_SIZE = 11; // FLV tag header size in bytes

// 将header转换为大端字节序的二进制buffer的静态函数
static void FLVHeaderToBinary(const FLVHeader* header, uint8_t* buf) {
    // 前3字节是signature
    buf[0] = header->signature_[0];
    buf[1] = header->signature_[1];
    buf[2] = header->signature_[2];
    
    // 版本号
    buf[3] = header->version_;
    
    // 将flags打包成一个字节
    buf[4] = (header->reserved_5bit_ << 3) | (header->has_audio_ << 2) | 
             (header->reserved_1bit_ << 1) | header->has_video_;
    
    // data_offset_ (4字节,大端序)
    buf[5] = (header->data_offset_ >> 24) & 0xFF;
    buf[6] = (header->data_offset_ >> 16) & 0xFF;
    buf[7] = (header->data_offset_ >> 8) & 0xFF;
    buf[8] = header->data_offset_ & 0xFF;
}


// 将tag header转换为大端字节序的二进制buffer的静态函数 
static void FLVTagHeaderToBinary(const FLVTagHeader* header, uint8_t* buf) {
    // reserved_for_fms_ (2 bits) + filter_ (1 bit) + tag_type_ (5 bits)
    buf[0] = (header->reserved_for_fms_ << 6) | (header->filter_ << 5) | header->tag_type_;
    
    // data_size_ (3 bytes, big-endian)
    buf[1] = (header->data_size_ >> 16) & 0xFF;
    buf[2] = (header->data_size_ >> 8) & 0xFF;
    buf[3] = header->data_size_ & 0xFF;
    
    // timestamp_ (3 bytes, big-endian)
    buf[4] = (header->timestamp_ >> 16) & 0xFF;
    buf[5] = (header->timestamp_ >> 8) & 0xFF;
    buf[6] = header->timestamp_ & 0xFF;
    
    // timestamp_extrabyte_
    buf[7] = header->timestamp_extrabyte_;
    
    // stream_id_ (3 bytes, always 0x00)
    buf[8] = header->stream_id_[0];
    buf[9] = header->stream_id_[1];
    buf[10] = header->stream_id_[2];
}

// 将tag转换为二进制buffer的静态函数
static void FLVTagToBinary(const FLVTag* tag, uint8_t* buf) {
    // previous_tag_size_ (4 bytes, big-endian)
    buf[0] = (tag->previous_tag_size_ >> 24) & 0xFF;
    buf[1] = (tag->previous_tag_size_ >> 16) & 0xFF;
    buf[2] = (tag->previous_tag_size_ >> 8) & 0xFF;
    buf[3] = tag->previous_tag_size_ & 0xFF;
    
    // tag header
    FLVTagHeaderToBinary(&tag->header_, buf + 4);
    
    // tag body (data)
    memcpy(buf + FLV_TAG_HEADER_SIZE, tag->body_, tag->header_.data_size_);
}
