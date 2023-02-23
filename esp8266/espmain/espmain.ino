#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Ticker.h>
#include "Light_sensor.h"

//#define PIN_LED1 13
#define PIN_PIR D2
#define PIN_LIGHT_SENSOR A0

Light_sensor* light_sensor;

// 获取当前时间
unsigned long now = millis();
// 上一次触发中断的时间
unsigned long lastTrigger = 0;
// 是否开启计时器的标志
boolean startTimer = false;
//  定时时间周期 2s
unsigned long detectDuration = 2000;

// Credentials for WiFi
//const char* ssid = "bobo";
//const char* password = "123456zby";
const char* ssid = "Vodafone-63Hao";
const char* password = "liushisan.4";

// MQTT Server(eg 192.168.1.4)
const char* mqtt_server = "broker.mqtt-dashboard.com";

// WiFi Client
WiFiClient nodeClient;
PubSubClient client(nodeClient);

// Function to connect NodeMCU to WiFi router
void wifiConfig(){
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected, NodeMCU IP address: ");
  Serial.println(WiFi.localIP());
}

// Function to reconnect NodeMCU with MQTT broker
void reconnect(){
    while (!client.connected()) {
      Serial.print("Attempting MQTT connection...");
  
      if (client.connect("MQTTClient")){
        Serial.println("connected");  
      } 
      else{
        Serial.print("failed, State: ");
        Serial.print(client.state());
        Serial.println("try again in 5 seconds...");
        delay(5000);
      }
    }
}

void setup(){
  
  Serial.begin(115200);
  startTimer = true;
  Serial.print("ESP starting...");
  light_sensor = new Light_sensor(PIN_LIGHT_SENSOR);
  pinMode(PIN_PIR, INPUT_PULLUP);

  wifiConfig();
  client.setServer(mqtt_server, 1883);
  
}

void loop() {
  now = millis();

  
  // 如果已经开始了计时，且当前时间减去上一次触发中断时间大于人体感应模块检测的时间周期 2s，将LED电平置为低，且将计时器标志置为false，等待下一次中断
  if(startTimer && (now - lastTrigger > detectDuration)) {
  int light_value=0,detect=0;
    if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("MQTTClient");
    
    // do something
    Serial.println("esp system running");
    
    light_value = light_sensor->getLightLevel();
    detect = digitalRead(PIN_PIR);
    Serial.println("detect_status: ");
    Serial.println(detect);
    Serial.println("light_value: ");
    Serial.println(light_value);

    //Convert float to string and store them in arrays
    char humidity[7]={ 'L', 'o', 'o', 'k', '\0' };
  

    // Publishes Temperature and Humidity values
    client.publish("light_level/human:", humidity);
    lastTrigger =now;
    //startTimer = false;
  }
} 
