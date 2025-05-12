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

#define FLV_CODE_OK 1
#define FLV_CODE_ERR 0

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
    AudioDesc audio_desc;
    VideoDesc video_desc;
};

struct AVFrame
{
    uint32_t frame_type;
    uint32_t codec_id;
    uint32_t timestamp;
    uint32_t data_size;
    bool is_key_frame;
    char* data;
};

typedef void(FLV_CALLBACK *FLVDataCallback) (SESSION_ID packer_id, char* data, int size, void* user_data);
#endif //__FLV_DEF_H__