//
// Created by EgrZver on 14.11.2026.
//

#ifndef ADALAB3_QUICKSORT_TESTUTILS_H
#define ADALAB3_QUICKSORT_TESTUTILS_H

#include <data/DataGenerationType.h>
#include <random>
#include <vector>

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

constexpr int SIZED_ARRAYS_VERIFY_RUNS = 1024;

template<typename T, comparator_t<T> Comparator>
const auto& qsort_f = quicksort<T, Comparator>;

template<typename T, std::derived_from<DataProvider<T>> DP, comparator_t<T> Comparator>
void run_test(DataGenerationType generation_type, Comparator cmp) {
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
            for (int sizes[] = {4,   8,   16,   32, 64, 128, 256, 512, 1024, 3,   6,    9,  27, 81,
                                243, 729, 2187, 5,  25, 125, 625, 7,   49,   343, 2401, 11, 121};
                 const int size: sizes) {
                for (int _ = 0; _ < SIZED_ARRAYS_VERIFY_RUNS; _++) {
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

#endif // ADALAB3_QUICKSORT_TESTUTILS_H
