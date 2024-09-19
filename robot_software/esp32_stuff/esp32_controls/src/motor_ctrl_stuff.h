#ifndef MOTORS_STUFF_
#define MOTORS_STUFF_
#include <Arduino.h>
#include "encoders_stuff.h"

#define LEFT            0
#define RIGHT           1

// pins

#define RIGHT_MOTOR_PWM 16 //
#define RIGHT_MOTOR_DIR 5 //
#define LEFT_MOTOR_PWM 17  //
#define LEFT_MOTOR_DIR 19  //

//back motors (Back of board)

#define RIGHT_MOTOR_PWM2 13 //
#define RIGHT_MOTOR_DIR2 12 //
#define LEFT_MOTOR_PWM2 26 //
#define LEFT_MOTOR_DIR2 14 //

QueueHandle_t dist_queue = NULL;
QueueHandle_t dist_queue_int;
QueueHandle_t theta_queue;
QueueHandle_t theta_queue_int; //inetrrupt

TaskHandle_t move_dist_task;
TaskHandle_t move_theta_task;



bool emergency_stop = false;

uint8_t pwm_pins[] = {LEFT_MOTOR_PWM, LEFT_MOTOR_PWM2,RIGHT_MOTOR_PWM, RIGHT_MOTOR_PWM2};
uint8_t dir_pins[] = {LEFT_MOTOR_DIR, LEFT_MOTOR_DIR2,RIGHT_MOTOR_DIR, RIGHT_MOTOR_DIR2};


// pwm paramters
const int mtr_left_pwm_channel = 8;
const int mtr_right_pwm_channel = 4;
const int mtr_left_pwm2_channel = 5;
const int mtr_right_pwm2_channel = 6;
const int lresolution = 8;
const int freq = 4000;

const int pwm_channels[] = {mtr_left_pwm_channel,mtr_left_pwm2_channel,mtr_right_pwm_channel,mtr_right_pwm2_channel};


int left_motor_speed;
int left_motor_speed2;
int right_motor_speed;
int right_motor_speed2;

int motor_spds[] = {150,150,150,150};

int set_target_speed(float target, int motor, int init_spd);
void set_motor_speed_motor(uint8_t pwm_channel, uint8_t motor_dir, int spd);
void move_dist(void *params);
void move_theta(void *params);

void robot_setup()
{
  // Pins for Motor Controller
  pinMode(LEFT_MOTOR_DIR, OUTPUT);
  pinMode(LEFT_MOTOR_PWM, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM, OUTPUT);
  pinMode(LEFT_MOTOR_DIR2, OUTPUT);
  pinMode(LEFT_MOTOR_PWM2, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR2, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM2, OUTPUT);

  // Motor uses PWM Channel 8
  ledcSetup(mtr_left_pwm_channel, freq, lresolution);
  ledcAttachPin(LEFT_MOTOR_PWM, mtr_left_pwm_channel);
  ledcWrite(mtr_left_pwm_channel, 0);

  ledcSetup(mtr_right_pwm_channel, freq, lresolution);
  ledcAttachPin(RIGHT_MOTOR_PWM, mtr_right_pwm_channel);
  ledcWrite(mtr_right_pwm_channel, 0);

  ledcSetup(mtr_left_pwm2_channel, freq, lresolution);
  ledcAttachPin(LEFT_MOTOR_PWM2, mtr_left_pwm2_channel);
  ledcWrite(mtr_left_pwm2_channel, 0);

  ledcSetup(mtr_right_pwm2_channel, freq, lresolution);
  ledcAttachPin(RIGHT_MOTOR_PWM2, mtr_right_pwm2_channel);
  ledcWrite(mtr_right_pwm2_channel, 0);

  dist_queue = xQueueCreate(7,sizeof(float));
  dist_queue_int = xQueueCreate(5,sizeof(bool));
  theta_queue = xQueueCreate(5,sizeof(float));
  theta_queue_int = xQueueCreate(5,sizeof(bool));

  xTaskCreatePinnedToCore(
    move_dist,
    "move_dist",
    5*1024,
    NULL,
    1,
    &move_dist_task,
    1);

  xTaskCreatePinnedToCore(
    move_theta,
    "move_theta",
    5*1024,
    NULL,
    1,
    &move_theta_task,
    1);
  
}

