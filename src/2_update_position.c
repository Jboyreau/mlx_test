#include "test.h"

void updateModelRotations(t_camera* camera, char* keysState)
{
	if (*(keysState + XK_Right))
	{
		(*camera).cosSinY.cos = (*camera).saveCosSin.cos;
		(*camera).cosSinY.sin = (*camera).saveCosSin.sin;
	}
	else if (*(keysState + XK_Left))
	{
		(*camera).cosSinY.cos = (*camera).minusSaveCosSin.cos;
		(*camera).cosSinY.sin = (*camera).minusSaveCosSin.sin;
	}
	else
	{
		(*camera).cosSinY.cos = 1;
		(*camera).cosSinY.sin = 0;
	}

	if (*(keysState + XK_Up))
	{
		(*camera).cosSinX.cos = (*camera).saveCosSin.cos;
		(*camera).cosSinX.sin = (*camera).saveCosSin.sin;
	}
	else if (*(keysState + XK_Down))
	{
		(*camera).cosSinX.cos = (*camera).minusSaveCosSin.cos;
		(*camera).cosSinX.sin = (*camera).minusSaveCosSin.sin;
	}
	else 	
	{
		(*camera).cosSinX.cos = 1;
		(*camera).cosSinX.sin = 0;
	}
}

void translateScaleModel(t_scene *scene, t_camera *camera, t_screenSpace *screenSpace, char *keysState)
{
	//calculer et sauvegarder la valeur de l'angle definit par la direction de la camera.
	(*camera).angleY.value = (((*scene).mouse_coord.x - (*screenSpace).xOffset) * M_PI) / (*screenSpace).xOffset;
	(*camera).angleY.cos = cos((*camera).angleY.value);
	(*camera).angleY.sin = sin((*camera).angleY.value);
	(*camera).angleX.value = -(((*scene).mouse_coord.y - (*screenSpace).yOffset) * 1.5708) / (*screenSpace).yOffset;
	(*camera).angleX.cos = cos((*camera).angleX.value);
	(*camera).angleX.sin = sin((*camera).angleX.value);
	if (*(keysState + XK_KP_Add))
		(*camera).zoom += ZOOM_STEP;
	else if (*(keysState + XK_KP_Subtract))
		(*camera).zoom -= ZOOM_STEP;
	if (*(keysState + XK_w))
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
	else if (*(keysState + XK_a))
	{
		(*camera).translations.x += (*camera).step * (*camera).angleY.cos;
		(*camera).translations.z -= (*camera).step * (*camera).angleY.sin;
	}
	if (*(keysState + XK_space))
		(*camera).translations.y += (*camera).step;
	else if (*(keysState + XK_Shift_L))
		(*camera).translations.y -= (*camera).step;
}
