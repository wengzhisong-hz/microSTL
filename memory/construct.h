#ifndef MICROSTL_CONSTRUCT_H
#define MICROSTL_CONSTRUCT_H

#include <new>
#include "../iterator/type_traits.h"
#include "../iterator/iterator_traits.h"

namespace MicroSTL {

    // --------------- placement new 构造 ---------------

    template<typename Address, typename Obj>
    inline void construct(Address *address, const Obj &obj) {
        new(address) Obj(obj);
    }

    // --------------- 接收一个指针，直接析构 ---------------

    template<typename Obj>
    inline void destroy(Obj *obj) {
        obj->~Obj();
    }

    // --------------- 接收两个迭代器指针，按类型析构 ---------------

    /**
    * 析构函数
    * 接收两个迭代器
    */
    template<typename ForwardIterator>
    inline void destroy(ForwardIterator first, ForwardIterator last) {
        _destroy(first, last, value_type(first));
    }

    /**
     * 析构辅助函数
     */
    template<typename ForwardIterator, typename T>
    inline void _destroy(ForwardIterator first, ForwardIterator last, T *) {
        using trivial_destructor = typename type_traits<T>::has_trivial_destructor;
        _destroy(first, last, trivial_destructor());
    }

    /**
     * 重载析构辅助函数
     * 处理 trivial destructor
     */
    template<typename ForwardIterator>
    inline void
    _destroy(ForwardIterator first, ForwardIterator last, true_type) {
        // 什么也不做
    }

    /**
     * 重载析构辅助函数
     * 处理 non trivial destructor
     */
    template<typename ForwardIterator>
    inline void
    _destroy(ForwardIterator first, ForwardIterator last, false_type) {
        for (; first < last; ++first) {
            destroy(&*first);
        }
    }

    // --------------- 特化的destroy版本 ---------------

    /**
     * 针对char*的重载
     */
    inline void destroy(char *, char *) {
        // 什么也不做
    }

    /**
     * 针对wchar_t*的重载
     */
    inline void destroy(wchar_t *, wchar_t *) {
        // 什么也不做
    }
}

#endif //MICROSTL_CONSTRUCT_H
