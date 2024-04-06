#include "utils.h"

void print_color_char(unsigned int y, unsigned int x,
		      const char ch, const int color_pair)
{
	attron(COLOR_PAIR(color_pair));
	mvaddch(y, x, ch);
	attroff(COLOR_PAIR(color_pair));
};
