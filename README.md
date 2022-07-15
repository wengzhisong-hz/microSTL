## 模块进度

| 迭代器 _iterator      | 空间配置器 allocator        | 容器 container | 算法 algorithm | 仿函数 functor | 适配器 adaptor |
|-------------------|------------------------|--------------|--------------|-------------|-------------|
| ✅ _iterator class  | ✅ constructor          | ✅ vector     | ✍️ 基本算法      |             |             |
| ✅ iterator_traits | ✅ destructor           | list         |              |             |             |
| ✅ type_traits     | ✅ allocator(malloc)    |              |              |             |             |
|                   | ✅ allocator(free list) |              |              |             |             |
|                   | ✅ uninitialized        |              |              |             |             |

## 测试覆盖

| 迭代器 _iterator      | 空间配置器 allocator        | 容器 container | 算法 algorithm | 仿函数 functor | 适配器 adaptor |
|-------------------|------------------------|--------------|--------------|-------------|-------------|
| ✅ iterator_traits | ✅ constructor          | ✅ vector     | ✍️ 基本算法      |             |             |
| ✅ type_traits     | ✅ destructor           | list         |              |             |             |
|                   | ✅ allocator(malloc)    |              |              |             |             |
|                   | ✅ allocator(free list) |              |              |             |             |
|                   | ✍️ uninitialized       |              |              |             |             |
