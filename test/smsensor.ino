void setup() {
  Serial.begin(9600);
  pinMode(16,INPUT);
  

}

void loop() {
  int pinread = digitalRead(16);
  Serial.print("GPIO16 read : ");
  Serial.println(pinread);
  delay(1000);

}
