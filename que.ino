static volatile unsigned int readPointer = 0;
static volatile unsigned int writePointer = 0;

static int bufSize = 256;
static volatile int q[256];

void queOpen() {
  readPointer = 0;
  writePointer = 0;
  for (int i = 0; i < bufSize; i++) {
    q[i] = 0;
  }
}

void quePush(int num) {
  unsigned char wp = writePointer & 0xFF;
  q[wp] = num;
  writePointer++;
}

int quePop() {
  unsigned char rp = readPointer & 0xFF;
  int result = q[rp];
  readPointer++;
  return result;
}

int queGetLength() {
  unsigned char wp = writePointer & 0xFF;
  unsigned char rp = readPointer & 0xFF;
  return wp - rp;
}

