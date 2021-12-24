
import ctypes
from ctypes import *
import time
import numpy as np
import cv2
#import detectmask as dt
import detectron 
import json


mylib = ctypes.cdll.LoadLibrary("liburtclib.so")

fourcc = cv2.VideoWriter_fourcc(*'X264')
out = cv2.VideoWriter('mask_output1115.mp4',fourcc, 20, (640, 360))


def onRemoteFrame(images, size, width, height, type ):
  global frame_toskip
  if (frame_toskip > 0 ):
    #skip frames due to delay of object detection
    frame_toskip = frame_toskip -1
    return 1 
  start_time = int(time.time() * 1000)   
  #YUV 420 format 
  #frame= numpy.ctypeslib.as_array(images, (width, height, 2))
  #print(type(numpy.mat(frame)))
  arr= bufferToImage(images,width, height)
  yuv = np.frombuffer(arr, dtype=np.uint8).reshape(height*3//2, width) 
  image= cv2.cvtColor (yuv, cv2.COLOR_YUV420p2RGB )
  #image  = dt.detectAndDraw(image)
  image = detectron.detAndDraw (image)
  out.write(image)

  
  #yuv420 = cv2.cvtColor (image, cv2.COLOR_RGB2YUV_I420  )
  #masked = np.reshape(yuv420, width*height*3//2 ) 
  #print ("Data Sample %d %d %d \n\r"%(masked[100] , masked[3000], masked [230800]))
  image_bgr = cv2.cvtColor(image, cv2.COLOR_RGB2BGR) 
  mylib.pushVideoFrame(image_bgr.ctypes, width, height)
  delay = int(time.time() * 1000)    - start_time
  frame_toskip =  remote_framerate * delay / 1000
  print ("PYTHON Image from remote %d x %d, size %d , type %d , delay  %d  frametoskip %d  \n\r"%(width, height, size, type, delay , frame_toskip))
  return 0

CharPtrWrapper=POINTER(c_uint8)
FRAME_CALLBACK= CFUNCTYPE(c_int, CharPtrWrapper , c_int, c_int, c_int, c_int)
#FRAME_CALLBACK= CFUNCTYPE(c_int, c_char_p, c_int, c_int, c_int, c_int)
rtc_frame_callback =FRAME_CALLBACK(onRemoteFrame)

def bufferToImage(buffer, width, height):
  memv= memoryview (buffer)
  buffer_len  = width*height*3//2  #len(memv)
  #buffer_len = len(memv) 
  BitmapType = c_uint8*(buffer_len)
  arr = BitmapType()
  print("Get %d frame data for %d * %d \n\r"% (buffer_len, width, height)) 
  memmove(arr, buffer, buffer_len)
  return  arr

#frame to skip
frame_toskip = 2
remote_framerate = 20 
 
def RtcEventHandler(eventid, jsonmsg):
  global remote_framerate, p_remoteid, p_userid
  msg = json.loads(str(jsonmsg, encoding="utf-8"))
  print ("RtcEvent: %d %s "%(eventid,jsonmsg))
  if (eventid == 1037):
    subRemoteResponse()
  if (eventid == 1046):
    #print (msg)
    remote_framerate = msg["data"]["framerate"] 
  if (eventid == 1026 or eventid==1035) :
    mylib.subscribeRemote(p_remoteid)
    mylib.publish(p_userid)
  return 0

def subRemoteResponse(): 
  print ("PYTHON: SubResponse\n\r")
  userid = "shihongjun"
  p_userid = c_char_p(bytes("shihongjun",encoding = "utf8"))
  mylib.startRemoteView (p_userid, rtc_frame_callback)
  return 0 



def testcallback(testid):
  print (testid)
  return 0 

CALLFUNC = CFUNCTYPE(c_int,c_int,  c_char_p)

FRAME_CALLBACK= CFUNCTYPE(c_int, c_char_p, c_int, c_int, c_int, c_int)

CALL2 = CFUNCTYPE(c_int,c_int)
callback= CALL2(testcallback)
rtc_event_callback = CALLFUNC(RtcEventHandler)
mylib.callback_fun(callback)
appid =""
appsecret=""
p_remoteid =c_char_p(bytes("shihongjun", encoding = "utf8"))
p_appid = c_char_p(bytes(appid, encoding = "utf8"))
p_secret = c_char_p(bytes(appsecret, encoding = "utf8"))
p_roomid  = c_char_p(bytes("gary", encoding = "utf8"))
p_userid = c_char_p(bytes("ai_k80_detectron2", encoding = "utf8"))
e = mylib.createEngine(p_appid, p_secret, rtc_event_callback)
mylib.joinRoom(e, p_roomid, p_userid)

print ("Sleep & waiting \r\n")
time.sleep(72000)
print ("Leaving Room !!")
#mylib.leaveRoom(p_roomid)
print ("Waiting 10s to leave&flush buffer\n\r")
time.sleep(10)
#mylib.closeEngine()
out.release()
time.sleep(10)
print ("Ending\r\n")
