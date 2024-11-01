#include "test.h"

int close_window(void *mlx)
{
	mlx_loop_end(mlx);
    return (0);
}

int keyPress(int keycode, void *keysState)
{
	(void)keysState;
	*((char *)keysState + keycode) = 1;
	return 0;
}

int keyRelease(int keycode, void *keysState)
{
	(void)keysState;
	*((char *)keysState + keycode) = 0;
	return 0;
}

int displayMouseCoordinates(int x, int y, void *scene)
{
	(*(t_scene *)scene).x = x;
	(*(t_scene *)scene).y = y;
	//sprintf((*(t_scene *)scene).str, "x = %d; y = %d", (*(t_scene *)scene).x, (*(t_scene *)scene).y);
	//mlx_string_put((*(*(t_scene *)scene).img).mlx, (*(*(t_scene *)scene).img).mlx_win, 40, 30, 0, (*(t_scene *)scene).str);
	return 0;
}

void ft_input(t_scene *scene)
{
	mlx_hook((*scene).mlx_win, 17, 0, close_window, (*scene).mlx);
	mlx_hook((*scene).mlx_win, 2, 1L<<0, keyPress, (*scene).keysState);
	mlx_hook((*scene).mlx_win, 3, 1L<<1, keyRelease, (*scene).keysState);	
	mlx_hook((*scene).mlx_win, 6, 1L<<6, displayMouseCoordinates, scene);	
}
