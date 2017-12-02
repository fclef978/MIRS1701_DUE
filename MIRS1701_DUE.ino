#include <Scheduler.h>
#include "define.h"
#include <Reset.h>
// RasPi:Ready;RM:2;RS:50;RD:100;CU:1;

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
  raspiSend("battA", String(num++));
  raspiSend("battB", String(num++));
  raspiSend("jsX", String(num++));
  raspiSend("jsY", String(num++));
  delay(1);
}

