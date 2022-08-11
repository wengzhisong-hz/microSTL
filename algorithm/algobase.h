#ifndef MICROSTL_ALGOBASE_H
#define MICROSTL_ALGOBASE_H

#include "../iterator/iterator.h"
#include "../iterator/iterator_traits.h"
#include "../iterator/type_traits.h"

namespace MicroSTL {
    // --------------------- fill_n --------------------------

    template<typename OutputIterator, typename Size, typename T>
    OutputIterator fill_n(OutputIterator first, Size n, const T &value) {
        for (; n > 0; --n, ++first) {
            *first = value;
        }
        return first;
    }

    // --------------------- fill --------------------------

    template<typename ForwardIterator, typename T>
    void fill(ForwardIterator first, ForwardIterator last, const T &value) {
        for (; first != last; ++first) {
            *first = value;
        }
    }


    /**
     * copy()方法会根据迭代器类型采取不同的策略：
     * - char* wchar_t*：采用memmove
     * - InputIterator：
     *      - 如果是（可强化为）RandomAccessIterator：采取distance > 0来判断是否结束
     *      - 如果不能，则采取 first != last 的方式判断是否结束
     * - T*：
     *      - 如果 has_trivial_assignment_operator 为 false type，则使用 RandomAccessIterator 的方式
     *      - 如果 has_trivial_assignment_operator 为 true type，则直接使用 memmove
     * - (const T*, T*) 同 T*
     *
     * 综上，copy尽可能的采用 memmove的方式进行复制，
     * 如果不能的话，判断迭代器是否为RandomAccessIterator，是的话则采用 (distance = last - first; distance > 0; distance--) 的方式进行迭代；
     * 实在不行，则使用 (;first != last; ++first)的方式进行比较
     */

    // --------------------- copy --------------------------

    template<typename RandomAccessIterator, typename OutputIterator, typename Distance>
    inline OutputIterator
    _copy_d(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, Distance *) {
        for (Distance distance = last - first; distance > 0; --distance, ++result, ++first) {
            *result = *first;
        }
        return result;
    }

    template<typename T>
    inline T *
    _copy_t(const T *first, const T *last, T *result, true_type) {
        memmove(result, first, sizeof(T) * (last - first));
        return result + (last - first);
    }

    template<typename T>
    inline T *
    _copy_t(const T *first, const T *last, T *result, false_type) {
        return _copy_d(first, last, result, static_cast<ptrdiff_t *>(nullptr));
    }

    template<typename InputIterator, typename OutputIterator>
    inline OutputIterator
    _copy(InputIterator first, InputIterator last, OutputIterator result, input_iterator_tag) {
        for (; first != last; ++result, ++first) {
            *result = *first;
        }
        return result;
    }

    template<typename RandomAccessIterator, typename OutputIterator>
    inline OutputIterator
    _copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, random_access_iterator_tag) {
        return _copy_d(first, last, result, distance_type(first));
    }

    template<typename InputIterator, typename OutputIterator>
    struct copy_dispatch {
        OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator result) {
            return _copy(first, last, result, iterator_category(first));
        }
    };

    template<typename T>
    struct copy_dispatch<T *, T *> {
        T *operator()(T *first, T *last, T *result) {
            using operator_type = typename type_traits<T>::has_trivial_assignment_operator;
            return _copy_t(first, last, result, operator_type());
        }
    };

    template<typename T>
    struct copy_dispatch<const T *, T *> {
        T *operator()(T *first, T *last, T *result) {
            using operator_type = typename type_traits<T>::has_trivial_assignment_operator;
            return _copy_t(first, last, result, operator_type());
        }
    };

    template<typename InputIterator, typename OutputIterator>
    inline OutputIterator
    copy(InputIterator first, InputIterator last, OutputIterator result) {
        return copy_dispatch<InputIterator, OutputIterator>()(first, last, result);
    }

    inline char *
    copy(char *first, char *last, char *result) {
        memmove(result, first, last - first);
        return result + (last - first);
    }

    inline wchar_t *
    copy(wchar_t *first, wchar_t *last, wchar_t *result) {
        memmove(result, first, sizeof(wchar_t) * (last - first));
        return result + (last - first);
    }

    /**
     * 逻辑同copy
     */

    // --------------------- copy backward --------------------------

    template<typename BidirectionalIterator1, typename BidirectionalIterator2, typename Distance>
    inline BidirectionalIterator2
    _copy_backward_d(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result,
                     Distance *) {
        for (Distance distance = last - first; distance > 0; --distance, --result, --last) {
            *result = *last;
        }
        return result;
    }

    template<typename T>
    inline T *
    _copy_backward_t(const T *first, const T *last, T *result, true_type) {
        size_t len = sizeof(T) * (last - first);
        memmove(result - (last - first), first, len);
        return result - (last - first);
    }

    template<typename T>
    inline T *
    _copy_backward_t(const T *first, const T *last, T *result, false_type) {
        return _copy_backward_d(first, last, result, static_cast<ptrdiff_t *>(nullptr));
    }

    template<typename BidirectionalIterator1, typename BidirectionalIterator2>
    inline BidirectionalIterator2
    _copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result,
                   bidirectional_iterator_tag) {
        for (; last != first; --last, --result) {
            *result = *last;
        }
        return result;
    }

    template<typename BidirectionalIterator1, typename BidirectionalIterator2>
    inline BidirectionalIterator2
    _copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result,
                   random_access_iterator_tag) {
        return _copy_backward_d(first, last, result, distance_type(first));
    }

    template<typename BidirectionalIterator1, typename BidirectionalIterator2>
    struct copy_backward_dispatch {
        BidirectionalIterator2
        operator()(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result) {
            return _copy_backward(first, last, result, iterator_category(first));
        }
    };

    template<typename T>
    struct copy_backward_dispatch<T *, T *> {
        T *operator()(T *first, T *last, T *result) {
            using operator_type = typename type_traits<T>::has_trivial_assignment_operator;
            return _copy_backward_t(first, last, result, operator_type());
        }
    };

    template<typename T>
    struct copy_backward_dispatch<const T *, T *> {
        T *operator()(T *first, T *last, T *result) {
            using operator_type = typename type_traits<T>::has_trivial_assignment_operator;
            return _copy_backward_t(first, last, result, operator_type());
        }
    };

    template<typename BidirectionalIterator1, typename BidirectionalIterator2>
    inline BidirectionalIterator2
    copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result) {
        return copy_backward_dispatch<BidirectionalIterator1, BidirectionalIterator2>()(first, last, result);
    }

    inline char *
    copy_backward(char *first, char *last, char *result) {
        memmove(result - (last - first), first, (last - first));
        return result - (last - first);
    }

    inline wchar_t *
    copy_backward(wchar_t *first, wchar_t *last, wchar_t *result) {
        size_t len = sizeof(wchar_t) * (last - first);
        memmove(result - (last - first), first, len);
        return result - (last - first);
    }

    // --------------------- swap --------------------------

    template<typename T>
    inline void swap(T &a, T &b) {
        T tmp = a;
        a = b;
        b = tmp;
    }
}

#endif //MICROSTL_ALGOBASE_H











