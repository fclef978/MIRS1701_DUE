static run_state_t run_state = STP;
static double speed_ref  = 0.0;
static double speed_curr = 0.0;
static double dist_ref   = 0.0;
static double dist_curr  = 0.0;
static double radius = 0.0;
static bool isLeft = true;

void runCtrlExecute() {
  // 直進制御において減速を開始する距離 [cm]
  const double dist_vel_down = 0.0;

  // 回転制御において減速を開始する角度 [deg]
  const double angle_vel_down = 0.0;

  // 直進制御における左右のタイヤの距離差の補正ゲイン
  const double Ks = 10.0 ; // 40.0;

  // 回転制御における左右のタイヤの距離差の補正ゲイン
  const double Kr = 0.0;

  int sign;
  double d_l, d_r, v_l, v_r, ratio, vel_ref, vel_mod;

  // 負の指令値に対応
  if (dist_ref >= 0.0) {
    sign = 1;
  } else {
    sign = -1;
  }

  distanceGet(&d_l, &d_r);
  velCtrlGet(&v_l, &v_r);

  switch (run_state) {
    case STP:
      velCtrlSet(0.0, 0.0);
      break;
    case STR:
      // 直進距離
      dist_curr  = (d_l + d_r) / 2.0;
      speed_curr = (v_l + v_r) / 2.0 * sign;

      // 減速率
      ratio = sign * (dist_ref - dist_curr) / dist_vel_down;
      if (ratio < 0.0) ratio = 0.0;
      if (ratio > 1.0) ratio = 1.0;

      if (speed_ref == 0.0 || dist_ref == 0.0 || ratio == 0.0) {
        run_state = STP;
        velCtrlSet(0.0, 0.0);
      } else {
        // 減速の実行
        vel_ref = sign * speed_ref * ratio;

        // 左右のタイヤの距離差の補正
        vel_mod = (d_l - d_r) * Ks;

        velCtrlSet((vel_ref - vel_mod), (vel_ref + vel_mod));
      }

      break;
    case ROT:
      // 回転角度
      dist_curr  = -(d_l - d_r) / D_TIRE * 180.0 / PI;
      speed_curr = -(v_l - v_r) / D_TIRE * 180.0 / PI * sign;

      // 減速率
      ratio = sign * (dist_ref - dist_curr) / angle_vel_down;
      if (ratio < 0.0) ratio = 0.0;
      if (ratio > 1.0) ratio = 1.0;

      if (speed_ref == 0.0 || dist_ref == 0.0 || ratio == 0.0) {
        run_state = STP;
        velCtrlSet(0.0, 0.0);
      } else {
        // 減速の実行＆角速度指令値→速度指令値に変換
        vel_ref = sign * speed_ref * ratio * D_TIRE / 2.0 * PI / 180.0;

        // 左右のタイヤの距離差の補正
        vel_mod = -(d_l + d_r) * Kr;

        velCtrlSet(-(vel_ref - vel_mod), (vel_ref + vel_mod));
      }

      break;
    case VEL:
      velCtrlSet(speed_ref, dist_ref);
      break;
    case TUR:
      double short_radius = 20.0 - D_TIRE / 2 + radius, long_radius = D_TIRE / 2 + 20.0 + radius;
      dist_curr  = deg((d_l + d_r) / (radius + 20.0) / 2.0); //回転角
      speed_curr = deg((v_l + v_r) / (radius + 20.0) / 2.0); //回転速度

      ratio = sign * (dist_ref - dist_curr) / angle_vel_down;
      if (ratio < 0.0) ratio = 0.0;
      if (ratio > 1.0) ratio = 1.0;

      if (speed_ref == 0.0 || dist_ref == 0.0 || ratio == 0.0) {
        run_state = STP;
        velCtrlSet(0.0, 0.0);
      } else {
        // 減速の実行＆角速度指令値→速度指令値に変換
        double tmp = sign * rad(speed_ref) * ratio;
        double v_c_l, v_c_r;
        if (isLeft) {
          v_c_l = tmp * short_radius;
          v_c_r = tmp * long_radius;
        } else {
          v_c_r = tmp * short_radius;
          v_c_l = tmp * long_radius;
        }
        velCtrlSet(v_c_l, v_c_r);
      }
      break;
  }
}

void runCtrlSet(run_state_t state, double speed, double dist) {
  run_state = state;
  if (state == VEL) speed_ref = speed;
  else speed_ref = abs(speed);
  dist_ref = dist;
  if (state != VEL) velCtrlReset();
}

void runCtrlSetRD(double radius_, double dir_) {
  radius = radius_;
  isLeft = dir_;
}

void runCtrlGet(run_state_t *state, double *speed, double *dist) {
  *state = run_state;
  *speed = speed_curr;
  *dist = dist_curr;
}

double rad(double deg) {
    return deg * PI / 180.0;
}

double deg(double rad) {
    return rad / PI * 180.0;
}

