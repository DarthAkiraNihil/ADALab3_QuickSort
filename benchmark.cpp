//
// Created by EgrZver on 14.11.2026.
//

#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <x86gprintrin.h>

#include <data/DataProvider.h>
#include <data/IntDataProvider.h>
#include <data/PodDataProvider.h>
#include <data/StringDataProvider.h>
#include <quicksort.h>

#include "tests/TestUtils.h"

using u64 = std::uint64_t;

template<typename T, typename P>
concept DataProviderType = std::derived_from<T, DataProvider<P>>;

namespace {
    template<typename T, comparator_t<T> Comparator>
    void insertion_sort(T* begin, T* end, Comparator cmp) {
        for (T* i = begin; i != end; ++i) {
            for (T* j = i + 1; j != end + 1; ++j) {
                if (cmp(*j, *i)) {
                    T t = std::move(*i);
                    *i = std::move(*j);
                    *j = std::move(t);
                }
            }
        }
    }

    template<typename T, comparator_t<T> Comparator>
    const auto& qsort_f = quicksort_w_median<T, Comparator>;

    template<typename T, comparator_t<T> Comparator>
    const auto& insertion_sort_f = insertion_sort<T, Comparator>;

    constexpr int SIZE_LIMIT = 1024;
    inline std::uniform_int_distribution size_dist(0, SIZE_LIMIT);

    constexpr int WARMUP_CYCLES = 1024 * 1024;

    template<typename T, std::derived_from<DataProvider<T>> DP, comparator_t<T> Comparator>
    void _warmup_subcycle(Comparator comp, DP& provider) {
        const int size = size_dist(rng);
        std::vector<T> data = provider.generate_array(DataGenerationType::Random, size);
        T* begin = data.data();
        T* end = data.data() + size - 1;
        qsort_f<T, Comparator>(begin, end, comp);
#ifdef QSORT_BENCH_VALIDATE
        if (const bool check = check_sort(begin, end, comp); !check) {
            std::cout << "Warning: a sort operation was not completed correctly" << std::endl;
        }
#endif // QSORT_BENCH_VALIDATE
    }

    void _warmup() {
        IntDataProvider int_provider{};
        StringDataProvider string_provider{};
        PodmanDataProvider podman_provider{};
        for (int _ = 0; _ < WARMUP_CYCLES; ++_) {
            _warmup_subcycle<int, IntDataProvider>(int_comparator, int_provider);
            _warmup_subcycle<std::string, StringDataProvider>(string_comparator, string_provider);
            _warmup_subcycle<Podman, PodmanDataProvider>(podman_comparator, podman_provider);
        }
    }

    struct BenchmarkResult {
            u64 cycles_int;
            u64 cycles_string;
            u64 cycles_podman;
            u64 cycles_average;
    };

    void add_running_average(u64& dst, const u64& src, u64& rem, const int cycle) {
        const int new_cycle = cycle + 1;

        const u64 val_div = src / new_cycle;
        const u64 val_rem = src % new_cycle;
        const u64 avg_div = dst / new_cycle;
        const u64 avg_rem = dst % new_cycle;

        dst = dst + val_div - avg_div;

        if (rem + val_rem >= avg_rem) {
            const uint64_t total_rem = rem + val_rem - avg_rem;
            dst += total_rem / new_cycle;
            rem = total_rem % new_cycle;
        } else {
            dst -= 1;
            rem = new_cycle + rem + val_rem - avg_rem;
        }
    }

    constexpr int BENCHMARK_CYCLES = 1024 * 256;

    template<typename T, DataProviderType<T> DP, comparator_t<T> Comparator>
    u64 _subbenchmark_insertion_sort(int size, Comparator cmp, DP& provider) {
        std::vector<T> data = provider.generate_array(DataGenerationType::Random, size);

        T* begin = data.data();
        T* end = begin + size - 1;

        const u64 start = __rdtsc();
        insertion_sort_f<T, Comparator>(begin, end, cmp);
#ifdef QSORT_BENCH_VALIDATE
        if (const bool check = check_sort(begin, end, cmp); !check) {
            std::cout << "Warning: a sort operation was not completed correctly" << size << std::endl;
        }
#endif // QSORT_BENCH_VALIDATE
        return __rdtsc() - start;
    }

