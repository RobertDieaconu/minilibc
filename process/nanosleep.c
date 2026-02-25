#include <time.h>
#include <errno.h>
#include <internal/syscall.h>

int nanosleep(const struct timespec *t1, struct timespec *t2) {
    int result = syscall(35, t1, t2);
    if (result < 0) {
        errno = -result;
        return -1;
    }else{
        return result;
    }
}
