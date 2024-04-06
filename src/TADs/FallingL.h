//structura de linea callente
typedef struct CHAR_LINE{
	unsigned int inicio;//fondo de la linea
	unsigned int act_pos;//en que parte de la linea estoy
	unsigned int fin;//tope de line
	unsigned int cleaner_pos;//posicion del limpiador
	char ant_char;//caracter anterior lo usamos para cambiar el color
	//de los caracteres
	//no necesito almacenar la linea, ncurses lo hara por mi
} Falling_l;

//para poder seguir con el efecto
void restart_line(Falling_l * line);
//llenar una lista de lineas
void start_fallin_l_array(Falling_l arr[], size_t size);
//dibujar un solo caracter de la linea
int draw_char_of_line(Falling_l * line, unsigned int xpos);
