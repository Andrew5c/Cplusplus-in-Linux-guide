objects = main.o btNode.o binaryTree.o
cc = g++

test:$(objects)
	$(cc) -o test $(objects)

main.o : binaryTree.cpp binaryTree.h btNode.cpp btNode.h
binaryTree.o : binaryTree.h btNode.cpp btNode.h
btNode.o : btNode.h binaryTree.h

.PHONY:clean
clean:
	-rm test $(objects)
	@echo "rm test files..."