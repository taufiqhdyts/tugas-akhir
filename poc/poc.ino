const int ANALOG_PIN = 4;
const int LED_PIN = 2;
const int BUZZER_PIN = 25;

const float KNOWN_RESISTOR = 90.0; // ohm
const float VCC_ESP32 = 3.1; // volt
const int ADC_MAX_VALUE = 4095; // 12 bit

void setup() {
  Serial.begin(115200);
  analogSetAttenuation(ADC_11db); // atenuasi 11dB
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int adcReading = analogRead(ANALOG_PIN); // 12 bit

  float voltageMeasured = (float)adcReading / ADC_MAX_VALUE * VCC_ESP32;
  
  float unknownResistor = 0.0;
  if (VCC_ESP32 - voltageMeasured > 0.001) {
    unknownResistor = (voltageMeasured * KNOWN_RESISTOR) / (VCC_ESP32 - voltageMeasured);
  } else {
    unknownResistor = 999999999.0; // open
  }

  if (unknownResistor < 1050.0) {
    tone(BUZZER_PIN, 1000);
    digitalWrite(LED_PIN, 1);
  } else {
    noTone(BUZZER_PIN);
    digitalWrite(LED_PIN, 0);
  }

  // print
  Serial.print("adc: ");
  Serial.print(adcReading);
  Serial.print(" of 4095\t");

  Serial.print("volt: ");
  Serial.print(voltageMeasured, 3);
  Serial.print(" V\t");

  Serial.print("res: ");
  Serial.print(unknownResistor, 2);
  Serial.println(" ohm\t");

  delay(200);
}
