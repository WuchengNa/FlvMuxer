#pragma once

#include <stdint.h>
#include <stdio.h>
#include <memory>
#include <functional>
#include "flv_def.h"

static const uint8_t FLV_HEADER_SIZE = 9; // FLV header size in bytes
static const uint8_t FLV_TAG_HEADER_SIZE = 11; // FLV tag header size in bytes

static const uint8_t VALUE_TRUE = 0x01;
static const uint8_t VALUE_FALSE = 0x00;
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

typedef struct FLVTagVideoData
{
    uint8_t frame_type_; // 4 bits, 0x01 (key frame), 0x02 (inter frame)
    uint32_t cts_; // 3 bytes, composition time stamp (ms)/ cts = (pts - dts)/90
    uint8_t* data_; // pointer to the video data
    uint32_t data_size_; // size of the video data
} FLVTagVideoMetaData;

typedef struct FLVTagAudioData
{
    uint8_t codec_id_;      // codec id / 0x00 (raw), 0x01 (adpcm), 0x02 (mp3), 0x0a (aac)
    uint8_t sample_rate_;     // sample rate of the audio/ 0x00 (5.5kHz), 0x01 (11kHz), 0x02 (22kHz), 0x03 (44kHz) /aac always 0x03
    uint8_t bits_per_sample_; // bits per sample/ 0x00 (8 bits), 0x01 (16 bits)
    uint8_t channels_;        // number of channels (0 for mono, 1 for stereo)
    uint8_t *data_;          // pointer to the audio data
    uint32_t data_size_;     // size of the audio data
} FLVTagAudioMetaData;

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

typedef std::function<void(SESSION_ID packer_id, char* data, int size)> FLVCallBackFunc;
