#ifndef _UMEETING_URTCENGINEIMPL_H_
#define _UMEETING_URTCENGINEIMPL_H_

#include "UCloudRtcEngine.h"
#include "RTCEngineBase.h"
#include "URTCEventHandler.h"

class URTCEngineImpl :   
	public RTCEngineBase{
public:
	URTCEngineImpl();
	virtual ~URTCEngineImpl();

	virtual int InitRTCEngine(const char* logdir, const char* logname,int loglevel, int classmode) ;
	virtual int UnInitRTCEngine() ;

	virtual std::string getSdkVersion();
	virtual int EnableRtspSource(int mediatype, bool enable, std::string rtspurl);

	virtual int AddFileList(std::vector<std::string>& filelist, bool);

	virtual int JoinRoom(tRTCAuthInfo& auth);
	virtual int LeaveRoom(std::string& roomid);
	virtual int sendMessage(std::string& msgid, std::string& msgdata)  ;
	virtual int SetCodecType(int codec);

	virtual int MuteCamBeforeJoin(bool mute);
	virtual int MuteMicBeforeJoin(bool mute);
	virtual int enableExtendVideoSource(bool enable);
	virtual int enableExtendVideocaptureAsScreen(bool enable)  ;
	virtual int enableExtendAudioSource(bool enable) ;
	virtual int enableExtendAudioSink(UCloudRtcAudioFrameCallback* sink) ;

	virtual int PushVideoFrame(int mediatype,tUCloudRtcVideoFrame* frame) ;
	virtual int PushAudioFrame(tUCloudRtcAudioFrame* frame)  ;


	virtual int PublishStream(tRTCStreamInfo& streaminfo) ;
	virtual int UnPublishStream(tRTCStreamInfo& streaminfo) ;
	virtual int StartLocalRender(tRTCRenderView& renderview);
	virtual int StopLocalRender(tRTCRenderView& renderview);
	virtual int MuteLocalCamVideo(tRTCStreamMute& mute) ;
	virtual int MuteLocalCamAudio(tRTCStreamMute& mute);
	virtual int MuteLocalScreen(tRTCStreamMute& mute);

	virtual int SubRemoteStream(tRTCStreamInfo& streaminfo);
	virtual int UnSubRemoteStream(tRTCStreamInfo& streaminfo);
	virtual int StartRemoteRender(tRTCRenderView& renderview);
	virtual int StopRemoteRender(tRTCRenderView& renderview);
	virtual int MuteRemoteCamVideo(tRTCStreamMute& mute);
	virtual int MuteRemoteCamAudio(tRTCStreamMute& mute);
	virtual int MuteRemoteScreen(tRTCStreamMute& mute) ;

	virtual int StartRecord(tRecordConfig& config);
	virtual int StopRecord() ;

	virtual int StartMixFile(const char* filepath, bool replace, bool loop, float musicvol);
	virtual int StopMixFile();
	virtual int StartRemoteView(tUCloudRtcVideoCanvas canvas);
	virtual int StopRemoteView (tUCloudRtcVideoCanvas canvas)  ;
private:

	UCloudRtcEngine*   m_rtcengine;
	URTCEventHandler* m_eventhandler;
};

#endif

