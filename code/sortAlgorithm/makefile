objects = main.o sort.o
cc = g++

test : $(objects)
	$(cc) -o test $(objects)

main.o sort.o : sort.h sort.cpp

.PHONY:clean
clean:
	-rm $(objects) test
	@echo "clean files done."
