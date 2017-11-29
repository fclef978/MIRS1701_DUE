/* 変数型の定義 */
typedef enum {
  STP = 0,
  STR,
  ROT,
  VEL
} run_state_t;

/* ピン配置 */
#define PIN_ENC_A_L  2
#define PIN_ENC_B_L  4
#define PIN_ENC_A_R  3
#define PIN_ENC_B_R  7
#define PIN_DIR_R    8
#define PIN_PWM_R    9
#define PIN_DIR_L   12
#define PIN_PWM_L   11
#define PIN_SW      10
#define PIN_BATT    19

/* パラメータ */
// 動作周期 [ms]
#define T_CTRL 10 

// タイヤ半径 [cm] 4.387
// タイヤ半径 [cm] 4.23238
#define R_TIRE    4.242
// タイヤ間隔 [cm] 32.0 31.3
// 31.28262
#define D_TIRE    31.396
// エンコーダ分解能 (A相立上り/立下りを利用するため2倍)
#define ENC_RANGE (13*2) 
// ギア比
#define T_E_RATIO 19.0   
// 左タイヤに対する右タイヤの回転比
#define L_R_RATIO 1.0033 //すると右 小さくすると左に曲がる
// バッテリ入力の分圧比
#define V_RATIO 0.5 
