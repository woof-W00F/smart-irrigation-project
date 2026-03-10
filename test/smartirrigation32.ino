
float reading;
int precipitation;
String swtch;

//Pin setup
int soil_sensor = 26;
int water_pump = 32;

void setup(){
  Serial.begin(9600);
  pinMode(soil_sensor,INPUT);
  pinMode(water_pump,OUTPUT);
}

void loop(){
  reading = read_data();
  Serial.print("Sensor readings: ");
  Serial.println(reading);
  swtch = pumpswtch(reading);
  Serial.print("Pump Switch : ");
  Serial.println(swtch);

  //Logic to turn pump on or off
  swtch = pumpswtch(reading);
  delay(1000);
  
  }

float read_data(){
  float val;
  val = analogRead(soil_sensor);
  val = (1-(val/4095))*100;
  return val;
 } 

String pumpswtch(float reading){
  String swtch;
  if (reading < 30){
    swtch = "ON";
    digitalWrite(water_pump,LOW);
    }
  else{
    swtch="OFF";}
    digitalWrite(water_pump,HIGH);
    delay(1000);
  return swtch;
  }
