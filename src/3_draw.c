#include "test.h"

void putPixel(int x, int y, float z, t_screenSpace *screenSpace)
{	
	if (x >= -((*screenSpace).xOffset) && x <= ((*screenSpace).xOffset) && y >= -((*screenSpace).yOffset) && y <= ((*screenSpace).yOffset) && z > 0)
		*((*screenSpace).colorBuffer + (y + (*screenSpace).yOffset) * WIDTH + x + (*screenSpace).xOffset) = DEFAULT_VECTOR_COLOR;
}


void project(t_camera *camera, t_screenSpace *screenSpace)
{
	int i;
	float x;
	float y;
	float z;

	i = 0;
	while (i < (*camera).modelSize)
	{
		if (!((*((*camera).model + i)).isEmpty)) 
		{
			z = ((*((*camera).model + i)).z + ((*camera).translations).z);
			x = (((*((*camera).model + i)).x + ((*camera).translations).x) / z) * (*camera).zoom;
			y = (((*((*camera).model + i)).y + ((*camera).translations).y) / z) * (*camera).zoom;
			putPixel(x, y, z, screenSpace);
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
