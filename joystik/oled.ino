const int MAX_POINTS = 1000; // Sesuaikan dengan kebutuhan
int pathPoints[MAX_POINTS][2];
int pathIndex = 0;
bool isDrawingPath = true;

void setupMap() {
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB08_tr); // Ganti dengan font yang tersedia dalam library

  // Inisialisasi titik awal
  xdot = ypos * -1;
  ydot = xpos * -1;
}

float prevXdot, prevYdot;
int x,y ;
void drawMap() {
  xdot = ypos * -1;
  ydot = xpos * -1;

  u8g2.clearBuffer();
   if (isDrawingPath) {
    // Cek apakah xdot atau ydot berubah cukup besar untuk menambahkan titik baru
    if (abs(xdot - prevXdot) >= 0.01 || abs(ydot - prevYdot) >= 0.01) {
      pathPoints[pathIndex][0] = x;
      pathPoints[pathIndex][1] = y;
      pathIndex++;

      // Cek apakah sudah mencapai batas maksimum jumlah titik
      if (pathIndex >= MAX_POINTS) {
        pathIndex = 0; // Mulai ulang dari awal
      }
    }

    // Gambar semua titik pada jalur
    for (int i = 0; i < pathIndex; i++) {
      u8g2.drawPixel(pathPoints[i][0], pathPoints[i][1]);
    }

    prevXdot = xdot;
    prevYdot = ydot;
  }

  // Gambar grid dengan offset
  for (int i = 0; i <= gridSize; i++) {
    u8g2.drawLine(xOffset + 0, i * cellSize, xOffset + gridSize * cellSize, i * cellSize);
    u8g2.drawLine(xOffset + i * cellSize, 0, xOffset + i * cellSize, gridSize * cellSize);
  }

  // Gambar robot dengan offset
  x = xOffset + (xdot + 2.5) * cellSize;
  y = (ydot + 2.5) * cellSize;
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
  u8g2.print(ydot*-1, 3);

  u8g2.setCursor(gridSize * cellSize + xOffset + 5, 50);
  u8g2.print("th:");
  u8g2.setCursor(gridSize * cellSize + xOffset + 5, 60);
  u8g2.print(th, 2);

  // Tampilkan buffer
  u8g2.sendBuffer();
  if (digitalRead(25) == LOW) {
    isDrawingPath = false;
    pathIndex = 0; // Reset indeks jalur
  }else{
    isDrawingPath = true;
    
  }
}
