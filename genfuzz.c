#include <stdio.h>
#include <stdlib.h>
// #include <time.h>
#include <sys/time.h>

#define NBYTES 11
int main()
{
    // srandom((unsigned int)time(NULL));
    struct timeval t1;
    gettimeofday(&t1, NULL);
    srandom((unsigned int)(t1.tv_sec ^ t1.tv_usec));

    for (int i = 0; i < NBYTES; i++)
    {
        long x = random();
        putc(x & 0xff, stdout);
    }

    return 0;
}
