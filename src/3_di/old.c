/* C: inject the sensor at run time through a stored function pointer. */
static int baro_read(void) { return *(volatile int*)0x40012000; }
struct Altimeter { int (*read)(void); };          /* 4 bytes RAM per object */
struct Altimeter alt = { baro_read };
int altitude(void) { return alt.read() * 2; }
