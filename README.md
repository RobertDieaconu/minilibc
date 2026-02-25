# minilibc

A minimal C standard library (`libc.a`) implemented from scratch for **x86-64 Linux**. Built without any host libc (`-nostdinc -fno-builtin`), this project re-implements the C runtime, syscall interface, memory management, string operations, I/O, and process management directly on top of Linux syscalls.

> Syscall architecture adapted from [Musl libc](https://musl.libc.org/) (BSD-3-Clause).

---

## Features

- **Custom ELF entry point** — `_start` in NASM assembly, calls into `__libc_start_main`
- **Direct syscall interface** — inline `syscall` instruction via `__syscall()` for all operations
- **Memory management** — `mmap`/`mremap`/`munmap` wrappers; `malloc`/`free`/`calloc`/`realloc`/`reallocarray` backed by a doubly-linked allocation list
- **String library** — `strcpy`, `strncpy`, `strcat`, `strncat`, `strcmp`, `strncmp`, `strlen`, `strchr`, `strrchr`, `strstr`, `strrstr`, `memcpy`, `memmove`, `memcmp`, `memset`
- **I/O** — `open`, `close`, `read`, `write`, `lseek`, `truncate`, `ftruncate`, `puts`
- **File stat** — `stat`, `fstat`, `fstatat`
- **Process** — `exit`, `sleep`, `nanosleep`
- **errno** — global `errno` variable with all standard POSIX error codes

---

## Project Structure

```
.
├── Makefile
├── errno.c                          # errno variable + POSIX error codes
├── syscall.c                        # Variadic syscall() wrapper
├── crt/
│   ├── start.asm                    # ELF _start entry point
│   └── __libc_start_main.c          # Initializes heap, calls main, cleanup
├── include/
│   ├── errno.h
│   ├── fcntl.h
│   ├── stdarg.h / stddef.h
│   ├── stdio.h / stdlib.h / string.h
│   ├── time.h / unistd.h
│   ├── sys/
│   │   ├── mman.h / stat.h / types.h
│   ├── internal/
│   │   ├── arch/x86_64/
│   │   │   ├── syscall_arch.h       # __syscall() inline asm
│   │   │   └── syscall_list.h       # All __NR_* syscall numbers (0–332)
│   │   ├── mm/mem_list.h
│   │   ├── essentials.h / io.h / syscall.h / types.h
├── io/
│   ├── open.c / close.c
│   ├── read_write.c
│   ├── lseek.c / truncate.c / ftruncate.c
│   └── puts.c
├── mm/
│   ├── mmap.c                       # mmap / mremap / munmap
│   ├── malloc.c                     # malloc / free / calloc / realloc
│   └── mem_list.c                   # Allocation tracking linked list
├── process/
│   ├── exit.c
│   ├── nanosleep.c
│   └── sleep.c
├── stat/
│   ├── stat.c / fstat.c / fstatat.c
└── string/
    └── string.c
```

---

## Requirements

- **GCC** (x86-64 Linux)
- **NASM** assembler
- **GNU Make** + **ar**

---

## Build

```bash
make
```

This produces `libc.a` — a static archive containing all compiled objects plus the CRT startup object `crt/start.o`.

To clean build artifacts:

```bash
make clean
```

To package the source into a zip archive:

```bash
make pack
```

---

## Usage

Link your program against this library instead of the system libc:

```bash
gcc -nostdinc -nostdlib -Ipath/to/include your_program.c libc.a -o your_program
```

---

## Implementation Notes

### Syscall Interface

All system calls go through the architecture-specific `__syscall()` function defined in `include/internal/arch/x86_64/syscall_arch.h`, which uses inline assembly to invoke the `syscall` instruction directly:

```c
static inline long __syscall(long n, long a1, long a2, long a3, long a4, long a5, long a6);
```

The public variadic `syscall()` function in `syscall.c` wraps `__syscall()` for general use.

### Memory Allocator

The allocator (`mm/malloc.c`) uses `mmap` to obtain memory from the OS. All live allocations are tracked in a doubly-linked list (`mm/mem_list.c`) that is initialized at program startup and cleaned up at exit via `__libc_start_main`.

### CRT Startup

Program execution begins at `_start` (`crt/start.asm`), which calls `__libc_start_main` with a pointer to `main`. The `__libc_start_main` function initializes the memory allocator, invokes `main`, performs cleanup, and returns the exit code to `_start`, which then calls `exit`.

---

## License

BSD-3-Clause. Syscall architecture code adapted from [Musl libc](https://musl.libc.org/).
