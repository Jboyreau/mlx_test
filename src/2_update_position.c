#include "test.h"

void updateModelRotations(t_camera* camera, char* keysState)
{
	if (*(keysState + XK_Right))
			(*camera).modelRotations.y = ROTATION_MODEL_STEP;
	else if (*(keysState + XK_Left))
			(*camera).modelRotations.y = -ROTATION_MODEL_STEP;
	else 
		(*camera).modelRotations.y = 0;
	if (*(keysState + XK_Up))
			(*camera).modelRotations.x = ROTATION_MODEL_STEP;
	else if (*(keysState + XK_Down))
			(*camera).modelRotations.x = -ROTATION_MODEL_STEP;
	else 
		(*camera).modelRotations.x = 0;
	(*camera).cosSinX.cos = cos((*camera).modelRotations.x);
	(*camera).cosSinX.sin = sin((*camera).modelRotations.x);
	(*camera).cosSinY.cos = cos((*camera).modelRotations.y);
	(*camera).cosSinY.sin = sin((*camera).modelRotations.y);
}

void translateScaleModel(t_scene *scene, t_camera *camera, t_screenSpace *screenSpace, char *keysState)
{
	//calculer et sauvegarder la valeur de l'angle definit par la direction de la camera.
	(*camera).angleY.value = (((*scene).mouse_coord.x - (*screenSpace).xOffset) * M_PI) / (*screenSpace).xOffset;
	(*camera).angleX.value = -(((*scene).mouse_coord.y - (*screenSpace).yOffset) * 1.5708) / (*screenSpace).yOffset;
	(*camera).angleY.cos = cos((*camera).angleY.value);
	(*camera).angleY.sin = sin((*camera).angleY.value);
	if (*(keysState + XK_KP_Add))
		(*camera).zoom += ZOOM_STEP;
	else if (*(keysState + XK_KP_Subtract))
		(*camera).zoom -= ZOOM_STEP;
	if (*(keysState + XK_z))
	{
		(*camera).translations.z -= (*camera).step * (*camera).angleY.cos;
		(*camera).translations.x -= (*camera).step * (*camera).angleY.sin;
	}
	else if (*(keysState + XK_s))
	{
		(*camera).translations.z += (*camera).step * (*camera).angleY.cos;
		(*camera).translations.x += (*camera).step * (*camera).angleY.sin;
	}
	if (*(keysState + XK_d))
	{
		(*camera).translations.x -= (*camera).step * (*camera).angleY.cos;
		(*camera).translations.z += (*camera).step * (*camera).angleY.sin;
	}
	else if (*(keysState + XK_q))
	{
		(*camera).translations.x += (*camera).step * (*camera).angleY.cos;
		(*camera).translations.z -= (*camera).step * (*camera).angleY.sin;
	}
	if (*(keysState + XK_space))
		(*camera).translations.y += (*camera).step;
	else if (*(keysState + XK_Shift_L))
		(*camera).translations.y -= (*camera).step;
}
