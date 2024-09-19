#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "encoders_stuff.h"
#include "esp_now_stuff.h"
#include "motor_ctrl_stuff.h"
#include "OLED_stuff.h"
#include "ssid_stuff.h"
#include "html_stuff.h"



// put function declarations here:


void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.begin(115200);
  init_wifi();
  start_server();
  init_encoders();
  robot_setup();

  left_motor_speed=106;
  right_motor_speed=106;

  unsigned long timer_strt;
  unsigned long timer_cur;
  timer_strt = millis();
  timer_cur = timer_strt;

  bool calib=false;
  if (calib){
    robot_fwd();

    while(millis()-timer_strt<2000){
      if(millis()-timer_cur > 300){
        timer_cur = millis();
        //print out pos*pule

        for (int i =0; i<4; i++){
          Serial.print("Motor: ");
          Serial.print(i); 
          Serial.print(", pulses: ");
          long enc = get_encoder_pos(i);
          float dist = ((float) enc )*pulse_dist;
          Serial.print(enc);
          Serial.print(", dist: ");
          Serial.println(dist);
        }
      }
    }
    robot_stop();
    // delay(500);
    emergency_stop=false;
    calibrate_motors(80);
    calibrate_motors(70);
    calibrate_motors(60);
    calibrate_motors(50);
    calibrate_motors(40);
    calibrate_motors(30);
    calibrate_motors(20);
    calibrate_motors(10);
  } //if calib
  emergency_stop=true;
  // move_robot_dist(2000.0);

  // robot_stop();

}

void loop() {
  // put your main code here, to run repeatedly:
}

