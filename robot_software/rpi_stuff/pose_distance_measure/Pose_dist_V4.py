from cvzone.PoseModule import PoseDetector
import cv2
import cvzone
import numpy as np
import os
import sys
import csv
import time
import math
import subprocess

from bus_servo_http import BusServoHttp
import threading
import queue
import requests

import http.server
import socketserver

# Configuration
PORT = 8000  # Port number for the HTTP server
jpgq = queue.Queue()


URL_ESP32 = "http://192.168.1.211"

robot_moved = False #only move robot once

# """The 33 pose landmarks."""
#   NOSE = 0
#   LEFT_EYE_INNER = 1
#   LEFT_EYE = 2
#   LEFT_EYE_OUTER = 3
#   RIGHT_EYE_INNER = 4
#   RIGHT_EYE = 5
#   RIGHT_EYE_OUTER = 6
#   LEFT_EAR = 7
#   RIGHT_EAR = 8
#   MOUTH_LEFT = 9
#   MOUTH_RIGHT = 10
#   LEFT_SHOULDER = 11
#   RIGHT_SHOULDER = 12
#   LEFT_ELBOW = 13
#   RIGHT_ELBOW = 14
#   LEFT_WRIST = 15
#   RIGHT_WRIST = 16
#   LEFT_PINKY = 17
#   RIGHT_PINKY = 18
#   LEFT_INDEX = 19
#   RIGHT_INDEX = 20
#   LEFT_THUMB = 21
#   RIGHT_THUMB = 22
#   LEFT_HIP = 23
#   RIGHT_HIP = 24
#   LEFT_KNEE = 25
#   RIGHT_KNEE = 26
#   LEFT_ANKLE = 27
#   RIGHT_ANKLE = 28
#   LEFT_HEEL = 29
#   RIGHT_HEEL = 30
#   LEFT_FOOT_INDEX = 31
#   RIGHT_FOOT_INDEX = 32
using_arm = True
if using_arm:
    URL_XARM = 'http://192.168.1.122'
    URL_XARM_R = 'http://192.168.1.125'
    servo_R = BusServoHttp(URL_XARM_R)
    servo = BusServoHttp(URL_XARM)
# servo.run(2, 6000)
# Set the resolution
width = 640  # Desired width
height = 240  # Desired height
mult = 1


class VideoCapture:

    def __init__(self, name):
        self.cap = cv2.VideoCapture(name, apiPreference=cv2.CAP_V4L2)
        self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, width*mult)
        self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, height*mult)
        self.q = queue.Queue()
        t = threading.Thread(target=self._reader)
        t.daemon = True
        t.start()

    # read frames as soon as they are available, keeping only most recent one
    def _reader(self):
        while True:
            ret, frame = self.cap.read()
            if not ret:
                break
            if not self.q.empty():
                try:
                    self.q.get_nowait()   # discard previous (unprocessed) frame
                except queue.Empty:
                    pass
            self.q.put(frame)

    def set(self, width, height, mult=1):
        self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, mult*width)
        self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, mult*height)
        

    def read(self):
        return True, self.q.get()

def get_auto_index(dataset_dir='./video_out/', dataset_name_prefix = '', data_suffix = 'jpg'):
    max_idx = 1000
    if not os.path.isdir(dataset_dir):
        os.makedirs(dataset_dir)
    for i in range(max_idx+1):
        if not os.path.isfile(os.path.join(dataset_dir, f'{dataset_name_prefix}fname_l_{i}.{data_suffix}')):
            return i
    raise Exception(f"Error getting auto index, or more than {max_idx} episodes")

def find_webcam_index(device_name):
    command = "v4l2-ctl --list-devices"
    output = subprocess.check_output(command, shell=True, text=True)
    devices = output.split('\n\n')
    
    for device in devices:
        if device_name in device:
            lines = device.split('\n')
            for line in lines:
                if "video" in line:
                    parts = line.split()
                    for part in parts:
                        if part.startswith('/dev/video'):
                            print(part)
                            return (part[10:])

webcam_index = int(find_webcam_index('3D')) #C922 #3D USB
# cap = cv2.VideoCapture(webcam_index, apiPreference=cv2.CAP_V4L2)
#use the VideoCapture class to stop it from lagging
cap = VideoCapture(webcam_index)

detector = PoseDetector(staticMode=False,
                        modelComplexity=1,
                        smoothLandmarks=True,
                        enableSegmentation=False,
                        smoothSegmentation=True,
                        detectionCon=0.5,
                        trackCon=0.5)

detector2 = PoseDetector(staticMode=False,
                        modelComplexity=1,
                        smoothLandmarks=True,
                        enableSegmentation=False,
                        smoothSegmentation=True,
                        detectionCon=0.5,
                        trackCon=0.5)
