//
// Created by EgrZver on 15.11.2026.
//

#include <data/PodDataProvider.h>
#include <gtest/gtest.h>
#include <quicksort.h>
#include "TestUtils.h"

TEST(QuickSortTests_Pod, TestsWithRandom) {
    run_test<Podman, PodmanDataProvider>(DataGenerationType::Random, podman_comparator);
}

TEST(QuickSortTests_Pod, TestsWithAllIsTheSame) {
    run_test<Podman, PodmanDataProvider>(DataGenerationType::AllIsTheSame, podman_comparator);
}

TEST(QuickSortTests_Pod, TestsWithSorted) {
    run_test<Podman, PodmanDataProvider>(DataGenerationType::Sorted, podman_comparator);
}

TEST(QuickSortTests_Pod, TestsWithAlmostSorted) {
    run_test<Podman, PodmanDataProvider>(DataGenerationType::AlmostSorted, podman_comparator);
}

TEST(QuickSortTests_Pod, TestsWithReverse) {
    run_test<Podman, PodmanDataProvider>(DataGenerationType::Reverse, podman_comparator);
}

TEST(QuickSortTests_Pod, TestsWithReverseAlmostSorted) {
    run_test<Podman, PodmanDataProvider>(DataGenerationType::ReverseAlmostSorted, podman_comparator);
}

TEST(QuickSortTests_Pod, TestsWithEmpty) {
    run_test<Podman, PodmanDataProvider>(DataGenerationType::Empty, podman_comparator);
}

TEST(QuickSortTests_Pod, TestsWithSingle) {
    run_test<Podman, PodmanDataProvider>(DataGenerationType::Single, podman_comparator);
}
TEST(QuickSortTests_Pod, TestsWithPair) {
    run_test<Podman, PodmanDataProvider>(DataGenerationType::Pair, podman_comparator);
}

TEST(QuickSortTests_Pod, TestsWithFewUnique) {
    run_test<Podman, PodmanDataProvider>(DataGenerationType::FewUnique, podman_comparator);
}

TEST(QuickSortTests_Pod, TestsWithSawTooth) {
    run_test<Podman, PodmanDataProvider>(DataGenerationType::SawTooth, podman_comparator);
}

TEST(QuickSortTests_Pod, TestsWithNegativeAndZero) {
    run_test<Podman, PodmanDataProvider>(DataGenerationType::NegativeAndZero, podman_comparator);
}

TEST(QuickSortTests_Pod, TestsWithExtremeValues) {
    run_test<Podman, PodmanDataProvider>(DataGenerationType::ExtremeValues, podman_comparator);
}

TEST(QuickSortTests_Pod, TestsWithStabilityCheck) {
    run_test<Podman, PodmanDataProvider>(DataGenerationType::StabilityCheck, podman_comparator);
}
