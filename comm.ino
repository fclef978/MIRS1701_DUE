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

