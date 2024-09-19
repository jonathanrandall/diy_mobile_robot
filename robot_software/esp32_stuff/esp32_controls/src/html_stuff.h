
#ifndef HTML_STUFF_H_
#define HTML_STUFF_H_

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "motor_ctrl_stuff.h"


IPAddress local_IP(192, 168, 1, 211);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   // optional
IPAddress secondaryDNS(8, 8, 4, 4); // optional

AsyncWebServer server(80);


void init_wifi()
{
    if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
    {
        Serial.println("STA Failed to configure");
    }
    WiFi.mode(WIFI_AP_STA); // need this mode to use esp now

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");

    Serial.print("Go to: http://");
    Serial.println(WiFi.localIP());

    
}



float param_theta;
float param_dist;

bool dist_set = false;
bool theta_set = false;

// const char* ssid = "WiFi-C5BFGF";
// const char* password = "****";

String sliderValue = "000";
String variable;

const char* PARAM_INPUT_1 = "distance";
const char* PARAM_INPUT_2 = "angle";


// setting PWM properties
//const int freq = 5000;
//const int ledChannel = 0;
//const int resolution = 8;

const char* PARAM_INPUT = "value";
const char* PARAM_CMD = "go";

// <div class="grid-container">
//       <img src="http://rpi5.local:8000/stream.mpg" class="grid-item" id="rt_img">
//       <img src="http://192.168.1.129:81/stream" class="grid-item" id = "lft_img">
//     </div>


const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
  <head>
    <title>ESP32-CAM Robot</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      body { font-family: Arial; text-align: center; margin:0px auto; padding-top: 30px;}
    .slider { -webkit-appearance: none; margin: 14px; width: 360px; height: 25px; background: #FFD65C;
      outline: none; -webkit-transition: .2s; transition: opacity .2s;}
    .slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 35px; height: 35px; background: #003249; cursor: pointer;}
    .slider::-moz-range-thumb { width: 35px; height: 35px; background: #003249; cursor: pointer; } 
      table { margin-left: auto; margin-right: auto; }
      td { padding: 8 px; }
      .button {
        background-color: #2f4468;
        border: none;
        color: white;
        padding: 10px 20px;
        text-align: center;
        text-decoration: none;
        display: inline-block;
        font-size: 18px;
        margin: 6px 3px;
        cursor: pointer;
        -webkit-touch-callout: none;
        -webkit-user-select: none;
        -khtml-user-select: none;
        -moz-user-select: none;
        -ms-user-select: none;
        user-select: none;
        -webkit-tap-highlight-color: rgba(0,0,0,0);
      }
       .grid-container {
        display: grid;
        grid-template-columns: repeat(2, 1fr); /* 2 columns */
        grid-gap: 10px;
      }

      .grid-item {
        width: 100%%;
        height: auto; 
        max-height: 400px; 
        object-fit: cover; 
      }
    </style>
  </head>
  <body>
    <h1>ESP32 Robot</h1>
    <form>
    <label for="text">Distance:</label>
    <input type="text" id="distance" name="distin">
    <button type="button" onclick="readText('distance')" ontouchstart="readText('distance')">Read Text</button>
    </form>
  <form>
    <label for="text">Angle:</label>
    <input type="text" id="angle" name="angleing">
    <button type="button" onclick="readText('angle')" ontouchstart="readText('angle')">Read Text</button>
  </form><br>
    
      <img src="http://rpi5.local:8000/stream.mpg"  id="rt_img">
      <img src="http://192.168.1.129:81/stream" id = "lft_img">
    
  <p><span id="textSliderValue">%SLIDERVALUE%</span></p>
  <p><input type="range" onchange="updateSliderPWM(this)" id="pwmSlider" min="0" max="255" value="%SLIDERVALUE%" step="1" class="slider"></p>
    <table>
      <tr><td colspan="3" align="center"><button class="button" onmousedown="toggleCheckbox('forward');" ontouchstart="toggleCheckbox('forward');" onmouseup="toggleCheckbox('stop');" ontouchend="toggleCheckbox('stop');">Forward</button></td></tr>
      <tr><td align="center"><button class="button" onmousedown="toggleCheckbox('left');" ontouchstart="toggleCheckbox('left');" onmouseup="toggleCheckbox('stop');" ontouchend="toggleCheckbox('stop');">Left</button></td><td align="center"><button class="button" onmousedown="toggleCheckbox('stop');" ontouchstart="toggleCheckbox('stop');">Stop</button></td><td align="center"><button class="button" onmousedown="toggleCheckbox('right');" ontouchstart="toggleCheckbox('right');" onmouseup="toggleCheckbox('stop');" ontouchend="toggleCheckbox('stop');">Right</button></td></tr>
      <tr><td colspan="3" align="center"><button class="button" onmousedown="toggleCheckbox('backward');" ontouchstart="toggleCheckbox('backward');" onmouseup="toggleCheckbox('stop');" ontouchend="toggleCheckbox('stop');">Backward</button></td></tr>                   
    </table>
   <script>
   function readText(x) {
    var text = document.getElementById(x).value;
    var xhr = new XMLHttpRequest();
     xhr.open("GET", "/action?"+x+"=" + text, true);
     xhr.send();
  
    }
   function toggleCheckbox(x) {
     var xhr = new XMLHttpRequest();
     xhr.open("GET", "/action?go=" + x, true);
     xhr.send();
   }
  function updateSliderPWM(element) {
  var sliderValue = document.getElementById("pwmSlider").value;
  document.getElementById("textSliderValue").innerHTML = sliderValue;
  console.log(sliderValue);
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/slider?value="+sliderValue, true);
  xhr.send();
}
  </script>
  </body>
</html>
)rawliteral";

