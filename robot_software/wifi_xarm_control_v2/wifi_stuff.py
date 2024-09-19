import network
import socket
from machine import Pin, PWM


# Configure Wi-Fi connection
ssid = '***'
password = '***'


# # HTML Content
# html = """<!DOCTYPE html>
# <html>
# <head>
#     <title>Servo Control</title>
# </head>
# <body>
#     <h1>Servo Control</h1>
#     <input type="range" min="0" max="180" value="90" id="servoSlider" onchange="sendAngle(this.value)">
#     <script>
#         function sendAngle(angle) {
#             var xhr = new XMLHttpRequest();
#             xhr.open("GET", "/angle?value=" + angle, true);
#             xhr.send();
#         }
#     </script>
# </body>
# </html>
# """
# HTML Content
html = """<!DOCTYPE html>
<html>
  <head>
    <title>ESP32-CAM Robot</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      body { font-family: Arial; text-align: center; margin:0px auto; padding-top: 10px;}
    .slider { -webkit-appearance: none; margin: 10px; width: 500px; height: 20px; background: #FFD65C;
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
      img {  width: auto ;
        max-width: 100% ;
        height: auto ; 
      }
    </style>
  </head>
  <body>
    <h1>ESP32 Robot Slider</h1>
      
    <p><span id="text1">Claw</span><input type="range" onchange="updateSliderPWM('1')" id="pwmSlider1" min="0" max="1000" value="500" step="1" class="slider"><span id="textSliderValue1">500</span></p>
    <p><span id="text2">Right</span><input type="range" onchange="updateSliderPWM('2')" id="pwmSlider2" min="0" max="1000" value="500" step="1" class="slider"><span id="textSliderValue2">500</span></p>
    <p><span id="text3">Left</span><input type="range" onchange="updateSliderPWM('3')" id="pwmSlider3" min="0" max="1000" value="500" step="1" class="slider"><span id="textSliderValue3">500</span></p>
    <p><span id="text4">Rotate</span><input type="range" onchange="updateSliderPWM('4')" id="pwmSlider4" min="0" max="1000" value="500" step="1" class="slider"><span id="textSliderValue4">500</span></p>
    <p><span id="text5">Left</span><input type="range" onchange="updateSliderPWM('5')" id="pwmSlider5" min="0" max="1000" value="500" step="1" class="slider"><span id="textSliderValue5">500</span></p>
    <p><span id="text6">Rotate</span><input type="range" onchange="updateSliderPWM('6')" id="pwmSlider6" min="0" max="1000" value="500" step="1" class="slider"><span id="textSliderValue6">500</span></p>
    
   <script>
   
   function updateSliderPWM(element) {
      var sliderValue = document.getElementById("pwmSlider"+element).value;
      document.getElementById("textSliderValue"+element).innerHTML = sliderValue;
      console.log(sliderValue);
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/slider?value="+element+"_"+sliderValue, true);
      xhr.send();

      localStorage.setItem("pwmSlider" + element, sliderValue);
    }

    
    function loadSliderValues() {
        for (let i = 1; i <= 6; i++) {
            var slider = document.getElementById("pwmSlider" + i);
                var defaultValue = 500;
                slider.value = defaultValue;
                document.getElementById("textSliderValue" + i).innerHTML = defaultValue;
            }
    }

    
    window.onload = loadSliderValues;
   
  </script>
  </body>
</html>
"""


# # Setup the web server
# addr = socket.getaddrinfo('0.0.0.0', 80)[0][-1]
# s = socket.socket()
# s.bind(addr)
# s.listen(1)

# print('listening on', addr)

# while True:
#     cl, addr = s.accept()
#     print('client connected from', addr)
#     request = cl.recv(1024)
#     request = str(request)
#     print('request:', request)
    
#     if 'GET / ' in request:
#         response = html
#     elif 'GET /angle?value=' in request:
#         angle = int(request.split('value=')[1].split(' ')[0])
#         servo.write_angle(angle)
#         response = "Angle set to " + str(angle)
#     else:
#         response = "Invalid Request"
    
#     cl.send('HTTP/1.1 200 OK\n')
#     cl.send('Content-Type: text/html\n')
#     cl.send('Connection: close\n\n')
#     cl.sendall(response)
#     cl.close()

