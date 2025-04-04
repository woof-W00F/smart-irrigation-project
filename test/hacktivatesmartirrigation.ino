
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "oviv 181";
char *passwd = "doggypup";

//mqtt broker variables
const char *mqtt_broker = "I";
const char *mqtt_topic = "emqx/ezcrop";    
const char *mqtt_username = "ezcrop";  
const char *mqtt_password = "12345";  
const int mqtt_port = 8083;

WiFiClient espclient;
PubSubClient mqtt_client(espclient);

void setup() {
  Serial.begin(9600);
  pinMode(A0,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  
  //connecting wifi
  WiFi.begin(ssid,passwd);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  connectwifi();
  //mqtt_client.setServer(mqtt_broker,mqtt_port);
  //mqtt_client.setCallback(mqttCallback);
  //connectToMQTTBroker();
 
}


void loop() {
  Serial.println(read_data());
  delay(500);
   

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

float read_data(){
  float val;
  val = analogRead(A0);
  val = 1-(val)/1024;
  return val*100;
  }

void connectToMQTTBroker() {
    while (!mqtt_client.connected()) {
       
         String client_id = "emqx_cloud580e30";
        //Serial.printf("Connecting to MQTT Broker as %s.....\n", client_id.c_str());
        if (mqtt_client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("Connected to MQTT broker");
            //mqtt_client.subscribe(mqtt_topic);
            // Publish message upon successful connection
            mqtt_client.publish(mqtt_topic, "Hi EMQX I'm ESP8266 ^^");
        } else {
            Serial.print("Failed to connect to MQTT broker, rc=");
           Serial.print(mqtt_client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void mqttCallback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message received on topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (unsigned int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
}
  
