#!/bin/sh
# Regenerates every listing and size figure used by the game.
# Needs the GNU Arm Embedded Toolchain (arm-none-eabi-gcc / g++).
set -e
cd "$(dirname "$0")"
FLAGS="-mcpu=cortex-m4 -mthumb -Os -fno-asynchronous-unwind-tables -fno-ident"
XX="-fno-exceptions -fno-rtti"
mkdir -p build
arm-none-eabi-g++ --version | head -1 > build/compiler.txt
for d in src/*/; do
  n=$(basename "$d")
  for f in "$d"old.* "$d"new.cpp; do
    tag=$(basename "$f" | cut -d. -f1)
    case "$f" in
      *.c)            CC="arm-none-eabi-gcc -std=c11" ;;
      */old.cpp)      CC="arm-none-eabi-g++ -std=c++03 $XX" ;;
      *)              CC="arm-none-eabi-g++ -std=c++20 $XX" ;;
    esac
    $CC $FLAGS -c "$f" -o "build/$n.$tag.o"
    arm-none-eabi-objdump -d --no-show-raw-insn -C "build/$n.$tag.o" > "build/$n.$tag.lst"
    echo "$n $tag $(arm-none-eabi-size "build/$n.$tag.o" | tail -1 | awk '{print "text="$1, "data="$2, "bss="$3}')"
  done
done | tee build/sizes.txt

# Optional: confirm the C++ side in C++26 mode with Clang (instruction listings only).
if command -v clang >/dev/null 2>&1; then
  for d in src/*/; do
    n=$(basename "$d")
    clang --target=thumbv7em-none-eabi -mcpu=cortex-m4 -std=c++2c -Os -fno-exceptions -fno-rtti -fno-unwind-tables \
      -c "${d}new.cpp" -o "build/$n.c++26.o"
    arm-none-eabi-objdump -d --no-show-raw-insn -C "build/$n.c++26.o" > "build/$n.c++26.lst"
  done
  echo "C++26 (clang) listings written to build/*.c++26.lst"
fi
rm -f build/*.o
