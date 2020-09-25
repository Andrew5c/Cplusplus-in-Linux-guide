objects = main.o num_seq.o fib.o
cc = g++

TEST : $(objects)
	$(cc) -o TEST $(objects)

main.o : num_seq.h num_seq.cpp fib.h fib.cpp
num_seq.o : num_seq.h
fib.o : num_seq.h num_seq.cpp fib.h

.PHONY:clean
clean:
	@echo "cleaning files..."
	rm $(objects) TEST
	@echo "clean done!"