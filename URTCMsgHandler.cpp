#include "URTCMsgHandler.h"
#include "RTCEventDefine.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"  
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "URTCConfig.h"
#include "stdio.h"


URTCMsgHandler::URTCMsgHandler(RTCEngineBase* rtcengine, Fun callback)  {
    mRtcengine = rtcengine ;
    mRoomId = "" ;
    mUserId = "" ; 
    mCallback = callback;
}

URTCMsgHandler::~URTCMsgHandler() 
{

}

void URTCMsgHandler::setUserId(std::string& userid) 
{
    mUserId = userid ;
}

void URTCMsgHandler::setRoomId(std::string& roomid) 
{
    mRoomId = roomid ;
}

void URTCMsgHandler::onMessage(int eventid, std::string jsonmsg) 
{
    printf("On Message %d \n\r ", eventid);

    switch (eventid)
    {
    case URTC_EVENT_MSG_JOINROOM_RSP:
        onJoinRoomHandler(jsonmsg) ;
        break;
    case URTC_EVENT_MSG_LEAVEROOM_RSP :
        onLeaveRoomHandler(jsonmsg) ;
        break;
    case URTC_EVENT_MSG_LOCALPUBLISH_RSP:
        onPublishStreamHandler(jsonmsg) ;
        break;
    case URTC_EVENT_MSG_LOCALUNPUBLISH_RSP :
        onUnPublishStreamHandler(jsonmsg) ;
        break;
    case URTC_EVENT_MSG_AI_TEACHER_FILE_BEGIN:
        onFileDataBeginHandler(jsonmsg) ;
        break;
    case URTC_EVENT_MSG_AI_TEACHER_FILE_END :
        onFileDataEndHandler(jsonmsg) ;
        break;
    case URTC_EVENT_MSG_AI_TEACHER_FILE_LIST_END :
        onFileListEndHandler(jsonmsg) ;
        break;
    case URTC_EVENT_MSG_REMOTESUB_RSP:
	onSubscribeRespHandler(jsonmsg);
	break; 
    case URTC_EVENT_MSG_REMOTEPUBLISH:
	printf("URTC_EVENT_MSG_REMOTEPUBLISH  %s", jsonmsg.c_str());
	break;   
    default:
	printf("Default Message Handler ID  %d, info %s\n\r", eventid, jsonmsg.c_str());
        break;
    }
    if (NULL != mCallback ){
        (mCallback)(eventid, jsonmsg.c_str()); 
    } 
    //printf("Message Handler ID  %d, info %s", eventid, jsonmsg.c_str());
}

void URTCMsgHandler::onJoinRoomHandler(std::string& jsonmsg) 
{
/*    tRTCStreamInfo info;
    info.mEnableVideo = true;
    info.mEnableAudio = true;
    info.mEnableData = false;
    info.mStreamMtype = UCLOUD_RTC_MEDIATYPE_VIDEO;
    info.mUserid = mUserId;
    mRtcengine->PublishStream(info) ;
    mRtcengine -> enableExtendVideoSource(true);
    mRtcengine -> enableExtendVideocaptureAsScreen(false);
    printf("Joined Room\n\r ");

                tRTCStreamInfo streaminfo ;
                streaminfo.mUserid="shihongjun";
                streaminfo.mEnableVideo = 1;
                streaminfo.mEnableAudio = 0;
                streaminfo.mStreamMtype = 1;

                mRtcengine->SubRemoteStream(streaminfo);
*/
}

void URTCMsgHandler::onLeaveRoomHandler(std::string& jsonmsg) 
{

}

void URTCMsgHandler::onPublishStreamHandler(std::string& jsonmsg) 
{

}

void URTCMsgHandler::onUnPublishStreamHandler(std::string& jsonmsg) 
{

}

void URTCMsgHandler::onFileDataBeginHandler(std::string& jsonmsg) 
{

}

void URTCMsgHandler::onFileDataEndHandler(std::string& jsonmsg) 
{

}

void URTCMsgHandler::onFileListEndHandler(std::string& jsonmsg) 
{
    
}

void URTCMsgHandler::onSubscribeRespHandler(std::string& jsonmsg)
{
/*	printf("Sub Response  \n\r ");	
    //tUCloudRtcVideoCanvas canvas;
    //MyVideoRender myrender ;
    MyVideoRender * render  =  &myrender; 
    myrender.callback = NULL ; 
    canvas.mVideoView = (void*)render; // mVideoView 由int 变更为 void*

    canvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
    canvas.mUserId = "shihongjun";
    canvas.mStreamMtype = UCLOUD_RTC_MEDIATYPE_VIDEO;
    canvas.mRenderType = UCLOUD_RTC_RENDER_TYPE_EXTEND; // 自定义渲染类型

    int pres = mRtcengine->startPreview(canvas);
    printf("Starting Preview %d \n\r", pres); */

}

std::string URTCMsgHandler::getUserId(){
    return mUserId;
}
