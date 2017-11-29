void slave() {
  if (raspiGetValue(0) == 0) {
    return;
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
        SerialUSB.println("STR");
        break;
      default:
        break;
    }
  }
  runCtrlExecute();
  velCtrlExecute();
}

