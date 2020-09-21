## makefile文件的编写（[makefile示例](../code/operatorOverload/makefile)）

#### 什么是makefile？
makefile文件定义了一个工程文件的编译和链接规则。

- 使得项目工程的编译变得自动化
- makefile支持多线程并发，缩短编译时间
- 当修改了源文件后，再次编译整个工程，make命令会只编译我们修改过的文件。
### 例程文件系统介绍
在这个工程中，共有两个文件
- main.cpp
- Triangular.h

编译main.cpp的时候，依赖Triangular.h文件。 那么，针对上面两个文件的makefile文件，可以编写如下

```
objects = main.o
cc = g++

test : $(objects)
	$(cc) -o test $(objects)

main.o : main.cpp Triangular.h
	$(cc) -c main.cpp

.PHONY:clean
clean:
	@echo "cleaning files..."
    rm $(objects) test
	@echo "clean done!"
```

#### 参考链接
- [跟我一起写makefile v1.0]()
