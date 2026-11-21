//
// Created by EgrZver on 16.11.2026.
//

#ifndef ADALAB3_QUICKSORT_DATAPROVIDER_H
#define ADALAB3_QUICKSORT_DATAPROVIDER_H

#include <data/DataGenerationType.h>
#include <random>
#include <vector>

constexpr int MIN_GENERATION_INT = -65536;
constexpr int MAX_GENERATION_INT = 65535;
constexpr int GENERATED_STRING_SIZE = 32;

inline std::random_device dev;
inline std::mt19937 rng(dev());
inline std::uniform_int_distribution data_dist(MIN_GENERATION_INT, MAX_GENERATION_INT);
inline std::uniform_int_distribution data_dist_only_neg(MIN_GENERATION_INT, 0);

template<typename T>
class DataProvider {
    public:
        std::vector<T> generate_array(const DataGenerationType type, const int size) {
            switch (type) {
                case DataGenerationType::Random: {
                    return this->generate_random_array(size);
                }
                case DataGenerationType::AllIsTheSame: {
                    return this->generate_same_array(size);
                }
                case DataGenerationType::Sorted: {
                    return this->generate_sorted_array(size);
                }
                case DataGenerationType::AlmostSorted: {
                    return this->generate_almost_sorted_array(size);
                }
                case DataGenerationType::Reverse: {
                    return this->generate_reverse_array(size);
                }
                case DataGenerationType::ReverseAlmostSorted: {
                    return this->generate_reserve_almost_sorted_array(size);
                }
                case DataGenerationType::Empty: {
                    return {};
                }
                case DataGenerationType::Single: {
                    return this->generate_single_array();
                }
                case DataGenerationType::Pair: {
                    return this->generate_pair_array();
                }
                case DataGenerationType::FewUnique: {
                    return this->generate_few_unique_array(size);
                }
                case DataGenerationType::SawTooth: {
                    return this->generate_sawtooth_array(size);
                }
                case DataGenerationType::NegativeAndZero: {
                    return this->generate_negative_and_zero_array(size);
                }
                case DataGenerationType::ExtremeValues: {
                    return this->generate_extreme_values_array(size);
                }
                case DataGenerationType::StabilityCheck: {
                    return this->generate_stability_check_array(size);
                }
                default: {
                    return {};
                }
            }
        }

        virtual ~DataProvider() = default;

    protected:
        virtual std::vector<T> generate_random_array(int size) = 0;
        virtual std::vector<T> generate_same_array(int size) = 0;
        virtual std::vector<T> generate_sorted_array(int size) = 0;
        virtual std::vector<T> generate_almost_sorted_array(int size) = 0;
        virtual std::vector<T> generate_reverse_array(int size) = 0;
        virtual std::vector<T> generate_reserve_almost_sorted_array(int size) = 0;
        virtual std::vector<T> generate_single_array() = 0;
        virtual std::vector<T> generate_pair_array() = 0;
        virtual std::vector<T> generate_few_unique_array(int size) = 0;
        virtual std::vector<T> generate_sawtooth_array(int size) = 0;
        virtual std::vector<T> generate_negative_and_zero_array(int size) = 0;
        virtual std::vector<T> generate_extreme_values_array(int size) = 0;
        virtual std::vector<T> generate_stability_check_array(int size) = 0;
};

#endif // ADALAB3_QUICKSORT_DATAPROVIDER_H
