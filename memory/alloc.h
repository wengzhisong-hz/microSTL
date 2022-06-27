#ifndef MICROSTL_ALLOC_H
#define MICROSTL_ALLOC_H

/**
 * stl内存分配策略：
 *
 * - 如果申请的内存块 > 128byte
 *      - 则直接调用 malloc
 * - 否则从free-list中进行分配一个大小合适的block
 *      - 如果当前list空间不够
 *          - 尝试向内存池申请20个block
 *          - 如果内存池空间不足20个block，则都分配出去
 *          - 如果连一个block都不够了
 *              - 先将剩余的内存给管理小块内存的list
 *              - malloc申请40个block+额外大小的内存区域
 *          - 如果malloc失败，则递归其余list，找到空闲的block以供使用
 *          - 如果free-list连这点内存都提供不了了，那么调用第一级allocator
 *              - 第一级allocator中有用户提供的oom handler
 *              - 如果oom handler失败，则抛出错误
 *      - 分配成功，则修改start_free end_free指针
 */

namespace MicroSTL {
    /**
     * 定义函数指针
     */
    using fn_ptr = void (*)();

    inline void throw_bad_alloc() {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    class AllocByMalloc {
    public:
        /**
         * 分配大块内存空间
         */
        static void *allocate(size_t size) {
            // 之所以使用malloc()，而不是::operation new，主要是因为c++未提供类似realloc()的操作
            void *res = malloc(size);
            // 手动实现oom异常处理
            if (res == nullptr) {
                res = oom_malloc(size);
            }
            return res;
        }

        /**
         * 重新分配大块内存空间
         */
        static void *reallocate(void *ptr, size_t /* old size */, size_t new_size) {
            void *res = realloc(ptr, new_size);
            if (res == nullptr) {
                res = oom_realloc(ptr, new_size);
            }
            return res;
        }

        /**
         * 回收内存空间
         */
        static void deallocate(void *ptr, size_t) {
            free(ptr);
        }

        /**
         * oom handler 接收一个用户自定义的 oom 处理函数指针，并返回原先的 oom 处理函数指针
         */
        static fn_ptr set_oom_user_handler(fn_ptr user_handler) {
            fn_ptr old_handler = oom_user_handler;
            oom_user_handler = user_handler;
            return old_handler;
        };
    private:
        /**
         * oom handler 应该由用户来定义
         */
        static void (*oom_user_handler)();

        /**
         * malloc oom 处理函数
         * 如果用户未定义 oom 处理函数，则直接抛出错误
         */
        static void *oom_malloc(size_t size) {
            void *res;

            // 不断尝试进行 释放 & 分配 操作
            for (;;) {
                if (oom_user_handler == nullptr) {
                    throw_bad_alloc();
                }
                // 调用用户 oom 处理函数，尝试释放一些可用空间
                oom_user_handler();
                res = malloc(size);
                if (res) {
                    return res;
                }
            }
        }

        /**
         * realloc oom 处理函数
         * 如果用户未定义 oom 处理函数，则直接抛出错误
         */
        static void *oom_realloc(void *ptr, size_t size) {
            void *res;
            for (;;) {
                if (oom_user_handler == nullptr) {
                    throw_bad_alloc();
                }
                oom_user_handler();
                res = realloc(ptr, size);
                if (res) {
                    return res;
                }
            }
        }
    };

    inline fn_ptr AllocByMalloc::oom_user_handler = nullptr;


    /**
     * free list阶梯值
     */
    static const int ALIGN = 8;
    /**
     * 最大block，超过这个大小则调用 AllocByMalloc
     */
    static const int MAX_BYTES = 128;
    /**
     * free list个数
     */
    static const int LIST_NUMBER = MAX_BYTES / ALIGN;

    /**
     * free list指针
     * 每个block为8byte，即上面我们定义的 ALIGN 大小
     * 这种做法，节约了一个指针的额外空间
     */
    union block {
        // 指针为8byte
        union block *next_block;
        // data类型所占空间只要小于8byte即可
        char data;
    };

    class AllocByFreeList {
    public:
        static void *allocate(size_t size) {
            // 如果 > 128byte则调用malloc直接进行内存分配
            if (size > MAX_BYTES) {
                return AllocByMalloc::allocate(size);
            }
            // 获取到合适的list
            block *list = free_list[get_free_list_index(size)];
            // 如果当前list没有可用空间，则向内存池申请内存
            if (list == nullptr) {
                void *res = refill(round_up(size));
                return res;
            }
            block *result = list;
            // 更新free list指针
            list = result->next_block;
            return result;
        }

        static void deallocate(void *ptr, size_t size) {
            // 如果 > 128byte则调用free
            if (size > MAX_BYTES) {
                return AllocByMalloc::deallocate(ptr, size);
            }
            block *data = static_cast<block *>(ptr);
            block *list = free_list[get_free_list_index(size)];
            data->next_block = list;
            // 将ptr作为新的list头节点
            *list = *data;
        }

        static void *reallocate(void *ptr, size_t old_size, size_t new_size);

    private:
        static char *start_free;
        static char *end_free;
        static size_t heap_size;
        /**
         * free list
         * 使用 volatile 关键字修饰，告诉编译器free list是会被某些因素修改的
         * 编译器不会对free list的访问进行优化，从而获得访问地址的稳定性
         */
        static block *volatile free_list[LIST_NUMBER];

        static size_t round_up(size_t size) {
            return (size / ALIGN) * ALIGN + ALIGN;
        }

        static size_t get_free_list_index(size_t size) {
            return size / ALIGN;
        }

        static void *refill(size_t size);

        static void *chunk_alloc(size_t size);
    };

    block *volatile AllocByFreeList::free_list[LIST_NUMBER] = {};

    class Alloc {

    };

}


#endif //MICROSTL_ALLOC_H
