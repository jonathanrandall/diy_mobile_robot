# Top assembly instructions
The top of the robot contans the raspberry pi 5, stereo camera and robot arms.

## Parts list:
1. [Hiwonder XARM esp32 X 2](https://www.hiwonder.com/products/xarm-esp32)
2. Raspberry pi 5.
3. Raspberry pi 5 mount. I 3D printed [this one](https://www.printables.com/model/253933-simple-raspberry-pi-mount).
4. 3S battery.
5. 5A, 5V buck converter for raspberry pi (I used a non adjustable one). Make sure you get a good quality one, or else the pi won't start. I used __[tunghey 2Pack DC 9V 12V 24V to DC 5V 5A Buck Converter Module, 9-36V Step Down to USB 5V Transformer Dual Output Voltage Regulator Board](https://www.amazon.com.au/gp/product/B0D5V5YDC3/)__ from Amazon. The other alternative is to use a Waveshare UPS supply at 5V, but this is more expensive. I also tried an 8A buck converter but the pi wouldn't boot (probably because the voltage was a bit noisy?) and I tried a powerbank and the pi worked but with throttling on the CPU, which means it would run a bit slower.
6. Adjustable Buck converter running at 8V to power the robot arms. I used this one: [DC5-30V to 1.25-30V Automatic Step DC-to-DC Power Converter UP/Down Converter Boost/Buck Voltage Regulator Module](https://www.amazon.com.au/gp/product/B08FXN9V68/), which is rated for high current and is fine with the robot arms, but didn't work with the pi.
7. Stereo Camera. I used [this one](https://www.amazon.com.au/gp/product/B07R8LQKV4/). Which is a Synchronized Dual Lens Stereo USB Camera 1.3MP HD 960P Webcam 3D VR Web Camera Module with 1/3 CMOS OV9715. Any stereo camera should work, but you need to make sure the left an right frames are synchronized, especially if the robot is moving.
8. Rocker switch.
9. Terminal strips X 4 (two for the top and two for the bottom). I used terminal strips with plastic cover and sixe connections. Six is the minimum. Make sure you get the ones with the plastic cover because if you drop a screw driver or something on it, you can cause a short.
10. Fork lugs to connect to the terminal strips.
11. Red and black wires (less than or equal 14 AWG). 




