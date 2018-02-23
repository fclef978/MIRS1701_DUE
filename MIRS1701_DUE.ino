#include "define.h"
/*
RM:1;CU:1;
RM:2;RS:50;RD:100;CU:1;
RasPi:Ready;RM:10;BA:1;BB:0;CU:1; 
RasPi:Ready;RM:10;BA:1;BB:0;CU:1;RM:4;VL:20;VR:20;CU:1;
RasPi:Ready;RM:10;BA:1;BB:0;CU:1;RM:4;VL:-20;VR:-20;CU:1;
RasPi:Ready;RM:10;BA:1;BB:0;CU:1;RM:5;TS:30;TA:45;TR:10;TD:1;CU:1;
*/

void setup() {
  // put your setup code here, to run once:
  ioSetLED(1);
  ioOpen();
  encoderOpen();
  motorOpen();
  //ioSetBt(1, 0);
  //motorSet(25, 25); testEncoder();
  //velCtrlSet(10, 10); testVelCtrl();
  raspiOpen();
  queOpen();
  //test_encoder();
}

int num = 0;

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long int start = micros();
  ioBlinkLed(10);
  slave();
  if (num++ == 10) {
    num = 0;
    comm();
  }
  delayMicroseconds((T_CTRL - 2) * 1000);
}


