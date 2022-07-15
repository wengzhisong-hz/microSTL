#ifndef MICROSTL_LIST_H
#define MICROSTL_LIST_H

#include "../iterator/iterator.h"

namespace MicroSTL {
    // --------------------- 双向链表结构 --------------------------
    template<typename T>
    struct _list_node {
        using void_pointer = _list_node<T> *;
        void_pointer prev;
        void_pointer next;
        T data;
    };

    // --------------------- 迭代器 --------------------------

    template<typename T, typename Ref, typename Ptr>
    struct list_iterator {
        using iterator = list_iterator<T, T &, T *>;
        using self = list_iterator<T, Ref, Ptr>;
        // list为双向迭代器
        using iterator_category = bidirectional_iterator_tag;
        using value_type = T;
        using reference = Ref;
        using pointer = Ptr;
        using link_type = _list_node<T> *;
        using size_type = size_t;
        using difference_type = ptrdiff_t;

        link_type node;

        list_iterator() = default;

        list_iterator(link_type iter) : node(iter) {}

        list_iterator(const iterator &iter) : node(iter.node) {}

        bool operator==(const self &iter) const {
            return node == iter.node;
        }

        bool operator!=(const self &iter) const {
            return node != iter.node;
        }

        reference operator*() const {
            return (*node).data;
        }

        pointer operator->() const {
            return &(operator*());
        }

        self &operator++() {
            node = static_cast<link_type >((*node).next);
        }

        self operator++(int) {
            self tmp = *this;
            ++*this;
            return tmp;
        }

        self &operator--() {
            node = static_cast<link_type >((*node).prev);
        }

        self operator--(int) {
            self tmp = *this;
            --*this;
            return tmp;
        }
    };

    // --------------------- list --------------------------

    template<typename T>
    class list {
    protected:
        using list_node = _list_node<T>;
        list_node *node;
    public:
        using link_type = _list_node<T> *;
        using value_type = T;
        using size_type = size_t;
        using pointer = T *;
        using reference = T &;
        using iterator = list_iterator<T, T &, T *>;

        iterator begin() {
            return static_cast<link_type>((*node).next);
        }

        iterator end() {
            return node;
        }

        bool empty() const {
            return node->next == node;
        }

        size_type size() const {
            size_type result = 0;
            distance(begin(), end(), result);
            return result;
        }

        reference front() {
            return *begin();
        }

        reference back() {
            return *(--end());
        }

        void distance(iterator first, iterator last, size_type size);
    };

    template<typename T>
    void list<T>::distance(list::iterator first, list::iterator last, list::size_type size) {

    }
}

#endif //MICROSTL_LIST_H














