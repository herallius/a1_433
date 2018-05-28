#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <stdio.h>
#include <time.h>
int main() 
{
    printf("Timing test\n");
    for (int i = 0; i < 5; i++) {
        long seconds = 1;
        long nanoseconds = 500000000;
        struct timespec reqDelay = {seconds, nanoseconds};
        nanosleep(&reqDelay, (struct timespec *) NULL);
        printf("Delayed print %d.\n", i);
    }
return 0;
}

//echo 0 > /sys/class/leds/beaglebone\:green\:usr0/brightness