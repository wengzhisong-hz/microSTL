#ifndef MICROSTL_ALLOCATOR_H
#define MICROSTL_ALLOCATOR_H

#include <new>
#include <cstddef>
#include <iostream>

namespace MicroSTL {
    template<class T1, class T2>
    void _construct(T1 *ptr, const T2 &value) {
        ::new(ptr) T1(value);
    }

    template<class T>
    class allocator {
    public:
        using value_type = T;
        using pointer = T *;
        using const_pointer = const T *;
        using referenct = T &;
        using size_type = size_t;
        using difference_type = ptrdiff_t;

        static T *allocate();

        static T *allocate(size_type n);

        static void deallocate(T *ptr);

        static void deallocate(T *ptr, size_t n);

        static void construct(pointer ptr, const T &value);

        static void destroy(T *ptr);
    };

    template<class T>
    T *allocator<T>::allocate() {
        T *ret = static_cast<T *>(::operator new(sizeof(T)));
        if (ret == 0) {
            std::cerr << "out of memory" << std::endl;
            exit(1);
        }
        return ret;
    }

    template<class T>
    T *allocator<T>::allocate(allocator::size_type n) {
        if (n == 0) {
            return nullptr;
        }
        T *ret = static_cast<T *>(::operator new(n * sizeof(T)));
        if (ret == 0) {
            std::cerr << "out of memory" << std::endl;
            exit(1);
        }
        return ret;
    }

    template<class T>
    void allocator<T>::deallocate(T *ptr) {
        if (ptr == nullptr) {
            return;
        }
        ::operator delete(ptr);
    }

    template<class T>
    void allocator<T>::deallocate(T *ptr, size_t /*n*/) {
        if (ptr == nullptr) {
            return;
        }
        ::operator delete(ptr);
    }

    template<class T>
    void allocator<T>::construct(allocator::pointer ptr, const T &value) {
        _construct(ptr, value);
    }

    template<class T>
    void allocator<T>::destroy(T *ptr) {
        if (ptr != nullptr) {
            ptr->~T();
        }
    }
}

#endif //MICROSTL_ALLOCATOR_H