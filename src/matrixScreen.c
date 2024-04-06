#include "utils.h"
#include "TADs/FallingL.h"
#define TIME_STEP 100 //milisegundos
#define ESCAPE 'E'

//iniciamos la animacion de lluvia
void matrix_rain_v1(void);

int main(void)
{
	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, 1);
	timeout(TIME_STEP);
	//iniciamos los colores
	init_pair(OLD_CHAR, COLOR_GREEN, COLOR_BLACK);
	init_pair(NEW_CHAR, COLOR_WHITE, COLOR_BLACK);
	matrix_rain_v1();
	getch();
	endwin();
	return 0;
};

void matrix_rain_v1(void)
{
	Falling_l lines[COLS];
	start_fallin_l_array(lines, COLS);
	char ch;
	unsigned int i = 0;
	unsigned int * cl_pos;
	int line_state;
	while ( toupper(ch = getch()) != ESCAPE )
	{
		while ( i < COLS )
		{
			line_state = draw_char_of_line(lines + i, i);

			cl_pos = &(lines + i)->cleaner_pos;

			mvaddch((*cl_pos),i,' ');
			*cl_pos += 1;

			if ( line_state < 0 )
				restart_line(lines + i);
			if (*cl_pos >= COLS - 1 )
				*cl_pos = 0;
			i++;
		}
		i = 0;
	};
};
