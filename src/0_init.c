#include "test.h"

void initCamera(t_camera *camera)
{
	(*camera).focalDistance = FOCAL_DISTANCE;
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
