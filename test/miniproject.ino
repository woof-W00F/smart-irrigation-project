#include<ESP8266WiFi.h>
#include<Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define APIKEY "AIzaSyBitGLWajCNnwkoeKWx_4Q_pS3hdSk1mNc"
#define DATABASEURL "https://ezcrop-7c579-default-rtdb.asia-southeast1.firebasedatabase.app"

float reading;
int precipitation;
String swtch;
const char *ssid = "oviv 181";
const char *passwd = "doggypup";

String refPath;
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

void setup(){
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(D0,OUTPUT);
  pinMode(D3,OUTPUT); 
  wificonnect();
  config.api_key = APIKEY;
  config.database_url = DATABASEURL;
  
  //Firebase Signup
  if (Firebase.signUp(&config,&auth,"","")){
    Serial.println("ok");
    signupOK = true;
    }
    else{
      Serial.printf("%s\n",config.signer.signupError.message.c_str());
      }

  config.token_status_callback = tokenStatusCallback;

  Firebase.begin(&config,&auth);
  Firebase.reconnectWiFi(true);

  
  }
void loop(){
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)) {
      sendDataPrevMillis = millis();
      
      //Soil moisture sensor
      reading = read_data();
      Serial.print("Sensor reading : ");
      Serial.println(reading);
      if (Firebase.RTDB.setFloat(&fbdo,refPath+"irrigation_control/SensorReading", reading)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType()  );
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    //precipitation
    if (Firebase.RTDB.getInt(&fbdo, "/irrigation_control/precipitation")) {
        if (fbdo.dataType() == "int") {
          precipitation = fbdo.intData();
          Serial.print("Precipitation : ");
          Serial.println(precipitation);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

//Logic to turn pump on or off
swtch = pumpswitch(reading,precipitation);

   Serial.print("Pump Switch : ");
   Serial.println(swtch);
   if (Firebase.RTDB.setString(&fbdo,refPath+"irrigation_control/switch", swtch)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType()  );
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  
  }
}

void wificonnect(){
  WiFi.begin(ssid,passwd);
  Serial.print("Connecting to wifi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.println(".");
    digitalWrite(D0,HIGH);
    delay(500);
    digitalWrite(D0,LOW);
    delay(1000);
    }
  Serial.println();
  Serial.print("Connected with IP:");
  Serial.println(WiFi.localIP());
  Serial.println();
  }

float read_data(){
  float val;
  val = analogRead(A0);
  val = (1-(val/1024.0))*100;
  return val;
  } 


String pumpswitch(float reading,int precipitation){
String swtch;
if (precipitation < 50){
    if (reading < 30){
      swtch = "ON";
      digitalWrite(D3,HIGH);
      }
     else{
      swtch = "OFF";}
    }
  else{
    swtch="OFF";}
    delay(2000);
    digitalWrite(D3,LOW);
return swtch;
  }
  
