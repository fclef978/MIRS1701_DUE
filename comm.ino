void commSend() {
  run_state_t rs;
  double distL, distR, speed, distance;
  distanceGet(&distL, &distR);
  runCtrlGet(&rs, &speed, &distance);
  raspiSend("distL", String(distL));
  raspiSend("distR", String(distR));
  raspiSend("mode", String(rs));
  raspiSend("speed", String(speed));
  raspiSend("distance", String(distance));
  raspiSend("jsX", String(ioGetJs('x')));
  raspiSend("jsY", String(ioGetJs('y')));
  raspiSend("btA", String(ioGetBatt('a')));
  raspiSend("btB", String(ioGetBatt('b')));
  raspiSend("slvr", String(ioGetVR()));
  raspiSend("ctrlA", String(ioGetCtrlBtn('a')));
  raspiSend("ctrlB", String(ioGetCtrlBtn('b')));
  raspiSend("cap", String(ioGetCap()));
  //analogRead(PIN_BTV_B);
  //raspiSend("test", String(analogRead(PIN_BTV_B)));
  raspiSend("mirs", "1701");  //何故か必要
}

void comm() {
  int cmd[8];
  for (int i = 0; i < 8; i++) {
    cmd[i] = 0;
  }
  while (true) {
    if (raspiReceive()) {
      if (raspiIsUpdated()) {
        packCmd(cmd);
        /*
        for (int i = 0; i < 8; i++) {
          SerialUSB.print(cmd[i]);
          SerialUSB.print(" ");
        }
        SerialUSB.println("");
        */
        quePush(cmd);
      }
    }
    else {
      break;
    }
  }
  //commSend();
}

static void packCmd(int cmd[]) {
  switch (raspiGetValue("RM")) {
    case 0:
      break;
    case 1:
      cmd[0] = 1;
      break;
    case 2:
      cmd[0] = 2;
      cmd[1] = raspiGetValue("RS");
      cmd[2] = raspiGetValue("RD");
      break;
    case 3:
      cmd[0] = 3;
      cmd[1] = raspiGetValue("RO");
      cmd[2] = raspiGetValue("RA");
      break;
    case 4:
      cmd[0] = 4;
      cmd[1] = raspiGetValue("VL");
      cmd[2] = raspiGetValue("VR");
      break;
    case 5:
      cmd[0] = 5;
      cmd[1] = raspiGetValue("TS");
      cmd[2] = raspiGetValue("TA");
      cmd[3] = raspiGetValue("TR");
      cmd[4] = raspiGetValue("TD");
      break;
    case 10:
      cmd[0] = 10;
      cmd[1] = raspiGetValue("BA");
      cmd[2] = raspiGetValue("BB");
      break;
  }
}

