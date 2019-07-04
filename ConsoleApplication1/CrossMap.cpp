#include "snake.h"

void CrossMap(node*&nexthead) {//ÅÐ¶ÏÊÇ·ñÀë¿ª±ß½ç
	if (nexthead->x == 30)//ÓÒ±ßÀë¿ª
		nexthead->x = 0;
	if (nexthead->x == -1)//×ó±ßÀë¿ª
		nexthead->x = 29;
	if (nexthead->y == 30)//ÏÂ±ßÀë¿ª
		nexthead->y = 0;
	if (nexthead->y == -1)//ÉÏ±ßÀë¿ª
		nexthead->y = 29;
}
