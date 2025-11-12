# RadixSort

A blazing fast radix sort implementation in C for 32-bit unsigned integers.

## Features

- Radix sort using configurable base
- Benchmark and tests

## Project Structure

```
sorting/
├── main.c
├── radix.c
├── radix.h
├── random.c
├── random.h
├── util.c
├── util.h
└── CMakeLists.txt
```

- `radix.c/h` – Radix sort implementation
- `random.c/h` – Xorshift32 random number generator
- `util.c/h` – Helper utilities (e.g., `isSorted`)
- `main.c` – Entry point and benchmarking
- `CMakeLists.txt` – CMake build configuration

## Build Instructions

### Windows (MinGW)

```powershell
mkdir build
cd build
cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..
mingw32-make
.\radixsort.exe
```

### Linux

```bash
mkdir build
cd build
cmake -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..
make
./radixsort
```

## Configuration

* `BITS` (in `radix.c`) controls the base. Higher values reduce passes with diminishing returns. Recommended around 11.
* Too high a base will cause the program to tank performance.

## Benchmarks (Intel i7-14700HX, 32GB RAM, Windows)

The contents of the array are generated using 32-bit XORShift, seeded using the current time. `BITS` = 11.

|   Array Size   | Time (ms) |
|----------------|-----------|
| 10,000         | <1        |
| 100,000        | 2         |
| 1,000,000      | 30        |
| 10,000,000     | 219       |
| 100,000,000    | 1690      |
| 1,000,000,000  | 14780     |

## Why `>>` and `&` Instead of `/` and `%`?

Radix sort processes numbers digit by digit. Since the radix/base is a power of two (`BASE = 2^BITS`), we can extract each digit efficiently with bitwise operations, which are much faster than `/` and `%`.

```c
x >> shift       ≡ x / (2 ** shift)       // Right shift replaces division
y & (BASE - 1)   ≡ y % BASE               // AND with mask replaces modulo
```

More generally, extracting a digit is equivalent to:

```c
(a / b) % c  ≡  (a >> lg(b)) & (c - 1)
```

In radix sort, `lg(b)` is simply the current bit shift (`shift`), so no logarithm calculation is needed. We instead just increment the shift by `BITS` each pass.
