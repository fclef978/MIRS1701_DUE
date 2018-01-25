static volatile unsigned char readPointer = 0;
static volatile unsigned char writePointer = 0;

static int bufSize = 256;
static volatile int q[256][8];


void queOpen() {
  readPointer = 0;
  writePointer = 0;
  for (int i = 0; i < 256; i++) {
    for (int j = 0; j < 8; j++) {
      q[i][j] = 0;
    }
  }
}

void quePush(int cmd[]) {
  int wp = writePointer++;
  for (int i = 0; i < 8; i++) {
    q[wp][i] = cmd[i];
  }
}

void quePop(int cmd[]) {
  int rp = readPointer++;
  for (int i = 0; i < 8; i++) {
    cmd[i] = q[rp][i];
  }
}

int queGetLength() {
  return writePointer - readPointer;
}
