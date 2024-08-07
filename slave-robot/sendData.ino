void sendDataToMaster(){
 Wire.beginTransmission(slaveAddress);
  
  // Mengirimkan data float sebagai byte array
  Wire.write((byte*)&xpos, sizeof(xpos));
  Wire.write((byte*)&ypos, sizeof(ypos));
  Wire.write((byte*)&thdot, sizeof(thdot));
  
  Wire.endTransmission();
}

