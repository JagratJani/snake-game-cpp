// Stub sys/mman.h for MinGW — mmap is not available on Windows
// gtest-death-test.cc includes this on non-Windows POSIX systems.
// Since MinGW is treated as POSIX by the patched gtest-port-arch.h, 
// we need this stub to allow compilation.
#ifndef SYS_MMAN_H_STUB
#define SYS_MMAN_H_STUB
// mmap is not used on Windows builds; this stub is empty.
#endif
