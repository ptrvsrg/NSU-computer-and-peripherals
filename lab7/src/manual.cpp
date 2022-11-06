#include <cfloat>      // FLOAT_MIN
#include <ctime>
#include <iostream>
#include <xmmintrin.h>

#define N 2048
#define M 10

void Inverse(const float * matrix,
             float * result);
float GetMaxSum(const float * matrix); // |A|_1 * |A|_infinity
void FillB(const float * matrix,
           float * B);
void FillI(float * I);
void Multiplication(const float * multiplier1,
                    const float * multiplier2,
                    float * result);
void Addition(const float * addend1,
              const float * addend2,
              float * result);
void Subtraction(const float * minuend,
                 const float * subtrahend,
                 float * result);
void Copy(float * dest,
          const float * src);
void Print(const float * matrix);

int main()
{
    srandom(time(nullptr));
    auto * matrix = new float [N * N];
    auto * result = new float [N * N];
    timespec start = {
        0,
        0
    };
    timespec end = {
        0,
        0
    };

    for (int i = 0; i < N * N; ++i)
    {
        matrix[i] = float(random());
        matrix[i] *= (random() % 2) ? 1 : -1;
        result[i] = 0;
    }

//    float matrix[N * N] = {
//        3, 0, 9, 0,
//        3, 4, 8, 1,
//        2, 4, 6, 2,
//        6, 2, 2, 6
//    };
//    float result[N * N] = { 0 };

    clock_gettime(CLOCK_MONOTONIC_RAW,
                  &start);
    Inverse(matrix,
            result);
    clock_gettime(CLOCK_MONOTONIC_RAW,
                  &end);

//    Print(matrix);
//    cout << endl;
//    Print(result);
//    cout << endl;

    std::cout << "Time with manual vectorization: "
         << (double)end.tv_sec - (double)start.tv_sec + 1e-9 * ((double)end.tv_nsec - (double)start.tv_nsec)
         << " sec." << std::endl;

    return EXIT_SUCCESS;
}

void Inverse(const float * matrix,
             float * result)
{
    auto * B = new float[N * N];
    auto * I = new float[N * N];
    auto * tmp = new float[N * N];
    auto * R = new float[N * N];
    bool flag = true;

    FillB(matrix, B);
    FillI(I);
    Multiplication(B,
                   matrix,
                   tmp);
    Subtraction(I,
                tmp,
                R);
    Addition(I,
             R,
             tmp);
    Copy(result,
         R);

    for (int i = 2; i < M; ++i)
    {
        Multiplication(flag ? result : I,
                       R,
                       flag ? I : result);
        Addition(tmp,
                 flag ? I : result,
                 tmp);
        flag = !flag;
    }

    Multiplication(tmp,
                   B,
                   result);

    delete[] I;
    delete[] B;
    delete[] tmp;
    delete[] R;
}

inline __m128 mm_abs_ps(__m128 A)
{
    const __m128 SIGNMASK = _mm_castsi128_ps(_mm_set1_epi32(int(0x80000000)));
    return _mm_andnot_ps(SIGNMASK, A);
}

float GetMaxSum(const float * matrix)
{
    float max_sum_row = FLT_MIN;
    float max_sum_column = FLT_MIN;
    __m128 m128_row;
    __m128 m128_column;
    __m128 m128_sum_row;
    __m128 m128_sum_column;
    float m32_sum[4];
    float sum_row;
    float sum_column;

    for (int i = 0; i < N; ++i)
    {
        m128_sum_row = _mm_setzero_ps();
        m128_sum_column = _mm_setzero_ps();

        for (int j = 0; j < N / 4; ++j)
        {
            m128_row = _mm_load_ps(matrix + N * i + 4 * j);
            m128_column = _mm_setr_ps(matrix[N * j + i],
                                      matrix[N * (j + 1) + i],
                                      matrix[N * (j + 2) + i],
                                      matrix[N * (j + 3) + i]);
            m128_row = mm_abs_ps(m128_row);
            m128_column = mm_abs_ps(m128_column);

            m128_sum_row = _mm_add_ps(m128_sum_row,
                                      m128_row);
            m128_sum_column = _mm_add_ps(m128_sum_column,
                                         m128_column);
        }

        _mm_store_ps(m32_sum,
                     m128_sum_row);
        sum_row = m32_sum[0] + m32_sum[1] + m32_sum[2] + m32_sum[3];

        _mm_store_ps(m32_sum,
                     m128_sum_column);
        sum_column = m32_sum[0] + m32_sum[1] + m32_sum[2] + m32_sum[3];

        if (sum_row > max_sum_row)          max_sum_row = sum_row;
        if (sum_column > max_sum_column)    max_sum_column = sum_column;
    }

    return max_sum_row * max_sum_column;
}

