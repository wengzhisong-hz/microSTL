#ifndef MICROSTL_ITERATOR_H
#define MICROSTL_ITERATOR_H

namespace MicroSTL::Iterator {
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
}
#endif //MICROSTL_ITERATOR_H
