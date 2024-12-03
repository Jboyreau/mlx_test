#include "test.h"

void putPixel(int x, int y, t_screenSpace *screenSpace)
{
	*((*screenSpace).colorBuffer + (y + (*screenSpace).yOffset) * WIDTH + x + (*screenSpace).xOffset) = DEFAULT_VECTOR_COLOR;
}

void rotateModel(t_biVec3 *biVector, t_vec3 *angles)
{
	float x;
	float y;
	float z;

	z = (*biVector).a.z * cos((*angles).x) - (*biVector).a.y * sin((*angles).x);
	y = (*biVector).a.y * cos((*angles).x) + (*biVector).a.z * sin((*angles).x);
	(*biVector).a.z = z;
	(*biVector).a.y = y;
	x = (*biVector).a.x * cos((*angles).y) - (*biVector).a.z * sin((*angles).y);
	z = (*biVector).a.z * cos((*angles).y) + (*biVector).a.x * sin((*angles).y);
	(*biVector).a.x = x;
	(*biVector).a.z = z;
	
	z = (*biVector).b.z * cos((*angles).x) - (*biVector).b.y * sin((*angles).x);
	y = (*biVector).b.y * cos((*angles).x) + (*biVector).b.z * sin((*angles).x);
	(*biVector).b.z = z;
	(*biVector).b.y = y;
	x = (*biVector).b.x * cos((*angles).y) - (*biVector).b.z * sin((*angles).y);
	z = (*biVector).b.z * cos((*angles).y) + (*biVector).b.x * sin((*angles).y);
	(*biVector).b.x = x;
	(*biVector).b.z = z;
}

void addTranslations(t_biVec3 *biVector, t_vec3 *translations)
{
	(*biVector).a.x += (*translations).x;
	(*biVector).a.y += (*translations).y;
	(*biVector).a.z += (*translations).z;	
	(*biVector).b.x += (*translations).x;
	(*biVector).b.y += (*translations).y;
	(*biVector).b.z += (*translations).z;
}

// Fonction pour tracer une ligne avec l'algorithme DDA
void drawLineDDA(t_biVec3 *biVec, t_screenSpace *screenSpace, float steps)
{
    // Calculer les différences entre les points
	float xInc;
	float yInc;
    float dx = (*biVec).b.x - (*biVec).a.x;
    float dy = (*biVec).b.y - (*biVec).a.y;

    // Trouver le plus grand des deux pour déterminer le nombre d'étapes
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);

    // Calculer les incréments pour chaque étape
    xInc = dx / steps;
    yInc = dy / steps;

    // Tracer la ligne point par point
    for (int i = 0; i <= steps; ++i) {
		putPixel((int)round((*biVec).a.x), (int)round((*biVec).a.y), screenSpace);
        (*biVec).a.x += xInc; // Incrémenter x
        (*biVec).a.y += yInc; // Incrémenter y
    }
}


void rotateCamera(t_biVec3 *biVector, t_camera *camera)
{
	float x;
	float y;
	float z;
	float angle;

	angle = (*camera).angleY.value;
	x = (*biVector).a.x * cos(angle) - (*biVector).a.z * sin(angle);
	z = (*biVector).a.z * cos(angle) + (*biVector).a.x * sin(angle);
	(*biVector).a.x = x;
	(*biVector).a.z = z;
	x = (*biVector).b.x * cos(angle) - (*biVector).b.z * sin(angle);
	z = (*biVector).b.z * cos(angle) + (*biVector).b.x * sin(angle);
	(*biVector).b.x = x;
	(*biVector).b.z = z;
	angle = (*camera).angleX.value;
	z = (*biVector).a.z * cos(angle) - (*biVector).a.y * sin(angle);
	y = (*biVector).a.y * cos(angle) + (*biVector).a.z * sin(angle);
	(*biVector).a.z = z;
	(*biVector).a.y = y;
	z = (*biVector).b.z * cos(angle) - (*biVector).b.y * sin(angle);
	y = (*biVector).b.y * cos(angle) + (*biVector).b.z * sin(angle);
	(*biVector).b.z = z;
	(*biVector).b.y = y;
}

void rotateIso(t_biVec3 *biVector)
{
	float x;
	float y;
	float z;

	z = (*biVector).a.z * cos(0.61548) - (*biVector).a.y * sin(0.61548);
	y = (*biVector).a.y * cos(0.61548) + (*biVector).a.z * sin(0.61548);
	(*biVector).a.z = z;
	(*biVector).a.y = y;
	x = (*biVector).a.x * cos(0.7854) - (*biVector).a.z * sin(0.7854);
	z = (*biVector).a.z * cos(0.7854) + (*biVector).a.x * sin(0.7854);
	(*biVector).a.x = x;
	(*biVector).a.z = z;
	
	z = (*biVector).b.z * cos(0.61548) - (*biVector).b.y * sin(0.61548);
	y = (*biVector).b.y * cos(0.61548) + (*biVector).b.z * sin(0.61548);
	(*biVector).b.z = z;
	(*biVector).b.y = y;
	x = (*biVector).b.x * cos(0.7854) - (*biVector).b.z * sin(0.7854);
	z = (*biVector).b.z * cos(0.7854) + (*biVector).b.x * sin(0.7854);
	(*biVector).b.x = x;
	(*biVector).b.z = z;
}

