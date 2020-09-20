## makefile文件的编写（[makefile示例](../code/operatorOverload/makefile)）

#### 什么时makefile？



### 例程文件系统介绍
在这个工程中，共有两个文件
- main.cpp
- Triangular.h

编译main.cpp文件的时候，依赖Triangular.h文件。

那么，针对上面两个文件的makefile文件，可以编写如下

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


