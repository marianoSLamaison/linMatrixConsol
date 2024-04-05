#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>

#define VACIO '\0'
#define OLD_CHAR 1
#define NEW_CHAR 2

#define TIME_STEP 100 //milisegundos

typedef struct CHAR_LINE{
	unsigned int inicio;//fondo de la linea
	unsigned int act_pos;//en que parte de la linea estoy
	unsigned int fin;//tope de line
	unsigned int cleaner_pos;//posicion del limpiador
	char ant_char;//caracter anterior lo usamos para cambiar el color
	//de los caracteres
	//no necesito almacenar la linea, ncurses lo hara por mi
} Falling_l;

//crear una sola linea
Falling_l create_falling_line(unsigned int xpos);
//para poder seguir con el efecto
void restart_line(Falling_l * line);
//llenar una lista de lineas
void start_fallin_l_array(Falling_l arr[], size_t size);
//dibujar un solo caracter de la linea
int draw_char_of_line(Falling_l * line, unsigned int xpos);
//iniciamos la animacion de lluvia
void matrix_rain_v1(void);

int main(void)
{
	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, 1);
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
	timeout(TIME_STEP);
	while ( (ch = getch()) != 'e' )
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
}

int randrange(unsigned inicio, unsigned fin)
{
	return (random() % (fin - inicio)) + inicio;
};

Falling_l create_falling_line(unsigned int xpos)
{
	unsigned int inicio, fin;
	inicio = randrange(0, LINES - 1);
	fin = randrange(inicio, LINES);
	Falling_l line = {inicio, inicio, fin, inicio + 1, VACIO};
	return line;
}

void start_fallin_l_array(Falling_l arr[], size_t size)
{
	unsigned int i = 0;
	for ( ; i < size; i++)
		arr[i] = create_falling_line(i);
}

void restart_line(Falling_l * line)
{
	line->cleaner_pos = line->inicio;
	line->inicio = randrange(0, LINES - 1);
	line->fin = randrange(line->inicio, LINES);
	line->act_pos = line->inicio;
	line->ant_char = VACIO;
}

void print_color_char(unsigned int y, unsigned int x,
		      const char ch, const int color_pair)
{
	attron(COLOR_PAIR(color_pair));
	mvaddch(y, x, ch);
	attroff(COLOR_PAIR(color_pair));
};

int draw_char_of_line(Falling_l * line, unsigned int xpos)
{
	// si hay algo que dibujar, se dibuja un solo caracter
	if ( line->act_pos < line->fin )
	{
		if ( line->ant_char != VACIO )
		{
			print_color_char(line->act_pos - 1, xpos,
				line->ant_char, OLD_CHAR);
		};
		//generamos una caracter al azar
		char r_char = randrange(33, 122);
		//escribimos el caracter
		print_color_char(line->act_pos, xpos, r_char, NEW_CHAR);
		//movemos el pie
		line->act_pos++;
		//actualizamos el caracter
		line->ant_char = r_char;
	}
	else
	{
		print_color_char(line->act_pos - 1, xpos,
			       	line->ant_char, OLD_CHAR);
		line->act_pos++;
	}
	//la limpieza del carril se realiza fuera de esta funcion
	return line->fin - (line->act_pos - 1);
}
