# Bottom of robot
The bottom layer of the robot contains the motor controllers, the esp32 a buck converter set to 12V and a buck converter set to 5V

## Parts list:
1. Cytron MD10C R3 motor controllers X 4. Or you can 2 X dual cytron dual motor drivers. I would recommend cytron if you want to use my code an wiring.
2. PCB or bread board. I printed up a PCB. The gerber files and fritzing files should be attached to this repo. I got this done at ![PCBWay](https://www.pcbway.com/).
3. ESP32: I'm using the 38 pin waveshare esp32. This has a thinner form factor than the ones you get off Amazon. My PCB design should also fit the fatter 38 pin esp32. I got it here ![https://www.waveshare.com/nodemcu-32s.htm](https://www.waveshare.com/nodemcu-32s.htm)
4. Nylon stand offs. I would get two packs of these.
5. 6S lipo battery or 2 X 3S lipo batteries. I used two 3S lip batteries in series. Also will need one 3S for the top.
6. Battery mount. I 3D printed mine. But you can make one out of lego, since the grid plates on the gobilda system line up with the lego grids, it is easy to drill holes to attach.
7. Four pin JST XH connectors. These are for the motor encoders. I used these from GoBilda. But you can use any you like. ![SKU: 3802-0910-0300](https://www.gobilda.com/encoder-cable-extension-4-pos-jst-xh-300mm-length/)
8. Bullet extenders (female) to connect the motor to the motor encoders. I used these from GoBilda. ![SKU:3800-0013-0300](https://www.gobilda.com/3-5mm-bullet-lead-mh-fc-300mm-length/)
9. Missile Switch. I used the missile switch to control the power to the motors because it's easy to turn off in a hurry, and i liked the look of it. I attached it with lego.
10. Buck converter for 5V. I'm using this one [here](https://www.amazon.com.au/gp/product/B08RBXCJCF/)
11. High current buck converter for 12V. I'm using [this one](https://www.amazon.com.au/gp/product/B08KXTV6RH/), which outputs 20A max. 
12. Terminal strips X 4 (two for the top and two for the bottom). I used terminal strips with plastic cover and sixe connections. Six is the minimum. Make sure you get the ones with the plastic cover because if you drop a screw driver or something on it, you can cause a short.
13. Fork lugs for connecting the wires to the terminal strips.
14. Red and Black wires. Make sure you use red for positive and black for ground.
15. Dupont femal to male jumper wires X 14. Two to connect the pcb to grnd and positive. And 12 to connect the motor controllers to the PCB.

## Connection Tables

![ESP32 connections](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/bottom_connections.png) ![bottom power connections](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/table_power_connections.png)

## Steps to assemble bottom of robot

__Bottom of the robot__<br/>
![labeled bottom](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/IMG_0062_labeled.JPEG) <br/>
The bottom of the robot contains motor controllers, motors, batteries, esp32, 5V & 12V regulators and terminal strips for power wires.

1. Screw on the PCB and the motor controllers. I've screwed my motor controllers on diagonally because that was the only way I could get the standoffs to line up with the holes. Only the two diagonal standoffs are attached to the gridplate <br/>
2. stuff
3. stuff
4. sst

![motor controller and pcb](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/bottom_pcb_stuck2.JPEG) <br/>
