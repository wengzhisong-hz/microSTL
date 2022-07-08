#ifndef MICROSTL_UNINITIALIZED_H
#define MICROSTL_UNINITIALIZED_H

#include "../iterator/iterator_traits.h"
#include "../iterator/type_traits.h"
#include "../algorithm/algobase.h"
#include "construct.h"

namespace MicroSTL {
    template<typename ForwardIterator, typename Size, typename T>
    inline ForwardIterator
    uninitialized_fill_n(ForwardIterator first, Size size, T &obj) {
        // 获取迭代器的类型
        return _uninitialized_fill_n(first, size, obj, value_type(first));
    }

    template<typename ForwardIterator, typename Size, typename T, typename T1>
    inline ForwardIterator
    // 判断迭代器类型是否是POD
    _uninitialized_fill_n(ForwardIterator first, Size size, T &obj, T1 *) {
        using is_POD = typename type_traits<T1>::is_POD_type;
        return _uninitialized_fill_n_aux(first, size, obj, is_POD());
    }

    template<typename ForwardIterator, typename Size, typename T>
    inline ForwardIterator
    _uninitialized_fill_n_aux(ForwardIterator first, Size size, T &obj, true_type) {
        return fill_n(first, size, obj);
    }

    template<typename ForwardIterator, typename Size, typename T>
    inline ForwardIterator
    _uninitialized_fill_n_aux(ForwardIterator first, Size size, T &obj, false_type) {
        ForwardIterator current = first;
        for (; size > 0; --size, ++current) {
            construct(&*current, obj);
        }
        return current;
    }

    template<typename InputIterator, typename ForwardIterator>
    inline ForwardIterator
    uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result) {
        return _uninitialized_copy(first, last, result, value_type(first));
    }

    // 针对 char* 的重载
    inline char *uninitialized_copy(const char *first, const char *last, char *result) {
        memmove(result, first, last - first);
        return result + (last - first);
    }

    // 针对 wchar_t* 的重载
    inline wchar_t *uninitialized_copy(const wchar_t *first, const wchar_t *last, wchar_t *result) {
        memmove(result, first, sizeof(wchar_t) * (last - first));
        return result + (last - first);
    }

    template<typename InputIterator, typename ForwardIterator, typename T>
    inline ForwardIterator
    _uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, T *) {
        using is_POD = typename type_traits<T>::is_POD_type;
        return _uninitialized_copy_aux(first, last, result, is_POD());
    }

    template<typename InputIterator, typename ForwardIterator>
    inline ForwardIterator
    _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, true_type) {
        return copy(first, last, result);
    }

    template<typename InputIterator, typename ForwardIterator>
    inline ForwardIterator
    _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, false_type) {
        ForwardIterator current = result;
        for (; first != last; ++first, ++current) {
            construct(&*current, *first);
        }
        return current;
    }

    template<typename ForwardIterator, typename T>
    inline void
    uninitialized_fill(ForwardIterator first, ForwardIterator last, T &obj) {
        return _uninitialized_fill(first, last, obj, value_type(first));
    }

    template<typename ForwardIterator, typename T>
    inline void
    _uninitialized_fill(ForwardIterator first, ForwardIterator last, T &obj, T *) {
        using is_POD = typename type_traits<T>::is_POD_type;
        return _uninitialized_fill_aux(first, last, obj, is_POD());
    }

    template<typename ForwardIterator, typename T>
    inline void
    _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, T &obj, true_type) {
        return fill(first, last, obj);
    }

    template<typename ForwardIterator, typename T>
    inline void
    _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, T &obj, false_type) {
        ForwardIterator current = first;
        for (; first != last; ++first) {
            construct(&*current, obj);
        }
    }
}

#endif //MICROSTL_UNINITIALIZED_H
