## 模块进度

| 迭代器 iterator      | 空间配置器 allocator        | 容器 container | 算法 algorithm | 仿函数 functor | 适配器 adaptor |
|-------------------|------------------------|--------------|--------------|-------------|-------------|
| ✅ iterator class  | ✅ constructor          | ✅ vector     | ✍️ 基本算法      |             |             |
| ✅ iterator_traits | ✅ destructor           | list         |              |             |             |
| ✅ type_traits     | ✅ allocator(malloc)    |              |              |             |             |
|                   | ✅ allocator(free list) |              |              |             |             |
|                   | ✅ alloc(包装接口)          |              |              |             |             |
|                   | ✅ uninitialized        |              |              |             |             |

## 测试覆盖

| 迭代器 iterator       | 空间配置器 allocator        | 容器 container | 算法 algorithm | 仿函数 functor | 适配器 adaptor |
|--------------------|------------------------|--------------|--------------|-------------|-------------|
| 🈚️ iterator class | ✅ constructor          | ✅ vector     | ✍️ 基本算法      |             |             |
| ✅ iterator_traits  | ✅ destructor           | list         |              |             |             |
| ✅ type_traits      | ✅ allocator(malloc)    |              |              |             |             |
|                    | ✅ allocator(free list) |              |              |             |             |
|                    | 🈚️ alloc(包装接口)        |              |              |             |             |
|                    | ✍️ uninitialized       |              |              |             |             |
