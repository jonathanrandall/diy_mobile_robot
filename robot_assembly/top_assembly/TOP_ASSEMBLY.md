# Top assembly instructions
The top of the robot contans the raspberry pi 5, stereo camera and robot arms. Assemble as shown in the picutres. 
![This is the platform](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/top_cam_platform.JPEG) <br/>
![this is the top platform](https://github.com/jonathanrandall/diy_mobile_robot/blob/main/project_photos/top_layour.JPEG?raw=true)


## Parts list, electronics and robotics:
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




