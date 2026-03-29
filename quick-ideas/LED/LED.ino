#include <Arduino_LED_Matrix.h>
ArduinoLEDMatrix matrix;

void setup() {
  matrix.begin();

  // LED stuff

  // 8 rows × 12 columns
  uint8_t frame[8][12] = {0};

  // Turn on one LED:
  // row 3, column 5
  frame[3][3] = 1;

  matrix.renderBitmap(frame, 8, 12);
}

void loop() {
  uint8_t frame[8][12] = {0};
  for (int k = 0; k <= 18; k++) {
    for (int i = 0; i <= 7; i++) {
      for (int j = 0; j <= 11; j++) {
        if (i+j==k) {
          frame[i][j] = 1;
        }
        if (i+j==k-1) {
          frame[i][j] = 0;
        }
      }
    }
  matrix.renderBitmap(frame, 8, 12);
  delay(100);
  } 
}
// arduino-cli compile --fqbn arduino:renesas_uno:unor4wifi .
// arduino-cli upload  --fqbn arduino:renesas_uno:unor4wifi -p /dev/ttyACM0 .
