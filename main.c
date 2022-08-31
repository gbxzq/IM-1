#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <windows.h>

#define N 1200

struct Event
{
    int id;
    double probability;
    int counter;
};

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

void calculate(struct Event *events, int n)
{
    double temp = 0;
    for (int i = 0; i < N; i++)
    {
        double randNum = randfrac();

        for (int j = 0; j < n; j++)
        {
            if (randNum < events[j].probability + temp)
            {
                events[j].counter += 1;
                break;
            }
            temp += events[j].probability;
        }
        temp = 0;
    }
}

int main(void)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    doseed();

    int events_amount;

    puts("Будь ласка, введіть кількість подій");
    scanf("%d", &events_amount);

    struct Event *events = malloc(events_amount * sizeof(struct Event));

    double probability_sum = 0;

    // todo: improve input of probability
    for (int i = 0; i < events_amount; i++)
    {
        events[i].id = i;
        events[i].counter = 0;
        printf("Введіть ймовірність для події A%d\n", events[i].id);
        scanf("%lf", &events[i].probability);
        probability_sum += events[i].probability;
    }

    if (probability_sum != 1)
    {
        fprintf(stderr, "Помилка. Ймовірності мають в сумі дорівнювати 1, натомість: %lf\n", probability_sum);
        return -1;
    }

    calculate(events, events_amount);

    for (int i = 0; i < events_amount; i++)
    {
        printf("Подія A%d з ймовірностю: %f\n", events[i].id, get_probability(events[i].counter, N));
    }

    return 0;
}
