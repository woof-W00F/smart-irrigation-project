#include<ESP8266WiFi.h>
#include <WiFiClientSecure.h>

int reading;

void setup() {
  Serial.begin(9600);
  pinMode(D1,OUTPUT);
  pinMode(A0,INPUT);
}

void loop() {
 
reading = read_data();
Serial.println(reading);

if (reading > 50){
  digitalWrite(D1,HIGH);
  delay(2000);
  }
else{  
  digitalWrite(D1,LOW);
  delay(2000);}

  delay(500);
}

int read_data(){
  float val;
  val = analogRead(A0);
  val = (val/1024.0)*100;
  return int(val);
  }
