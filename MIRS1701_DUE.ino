#include <Scheduler.h>
#include "QList.h"

void setup() {
  // put your setup code here, to run once:
  raspiOpen();
  Scheduler.startLoop(loopCommunication);
}

QList<String> qStrA;
QList<String> qStrB;

void loop() {
  // put your main code here, to run repeatedly:
  slave();
  delay(2000);
}

void loopCommunication() {
  raspiReceive();
  delay(1000);
}

