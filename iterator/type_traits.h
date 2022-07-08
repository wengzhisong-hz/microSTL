#ifndef MICROSTL_TYPE_TRAITS_H
#define MICROSTL_TYPE_TRAITS_H

namespace MicroSTL {
    /**
     * 包含该特性
     */
    struct true_type {
    };

    /**
     * 不包含该特性
     */
    struct false_type {
    };

    // --------------- 定义constructor、destructor函数的trivial类型 --------------

    /**
     * 对于某数据的以下四种函数：
     * - 默认构造函数(default constructor)
     * - 拷贝构造函数(copy constructor)
     * - 赋值函数(copy assignment operator)
     * - 析构函数(destructor)
     *
     * 如果它们至少满足以下三个条件之一：
     * - 显式(explict)定义了这四种函数
     * - 类里有非静态非POD的数据成员
     * - 有基类
     *
     * 那么它们为non-trivial函数;
     * 如果以上四个函数都是trivial函数，那么这个对象属于POD类型。
     *
     * 由于c++中基本内置类型都是POD类型，因此我们一般讨论class、struct和union是否为POD类型
     *
     * 对于POD类型的数据，进行构造、析构、拷贝和赋值时，不需要调用它们的constructor、destructor函数，可以直接采用malloc()、memcpy()来提高效率。
     */
    template<typename T>
    struct type_traits {
        // 默认都为false_type
        using has_trivial_default_constructor = false_type;
        using has_trivial_copy_constructor = false_type;
        using has_trivial_assignment_operator = false_type;
        using has_trivial_destructor = false_type;
        using is_POD_type = false_type;
    };

    // --------------- c++内置类型的constructor、destructor函数trivial类型全特化 --------------

    template<>
    struct type_traits<bool> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<>
    struct type_traits<char> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<>
    struct type_traits<unsigned char> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<>
    struct type_traits<signed char> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<>
    struct type_traits<wchar_t> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<>
    struct type_traits<short> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<>
    struct type_traits<unsigned short> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<>
    struct type_traits<int> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<>
    struct type_traits<unsigned int> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<>
    struct type_traits<long> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<>
    struct type_traits<unsigned long> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<>
    struct type_traits<long long> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<>
    struct type_traits<unsigned long long> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<>
    struct type_traits<float> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<>
    struct type_traits<double> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<>
    struct type_traits<long double> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<typename T>
    struct type_traits<T *> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<typename T>
    struct type_traits<const T *> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<>
    struct type_traits<char *> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<>
    struct type_traits<unsigned char *> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<>
    struct type_traits<signed char *> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<>
    struct type_traits<const char *> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<>
    struct type_traits<const unsigned char *> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };

    template<>
    struct type_traits<const signed char *> {
        using has_trivial_default_constructor = true_type;
        using has_trivial_copy_constructor = true_type;
        using has_trivial_assignment_operator = true_type;
        using has_trivial_destructor = true_type;
        using is_POD_type = true_type;
    };
}

#endif //MICROSTL_TYPE_TRAITS_H
