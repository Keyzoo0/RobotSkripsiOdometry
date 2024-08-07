
void setup_motor() {
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(EN3, OUTPUT);
  pinMode(EN4, OUTPUT);

  ledcSetup(PWM_M1A, freq, res);  //channel, freq, res
  ledcAttachPin(M1A, PWM_M1A);    //pin, channel

  ledcSetup(PWM_M1B, freq, res);
  ledcAttachPin(M1B, PWM_M1B);

  ledcSetup(PWM_M2A, freq, res);
  ledcAttachPin(M2A, PWM_M2A);

  ledcSetup(PWM_M2B, freq, res);
  ledcAttachPin(M2B, PWM_M2B);

  ledcSetup(PWM_M3A, freq, res);
  ledcAttachPin(M3A, PWM_M3A);

  ledcSetup(PWM_M3B, freq, res);
  ledcAttachPin(M3B, PWM_M3B);

  ledcSetup(PWM_M4A, freq, res);
  ledcAttachPin(M4A, PWM_M4A);

  ledcSetup(PWM_M4B, freq, res);
  ledcAttachPin(M4B, PWM_M4B);

  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, HIGH);
  digitalWrite(EN3, HIGH);
  digitalWrite(EN4, HIGH);
}

void kinMotor(int x, int y, int th) {
  int teta = LengthAlpha * d2r(th) * -1;
  m1 = lambda * (cos(d2r(45)) * x + sin(d2r(45)) * y + teta);
  m4 = lambda * (cos(d2r(135)) * x + sin(d2r(135)) * y + (teta*-1));
  m3 = lambda * (cos(d2r(225)) * x + sin(d2r(225)) * y + teta);
  m2 = lambda * (cos(d2r(315)) * x + sin(d2r(315)) * y + (teta*-1));

  // Serial.printf("  m1=%4d m2=%4d m3=%4d m4=%4d ", m1, m2, m3, m4);
  // Serial.println();

  // Serial.printf("th = %5d \n" , LengthAlpha*d2r(th) );
  if (abs(m1) < 50) {
    m1 = 0;
  }

  if (abs(m2) < 50) {
    m2 = 0;
  }

  if (abs(m3) < 50) {
    m3 = 0;
  }

  if (abs(m4) < 50) {
    m4 = 0;
  }
  set_pwm(M1, m1);
  set_pwm(M2, m2);
  set_pwm(M3, m3);
  set_pwm(M4, m4);
}

void set_pwm(byte MTR, int val_pwm) {
  switch (MTR) {
    case M1:
      if (val_pwm > 0) {
        digitalWrite(EN1, HIGH);
        ledcWrite(PWM_M1A, val_pwm);
        ledcWrite(PWM_M1B, 0);
      } else if (val_pwm < 0) {
        digitalWrite(EN1, HIGH);
        ledcWrite(PWM_M1B, abs(val_pwm));
        ledcWrite(PWM_M1A, 0);
      } else {
        digitalWrite(EN1, LOW);
      }
      break;

    case M2:
      if (val_pwm > 0) {
        digitalWrite(EN2, HIGH);
        ledcWrite(PWM_M2A, val_pwm);
        ledcWrite(PWM_M2B, 0);
      } else if (val_pwm < 0) {
        digitalWrite(EN2, HIGH);
        ledcWrite(PWM_M2B, abs(val_pwm));
        ledcWrite(PWM_M2A, 0);
      } else {
        digitalWrite(EN2, LOW);
      }
      break;

    case M3:
      if (val_pwm > 0) {
        digitalWrite(EN3, HIGH);
        ledcWrite(PWM_M3A, val_pwm);
        ledcWrite(PWM_M3B, 0);
      } else if (val_pwm < 0) {
        digitalWrite(EN3, HIGH);
        ledcWrite(PWM_M3B, abs(val_pwm));
        ledcWrite(PWM_M3A, 0);
      } else {
        digitalWrite(EN3, LOW);
      }

      break;

    case M4:
      if (val_pwm > 0) {
        digitalWrite(EN4, HIGH);
        ledcWrite(PWM_M4A, val_pwm);
        ledcWrite(PWM_M4B, 0);
      } else if (val_pwm < 0) {
        digitalWrite(EN4, HIGH);
        ledcWrite(PWM_M4B, abs(val_pwm));
        ledcWrite(PWM_M4A, 0);
      } else {
        digitalWrite(EN4, LOW);
      }
      break;
  }
}
