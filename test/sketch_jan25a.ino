#include <ESP8266WiFi.h>

char *ssid = "oviv 181";
char *passwd = "doggypup";

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);
  delay(10);

  WiFi.begin(ssid,passwd);
  Serial.print("Connecting to ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("....");
    digitalWrite(LED_BUILTIN,LOW);
    delay(500);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(500);
    }
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());  
 
}

void loop() {
  // put your main code here, to run repeatedly:

}
