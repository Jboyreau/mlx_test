#include "test.h"

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

void translateScaleModel(t_camera *camera, char *keysState, float *zoom, float step)
{
	if (*(keysState + XK_KP_Add))
		*zoom += ZOOM_STEP;
	else if (*(keysState + XK_KP_Subtract))
		*zoom -= ZOOM_STEP;
	if (*(keysState + XK_z))
	{
		(*camera).translations.z -= step * (*camera).angleY.cos;
		(*camera).translations.x -= step * (*camera).angleY.sin;
	}
	else if (*(keysState + XK_s))
	{
		(*camera).translations.z += step * (*camera).angleY.cos;
		(*camera).translations.x += step * (*camera).angleY.sin;
	}
	if (*(keysState + XK_d))
	{
		(*camera).translations.x -= step * (*camera).angleY.cos;
		(*camera).translations.z += step * (*camera).angleY.sin;
	}
	else if (*(keysState + XK_q))
	{
		(*camera).translations.x += step * (*camera).angleY.cos;
		(*camera).translations.z -= step * (*camera).angleY.sin;
	}
	if (*(keysState + XK_space))
		(*camera).translations.y += step;
	else if (*(keysState + XK_Shift_L))
		(*camera).translations.y -= step;
}
