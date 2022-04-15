#include "./time.h"

clock_t start;
clock_t end;

void timefhere()
{
    start = clock();
}

void timeresult(const char* phase)
{
    end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("[INFO] %s took %f secs...\n", phase, cpu_time_used);
}
