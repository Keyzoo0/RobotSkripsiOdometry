TaskHandle_t Task1;
TaskHandle_t Task2;

void setupRTOS() {
  xTaskCreatePinnedToCore(Task1code,"Task1",8192,NULL,1,&Task1,0);                         

  xTaskCreatePinnedToCore(Task2code,"Task2",8192,NULL,1,&Task2,1);          

}

void Task1code( void * parameter ){
 
  for(;;){
    readController();
    computeForward();
    printAnalog();
    sendForward();
    vTaskDelay(2);
  } 
}

void Task2code( void * parameter ){
 
  for(;;){
    readPosition();
    drawMap();
  }
}

void printAnalog(){
  Serial.printf("%f %f\n", lxValue , lyValue);
}
