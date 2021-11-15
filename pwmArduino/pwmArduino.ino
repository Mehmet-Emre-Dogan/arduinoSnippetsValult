void setup(){
  pinMode(A5, INPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}
void loop(){
  int value = analogRead(A5)/4;
  /*
  if (value < 10)
    value = 0;
  if (value > 1015)
    value = 1023;*/
    
  analogWrite(3, value);
  Serial.println(value);
}
