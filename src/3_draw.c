#include "test.h"

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
