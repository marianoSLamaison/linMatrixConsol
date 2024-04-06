dlinks := -lncurses

matrixConsole:objects/matrixScreen.o objects/FallingL.o objects/utils.o
	gcc $(^) -o $(@) $(dlinks)
objects/matrixScreen.o: src/matrixScreen.c
	gcc -c $(^) -o $(@) $(dlinks)
objects/FallingL.o: src/TADs/FallingL.c
	gcc -c $^ -o $@ $(dlinks)
objects/utils.o: src/utils.c
	gcc -c $^ -o $@ $(dlinks)
