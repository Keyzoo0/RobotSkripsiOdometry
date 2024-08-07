
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Arduino.h>
#include <ESP32Encoder.h>
#include <Wire.h>
#include <EEPROM.h>
#define BNO055_SAMPLERATE_DELAY_MS (100)


const int slaveAddress = 0;
// Check I2C device address and correct line below (by default address is 0x29 or 0x28)
//                                   id, address
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
int curr , prev = 0;
float initialOrientationY = 0.0;
bool isOrientationYSet = false;


float r_wheel = 0.03; // 3cm = 0.03 meter

float scale[3] = {0.002620195 , 0.002498034}; // 0.254045307
// float scale[3] = {1 , 1 , 1}; // 0.0123020145
float ts = 0.1;
float xpos = 0, ypos = 0, th = 0;
float xdot = 0, ydot = 0, thdot = 0;

float atanVal;


float d2r(int degree){
  float radians = degree * 0.0174533;
  return radians;
}

// Define encoder instances
ESP32Encoder encoder1;
ESP32Encoder encoder2;
ESP32Encoder encoder3;
ESP32Encoder encoder4;

// Define the pins connected to the encoders
#define ENCODER1_PIN_A 12
#define ENCODER1_PIN_B 13
#define ENCODER2_PIN_A 19
#define ENCODER2_PIN_B 18
#define ENCODER3_PIN_A 33
#define ENCODER3_PIN_B 32
#define ENCODER4_PIN_A 26
#define ENCODER4_PIN_B 27

#define ENCODERVAL 452

// Variables to store RPM calculations for each encoder
volatile long lastCount1 = 0;
volatile long currentCount1 = 0;
volatile float rpm1 = 0.0;
volatile unsigned long lastTime1 = 0;

volatile long lastCount2 = 0;
volatile long currentCount2 = 0;
volatile float rpm2 = 0.0;
volatile unsigned long lastTime2 = 0;

volatile long lastCount3 = 0;
volatile long currentCount3 = 0;
volatile float rpm3 = 0.0;
volatile unsigned long lastTime3 = 0;

volatile long lastCount4 = 0;
volatile long currentCount4 = 0;
volatile float rpm4 = 0.0;
volatile unsigned long lastTime4 = 0;

// Declare the timer variable
hw_timer_t * timer = NULL;
