// C++03: no constexpr, so a constructor that touches a volatile runs at boot.
struct Mutex { Mutex() : owner(0) {} volatile unsigned owner; };
struct Lock {
  Mutex& m;
  Lock(Mutex& m_) : m(m_) { m.owner = 1; }
  ~Lock() { m.owner = 0; }
};
Mutex bus;                 // dynamic initialisation -> static ctor + .init_array
volatile unsigned reg;
void write_reg(unsigned v) { Lock l(bus); reg = v; }
