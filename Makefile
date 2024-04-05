dlinks := -lncurses

srcVimStuff := $(wildcard *~)

matrixConsole: objects/matrixScreen.o
	gcc $^ -o $@ $(dlinks)
objects/matrixScreen.o: src/matrixScreen.c
	gcc -c $^ -o $@ $(dlinks)
