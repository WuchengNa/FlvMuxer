# FlvMuxer

## 项目简介

FlvMuxer 是一个用于将音视频数据（H264+AAC）打包为 FLV格式的 C++ 库，提供C风格接口。

该项目支持音视频流的 FLV 封装，适用于流媒体推流、录制等场景。

## 

## 主要功能

- 初始化/反初始化 SDK
- 创建/销毁 FLV 打包器
- 设置数据回调
- 推送音视频帧进行打包

## 主要接口

详见 [`include/flvmuxer.h`](include/flvmuxer.h)：

- `FLVSDK_Init()`：初始化 SDK
- `FLVSDK_UnInit()`：反初始化 SDK
- `FLVSDK_CreatePacker(MediaDesc* media_desc)`：创建打包器
- `FLVSDK_SetFlvDataCallback(SESSION_ID packer_id, FLVDataCallback callback, void* user_data)`：设置数据回调
- `FLVSDK_PushAVFrame(SESSION_ID packer_id, AVFrame* av_frame)`：推送音视频帧
- `FLVSDK_DestroyPacker(SESSION_ID packer_id)`：销毁打包器

### FLV Format:

| FLV Header | footer | FLV Tag Header | FLV Tag Body | ... |
| ---------- | ------ | -------------- | ------------ | --- |

****FLV Header Struct**** (9 BYTE)

|1 byte "F" | signature|
| 1 byte "L" | signature|
| 1 byte "V" | signature|
| 1 byte 0x01 | version 1|
| 5 bit 00000 | TypeFlags Reserved must be 0|
| 1 bit 0 or 1 | TypeFlags boHasAudio Tag|
| 1 bit 0 | TypeFlags Reserved must be 0|
| 1 bit 0 or 1 | TypeFlags boHasVideo Tag| 
| 4 byte | Header size, (Always be 9)|

****FLV Body Struct**** 

| 4 byte | pervious tag size
| 11 byte | tag header
| ... byte | tag body (data)
| 4 byte | pervious tag size
| 11 byte | tag header
| ... byte | tag body (data)

****FLV TAG Header Struct****(11 BYTE)
| 2 bit | Reserved for FMS, Always be 0 

| 1 bit | Filter，Always be 0
| 5 bit | Tag Types, Audio:8/ video:9/ script:18
| 3 byte | Tag body size
| 3 byte | Timestamp
| 1 byte | Timestamp Extended
| 3 byte | steamID, Always be 0

## 构建方法

本项目使用 CMake 构建，支持 Windows、Linux、macOS。

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

## 目录结构

include/：头文件
src/：核心实现
unittest/：单元测试
3rd/：第三方依赖（如 gtest）

**许可证**
本项目遵循开源协议，详情见各文件头部版权声明。