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
}