void calibrate_motors(float target_speed = 70)
{
  reset_encoders();

  //pid only use p

  // float traget_speed = 70;
  int point5_spd = 0;

  for (int i=0; i < 4; i++){
   point5_spd = set_target_speed(target_speed, i, 140);
   Serial.println("_________________________________");
   Serial.println("_________________________________");
   Serial.print("motor: ");
   Serial.print(i);
   Serial.print(", point5_spd: ");
   Serial.println(point5_spd);
   Serial.println("_________________________________");
   Serial.println("_________________________________");
  }
  

  //motor 1
  //start all motors
  //run for 5 seconds 
  //output encoder values.



}

int set_target_speed(float target, int motor, int init_spd=150){
  //pwm_pins
  //dir_pins
  unsigned long timer_strt;
  unsigned long timer_curr;

  int its = 0;
  
  uint8_t pwm_pin = pwm_pins[motor];
  uint8_t dir_pin = dir_pins[motor];

  const int pwm_channel = pwm_channels[motor];

  //run for 200ms, do encoder count

  
  float tol = 0.1;
  float error = 0.0;

  float speed = 0.0;

  long cnts_prev;
  long cnts;

  float Kp = 2.0;
  float Kd = 0.5;
  float Ki = 0.1;
  
  float iterm=0;
  float prev_error=0;
  float prev_speed;
  

  while(!emergency_stop && abs(speed-target)>tol){
    timer_strt = millis();
    cnts_prev = get_encoder_pos(motor);

    set_motor_speed_motor((uint8_t) pwm_channel, dir_pin, init_spd);

    while(millis()-timer_strt < 50){

    }

    
    
    cnts = get_encoder_pos(motor);

    speed = ((float) abs(cnts -cnts_prev))*pulse_dist*1000/((float) millis()-timer_strt);
    if (its==0) prev_speed = speed;  //initialise previous speed

    Serial.print("motor: ");
    Serial.print(motor);
    Serial.print(", speed: ");
    Serial.print(speed);
    Serial.print(", init_spd: ");
    Serial.print(init_spd);

    error = target-speed;

    // iterm += Ki*error;
    iterm = Ki*prev_error; //using momentum for the i-term instead.
    
    Serial.print(", error: ");
    Serial.println((int) ((error)*Kp+Kd*(speed-prev_speed)+iterm));
    init_spd += (int) (error*Kp+Kd*(speed-prev_speed)+iterm);
    // init_spd -= (int) (Kd*(speed-prev_speed));

    if (init_spd > 255){
      init_spd=255;
      Serial.println("speed maximised");
      // break;
    } 

    its++;
    if(its>10) break;

    prev_speed=speed;
    prev_error = error;

  }

  set_motor_speed_motor((uint8_t) pwm_channel, dir_pin, 0);

  return init_spd;

}

void set_robot_target_speed(float target, int spd){
  bool fwd = true;
  unsigned long timer_strt;
  unsigned long timer_curr;

  int its = 0;
  
  // uint8_t pwm_pin = pwm_pins[motor];
  // uint8_t dir_pin = dir_pins[motor];

  // const int pwm_channel = pwm_channels[motor];

  //run for 200ms, do encoder count

  
  float tol = 0.2;
  float error = 0.0;

  float speed = 0.0;

  long cnts_prev;
  long cnts;

  float Kp = 2.0;
  float Kd = 0.5;
  float Ki = 0.1;
  
  float iterm=0;
  float prev_error=0;
  float prev_speed;

  if (spd < 0)
  {
    spd = -spd;
    fwd = false;
  }
  if (spd > 255)
    spd = 255;

  

}

void set_motor_speed_motor(uint8_t pwm_channel, uint8_t motor_dir, int spd){
  //for single motor
  bool fwd = true;
  

  if (spd < 0)
  {
    spd = -spd;
    fwd = false;
  }
  if (spd > 255)
    spd = 255;

  digitalWrite( motor_dir, fwd ? HIGH : LOW);
  ledcWrite(pwm_channel,spd);

}

