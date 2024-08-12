void setupController(){
   
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button4Pin, INPUT);

  pinMode(buttonL3, INPUT);
  pinMode(buttonR3, INPUT);

  pinMode(lxPin, INPUT_PULLUP);
  pinMode(lyPin, INPUT_PULLUP);
  pinMode(rxPin, INPUT);
  pinMode(ryPin, INPUT);

}

void readController(){
   lxValue = analogRead(lxPin);
  lyValue = analogRead(lyPin);
  rxValue = analogRead(rxPin);
  ryValue = analogRead(ryPin);

  dataSend.button1State = !digitalRead(button1Pin);
  dataSend.button2State = !digitalRead(button2Pin);
  dataSend.button3State = !digitalRead(button3Pin);
  dataSend.buttonL3State = !digitalRead(buttonL3);
  dataSend.buttonR3State = !digitalRead(buttonR3);

}

void computeForward(){

  lxValue = map(lxValue, 0, 4095, 128, -128);
  lyValue = map(lyValue, 0, 4095, 128, -128);
  rxValue = map(rxValue, 0, 4095, 128, -128);
  ryValue = map(ryValue, 0, 4095, 0, 128);
  if (abs(lxValue) < 30) lxValue = 0;
  if (abs(lyValue) < 30) lyValue = 0;
  if (abs(ryValue) < 30) ryValue = 0;
  if (abs(rxValue) < 30) rxValue = 0;

  atanVal = atan2(rxValue, ryValue);
  atanVal = (atanVal  * 360 / PI);

}