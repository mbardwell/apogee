// C++20: C++14 relaxed constexpr loop + constinit -> no guard, no boot code.
constexpr int channel_for(int mhz) { int c = 0; while (mhz > 400) { mhz -= 25; ++c; } return c; }
struct Radio { constexpr Radio() : ch(channel_for(437)) {} int ch; };
constinit Radio r;
Radio& radio() { return r; }