void setMotorSpeed(int i, int spd)
{
  bool reverse = false;

  if (spd < 0)
  {
    spd = -spd;
    reverse = true;
  }
  if (spd > 255)
    spd = 255;
  // note left and right motors facing in opposite directions.
  if (i == LEFT)
  {
    if (reverse == false)
    {
      digitalWrite(LEFT_MOTOR_DIR, 1);
      digitalWrite(LEFT_MOTOR_DIR2, 1);
    }
    else if (reverse == true)
    {
      digitalWrite(LEFT_MOTOR_DIR, 0);
      digitalWrite(LEFT_MOTOR_DIR2, 0);
    }
    ledcWrite(mtr_left_pwm_channel, spd);
    ledcWrite(mtr_left_pwm2_channel, spd);
    // if (spd > 0)
    // {
    //   Serial.print("left motor: ");
    //   Serial.println(spd);
    // }
  }
  else /*if (i == RIGHT) //no need for condition*/
  {
    if (reverse == false)
    {
      digitalWrite(RIGHT_MOTOR_DIR, 1);
      digitalWrite(RIGHT_MOTOR_DIR2, 1);
    }
    else if (reverse == true)
    {
      digitalWrite(RIGHT_MOTOR_DIR, 0);
      digitalWrite(RIGHT_MOTOR_DIR2, 0);
    }
    ledcWrite(mtr_right_pwm_channel, spd);
    ledcWrite(mtr_right_pwm2_channel, spd);
    // if (spd > 0)
    // {
    //   Serial.print("right motor: ");
    //   Serial.println(spd);
    // }
  }
}

void setMotorSpeeds(int leftSpeed, int rightSpeed)
{
  
  setMotorSpeed(RIGHT, rightSpeed);
  setMotorSpeed(LEFT, leftSpeed);
 
}

void robot_stop(){
  int motr_spd;
  while(abs(motr_spd)>0){

  }
    setMotorSpeeds(0,0);
}

void robot_back(){
  for(int i=0; i<4; i++){
        set_motor_speed_motor((uint8_t) pwm_channels[i],dir_pins[i],-motor_spds[i]);
    }
    // setMotorSpeeds(-left_motor_speed, -right_motor_speed);
}

void robot_fwd(){
    
    for(int i=0; i<4; i++){
        // Serial.println(pwm_channels[i]);
        // Serial.println(dir_pins[i]);
        // Serial.println(motor_spds[i]);
        set_motor_speed_motor((uint8_t) pwm_channels[i],dir_pins[i],motor_spds[i]);
    }

    // setMotorSpeeds(left_motor_speed, right_motor_speed);
}

void robot_left(){
    setMotorSpeeds(-left_motor_speed, right_motor_speed);
}

void robot_right(){
    setMotorSpeeds(left_motor_speed, -right_motor_speed);
}

double constrainAngle(double x){
    x = fmod(x + 180,360);
    if (x < 0)
        x += 360;
    return x - 180;
}




