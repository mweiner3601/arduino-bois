const int pinHigh = 12;
const int pinLow  = 13;
const int analogPin = A1;

const float R_known = 10000.0; // 10k ohm

void setup() {
  Serial.begin(115200);

  pinMode(pinHigh, OUTPUT);
  pinMode(pinLow, OUTPUT);

  digitalWrite(pinHigh, HIGH); // 5V
  digitalWrite(pinLow, LOW);   // GND
}

void loop() {
  int adc = analogRead(analogPin); // 0–4095 on UNO R4

  float Vcc = 5.0;
  float Vout = (adc / 1023.0) * Vcc;

  float R_unknown = R_known * Vout / (Vcc - Vout);

  Serial.print("ADC: ");
  Serial.print(adc);
  Serial.print("  Voltage: ");
  Serial.print(Vout);
  Serial.print(" V  Resistance: ");
  Serial.print(R_unknown);
  Serial.println(" ohms");

  delay(500);
}
