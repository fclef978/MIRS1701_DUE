void ioOpen() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_SW, INPUT);
  pinMode(PIN_BATT, INPUT);
  
  digitalWrite(PIN_LED, LOW);
  digitalWrite(PIN_SW, HIGH);
  digitalWrite(PIN_BATT, LOW);
}

void ioSetLed(int val) {
  digitalWrite(PIN_LED, val);
}

int ioGetLed() {
  return digitalRead(PIN_LED);
}

int ioGet_sw() {
  return digitalRead(PIN_SW);
}

double ioGetBatt() {
  return analogRead(PIN_BATT) * 5.0 / 1024.0 / V_RATIO;
}
