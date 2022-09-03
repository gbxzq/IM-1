#include "../lib/random.h"

void calculate(struct Event *events, int n)
{
    double temp = 0;
    for (int i = 0; i < N; i++)
    {
        double rand_num = randfrac();

        for (int j = 0; j < n; j++)
        {
            if (rand_num < events[j].probability + temp)
            {
                events[j].counter += 1;
                break;
            }
            temp += events[j].probability;
        }
        temp = 0;
    }
}

int first(void)
{
    doseed();

    int events_amount;

    puts("Будь ласка, введіть кількість подій");
    scanf("%d", &events_amount);

    struct Event *events = malloc(events_amount * sizeof(struct Event));

    double probability_sum = 0;

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

double *f(double *probabilities, int *values)
{
    double *distr;

    distr = malloc(sizeof(double) * (sizeof(values) / sizeof(*values)));

    distr[0] = probabilities[0];

    double sum = probabilities[0];

    for (int i = 1; i < (sizeof(values) / sizeof(*values)) + 1; i++)
    {
        sum += probabilities[i];
        distr[i] = sum;
    }

    return distr;
}

int second()
{
    doseed();
    double probabilities[] = {0.3, 0.35, 0.45};

    int values[] = {3, 5, 8};
    int counters[] = {0, 0, 0};

    double *distr = f(probabilities, values);

    for (int i = 0; i < N; i++)
    {
        double rand_num = randfrac();

        for (int j = 0; j < sizeof(values) / sizeof(*values); j++)
        {
            if (rand_num < distr[j])
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
int main(void)
{
    while (1)
    {
        int choise;
        puts("Виберіть завдання (1 або 2): ");
        scanf("%d", &choise);

        if (choise < 1 && choise > 2)
        {
            puts("Такого завдання не існує. Спробуйте ще раз");
            continue;
        }

        if (choise == 1)
        {
            first();
            break;
        }

        second();
    }

    return 0;
}
