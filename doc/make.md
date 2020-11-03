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





### 总结
- make， 自动化编译工具，用户需要编写makefile文件来指定编译规则和依赖文件，然后make工具读取makefile文件来进行批处理编译，但是对于大型工程，自行编写makefile文件较为繁琐。

- Cmake，跨平台编译工具，比make更为高级，使用起来较为方便。用户需要编写CMakeList.txt文件来指定编译规则，然后cmake命令将该文件转化为make需要的makefile文件。最后再进行make的相关操作。



#### 参考链接
- [跟我一起写makefile v1.0](https://seisman.github.io/how-to-write-makefile/index.html)

