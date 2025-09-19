#include "wifiserver.h"

#pragma region HTML_PAGE
const char indexPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Robot Dashboard</title>
<style>
body { font-family: Arial; background: #f0f0f0; }
h2 { margin: 10px 0; }
section { background: #fff; padding: 10px; margin: 10px; border-radius: 8px; }
input { width: 80px; }
button { width: 60px; height: 60px; margin: 2px; pointer-events: none; }
#dpad { display: grid; grid-template-columns: 60px 60px 60px; grid-template-rows: 60px 60px 60px; }
</style>
</head>
<body>
<h1>Robot Dashboard</h1>
<section>
<h2>IMU</h2>
Accel X:<input id="accX"><br>
Accel Y:<input id="accY"><br>
Accel Z:<input id="accZ"><br>
Gyro X:<input id="gyroX"><br>
Gyro Y:<input id="gyroY"><br>
Gyro Z:<input id="gyroZ"><br>
Mag X:<input id="magX"><br>
Mag Y:<input id="magY"><br>
Mag Z:<input id="magZ"><br>
Temp:<input id="imuTemp"><br>
</section>
<section>
<h2>Battery</h2>
Voltage:<input id="voltage"><br>
Current:<input id="current"><br>
Shunt:<input id="shunt"><br>
Power:<input id="power"><br>
Energy:<input id="energy"><br>
Charge:<input id="charge"><br>
Temp:<input id="batTemp"><br>
</section>
<section>
<h2>Controller</h2>
<button id="home">Home</button>
<button id="restart">Restart</button>
<button id="stopped">Stopped</button>
<div id="dpad">
<button id="up">↑</button><button></button><button id="down">↓</button>
<button id="left">←</button><button></button><button id="right">→</button>
</div>
<button id="forward">Forward</button>
<button id="backward">Backward</button>
</section>
<script>
function updateDashboard() {
  fetch('/data')
    .then(resp => resp.json())
    .then(data => {
      // IMU
      document.getElementById("accX").value = data.imu.accX.toFixed(2);
      document.getElementById("accY").value = data.imu.accY.toFixed(2);
      document.getElementById("accZ").value = data.imu.accZ.toFixed(2);
      document.getElementById("gyroX").value = data.imu.gyroX.toFixed(2);
      document.getElementById("gyroY").value = data.imu.gyroY.toFixed(2);
      document.getElementById("gyroZ").value = data.imu.gyroZ.toFixed(2);
      document.getElementById("magX").value = data.imu.magX.toFixed(2);
      document.getElementById("magY").value = data.imu.magY.toFixed(2);
      document.getElementById("magZ").value = data.imu.magZ.toFixed(2);
      document.getElementById("imuTemp").value = data.imu.temp.toFixed(2);
      // Battery
      document.getElementById("voltage").value = data.battery.voltage.toFixed(2);
      document.getElementById("current").value = data.battery.current.toFixed(2);
      document.getElementById("shunt").value = data.battery.shuntvoltage.toFixed(2);
      document.getElementById("power").value = data.battery.power.toFixed(2);
      document.getElementById("energy").value = data.battery.energy.toFixed(2);
      document.getElementById("charge").value = data.battery.charge.toFixed(2);
      document.getElementById("batTemp").value = data.battery.temp.toFixed(2);
      // Controller
      document.getElementById("home").style.background = data.controller.home ? "green" : "red";
      document.getElementById("restart").style.background = data.controller.restart ? "green" : "red";
      document.getElementById("stopped").style.background = data.controller.stopped ? "green" : "red";
      document.getElementById("up").style.background = data.controller.up ? "green" : "red";
      document.getElementById("down").style.background = data.controller.down ? "green" : "red";
      document.getElementById("left").style.background = data.controller.left ? "green" : "red";
      document.getElementById("right").style.background = data.controller.right ? "green" : "red";
      document.getElementById("forward").style.background = data.controller.forward ? "green" : "red";
      document.getElementById("backward").style.background = data.controller.backward ? "green" : "red";
    })
    .catch(err => console.log(err));
}
setInterval(updateDashboard, 200);
</script>
</body>
</html>
)rawliteral";
#pragma endregion

WIFIServer::WIFIServer() : server(PORT) {}

void WIFIServer::begin() {
    Console.printf("Connecting to %s\n", SSID);
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Console.println("\nWiFi connected.");
    Console.printf("IP address: %s\n", WiFi.localIP().toString().c_str());
    server.begin();
    Console.println("Server started");
}

void WIFIServer::handleClient(BLEController::BLEControllerData& c, IMU::IMUData& i, BatteryMonitor::BatteryData& b) {
    if (!webClient || !webClient.connected()) {
        webClient = server.accept();
        clientRequest = "";
    }

    if (webClient && webClient.connected() && webClient.available()) {
        char ch = webClient.read();
        clientRequest += ch;

        if (clientRequest.endsWith("\r\n\r\n")) {
            if (clientRequest.indexOf("GET / ") >= 0) {
                 webClient.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n");
                webClient.print(indexPage);
                webClient.stop();
                Console.println("Served HTML page");
                return;
            }
            if (clientRequest.indexOf("GET /data") >= 0) {
                StaticJsonDocument<512> doc;

                // IMU
                doc["imu"]["accX"] = i.accelerometer.acceleration.x;
                doc["imu"]["accY"] = i.accelerometer.acceleration.y;
                doc["imu"]["accZ"] = i.accelerometer.acceleration.z;
                doc["imu"]["gyroX"] = i.gyroscope.gyro.x;
                doc["imu"]["gyroY"] = i.gyroscope.gyro.y;
                doc["imu"]["gyroZ"] = i.gyroscope.gyro.z;
                doc["imu"]["magX"] = i.magnetometer.magnetic.x;
                doc["imu"]["magY"] = i.magnetometer.magnetic.y;
                doc["imu"]["magZ"] = i.magnetometer.magnetic.z;
                doc["imu"]["temp"] = i.temperature.temperature;

                // Battery
                doc["battery"]["voltage"] = b.voltage;
                doc["battery"]["current"] = b.current;
                doc["battery"]["shuntvoltage"] = b.shuntvoltage;
                doc["battery"]["power"] = b.power;
                doc["battery"]["energy"] = b.energy;
                doc["battery"]["charge"] = b.charge;
                doc["battery"]["temp"] = b.temperature;

                // Controller
                doc["controller"]["home"] = c.home;
                doc["controller"]["restart"] = c.restart;
                doc["controller"]["stopped"] = c.stopped;
                doc["controller"]["up"] = c.up;
                doc["controller"]["down"] = c.down;
                doc["controller"]["left"] = c.left;
                doc["controller"]["right"] = c.right;
                doc["controller"]["forward"] = c.forward;
                doc["controller"]["backward"] = c.backward;

                String output;
                serializeJson(doc, output);

                webClient.print("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nConnection: close\r\n\r\n");
                webClient.print(output);
                webClient.stop();
                return;
            }
        }
    }
}