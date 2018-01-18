void softwareReset() {
  //ioReset();]
  SerialUSB.end();
  //SCB->AIRCR = ((0x5FA << SCB_AIRCR_VECTKEY_Pos) | SCB_AIRCR_SYSRESETREQ_Msk);
  //RSTC->RSTC_MR = 0xA5000801;
  //RSTC->RSTC_CR = 0xA5000013;
}

