#ifndef ENCODERS_STUFF_
#define ENCODERS_STUFF_

// wheel encoder interrupts
#include <Arduino.h>

#define encoder0PinA 23      // encoder top left
#define encoder0PinB 18

#define encoder1PinA 35     // encoder bottom left
#define encoder1PinB 32


#define encoder2PinA 4      // encoder top right
#define encoder2PinB 27

#define encoder3PinA 33     // encoder bottom right
#define encoder3PinB 25

volatile long encoder0Pos = 0;    // encoder 1 top left
volatile long encoder1Pos = 0;    // encoder 2 bottom left
volatile long encoder2Pos = 0;    // encoder 3 top right
volatile long encoder3Pos = 0;    // encoder 4 bottom right

const float ppr = 1425.1; //pulses per revolution
const float wheel_diameter = 13.7;//14.4;//cm
const float pi = 3.14159265359;
const float circum = wheel_diameter*pi; //cm
const float pulse_dist = circum/ppr;
const float robot_width = 60.0; //cm

const float turning_circle = robot_width*pi;

const float one_m = 100.0/pulse_dist; //number of pulses to travel 1m

void IRAM_ATTR doEncoderA();
void IRAM_ATTR doEncoderB();
void IRAM_ATTR doEncoderC();
void IRAM_ATTR doEncoderD();
void IRAM_ATTR doEncoderE();
void IRAM_ATTR doEncoderF();
void IRAM_ATTR doEncoderG();
void IRAM_ATTR doEncoderH();

void reset_encoders(){
  encoder0Pos = 0;    // encoder 1
  encoder1Pos = 0;    // encoder 2
  encoder2Pos = 0;    // encoder 3
  encoder3Pos = 0;    // encoder 4
}

void init_encoders(){
  pinMode(encoder0PinA, INPUT_PULLUP);    // encoder pins
  pinMode(encoder0PinB, INPUT_PULLUP);

  pinMode(encoder1PinA, INPUT_PULLUP); 
  pinMode(encoder1PinB, INPUT_PULLUP);

  pinMode(encoder2PinA, INPUT_PULLUP);    // encoder pins
  pinMode(encoder2PinB, INPUT_PULLUP);

  pinMode(encoder3PinA, INPUT_PULLUP); 
  pinMode(encoder3PinB, INPUT_PULLUP);


  attachInterrupt(encoder0PinA, doEncoderA, CHANGE);
  attachInterrupt(encoder0PinB, doEncoderB, CHANGE); 

  attachInterrupt(encoder1PinA, doEncoderC, CHANGE);
  attachInterrupt(encoder1PinB, doEncoderD, CHANGE); 

  attachInterrupt(encoder2PinA, doEncoderE, CHANGE);
  attachInterrupt(encoder2PinB, doEncoderF, CHANGE); 

  attachInterrupt(encoder3PinA, doEncoderG, CHANGE);
  attachInterrupt(encoder3PinB, doEncoderH, CHANGE);

  reset_encoders();
}

void IRAM_ATTR doEncoderA(){  

  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == LOW) {  
      encoder0Pos = encoder0Pos + 1;         // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder0PinB) == HIGH) {   
      encoder0Pos = encoder0Pos + 1;          // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
 
}

void IRAM_ATTR doEncoderB(){  

  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA) == HIGH) {  
      encoder0Pos = encoder0Pos + 1;         // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder0PinA) == LOW) {   
      encoder0Pos = encoder0Pos + 1;          // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
  

}

// ************** encoder 2 *********************

void IRAM_ATTR doEncoderC(){  

  // look for a low-to-high on channel A
  if (digitalRead(encoder1PinA) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder1PinB) == LOW) {  
      encoder1Pos = encoder1Pos + 1;         // CW
    } 
    else {
      encoder1Pos = encoder1Pos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder1PinB) == HIGH) {   
      encoder1Pos = encoder1Pos + 1;          // CW
    } 
    else {
      encoder1Pos = encoder1Pos - 1;          // CCW
    }
  }
 
}

void IRAM_ATTR doEncoderD(){  

  // look for a low-to-high on channel B
  if (digitalRead(encoder1PinB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(encoder1PinA) == HIGH) {  
      encoder1Pos = encoder1Pos + 1;         // CW
    } 
    else {
      encoder1Pos = encoder1Pos - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder1PinA) == LOW) {   
      encoder1Pos = encoder1Pos + 1;          // CW
    } 
    else {
      encoder1Pos = encoder1Pos - 1;          // CCW
    }
  }
  

}

void IRAM_ATTR doEncoderE(){  

  // look for a low-to-high on channel A
  if (digitalRead(encoder2PinA) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder2PinB) == LOW) {  
      encoder2Pos = encoder2Pos + 1;         // CW
    } 
    else {
      encoder2Pos = encoder2Pos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder2PinB) == HIGH) {   
      encoder2Pos = encoder2Pos + 1;          // CW
    } 
    else {
      encoder2Pos = encoder2Pos - 1;          // CCW
    }
  }
 
}

void IRAM_ATTR doEncoderF(){  

  // look for a low-to-high on channel B
  if (digitalRead(encoder2PinB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(encoder2PinA) == HIGH) {  
      encoder2Pos = encoder2Pos + 1;         // CW
    } 
    else {
      encoder2Pos = encoder2Pos - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder2PinA) == LOW) {   
      encoder2Pos = encoder2Pos + 1;          // CW
    } 
    else {
      encoder2Pos = encoder2Pos - 1;          // CCW
    }
  }
  

}

// ************** encoder 2 *********************

void IRAM_ATTR doEncoderG(){  

  // look for a low-to-high on channel A
  if (digitalRead(encoder3PinA) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder3PinB) == LOW) {  
      encoder3Pos = encoder3Pos + 1;         // CW
    } 
    else {
      encoder3Pos = encoder3Pos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder3PinB) == HIGH) {   
      encoder3Pos = encoder3Pos + 1;          // CW
    } 
    else {
      encoder3Pos = encoder3Pos - 1;          // CCW
    }
  }
 
}

void IRAM_ATTR doEncoderH(){  

  // look for a low-to-high on channel B
  if (digitalRead(encoder3PinB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(encoder3PinA) == HIGH) {  
      encoder3Pos = encoder3Pos + 1;         // CW
    } 
    else {
      encoder3Pos = encoder3Pos - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder3PinA) == LOW) {   
      encoder3Pos = encoder3Pos + 1;          // CW
    } 
    else {
      encoder3Pos = encoder3Pos - 1;          // CCW
    }
  }
  

}

long get_encoder_pos(int mtr){

  if(mtr==0) return encoder0Pos;
  if(mtr==1) return encoder1Pos;
  if(mtr==2) return -encoder2Pos;
  if(mtr==3) return -encoder3Pos;

  return 0;
  
}
// filter funcition
// float filter(float prevValue, float currentValue, int filter) {  
//   float lengthFiltered =  (prevValue + (currentValue * filter)) / (filter + 1);  
//   return lengthFiltered;  
// }

#endif