#include "test.h"

int main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	(void)argc;(void)argv;

	//Intialisation.
	mlx = mlx_init();
	if (mlx == NULL)
		return 0;
	//Create window.
	mlx_win = mlx_new_window(mlx, WIDTH, HIGHT, "MLX_TEST!");
	if (mlx_win == NULL)
		return 0;
	//Image initialisation.
	img.img = mlx_new_image(mlx, WIDTH, HIGHT);
	if (img.img == NULL)
		return 0;
	img.addr = (int *)mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	//TEST red screen.
	for (int i = 0; i < WIDTH * HIGHT; ++i)
		*(img.addr + i) = BACKGROUND_COLOR;
	
	//Display image.
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	//Hooks aka Input Handlers.
	mlx_hook(mlx_win, 17, 0, close_window, NULL);
	//TODO study hooks.
	//Start GameLoop.	
	mlx_loop(mlx);
	return 0;
}
