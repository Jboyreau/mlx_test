#include "test.h"


void updateCursor(t_vec2 *cursor, char *keysState)
{
	if (*(keysState + XK_Right))
			++((*cursor).x);
	else if (*(keysState + XK_Left))
			--((*cursor).x);
	else if (*(keysState + XK_Up))
			--((*cursor).y);
	else if (*(keysState + XK_Down))
			++((*cursor).y);
}
