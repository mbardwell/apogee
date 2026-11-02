// C++20: constexpr constructor + constinit -> placed in .bss, no boot code.
struct Mutex { constexpr Mutex() : owner(0) {} volatile unsigned owner; };
struct Lock {
  Mutex& m;
  explicit Lock(Mutex& m_) : m(m_) { m.owner = 1; }
  ~Lock() { m.owner = 0; }
};
constinit Mutex bus;       // compile error if it would need runtime init
volatile unsigned reg;
void write_reg(unsigned v) { Lock l(bus); reg = v; }
