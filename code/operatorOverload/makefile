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
