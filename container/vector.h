#ifndef MICROSTL_VECTOR_H
#define MICROSTL_VECTOR_H

#include "../memory/alloc.h"
#include "../memory/construct.h"
#include "../algorithm/algobase.h"
#include "../memory/uninitialized.h"

namespace MicroSTL {
    template<typename T>
    class vector {
    public:
        using value_type = T;
        using pointer = value_type *;
        // 迭代器为原生指针
        using iterator = value_type *;
        using reference = value_type &;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
    protected:
        using allocator = Alloc<value_type>;
        // 使用空间的起点
        iterator start;
        // 使用空间的终点
        iterator finish;
        // 可用空间的终点
        iterator end_of_storage;

        void deallocate() {
            if (start) {
                allocator::deallocate(start, end_of_storage - start);
            }
        }

        void fill_initialize(size_type size, const T &value) {
            start = allocate_and_fill(size, value);
            finish = start + size;
            end_of_storage = finish;
        }

        void insert_aux(iterator position, const T &obj) {
            if (finish != end_of_storage) {
                construct(finish, *(finish - 1));
                ++finish;
                T obj_copy = obj;
                copy_backward(position, finish - 2, finish - 1);
                *position = obj_copy;
            } else {
                const size_type old_size = size();
                // 扩展为原先空间的2倍
                const size_type len = old_size != 0 ? 2 * old_size : 1;
                iterator new_start = allocator::allocate(len);
                iterator new_finish = new_start;


                // commit or rollback
                try {
                    new_finish = uninitialized_copy(start, position, new_start);
                    construct(new_finish, obj);
                    ++new_finish;
                    new_finish = uninitialized_copy(position, finish, new_finish);
                } catch (...) {
                    destroy(new_start, new_finish);
                    allocator::deallocate(new_start, len);
                    throw;
                }

                destroy(begin(), end());
                deallocate();

                start = new_start;
                finish = new_finish;
                end_of_storage = new_start + len;
            }
        }

        void copy_backward();

        iterator allocate_and_fill(size_type size, const T &value) {
            iterator result = allocator::allocate(size);
            uninitialized_fill_n(result, size, value);
            return result;
        }

    public:
        iterator begin() {
            return start;
        };

        iterator end() {
            return finish;
        };

        size_type size() const {
            return size_type(end() - begin());
        }

        size_type capacity() const {
            return size_type(end_of_storage - begin());
        }

        bool empty() const {
            return begin() == end();
        }

        reference operator[](size_type n) {
            return *(begin() + n);
        }

        vector() : start(0), finish(0), end_of_storage(0) {}

        vector(size_type size, const T &value) {
            fill_initialize(size, value);
        }

        vector(long size, const T &value) {
            fill_initialize(size, value);
        }

        vector(int size, const T &value) {
            fill_initialize(size, value);
        }

        explicit vector(size_type size) {
            fill_initialize(size, T());
        }

        ~vector() {
            destroy(start, finish);
            deallocate();
        }

        reference front() {
            return *begin();
        }

        reference back() {
            return *(end() - 1);
        }

        void push_back(const T &obj) {
            if (finish != end_of_storage) {
                construct(finish, obj);
                finish++;
            } else {
                insert_aux(end(), obj);
            }
        }

        void pop_back() {
            finish--;
            destroy(finish);
        }

        iterator erase(iterator position) {
            if (position + 1 != end()) {
                copy(position + 1, finish, position);
            }
            finish--;
            destroy(finish);
            return position;
        }

        iterator erase(iterator first, iterator last);

        void resize(size_type new_size, const T &obj) {
            if (new_size < size()) {
                erase(begin() + new_size, end());
            } else {
                insert(end(), new_size, obj);
            }
        }

        void resize(size_type size) {
            return (resize(size, T()));
        }

        void clear() {
            erase(begin(), end());
        }

        void insert(iterator position, size_type size, const T &obj);
    };
}

#endif //MICROSTL_VECTOR_H
















