void setupIMU() {
  Wire.begin();

  while (!Serial) delay(10);  // wait for serial port to open!
  if (!bno.begin()) {
    while (1)
      ;
  }

  bno.setExtCrystalUse(true);
}


void readIMU() {
  curr = millis();
  if (BNO055_SAMPLERATE_DELAY_MS < (curr - prev)) {
    prev = curr;
    sensors_event_t event;
    bno.getEvent(&event);

    // Set the initial orientation.y value the first time the function runs
    if (!isOrientationYSet) {
      initialOrientationY = event.orientation.y;
      isOrientationYSet = true;
    }


    // Adjust the orientation.x value
    thdot = event.orientation.x - initialOrientationY;
    if (thdot > 180) thdot = thdot - 360;
    else if (thdot < -180) thdot = thdot + 360;

    }
}

