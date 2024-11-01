#include "test.h"

int gameLoop(t_scene *scene)
{
	t_camera *camera = (*scene).camera;
	(void)camera;
	
	clear(scene);
	updateCursor(&((*(*scene).screenSpace).cursor), (*scene).keysState);
	drawSquare(scene, CURSOR_SIZE, (*(*scene).screenSpace).cursor);

	//Display image.
	mlx_put_image_to_window(
		(*scene).mlx,
		(*scene).mlx_win,
		(*scene).img,
		0,
		0);	
	sprintf((*(t_scene *)scene).str, "x = %d; y = %d", (*(t_scene *)scene).x, (*(t_scene *)scene).y);
	mlx_string_put((*(t_scene *)scene).mlx, (*(t_scene *)scene).mlx_win, WIDTH >> 5, HEIGHT >> 5, 0, (*(t_scene *)scene).str);
	return 0;
}

void initCamera(t_camera *camera)
{
	(*camera).focalDistance = 5;
	((*camera).rotations).x = 0;
	((*camera).rotations).y = 0;
	((*camera).translations).x = 0;
	((*camera).translations).y = 0;
	((*camera).translations).z = 0;
}

void initScreenSpace(t_screenSpace *screenSpace, t_data *img)
{
	(*screenSpace).colorBuffer = (*img).addr;
	(*screenSpace).xOffset = WIDTH / 2;
	(*screenSpace).yOffset = HEIGHT / 2;
	((*screenSpace).cursor).x = 0;
	((*screenSpace).cursor).y = 0;
}

void initScene(t_scene *scene, t_data *img, t_camera *camera, t_screenSpace *screenSpace)
{
	(*scene).camera = camera;
	(*scene).screenSpace = screenSpace;
	(*scene).mlx = (*img).mlx;
	(*scene).mlx_win = (*img).mlx_win;
	(*scene).img = (*img).img;
	for (int i = 0; i < KEYSIZE; ++i)
		*(((*scene).keysState) + i) = 0;
	for (int i = 0; i < 1000; ++i)
		*(((*scene).str) + i) = 0;
}

int main(int argc, char **argv)
{
	t_data	img;
	t_camera camera;
	t_screenSpace screenSpace;
	t_scene scene;

	(void)argc;(void)argv;

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
