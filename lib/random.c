#include <sys/time.h>
#include <stdlib.h>

// return a random double in [0.0, 1.0)
double randfrac(void)
{
    double res = (rand() % RAND_MAX) / (double)RAND_MAX;
    return res;
}

void doseed(void)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    unsigned seed = (unsigned)tp.tv_usec;
    srand(seed);
}

double get_probability(int m, int n)
{
    return (double)m / (double)n;
}