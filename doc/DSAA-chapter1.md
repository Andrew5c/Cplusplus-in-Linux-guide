## 《DSAA》第一章——C++回顾

### 二维数组
[代码示例](../code/DSAA/make2dArray.cpp)

### 自有数据类型

- 头文件中使用 `#ifndef  #endif`，保证其中的代码只被编译一次
- `#param once` 其实起到的效果和上面类似，保证同一个物理文件不会被包含多次



### 递归函数
递归函数`f(n)`必须满足的条件：
- 需要有一个基础部分，其中`f(n)`是直接定义的
- 需要有递归部分

使用递归函数实现对一个数组中的元素进行全排列。
[代码示例](../code/DSAA/permutation.cpp)

