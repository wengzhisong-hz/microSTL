#ifndef MICROSTL_ITERATOR_TRAITS_H
#define MICROSTL_ITERATOR_TRAITS_H

#include "iterator.h"

namespace MicroSTL {
    // --------------- 定义迭代器的类型萃取 ---------------

    /**
     * traits
     */
    template<typename T>
    struct iterator_traits {
        using iterator_category = typename T::iterator_category;
        using value_type = typename T::value_type;
        using difference_type = typename T::difference_type;
        using pointer = typename T::pointer;
        using reference = typename T::reference;
    };

    /**
     * 针对原生指针的偏特化
     */
    template<typename T>
    struct iterator_traits<T *> {
        // 原生指针需要随机访问
        using iterator_category = random_access_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T *;
        using reference = T &;
    };

    /**
     * 针对指针常量的偏特化
     */
    template<typename T>
    struct iterator_traits<const T *> {
        using iterator_category = random_access_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T *;
        using reference = T &;
    };

    /**
     * 萃取迭代器的 iterator_category
     */
    template<typename Iterator>
    inline typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator &) {
        // category是一个struct（定义在iterator.h中）
        using catgory = typename iterator_traits<Iterator>::iterator_category;
        return catgory();
    }

    /**
     * 萃取迭代器的 value_type
     */
    template<typename Iterator>
    inline typename iterator_traits<Iterator>::value_type
    value_type(const Iterator &) {
        return static_cast<typename iterator_traits<Iterator>::value_type>(0);
    }

    /**
     * 萃取迭代器的 distance_type
     */
    template<typename Iterator>
    inline typename iterator_traits<Iterator>::difference_type
    distance_type(const Iterator &) {
        return static_cast<typename iterator_traits<Iterator>::difference_type>(0);
    }
}

#endif //MICROSTL_ITERATOR_TRAITS_H
