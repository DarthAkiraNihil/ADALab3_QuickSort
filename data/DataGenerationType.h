//
// Created by EgrZver on 16.11.2026.
//

#ifndef ADALAB3_QUICKSORT_DATAGENERATIONTYPE_H
#define ADALAB3_QUICKSORT_DATAGENERATIONTYPE_H

enum class DataGenerationType {
    Random,
    AllIsTheSame,

    Sorted,
    AlmostSorted,
    Reverse,
    ReverseAlmostSorted,

    Empty,
    Single,
    Pair,

    FewUnique,
    SawTooth,

    NegativeAndZero, // only ints
    ExtremeValues,
    StabilityCheck,
};

#endif // ADALAB3_QUICKSORT_DATAGENERATIONTYPE_H
