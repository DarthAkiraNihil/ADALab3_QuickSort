cmake_minimum_required(VERSION 4.3)
project(ADALab3_QuickSort)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -Wl,--whole-archive -lwinpthread -Wl,--no-whole-archive")


include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    ADALab3_QuickSort_Benchmark
        benchmark.cpp
        data/DataProvider.h
        data/StringDataProvider.h
        data/IntDataProvider.h
        data/PodDataProvider.h
        data/DataGenerationType.h
)
add_executable(
    ADALab3_QuickSort_StrictBenchmark
        benchmark.cpp
        data/DataProvider.h
        data/StringDataProvider.h
        data/IntDataProvider.h
        data/PodDataProvider.h
        data/DataGenerationType.h
)


add_executable(
    ADALab3_QuickSort_Tests
    quicksort.h
    tests/TestsWithInts.cpp
    tests/TestsWithStrings.cpp
    tests/TestUtils.h
        tests/TestsWithPods.cpp
        data/DataProvider.h
)

target_link_libraries(
    ADALab3_QuickSort_Tests
    GTest::gtest_main
)

target_include_directories(ADALab3_QuickSort_Tests PRIVATE "${CMAKE_SOURCE_DIR}")
target_include_directories(ADALab3_QuickSort_Benchmark PRIVATE "${CMAKE_SOURCE_DIR}")
target_include_directories(ADALab3_QuickSort_StrictBenchmark PRIVATE "${CMAKE_SOURCE_DIR}")

target_compile_definitions(ADALab3_QuickSort_StrictBenchmark PUBLIC QSORT_BENCH_VALIDATE)

include(GoogleTest)
#gtest_add_tests(TARGET ADALab3_QuickSort_Tests)
gtest_discover_tests(ADALab3_QuickSort_Tests)
