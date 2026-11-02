# Apogee

A browser game about what modern C++ does to Arm firmware. You are trimming the flight software of a fictional deep-space probe, Apogee-7. Each level shows the real Cortex-M4 assembly that a C++14–C++26 feature produces, with up to three blanks to fill. Get it right and the game puts it side by side with the C or C++03 version of the same code: flash, RAM and instructions executed.

Every byte you save is mass the probe doesn't have to lift. Seven levels take it from perigee to apogee.

Inspired by and structured after [Kestrel-1](https://github.com/mbardwell/kestral): one level per Kestrel category.

## Play

Open `index.html` in any modern browser, or the GitHub Pages site once it's published. Progress is saved in your browser's local storage.

## Levels

| # | Category | Subsystem | Pattern | Modern feature | Old way | Flash + RAM, old → new |
|---|----------|-----------|---------|----------------|---------|-------------|
| 1 | RAII | Power bus arbiter | Bus lock guard | C++20 `constinit` | C++03 global with a constructor | 44 → 28 B |
| 2 | CRTP | Beacon transmitter | Static driver interface | CRTP checked by a C++20 concept | C function-pointer table | 24 → 12 B |
| 3 | Dependency injection | Altimeter | Compile-time policy | C++17 `auto` template parameter | C stored function pointer | 36 → 13 B |
| 4 | GoF Creational | Radio | Singleton | C++14 constexpr loops + C++20 `constinit` | C++03/11 function-local static | 80 → 16 B |
| 5 | GoF Structural | Telemetry checksum | Flyweight (shared CRC table) | C++17 constexpr table in flash | C table built in RAM at boot | 320 → 268 B |
| 6 | GoF Behavioral | Sensor gain stage | Strategy | C++14 generic lambda | C library function + pointer | 28 → 22 B |
| 7 | GoF State | Boot sequencer | Compile-time state machine | C++20 `consteval` | C run-time state machine | 59 → 4 B |

Total: 591 → 363 bytes (39% less). The modern versions never execute more instructions than the old ones, and execute fewer in six of the seven levels. The RAII level ties per call; its saving is the boot-time constructor C++03 needed.

## How the numbers were made

Compiler: the GNU Arm Embedded Toolchain, `arm-none-eabi-gcc` 13.2.1.

```
-mcpu=cortex-m4 -mthumb -Os -fno-asynchronous-unwind-tables
C++ adds: -fno-exceptions -fno-rtti
C: -std=c11   old C++: -std=c++03   new C++: -std=c++20
```

Sources are in `src/<level>/old.*` and `src/<level>/new.cpp`. Run `./build.sh` to regenerate `build/*.lst` (disassembly) and `build/sizes.txt`. In the game, literal-pool loads are written as `ldr rX, =symbol`, labels are named and comments are added; the instructions themselves are unchanged.

C++23 (`-std=c++23`) gives byte-identical results with GCC 13.2. GCC 13 has no C++26 mode, so `build.sh` also compiles the new versions with Clang 18 in `-std=c++2c` mode for the same Cortex-M4; it produces the same instruction sequences (Clang materialises addresses with `movw`/`movt` instead of a literal pool, so its byte counts differ slightly).

Notes on fairness:

- Each C version includes everything it needs to work (the driver function and its pointer table, the stored pointer, the init loop), because the C++ version contains all of those too.
- Level 4's old version also links `__cxa_guard_acquire`/`__cxa_guard_release` from libsupc++. They are not counted, so the real gap is larger.
- Level 5 trades flash for RAM: the C++ table costs 204 more bytes of flash but saves all 256 bytes of RAM and about 24,000 instructions at every reset.
- Level 6's C version does not count the separate strategy function or the caller.
- Instruction counts are taken from the listings (the path for one call, one sample, or the boot loop as labelled), not measured on hardware.

## Primary sources

- ISO/IEC 14882 (the C++ standard): [dcl.constinit], [dcl.constexpr], [basic.start.static], [stmt.dcl], [temp.concept], [temp.param], [expr.const], [expr.prim.lambda].
- N3652, *Relaxing constraints on constexpr functions* (C++14). N3649, *Generic (polymorphic) lambda expressions* (C++14). P1073, *Immediate functions* (C++20).
- Stroustrup, B. *The Design and Evolution of C++*. Addison-Wesley, 1994, §16.5.
- Coplien, J. O. "Curiously Recurring Template Patterns." *C++ Report*, February 1995.
- ISO/IEC TR 18015:2006, *Technical Report on C++ Performance*.
- Fowler, M. "Inversion of Control Containers and the Dependency Injection pattern." 2004.
- Alexandrescu, A. *Modern C++ Design*. Addison-Wesley, 2001, ch. 1.
- Gamma, E., Helm, R., Johnson, R. & Vlissides, J. *Design Patterns*. Addison-Wesley, 1994: Singleton p. 127, Flyweight p. 195, Strategy p. 315.
- Harel, D. "Statecharts: A visual formalism for complex systems." *Science of Computer Programming* 8(3), 1987.
- Samek, M. *Practical UML Statecharts in C/C++*, 2nd ed. Newnes, 2008.

The code is written for teaching and is intentionally minimal; it is not flight-qualified.
