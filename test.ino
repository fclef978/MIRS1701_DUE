void test_encoder() {
  long enc_l, enc_r;
  char str[100];
  SerialUSB.begin(115200);
  while (1) {
    encoderGet(&enc_l, &enc_r);
    sprintf(str, "enc_l = %6ld, enc_r = %6ld\n", enc_l, enc_r);
    SerialUSB.print(str);
    delay(T_CTRL);
  }
}
