# DIY Mobile Robotics Platform:
The video instructions are [here]([https://youtu.be/9S9H8HX5MNA](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/youtube_screenshot.png?raw=true)). <br/>
The regression used to calibrate the stereo camera is in the file points_regression.ods. <br/>
The fritzing diagram for the pcb is in esp32_motor_control.fzz <br/>
The gerber files for the pcb are in gerber_esp32_motor_control <br/>
The code is in [robot_software](https://github.com/jonathanrandall/diy_mobile_robot/tree/main/robot_software). <br/>


![the robot](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/robot_complete.JPEG)


# Assemble the Frame and Motors.

__Screw Drivers and Hex Keys__<br/>
![screw drivers](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/IMG_9034.JPEG) <br/>
The M4 socket head screws require a 3mm drive size. It is recommended to get the __Wera Tools 3mm Ball-End Hex-Plus L-Key__ (SKU: 5027104001). This will make building much easier, since it can access screws in awkward places. The drivers I used are pictured below.

__Step 1: Build the base of the frame:__<br/>
Note: robot upside down in picutre, so base is at the top. <br/>
![robot frame](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/IMG_9070.jpeg)<br/>
<ins>parts list for base</ins>
* 2 X 432mm 1120 Series U-Channel (SKU: 1120-0017-0432)
* 2 X 528mm 1120 Series U-Chaneel (SKU: 1120-0021-0528)
* 4 X 1201 Series Quadblock pattern mount (SKU: 1201-0043-0002)
* 16 X 11mm M4 screws
* 16 X 8mm M4 screws
* 16 X 12mm M4 screws
* 4 X flanged ball bearing, 8mm REX ID x 14mm OD, 5mm thickness (SKU: 1611-0514-4008). Note ID is inner diameter and OD is outer diameter.
* 4 X 1320 Series hyper hub, 8mm REX Bore (SKU: 1310-0016-4008)
* 4 X Threaded Steel L-Bracket, 3 hole (SKU: 1147-0001-0003). Note there are four in each pack, so once pack.
* 1 X 1116 Series Grid Plate, 29 x 53 Hole, 232 x 424mm (SKU: 1116-0232-0424)
* 24 X 6mm screws (can also use 8mm if you run out, but 6mm is preferred).
* 5204 Series Yellow  Jacket Planetary Gear Motor, 80mm Lenght 8mm REX shart, 117 RPM (SKU: 5204-8002-0051). Note, this is the long shaft motor. If you use the shorter shaft, you will need a coupler and a shaft to attach to the wheel. This can be quite fiddly and adds to the cost. Also I'm using the 117 RPM motor, which is not fast but has good torque. My aim is to handle a payload of up to 50kg on a 30 degree incline. According to my calculations, this should handle that quite well, but might struggle witht he 223 RMP version.
* 4 X 1109 Series goRail, 624mm lenghth (SKU: 1109-0024-0624). 

<ins>Assembly of base</ins>
1. Attach the quadblocks to the end of the shorter U-channels (432mm) with the 11mm screws. Mounting the quadblocks on the shorter channels will result in the base being a square. Each channel is 48mm wide, so the base will be (432 +48 +48) = 528mm. Note, you can use different sized U-Channels, depending on what you need. I've chosen theses sizes to bring it into line with the Stanford Mobile Aloha robot. This build is on the wider end of what I would normally do.<br/> 
![Quad Blocks](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/IMG_9015.JPEG)
2. Attach the two 432mm at right angles with the 528mm channels, using the 8mm screws to connect, to make a square shape (see picture).<br/>
![channels and motor](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/IMG_9023.JPEG)
3. Attach the motors to the side of the frame. You can 10mm to 12mm screws for this. I've attached mine to the fourth hole down. There are lots of diagrams on the gobilda page for attaching the motors to channel. Make sure the motor's power wires and encoder plug are facing upwards, so they are easy to access from the top. <br/>
![motor attach](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/IMG_9020.JPEG)
4. Place the bearing,spacer and hyperhub on the end of the motor shaft and push down so that everything is nice and snug. Tighten the pinch screws on the hyperhub. Don't place the wheels on yet. They will get in the way.<br/>
![bearing attach](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/IMG_9021.JPEG)
5. Attach the goRail to the corners of the base with the 12mm M4 screws (or 10mm is ok as well), so they are standing verticle. They have threaded holes, which will line up with the holes on the U-Channel. When you attach a goRail, do not tighten the screws until all four have been placed, otherwise you risk cross-threading. I'm using 624mm goRail. You can use up to 1200mm. You can adjust the height of the goRail without changing anything else. If you adjust the dimensions of the U-Channel, the grid plates will also need to be adjusted.<br/>
![gorail attach](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/IMG_9032.JPEG) ![gorail](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/IMG_9039.JPEG)
6. Attach the L-Brackets, with the 6mm M4 screws, to each of the U-Channels that the motors are on. They should be attached off centre becasue this is where you are going to mount the grid plate.<br/>
![L brackets attach](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/IMG_9042.JPEG)
7. Mount the grid plate on the L-Brackets with the 6mm M4 screws.<br/>
![grid plate attach](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/IMG_9068.JPEG)

__Step 2: Build the top of the frame:__

<ins>parts list</ins>
* 2 X 528mm 1120 Series U-Chaneel (SKU: 1120-0021-0528)
* 2 X 1116 Series Grid Plate, 29 x 53 Hole, 232 x 424mm (SKU: 1116-0232-0424)
* 8 X Threaded Steel L-Bracket, 3 hole (SKU: 1147-0001-0003). Note there are four in each pack, so two packs.
* 48 X 6mm M4 screws (can also use 8mm if you run out, but 6mm is preferred).

<ins>Assembly of top of the frame</ins>
1. Attach the 4 L-Brackets to the edge of each of the U-Channels, so that the U-Channel is like an upside down U, and the bracket is flush with the top (see picture). Makes sure the L-Brackets are spaced, so that you can attach the grid plates. Don't put any in the middle of the channel.
2. Once you have all L-brackets attached line up the two U-channels with the brackets facing each other and put the grid plates on, so that the two U-Channels are held together with the grid plates. Make sure the grid plates are attached along the short edge (see pictures). So the long edge is connecting the two U-Channels. Everything is measured out so it fits perfectly on the top of the robot.<br/>
![top grid](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/IMG_9049.JPEG) ![top grid 2](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/IMG_9050.JPEG)

__Step 3: Attach the top of the frame:__

<ins>parts list</ins>
* 16 X 12mm M4 screws. Can use anywhere from 10mm to 12mm for this step, depedending on what you have. I mixed it up a bit because I was running out of 12mm screws.

<ins>Finish assembly</ins?
1. Line up the threaded holes in the GoRail with the holes in the corner of the top of the frame.
2. Fix on with the chosen screws.<br/>
![channels and motor](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/IMG_9054.JPEG)

__Step 4: Attach the wheels:__

Put the wheels on last, otherwise they get in the way when you're trying to screw on the other stuff.

<ins>parts list</ins>
* Four wheels. I'm using the Wasteland Wheel, 144mm Diameter, 52mm Width (SKU: 3616-0014-0144)
* 16 X 11mm M4 screws (can also use 10mm).
* 4 X washers

<ins>Assembly of wheels</ins>
1. Screw onto hyperhubs with 11mm screws and washers.<br/>
![channels and motor](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/IMG_9071.JPEG)<br/>

# Assemble the Bottom Layer to get the robot driving
(Note: Also, need top battery for this)
The bottom layer of the robot contains the motor controllers, the esp32 a buck converter set to 12V and a buck converter set to 5V

### Parts list:
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

__Bottom of the robot:__ Connect all parts as shown in the picture. I've screwed my motor controllers on diagonally because that was the only way I could get the standoffs to line up with the holes. Only the two diagonal standoffs are attached to the gridplate. And make connections as in above tables <br/>
![labeled bottom](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/IMG_0062_labeled.JPEG) <br/>


![motor controller and pcb](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/bottom_pcb_stuck2.JPEG) <br/>


# Assemble the Top of the robot

The top of the robot contans the raspberry pi 5, stereo camera and robot arms. Assemble as shown in the picutres. 
![This is the platform](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/top_cam_platform.JPEG) <br/>
![this is the top platform](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/top_layour.JPEG?raw=true) <br/>
![Connecctions](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/top_connections.png)


### Parts list, electronics and robotics:
1. [__Hiwonder XARM esp32 X 2__](https://www.hiwonder.com/products/xarm-esp32)
2. __Raspberry pi 5.__
3. Raspberry pi 5 mount. I 3D printed [this one](https://www.printables.com/model/253933-simple-raspberry-pi-mount).
4. 3S battery.
5. __5A, 5V buck converter__ for raspberry pi (I used a non adjustable one). Make sure you get a good quality one, or else the pi won't start. I used __[tunghey 2Pack DC 9V 12V 24V to DC 5V 5A Buck Converter Module, 9-36V Step Down to USB 5V Transformer Dual Output Voltage Regulator Board](https://www.amazon.com.au/gp/product/B0D5V5YDC3/)__ from Amazon. The other alternative is to use a Waveshare UPS supply at 5V, but this is more expensive. I also tried an 8A buck converter but the pi wouldn't boot (probably because the voltage was a bit noisy?) and I tried a powerbank and the pi worked but with throttling on the CPU, which means it would run a bit slower. This is attached to the grid with a piece of lego, which is mounted on stand offs. The lego grid matches the goBilda grid plates, so it's easy to drill holes.
6. Adjustable Buck converter running at 8V to power the robot arms. I used this one: [DC5-30V to 1.25-30V Automatic Step DC-to-DC Power Converter UP/Down Converter Boost/Buck Voltage Regulator Module](https://www.amazon.com.au/gp/product/B08FXN9V68/), which is rated for high current and is fine with the robot arms, but didn't work with the pi.
7. __Stereo Camera__. I used [this one](https://www.amazon.com.au/gp/product/B07R8LQKV4/). Which is a Synchronized Dual Lens Stereo USB Camera 1.3MP HD 960P Webcam 3D VR Web Camera Module with 1/3 CMOS OV9715. Any stereo camera should work, but you need to make sure the left an right frames are synchronized, especially if the robot is moving.
8. Rocker switch.
9. Terminal strips X 4 (two for the top and two for the bottom). I used terminal strips with plastic cover and sixe connections. Six is the minimum. Make sure you get the ones with the plastic cover because if you drop a screw driver or something on it, you can cause a short.
10. Fork lugs to connect to the terminal strips.
11. Red and black wires (less than or equal 14 AWG).
12. Copper standoffs for XARM.
13. Nylong standoffs for 8V buck converter.
14. Male to male jumpber cables for connecting 8V buck converter to robot arm.

## structure parts:

__these parts will be used to mount the stereo camera an raspberry pi__
1. [1109 Series goRAIL](https://www.gobilda.com/1109-series-gorail-336mm-length/) (336mm Length). This is the neck (SKU: 1109-0024-0336).
2. [1116 Series Grid Plate](https://www.gobilda.com/1116-series-grid-plate-29-x-53-hole-232-x-424mm/) (29 x 53 Hole, 232 x 424mm). This is the platform to mount the pi on.
3. [1113 Series L-Channel](https://www.gobilda.com/1113-series-l-channel-1-hole-48mm-length/) (1 Hole, 48mm Length). This will connect the perf board that the camera is on to the grip plate to it is at right angles (SKU: 1113-0001-0048).
4. perf board. The camera is mounted on a perf board. This was from an old project, but it turned out quite nicely because the holes in the perf board lined up with the mounting holes in the camera.





















