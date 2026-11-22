//
// Created by EgrZver on 06.11.2026.
//

#ifndef ADALAB3_QUICKSORT_QUICKSORT_H
#define ADALAB3_QUICKSORT_QUICKSORT_H
#include <algorithm>
#include <vector>
#include <stack>

constexpr int INSERTION_SORT_LIMIT = 52;

template<typename Comparator, typename T>
concept comparator_t = std::is_invocable_v<Comparator, const T&, const T&> &&
    std::is_same_v<bool, std::invoke_result_t<Comparator, const T&, const T&>>;

namespace qsort_internal {

    template<typename T, comparator_t<T> Comparator>
    bool _eq(T* a, T* b, Comparator c) {
        return !(c(*a, *b)) && !(c(*b, *a));
    }

    template<typename T, comparator_t<T> Comparator>

    // a - first, b - mid, c - last
    // a < b => a != b
    // b < a => a != b
    // a <= b <= c, comp(a, b) = a < b, !comp(a, b) = a >= b
    T* median(T* a, T* b, T* c, Comparator comp) {
        if (_eq(a, b, comp) && _eq(b, c, comp)) {
            return b;
        }

        if ((_eq(a, b, comp) && !_eq(b, c, comp)) || (!_eq(a, b, comp) && _eq(b, c, comp))) {
            return b;
        }

        if (_eq(a, c, comp) && !_eq(b, c, comp)) {
            T t = std::move(*c);
            *c = std::move(*b);
            *b = std::move(t);
            return b;
        }

        if ((comp(*a, *b) && comp(*b, *c)) || (comp(*c, *b) && comp(*b, *a))) {
            return b;
        }

        if ((comp(*b, *a) && comp(*a, *c)) || (comp(*c, *a) && comp(*a, *b))) {
            return a;
        }

        return c;
    }

    template<typename T, comparator_t<T> Comparator>
    T* partition(T* first, T* last, Comparator comp) {
        const int l = last - first + 1;
        T* mid = first + l / 2;
        T pivot = *mid; // qsort_internal::median(first, mid, last, comp);

        T* i = first - 1;
        T* j = last + 1;
        while (true) {
            ++i;
            --j;

            while (comp(*i, pivot)) {
                ++i;
            }
            while (comp(pivot, *j)) {
                --j;
            }

            if (i >= j) {
                return j;
            }

            T t = std::move(*j);
            *j = std::move(*i);
            *i = std::move(t);
        }
    }

    template<typename T, comparator_t<T> Comparator>
    T* median_based_partition(T* first, T* last, Comparator comp) {
        const int l = last - first + 1;
        T* mid = first + l / 2;
        T pivot = *qsort_internal::median(first, mid, last, comp);

        T* i = first - 1;
        T* j = last + 1;
        while (true) {
            ++i;
            --j;

            while (comp(*i, pivot)) {
                ++i;
            }
            while (comp(pivot, *j)) {
                --j;
            }

            if (i >= j) {
                return j;
            }

            if constexpr (std::is_move_constructible_v<T> && std::is_move_assignable_v<T>) {
                T t = std::move(*j);
                *j = std::move(*i);
                *i = std::move(t);
            } else {
                T t(*j);
                *j = *i;
                *i = *t;
            }
        }
    }

    template<typename T, comparator_t<T> Comparator>
    void ins_sort(T* begin, T* end, Comparator cmp) {
        if (end - begin + 1 <= 1) {
            return;
        }

        for (T* i = begin; i != end; ++i) {
            for (T* j = i + 1; j != end + 1; ++j) {
                if (!cmp(*j, *i)) {
                    continue;
                }

                if constexpr (std::is_move_constructible_v<T> && std::is_move_assignable_v<T>) {
                    T t = std::move(*i);
                    *i = std::move(*j);
                    *j = std::move(t);
                } else {
                    T t(*i);
                    *i = *j;
                    *j = *t;
                }
            }
        }
    }
} // namespace qsort_internal

// comp = a < b
template<typename T, comparator_t<T> Comparator>
void quicksort_ugly(T* first, T* last, Comparator comp) {
    const int l = last - first + 1;
    if (l < 2) {
        return;
    }

    if (l == 2) {
        if (comp(*last, *first)) {
            T t = std::move(*first);
            *first = std::move(*last);
            *last = std::move(t);
        }

        return;
    }

    T* pivot = qsort_internal::partition(first, last, comp);
    quicksort_ugly(first, pivot, comp);
    quicksort_ugly(pivot + 1, last, comp);
}

