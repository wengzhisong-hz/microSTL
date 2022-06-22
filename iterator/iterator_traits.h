#ifndef MICROSTL_ITERATOR_TRAITS_H
#define MICROSTL_ITERATOR_TRAITS_H

namespace MicroSTL::IteratorTraits {
    // --------------- 定义 Category 类型 ---------------

    /**
     * 只读迭代器标记
     */
    struct input_iterator_tag {
    };
    /**
     * 只写迭代器标记
     */
    struct output_iterator_tag {
    };
    /**
     * 前向访问迭代器，支持读写标记
     */
    struct forward_iterator_tag : public input_iterator_tag {
    };
    /**
     * 双向访问迭代器，支持读写标记
     */
    struct bidirectional_iterator_tag : public forward_iterator_tag {
    };
    /**
     * 随机访问迭代器，支持读写标记
     */
    struct random_access_iterator_tag : public bidirectional_iterator_tag {
    };

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
        return iterator_traits<Iterator>::iterator_category();
    }

    /**
     * 萃取迭代器的 value_type
     */
    template<typename Iterator>
    inline typename iterator_traits<Iterator>::value_type *
    value_type(const Iterator &) {
        return iterator_traits<Iterator>::value_type * (0);
    }

    /**
     * 萃取迭代器的 distance_type
     */
    template<typename Iterator>
    inline typename iterator_traits<Iterator>::difference_type *
    distance_type(const Iterator &) {
        return iterator_traits<Iterator>::difference_type * (0);
    }
}

#endif //MICROSTL_ITERATOR_TRAITS_H
