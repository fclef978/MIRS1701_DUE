void slave() {
  SerialUSB.println("MainTask");
  if (raspiGetValue(0) == 0) {
    return;
  }
  SerialUSB.print("runMode ");
  SerialUSB.println(raspiGetValue(0));
  raspiResetRunMode();
}

