#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_SIZE (1 * 1024)
#define MAX_SIZE (2 * 1024 * 1024)

typedef uint64_t Time;

void Clock(Time * time);
void CreateStraight(uint32_t * array,
                    uint32_t size);
void CreateReverse(uint32_t * array,
                   uint32_t size);
uint32_t FindIndex(uint32_t * indexes,
                   uint32_t ind);
void CreateRandom(uint32_t * array,
                  uint32_t size);
uint64_t CalcTime(const uint32_t * array,
                  uint32_t size);
void Bypass(const uint32_t * array,
            uint32_t size);

int main(void)
{
    for (uint32_t size = MIN_SIZE; size <= MAX_SIZE; size *= 2)
    {
        printf("Size: %lu\n", size * sizeof(uint32_t));

        uint32_t * array = malloc(size * sizeof(uint32_t));

        CreateStraight(array,
                       size);
        Bypass(array,
               size);

        CreateRandom(array,
                     size);
        printf("Random: %lu\t", CalcTime(array, size));

        CreateReverse(array,
                      size);
        printf("Reverse: %lu\t", CalcTime(array, size));

        CreateStraight(array,
                       size);
        printf("Straight: %lu\n", CalcTime(array, size));

        free(array);
    }

    return EXIT_SUCCESS;
}

void Clock(Time * time)
{
    asm("rdtsc\n":"=a"(*time));
}

void CreateStraight(uint32_t * array,
                    uint32_t size)
{
    array[size - 1] = 0;
    for (uint32_t i = 0; i < size - 1; ++i)
        array[i] = i + 1;
}

void CreateReverse(uint32_t * array,
                   uint32_t size)
{
    array[0] = size - 1;
    for (uint32_t i = 1; i < size; ++i)
        array[i] = i - 1;
}

uint32_t FindIndex(uint32_t * indexes,
                   uint32_t ind)
{
    for (int i = 0, j = 0; ; ++i)
    {
        if (indexes[i] == -1)
        {
            continue;
        }

        if (j == ind)
        {
            uint32_t res = indexes[i];
            indexes[i] = -1;
            return res;
        }

        ++j;
    }
}

void CreateRandom(uint32_t * array,
                  uint32_t size)
{
    uint32_t * indexes = malloc((size - 1) * sizeof(uint32_t));
    for (uint32_t i = 0; i < size - 1; ++i)
        indexes[i] = i + 1;

    srandom(time(NULL));
    uint32_t ind = 0;
    uint32_t indexes_size = size - 1;
    while (indexes_size != 0)
    {
        uint32_t indexes_ind = random() % indexes_size;
        uint32_t next_ind = FindIndex(indexes,
                                      indexes_ind);
        array[ind] = next_ind;
        ind = next_ind;
        --indexes_size;
    }

    array[ind] = 0;
}

void Bypass(const uint32_t * array,
            uint32_t size)
{
    for (uint32_t i = 0, k = 0; i < size; ++i)
        k = array[k];
}

uint64_t CalcTime(const uint32_t * array,
                  uint32_t size)
{
    uint64_t min = UINT64_MAX;
    Time start, end;

    for (int i = 0; i < 3; ++i)
    {
        Clock(&start);
        Bypass(array,
               size);
        Clock(&end);

        uint64_t res = (end - start) / size;
        min = (min < res) ? min : res;
    }

    return min;
}