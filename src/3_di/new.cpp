// C++17: inject the sensor at compile time as an `auto` template parameter.
inline int baro_read() { return *reinterpret_cast<volatile int*>(0x40012000); }
template <auto Read> struct Altimeter {            // empty: no pointer stored
  int altitude() const { return Read() * 2; }
};
Altimeter<baro_read> alt;
int altitude() { return alt.altitude(); }