// Replaces placeholder with button section in your web page
String processor(const String& var){
  //Serial.println(var);
  if (var == "SLIDERVALUE"){
    return sliderValue;
  }
  return String();
}

void start_server(){
  // Route for root / web page
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/slider?value=<inputMessage>
  server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest *request) {
    if (request->hasParam(PARAM_INPUT)) {
      sliderValue = request->getParam(PARAM_INPUT)->value();      
      uint8_t motor_speed = (uint8_t) sliderValue.toInt(); //ledcWrite(ledChannel, sliderValue.toInt());
    //   Serial.println(motor_speed);
      left_motor_speed = motor_speed;
      right_motor_speed = motor_speed;
      for(int i=0; i<4; i++){motor_spds[i]=motor_speed;}
    }
    else {
      String inputMessage = "No message sent";
    }
//    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });
 
  // Send a GET request to <ESP_IP>/slider?value=<inputMessage>
  server.on("/action", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_CMD)) {
      inputMessage = request->getParam(PARAM_CMD)->value();
      variable = inputMessage.c_str();
      
      if (variable== "stop"){
        emergency_stop=true;
        robot_stop();
      }
      if (variable== "backward"){
        emergency_stop=false;
        robot_back();
        
      }
      if (variable== "forward"){
        emergency_stop=false;
        robot_fwd();
        
      }
      if (variable== "left"){
//        Serial.println("left");
        emergency_stop=false;
        robot_left();
        
      }
      if (variable== "right"){
        emergency_stop=false;
        robot_right();
        
      }
    }
    else if (request->hasParam(PARAM_INPUT_1)) {
      param_dist = (float) (request->getParam(PARAM_INPUT_1)->value()).toDouble();
      Serial.println(param_dist);
      emergency_stop=false;
      xQueueSend(dist_queue,&param_dist, 0);
      
    }
    else if (request->hasParam(PARAM_INPUT_2)) {
      param_theta = (float) (request->getParam(PARAM_INPUT_2)->value()).toDouble();
      emergency_stop=false;
      xQueueSend(theta_queue,&param_theta, 0);
      // turn_robot(param_theta);
//      inputParam = PARAM_INPUT_2;
    }
    else {
      inputMessage = "No message sent";
    }
//    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });
  
  // Start server
  server.begin();
}

#endif