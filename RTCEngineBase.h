#ifndef _UMEETING_RTCENGINEBASE_H_
#define _UMEETING_RTCENGINEBASE_H_
#include <vector>
#include <string>
#include "RTCDefine.h"
#include "UCloudRtcComDefine.h"

class UCloudRtcAudioFrameCallback ;
class RTCEngineBase{
public:
	virtual ~RTCEngineBase(){}

	virtual int InitRTCEngine(const char* logdir,const char* logname, int loglevel, int classmode) = 0 ;
	virtual int UnInitRTCEngine() = 0;

	virtual std::string getSdkVersion() = 0;

	virtual int EnableRtspSource(int mediatype, bool enable, std::string rtspurl) =0;

	virtual int AddFileList(std::vector<std::string>& filelist, bool) = 0 ;

	virtual int JoinRoom(tRTCAuthInfo& auth) = 0;
	virtual int LeaveRoom(std::string& roomid) = 0;

	virtual int sendMessage(std::string& msgid, std::string& msgdata) = 0 ;

	virtual int MuteCamBeforeJoin(bool mute) = 0;
	virtual int MuteMicBeforeJoin(bool mute) = 0;

	virtual int enableExtendVideoSource(bool enable) = 0;
	virtual int enableExtendAudioSource(bool enable) = 0;
	virtual int enableExtendVideocaptureAsScreen(bool enable) = 0;
	virtual int enableExtendAudioSink(UCloudRtcAudioFrameCallback* sink) = 0;

	virtual int PushVideoFrame(int mediatype, tUCloudRtcVideoFrame* frame) = 0 ;
	virtual int PushAudioFrame(tUCloudRtcAudioFrame* frame) = 0 ;

	virtual int PublishStream(tRTCStreamInfo& streaminfo) = 0;
	virtual int UnPublishStream(tRTCStreamInfo& streaminfo) = 0;
	virtual int StartLocalRender(tRTCRenderView& renderview) = 0;
	virtual int StopLocalRender(tRTCRenderView& renderview) = 0;
	virtual int MuteLocalCamVideo(tRTCStreamMute& mute) = 0;
	virtual int MuteLocalCamAudio(tRTCStreamMute& mute) = 0;
	virtual int MuteLocalScreen(tRTCStreamMute& mute) = 0;

	virtual int SetCodecType(int codec) = 0;

	virtual int SubRemoteStream(tRTCStreamInfo& streaminfo) = 0;
	virtual int UnSubRemoteStream(tRTCStreamInfo& streaminfo) = 0;
	virtual int StartRemoteRender(tRTCRenderView& renderview) = 0;
	virtual int StopRemoteRender(tRTCRenderView& renderview) = 0;
	virtual int MuteRemoteCamVideo(tRTCStreamMute& mute) = 0;
	virtual int MuteRemoteCamAudio(tRTCStreamMute& mute) = 0;
	virtual int MuteRemoteScreen(tRTCStreamMute& mute) = 0;

	virtual int StartRecord(tRecordConfig& config) = 0;
	virtual int StopRecord() = 0;

	virtual int StartMixFile(const char* filepath, bool replace, bool loop, float musicvol) = 0;
	virtual int StopMixFile() = 0;
	virtual int StartRemoteView(tUCloudRtcVideoCanvas canvas) =0 ;
	virtual int StopRemoteView (tUCloudRtcVideoCanvas canvas) =0 ;
};

#endif
