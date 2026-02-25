// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
    int result = syscall(2, filename, flags);
    if (result < 0) {
        errno = -result;
        return -1;
    }else{
        return result;
    }
}
