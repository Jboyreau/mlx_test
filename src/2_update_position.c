#include "test.h"

//TODO void updateCameraTranslations()
//TODO void updateCameraRotations()
//TODO void updateModelTranslations()
//TODO void updateModelRotations()

void updateCursor(t_vec2 *cursor, char *keysState)
{
	if (*(keysState + XK_Right))
			(*cursor).x += CURSOR_SPEED * (((*cursor).x + CURSOR_SPEED) < SWIDTH);
	else if (*(keysState + XK_Left))
			(*cursor).x -= CURSOR_SPEED * (((*cursor).x - CURSOR_SPEED) > -SWIDTH);
	else if (*(keysState + XK_Up))
			(*cursor).y -= CURSOR_SPEED * (((*cursor).y - CURSOR_SPEED) > -SHEIGHT);
	else if (*(keysState + XK_Down))
			(*cursor).y += CURSOR_SPEED * (((*cursor).y + CURSOR_SPEED) < SHEIGHT);
}
