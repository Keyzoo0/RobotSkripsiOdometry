
void setupMap() {
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB08_tr); // Ganti dengan font yang tersedia dalam library
  xdot = ypos*-1;
  ydot = xpos*-1;
  pathX[0] = xdot;
  pathY[0] = ydot;
 
}


void drawMap() {
  xdot = ypos * -1;
  ydot = xpos * -1;

  // Simpan posisi baru ke dalam array jalur
  if (pathLength < maxPathLength) {
    pathX[pathLength] = xdot;
    pathY[pathLength] = ydot;
    pathLength++;
  }

  u8g2.clearBuffer();

  // Gambar grid dengan offset
  for (int i = 0; i <= gridSize; i++) {
    u8g2.drawLine(xOffset + 0, i * cellSize, xOffset + gridSize * cellSize, i * cellSize);
    u8g2.drawLine(xOffset + i * cellSize, 0, xOffset + i * cellSize, gridSize * cellSize);
  }

  // Gambar jalur yang telah dilalui dengan offset
  for (int i = 1; i < pathLength; i++) {
    int x1 = xOffset + (pathX[i-1] + 2.5) * cellSize;
    int y1 = (pathY[i-1] + 2.5) * cellSize;
    int x2 = xOffset + (pathX[i] + 2.5) * cellSize;
    int y2 = (pathY[i] + 2.5) * cellSize;
    u8g2.drawLine(x1, y1, x2, y2);
  }

  // Gambar garis dari posisi terakhir ke posisi baru
  if (pathLength > 1) {
    int lastX = xOffset + (pathX[pathLength-2] + 2.5) * cellSize;
    int lastY = (pathY[pathLength-2] + 2.5) * cellSize;
    int newX = xOffset + (xdot + 2.5) * cellSize;
    int newY = (ydot + 2.5) * cellSize;
    u8g2.drawLine(lastX, lastY, newX, newY);
  }

  // Gambar robot dengan offset
  int x = xOffset + (xdot + 2.5) * cellSize;
  int y = (ydot + 2.5) * cellSize;
  u8g2.drawPixel(x, y);

  // Gambar segitiga untuk arah dengan offset
  float angle = radians(th + 90.0);
  int x1 = x + 5 * cos(angle);
  int y1 = y + 5 * sin(angle);
  int x2 = x + 3 * cos(angle + PI / 4);
  int y2 = y + 3 * sin(angle + PI / 4);
  int x3 = x + 3 * cos(angle - PI / 4);
  int y3 = y + 3 * sin(angle - PI / 4);

  u8g2.drawLine(x, y, x1, y1);
  u8g2.drawLine(x, y, x2, y2);
  u8g2.drawLine(x, y, x3, y3);

  // Tampilkan variabel xdot, ydot, dan th di sebelah kanan grid
  u8g2.setCursor(gridSize * cellSize + xOffset + 5, 10);
  u8g2.print("xpos:");
  u8g2.setCursor(gridSize * cellSize + xOffset + 5, 20);
  u8g2.print(xdot, 3);

  u8g2.setCursor(gridSize * cellSize + xOffset + 5, 30);
  u8g2.print("ypos:");
  u8g2.setCursor(gridSize * cellSize + xOffset + 5, 40);
  u8g2.print(ydot, 3);

  u8g2.setCursor(gridSize * cellSize + xOffset + 5, 50);
  u8g2.print("th:");
  u8g2.setCursor(gridSize * cellSize + xOffset + 5, 60);
  u8g2.print(th, 2);

  // Tampilkan buffer
  u8g2.sendBuffer();
}
