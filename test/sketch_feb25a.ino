#include<ESP8266WiFi.h>
#include<Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define APIKEY "AIzaSyBitGLWajCNnwkoeKWx_4Q_pS3hdSk1mNc"
#define DATABASEURL "https://ezcrop-7c579-default-rtdb.asia-southeast1.firebasedatabase.app"

float reading;
const char *ssid = "oviv 181";
const char *passwd = "doggypup";
//const char *apikey= "AlzaSyBitGLWajCNnwkoeKWx_4Q_pS3hdSk1mNc";
//const char *databaseurl = "https://ezcrop-7c579-default-rtdb.asia-southeast1.firebasedatabase.app";

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
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    // Write an Int number on the database path test/int
    reading = read_data();
    Serial.print("SENSOR READING : ");
    Serial.println(reading);
    if (Firebase.RTDB.setInt(&fbdo, "sensor_data/float", reading)){
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
  val = (val/1024.0)*100;
  return val;
  }
