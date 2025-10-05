cmake_minimum_required(VERSION 3.10)
project(RadixSort C)

# Use high optimization and native CPU instructions
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -march=native -flto -funroll-loops -fstrict-aliasing -fomit-frame-pointer -Wall -Wextra")

# List all source files
set(SOURCES
    main.c
    radix.c
    random.c
    util.c
)

# Create executable
add_executable(radixsort ${SOURCES})
