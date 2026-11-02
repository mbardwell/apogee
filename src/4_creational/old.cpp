// C++03: channel computed by a plain function -> Meyers singleton needs a guard.
int channel_for(int mhz) { int c = 0; while (mhz > 400) { mhz -= 25; ++c; } return c; }
struct Radio { Radio() : ch(channel_for(437)) {} int ch; };
Radio& radio() { static Radio r; return r; }
