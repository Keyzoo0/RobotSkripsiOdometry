
void setup_wire() {
  Wire.begin(slaveAddress);     // Memulai I2C sebagai slave dengan alamat 8
  Wire.onReceive(receiveEvent); // Handler untuk menerima data dari master
}

void print_pos() {
  // Menampilkan nilai yang diterima pada serial monitor
  Serial.print("xpos: ");
  Serial.print(xpos);
  Serial.print(", ypos: ");
  Serial.print(ypos);
  Serial.print(", th: ");
  Serial.println(th);
  
}

// Fungsi untuk menerima data dari master
void receiveEvent(int bytes) {
  if (bytes == sizeof(float) * 3) {
    Wire.readBytes((char*)&xpos, sizeof(xpos));
    Wire.readBytes((char*)&ypos, sizeof(ypos));
    Wire.readBytes((char*)&th, sizeof(th));
    }
}

void calImu(){
  if(dataReceive.button2State == 1){
    th_cal = th;
  }
  if(dataReceive.button1State == 1){
    xpos_cal = xdot;
    
  }
  if(dataReceive.button3State == 1){
    ypos_cal = ydot;
   
  }
}