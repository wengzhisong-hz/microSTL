#ifndef MICROSTL_ITERATOR_H
#define MICROSTL_ITERATOR_H

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


    // --------------- 定义迭代器原型 ---------------

    /**
     * iterator 原型，所有的迭代器都应该继承这个迭代器
     */
    template<typename Category,
            typename T,
            typename Distance = ptrdiff_t,
            typename Pointer = T *,
            typename Reference = T &>
    struct iterator {
        /**
         * 迭代器类型，分为五类：
         * - input iterator：只读
         * - output iterator：只写
         * - forward iterator：前向访问，支持读写
         * - bidirectional iterator：双向访问，支持读写
         * - random access iterator：随机访问，支持读写
         */
        using iterator_category = Category;
        /**
         * 迭代器所指对象类型；
         */
        using value_type = T;
        /**
         * 两个迭代器之间的距离；
         * 可以用来表示容器的最大容量；
         */
        using difference_type = Distance;
        /**
         * 指向迭代器所指之物的指针；
         */
        using pointer = Pointer;
        /**
         * 迭代器所指之物是否允许改变；
         * 对迭代器解引用的时候，返回的是左值还是右值；
         */
        using reference = Reference;
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

#endif //MICROSTL_ITERATOR_H
