#include <Scheduler.h>
#include "define.h"
#include <Reset.h>
// RasPi:Ready;RM:2;RS:50;RD:100;CU:1;
// RasPi:Ready;RM:4;VL:60;VR:20;CU:1;

void setup() {
  // put your setup code here, to run once:
  ioOpen();
  encoderOpen();
  motorOpen();
  raspiOpen();
  queOpen();
  Scheduler.startLoop(loopCommunication);
}

int num = 0;

void loop() {
  // put your main code here, to run repeatedly:
  slave();
  delay(T_CTRL);
}

void loopCommunication() {
  while (raspiReceive()) {}
  /*
  raspiSend("battA", String(0));
  raspiSend("battB", String(0));
  */
  delay(10);
}

