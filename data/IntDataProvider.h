//
// Created by EgrZver on 16.11.2026.
//

#ifndef ADALAB3_QUICKSORT_INTDATAPROVIDER_H
#define ADALAB3_QUICKSORT_INTDATAPROVIDER_H

#include <data/DataProvider.h>

class IntDataProvider: public DataProvider<int> {
    protected:
        std::vector<int> generate_random_array(const int size) override {
            std::vector<int> result(size);
            for (int i = 0; i < size; i++) {
                result[i] = data_dist(rng);
            }
            return result;
        }

        std::vector<int> generate_same_array(const int size) override {
            const int val = data_dist(rng);
            std::vector<int> result(size);
            for (int i = 0; i < size; i++) {
                result[i] = val;
            }
            return result;
        }

        std::vector<int> generate_sorted_array(const int size) override {
            int val = data_dist(rng);
            std::vector<int> result(size);
            for (int i = 0; i < size; i++) {
                result[i] = val++;
            }
            return result;
        }

        std::vector<int> generate_almost_sorted_array(const int size) override {
            std::uniform_int_distribution size_dist(0, size - 1);
            const int pos = size_dist(rng);
            int val = data_dist(rng);
            std::vector<int> result(size);
            for (int i = 0; i < size; i++) {
                if (i < pos) {
                    result[i] = val++;
                } else {
                    result[i] = data_dist(rng);
                }
            }

            return result;
        }

        std::vector<int> generate_reverse_array(const int size) override {
            int val = -data_dist(rng);
            std::vector<int> result(size);
            for (int i = 0; i < size; i++) {
                result[i] = val--;
            }
            return result;
        }

        std::vector<int> generate_reserve_almost_sorted_array(const int size) override {
            std::uniform_int_distribution size_dist(0, size - 1);
            const int pos = size_dist(rng);
            int val = data_dist(rng);
            std::vector<int> result(size);
            for (int i = 0; i < size; i++) {
                if (i < pos) {
                    result[i] = val--;
                } else {
                    result[i] = data_dist(rng);
                }
            }

            return result;
        }

        std::vector<int> generate_single_array() override {
            return {1};
        }

        std::vector<int> generate_pair_array() override {
            if (const int chance = std::abs(data_dist(rng)); chance % 2 == 0) {
                return {1, 2};
            }

            return {2, 1};
        }

        std::vector<int> generate_few_unique_array(const int size) override {
            const int v1 = data_dist(rng);
            const int v2 = data_dist(rng);
            const int v3 = data_dist(rng);

            std::vector<int> result(size);
            for (int i = 0; i < size; i++) {
                switch (const int chance = data_dist(rng); chance % 3) {
                    case 0: {
                        result[i] = v1;
                        break;
                    }
                    case 1: {
                        result[i] = v2;
                        break;
                    }
                    case 2: {
                        result[i] = v3;
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }

            return result;
        }

        std::vector<int> generate_sawtooth_array(const int size) override {
            std::uniform_int_distribution size_dist(0, size - 1);
            const int pos = size_dist(rng);
            int val = data_dist(rng);
            std::vector<int> result(size);
            for (int i = 0; i < size; i++) {
                if (i < pos) {
                    result[i] = val++;
                } else {
                    result[i] = val--;
                }
            }

            return result;
        }

        std::vector<int> generate_negative_and_zero_array(const int size) override {
            std::vector<int> result(size);
            for (int i = 0; i < size; i++) {
                if (const int chance = data_dist(rng); chance % 8 == 0) {
                    result[i] = 0;
                } else {
                    result[i] = data_dist_only_neg(rng);
                }
            }
            return result;
        }

        std::vector<int> generate_extreme_values_array(const int size) override {
            std::vector<int> result(size);
            for (int i = 0; i < size; i++) {
                if (const int chance = data_dist(rng); chance % 6 == 0) {
                    result[i] = INT_MIN;
                } else if (chance % 8 == 0) {
                    result[i] = INT_MAX;
                } else {
                    result[i] = data_dist_only_neg(rng);
                }
            }
            return result;
        }

        std::vector<int> generate_stability_check_array(const int size) override {
            return generate_few_unique_array(size);
        }
};

inline constexpr auto int_comparator = [](const int a, const int b) { return a < b; };

#endif // ADALAB3_QUICKSORT_INTDATAPROVIDER_H