void move_dist(void *params){

  
  float dist = 0.0; //myparams->dist;
  bool stop;
  const TickType_t xDelay = 1 / portTICK_PERIOD_MS; 
  
  while(true){
    // Serial.println("in move dist");
    xQueueReceive(dist_queue, &dist, portMAX_DELAY);
    int motor_spds_original[] = {100, 100, 100,100};
    memcpy(motor_spds_original, motor_spds, sizeof(motor_spds));
    
    Serial.print(dist);
    Serial.println(" distance recieved");
    reset_encoders();
    // Serial.println("encoders reset");
    float total_pulses = abs(dist/pulse_dist);
    Serial.println(total_pulses);
    unsigned long t_strt = millis();
    long enc_puls_prev[] = {0,0,0,0};
    
    long cm30 = (long) (30.0/pulse_dist); //number of pulses in 30cm
    int spd0 = motor_spds[0];
    while (!emergency_stop && ((float) (abs(encoder0Pos)+abs(encoder2Pos)))< 2*total_pulses){

      if (true && (millis() - t_strt > 30))
      {
        t_strt=millis();
        
        for (int i = 1; i < 4; i++)
        {
          int ms;
          ms = abs(motor_spds[i]);
          if (ms == 0)
            break;
          if (abs(get_encoder_pos(i)-enc_puls_prev[i]) > abs(encoder0Pos-enc_puls_prev[0]))
          {
            motor_spds[i]--;
          }
          else if (abs(get_encoder_pos(i)-enc_puls_prev[i]) < abs(encoder0Pos-enc_puls_prev[0]))
          {
            motor_spds[i]++;
          }

          

          enc_puls_prev[i] = get_encoder_pos(i);
          // if (abs(enc_puls_prev[0]) > cm30 ){
          //   if (spd0 > 100) motor_spds[i] -=5;
          //   motor_spds[i] -= 5;
          //   if (motor_spds[i]<25){
          //     motor_spds[i] = 25;
          //   }
          // }
        }
        enc_puls_prev[0] = get_encoder_pos(0);
        if ((total_pulses-abs(enc_puls_prev[0]))<cm30){
          spd0 = motor_spds[0];
          //30 cm left to travel
          if (spd0>55) {
            for(int j=0; j<4; j++){
              motor_spds[j] = motor_spds[j] - 3;
            }
          }

        }
      }

        if(dist>0){
            robot_fwd();
        }
        if (dist<0){
            robot_back();
        }
        // if (xQueueReceive(dist_queue_int, &stop, xDelay)) {
        //   dist=0.0;
        //   break;
        // }

        if(xQueueReceive(dist_queue, &dist, xDelay)){
          //keep going for that distance
          total_pulses = abs(dist/pulse_dist);
          reset_encoders();
          for (int i =0; i<4; i++){enc_puls_prev[i]=get_encoder_pos(i);}
          Serial.println("interrupting cow!");
        }
        // vTaskDelay(500);
        // Serial.println(total_pulses);
        // Serial.println(encoder0Pos);
    }
    robot_stop();
    emergency_stop=true;
    Serial.println(encoder0Pos);
    Serial.println(encoder2Pos);
    //now reset motor speeds
    memcpy(motor_spds, motor_spds_original, sizeof(motor_spds));

  }

}

void move_theta(void *params){

  float thet = 0.0; //myparams->dist;
  bool stop;
  const TickType_t xDelay = 1 / portTICK_PERIOD_MS; 
  float dist = 0.0;
  float total_pulses = 0.0; 
  
  while(true){
    // Serial.println("in move dist");
    xQueueReceive(theta_queue, &thet, portMAX_DELAY);
    reset_encoders();
    dist = turning_circle*(thet/360);
    total_pulses = abs(dist/pulse_dist);

    while (!emergency_stop && ((float) (abs(encoder0Pos)+abs(encoder2Pos)))< 2*total_pulses){
        if(dist>0){
            robot_right();
        }
        if (dist<0){
            robot_left();
        }
        // if (xQueueReceive(dist_queue_int, &stop, xDelay)) {
        //   dist=0.0;
        //   break;
        // }

        if(xQueueReceive(theta_queue, &thet, xDelay)){
          //keep going for that distance
          dist = turning_circle*(thet/360);
          total_pulses = abs(dist/pulse_dist);
          reset_encoders();
          Serial.println("interrupting cow!");
        }
        // vTaskDelay(500);
        // Serial.println(total_pulses);
        // Serial.println(encoder0Pos);
    }
    robot_stop();
    emergency_stop=true;
    // vTaskDelete(NULL);

  }

}

void move_robot_dist(float dist){
    reset_encoders();
    Serial.println(dist);
    float total_pulses = abs(dist/pulse_dist);
    Serial.println(total_pulses);
    while (!emergency_stop && abs(encoder0Pos)+abs(encoder2Pos)< 2*total_pulses){
        if(dist>0){
            robot_fwd();
        }
        if (dist<0){
            robot_back();
        }
        delay(200);
        Serial.println(encoder0Pos);
    }
    robot_stop();
    
}

void turn_robot(float thet){
    reset_encoders();
//   thet = constrainAngle(thet);
    float dist = turning_circle*(thet*2*pi/360);
    float total_pulses = abs(dist/pulse_dist);
    while (!emergency_stop && abs(encoder0Pos)+abs(encoder2Pos)< 2*total_pulses){
        if(thet>0){
            robot_right();
        }
        if (thet<0){
            robot_left();
        }
    }
    robot_stop();
}

//i need some code to dirve the seperate motors



#endif