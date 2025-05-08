#pragma once

#include <stdint.h>
#include <stdio.h>
#include <memory>

typedef struct FLVHeader 
{
    uint8_t signature_[3]{'F', 'L', 'V'}; // "FLV"
    uint8_t version_;      // 1byte, 0x01
    uint8_t reserved_5bit_; // 5 bit, reserved bits
    uint8_t has_audio_;      // 1 bit, 0x01 if audio is present
    uint8_t reserved_1bit_;  // 1 bit, reserved bits always 0x00
    uint8_t has_video_;      // 1 bit, 0x01 if video is present
    uint32_t data_offset_;   //4 byte, always 0x09 (9 bytes) for the header size
} FLVHeader;

typedef struct FLVTagHeader
{
    uint8_t reserved_for_fms_; //2 reserved bits always 0x00
    uint8_t filter_;      //1 bit, 0x00 (no filter) or 0x01 (filter)
    uint8_t tag_type_;    //5 bit, 8 (audio) or 9 (video) or 18 (script data)
    uint32_t data_size_;    //3 byte, size of the data in bytes
    uint32_t timestamp_;   //3 byte, timestamp in milliseconds
    uint8_t timestamp_extrabyte_; // extra byte for timestamp
    uint8_t stream_id_[3]; // always 0x00 0x00 0x00
} FLVTagHeader;

typedef struct FLVTag
{
    uint32_t previous_tag_size_; // size of the previous tag header + data
    FLVTagHeader header_;
    uint8_t *body_; // pointer to the data (audio or video)
} FLVTag;


// typedef struct FLVFile
// {
//     FILE *file;         // file pointer
//     FLVHeader header;   // FLV header
//     FLVTag *tags;       // array of tags
//     size_t tagCount;    // number of tags
//     size_t tagCapacity; // capacity of the tags array
// } FLVFile;

typedef std::shared_ptr<FLVHeader> FLVHeaderPtr;
typedef std::shared_ptr<FLVTagHeader> FLVTagHeaderPtr;
typedef std::shared_ptr<FLVTag> FLVTagPtr;