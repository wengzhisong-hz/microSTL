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


}

#endif //MICROSTL_UNINITIALIZED_H
