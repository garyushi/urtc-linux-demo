# URTC X64 SDK DEMO使用说明

适用环境：ubuntu 16.04 18.04

编译工具: cmake make gcc g++

URTC 以动态链接库的方式提供SDK，包括头文件和动态链接库文件：
- urtclib/interface/UCloudRtcComDefine.h
- urtclib/interface/UCloudRtcEngine.h
- urtclib/interface/UCloudRtcErrorCode.h
- urtclib/interface/UCloudRtcMediaDevice.h
- urtclib/lib/libliburtcmediaengine.so
- urtclib/lib/liburtcnetengine.so

URTC DEMO为开源，用户可以直接使用到自己的产品中。

## DEMO及SDK提供的功能

- DEMO的入口在Python中
- 加入房间
- 从远程拉流
- 将远程流解码成I420的图片格式
- 调用detect程序检测图片中内容，并处理（注：detect的代码并未提供）
- 如果图片处理能力小于视频 的FPS，会按时延向上取整后跳过后续若干帧
- 将图片回推到房间里，格式为BGR，（对，URTC SDK里的设置为RGB，必须是这样）
- Python的环境上需要安装对应的opencv，opencv需要支持h264 codec
- 按需安装对应的tensorflow, yolo等 AI库

## 如果在目标机器上编译使用下面的命令

```
cd build
# 生成Makefile等
cmake ../.
# 编译成功后，在../bin中生成可执行文件
make
# 执行

# 以下只需要做一次
# 修改/etc/ld.so.conf.d/xxx.conf文件，将相应urtc的so以及本项目生成的so所在目录放入
ldconfig -v 

cd ../python
修改python文件，
1. 将appid/secret /room id /user id修改成自己需要的
2. 检查OnRemoteFrame中的实现，根据需要处理视频图象回调

执行python3
python3 fb_det.py 

客户端 或Web 加入 roomid 指定的房间 输入视频源或者观看视频
```



## 创建URTC应用快速入门

参考：[快速上手](https://docs.ucloud.cn/video/urtc/quick)


## **注意事项**

1. 使用本库需要了解URTC的基本配置参数，包括应用名称，AppID, AppKey, roomid，userid, tokenid, 具体使用方法请参考[URTC文档](https://docs.ucloud.cn/urtc/README)
2. 使用本库需要了解[URTC常用术语](https://docs.ucloud.cn/urtc/sdk/term)，包括进入房间、离开房间、发布视频流、取消发布、订阅视频流、取消订阅.
3. URTC 加入参考(参考`main.cpp`,`URTCConfig.cpp`):
   - AppID、AppKey为在UCloud控制台创建应用时系统自动生成;
   - 【重要】AppKey为接入平台认证Key，本demo中直接使用该Key接入，生产环境下务必将AppKey存在服务器端,[使用Token接入](https://docs.ucloud.cn/video/urtc/sdk/token)；
   - 应用名称采用 产品序列号+产品名称，比如：ozuz63kum2i4djb3_巡检无人机；
   - roomid采用设备序列号，比如：afnyhnizq9l4l9ev；
   - userid采用设备序列号+摄像头编号，比如：afnyhnizq9l4l9ev_camera3；
   - tokenid为服务器端生成，测试环境直接使用AppKey测试，生产环境务必参考本项第2条；
4. 生产、测试环境切换：
   - 生产模式使用Tokenid，配置`URTCConfig.cpp`，`mSdkMode = UCLOUD_RTC_SDK_MODE_NORMAL;`, 此时在`main.cpp中获取tokenid;