    BenchmarkResult _benchmark_insertion_sort(const int size) {

        BenchmarkResult result{.cycles_int = 0, .cycles_string = 0, .cycles_podman = 0, .cycles_average = 0};

        u64 irem = 0, srem = 0, prem = 0;

        IntDataProvider int_provider{};
        StringDataProvider string_provider{};
        PodmanDataProvider podman_provider{};

        for (int _ = 0; _ < BENCHMARK_CYCLES; ++_) {
            u64 int_time = _subbenchmark_insertion_sort<int, IntDataProvider>(size, int_comparator, int_provider);
            add_running_average(result.cycles_int, int_time, irem, _);

            u64 string_time =
                _subbenchmark_insertion_sort<std::string, StringDataProvider>(size, string_comparator, string_provider);
            add_running_average(result.cycles_string, string_time, srem, _);

            u64 pod_time =
                _subbenchmark_insertion_sort<Podman, PodmanDataProvider>(size, podman_comparator, podman_provider);
            add_running_average(result.cycles_podman, pod_time, prem, _);
        }

        const u64 hi = (result.cycles_int >> 32) + (result.cycles_string >> 32) + (result.cycles_podman >> 32);
        const u64 lo = hi + (result.cycles_int & 0xffffffff) + (result.cycles_string & 0xffffffff) +
            (result.cycles_podman & 0xffffffff);
        result.cycles_average = 0x55555555 * hi + lo / 3;

        return result;
    }

    template<typename T, DataProviderType<T> DP, comparator_t<T> Comparator>
    u64 _subbenchmark_quicksort(int size, Comparator cmp, DP& provider) {
        std::vector<T> data = provider.generate_array(DataGenerationType::Random, size);

        T* begin = data.data();
        T* end = begin + size - 1;

        const u64 start = __rdtsc();
        qsort_f<T, Comparator>(begin, end, cmp);
#ifdef QSORT_BENCH_VALIDATE
        if (const bool check = check_sort(begin, end, cmp); !check) {
            std::cout << "Warning: a sort operation was not completed correctly" << std::endl;
        }
#endif // QSORT_BENCH_VALIDATE
        return __rdtsc() - start;
    }

    BenchmarkResult _benchmark_quicksort(const int size) {

        BenchmarkResult result{.cycles_int = 0, .cycles_string = 0, .cycles_podman = 0, .cycles_average = 0};

        u64 irem = 0, srem = 0, prem = 0;

        IntDataProvider int_provider{};
        StringDataProvider string_provider{};
        PodmanDataProvider podman_provider{};

        for (int _ = 0; _ < BENCHMARK_CYCLES; ++_) {
            u64 int_time = _subbenchmark_quicksort<int, IntDataProvider>(size, int_comparator, int_provider);
            add_running_average(result.cycles_int, int_time, irem, _);

            u64 string_time =
                _subbenchmark_quicksort<std::string, StringDataProvider>(size, string_comparator, string_provider);
            add_running_average(result.cycles_string, string_time, srem, _);

            u64 pod_time =
                _subbenchmark_quicksort<Podman, PodmanDataProvider>(size, podman_comparator, podman_provider);
            add_running_average(result.cycles_podman, pod_time, prem, _);
        }

        const u64 hi = (result.cycles_int >> 32) + (result.cycles_string >> 32) + (result.cycles_podman >> 32);
        const u64 lo = hi + (result.cycles_int & 0xffffffff) + (result.cycles_string & 0xffffffff) +
            (result.cycles_podman & 0xffffffff);
        result.cycles_average = 0x55555555 * hi + lo / 3;

        return result;
    }

    int benchmark() {
        std::ofstream report("benchmark_report.csv");
        if (!report.good()) {
            std::cout << "Fatal error: report file could not be opened. Session terminated" << std::endl;
            return 1;
        }

        report << "size,insertion_int,insertion_string,insertion_pod,insertion_average,quick_int,quick_string,quick_"
                  "pod,quick_average"
               << std::endl;

        std::cout << "Warming up..." << std::endl;
        _warmup();

        for (int size = 3; size <= 128; ++size) {
            std::cout << "Running benchmark for size=" << size << std::endl;
            const BenchmarkResult insertion_sort_benchmark = _benchmark_insertion_sort(size);
            const BenchmarkResult quicksort_benchmark = _benchmark_quicksort(size);

            report << size << "," << insertion_sort_benchmark.cycles_int << ","
                   << insertion_sort_benchmark.cycles_string << "," << insertion_sort_benchmark.cycles_podman << ","
                   << insertion_sort_benchmark.cycles_average << "," << quicksort_benchmark.cycles_int << ","
                   << quicksort_benchmark.cycles_string << "," << quicksort_benchmark.cycles_podman << ","
                   << quicksort_benchmark.cycles_average << std::endl;

            std::cout << "Insertion sort: "
                      << "int = " << insertion_sort_benchmark.cycles_int << " cycles, "
                      << "string = " << insertion_sort_benchmark.cycles_string << " cycles, "
                      << "pod = " << insertion_sort_benchmark.cycles_podman << " cycles, "
                      << "average = " << insertion_sort_benchmark.cycles_average << " cycles;" << std::endl;

            std::cout << "Quicksort: "
                      << "int = " << quicksort_benchmark.cycles_int << " cycles, "
                      << "string = " << quicksort_benchmark.cycles_string << " cycles, "
                      << "pod = " << quicksort_benchmark.cycles_podman << " cycles, "
                      << "average = " << quicksort_benchmark.cycles_average << " cycles;" << std::endl;
        }

        return 0;
    }
} // namespace

int main() {
    return benchmark();
}
