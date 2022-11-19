#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <set>

#define CPU_HZ 2100000000ULL

union Time
{
    uint64_t t64;
    struct
    {
        uint32_t th, tl;
    } t32;
};

void Clock(Time & time);
void CreateStraight(uint32_t * array,
                    uint32_t size);
void CreateReverse(uint32_t * array,
                   uint32_t size);
void CreateRandom(uint32_t * array,
                  uint32_t size);
uint64_t CalcTime(const uint32_t * array,
                  uint32_t size);
void Bypass(const uint32_t * array,
            uint32_t size,
            uint32_t bypass_count);

int main()
{
    std::cout << std::setw(10) << std::left << "Size"
              << std::setw(10) << std::left << "Random"
              << std::setw(10) << std::left << "Reverse"
              << std::setw(10) << std::left << "Straight" << std::endl;

    uint32_t size = 8 * 1024 * 1024;

    for (int i = 0; i < 18; ++i)
    {
        std::cout << std::setw(10) << std::left << size * sizeof(uint32_t);

        auto * array = new uint32_t[size];

        CreateRandom(array,
                     size);
        std::cout << std::setw(10) << std::left << CalcTime(array, size);

        CreateReverse(array,
                      size);
        std::cout << std::setw(10) << std::left << CalcTime(array, size);

        CreateStraight(array,
                       size);
        std::cout << std::setw(10) << std::left << CalcTime(array, size) << std::endl;

        size /= 2;
        delete [] array;
    }

    return EXIT_SUCCESS;
}

void Clock(Time & time)
{
    asm("rdtsc\n":"=a"(time.t32.th),"=d"(time.t32.tl));
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

void CreateRandom(uint32_t * array,
                  uint32_t size)
{
    std::set<uint32_t> indexes;
    for (uint32_t i = 0; i < size - 1; ++i) // { 1, 2, ... , size - 1 }
        indexes.insert(i + 1);

    srandom(time(nullptr));
    uint32_t ind = 0;
    while (!indexes.empty())
    {
        uint32_t indexes_ind = random() % indexes.size();
        auto next_ind_iter = std::next(indexes.begin(),
                                       indexes_ind);
        array[ind] = *next_ind_iter;
        ind = *next_ind_iter;
        indexes.erase(next_ind_iter);
    }

    array[ind] = 0;
}

void Bypass(const uint32_t * array,
            uint32_t size,
            uint32_t bypass_count)
{
    for (uint32_t i = 0, k = 0; i < size * bypass_count; ++i)
        k = array[k];
}

uint64_t CalcTime(const uint32_t * array,
                  uint32_t size)
{
    Time start{}, end{};

    Clock(start);
    Bypass(array,
           size,
           3);
    Clock(end);

    uint64_t res = (end.t64 - start.t64) / (size * 3);
    return res;
}