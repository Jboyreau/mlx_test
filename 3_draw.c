#include "test.h"

void clear(t_scene *scene)
{
	//Clear Background.
	for (int i = 0; i < WIDTH * HIGHT; ++i)
		*((*(*scene).img).addr + i) = BACKGROUND_COLOR;
}

void drawSquare(t_scene *scene , int size, t_vec2 cursor)
{
	t_screenSpace *screenSpace = (*scene).screenSpace;
	int x;

	size = (size >> 1) + ((size <= 1) >> 1);
	
	for (int y = (*screenSpace).yOffset - size + cursor.y; y < (*screenSpace).yOffset + size + cursor.y; ++y)
	{
		x = (*screenSpace).xOffset - size + cursor.x;
		for (; x < (*screenSpace).xOffset + size + cursor.x; ++x)
			*((*(*scene).img).addr + y * WIDTH + x) = 0x0000ff00;
	}
}
