float val;
void setup() {
  Serial.begin(9600);
  pinMode(D0,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(D0);
  Serial.println(val); 
  delay(1000);


}
