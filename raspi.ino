// ラズパイ通信
static int values[128];

void raspiOpen() {
  SerialUSB.begin(2000000UL); // 2Mbpsで通信 (ULはunsigned longの意)
  SerialUSB.setTimeout(1);    // タイムアウト時間を設定 単位はミリ秒)
  SerialUSB.flush();          // バッファをクリア

  String buf; // バッファ
  while (1) {
    buf = findStringUntil(';');         // セミコロンが見つかったら文字列を返す
    if (buf == "RasPi:Ready") {         // 所定の文字列かどうか判定する
      SerialUSB.print("Arduino:OK;"); // 応答を返す
      break;
    }
    delay(1);
  }

  for (int i = 0; i < 128; i++) {
    values[i] = 0;
  }
}

int raspiGetValue(int addr) {
  return values[addr];
}

void raspiSend(String cmd, String val) {
  raspiWrite(cmd + ":" + val + ";");
}

void raspiWrite(String data) {
  SerialUSB.print(data);
}

bool raspiIsUpdated() {
  if (values[100] == 0) {
    return false;
  }
  values[100] = 0;
  return true;
}

bool raspiReceive() {
  String s, a = "", b = "";
  int resAddr = 0;
  s = findStringUntil(';');
  if (!split(&a, &b, s, ':')) {
    return false;
  }
  resAddr = raspiSortCommand(a);
  if (resAddr == -1) {
    return false;
  }
  values[resAddr] = b.toInt();
  return true;
}

int raspiSortCommand(String cmd) {
  if (cmd.length() != 2) {
    return -1;
  }
  int result = 0;
  char forward = cmd[0], backward = cmd[1];
  switch (forward) {
    case 'R': // run
      switch (backward) {
        case 'M': // mode
          result = 0;
          break;
        case 'S': // speed
          result = 1;
          break;
        case 'D': // distance
          result = 2;
          break;
        case 'O': // omega
          result = 3;
          break;
        case 'A': // angle
          result = 4;
          break;
        default:
          result = -1;
      }
      break;
    case 'C': // command
      switch (backward) {
        case 'U': // update
          result = 100;
          break;
        default:
          result = -1;
      }
      break;
    case 'B': // command
      switch (backward) {
        case 'A': // update
          result = 10;
          break;
        case 'B': // update
          result = 11;
          break;
        default:
          result = -1;
      }
      break;
    case 'V': // velocity
      switch (backward) {
        case 'L':
          result = 5;
          break;
        case 'R':
          result = 6;
          break;
        default:
          result = -1;
      }
    default:
      result = -1;
  }
  return result;
}

/*
   シリアルから指定の文字が見つかったらそこまでの文字列を返す関数です。
   terminater : 読み込みを終わらせる文字です
   reteurn : 指定の文字列が見つかったらそこまでの文字列を返し、タイムアウト(1ms)したら空文字列を返します。
*/
String findStringUntil(char terminater) {
  char tmp;           // シリアルから読み込んだ文字を一時的に保管しておく変数です。
  static String buf;  // 内部でシリアルからの文字をため込む変数です。terminaterが見つからなかった場合は次回の関数呼び出し時まで値を保持します。
  String result;      // 返り値です
  const unsigned long startTime = millis(); // 関数呼び出し時の時間です。
  while (1) {
    if (millis() - startTime > 0) { // タイムアウトの判定です。
      result = "";                  // 結果に空文字列を代入します。
      break;
    }
    if (SerialUSB.available() > 0) {  // バッファに何か入っているか判定します。
      tmp = SerialUSB.read();         // 一時的な変数にバッファから一文字読み出します。
      if (tmp == terminater) {         // 指定文字と等しいか判定する。
        result = buf;                  // 内部バッファを結果に代入する。
        buf = "";                      // 内部バッファを初期化する。
        break;
      }
      buf += tmp; // バッファに読みだした文字を連結する。
    }
  }
  return result;
}

/*
   指定した文字で文字列を二つに分断する関数です。
   strA : 前半を格納します。指定文字が見つからなかった場合、入力した文字列がそのまま入ります。
   strB : 公判を格納します。指定文字が見つからなかった場合、空文字列が入ります。
   data : 分解する文字列です。
   delimiter : 分解する文字です。
   return : 分解文字が見つからなかった場合、falseを返します。
*/
bool split(String *strA, String *strB, String data, char delimiter) {
  int delimitPoint = data.indexOf(delimiter); // 文字列から分解文字を検索します。
  *strA = ""; // 初期化
  *strB = "";
  if (delimitPoint == -1) { // 見つからなかった場合
    *strA = data; // そのまま
    *strB = "";   // 空文字列
    return false;
  }
  for (int i = 0; i < delimitPoint; i++) {
    *strA += data[i];
  }
  for (int i = delimitPoint + 1; i < data.length(); i++) {
    *strB += data[i];
  }
  return true;
}

