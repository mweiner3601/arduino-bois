#include <Arduino_LED_Matrix.h>
ArduinoLEDMatrix matrix;

void setup() {

  // Synth stuff
  pinMode(8, OUTPUT);
}

void loop() {
  int value = analogRead(A0);
  int pwm = value/16;
  analogWrite(8, pwm);
  // digitalWrite(8, HIGH);
  // delayMicroseconds(20000);  // 1 kHz signal
  // digitalWrite(8, LOW);
  // delayMicroseconds(20000);
}

// arduino-cli compile --fqbn arduino:renesas_uno:unor4wifi .
// arduino-cli upload  --fqbn arduino:renesas_uno:unor4wifi -p /dev/ttyACM0 .
