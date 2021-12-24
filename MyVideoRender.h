#ifndef _UMEETING_MYVIDEORENDER_H_
#define _UMEETING_MYVIDEORENDER_H_
#include <vector>
#include <string>
#include "RTCDefine.h"
#include "UCloudRtcComDefine.h"
#include "RTCEngineBase.h"

//typedef void (*CFun)(int);

/*
        unsigned char* mDataBuf;
        unsigned int mDataSize ; //仅对编码好数据有效
        int mWidth;
        int mHeight;
        int mFrameType ; // 0 关键帧 1 非关键帧
        int64_t mTimeStampms ;
        eUCloudRtcVideoFrameType mVideoType;
*/
typedef void (*RemoteCallback)(unsigned char * , unsigned int , int , int, int );
class MyVideoRender : public UCloudRtcExtendVideoRender {
    public:
        virtual  void onRemoteFrame(const tUCloudRtcVideoFrame* videoframe);
        RemoteCallback callback;
        RTCEngineBase* engine  = nullptr;
    };
#endif
