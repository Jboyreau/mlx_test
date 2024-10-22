#include "test.h"

int gameLoop(t_scene *scene)
{
	t_camera *camera = (*scene).camera;
	(void)camera;
	
	clear(scene);
	updateCursor(&((*(*scene).screenSpace).cursor), (*scene).keysState);
	drawSquare(scene, 10, (*(*scene).screenSpace).cursor);

	//Display image.
	mlx_put_image_to_window(
		(*(*scene).img).mlx,
		(*(*scene).img).mlx_win,
		(*(*scene).img).img,
		0,
		0);
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

void initScreenSpace(t_screenSpace *screenSpace)
{
	(*screenSpace).xOffset = WIDTH / 2;
	(*screenSpace).yOffset = HIGHT / 2;
	((*screenSpace).cursor).x = 0;
	((*screenSpace).cursor).y = 0;
}

void initKeysState(char *keysState)
{
	for (int i = 0; i < KEYSIZE; ++i)
		*(keysState + i) = 0;
}

int main(int argc, char **argv)
{
	t_data	img;
	t_camera camera;
	t_screenSpace screenSpace;
	t_scene scene = {.camera = &camera, .screenSpace = &screenSpace, .img = &img};

	(void)argc;(void)argv;

	//Creation window/colorBuffer.
	if (!houseKeeping(&img))
		return 1;

	//scene initialisation.
	initCamera(&camera);
	initScreenSpace(&screenSpace);
	initKeysState(scene.keysState);

	//Hooks aka Input Handlers.
	ft_input(&scene);

	//Start GameLoop.	
	mlx_loop_hook(img.mlx, gameLoop, &scene);
	mlx_loop(img.mlx);
	return 0;
}
