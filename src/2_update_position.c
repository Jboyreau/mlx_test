#include "test.h"

//TODO void updateCameraTranslations()
//TODO void updateCameraRotations()
//TODO void updateModelTranslations()
//TODO void updateModelRotations()

void updateCursor(t_vec2 *cursor, char *keysState, void *mlx)
{
	if (*(keysState + XK_Right))
			(*cursor).x += CURSOR_SPEED * (((*cursor).x + CURSOR_SPEED) < SWIDTH);
	else if (*(keysState + XK_Left))
			(*cursor).x -= CURSOR_SPEED * (((*cursor).x - CURSOR_SPEED) > -SWIDTH);
	if (*(keysState + XK_Up))
			(*cursor).y -= CURSOR_SPEED * (((*cursor).y - CURSOR_SPEED) > -SHEIGHT);
	else if (*(keysState + XK_Down))
			(*cursor).y += CURSOR_SPEED * (((*cursor).y + CURSOR_SPEED) < SHEIGHT);	
	if (*(keysState + XK_Escape))
		mlx_loop_end(mlx);
}

void translateScaleModel(t_vec3 *translations, char *keysState, float *zoom)
{
	if (*(keysState + XK_KP_Add))
		*zoom += 0.1;
	else if (*(keysState + XK_KP_Subtract))
		*zoom -= 0.1;
	if (*(keysState + XK_w))
		(*translations).z -= 0.1;
	else if (*(keysState + XK_s))
		(*translations).z += 0.1;
	if (*(keysState + XK_d))
		(*translations).x -= 0.1;
	else if (*(keysState + XK_a))
		(*translations).x += 0.1;
	if (*(keysState + XK_Page_Up))
		(*translations).y += 0.1;
	else if (*(keysState + XK_Page_Down))
		(*translations).y -= 0.1;
}
