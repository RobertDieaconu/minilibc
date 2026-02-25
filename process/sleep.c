#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>
#include <time.h>

unsigned int sleep(unsigned int seconds){
    struct timespec t1;
    struct timespec t2;
    t1.sec = seconds;
    t1.n_sec = 0;

    while (nanosleep(&t1, &t2) < 0){
        if (errno < 0){
            return seconds;
        }
        t1 = t2;
    }
    return 0;
}
