#ifndef MICROSTL_ITERATOR_H
#define MICROSTL_ITERATOR_H

namespace MicroSTL {
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
     * _iterator 原型，所有的迭代器都应该实现这个迭代器
     */
    template<typename Category,
            typename T,
            typename Distance = ptrdiff_t,
            typename Pointer = T *,
            typename Reference = T &>
    struct _iterator {
        /**
         * 迭代器类型，分为五类：
         * - input _iterator：只读
         * - output _iterator：只写
         * - forward _iterator：前向访问，支持读写
         * - bidirectional _iterator：双向访问，支持读写
         * - random access _iterator：随机访问，支持读写
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
