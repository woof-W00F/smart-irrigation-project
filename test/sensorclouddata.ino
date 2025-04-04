#include<ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "oviv 181";
const char* passwd = "doggypup";
const unsigned int writeinterval = 25000;
const char* apikey = "nD3AhGCxTkcCYJ3Kis5jHkSefKI8Pt83";
String https_host = "api.asksensors.com";
const int https_port = 443;
const char* https_fingerprint =  "B5 C3 1B 2C 0D 5D 9B E5 D6 7C B6 EF 50 3A AD 3F 9F 1E 44 75";
WiFiClientSecure client;


void setup() {
  Serial.begin(9600);
  Serial.print("connecting to WIFI : ");
  Serial.println(ssid);
  WiFi.begin(ssid, passwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("-> WiFi connected");
  Serial.println("-> IP address: ");
  Serial.println(WiFi.localIP());
  client.setInsecure();

  pinMode(A0,INPUT);
  
}

void loop() {
  Serial.print("********** connecting to HOST : ");
  Serial.println(https_host);
  if (!client.connect(https_host, https_port)) {
    Serial.println("-> connection failed");
    //return;
  }
  
  String url = "/write/";
  url += apikey;
  url += "?module1=";
  //url += random(10,100); //This sends/writes data to the website 
  url += readpin();

  
  Serial.print("********** requesting URL: ");
  Serial.println(url);
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + https_host + "\r\n" +
               "Connection: close\r\n\r\n");
 
  Serial.println("> Request sent to ASKSENSORS");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
        String line = client.readStringUntil('\n');
        Serial.println("********** ASKSENSORS replay:");
        Serial.println(line);
        delay(1000);
    }
  }
  
  /*
  while(client.connected()){
    client.print(99);
    Serial.println("success");
    delay(1000);
    }
  */


  delay(10000);
}

int readpin(){
  float val;
  val = analogRead(A0);
  val = 1 - (val/1024.0);
  val = val*100;
  return int(val);
  }
