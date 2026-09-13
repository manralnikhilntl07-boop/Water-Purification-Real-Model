#define TDS_PIN 34
#define RELAY_PIN 26
#define VREF 3.3

unsigned long lastSwitch = 0;
bool pumpOn = true;
const unsigned long ON_TIME = 12000;  // 12 sec
const unsigned long OFF_TIME = 3000;  // 3 sec

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); 
  lastSwitch = millis();
}

void loop() {
  unsigned long now = millis();
  unsigned long elapsed = now - lastSwitch;

  if (pumpOn && elapsed >= ON_TIME) {
    digitalWrite(RELAY_PIN, HIGH); // OFF
    pumpOn = false;
    lastSwitch = now;
  } else if (!pumpOn && elapsed >= OFF_TIME) {
    digitalWrite(RELAY_PIN, LOW); // ON
    pumpOn = true;
    lastSwitch = now;
  }

  // TDS reading, unaffected by pump cycle
  long sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(TDS_PIN);
    delay(10);
  }
  int raw = sum / 10;
  float voltage = raw * (VREF / 4095.0);
  float tds = (133.42*voltage*voltage*voltage - 255.86*voltage*voltage + 857.39*voltage) * 0.5;
  Serial.println(tds);
}