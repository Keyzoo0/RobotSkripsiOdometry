#include "variabel.h"
void setup() {
  Serial.begin(115200);
  setupForward();
  setupMap();
  setupController();
}

void loop() {
  readController();
  if(dataSend.button3State){
  printForward();
  }
  computeForward();
  sendForward();
  readPosition();
  drawMap();
  // drawOled();
  delay(1);
}
