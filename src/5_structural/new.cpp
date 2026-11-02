// C++17: the shared table is computed by the compiler and lives in flash.
struct Table { unsigned char v[256]; };
constexpr Table make() {
  Table t{};
  for (int i = 0; i < 256; ++i) {
    unsigned char c = i;
    for (int b = 0; b < 8; ++b) c = (c & 0x80) ? (c << 1) ^ 0x07 : (c << 1);
    t.v[i] = c;
  }
  return t;
}
constexpr Table tab = make();
unsigned char crc_step(unsigned char crc, unsigned char x) { return tab.v[crc ^ x]; }
