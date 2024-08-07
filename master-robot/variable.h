#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>


// Struktur variabel untuk menerima data
typedef struct struct_message_receive {
  float x;
  float y;
  float teta;
  bool button1State;
  bool button2State;
  bool button3State;
  bool buttonL3State;
  bool buttonR3State;
} struct_message_receive;

struct_message_receive dataReceive;

typedef struct struct_message_send {
  float xpos;
  float ypos;
  float th;
} struct_message_send;

struct_message_send dataSend;

esp_now_peer_info_t peerInfo;

// Alamat MAC dari ESP32 Master
uint8_t broadcastAddress[] = { 0xd8, 0xbc, 0x38, 0xfd, 0xdf, 0x08 };

#define res 10
#define freq 15000

int m1, m2, m3, m4;

#define M1 1
#define M2 2
#define M3 3
#define M4 4

//motor1
#define EN1 15
#define M1A 13
#define M1B 12
//motor2
#define EN2 19
#define M2A 5
#define M2B 18
//motor3
#define EN3 32
#define M3A 33
#define M3B 25
//motor4
#define EN4 26
#define M4A 14
#define M4B 27

#define PWM_M1A 1
#define PWM_M1B 2
#define PWM_M2A 3
#define PWM_M2B 4
#define PWM_M3A 5
#define PWM_M3B 6
#define PWM_M4A 7
#define PWM_M4B 8

#define lambda 5
#define d2r(x) x *(PI / 180)

#define LengthAlpha 45  // Ubah Disini untuk panjang dari sumbu roda ke tengah roda


const int slaveAddress = 0;
volatile float xpos = 0.0;
volatile float ypos = 0.0;
volatile float th = 0.0;

volatile float xpos_cal = 0.0;
volatile float ypos_cal = 0.0;
volatile float th_cal = 0.0;
