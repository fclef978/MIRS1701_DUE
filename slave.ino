static int btChangeFlag = 0;
static int btA = 0;
static int btB = 0;

void slave() {
  //ioSetBt(0, 1);
  run_state_t rs;
  double a, b;
  runCtrlGet(&rs, &a, &b);
  if (btChangeFlag && rs == STP) {
    btChangeFlag = 0;
    ioSetBt(btA, btB);
  }
  while (queGetLength() > 0) {
    int cmd[8];
    quePop(cmd);
    /*
    for (int i = 0; i < 8; i++) {
      SerialUSB.print(cmd[i]);
      SerialUSB.print(" ");
    }
    SerialUSB.println("");
    */
    switch (cmd[0]) {
      case 0:
        break;
      case 1:
        runCtrlSet(STP, 0, 0);
        break;
      case 2:
        runCtrlSet(STR, cmd[1], cmd[2]);
        break;
      case 3:
        runCtrlSet(ROT, cmd[1], cmd[2]);
        break;
      case 4:
        runCtrlSet(VEL, cmd[1], cmd[2]);
        break;
      case 5:
        runCtrlSet(TUR, cmd[1], cmd[2]);
        runCtrlSetRD(cmd[3], cmd[4]);
        break;
      case 10:
        ioSetBt(cmd[1], cmd[2]);
        break;
      case 100:
        softwareReset();
        break;
      default:
        break;
    }
  }
  runCtrlExecute();
  velCtrlExecute();
}

