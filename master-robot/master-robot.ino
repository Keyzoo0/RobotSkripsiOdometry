#include "variable.h"

void setup() {
  Serial.begin(115200);
  setup_motor();
  setup_wire();
  setupController();
 }

// + x=maju; - x=mundur; + y=kanan; - y=kiri; + teta=; - teta= putar kiri

void loop() {
  if(dataReceive.button3State){
  printForward();
  }

  // print_pos();
  calImu();
  kinMotor(dataReceive.x, dataReceive.y*-1 , dataReceive.teta);
  sendPosition();
  delay(1);
}
