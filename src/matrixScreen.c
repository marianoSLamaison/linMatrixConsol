#include<stdio.h>
#include<ncurses.h>
#include<string.h>
#include<unistd.h>
#include<time.h>

typedef struct CHAR_LINE{
	unsigned int xpos;//posicion de la linea
	unsigned int pie;//fondo de la linea
	unsigned int cabeza;//tope de line
	//no necesito almacenar la linea, ncurses lo hara por mi
} falling_l;

void draw_char_of_line(falling_l * line);

int main(void)
{
	unsigned int maxy, maxx;
	initscr();
	falling_l line = {3, 2, 5};
	unsigned i = 0;
	for ( ; i < 3; i++)
	{
		draw_char_of_line(&line);
		refresh();
		sleep(1);
	}
	getch();
	endwin();
	return 0;
};
//TODO
void restart_line(falling_l * line){}

void draw_char_of_line(falling_l * line)
{
	// si hay algo que dibujar, se dibuja un solo caracter
	if ( line->pie <= line->cabeza )
	{
		mvaddch(line->pie, line->xpos, ACS_BLOCK);
		line->pie++;
	}
	else//si no, solo se reinicia
		restart_line(line);
}
