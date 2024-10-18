#include "test.h"

int close_window(int keycode, void *param)
{
    (void)keycode;
    (void)param;
    exit(0); // Quitter proprement le programme
    return (0);
}

void ft_input(void)
{
	;
}
