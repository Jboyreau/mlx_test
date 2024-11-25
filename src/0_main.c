#include "test.h"

int gameLoop(t_scene *scene)
{
	//t_camera *camera = (*scene).camera;
	//(void)camera;
	
	clear(scene);
	updateCursor(&((*(*scene).screenSpace).cursor), (*scene).keysState, (*scene).mlx);
	drawSquare(scene, CURSOR_SIZE, (*(*scene).screenSpace).cursor);

	//Display image.
	mlx_put_image_to_window(
		(*scene).mlx,
		(*scene).mlx_win,
		(*scene).img,
		0,
		0);
	//print mouse coordinates.	
	sprintf((*(t_scene *)scene).str, "x = %d; y = %d", (int)(*(t_scene *)scene).mouse_coord.x, (int)(*(t_scene *)scene).mouse_coord.y);
	mlx_string_put((*(t_scene *)scene).mlx, (*(t_scene *)scene).mlx_win, WIDTH >> 5, HEIGHT >> 5, 0, (*(t_scene *)scene).str);
	return 0;
}

int main(int argc, char **argv)
{
	t_data	img;
	t_camera camera;
	t_screenSpace screenSpace;
	t_scene scene;

	if (argc != 2)
		return (write(2, "Wrong number of argument.\n", 26));
	//map parsing
	parsing(*(argv + 1), scene);
	if (scene.model == NULL)
		return 1;
	//Creation window/colorBuffer.
	if (!houseKeeping(&img))
		return 1;

	//scene initialisation.
	initCamera(&camera);
	initScreenSpace(&screenSpace, &img);
	initScene(&scene, &img, &camera, &screenSpace);

	//Hooks aka Input Handlers.
	ft_input(&scene);

	//Start GameLoop.	
	mlx_loop_hook(img.mlx, gameLoop, &scene);
	mlx_loop(img.mlx);
	return 0;
}
