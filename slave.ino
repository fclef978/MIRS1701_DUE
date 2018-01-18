static int btChangeFlag = 0;
static int btA = 0;
static int btB = 0;

void slave() {
  run_state_t rs;
  double a, b;
  runCtrlGet(&rs, &a, &b);
  if (btChangeFlag && rs == STP) {
    btChangeFlag = 0;
    ioSetBt(btA, btB);
  }
  if (raspiIsUpdated()) {
    switch (raspiGetValue(0)) {
      case 0:
        break;
      case 1:
        runCtrlSet(STP, 0, 0);
        break;
      case 2:
        runCtrlSet(STR, raspiGetValue(1), raspiGetValue(2));
        break;
      case 3:
        runCtrlSet(ROT, raspiGetValue(3), raspiGetValue(4));
        break;
      case 4:
        runCtrlSet(VEL, raspiGetValue(5), raspiGetValue(6));
        break;
      case 5:
        
      case 10:
        btA = raspiGetValue(10);
        btB = raspiGetValue(11);
        btChangeFlag = 1;
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

