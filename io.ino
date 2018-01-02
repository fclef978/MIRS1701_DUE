void ioOpen() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_CTRL_A, INPUT_PULLUP);
  pinMode(PIN_CTRL_B, INPUT_PULLUP);
  pinMode(PIN_PIC, INPUT);
  pinMode(PIN_BTSW_A, OUTPUT);
  pinMode(PIN_BTSW_B, OUTPUT);
  pinMode(PIN_BTV_A, INPUT);
  pinMode(PIN_BTV_B, INPUT);
  pinMode(PIN_JS_X, INPUT);
  pinMode(PIN_JS_Y, INPUT);
  pinMode(PIN_SLVR, INPUT);
  
  digitalWrite(PIN_LED, LOW);
  digitalWrite(PIN_BTSW_A, LOW);
  digitalWrite(PIN_BTSW_B, LOW);
}

void ioSetLed(int val) {
  digitalWrite(PIN_LED, val);
}

void ioSetBt(int a, int b) {
  if (a == 1 && b == 1) {
    return;
  }
  digitalWrite(PIN_BTSW_A, a);
  digitalWrite(PIN_BTSW_B, b);
}

int ioGetLed() {
  return digitalRead(PIN_LED);
}

int ioGetCap() {
  return digitalRead(PIN_PIC);
}

int ioGetCtrlBtn(char ch) {
  switch (ch) {
    case 'a':
      return digitalRead(PIN_CTRL_A);
      break;
    case 'b':
      return digitalRead(PIN_CTRL_B);
      break;
    default:
      break;
  }
}

double ioGetBatt(char ch) {
  switch (ch) {
    case 'a':
      return analogRead(PIN_BTV_A) * 3.3 / 1024.0 / V_RATIO;
      break;
    case 'b':
      return analogRead(PIN_BTV_A) * 3.3 / 1024.0 / V_RATIO;
      break;
    default:
      break;
  }
}

int ioGetJs(char ch) {
  switch (ch) {
    case 'x':
      return analogRead(PIN_JS_X) - 512;
      break;
    case 'y':
      return analogRead(PIN_JS_Y) - 512;
      break;
    default:
      break;
  }
}

int ioGetVR() {
  analogRead(PIN_SLVR) - 512;
}

