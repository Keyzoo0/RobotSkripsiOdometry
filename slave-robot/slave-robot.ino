#include "variable.h"
void setup() {
  Serial.begin(115200);  
  Wire.begin();
  setupEncoder();
  setupIMU();
}

void loop() {
  readIMU();
  computePosition();
  sendDataToMaster();
}



void computePosition(){ // forward kinematic
    xdot = 0, ydot = 0;
    th = d2r(thdot);
   
xdot = r_wheel * (
    (cos(th) * (
        cos(d2r(45.)) * rpm1 +
        cos(d2r(135.)) * rpm4 +
        cos(d2r(-135.)) * rpm3 +
        cos(d2r(-45.)) * rpm2
    )) +
    (sin(th) * (
        sin(d2r(45)) * rpm1 +
        sin(d2r(135)) * rpm4 +
        sin(d2r(-135)) * rpm3 +
        sin(d2r(-45)) * rpm2
    ))
);

ydot = r_wheel * (
    (-sin(th) * (
        cos(d2r(45.)) * rpm1 +
        cos(d2r(135.)) * rpm4 +
        cos(d2r(-135.)) * rpm3 +
        cos(d2r(-45.)) * rpm2
    )) +
    (cos(th) * (
        sin(d2r(45)) * rpm1 +
        sin(d2r(135)) * rpm4 +
        sin(d2r(-135)) * rpm3 +
        sin(d2r(-45)) * rpm2
    ))
);

// odometry scale
  xdot = xdot * scale[0];
  ydot = ydot * scale[1];
  // thdot = thdot * scale[2];
  // update position
  xpos = xpos + xdot*ts;
  ypos = ypos + ydot*ts;
  // th = th + thdot*ts;
  // Serial.printf("%4f | %4f | %4f | %4f \n " , rpm1 , rpm2 , rpm3 , rpm4);
  // Serial.print(xpos);Serial.print("\t");Serial.print(ypos);Serial.print("\t");Serial.println(thdot);
  // Serial.print(xdot);Serial.print("\t");Serial.print(ydot);Serial.print("\t");Serial.println(th);
  //Serial.print(encoderValue[0]);Serial.print("\t");Serial.print(encoderValue[1]);Serial.print("\t");Serial.print(encoderValue[2]);Serial.print("\t");Serial.println(encoderValue[3]);
}



