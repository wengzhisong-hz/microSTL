#ifndef MICROSTL_LIST_H
#define MICROSTL_LIST_H

#include "../iterator/iterator.h"
#include "../memory/alloc.h"
#include "../memory/construct.h"
#include "../algorithm/algobase.h"

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
            node = link_type((*node).next);
        }

        self operator++(int) {
            self tmp = *this;
            ++*this;
            return tmp;
        }

        self &operator--() {
            node = link_type((*node).prev);
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
            return link_type((*node).next);
        }

        iterator end() {
            return node;
        }

        bool empty() const {
            return node->next == node;
        }

        size_type size() const {
            size_type result = 0;
            for (auto first = begin(); first != end(); ++first) {
                ++result;
            }
            return result;
        }

        reference front() {
            return *begin();
        }

        reference back() {
            return *(--end());
        }

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
            (link_type(position.node->prev))->next = temp;
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
            link_type next_node = link_type(position.node->next);
            link_type prev_node = link_type(position.node->prev);
            prev_node->next = next_node;
            next_node->prev = prev_node;
            destroy_node(position.node);
            return iterator(next_node);
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

        // 将[first, last)内的元素移动到position之前
        void transfer(iterator position, iterator first, iterator last);

        void list_swap(list &obj);

    public:
        list() {
            empty_initialize();
        }

        void splice(iterator position, list &obj) {
            if (!obj.empty()) {
                transfer(position, obj.begin(), obj.end());
            }
        }

        void splice(iterator position, list &, iterator iter_i) {
            iterator iter_j = iter_i;
            ++iter_j;
            if (position == iter_i || position == iter_j) {
                return;
            }
            transfer(position, iter_i, iter_j);
        }

        void splice(iterator position, list &, iterator first, iterator last) {
            if (first != last) {
                transfer(position, first, last);
            }
        }

        // 将target 合并到当前list上，两个list的内容需要经过递增排序
        void merge(list<T> &target);

        // 反转
        void reverse();

        // 快排方案
        void sort();
    };

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

    template<typename T>
    void list<T>::transfer(list::iterator position, list::iterator first, list::iterator last) {
        if (position != last) {
            (*(link_type((*last.node).prev))).next = position.node;
            (*(link_type((*first.node).prev))).next = last.node;
            (*(link_type((*position.node).prev))).next = first.node;

            link_type temp = link_type((*position.node).prev);
            (*position.node).prev = (*last.node).prev;
            (*last.node).prev = (*first.node).prev;
            (*first.node).prev = temp;
        }
    }

    template<typename T>
    void list<T>::merge(list<T> &target) {
        iterator first1 = begin();
        iterator last1 = end();
        iterator first2 = target.begin();
        iterator last2 = target.end();

        while (first1 != last1 && first2 != last2) {
            if (*first2 < *first1) {
                iterator next = first2;
                transfer(first1, first2, ++next);
                first2 = next;
            } else {
                ++first1;
            }
            if (first2 != last2) {
                transfer(last1, first2, last2);
            }
        }
    }

    template<typename T>
    void list<T>::reverse() {
        if (node->next == node || link_type(node->next)->next == node) {
            return;
        }

        iterator first = begin();
        ++first;
        while (first != end()) {
            iterator old = first;
            ++first;
            transfer(begin(), old, first);
        }
    }

    template<typename T>
    void list<T>::sort() {
        // 空或者只有一个节点不处理
        if (node->next == node || link_type(node->next)->next == node) {
            return;
        }

        // 暂存
        list<T> carry;
        list<T> counter[64];

        int fill = 0;

        while (!empty()) {
            carry.splice(carry.begin(), *this, begin());
            int i = 0;

            while (i < fill && !counter[i].empty()) {
                counter[i].merge(carry);
                carry.list_swap(counter[i++]);
            }

            carry.list_swap(counter[i]);
            if (i == fill) {
                ++fill;
            }

            for (int i = 1; i < fill; ++i) {
                counter[i].merge(counter[i - 1]);
            }

            swap(counter[fill - 1]);
        }
    }

    template<class T>
    void list<T>::list_swap(list &obj) {
        iterator head1 = begin();
        iterator tail1 = end();
        iterator head2 = obj.begin();
        iterator tail2 = obj.end();

        swap(head1.node, head2.node);
        swap(tail1.node, tail2.node);
    }
}

#endif //MICROSTL_LIST_H














