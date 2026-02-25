#include <unistd.h>   // For write()
#include <string.h>   // For strlen()
#include <errno.h>    // For errno
#include <stdio.h>    // For EOF

int puts(const char *str) {
    int len = strlen(str);
    int result = write(1, str, len);
    if (result < 0) {
        errno = -result;
        return -1;
    }
    result = write(1, "\n", 1);
    if (result < 0) {
        errno = -result;
        return -1;
    }
    return result;
}
