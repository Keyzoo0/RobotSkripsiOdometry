#include <esp_now.h>
#include <WiFi.h>
#include <U8g2lib.h>
#include <math.h>


// Inisialisasi OLED
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


// Ukuran grid dan ukuran sel grid
const int gridSize = 5;
const int cellSize = 12; // 12
const int xOffset = 10; // Offset untuk menggeser grid ke kanan



//===============================
uint8_t broadcastAddress[] = { 0x94, 0xB5, 0x55, 0x2C, 0x54, 0xDC };

float xpos,
      ypos,
      th;

float xdot,
      ydot;
      
// Struktur variabel untuk mengirimkan data
typedef struct struct_message_send {
  float x;
  float y;
  float teta;
  bool button1State = false;
  bool button2State = false;
  bool button3State = false;
  bool buttonL3State = false;
  bool buttonR3State = false;
} struct_message_send;

struct_message_send dataSend;

typedef struct struct_message_receive {
  float xpos;
  float ypos;
  float th;
} struct_message_receive;

struct_message_receive dataReceive;

esp_now_peer_info_t peerInfo;



// Alamat MAC dari ESP32 Robot

const int button1Pin = 19;
const int button2Pin = 26;
const int button3Pin = 23;
const int button4Pin = 25;
const int buttonL3 = 13;
const int buttonR3 = 14;

const int lxPin = 33;
const int lyPin = 34;
const int rxPin = 35;
const int ryPin = 32;

float lxValue;
float lyValue;
float rxValue;
float ryValue;

float atanVal;
int inv_yR;
