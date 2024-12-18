#include "test.h"

void putPixel(int x, int y, t_screenSpace *screenSpace)
{
	*((*screenSpace).colorBuffer + (y + (*screenSpace).yOffset) * WIDTH + x + (*screenSpace).xOffset) = DEFAULT_VECTOR_COLOR;
}

void rotateModel(t_biVec3 *biVector, t_cosSin *csX, t_cosSin *csY)
{
	float x;
	float y;
	float z;

	z = (*biVector).a.z * (*csX).cos - (*biVector).a.y * (*csX).sin;
	y = (*biVector).a.y * (*csX).cos + (*biVector).a.z * (*csX).sin;
	(*biVector).a.z = z;
	(*biVector).a.y = y;
	x = (*biVector).a.x * (*csY).cos - (*biVector).a.z * (*csY).sin;
	z = (*biVector).a.z * (*csY).cos + (*biVector).a.x * (*csY).sin;
	(*biVector).a.x = x;
	(*biVector).a.z = z;
	
	z = (*biVector).b.z * (*csX).cos - (*biVector).b.y * (*csX).sin;
	y = (*biVector).b.y * (*csX).cos + (*biVector).b.z * (*csX).sin;
	(*biVector).b.z = z;
	(*biVector).b.y = y;
	x = (*biVector).b.x * (*csY).cos - (*biVector).b.z * (*csY).sin;
	z = (*biVector).b.z * (*csY).cos + (*biVector).b.x * (*csY).sin;
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

	x = (*biVector).a.x * (*camera).angleY.cos - (*biVector).a.z * (*camera).angleY.sin;
	z = (*biVector).a.z * (*camera).angleY.cos + (*biVector).a.x * (*camera).angleY.sin;
	(*biVector).a.x = x;
	(*biVector).a.z = z;
	x = (*biVector).b.x * (*camera).angleY.cos - (*biVector).b.z * (*camera).angleY.sin;
	z = (*biVector).b.z * (*camera).angleY.cos + (*biVector).b.x * (*camera).angleY.sin;
	(*biVector).b.x = x;
	(*biVector).b.z = z;

	z = (*biVector).a.z * (*camera).angleX.cos - (*biVector).a.y * (*camera).angleX.sin;
	y = (*biVector).a.y * (*camera).angleX.cos + (*biVector).a.z * (*camera).angleX.sin;
	(*biVector).a.z = z;
	(*biVector).a.y = y;
	z = (*biVector).b.z * (*camera).angleX.cos - (*biVector).b.y * (*camera).angleX.sin;
	y = (*biVector).b.y * (*camera).angleX.cos + (*biVector).b.z * (*camera).angleX.sin;
	(*biVector).b.z = z;
	(*biVector).b.y = y;
}

void rotateIso(t_biVec3 *biVector)
{
	float x;
	float y;
	float z;

	x = (*biVector).a.x * cos(-0.7854) - (*biVector).a.z * sin(-0.7854);
	z = (*biVector).a.z * cos(-0.7854) + (*biVector).a.x * sin(-0.7854);
	(*biVector).a.x = x;
	(*biVector).a.z = z;
	z = (*biVector).a.z * cos(-0.61548) - (*biVector).a.y * sin(-0.61548);
	y = (*biVector).a.y * cos(-0.61548) + (*biVector).a.z * sin(-0.61548);
	(*biVector).a.z = z;
	(*biVector).a.y = y;
	
	x = (*biVector).b.x * cos(-0.7854) - (*biVector).b.z * sin(-0.7854);
	z = (*biVector).b.z * cos(-0.7854) + (*biVector).b.x * sin(-0.7854);
	(*biVector).b.x = x;
	(*biVector).b.z = z;
	z = (*biVector).b.z * cos(-0.61548) - (*biVector).b.y * sin(-0.61548);
	y = (*biVector).b.y * cos(-0.61548) + (*biVector).b.z * sin(-0.61548);
	(*biVector).b.z = z;
	(*biVector).b.y = y;
}

void projectIso(t_camera *camera, t_screenSpace *screenSpace, int i)
{
	float		zoom;
	t_biVec3	biVector;

	i = 0;
	while (i < (*camera).biVecSize)
	{
		if (!((*((*camera).modelT + i)).a.isEmpty) && !((*((*camera).modelT + i)).b.isEmpty)) 
		{
			rotateModel((*camera).modelT + i, &((*camera).cosSinX), &((*camera).cosSinY));
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

void project(t_camera *camera, t_screenSpace *screenSpace, int i)
{
	float		z;
	t_biVec3	biVector;
	i = 0;
	while (i < (*camera).biVecSize)
	{
		if (!((*((*camera).modelT + i)).a.isEmpty) && !((*((*camera).modelT + i)).b.isEmpty)) 
		{
			rotateModel((*camera).modelT + i, &((*camera).cosSinX), &((*camera).cosSinY));
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