// comp = a < b
template<typename T, comparator_t<T> Comparator>
void quicksort_w_iteration(T* first, T* last, Comparator comp) {
    const int l = last - first + 1;
    if (l < 2) {
        return;
    }

    if (l == 2) {
        if (comp(*last, *first)) {
            T t = std::move(*first);
            *first = std::move(*last);
            *last = std::move(t);
        }

        return;
    }

    T* pivot = qsort_internal::partition(first, last, comp);

    const int first_interval_length = pivot - first + 1;
    const int last_interval_length = last - pivot;

    T* recursive_begin = first_interval_length < last_interval_length ? first : pivot + 1;
    T* recursive_end = first_interval_length < last_interval_length ? pivot : last;
    T* iterative_begin = first_interval_length < last_interval_length ? pivot + 1 : first;
    T* iterative_end = first_interval_length < last_interval_length ? last : pivot;

    // do iteration sort
    std::stack<T*> stack;
    stack.push(iterative_begin);
    stack.push(iterative_end);

    while (!stack.empty()) { ///
        T* la = stack.top();
        stack.pop();
        T* fi = stack.top();
        stack.pop();

        const int li = la - fi + 1;
        if (li < 2) {
            continue;
        }

        if (li == 2) {
            if (comp(*la, *fi)) {
                T t = std::move(*fi);
                *fi = std::move(*la);
                *la = std::move(t);
            }

            continue;
        }

        T* pi = qsort_internal::partition(fi, la, comp);

        stack.push(fi);
        stack.push(pi);
        stack.push(pi + 1);
        stack.push(la);
    }

    // quicksort(iterative_begin, iterative_end, comp);
    quicksort(recursive_begin, recursive_end, comp);
}

// comp = a < b
template<typename T, comparator_t<T> Comparator>
void quicksort_w_median(T* first, T* last, Comparator comp) {
    const int l = last - first + 1;
    if (l < 2) {
        return;
    }

    if (l == 2) {
        if (comp(*last, *first)) {
            T t = std::move(*first);
            *first = std::move(*last);
            *last = std::move(t);
        }

        return;
    }

    T* pivot = qsort_internal::median_based_partition(first, last, comp);

    const int first_interval_length = pivot - first + 1;
    const int last_interval_length = last - pivot;

    T* recursive_begin = first_interval_length < last_interval_length ? first : pivot + 1;
    T* recursive_end = first_interval_length < last_interval_length ? pivot : last;
    T* iterative_begin = first_interval_length < last_interval_length ? pivot + 1 : first;
    T* iterative_end = first_interval_length < last_interval_length ? last : pivot;

    // do iteration sort
    std::stack<T*> stack;
    stack.push(iterative_begin);
    stack.push(iterative_end);

    while (!stack.empty()) { ///
        T* la = stack.top();
        stack.pop();
        T* fi = stack.top();
        stack.pop();

        const int li = la - fi + 1;
        if (li < 2) {
            continue;
        }

        if (li == 2) {
            if (comp(*la, *fi)) {
                T t = std::move(*fi);
                *fi = std::move(*la);
                *la = std::move(t);
            }

            continue;
        }

        T* pi = qsort_internal::median_based_partition(fi, la, comp);

        stack.push(fi);
        stack.push(pi);
        stack.push(pi + 1);
        stack.push(la);
    }

    // quicksort(iterative_begin, iterative_end, comp);
    quicksort(recursive_begin, recursive_end, comp);
}

// comp = a < b
template<typename T, comparator_t<T> Comparator>
void quicksort_fake_recursion_elimitaion(T* first, T* last, Comparator comp) {
    if (last - first + 1 < INSERTION_SORT_LIMIT) {
        qsort_internal::ins_sort(first, last, comp);
        return;
    }

    T* pivot = qsort_internal::median_based_partition(first, last, comp);

    const int first_interval_length = pivot - first + 1;
    const int last_interval_length = last - pivot;

    T* recursive_begin = first_interval_length < last_interval_length ? first : pivot + 1;
    T* recursive_end = first_interval_length < last_interval_length ? pivot : last;
    T* iterative_begin = first_interval_length < last_interval_length ? pivot + 1 : first;
    T* iterative_end = first_interval_length < last_interval_length ? last : pivot;

    // do iteration sort
    std::vector<T*> stack;
    stack.reserve(iterative_end - iterative_begin + 1);
    stack.push_back(iterative_begin);
    stack.push_back(iterative_end);

    while (!stack.empty()) {
        T* la = stack.back();
        stack.pop_back();
        T* fi = stack.back();
        stack.pop_back();

        if (la - fi + 1 < INSERTION_SORT_LIMIT) {
            qsort_internal::ins_sort(fi, la, comp);
            continue;
        }

        T* pi = qsort_internal::median_based_partition(fi, la, comp);

        stack.push_back(fi);
        stack.push_back(pi);
        stack.push_back(pi + 1);
        stack.push_back(la);
    }

    // quicksort(iterative_begin, iterative_end, comp);
    quicksort_fake_recursion_elimitaion(recursive_begin, recursive_end, comp);
}

// comp = a < b
template<typename T, comparator_t<T> Comparator>
void quicksort(T* first, T* last, Comparator comp) {
    while (first < last) {
        if (last - first + 1 < INSERTION_SORT_LIMIT) {
            qsort_internal::ins_sort(first, last, comp);
            return;
        }

        T* pivot = qsort_internal::median_based_partition(first, last, comp);
        if (pivot - first + 1 < last - pivot) {
            quicksort(first, pivot, comp);
            first = pivot + 1;
        } else {
            quicksort(pivot + 1, last, comp);
            last = pivot;
        }
    }
}

#endif // ADALAB3_QUICKSORT_QUICKSORT_H