void FillB(const float * matrix,
           float * B)
{
    float max = GetMaxSum(matrix);
    __m128 m128_max = _mm_set1_ps(max);
    __m128 * m128_B;
    m128_B = (__m128 *)B;
    __m128 m128_matrix_column;

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N / 4; ++j)
        {
            m128_matrix_column = _mm_setr_ps(matrix[N * j + i],
                                             matrix[N * (j + 1) + i],
                                             matrix[N * (j + 2) + i],
                                             matrix[N * (j + 3) + i]);

            m128_B[N * i / 4 + j] = _mm_div_ps(m128_matrix_column,
                                               m128_max);
        }
}

void FillI(float * I)
{
    __m128 * m128_I;
    m128_I = (__m128 *)I;

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N / 4; ++j)
            m128_I[N * i / 4 + j] = _mm_setr_ps(i == j,
                                                i == (j + 1),
                                                i == (j + 2),
                                                i == (j + 3));
}

void Multiplication(const float * multiplier1,
                    const float * multiplier2,
                    float * result)
{
    __m128 * m128_result;
    const __m128 * m128_multiplier2;
    m128_result = (__m128 *)result;
    m128_multiplier2 = (const __m128 *)multiplier2;
    __m128 m128_multiplier1;
    __m128 tmp;

    for (int i = 0; i < N * N / 4; ++i)
        m128_result[i] = _mm_setzero_ps();

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            m128_multiplier1 = _mm_set1_ps(multiplier1[N * i + j]);
            for (int k = 0; k < N / 4; ++k)
            {
                tmp = _mm_mul_ps(m128_multiplier1,
                                 m128_multiplier2[N * j / 4 + k]);
                m128_result[N * i / 4 + k] = _mm_add_ps(m128_result[N * i / 4 + k],
                                                        tmp);
            }
        }
}

void Addition(const float * addend1,
              const float * addend2,
              float * result)
{
    const __m128 * m128_addend1;
    const __m128 * m128_addend2;
    __m128 * m128_result;
    m128_addend1 = (const __m128 *)addend1;
    m128_addend2 = (const __m128 *)addend2;
    m128_result = (__m128 *)result;

    for (int i = 0; i < N * N / 4; i++)
        m128_result[i] = _mm_add_ps(m128_addend1[i],
                                    m128_addend2[i]);
}

void Subtraction(const float * minuend,
                 const float * subtrahend,
                 float * result)
{
    const __m128 * m128_minuend;
    const __m128 * m128_subtrahend;
    __m128 * m128_result;
    m128_minuend = (const __m128 *)minuend;
    m128_subtrahend = (const __m128 *)subtrahend;
    m128_result = (__m128 *)result;

    for (int i = 0; i < N * N / 4; i++)
        m128_result[i] = _mm_sub_ps(m128_minuend[i],
                                    m128_subtrahend[i]);
}

void Copy(float * dest,
          const float * src)
{
    const __m128 * m128_src;
    m128_src = (const __m128 *)src;

    for (int i = 0; i < N / 4; i++)
        _mm_store_ps(dest + 4 * i,
                     m128_src[i]);
}

void Print(const float * matrix)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            std::cout << matrix[N * i + j] << " ";

        std::cout << std::endl;
    }
}