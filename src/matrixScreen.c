#include<stdio.h>
#include<ncurses.h>

int main(void)
{
	unsigned int maxy, maxx;
	initscr();
	getmaxyx(stdscr, maxy, maxx);
	printw("Las dimensiones de la ventana son:\n<%2d, %2d>\n",maxx,maxy);
	getch();
	endwin();
	return 0;
};
