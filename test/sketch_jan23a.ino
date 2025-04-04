const unsigned int blinknumber=200;
const unsigned int blinkblank=500;

void setup() {   
  // initialize inbuilt LED pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  for (int i=1;i<=5;i++){
    for (int j=1;j<=i;j++){
      Serial.printf("i = %d ;j = %d\n",i,j);
      digitalWrite(LED_BUILTIN,LOW);
      delay(200);
      digitalWrite(LED_BUILTIN,HIGH);
      delay(200);
      }
      digitalWrite(LED_BUILTIN,HIGH);
      delay(1000);
  }
  Serial.println("Program ends");
}

void loop(){
//  digitalWrite(LED_BUILTIN,LOW); //it lights up the LED
//  delay(2000);
//  digitalWrite(LED_BUILTIN,HIGH);//it turns off the LED
//  delay(2000);
  }
