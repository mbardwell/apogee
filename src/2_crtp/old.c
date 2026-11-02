/* C: driver "interface" as a table of function pointers (C++03 virtual is the same). */
struct Uart;
struct UartOps { void (*put)(struct Uart*, char); };
struct Uart { const struct UartOps* ops; };
static void stm32_put(struct Uart* u, char c) { (void)u; *(volatile unsigned*)0x40011004 = c; }
const struct UartOps stm32_ops = { stm32_put };
void beacon(struct Uart* u) { u->ops->put(u, 'K'); }
