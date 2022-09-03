#include <stdio.h>
#include <malloc.h>

#define N 1000

struct Event
{
    int id;
    double probability;
    int counter;
};

double randfrac(void);
void doseed(void);
double get_probability(int m, int n);