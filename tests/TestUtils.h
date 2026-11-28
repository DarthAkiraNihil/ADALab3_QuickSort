//
// Created by EgrZver on 14.11.2026.
//

#ifndef ADALAB3_QUICKSORT_TESTUTILS_H
#define ADALAB3_QUICKSORT_TESTUTILS_H

#include <data/DataGenerationType.h>
#include <random>
#include <vector>
#include <array>

// TODO: add tests for sorting BIG data

template<typename T>
class DataProvider;

template<typename T, comparator_t<T> Comparator>
bool check_sort(T* begin, T* end, Comparator comp) {
    if (end - begin <= 1) {
        return true;
    }

    for (T* it = begin; it != end; ++it) {
        if (!comp(*it, *(it + 1)) && !qsort_internal::_eq(it, it + 1, comp)) {
            return false;
        }
    }

    return true;
}



template<typename T, comparator_t<T> Comparator>
const auto& qsort_f = quicksort<T, Comparator>;

template<typename T, std::derived_from<DataProvider<T>> DP, comparator_t<T> Comparator, int SizeArraySize>
void run_test_internal(DataGenerationType generation_type, Comparator cmp, const int verify_passes, const std::array<int, SizeArraySize>& sized_array_sizes) {
    DP provider{};

    switch (generation_type) {
        case DataGenerationType::Empty:
        case DataGenerationType::Single:
        case DataGenerationType::Pair: {
            std::vector<T> data = provider.generate_array(generation_type, 0);
            T* begin = data.data();
            T* end = begin + data.size() - 1;

            qsort_f<T, Comparator>(begin, end, cmp);
            ASSERT_TRUE(check_sort(begin, end, cmp)) << "On gen type: " << static_cast<int>(generation_type);
            return;
        }
        default: {
            for (const int size: sized_array_sizes) {

                for (int _ = 0; _ < verify_passes; _++) {
                    std::vector<T> data = provider.generate_array(generation_type, size);
                    T* begin = data.data();
                    T* end = begin + data.size() - 1;

                    qsort_f<T, Comparator>(begin, end, cmp);
                    ASSERT_TRUE(check_sort(begin, end, cmp)) << "On size: " << size;
                }
            }
        }
    }
}


constexpr int SMALL_SIZE_VERIFY_RUNS = 1024;
constexpr int BIG_SIZE_VERIFY_RUNS = 8;

constexpr std::array small_sizes = {
    4,   8,   16,   32, 64, 128, 256, 512, 1024, 3,   6,    9,  27, 81,
    243, 729, 2187, 5,  25, 125, 625, 7,   49,   343, 2401, 11, 121
};

constexpr std::array big_sizes = {
    65536 * 4,
    65536 * 16, // 16777216, // 2147483647, // 2 ^ 16, 24, 31 - 1
    // 14348907, // 3 ^ 15
    // 9765625, // 5 ^ 10
    // 282475249, // 7 ^ 10
    // 19487171, // 11 ^ 7
};

template<typename T, std::derived_from<DataProvider<T>> DP, comparator_t<T> Comparator>
void run_test(const DataGenerationType generation_type, Comparator cmp, const bool use_big_data = false) {
    if (use_big_data) {
        run_test_internal<T, DP, Comparator, big_sizes.size()>(
            generation_type,
            cmp,
            BIG_SIZE_VERIFY_RUNS,
            big_sizes
        );
    } else {
        run_test_internal<T, DP, Comparator, small_sizes.size()>(
            generation_type,
            cmp,
            SMALL_SIZE_VERIFY_RUNS,
            small_sizes
        );
    }
}

#endif // ADALAB3_QUICKSORT_TESTUTILS_H
