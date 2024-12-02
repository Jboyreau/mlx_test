#include "test.h"

//TODO void updateCameraTranslations()
//TODO void updateCameraRotations()
//TODO void updateModelTranslations()

void updateCursor(t_vec2 *cursor, char *keysState)
{
	if (*(keysState + XK_Right))
			(*cursor).x += CURSOR_SPEED * (((*cursor).x + CURSOR_SPEED) < SWIDTH);
	else if (*(keysState + XK_Left))
			(*cursor).x -= CURSOR_SPEED * (((*cursor).x - CURSOR_SPEED) > -SWIDTH);
	if (*(keysState + XK_Up))
			(*cursor).y -= CURSOR_SPEED * (((*cursor).y - CURSOR_SPEED) > -SHEIGHT);
	else if (*(keysState + XK_Down))
			(*cursor).y += CURSOR_SPEED * (((*cursor).y + CURSOR_SPEED) < SHEIGHT);
}

void updateModelRotations(t_vec3 *angles, char *keysState)
{
	if (*(keysState + XK_Right))
			(*angles).y = ROTATION_MODEL_STEP;
	else if (*(keysState + XK_Left))
			(*angles).y = -ROTATION_MODEL_STEP;
	else 
		(*angles).y = 0;
	if (*(keysState + XK_Up))
			(*angles).x = ROTATION_MODEL_STEP;
	else if (*(keysState + XK_Down))
			(*angles).x = -ROTATION_MODEL_STEP;
	else 
		(*angles).x = 0;
}

void translateScaleModel(t_vec3 *translations, char *keysState, float *zoom, float step)
{
	if (*(keysState + XK_KP_Add))
		*zoom += ZOOM_STEP;
	else if (*(keysState + XK_KP_Subtract))
		*zoom -= ZOOM_STEP;
	if (*(keysState + XK_w))
		(*translations).z -= step;
	else if (*(keysState + XK_s))
		(*translations).z += step;
	if (*(keysState + XK_d))
		(*translations).x -= step;
	else if (*(keysState + XK_a))
		(*translations).x += step;
	if (*(keysState + XK_Page_Up))
		(*translations).y += step;
	else if (*(keysState + XK_Page_Down))
		(*translations).y -= step;
}
