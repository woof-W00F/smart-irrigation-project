
void setup() {
  pinMode(D0,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  //int pinread = digitalRead(1);
  //Serial.println(pinread);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(D0,LOW);
  delay(1000);
  digitalWrite(D0,HIGH);
  //delay(1000);
  digitalWrite(LED_BUILTIN,LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(1000);
}
