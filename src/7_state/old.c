/* C: walk the boot state machine at run time. */
enum S { OFF, BOOT, SAFE, NOMINAL };
static enum S next(enum S s, int e) {
  switch (s) { case OFF: return e == 0 ? BOOT : s; case BOOT: return e == 1 ? SAFE : s;
               case SAFE: return e == 2 ? NOMINAL : s; default: return s; }
}
static const unsigned char boot_seq[3] = {0, 1, 2};
enum S boot_state(void) { enum S s = OFF; for (int i = 0; i < 3; ++i) s = next(s, boot_seq[i]); return s; }
