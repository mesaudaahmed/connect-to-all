// Code to upload onto ESP8266
#include <PubSubClient.h>
#include <WiFi.h>

const char* ssid = "Yusef_2GExt";
const char* password = "054652898";

#define MQTT_SERVER  "10.0.0.18"   /// example 192.168.0.19

long now = millis();
long lastMeasure = 0;
//String value = "";
char* Topic = "inTopic";

WiFiClient wifiClient;
void setup() {
  //initialize the light as an output and set to LOW (off)

  //start the serial line for debugging
  Serial.begin(9600);
  delay(100);
    pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(15,OUTPUT);
  delay(100);
  //start wifi subsystem
  WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
    }
  //wait a bit before starting the main loop
      delay(2000);
      if(WiFi.status() == WL_CONNECTED)  
      {
        
        Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  }
}

PubSubClient client(MQTT_SERVER,1883, callback, wifiClient);
void loop() {

  if (!client.connected() && WiFi.status()== 3) {reconnect();}
  client.loop();
  delay(20);
  }
void callback(char* topic, byte* payload, unsigned int length) {
String topicStr = topic;
  // Switch on the LED if an 1 was received as first character
  if (payload[0] == '0') {
    client.publish("outTopic","Realy 1 is ON");
    Serial.print("0");
    digitalWrite(12,HIGH);} 

  if (payload[0] == '1') {
    client.publish("outTopic","Realy 1 is OFF");
    Serial.print("1");
    digitalWrite(12,LOW);}
    
  if (payload[0] == '2') {
    client.publish("outTopic","Realy 2 is ON");
    Serial.print("2");
    digitalWrite(13,HIGH);} 

  if (payload[0] == '3') {
    client.publish("outTopic","Realy 2 is OFF");
    Serial.print("3");
    digitalWrite(13,LOW);}
    
  if (payload[0] == '4') {
    client.publish("outTopic","Realy 3 is ON");
    Serial.print("4");
    digitalWrite(14,HIGH);} 

  if (payload[0] == '5') {
    client.publish("outTopic","Realy 3 is OFF");
    Serial.print("5");
    digitalWrite(14,LOW);}
    
  if (payload[0] == '6') {
    client.publish("outTopic","Realy 4 is ON");
    Serial.print("6");
    digitalWrite(15,HIGH);} 

  if (payload[0] == '7') {
    client.publish("outTopic","Realy 4 is OFF");
    Serial.print("7");
    digitalWrite(15,LOW);}
}
void reconnect() {
      // Loop until we're reconnected
         if(WiFi.status() != WL_CONNECTED){
         while (WiFi.status() != WL_CONNECTED){
              delay(500);
                                              }
                                           }
    //make sure we are connected
      if(WiFi.status() == WL_CONNECTED){
    //loop until we are recennected to mqtt broker
     while(!client.connected()){
     String clientName;
    clientName +="esp8266-";
    uint8_t mac[6];
    WiFi.macAddress(mac);
    clientName += macToStr(mac);
    if(client.connect((char*) clientName.c_str())){
      Serial.print("\tMT00 Connected");
      client.subscribe(Topic);
      }
      //otherwise print failed for debugging
      else{Serial.println("\tFailed.");abort();}
    }
  }
}
//generate unique name for MAC Add
String macToStr(const uint8_t* mac){
  String result;
  for (int i = 0; i<6;++i){
    result += String(mac[i],16);
    if(i<5){
      result += ';';
      }
    }
    return result;
  }