# Function to encode the image frames into JPEG format and store in queue
def stream_frames():
    global robot_moved
    global jpgq
    arm_down = True
    # Continuously get frames from the webcam
    while True:
        success, img = cap.read()
        h, w, _ = (img.shape)
        imgr = img[0:h, 0:(w // 2)]
        imgl = img[0:h, (w // 2):w]
        # imgl = cv2.medianBlur(imgl,3)
        NW = (w // 2)

        imgr = detector.findPose(imgr)
        imgl = detector2.findPose(imgl)

        lmList1, bboxInfo1 = detector.findPosition(imgr, draw=True, bboxWithHands=False)
        lmList2, bboxInfo2 = detector2.findPosition(imgl, draw=True, bboxWithHands=False)
        isCloseAngle50 = False
        isCloseAngle50_b = False
        

        if lmList1 and lmList2:
            lmList1_np = np.array(lmList1)[[0, 11, 12], 0]  # x coordinate of nose, left shoulder, right shoulder
            lmList2_np = np.array(lmList2)[[0, 11, 12], 0]

            dist = (NW / ((lmList1_np - lmList2_np).mean())) * 4.52 - 2.64

            if math.isinf(dist):
                dist = 0

            dist2move = dist - 90

            if dist2move < 0:
                dist2move = 0

            custom_text = f"{int(dist)} cm"  # Replace with your desired text
            cv2.putText(imgr, custom_text, (30, 100), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 255), 2)
            cv2.putText(imgl, custom_text, (30, 100), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 255), 2)

            angle1, imgr = detector.findAngle(lmList1[23][0:2],  # left hip
                                              lmList1[11][0:2],  # left shoulder
                                              lmList1[13][0:2],  # left elbow
                                              img=imgr,
                                              color=(0, 0, 255),
                                              scale=5)

            angle3, imgr = detector.findAngle(lmList1[24][0:2],  # right hip
                                              lmList1[12][0:2],  # right shoulder
                                              lmList1[14][0:2],  # right elbow
                                              img=imgr,
                                              color=(0, 0, 255),
                                              scale=5)

            isCloseAngle50 = detector.angleCheck(myAngle=angle1,
                                                 targetAngle=210,
                                                 offset=20)

            # right
            isCloseAngle50_b = detector.angleCheck(myAngle=angle3,
                                                   targetAngle=200,
                                                   offset=30)

        # Encode the image frame as JPEG
        ret, jpeg = cv2.imencode('.jpg', img)
        if ret:
            # Put the encoded frame into the queue
            jpgq.put(jpeg.tobytes())
        
        if dist > 0 and isCloseAngle50 and not robot_moved:
            str_move = URL_ESP32 + f"/action?distance={int(dist2move)}"
            ret=requests.get(str_move)
            print(str_move)
            print(ret)
            # robot_moved = True
        
        srt = 1000 # servo runt time

        if using_arm:
            if isCloseAngle50_b and arm_down:
                servo.run(5, 500, servo_run_time=srt)
                servo.run(4, 500, servo_run_time=srt)
                servo.run(3, 500, servo_run_time=srt)
                servo_R.run(5, 500, servo_run_time=srt)
                servo_R.run(4, 500, servo_run_time=srt)
                servo_R.run(3, 500, servo_run_time=srt)
                arm_down = False
                
                #robot_moved = True
            elif not isCloseAngle50_b and not arm_down:
                servo.run(5, 850, servo_run_time=srt)
                servo.run(4, 870, servo_run_time=srt)
                servo.run(3, 130, servo_run_time=srt)
                servo_R.run(5, 850, servo_run_time=srt)
                servo_R.run(4, 870, servo_run_time=srt)
                servo_R.run(3, 130, servo_run_time=srt)
                arm_down = True
                

# HTTP Request Handler Class
class StreamHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'multipart/x-mixed-replace; boundary=frame')
        self.end_headers()
        
        while True:
            try:
                # Get the JPEG frame from the queue
                frame = jpgq.get()
                self.wfile.write(b'--frame\r\n')
                self.send_header('Content-Type', 'image/jpeg')
                self.send_header('Content-Length', len(frame))
                self.end_headers()
                self.wfile.write(frame)
                self.wfile.write(b'\r\n')
            except Exception as e:
                print(f"Error streaming frame: {e}")
                break

# Start the streaming thread
stream_thread = threading.Thread(target=stream_frames)
stream_thread.daemon = True
stream_thread.start()

# Start the HTTP server
with socketserver.TCPServer(("", PORT), StreamHandler) as httpd:
    print(f"Serving HTTP stream on port {PORT}")
    httpd.serve_forever()

# Keep the script running
try:
    while True:
        pass
except KeyboardInterrupt:
    print("Stopping server...")
    httpd.shutdown()
