//
// Created by EgrZver on 14.11.2026.
//

#include <gtest/gtest.h>
#include <quicksort.h>
#include "TestUtils.h"

#include <data/IntDataProvider.h>

TEST(QuickSortTests_Ints, TestsWithRandom) {
    run_test<int, IntDataProvider>(DataGenerationType::Random, int_comparator);
}

TEST(QuickSortTests_Ints, TestsWithAllIsTheSame) {
    run_test<int, IntDataProvider>(DataGenerationType::AllIsTheSame, int_comparator);
}

TEST(QuickSortTests_Ints, TestsWithSorted) {
    run_test<int, IntDataProvider>(DataGenerationType::Sorted, int_comparator);
}

TEST(QuickSortTests_Ints, TestsWithAlmostSorted) {
    run_test<int, IntDataProvider>(DataGenerationType::AlmostSorted, int_comparator);
}

TEST(QuickSortTests_Ints, TestsWithReverse) {
    run_test<int, IntDataProvider>(DataGenerationType::Reverse, int_comparator);
}

TEST(QuickSortTests_Ints, TestsWithReverseAlmostSorted) {
    run_test<int, IntDataProvider>(DataGenerationType::ReverseAlmostSorted, int_comparator);
}

TEST(QuickSortTests_Ints, TestsWithEmpty) {
    run_test<int, IntDataProvider>(DataGenerationType::Empty, int_comparator);
}

TEST(QuickSortTests_Ints, TestsWithSingle) {
    run_test<int, IntDataProvider>(DataGenerationType::Single, int_comparator);
}
TEST(QuickSortTests_Ints, TestsWithPair) {
    run_test<int, IntDataProvider>(DataGenerationType::Pair, int_comparator);
}

TEST(QuickSortTests_Ints, TestsWithFewUnique) {
    run_test<int, IntDataProvider>(DataGenerationType::FewUnique, int_comparator);
}

TEST(QuickSortTests_Ints, TestsWithSawTooth) {
    run_test<int, IntDataProvider>(DataGenerationType::SawTooth, int_comparator);
}

TEST(QuickSortTests_Ints, TestsWithNegativeAndZero) {
    run_test<int, IntDataProvider>(DataGenerationType::NegativeAndZero, int_comparator);
}

TEST(QuickSortTests_Ints, TestsWithExtremeValues) {
    run_test<int, IntDataProvider>(DataGenerationType::ExtremeValues, int_comparator);
}

TEST(QuickSortTests_Ints, TestsWithStabilityCheck) {
    run_test<int, IntDataProvider>(DataGenerationType::StabilityCheck, int_comparator);
}

TEST(QuickSortTestsWithBIGData_Ints, TestsWithRandom) {
    run_test<int, IntDataProvider>(DataGenerationType::Random, int_comparator, true);
}

TEST(QuickSortTestsWithBIGData_Ints, TestsWithAllIsTheSame) {
    run_test<int, IntDataProvider>(DataGenerationType::AllIsTheSame, int_comparator, true);
}

TEST(QuickSortTestsWithBIGData_Ints, TestsWithSorted) {
    run_test<int, IntDataProvider>(DataGenerationType::Sorted, int_comparator, true);
}

TEST(QuickSortTestsWithBIGData_Ints, TestsWithAlmostSorted) {
    run_test<int, IntDataProvider>(DataGenerationType::AlmostSorted, int_comparator, true);
}

TEST(QuickSortTestsWithBIGData_Ints, TestsWithReverse) {
    run_test<int, IntDataProvider>(DataGenerationType::Reverse, int_comparator, true);
}

TEST(QuickSortTestsWithBIGData_Ints, TestsWithReverseAlmostSorted) {
    run_test<int, IntDataProvider>(DataGenerationType::ReverseAlmostSorted, int_comparator, true);
}

TEST(QuickSortTestsWithBIGData_Ints, TestsWithEmpty) {
    run_test<int, IntDataProvider>(DataGenerationType::Empty, int_comparator, true);
}

TEST(QuickSortTestsWithBIGData_Ints, TestsWithSingle) {
    run_test<int, IntDataProvider>(DataGenerationType::Single, int_comparator, true);
}
TEST(QuickSortTestsWithBIGData_Ints, TestsWithPair) {
    run_test<int, IntDataProvider>(DataGenerationType::Pair, int_comparator, true);
}

TEST(QuickSortTestsWithBIGData_Ints, TestsWithFewUnique) {
    run_test<int, IntDataProvider>(DataGenerationType::FewUnique, int_comparator, true);
}

TEST(QuickSortTestsWithBIGData_Ints, TestsWithSawTooth) {
    run_test<int, IntDataProvider>(DataGenerationType::SawTooth, int_comparator, true);
}

TEST(QuickSortTestsWithBIGData_Ints, TestsWithNegativeAndZero) {
    run_test<int, IntDataProvider>(DataGenerationType::NegativeAndZero, int_comparator, true);
}

TEST(QuickSortTestsWithBIGData_Ints, TestsWithExtremeValues) {
    run_test<int, IntDataProvider>(DataGenerationType::ExtremeValues, int_comparator, true);
}

TEST(QuickSortTestsWithBIGData_Ints, TestsWithStabilityCheck) {
    run_test<int, IntDataProvider>(DataGenerationType::StabilityCheck, int_comparator, true);
}
