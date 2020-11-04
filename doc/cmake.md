## 学习使用 CMake

> 这里建议直接看参考文章下面的链接，写的非常好。这里只是简单做一下自己学习的笔记。

Cmake，跨平台编译工具，比make更为高级，使用起来较为方便。用户需要编写CMakeList.txt文件来指定编译规则，然后cmake命令将该文件转化为make需要的makefile文件。最后再进行make的相关操作。

- CMakeLists.txt 的语法比较简单，由命令、注释、空格组成
- 命令不区分大小写
- `#`后面的内容被认为是注释
- 参数之间用空格进行间隔
- CMakeLists.txt中的命令并不是被cmake给按顺序执行的，它相当于一系列的声明

### linux下使用cmake的步骤
1. 编写cmake的配置文件CMakeList.txt，一般放在工程目录下面
2. 执行命令`cmake PATH`来生成makefile文件。在linux平台下面通常在工程目录下面新建`build`文件夹，然后在build中执行`cmake ..`
3. 在上面的build文件夹中使用`make`命令编译


### case1：多个源文件都在一个文件夹中

这样只需要在根目录下面编写一个CMakeLists.txt文件即可。
```cmake
# cmake 最低版本要求 
cmake_minimum_required (VERSION 2.8) 

# 项目信息 
project (sortAlgorithm)

# 查找当前目录下的所有源文件
# 并保存到SRCS变量中
aux_source_directory (. SRCS)

# 引用上面的变量，指定生成的目标
add_executable (sort ${SRCS})
```
工程文件展示：[一个文件夹，多个源文件](../code/sortAlgorithm/)


### case2：多个源文件分布在多个文件夹中
- 需要在工程根目录下面编写一个CMakeLists.txt文件，然后下面的每一个文件夹中都需要编写一个CMakeLists.txt，将该文件夹中的源文件都编译为一个**静态链接库**，然后由顶层的文件调用。
- 子文件夹中的txt文件会被根目录中的txt文件调用执行。

**特别注意**
根目录下面的txt文件中使用`add_subdirectory()` 添加子目录的时候，它原理上应该是把子目录中的txt文件插入到当前的txt文件中了。所以要特别注意这两个txt文件中的全局变量的声明，不要重名，不然cmake会迷茫。

工程文件展示：[多个文件夹，多个源文件](../code/cmakeDemo/demo1/)

**根目录下的CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)

project(DEMO1)

# 搜索源文件
aux_source_directory(. SRCS)

# 添加子目录
# 此时它会进入该子目录搜索txt文件并执行
add_subdirectory(sort)

# 生成指定目标文件
add_executable(demo main.cpp)

# 添加链接库
target_link_libraries(demo sort1)
```


**子目录下的CMakeLists.txt**
```cmake
# 查找源文件
# 注意这个命令中的变量不要与上面的重复
aux_source_directory(. DIR_LIB_SRCS)

# 生成静态链接库
add_library(sort1 ${DIR_LIB_SRCS})
```


### 总结
- make， 自动化编译工具，用户需要编写makefile文件来指定编译规则和依赖文件，然后make工具读取makefile文件来进行批处理编译，但是对于大型工程，自行编写makefile文件较为繁琐。

- Cmake，跨平台编译工具，比make更为高级，使用起来较为方便。用户需要编写CMakeList.txt文件来指定编译规则，然后cmake命令将该文件转化为make需要的makefile文件。最后再进行make的相关操作。



#### 参考文章
- [cmake入门实战](https://www.hahack.com/codes/cmake/)

---

## 静态、动态链接库
