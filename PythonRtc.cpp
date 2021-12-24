#include "stdio.h"
#include "URTCConfig.h"
#include "RTCEngineFactory.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include "UCloudRtcMediaDevice.h"
#include <cstring>
#include "URTCMsgHandler.h"
#include "msgqueue.h"
#include "URTCCustomAudioSink.h"
#include <iostream>
#include "MyVideoRender.h"
#include "time.h"

using namespace std;

URTCMsgHandler* g_pymsghandler = nullptr ;
RTCEngineBase* g_urtcengine = nullptr; 
tUCloudRtcVideoCanvas canvas;
MyVideoRender myrender ;
tRTCStreamInfo info;
std::string guserid = "ai_test";
//Python事件回调
typedef void (*CFun)(int);

extern "C"{//在extern “C”中的函数才能被外部调用

    int  callback_fun(CFun callback){
	printf("in urtc sdk\n\r");
        (*callback)((int)rand());
    	return 0;
    }
    
    RTCEngineBase*  createEngine(char * appid, char * secret , Fun callback){
	std::string id = appid;
	std::string key = secret;
	
	printf ("Create Engine %s ***\n\r", appid);
	URTCConfig::getInstance()->setAppId(id);
	URTCConfig::getInstance()->setSecKey(key);
	//CHANNELTYPE is defined in the DEMO.只是创了一个引擎实例
        g_urtcengine = RTCEngineFactory::createRtcEngine(RTC_CHANNELTYPE_UCLOUD);
	g_pymsghandler = new URTCMsgHandler(g_urtcengine, callback) ;
	//g_urtcengine -> enableExtendVideoSource(true);
	//g_urtcengine -> enableExtendVideocaptureAsScreen(false);
	int vstate = UCloudRtcMediaDevice::sharedInstance()->InitVideoMoudle();
	int astate = UCloudRtcMediaDevice::sharedInstance()->InitAudioMoudle();
	
	printf("Media device state  A %d / V %d , total %d device \n\r", astate, vstate, UCloudRtcMediaDevice::sharedInstance()-> getPlayoutDevNums());
	return g_urtcengine;
    }

    int joinRoom(void * engine, char * _roomid, char * _userid){
	printf("Joining Room\n\r");
	std::string roomid = _roomid;
	std::string userid = _userid;
	int classmode = UCLOUD_RTC_CLASS_TYPE_NORMAL ; 
        
	g_urtcengine->InitRTCEngine("log", roomid.data(),0, classmode) ;	
	//g_urtcengine->EnableRtspSource(1, false, "");
        if (g_urtcengine){
		//g_pymsghandler = new URTCMsgHandler(g_urtcengine) ;
		MsgQueue::getInstance()->regEventHandler("", g_pymsghandler);
		MsgQueue::getInstance()->startMsgQue() ;
        
		g_pymsghandler->setUserId(userid) ;
       		g_pymsghandler->setRoomId(roomid) ;

		tRTCAuthInfo auth;
		auth.mAppid = URTCConfig::getInstance()->getAppId();
		auth.mRoomid = roomid;
		auth.mUserid = userid ;
		int re= g_urtcengine->JoinRoom(auth);	
		if (re >0){
			printf("Error while join Room, code %d \n\r", re);
		} 

	}else {
	    printf("Error while joining Room \r\n");
	}
	return 0;
    } 
    
    int leaveRoom(char * _roomid){
	
        std::string roomid = _roomid;
        if (g_urtcengine){
	    //if (NULL != canvas){
		g_urtcengine -> StopRemoteView(canvas);
	    //}
            g_urtcengine ->  UnPublishStream(info);
            return  g_urtcengine -> LeaveRoom(roomid);
 
        }
	return 0;
    }

    int subscribeRemote(char * _userid){

                tRTCStreamInfo streaminfo ;
                streaminfo.mUserid=_userid;
                streaminfo.mEnableVideo = 1;
                streaminfo.mEnableAudio = 0;
                streaminfo.mStreamMtype = 1;

                g_urtcengine->SubRemoteStream(streaminfo);
    	return 0;
    }

    int publish(char * _userid){
    	//tRTCStreamInfo info;
    	info.mEnableVideo = true;
    	info.mEnableAudio = true;
    	info.mEnableData = false;
    	info.mStreamMtype = UCLOUD_RTC_MEDIATYPE_VIDEO;
    	info.mUserid = g_pymsghandler->getUserId();//_userid;
	printf ("Publish Stream for user %s \n\r", _userid);
    	g_urtcengine->PublishStream(info) ;
        g_urtcengine -> enableExtendVideoSource(true);
    	g_urtcengine -> enableExtendVideocaptureAsScreen(false);
	return 0; 
    }    


    int startRemoteView (char * _userid, RemoteCallback callback){
                printf("PYTHON CALL start remote view   \n\r ");
    //tUCloudRtcVideoCanvas canvas;
    //MyVideoRender myrender ;
    	myrender.callback=callback;
        myrender.engine= g_urtcengine;
    	MyVideoRender * render  =  &myrender;
    	canvas.mVideoView = (void*)render; // mVideoView 由int 变更为 void*

    	canvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
    	canvas.mUserId = _userid;
    	canvas.mStreamMtype = UCLOUD_RTC_MEDIATYPE_VIDEO;
    	canvas.mRenderType = UCLOUD_RTC_RENDER_TYPE_EXTEND; // 自定义渲染类型
    	canvas.mVideoFrameType = UCLOUD_RTC_VIDEO_FRAME_TYPE_I420;
    	int pres = g_urtcengine->StartRemoteView(canvas);
        printf("Starting Preview %d \n\r", pres);
	
        return 0 ; 
    }
    
    void pushVideoFrame(unsigned char * data, int width, int height){
        struct timeval tvValue;
        gettimeofday(&tvValue, NULL);

	tUCloudRtcVideoFrame frame; 
        frame.mDataBuf  = data;
	frame.mWidth= width;
        frame.mHeight= height;
	//frame.mDataSize = width* height*3/2;
        //frame.mFrameType = 1;
	frame.mVideoType=UCLOUD_RTC_VIDEO_FRAME_TYPE_RGB24 ; 
	frame.mTimeStampms = tvValue.tv_sec * 1000  + tvValue.tv_usec/1000;
	//frame.mVideoType = UCLOUD_RTC_VIDEO_FRAME_TYPE_I420 ;
	printf(">>> Push Frame to Room, %d x %d, Data %d , %d , %d \n\r", width, height, data[100], data[3000], data[230800]);
        g_urtcengine -> PushVideoFrame(UCLOUD_RTC_MEDIATYPE_VIDEO, &frame );
	return ; 
    }
    void closeEngine(){
         g_urtcengine -> UnInitRTCEngine();
    }
}
