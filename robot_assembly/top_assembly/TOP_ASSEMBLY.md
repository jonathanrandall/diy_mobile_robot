# Top assembly instructions
The top of the robot contans the raspberry pi 5, stereo camera and robot arms.


## Parts list:
1. [Hiwonder XARM esp32 X 2](https://www.hiwonder.com/products/xarm-esp32)
2. Raspberry pi 5.
3. Raspberry pi 5 mount. I 3D printed [this one](https://www.printables.com/model/253933-simple-raspberry-pi-mount).
4. 3S battery.
5. 5A, 5V buck converter for raspberry pi. Make sure you get a good quality one, or else the pi won't start. I used __[tunghey 2Pack DC 9V 12V 24V to DC 5V 5A Buck Converter Module, 9-36V Step Down to USB 5V Transformer Dual Output Voltage Regulator Board](https://www.amazon.com.au/gp/product/B0D5V5YDC3/)__ from Amazon. The other alternative is to use a Waveshare UPS supply at 5V, but this is more expensive. I also tried an 8A buck converter but the pi wouldn't boot (probably because the voltage was a bit noisy?) and I tried a powerbank and the pi worked but with throttling on the CPU, which means it would run a bit slower.
6. Terminal strips X 4 (two for the top and two for the bottom). I used terminal strips with plastic cover and sixe connections. Six is the minimum. Make sure you get the ones with the plastic cover because if you drop a screw driver or something on it, you can cause a short.
7. Fork lugs to connect to the terminal strips.
8. Red and black wires (less than or equal 14 AWG). 




