#ifndef MICROSTL_ALLOC_H
#define MICROSTL_ALLOC_H


namespace MicroSTL {
    /**
         * 定义函数指针
         */
    using fn_ptr = void (*)();

    inline void throw_bad_alloc() {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    class Alloc {

    };

    class AllocByFreeList {

    };

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
         * oom handler 接收一个用户自定义的 oom 处理函数，并返回原先的 oom 处理函数
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
}


#endif //MICROSTL_ALLOC_H
