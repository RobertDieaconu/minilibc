# minilibc

O bibliotecă standard C minimală (`libc.a`) implementată de la zero pentru **Linux x86-64**. Construită fără nicio libc gazdă (`-nostdinc -fno-builtin`), acest proiect reimplementează runtime-ul C, interfața de apeluri de sistem, gestionarea memoriei, operațiile pe șiruri, I/O și gestionarea proceselor direct peste apelurile de sistem Linux.

> Arhitectura syscall adaptată din [Musl libc](https://musl.libc.org/) (BSD-3-Clause).

---

## Funcționalități

- **Punct de intrare ELF personalizat** — `_start` scris în assembly NASM, apelează `__libc_start_main`
- **Interfață directă de syscall** — instrucțiunea `syscall` inline prin `__syscall()` pentru toate operațiunile
- **Gestionarea memoriei** — wrappere pentru `mmap`/`mremap`/`munmap`; `malloc`/`free`/`calloc`/`realloc`/`reallocarray` bazate pe o listă dublu înlănțuită de alocări
- **Bibliotecă de șiruri** — `strcpy`, `strncpy`, `strcat`, `strncat`, `strcmp`, `strncmp`, `strlen`, `strchr`, `strrchr`, `strstr`, `strrstr`, `memcpy`, `memmove`, `memcmp`, `memset`
- **I/O** — `open`, `close`, `read`, `write`, `lseek`, `truncate`, `ftruncate`, `puts`
- **Stat fișiere** — `stat`, `fstat`, `fstatat`
- **Procese** — `exit`, `sleep`, `nanosleep`
- **errno** — variabila globală `errno` cu toate codurile de eroare POSIX standard

---

## Structura proiectului

```
.
├── Makefile
├── errno.c                          # variabila errno + coduri de eroare POSIX
├── syscall.c                        # wrapper variadic syscall()
├── crt/
│   ├── start.asm                    # punct de intrare ELF _start
│   └── __libc_start_main.c          # inițializează heap-ul, apelează main, curăță
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
│   │   │   └── syscall_list.h       # toate numerele de syscall __NR_* (0–332)
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
│   └── mem_list.c                   # listă înlănțuită pentru urmărirea alocărilor
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

## Cerințe

- **GCC** (Linux x86-64)
- **NASM** assembler
- **GNU Make** + **ar**

---

## Compilare

```bash
make
```

Aceasta generează `libc.a` — o arhivă statică ce conține toate obiectele compilate plus obiectul de pornire CRT `crt/start.o`.

Pentru a șterge fișierele generate:

```bash
make clean
```

Pentru a arhiva sursele într-un fișier zip:

```bash
make pack
```

---

## Utilizare

Leagă programul tău de această bibliotecă în loc de libc-ul sistemului:

```bash
gcc -nostdinc -nostdlib -Ipath/to/include program.c libc.a -o program
```

---

## Note de implementare

### Interfața syscall

Toate apelurile de sistem trec prin funcția `__syscall()` specifică arhitecturii, definită în `include/internal/arch/x86_64/syscall_arch.h`, care folosește assembly inline pentru a invoca direct instrucțiunea `syscall`:

```c
static inline long __syscall(long n, long a1, long a2, long a3, long a4, long a5, long a6);
```

Funcția publică variadică `syscall()` din `syscall.c` este un wrapper peste `__syscall()` pentru uz general.

### Alocatorul de memorie

Alocatorul (`mm/malloc.c`) folosește `mmap` pentru a obține memorie de la sistemul de operare. Toate alocările active sunt urmărite într-o listă dublu înlănțuită (`mm/mem_list.c`) care este inițializată la pornirea programului și curățată la ieșire prin `__libc_start_main`.

### Pornirea CRT

Execuția programului începe la `_start` (`crt/start.asm`), care apelează `__libc_start_main` cu un pointer către `main`. Funcția `__libc_start_main` inițializează alocatorul de memorie, invocă `main`, efectuează curățarea și returnează codul de ieșire către `_start`, care apelează apoi `exit`.

---

## Licență

BSD-3-Clause. Codul arhitecturii syscall adaptat din [Musl libc](https://musl.libc.org/).
