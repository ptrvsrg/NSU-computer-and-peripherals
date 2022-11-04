#include <xmmintrin.h>

#include <cmath>        // fabs()
#include <ctime>
#include <iostream>
#include <cfloat>       // FLT_MIN

#define N 4
#define M 10000

using namespace std;

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
//    srand(time(nullptr));
//    auto * matrix = new float [N * N];
//    auto * result = new float [N * N];
//
//    for (int i = 0; i < N * N; ++i)
//    {
//        matrix[i] = rand() % 10;
//        result[i] = 0;
//    }
//
    float matrix[N * N] = {
        3, 0, 9, 0,
        3, 4, 8, 1,
        2, 4, 6, 2,
        6, 2, 2, 6
    };
    float result[N * N] = { 0 };

    timespec start = {
        0,
        0
    };
    clock_gettime(CLOCK_MONOTONIC_RAW,
                  &start);

    Inverse(matrix,
            result);

    Print(matrix);
    cout << endl;
    Print(result);
    cout << endl;

    timespec end = {
        0,
        0
    };
    clock_gettime(CLOCK_MONOTONIC_RAW,
                  &end);

    cout << "Time with manual vectorization: "
         << (double)end.tv_sec - (double)start.tv_sec + 1e-9 * ((double)end.tv_nsec - (double)start.tv_nsec)
         << " sec." << endl;

    return EXIT_SUCCESS;
}

void Inverse(const float * matrix,
             float * result)
{
    auto * B = new float[N * N];
    FillB(matrix, B);

    auto * I = new float[N * N];
    FillI(I);

    auto * tmp = new float[N * N];
    auto * R = new float[N * N];
    Multiplication(B,
                   matrix,
                   tmp);
    Subtraction(I,
                tmp,
                R);

    Addition(I,
             R,
             tmp);
    Copy(result, R);
    bool flag = true;
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

float GetMaxSum(const float * matrix)
{
    float max_sum_row = FLT_MIN;
    float max_sum_column = FLT_MIN;

    for (int i = 0; i < N; i++) // rows
    {
        float sum_row = 0;
        float sum_column = 0;

        for (int j = 0; j < N; j++) // columns
        {
            sum_row += fabs(matrix[N * i + j]);
            sum_column += fabs(matrix[j * N + i]);
        }

        if (sum_row > max_sum_row)          max_sum_row = sum_row;
        if (sum_column > max_sum_column)    max_sum_column = sum_column;
    }

    return max_sum_row * max_sum_column;
}

void FillB(const float * matrix,
           float * B)
{
    float max = GetMaxSum(matrix);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            B[N * i + j] = matrix[j * N + i] / max;
}

void FillI(float * I)
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            I[N * i + j] = (float)(i == j);

}

void Multiplication(const float * multiplier1,
                    const float * multiplier2,
                    float * result)
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            __m128 m128_result = _mm_setzero_ps();
            for (int k = 0; k < N / 4; ++k)
            {
                __m128 m128_multiplier1 = _mm_load_ps(multiplier1 + N * i + 4 * k);
                __m128 m128_multiplier2 = _mm_setr_ps(multiplier2[N * k + j],
                                                      multiplier2[N * (k + 1) + j],
                                                      multiplier2[N * (k + 2) + j],
                                                      multiplier2[N * (k + 3) + j]);
                m128_result = _mm_add_ps(m128_result,
                                         _mm_mul_ps(m128_multiplier1,
                                                    m128_multiplier2));
            }
            float m32_result[4];
            _mm_store_ps(m32_result,
                         m128_result);
            result[N * i + j] = m32_result[0] + m32_result[1] + m32_result[2] + m32_result[3];
        }
}

void Addition(const float * addend1,
              const float * addend2,
              float * result)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N / 4; j++)
        {
            __m128 m128_addend1 = _mm_load_ps(addend1 + N * i + 4 * j);
            __m128 m128_addend2 = _mm_load_ps(addend2 + N * i + 4 * j);
            __m128 m128_result = _mm_add_ps(m128_addend1,
                                            m128_addend2);
            _mm_store_ps(result + N * i + 4 * j,
                         m128_result);
        }
}

void Subtraction(const float * minuend,
                 const float * subtrahend,
                 float * result)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N / 4; j++)
        {
            __m128 m128_minuend = _mm_load_ps(minuend + N * i + 4 * j);
            __m128 m128_subtrahend = _mm_load_ps(subtrahend + N * i + 4 * j);
            __m128 m128_result = _mm_sub_ps(m128_minuend,
                                            m128_subtrahend);
            _mm_store_ps(result + N * i + 4 * j,
                         m128_result);
        }
}

void Copy(float * dest,
          const float * src)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N / 4; j++)
        {
            __m128 m128_src = _mm_load_ps(src + N * i + 4 * j);
            _mm_store_ps(dest + N * i + 4 * j,
                         m128_src);
        }
}

void Print(const float * matrix)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << matrix[N * i + j] << " ";
        }

        cout << endl;
    }
}