#include <Scheduler.h>
#include "define.h"
// RasPi:Ready;RM:2;RS:50;RD:100;CU:1;

void setup() {
  // put your setup code here, to run once:
  raspiOpen();
  ioOpen();
  encoderOpen();
  motorOpen();
  queOpen();
  Scheduler.startLoop(loopCommunication);
}

void loop() {
  // put your main code here, to run repeatedly:
  slave();
  delay(T_CTRL);
}

void loopCommunication() {
  raspiReceive();
  delay(1);
}

