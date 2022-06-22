#ifndef MICROSTL_CONSTRUCT_H
#define MICROSTL_CONSTRUCT_H

#include <new>
#include "../type_traits.h"

namespace MicroSTL {
    /**
     * construct负责在指定的内存空间上构造、销毁对象
     */
    namespace Construct {
        /**
         * placement new
         */
        template<typename Address, typename Obj>
        inline void construct(Address *address, const Obj &obj) {
            new(address) Obj(obj);
        }

        /**
         * 直接调用析构函数
         */
        template<typename Obj>
        inline void destroy(Obj *obj) {
            obj->~Obj();
        }

        /**
         * 接收两个迭代器，通过type traits获得相应的destructor类型，采取对应的析构方案
         */
        template<typename ForwardIterator>
        inline void destroy(ForwardIterator first, ForwardIterator last) {
//            value_type()
        }

        template<typename ForwardIterator, typename T>
        inline void _destroy(ForwardIterator first, ForwardIterator last, T *) {
            using trivial_destructor = typename iterator_traits<T>::
        }
    }
}

#endif //MICROSTL_CONSTRUCT_H
