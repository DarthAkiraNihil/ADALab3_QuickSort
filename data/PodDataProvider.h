//
// Created by EgrZver on 16.11.2026.
//

#ifndef ADALAB3_QUICKSORT_PODDATAPROVIDER_H
#define ADALAB3_QUICKSORT_PODDATAPROVIDER_H

#include <data/DataProvider.h>

struct Podman {
        int key;
        int value;

        explicit Podman(): key(0), value(0) {};
        Podman(const int key, const int value): key(key), value(value) {};
};

class PodmanDataProvider: public DataProvider<Podman> {
    protected:
        std::vector<Podman> generate_random_array(const int size) override {
            std::vector<Podman> result(size);
            for (int i = 0; i < size; i++) {
                result[i] = {data_dist(rng), data_dist(rng)};
            }
            return result;
        }

        std::vector<Podman> generate_same_array(const int size) override {
            const Podman val = {data_dist(rng), data_dist(rng)};
            std::vector<Podman> result(size);
            for (int i = 0; i < size; i++) {
                result[i] = val;
            }
            return result;
        }

        std::vector<Podman> generate_sorted_array(const int size) override {
            Podman val = {data_dist(rng), data_dist(rng)};
            std::vector<Podman> result(size);
            for (int i = 0; i < size; i++) {
                result[i] = val;
                val.key++;
            }
            return result;
        }

        std::vector<Podman> generate_almost_sorted_array(const int size) override {
            std::uniform_int_distribution size_dist(0, size - 1);
            const int pos = size_dist(rng);
            Podman val = {data_dist(rng), data_dist(rng)};
            std::vector<Podman> result(size);
            for (int i = 0; i < size; i++) {
                if (i < pos) {
                    result[i] = val;
                    val.key++;
                } else {
                    result[i] = {data_dist(rng), data_dist(rng)};
                }
            }

            return result;
        }

        std::vector<Podman> generate_reverse_array(const int size) override {
            Podman val = {-data_dist(rng), -data_dist(rng)};
            std::vector<Podman> result(size);
            for (int i = 0; i < size; i++) {
                result[i] = val;
                val.key--;
            }
            return result;
        }

        std::vector<Podman> generate_reserve_almost_sorted_array(const int size) override {
            std::uniform_int_distribution size_dist(0, size - 1);
            const int pos = size_dist(rng);
            Podman val = {data_dist(rng), data_dist(rng)};
            std::vector<Podman> result(size);
            for (int i = 0; i < size; i++) {
                if (i < pos) {
                    result[i] = val;
                    val.key--;
                } else {
                    result[i] = {data_dist(rng), data_dist(rng)};
                }
            }

            return result;
        }

        std::vector<Podman> generate_single_array() override {
            return {{1, 2}};
        }

        std::vector<Podman> generate_pair_array() override {
            if (const int chance = std::abs(data_dist(rng)); chance % 2 == 0) {
                return {{1, 2}, {3, 4}};
            }

            return {{4, 3}, {2, 1}};
        }

        std::vector<Podman> generate_few_unique_array(const int size) override {
            const Podman v1 = {data_dist(rng), data_dist(rng)};
            const Podman v2 = {data_dist(rng), data_dist(rng)};
            const Podman v3 = {data_dist(rng), data_dist(rng)};

            std::vector<Podman> result(size);
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

        std::vector<Podman> generate_sawtooth_array(const int size) override {
            std::uniform_int_distribution size_dist(0, size - 1);
            const int pos = size_dist(rng);
            Podman val = {data_dist(rng), data_dist(rng)};
            std::vector<Podman> result(size);
            for (int i = 0; i < size; i++) {
                result[i] = val;
                if (i < pos) {
                    val.key++;
                } else {
                    val.key--;
                }
            }

            return result;
        }

        std::vector<Podman> generate_negative_and_zero_array(const int size) override {
            std::vector<Podman> result(size);
            for (int i = 0; i < size; i++) {
                if (const int chance = data_dist(rng); chance % 8 == 0) {
                    result[i] = {0, data_dist(rng)};
                } else {
                    result[i] = {data_dist_only_neg(rng), data_dist(rng)};
                }
            }
            return result;
        }

        std::vector<Podman> generate_extreme_values_array(const int size) override {
            std::vector<Podman> result(size);
            for (int i = 0; i < size; i++) {
                if (const int chance = data_dist(rng); chance % 6 == 0) {
                    result[i] = {INT_MIN, data_dist(rng)};
                } else if (chance % 8 == 0) {
                    result[i] = {INT_MAX, data_dist(rng)};
                } else {
                    result[i] = {data_dist(rng), data_dist(rng)};
                }
            }
            return result;
        }

        std::vector<Podman> generate_stability_check_array(const int size) override {
            const int k = data_dist(rng);
            std::vector<Podman> result(size);
            for (int i = 0; i < size; i++) {
                result[i] = {k, data_dist(rng)};
            }
            return result;
        }
};

inline constexpr auto podman_comparator = [](const Podman& a, const Podman& b) { return a.key < b.key; };

#endif // ADALAB3_QUICKSORT_PODDATAPROVIDER_H
