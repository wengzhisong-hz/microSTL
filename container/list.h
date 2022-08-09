#ifndef MICROSTL_LIST_H
#define MICROSTL_LIST_H

#include "../iterator/iterator.h"
#include "../memory/alloc.h"
#include "../memory/construct.h"

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
        using list_node_allocator = Alloc<list_node>;
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

    protected:
        link_type get_node() {
            return list_node_allocator::allocate();
        }

        void put_node(link_type ptr) {
            list_node_allocator::deallocate(ptr);
        }

        link_type create_node(const T &obj) {
            link_type ptr = get_node();
            construct(&ptr->data, obj);
            return ptr;
        }

        void destroy_node(link_type ptr) {
            destroy(&ptr->data);
            put_node(ptr);
        }

        // 配置一个空的双向链表
        void empty_initialize() {
            node = get_node();
            node->next = node;
            node->prev = node;
        }

        // 在position处插入一个node
        iterator insert(iterator position, const T &obj) {
            link_type temp = create_node(obj);
            temp->next = position.node;
            temp->prev = position.node->prev;
            (static_cast<link_type>(position.node->prev))->next = temp;
            position.node->prev = temp;
            return temp;
        }

        void push_front(const T &obj) {
            insert(begin(), obj);
        }

        void push_back(const T &obj) {
            insert(end(), obj);
        }

        iterator erase(iterator position) {
            link_type next_node = static_cast<link_type>(position.node->next);
            link_type prev_node = static_cast<link_type>(position.node->prev);
            prev_node->next = next_node;
            next_node->prev = prev_node;
            destroy_node(position.node);
            return static_cast<iterator>(next_node);
        }

        void pop_front() {
            erase(begin());
        }

        void pop_back() {
            iterator temp = end();
            erase(--temp);
        }

        // 移除目标值
        void remove(const T &obj);

        // 移除连续而相同的元素
        void unique();

    public:
        list() {
            empty_initialize();
        }
    };

    template<typename T>
    void list<T>::distance(list::iterator first, list::iterator last, list::size_type size) {

    }

    template<typename T>
    void list<T>::remove(const T &value) {
        iterator first = begin();
        iterator last = end();
        while (first != last) {
            iterator next = first;
            ++next;
            if (*first == value) {
                erase(first);
            }
            first = next;
        }
    }

    template<typename T>
    void list<T>::unique() {
        iterator first = begin();
        iterator last = end();
        if (first == last) {
            return;
        }
        iterator next = first;
        while (++next != last) {
            if (*first == *next) {
                erase(next);
            } else {
                first = next;
            }
            next = first;
        }
    }
}

#endif //MICROSTL_LIST_H














