#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include<ctype.h>

#define VACIO '\0'
#define OLD_CHAR 1
#define NEW_CHAR 2

//queria usar un macro a modo de funcion nada mas
#define randrange(INICIO, FIN) (random() % ( (FIN) - (INICIO) )) + (INICIO)

void print_color_char(unsigned int y, unsigned int x,
		      const char ch, const int color_pair);
