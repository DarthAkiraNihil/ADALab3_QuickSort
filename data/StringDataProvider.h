//
// Created by EgrZver on 16.11.2026.
//

#ifndef ADALAB3_QUICKSORT_STRINGDATAPROVIDER_H
#define ADALAB3_QUICKSORT_STRINGDATAPROVIDER_H

#include <data/DataProvider.h>

class StringDataProvider: public DataProvider<std::string> {
    private:
        static std::string gen_random_string(const int len) {

            // TODO: better random
            static constexpr char alphanum[] = "0123456789"
                                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                               "abcdefghijklmnopqrstuvwxyz"
                                               "!@#$%^&*()_[]{}<>,.";
            std::string tmp_s;
            tmp_s.reserve(len);

            for (int i = 0; i < len; ++i) {
                tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
            }

            return tmp_s;
        }

    protected:
        std::vector<std::string> generate_random_array(const int size) override {
            std::vector<std::string> result(size);
            for (int i = 0; i < size; i++) {
                result[i] = StringDataProvider::gen_random_string(GENERATED_STRING_SIZE);
            }
            return result;
        }

        std::vector<std::string> generate_same_array(const int size) override {
            const std::string val = StringDataProvider::gen_random_string(GENERATED_STRING_SIZE);
            std::vector<std::string> result(size);
            for (int i = 0; i < size; i++) {
                result[i] = val;
            }
            return result;
        }

        std::vector<std::string> generate_sorted_array(const int size) override {
            std::string val = {GENERATED_STRING_SIZE, ' '};
            std::vector<std::string> result(size);
            for (int i = 0; i < size; i++) {
                result[i] = val;
                val.at(val.size() - 1)++;
                int j = static_cast<int>(val.size()) - 1;
                while (j > 0 && val.at(j) > 0x7e) {
                    val.at(j) = ' ';
                    val.at(j - 1)++;
                    j--;
                }
            }
            return result;
        }

        std::vector<std::string> generate_almost_sorted_array(const int size) override {
            std::uniform_int_distribution size_dist(0, size - 1);
            const int pos = size_dist(rng);
            std::string val = {GENERATED_STRING_SIZE, ' '};
            std::vector<std::string> result(size);
            for (int i = 0; i < size; i++) {
                if (i < pos) {
                    result[i] = val;
                    val.at(val.size() - 1)++;
                    int j = static_cast<int>(val.size()) - 1;
                    while (j > 0 && val.at(j) > 0x7e) {
                        val.at(j) = ' ';
                        val.at(j - 1)++;
                        j--;
                    }
                } else {
                    result[i] = StringDataProvider::gen_random_string(GENERATED_STRING_SIZE);
                }
            }

            return result;
        }

        std::vector<std::string> generate_reverse_array(const int size) override {
            std::string val = {GENERATED_STRING_SIZE, 0x7E};
            std::vector<std::string> result(size);
            for (int i = 0; i < size; i++) {
                result[i] = val;
                val.at(0)--;
                int j = 0;
                while (j < val.size() - 1 && val.at(j) < ' ') {
                    val.at(j) = 0x7E;
                    val.at(j + 1)--;
                    j++;
                }
            }
            return result;
        }

        std::vector<std::string> generate_reserve_almost_sorted_array(const int size) override {
            std::uniform_int_distribution size_dist(0, size - 1);
            const int pos = size_dist(rng);
            std::string val = {GENERATED_STRING_SIZE, 0x7E};
            std::vector<std::string> result(size);
            for (int i = 0; i < size; i++) {
                if (i < pos) {
                    result[i] = val;
                    val.at(0)--;
                    int j = 0;
                    while (j < val.size() - 1 && val.at(j) < ' ') {
                        val.at(j) = 0x7E;
                        val.at(j + 1)--;
                        j++;
                    }
                } else {
                    result[i] = StringDataProvider::gen_random_string(GENERATED_STRING_SIZE);
                }
            }

            return result;
        }

        std::vector<std::string> generate_single_array() override {
            return {"Aboba"};
        }

        std::vector<std::string> generate_pair_array() override {
            if (const int chance = std::abs(data_dist(rng)); chance % 2 == 0) {
                return {"ab", "ba"};
            }

            return {"ba", "ab"};
        }

        std::vector<std::string> generate_few_unique_array(const int size) override {
            const std::string v1 = StringDataProvider::gen_random_string(GENERATED_STRING_SIZE);
            const std::string v2 = StringDataProvider::gen_random_string(GENERATED_STRING_SIZE);
            const std::string v3 = StringDataProvider::gen_random_string(GENERATED_STRING_SIZE);

            std::vector<std::string> result(size);
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

        std::vector<std::string> generate_sawtooth_array(const int size) override {
            std::uniform_int_distribution size_dist(0, size - 1);
            const int pos = size_dist(rng);
            std::string val = {GENERATED_STRING_SIZE, ' '};
            std::vector<std::string> result(size);
            for (int i = 0; i < size; i++) {
                result[i] = val;
                if (i < pos) {
                    val.at(val.size() - 1)++;
                    int j = static_cast<int>(val.size()) - 1;
                    while (j > 0 && val.at(j) > 0x7e) {
                        val.at(j) = ' ';
                        val.at(j - 1)++;
                        j--;
                    }
                } else {
                    val.at(0)--;
                    int j = 0;
                    while (j < val.size() - 1 && val.at(j) < ' ') {
                        val.at(j) = 0x7E;
                        val.at(j + 1)--;
                        j++;
                    }
                }
            }

            return result;
        }

        std::vector<std::string> generate_negative_and_zero_array(const int size) override {
            return {}; // not tested
        }

        std::vector<std::string> generate_extreme_values_array(const int size) override {
            return {}; // not tested
        }

        std::vector<std::string> generate_stability_check_array(const int size) override {
            return generate_few_unique_array(size);
        }
};

inline constexpr auto string_comparator = [](const std::string& a, const std::string& b) { return a < b; };

#endif // ADALAB3_QUICKSORT_STRINGDATAPROVIDER_H
