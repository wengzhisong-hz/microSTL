#ifndef MICROSTL_TYPE_TRAITS_H
#define MICROSTL_TYPE_TRAITS_H

namespace MicroSTL {

    // 用于函数重载决议的五个迭代器类型标记

    /**
     * 只读迭代器
     */
    struct input_iterator_tag {
    };
    /**
     * 只写迭代器
     */
    struct output_iterator_tag {
    };
    /**
     * 前向访问迭代器，支持读写
     */
    struct forward_iterator_tag : public input_iterator_tag {
    };
    /**
     * 双向访问迭代器，支持读写
     */
    struct bidirectional_iterator_tag : public forward_iterator_tag {
    };
    /**
     * 随机访问迭代器，支持读写
     */
    struct random_access_iterator_tag : public bidirectional_iterator_tag {
    };

    /**
     * 迭代器原型，所有的迭代器都应该继承这个迭代器
     */
    template<typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T *, typename Reference = T &>
    struct iterator {
        /**
         * 迭代器类别，分为五类：
         * - input iterator：只读
         * - output iterator：只写
         * - forward iterator：前向访问，支持读写
         * - bidirectional iterator：双向访问，支持读写
         * - random access iterator：随机访问，支持读写
         */
        using iterator_category = Category;
        /**
         * 迭代器所指对象类别；
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

    /**
     * traits
     */
    template<class T>
    struct iterator_traits {
        using iterator_category = typename T::iterator_category;
        using value_type = typename T::value_type;
        using difference_type = typename T::difference_type;
        using pointer = typename T::pointer;
        using reference = typename T::reference;
    };

    /**
     * 针对原生指针的traits偏特化
     */
    template<typename T>
    struct iterator_traits<T *> {
        using iterator_categor = random_access_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T *;
        using reference = T &;
    };

    /**
     * 针对const原生指针的traits偏特化
     */
    template<typename T>
    struct iterator_traits<const T *> {
        using iterator_categor = random_access_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T *;
        using reference = T &;
    };
}

#endif //MICROSTL_TYPE_TRAITS_H
