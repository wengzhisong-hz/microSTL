#ifndef MICROSTL_TYPE_TRAITS_H
#define MICROSTL_TYPE_TRAITS_H

namespace MicroSTL {
    template <class T>
    struct iterator_traits {
        /**
         * 迭代器类别，分为五类：
         * - input iterator：只读
         * - output iterator：只写
         * - forward iterator：支持读写
         * - bidirectional iterator：可双向移动
         * - random access iterator：随机
         */
        using iterator_category = typename T::iterator_category;
        /**
         * 迭代器所指对象类别；
         */
        using value_type = typename T::value_type;
        /**
         * 两个迭代器之间的距离；
         * 可以用来表示容器的最大容量；
         */
        using difference_type = typename T::difference_type;
        /**
         * 指向迭代器所指之物的指针；
         */
        using pointer = typename T::pointer;
        /**
         * 迭代器指向事物是否允许改变；
         * 对迭代器解引用的时候，返回的是左值还是右值；
         */
        using reference = typename T::reference;
    };
}

#endif //MICROSTL_TYPE_TRAITS_H
