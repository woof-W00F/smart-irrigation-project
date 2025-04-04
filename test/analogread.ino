float val;
void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);
}

void loop() {
  val = analogRead(A0);
  val = 1-(val/1024.0);
  val = val*100;
  delay(200);
  Serial.printf("%f%%\n",val);  

}
