#ifndef COLOR_H
#define COLOR_H
	typedef enum{
		BLACK,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE
	}COULEUR_TERMINAL;
	void clear_terminal();
	int color_printf(COULEUR_TERMINAL fg, COULEUR_TERMINAL bg, const char * format, ...);
#endif
