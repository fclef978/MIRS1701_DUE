void slave() {
  SerialUSB.println("MainTask");
  if (raspiGetValue(0) == 0) {
    return;
  }
  if (raspiIsNew()) {
    switch (raspiGetValue(0)) {
      case 0:
        break;
      case 1:
        SerialUSB.println("Stop");
        break;
      case 2:
        SerialUSB.print("Straight ");
        SerialUSB.print(raspiGetValue(1));
        SerialUSB.print(",");
        SerialUSB.println(raspiGetValue(2));
        break;
      default:
        break;
    }
  }
}

