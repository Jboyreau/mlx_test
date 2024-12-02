#include "test.h"

void initCamera(t_camera *camera)
{
	(*camera).step = ((float)((*camera).modelHeight) * (float)STEP) / (float)REF_MODEF_DEPTH;
	(*camera).zoom = ZOOM;
	(*camera).focalDistance = FOCAL_DISTANCE;
	((*camera).rotations).x = 0;
	((*camera).rotations).y = 0;
	((*camera).modelRotations).x = 0;
	((*camera).modelRotations).y = 0;
	((*camera).modelRotations).z = 0;
	((*camera).translations).x = X;
	((*camera).translations).y = Y;
}

void initScreenSpace(t_screenSpace *screenSpace, t_data *img)
{
	(*screenSpace).colorBuffer = (*img).addr;
	(*screenSpace).xOffset = SWIDTH;
	(*screenSpace).yOffset = SHEIGHT;
	((*screenSpace).cursor).x = 0;
	((*screenSpace).cursor).y = 0;
}

void initScene(t_scene *scene, t_data *img, t_camera *camera, t_screenSpace *screenSpace)
{
	((*scene).mouse_coord).x = 0;
	((*scene).mouse_coord).y = 0;
	(*scene).camera = camera;
	(*scene).screenSpace = screenSpace;
	(*scene).mlx = (*img).mlx;
	(*scene).mlx_win = (*img).mlx_win;
	(*scene).img = (*img).img;
	for (int i = 0; i < KEYSIZE; ++i)
		*(((*scene).keysState) + i) = 0;
	for (int i = 0; i < STR_SIZE; ++i)
		*(((*scene).str) + i) = 0;
}
