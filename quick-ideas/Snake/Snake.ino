#include <Arduino_LED_Matrix.h>

ArduinoLEDMatrix matrix;

// Matrix size
#define W 12
#define H 8

// Snake
int snakeX[W * H];
int snakeY[W * H];
int length = 3;

// Direction: 0=up,1=right,2=down,3=left
int dir = 1;

// Apple
int appleX = 5;
int appleY = 3;

// Frame toggle for "dim" snake
bool dimToggle = false;

void spawnApple() {
  appleX = random(W);
  appleY = random(H);
}

void setup() {
  Serial.begin(115200);
  matrix.begin();
  randomSeed(analogRead(A0));

  // Initial snake
  snakeX[0] = 5; snakeY[0] = 4;
  snakeX[1] = 4; snakeY[1] = 4;
  snakeX[2] = 3; snakeY[2] = 4;
}

void loop() {
  handleInput();
  updateGame();
  draw();
  delay(50);
}

// ---------------- INPUT ----------------
void handleInput() {
  while (Serial.available()) {
    char c = Serial.read();

    if (c == 27 && Serial.available() >= 2) {
      Serial.read(); // '['
      char dirChar = Serial.read();

      switch (dirChar) {
        case 'A': if (dir != 2) dir = 0; break;
        case 'C': if (dir != 3) dir = 1; break;
        case 'B': if (dir != 0) dir = 2; break;
        case 'D': if (dir != 1) dir = 3; break;
      }
    }
  }
}

// ---------------- GAME LOGIC ----------------
void updateGame() {
  int newX = snakeX[0];
  int newY = snakeY[0];

  if (dir == 0) newY--;
  if (dir == 1) newX++;
  if (dir == 2) newY++;
  if (dir == 3) newX--;

  // Wrap around edges
  if (newX < 0) newX = W - 1;
  if (newX >= W) newX = 0;
  if (newY < 0) newY = H - 1;
  if (newY >= H) newY = 0;

  // Move body
  for (int i = length; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  snakeX[0] = newX;
  snakeY[0] = newY;

  // Eat apple
  if (newX == appleX && newY == appleY) {
    length++;
    spawnApple();
  }
}

// ---------------- DRAW ----------------
void draw() {
  uint8_t frame[H][W] = {0};

  // Apple = full brightness (always on)
  frame[appleY][appleX] = 1;

  // Snake = fake half brightness (flicker)
  dimToggle = !dimToggle;

  for (int i = 0; i < length; i++) {
    if (dimToggle) {
      frame[snakeY[i]][snakeX[i]] = 1;
    }
  }

  matrix.renderBitmap(frame, H, W);
}