#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include<string.h>
#include<unistd.h>
#include<time.h>

#define VACIO '\0'
#define OLD_CHAR 1
#define NEW_CHAR 2

typedef struct CHAR_LINE{
	unsigned int xpos;//posicion de la linea
	unsigned int pie;//fondo de la linea
	unsigned int cabeza;//tope de line
	char ant_char;//caracter anterior lo usamos para cambiar el color
	//de los caracteres
	//no necesito almacenar la linea, ncurses lo hara por mi
} falling_l;

int draw_char_of_line(falling_l * line);

int main(void)
{
	unsigned int maxy, maxx;
	initscr();
	start_color();
	//iniciamos los colores
	init_pair(OLD_CHAR, COLOR_GREEN, COLOR_BLACK);
	init_pair(NEW_CHAR, COLOR_WHITE, COLOR_BLACK);
	falling_l line = {1, 0, 4, VACIO};
	unsigned i = 0;
	while ( draw_char_of_line(&line) > 0 )
	{
		refresh();
		sleep(1);
	}
	getch();
	endwin();
	return 0;
};
//TODO
void restart_line(falling_l * line){}

void print_color_char(unsigned int y, unsigned int x,
		      const char ch, const int color_pair)
{
	attron(COLOR_PAIR(color_pair));
	mvaddch(y, x, ch);
	attroff(COLOR_PAIR(color_pair));
};

int draw_char_of_line(falling_l * line)
{
	
	// si hay algo que dibujar, se dibuja un solo caracter
	if ( line->pie < line->cabeza )
	{
		if ( line->ant_char != VACIO )
		{
			print_color_char(line->pie - 1, line->xpos,
				line->ant_char, OLD_CHAR);
		};
		//generamos una caracter al azar
		char r_char = (random() % (126 + 1) ) + 33;
		//escribimos el caracter
		print_color_char(line->pie, line->xpos, r_char, NEW_CHAR);
		//movemos el pie
		line->pie++;
		//actualizamos el caracter
		line->ant_char = r_char;
	}
	else
	{
		print_color_char(line->pie - 1, line->xpos,
			       	line->ant_char, OLD_CHAR);
		line->pie++;
	}
	return line->cabeza - (line->pie - 1);
}
