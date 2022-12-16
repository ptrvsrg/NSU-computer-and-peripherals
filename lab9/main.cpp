#include <cstdint>
#include <iomanip>
#include <iostream>

#define MAX_FRAGMENTS_COUNT 32
#define FRAGMENT_SIZE (12 * 1024 * 1024 / sizeof(uint32_t))
#define OFFSET (24 * 1024 * 1024 / sizeof(uint32_t))
#define SIZE (MAX_FRAGMENTS_COUNT * OFFSET)

union Time
{
    uint64_t m64;
    struct
    {
        uint32_t l;
        uint32_t h;
    } m32;
};

void Clock(Time & time);
uint64_t Bypass(const uint32_t * array,
                size_t fragments_count,
                size_t fragment_size);
void InitArray(uint32_t * array,
               size_t fragments_count,
               size_t offset,
               size_t fragment_size);

int main()
{
    auto * array = new uint32_t[SIZE];

    std::cout << std::left << std::setw(20)
              << "Fragments: "
              << "Tacts: " << std::endl;

    InitArray(array,
              MAX_FRAGMENTS_COUNT,
              OFFSET,
              FRAGMENT_SIZE);

    Bypass(array,
           MAX_FRAGMENTS_COUNT,
           FRAGMENT_SIZE);

    for(int fragments = 1; fragments <= MAX_FRAGMENTS_COUNT; ++fragments)
    {
        InitArray(array,
                  fragments,
                  OFFSET,
                  FRAGMENT_SIZE);

        std::cout << std::left << std::setw(20)
                  << fragments
                  << Bypass(array,
                            fragments,
                            FRAGMENT_SIZE) << std::endl;
    }

    delete [] array;
    return EXIT_SUCCESS;
}

void Clock(Time & time)
{
    asm volatile ( "rdtsc\n" : "=a" (time.m32.l), "=d" (time.m32.h) );
}

void InitArray(uint32_t * array,
               size_t fragments_count,
               size_t offset,
               size_t fragment_size)
{
    for(size_t i = 0; i < fragment_size; ++i)
    {
        for(size_t j = 0; j < fragments_count; ++j)
            array[i + j * offset] = i + (j + 1) * offset;

        array[i + (fragments_count - 1) * offset] = i + 1;
    }

    array[(fragment_size - 1) + (fragments_count - 1) * offset] = 0;
}

uint64_t Bypass(const uint32_t * array,
                size_t fragments_count,
                size_t fragment_size)
{
    uint64_t t_min = UINT64_MAX;
    Time start{}, end{};

    for (int i = 0; i < 10; ++i)
    {
        Clock(start);

        for (uint32_t k = 0, j = 0; j < fragments_count * fragment_size; ++j)
            k = array[k];

        Clock(end);

        if (t_min > end.m64 - start.m64)
            t_min = end.m64 - start.m64;
    }

    return t_min / (fragments_count * fragment_size);
}