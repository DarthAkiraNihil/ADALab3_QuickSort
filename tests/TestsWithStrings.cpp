//
// Created by EgrZver on 15.11.2026.
//

#include <data/StringDataProvider.h>
#include <gtest/gtest.h>
#include <quicksort.h>
#include "TestUtils.h"

TEST(QuickSortTests_Strings, TestsWithRandom) {
    run_test<std::string, StringDataProvider>(DataGenerationType::Random, string_comparator);
}

TEST(QuickSortTests_Strings, TestsWithAllIsTheSame) {
    run_test<std::string, StringDataProvider>(DataGenerationType::AllIsTheSame, string_comparator);
}

TEST(QuickSortTests_Strings, TestsWithSorted) {
    run_test<std::string, StringDataProvider>(DataGenerationType::Sorted, string_comparator);
}

TEST(QuickSortTests_Strings, TestsWithAlmostSorted) {
    run_test<std::string, StringDataProvider>(DataGenerationType::AlmostSorted, string_comparator);
}

TEST(QuickSortTests_Strings, TestsWithReverse) {
    run_test<std::string, StringDataProvider>(DataGenerationType::Reverse, string_comparator);
}

TEST(QuickSortTests_Strings, TestsWithReverseAlmostSorted) {
    run_test<std::string, StringDataProvider>(DataGenerationType::ReverseAlmostSorted, string_comparator);
}

TEST(QuickSortTests_Strings, TestsWithEmpty) {
    run_test<std::string, StringDataProvider>(DataGenerationType::Empty, string_comparator);
}

TEST(QuickSortTests_Strings, TestsWithSingle) {
    run_test<std::string, StringDataProvider>(DataGenerationType::Single, string_comparator);
}
TEST(QuickSortTests_Strings, TestsWithPair) {
    run_test<std::string, StringDataProvider>(DataGenerationType::Pair, string_comparator);
}

TEST(QuickSortTests_Strings, TestsWithFewUnique) {
    run_test<std::string, StringDataProvider>(DataGenerationType::FewUnique, string_comparator);
}

TEST(QuickSortTests_Strings, TestsWithSawTooth) {
    run_test<std::string, StringDataProvider>(DataGenerationType::SawTooth, string_comparator);
}

TEST(QuickSortTests_Strings, TestsWithStabilityCheck) {
    run_test<std::string, StringDataProvider>(DataGenerationType::StabilityCheck, string_comparator);
}
