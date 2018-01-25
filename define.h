/* 変数型の定義 */
typedef enum {
  STP = 0,
  STR,
  ROT,
  VEL,
  TUR
} run_state_t;

/* ピン配置 */
#define PIN_CTRL_A  0
#define PIN_CTRL_B  1
#define PIN_PIC     2
#define PIN_BTSW_A  3
#define PIN_BTSW_B  4
#define PIN_ENC_B_L 5
#define PIN_ENC_A_L 6
#define PIN_ENC_B_R 7
#define PIN_ENC_A_R 8
#define PIN_PWM_L   9
#define PIN_DIR_L   10
#define PIN_PWM_R   11
#define PIN_DIR_R   12
#define PIN_RESET   13
#define PIN_DBG     52
#define PIN_BTV_A   54
#define PIN_BTV_B   55
#define PIN_JS_X    57
#define PIN_JS_Y    58
#define PIN_SLVR    59

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
#define V_RATIO 0.33333
//機体半径
#define RADIUS  20.0
