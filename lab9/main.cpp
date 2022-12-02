#include <cstdint>
#include <iomanip>
#include <iostream>

#define SIZE        (32 * 24 * 1024 * 1024 / sizeof(uint32_t))
#define CACHE_SIZE  (12 * 1024 * 1024 / sizeof(uint32_t))
#define OFFSET      (24 * 1024 * 1024 / sizeof(uint32_t))

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
                size_t fragments,
                size_t cache_size);
void InitArray(uint32_t * array,
               size_t fragments,
               size_t offset,
               size_t cache_size);

int main()
{
    auto * array = new uint32_t[SIZE];

    std::cout << std::left << std::setw(20)
              << "Fragments: "
              << "Tacts: " << std::endl;

    InitArray(array,
              32,
              OFFSET,
              CACHE_SIZE);

    Bypass(array,
           32,
           CACHE_SIZE);

    for(int fragments = 1; fragments <= 32; ++fragments)
    {
        InitArray(array,
                  fragments,
                  OFFSET,
                  CACHE_SIZE);

        std::cout << std::left << std::setw(20)
                  << fragments
                  << Bypass(array,
                            fragments,
                            CACHE_SIZE) << std::endl;
    }

    delete [] array;
    return EXIT_SUCCESS;
}

void Clock(Time & time)
{
    asm volatile ( "rdtsc\n" : "=a" (time.m32.l), "=d" (time.m32.h) );
}

void InitArray(uint32_t * array,
               size_t fragments,
               size_t offset,
               size_t cache_size)
{
    for(size_t i = 0; i < cache_size; ++i)
    {
        for(size_t j = 0; j < fragments; ++j)
            array[i + j * offset] = i + (j + 1) * offset;

        array[i + (fragments - 1) * offset] = i + 1;
    }

    array[(cache_size - 1) + (fragments - 1) * offset] = 0;
}

uint64_t Bypass(const uint32_t * array,
                size_t fragments,
                size_t cache_size)
{
    uint64_t t_min = UINT64_MAX;
    Time start{}, end{};

    for (int i = 0; i < 10; ++i)
    {
        Clock(start);

        for (uint32_t k = 0, j = 0; j < fragments * cache_size; ++j)
            k = array[k];

        Clock(end);

        if (t_min > end.m64 - start.m64)
            t_min = end.m64 - start.m64;
    }

    return t_min / (fragments * cache_size);
}