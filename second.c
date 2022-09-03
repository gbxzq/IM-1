#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#define N 1000

struct Distributed
{
    double distr[255];
};

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

struct Distributed f(double *probabilities, int *values)
{
    struct Distributed d;

    d.distr[0] = probabilities[0];

    double sum = probabilities[0];

    for (int i = 1; i < (sizeof(values) / sizeof(*values)) + 1; i++)
    {
        sum += probabilities[i];
        d.distr[i] = sum;
    }

    return d;
}

int main()
{
    doseed();

    double probabilities[] = {0.3, 0.35, 0.45};

    int values[] = {3, 5, 8};
    int counters[] = {0, 0, 0};

    struct Distributed d = f(probabilities, values);

    for (int i = 0; i < N; i++)
    {
        double rand_num = randfrac();

        for (int j = 0; j < sizeof(values) / sizeof(*values); j++)
        {
            if (rand_num < d.distr[j])
            {
                counters[j] += 1;
                break;
            }
        }
    }
    
    for (int i = 0; i < sizeof(values) / sizeof(*values); i++)
    {
        printf("Величина %d з ймовірностю: %f\n", values[i], get_probability(counters[i], N));
    }

    return 0;
}