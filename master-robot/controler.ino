void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&dataReceive, incomingData, sizeof(dataReceive));
  // Serial.printf("x:%4f y:%4f teta:%4f b1:%d b2:%d b3:%d L3:%d R3:%d \n", dataReceive.x, dataReceive.y, dataReceive.teta, dataReceive.button1State, dataReceive.button2State, dataReceive.button3State, dataReceive.buttonL3State, dataReceive.buttonR3State);
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
}

void setupController(){
   // Inisialisasi WiFi
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
  }
}

void printForward(){
  Serial.printf("dataReceive : ");
  Serial.printf(" x : %f",dataReceive.x);
  Serial.printf(" y : %f",dataReceive.y);
  Serial.printf(" z : %f \n",dataReceive.teta);
  
}

void sendPosition(){
  xdot = xdot + xpos*0.01;
  ydot = ydot + ypos*0.01;
  dataSend.xpos = xdot - xpos_cal;
  dataSend.ypos = ydot - ypos_cal;
  dataSend.th = th - th_cal;
  // Serial.printf("x:%4f|y:%4f|z:%4f\n",dataSend.xpos,dataSend.ypos,dataSend.th);
  
  // Kirim data float ke ESP32 Robot
  esp_now_send(broadcastAddress, (uint8_t *)&dataSend, sizeof(dataSend));

}