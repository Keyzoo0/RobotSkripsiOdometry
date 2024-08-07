
void IRAM_ATTR calculateRPMs() {
  unsigned long currentTime = millis();
  float timeDiff;

  // Calculate RPM for encoder 1
  timeDiff = (currentTime - lastTime1) / 60000.0;
  currentCount1 = encoder1.getCount();
  long pulses1 = currentCount1 - lastCount1;
  rpm1 = (pulses1 / timeDiff) / ENCODERVAL;
  lastCount1 = currentCount1;
  lastTime1 = currentTime;

  // Calculate RPM for encoder 2
  timeDiff = (currentTime - lastTime2) / 60000.0;
  currentCount2 = encoder2.getCount();
  long pulses2 = currentCount2 - lastCount2;
  rpm2 = (pulses2 / timeDiff) / ENCODERVAL;
  lastCount2 = currentCount2;
  lastTime2 = currentTime;

  // Calculate RPM for encoder 3
  timeDiff = (currentTime - lastTime3) / 60000.0;
  currentCount3 = encoder3.getCount();
  long pulses3 = currentCount3 - lastCount3;
  rpm3 = (pulses3 / timeDiff) / ENCODERVAL;
  lastCount3 = currentCount3;
  lastTime3 = currentTime;

  // Calculate RPM for encoder 4
  timeDiff = (currentTime - lastTime4) / 60000.0;
  currentCount4 = encoder4.getCount();
  long pulses4 = currentCount4 - lastCount4;
  rpm4 = (pulses4 / timeDiff) / ENCODERVAL;
  lastCount4 = currentCount4;
  lastTime4 = currentTime;
}


void setupEncoder(){

  // Initialize encoders
  pinMode(ENCODER1_PIN_A, INPUT_PULLUP);
  pinMode(ENCODER1_PIN_B, INPUT_PULLUP);
  encoder1.attachFullQuad(ENCODER1_PIN_A, ENCODER1_PIN_B);

  pinMode(ENCODER2_PIN_A, INPUT_PULLUP);
  pinMode(ENCODER2_PIN_B, INPUT_PULLUP);
  encoder2.attachFullQuad(ENCODER2_PIN_A, ENCODER2_PIN_B);

  pinMode(ENCODER3_PIN_A, INPUT_PULLUP);
  pinMode(ENCODER3_PIN_B, INPUT_PULLUP);
  encoder3.attachFullQuad(ENCODER3_PIN_A, ENCODER3_PIN_B);

  pinMode(ENCODER4_PIN_A, INPUT_PULLUP);
  pinMode(ENCODER4_PIN_B, INPUT_PULLUP);
  encoder4.attachFullQuad(ENCODER4_PIN_A, ENCODER4_PIN_B);

  // Initialize lastTime for each encoder
  lastTime1 = millis();
  lastTime2 = millis();
  lastTime3 = millis();
  lastTime4 = millis();

  // Setup a timer to call calculateRPM function every second
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &calculateRPMs, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);

}

