// C++20: CRTP static interface, contract checked by a concept (0 bytes).
template <class D> struct UartBase {
  void put(char c) { static_cast<D*>(this)->put_impl(c); }
};
struct Stm32Uart : UartBase<Stm32Uart> {
  void put_impl(char c) { *reinterpret_cast<volatile unsigned*>(0x40011004) = c; }
};
template <class U> concept Uart = requires(U u, char c) { u.put(c); };
static_assert(Uart<Stm32Uart>);
void beacon(Stm32Uart& u) { u.put('K'); }
