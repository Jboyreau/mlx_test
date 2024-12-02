#include "test.h"

int gameLoop(t_scene *scene)
{
	//t_camera *camera = (*scene).camera;
	//(void)camera;

	clear(scene);
//	updateCursor(&((*(*scene).screenSpace).cursor), (*scene).keysState);
	translateScaleModel(&((*(*scene).camera).translations), (*scene).keysState, &((*(*scene).camera).zoom), (*(*scene).camera).step);
	updateModelRotations(&((*(*scene).camera).modelRotations), (*scene).keysState);
//	drawSquare(scene, CURSOR_SIZE, (*(*scene).screenSpace).cursor);
	if (*((*scene).keysState + KEYSIZE - 1))
		projectIso((*scene).camera, (*scene).screenSpace, scene, 0);
	else
		project((*scene).camera, (*scene).screenSpace, scene, 0);
	//Display image.
	mlx_put_image_to_window(
		(*scene).mlx,
		(*scene).mlx_win,
		(*scene).img,
		0,
		0);
	//print mouse coordinates.	
	mlx_string_put((*(t_scene *)scene).mlx, (*(t_scene *)scene).mlx_win, 50, 40, 0, "UP       : PageUP.");
	mlx_string_put((*(t_scene *)scene).mlx, (*(t_scene *)scene).mlx_win, 50, 60, 0, "DOWN     : PageDown.");
	mlx_string_put((*(t_scene *)scene).mlx, (*(t_scene *)scene).mlx_win, 50, 80, 0, "FORWARD  : w.");
	mlx_string_put((*(t_scene *)scene).mlx, (*(t_scene *)scene).mlx_win, 50, 100, 0,"BACKWARD : s.");
	mlx_string_put((*(t_scene *)scene).mlx, (*(t_scene *)scene).mlx_win, 50, 120, 0,"LEFT     : a.");
	mlx_string_put((*(t_scene *)scene).mlx, (*(t_scene *)scene).mlx_win, 50, 140, 0,"RIGHT    : d.");
	mlx_string_put((*(t_scene *)scene).mlx, (*(t_scene *)scene).mlx_win, 50, 160, 0,"Persp    : p.");
	mlx_string_put((*(t_scene *)scene).mlx, (*(t_scene *)scene).mlx_win, 50, 180, 0,"ISO      : i.");
	mlx_string_put((*(t_scene *)scene).mlx, (*(t_scene *)scene).mlx_win, 50, 200, 0,"Rotation : arrrows.");
	if (*((*scene).keysState + XK_Escape))
		mlx_loop_end((*scene).mlx);
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
	parsing(*(argv + 1), &camera, &screenSpace);
	if (camera.model == NULL)
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

	//Move the mouse to the center.
	mlx_mouse_move(img.mlx, img.mlx_win, WIDTH / 2, HEIGHT / 2);

	//Start GameLoop.	
	mlx_loop_hook(img.mlx, gameLoop, &scene);
	mlx_loop(img.mlx);
	return (free(camera.model), 0);
}
