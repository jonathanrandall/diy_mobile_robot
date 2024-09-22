from cvzone.HandTrackingModule import HandDetector
import cv2
import cvzone
import numpy as np
import os
import sys
import csv
import time
import subprocess

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
cap = cv2.VideoCapture(webcam_index, apiPreference=cv2.CAP_V4L2)

# Set the resolution
width = 640  # Desired width
height = 240  # Desired height
mult = 1
cap.set(cv2.CAP_PROP_FRAME_WIDTH, mult*width)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, mult*height)


# Initialize the webcam to capture video
# The '2' indicates the third camera connected to your computer; '0' would usually refer to the built-in camera
# cap = cv2.VideoCapture(2)

# Initialize the HandDetector class with the given parameters
detector = HandDetector(staticMode=True, maxHands=4, modelComplexity=1, detectionCon=0.5, minTrackCon=0.4)
sharpening_kernel = np.array([[0, -1, 0],
                              [-1, 5, -1],
                              [0, -1, 0]])

# Continuously get frames from the webcam
while True:
    # Capture each frame from the webcam
    # 'success' will be True if the frame is successfully captured, 'img' will contain the frame
    success, img = cap.read()
    h, w, _ = (img.shape)
    imgr = img[0:h,0:(w // 2)]
    imgl = img[0:h,(w // 2):w]
    # imgl = cv2.medianBlur(imgl,3)

    # Find hands in the current frame
    # The 'draw' parameter draws landmarks and hand outlines on the image if set to True
    # The 'flipType' parameter flips the image, making it easier for some detections
    handsr, imgr = detector.findHands(imgr, draw=False, flipType=True)
    handsl, imgl = detector.findHands(imgl, draw=False, flipType=True)

    # Check if any hands are detected
    if handsr:
        # print(len(hands))
        for h in handsr:
            pass
            # print(h["type"], end = " ")
            # for key in h.keys():
            #     print(key)
        # Information for the first hand detected
        hand1 = handsr[0]  # Get the first hand detected
        lmList1 = hand1["lmList"]  # List of 21 landmarks for the first hand
        x, y, w, h = hand1["bbox"]  # Bounding box around the first hand (x,y,w,h coordinates)
        center1 = hand1['center']  # Center coordinates of the first hand
        handType1 = hand1["type"]  # Type of the first hand ("Left" or "Right")
        # see https://mediapipe.readthedocs.io/en/latest/solutions/hands.html
        lmList1_np = np.array(lmList1)[[0,5,9,13,17],0]

        # fingers1 = detector.fingersUp(hand1)

    if handsl:
        # print(len(hands))
        for h in handsr:
            pass
            # print(h["type"], end = " ")
            # for key in h.keys():
            #     print(key)
            # print(h["score"])
        # Information for the first hand detected
        hand2 = handsl[0]  # Get the first hand detected
        lmList2 = hand2["lmList"]  # List of 21 landmarks for the first hand
        x2, y2, w2, h2 = hand2["bbox"]  # Bounding box around the first hand (x,y,w,h coordinates)
        center2 = hand2['center']  # Center coordinates of the first hand
        handType2 = hand2["type"]  # Type of the first hand ("Left" or "Right")
        lmList2_np = np.array(lmList2)[[0,5,9,13,17],0]

        dist = (320/((lmList1_np-lmList2_np).mean()))*4.52 - 2.64

        
        # fingers1 = detector.fingersUp(hand1)
        # print(f'H1 = {fingers1.count(1)}', end=" ")  # Print the count of fingers that are up

        # Calculate distance between specific landmarks on the first hand and draw it on the image
        # length, info, img = detector.findDistance(lmList1[8][0:2], lmList1[12][0:2], img, color=(255, 0, 255),
        #                                           scale=10)

        # Check if a second hand is detected
        
            
        custom_text = f"{int(dist)} cm"  # Replace with your desired text
        cv2.putText(imgr, custom_text, (x+4, y - 26), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 255), 2)
        cv2.putText(imgl, custom_text, (x2+4, y - 26), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 255), 2)

            

        # print(" ")  # New line for better readability of the printed output

    # Display the image in a window
    # imgn = cvzone.stackImages([imgl, imgr], 2, 1)
    cv2.imshow("Image original", img)
    # cv2.imshow("Image new", imgn)

    # Keep the window open and update it for each frame; wait for 1 millisecond between frames
    key=cv2.waitKey(1)
    if key == ord("q"):
        cv2.destroyAllWindows()
        sys.exit(0)
    if key == ord("s"):
        # time.sleep(3)
        i = get_auto_index(dataset_dir='./image_out/',data_suffix='jpg')
        fname_l = './image_out/fname_l_'+str(i) + '.jpg'
        fname_r = './image_out/fname_r_'+str(i) + '.jpg'
        fname_all = './image_out/fname_all_'+str(i) + '.jpg'
        cv2.imwrite(fname_l, imgl)
        cv2.imwrite(fname_r, imgr)
        cv2.imwrite(fname_r, img)
        with open('./image_out/points_'+str(i)+'.csv', 'w', newline='') as file:
            writer = csv.writer(file)
            writer.writerows(lmList1)
            writer.writerows(lmList2)