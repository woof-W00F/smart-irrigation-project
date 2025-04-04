int reading;
void setup() {
  Serial.begin(9600);
  pinMode(5,OUTPUT);
  pinMode(A0,INPUT);
}

void loop() {
reading = read_data();
Serial.println(reading);

if (reading > 10){
  digitalWrite(5,HIGH);
  delay(2000);
  }
  
  digitalWrite(5,LOW);
  delay(2000);

/*
Serial.println("OFF");
digitalWrite(5,HIGH);
delay(2000);
Serial.println("ON");
digitalWrite(5,LOW);
delay(2000);
*/





}

float read_data(){
  float val;
  val = analogRead(A0);
  val = (val/1024)*100;
  return val;
  
  }
