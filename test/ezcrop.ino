#include<ESP8266WiFi.h>
#include<BlynkSimpleEsp8266.h>

const char *ssid = "oviv 181";
const char *passwd = "doggypup";



void setup() {
  Serial.begin(9600);
  connectwifi();

}

void loop() {
  // put your main code here, to run repeatedly:

}

void connectwifi(){
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("....");
    digitalWrite(LED_BUILTIN,LOW);
    delay(500);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(500);
    }
    Serial.print("Connection established!");
    Serial.println(WiFi.localIP());
  
  }