void projectIso(t_camera *camera, t_screenSpace *screenSpace, t_scene (*scene), int i)
{
	float		zoom;
	t_biVec3	biVector;

	//calculer et sauvegarder la valeur de l'angle definit par la direction de la camera.
	(*camera).angleY.value = (((*scene).mouse_coord.x - (*screenSpace).xOffset) * M_PI) / (*screenSpace).xOffset;
	(*camera).angleX.value = -(((*scene).mouse_coord.y - (*screenSpace).yOffset) * M_PI) / (*screenSpace).yOffset;
	(*camera).angleY.cos = cos((*camera).angleY.value);
	(*camera).angleY.sin = sin((*camera).angleY.value);
	i = 0;
	while (i < (*camera).biVecSize)
	{
		if (!((*((*camera).modelT + i)).a.isEmpty) && !((*((*camera).modelT + i)).b.isEmpty)) 
		{
			rotateModel((*camera).modelT + i, &((*camera).modelRotations));
			biVector = *((*camera).modelT + i);
			rotateIso(&biVector);
			addTranslations(&biVector, &((*camera).translations));
			rotateCamera(&biVector, camera);
			zoom = (*camera).zoom / 15;
			biVector.a.x = (biVector).a.x * zoom;
			biVector.a.y = (biVector).a.y * zoom;
			biVector.b.x = (biVector).b.x * zoom;
			biVector.b.y = (biVector).b.y * zoom;
			if ((biVector.a.x >= -((*screenSpace).xOffset) && biVector.a.x <= ((*screenSpace).xOffset))
					&& (biVector.a.y >= -((*screenSpace).yOffset) && biVector.a.y <= ((*screenSpace).yOffset))
					&& (biVector.b.x >= -((*screenSpace).xOffset) && biVector.b.x <= ((*screenSpace).xOffset))
					&& (biVector.b.y >= -((*screenSpace).yOffset) && biVector.b.y <= ((*screenSpace).yOffset)))
				drawLineDDA(&biVector, screenSpace, 0);
		}
		++i;
	}
}

void project(t_camera *camera, t_screenSpace *screenSpace, t_scene (*scene), int i)
{
	float		z;
	t_biVec3	biVector;

	//calculer et sauvegarder la valeur de l'angle definit par la direction de la camera.
	(*camera).angleY.value = (((*scene).mouse_coord.x - (*screenSpace).xOffset) * M_PI) / (*screenSpace).xOffset;
	(*camera).angleX.value = -(((*scene).mouse_coord.y - (*screenSpace).yOffset) * 1.5708) / (*screenSpace).yOffset;
	(*camera).angleY.cos = cos((*camera).angleY.value);
	(*camera).angleY.sin = sin((*camera).angleY.value);
	i = 0;
	while (i < (*camera).biVecSize)
	{
		if (!((*((*camera).modelT + i)).a.isEmpty) && !((*((*camera).modelT + i)).b.isEmpty)) 
		{
			rotateModel((*camera).modelT + i, &((*camera).modelRotations));
			biVector = *((*camera).modelT + i);
			addTranslations(&biVector, &((*camera).translations));
			rotateCamera(&biVector, camera);
			if (((biVector).a.z) > ZMIN && ((biVector).b.z) > ZMIN)
			{
				z = (*camera).zoom / (biVector).a.z;
				biVector.a.x = (biVector).a.x * z;
				biVector.a.y = (biVector).a.y * z;
				z = (*camera).zoom / (biVector).b.z;
				biVector.b.x = (biVector).b.x * z;
				biVector.b.y = (biVector).b.y * z;
				if ((biVector.a.x >= -((*screenSpace).xOffset) && biVector.a.x <= ((*screenSpace).xOffset))
						&& (biVector.a.y >= -((*screenSpace).yOffset) && biVector.a.y <= ((*screenSpace).yOffset))
						&& (biVector.b.x >= -((*screenSpace).xOffset) && biVector.b.x <= ((*screenSpace).xOffset))
						&& (biVector.b.y >= -((*screenSpace).yOffset) && biVector.b.y <= ((*screenSpace).yOffset)))
					drawLineDDA(&biVector, screenSpace, 0);
			}
		}
		++i;
	}
}

void clear(t_scene *scene)
{
	//Clear Background.
	for (int i = 0; i < COLOR_BUFFER_SIZE; ++i)
		*((*(*scene).screenSpace).colorBuffer + i) = BACKGROUND_COLOR;
}

void drawSquare(t_scene *scene , int size, t_vec2 cursor)
{
	t_screenSpace *screenSpace = (*scene).screenSpace;
	int x;

	size = (size >> 1) + ((size <= 1) >> 1);

	for (int y = (*screenSpace).yOffset - size + cursor.y; y < (*screenSpace).yOffset + size + cursor.y; ++y)
	{
		if ((y < HEIGHT) && (y > -1))
		{
			x = (*screenSpace).xOffset - size + cursor.x;
			for (; x < (*screenSpace).xOffset + size + cursor.x; ++x)
				if ((x < WIDTH) && (x > -1))
					*((*(*scene).screenSpace).colorBuffer + y * WIDTH + x) = 0x0000ff00;
		}
	}
}
