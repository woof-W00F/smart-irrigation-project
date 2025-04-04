//static int val = 0;

void setup() {
  Serial.begin(9600);
  //static int val=0;

}

void loop() {
  static int val=0;
  Serial.println(val);
  delay(1000);
  val++;

}
