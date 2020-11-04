## makefile文件的编写（[makefile示例](../code/operatorOverload/makefile)）

#### 程序编译的流程
源文件（编译） -> 目标文件（链接） -> 目标文件
> 有时因为源文件太多，生成了很多目标文件，而在链接阶段又需要显示的指出这些目标文件，这对于编译很不方便。
> 因此，可以给这些目标文件打包，在Windows下叫做“库文件（.lib）”

#### 什么是makefile？
makefile文件定义了一个工程文件的编译和链接规则。哪些需要先编译？后编译？重新编译？
**特点**
- 自动化编译，一旦写好makefile，只需要一个make命令，整个工程就会自动编译。
- makefile支持多线程并发，缩短编译时间。
- 当修改了源文件后，再次编译整个工程，make命令会只编译我们修改过的文件。

#### 什么是make？
- make是一个命令工具，用来解释makefile中指令的命令。

#### makefile基本规则
```
target-name : require-files
	command
	...
```
- target-name ： 可以是一个目标文件、可执行文件，或者一个标签；
- require-files ： 生成该target所依赖的文件
- command ：该target要执行的命令

**makefile核心内容**
> require-files 中，如果有一个及以上的文件比target文件要新的话（make通过比较他们的生成日期确定），或者target文件不存在时，command所定义的命令就会被执行。

#### 输入make时，发生了什么？
- make首先会在当前目录下查找makefile文件；
- 然后，继续在该路径下，找makefile中第一个目标文件（target），并把它作为最终的目标文件；
- 如果target不存在，或者它后面的文件比它新（说明文件有改动），那么会执行command来生成这个target；
- 如果target所依赖的`.o`文件也不存在，make会继续类似上面的步骤生成该`.o`文件
> make执行时，只会去寻找文件的依赖性，如果依赖文件找不到，那么make会报错。至于command是否正确，make不关心。

### 一个简单的例子（[工程文件](../code/operatorOverload)）
在这个工程中，共有两个文件：
- main.cpp
- Triangular.h

编译main.cpp的时候，依赖Triangular.h文件。 它的makefile文件可以编写如下（注释是特地在这里添加的）：
```makefile
objects = main.o   # 变量定义，方便后面使用，如果有多个目标文件，之间空格隔开即可
cc = g++    # 使用的编译器类型

test : $(objects)  # 生成可执行文件所需要的目标文件
	$(cc) -o test $(objects)    # 命令前面都要有一个TAB缩进

main.o : main.cpp Triangular.h
	$(cc) -c main.cpp

.PHONY:clean   # 表示clean是一个伪目标
clean:
	@echo "cleaning files..."  # 输出到终端
    rm $(objects) test  # 删除目标文件和可执行文件
	@echo "clean done!"
```

### 操作
- 编写完makefile文件之后；
- 直接在当前路径下执行`make`命令即可；
- 需要删除执行文件和中间文件时，执行`make clean`

### make自动推导功能（隐晦规则）
- 他会自动推导文件的依赖关系、以及它后面的命令

> make只要看到一个.o文件，就会自动把.c文件加入依赖关系，并且`cc -c main.cpp`这个命令也会被自动推导出来。

因此，上面的makefile文件可以简写如下
```makefile
objects = main.o   # 可以定义多个目标文件，方便后面使用
cc = g++    # 使用的编译器类型

test : $(objects)  # 生成可执行文件所需要的目标文件
	$(cc) -o test $(objects)    # 命令前面都要有一个TAB缩进

main.o : Triangular.h

.PHONY:clean
clean:
	@echo "cleaning files..."
    rm $(objects) test
	@echo "clean done!"
```

- [一个稍微复杂的例子](../code/abstractClass)

### makefile文件的命名
- 最好使用`makefile`或者`Makefile`，这是make会去自动搜索的文件
- 使用其他文件名时，比如`myMake`，可以使用`make -f myMake`命令来指定特殊的文件



**makefile在一些简单的工程下，可以人工手写拿下，但是当工程量比较大的时候，手写makefile比较繁琐。并且换了平台之后，makefile文件需要重新修改。这个时候，可以考虑使用Cmake工具**


---

## 使用Cmake
> 这里建议直接看参考文章中的第二个链接，写的非常好。这里只是简单做一下自己学习的笔记。

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
- [跟我一起写makefile v1.0](https://seisman.github.io/how-to-write-makefile/index.html)
- [cmake入门实战](https://www.hahack.com/codes/cmake/)


---

## 静态、动态链接库


