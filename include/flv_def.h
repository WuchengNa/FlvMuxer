#ifndef __FLV_DEF_H__
#define __FLV_DEF_H__

#ifdef _WIN32
# ifdef FLVSDK_EXPORT
#   define FLVSDK_API extern "C" __declspec(dllexport)
# else
#   define FLVSDK_API extern "C" __declspec(dllimport)
# endif
#define FLV_CALL __stdcall
#define FLV_CALLBACK __stdcall
#elif defined(__linux__)
#ifdef FLVSDK_EXPORT
#   define FLVSDK_API extern "C" __attribute__((visibility("default")))
#else
#   define FLVSDK_API extern "C" __attribute__((visibility("hidden")))
#endif
#define FLV_CALL
#define FLV_CALLBACK
#endif

#include <stdint.h>

// ERROR CODE
#define FLV_CODE_OK 0
#define FLV_CODE_ERR 1
#define FLV_CODE_ERR_NO_MEMORY 2
#define FLV_CODE_ERR_INVALID_PARAM 3
#define FLV_CODE_ERR_INVALID_STATE 4
#define FLV_CODE_ERR_NO_DATA 5

//Media Type
#define FLV_MEDIA_TYPE_AUDIO 0
#define FLV_MEDIA_TYPE_VIDEO 1
#define FLV_MEDIA_TYPE_SCRIPT 2

//Codec ID
#define FLV_CODEC_ID_UNKOWN 0
#define FLV_CODEC_ID_AAC 1
#define FLV_CODEC_ID_H264 2

//Frame Type
#define FLV_FRAME_TYPE_UNKOWN 0
#define FLV_FRAME_TYPE_KEY 1
#define FLV_FRAME_TYPE_INTER 2
#define FLV_FRAME_TYPE_SCRIPT 3
#define FLV_FRAME_TYPE_AUDIO 4


typedef uint32_t FLVSDK_ERR_CODE;
typedef  uint32_t SESSION_ID;

struct VideoDesc
{
    uint32_t codec_id;
    uint32_t width;
    uint32_t height;
    uint32_t fps;
};

struct AudioDesc
{
    uint32_t codec_id;
    uint32_t sample_rate;
    uint32_t channels;
    uint32_t bits_per_sample;
};

struct MediaDesc
{
    const char* media_name;
    uint32_t duration; //-1 for infinite
    AudioDesc* audio_desc;
    VideoDesc* video_desc;
};

struct AVFrame
{
    uint32_t frame_type;
    uint32_t codec_id;
    uint32_t pts; //pts (in milliseconds)
    uint32_t dts; //dts (in milliseconds)

    uint8_t is_key_frame;
    uint8_t* data;
    uint32_t data_size;
};

typedef void(FLV_CALLBACK *FLVDataCallback) (SESSION_ID packer_id, char* data, int size, void* user_data);
#endif //__FLV_DEF_H__