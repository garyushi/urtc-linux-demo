#include "MyVideoRender.h"

/*        unsigned char* mDataBuf;
        unsigned int mDataSize ; //仅对编码好数据有效
        int mWidth;
        int mHeight;
        int mFrameType ; // 0 关键帧 1 非关键帧
*/
void MyVideoRender::onRemoteFrame(const tUCloudRtcVideoFrame* videoFrame)
{
	printf ("Get Video Frame %d x %d, size %d , frame type %d  , frame time %d\n\r", 
            videoFrame->mWidth, videoFrame->mHeight , videoFrame->mDataSize , videoFrame-> mFrameType, videoFrame -> mTimeStampms);
        if (NULL != callback ){
                (callback)(videoFrame->mDataBuf, videoFrame->mDataSize, videoFrame->mWidth,videoFrame-> mHeight, videoFrame->mFrameType);
        }
        //engine -> PushVideoFrame(UCLOUD_RTC_MEDIATYPE_VIDEO, videoFrame );
}
