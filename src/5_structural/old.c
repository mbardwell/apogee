/* C: shared CRC-8 table is built in RAM at boot. */
static unsigned char tab[256];
void crc_init(void) {
  for (int i = 0; i < 256; ++i) {
    unsigned char c = i;
    for (int b = 0; b < 8; ++b) c = (c & 0x80) ? (c << 1) ^ 0x07 : (c << 1);
    tab[i] = c;
  }
}
unsigned char crc_step(unsigned char crc, unsigned char x) { return tab[crc ^ x]; }
