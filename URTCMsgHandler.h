#ifndef _UMEETING_MSGHANDLER_H_
#define _UMEETING_MSGHANDLER_H_
#include <string>
#include "RTCDefine.h"
#include "RTCEngineBase.h"
#include "MyVideoRender.h"

typedef void (*Fun)(int, char *);

class URTCMsgHandler : public MsgHandler{
public:
    URTCMsgHandler(RTCEngineBase* rtcengine , Fun callback) ;
    virtual ~URTCMsgHandler() ;

    void setUserId(std::string& roomid) ;
    void setRoomId(std::string& userid) ;
    std::string getUserId(); 
    void onMessage(int eventid, std::string jsonmsg);


private :
    void onJoinRoomHandler(std::string& jsonmsg) ;
    void onLeaveRoomHandler(std::string& jsonmsg) ;

    void onPublishStreamHandler(std::string& jsonmsg) ;
    void onUnPublishStreamHandler(std::string& jsonmsg) ;

    void onFileDataBeginHandler(std::string& jsonmsg) ;
    void onFileDataEndHandler(std::string& jsonmsg) ;
    void onFileListEndHandler(std::string& jsonmsg) ;
    void onSubscribeRespHandler(std::string& jsonmsg);    

private:
    RTCEngineBase* mRtcengine ;
    std::string mRoomId ;
    std::string mUserId ;
    Fun mCallback; 
    tUCloudRtcVideoCanvas canvas;
    MyVideoRender myrender ; 
};
#endif

