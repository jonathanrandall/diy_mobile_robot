### This directory contains the software for the robot.

__There are three directories for sofware__

1. [esp32_stuff/esp32_controls](https://github.com/jonathanrandall/diy_mobile_robot/tree/main/robot_software/esp32_stuff/esp32_controls): This directory contains the code for the esp32 that goes on the esp32 that is on the bottom level of the robot. thi is written in Platform IO. The code broadcasts a webpage over a local wifi network. So you need to input the wifi ssid and password for this to work. Also, the routines to move the robot a certain distance are on free rtos. I have them threaded so they won't block the commands set to the robot. This means, the "STOP" won't be blocked and I don't have to implement an emergency stop with an interrupt. It also means I can interrupt the robot with other commands if neeed be.
2. [rpi_stuff](https://github.com/jonathanrandall/diy_mobile_robot/tree/main/robot_software/rpi_stuff): This directory contains the python code that is running on the raspberry pi.
  - The hand_distance_measure code is used for calibrating the stereo cameras.
  - The pose_estimation_measure broadcasts the stereo image over the network (for me this is address http://rpi5.local, but for you, you will need to replace the name rpi5 with the name you gave your raspberry pi when you flashed the operating system).
3. [wifi_xarm_control_v2](https://github.com/jonathanrandall/diy_mobile_robot/tree/main/robot_software/wifi_xarm_control_v2):This is the micropython code that is flashed to the esp32 on the [hiwonder robot arms](https://www.hiwonder.com/products/xarm-esp32). 
    
