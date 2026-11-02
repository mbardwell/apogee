// C++20: consteval runs the same state machine inside the compiler.
enum class S : unsigned char { Off, Boot, Safe, Nominal };
constexpr S next(S s, int e) {
  switch (s) { case S::Off: return e == 0 ? S::Boot : s; case S::Boot: return e == 1 ? S::Safe : s;
               case S::Safe: return e == 2 ? S::Nominal : s; default: return s; }
}
constexpr unsigned char boot_seq[3] = {0, 1, 2};
consteval S run() { S s = S::Off; for (int e : boot_seq) s = next(s, e); return s; }
S boot_state() { return run(); }
