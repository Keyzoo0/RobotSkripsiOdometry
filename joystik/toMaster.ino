// Callback ketika data terkirim
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&dataReceive, incomingData, sizeof(dataReceive));
  // Serial.printf("x:%4f|y:%4f|z:%4f\n",dataReceive.xpos,dataReceive.ypos,dataReceive.th);

}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
}

void setupForward(){
  WiFi.mode(WIFI_STA);
   // Inisialisasi ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Daftarkan callback
  esp_now_register_recv_cb(OnDataRecv);
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Tambahkan peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void sendForward(){
  dataSend.x = lxValue;
  dataSend.y = lyValue;
  dataSend.teta = atanVal;
  // Kirim data float ke ESP32 Robot
  esp_now_send(broadcastAddress, (uint8_t *)&dataSend, sizeof(dataSend));

}
  

void printForward(){
  Serial.printf("dataSend : ");
  Serial.printf(" x : %f",dataSend.x);
  Serial.printf(" y : %f",dataSend.y);
  Serial.printf(" z : %f \n",dataSend.teta);
  
}
void readPosition(){
  xpos = dataReceive.xpos ;
  ypos = dataReceive.ypos ;
  th = dataReceive.th ;
 }