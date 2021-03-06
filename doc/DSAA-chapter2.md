## 《DSAA》第二章——程序性能分析

### 什么是程序性能？
> 程序性能是指运行这个程序所需要的内存和时间的多少。

两种方法确定：
- 性能分析
- 性能测量


- **空间复杂度**：程序运行所需要的内存大小
- **时间复杂度**：程序运行所需要的时间

## 空间复杂度
1. 组成
    - 指令空间 ： 编译之后，程序指令所需要的存储空间
    - 数据空间 ： 常量、简单变量、动态数组、动态类实例等
    - 环境栈空间 ： 保存暂停的函数在恢复运行时需要的信息，比如函数入口，中间变量等

**程序要处理的问题都有一些实例特征，这些特征都包含着可以决定程序空间大小的因素，称为 实例特征**

- 环境栈的大小一般不依赖于实例特征，但是在递归函数中，实例特征会影响环境栈的大小。
- 递归函数需要的栈空间，通常称为 递归栈空间


一个程序所需要的空间可以被分为：
- 固定部分（c）：独立于实例特征，包括指令空间，简单变量，常量等
- 可变部分（Sp）：由动态分配空间和递归栈空间组成，在后面将被集中计算

**任意程序P所需要的空间 = c + Sp**