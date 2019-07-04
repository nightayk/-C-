#include "snake.h"
#include <Windows.h>


void keyboard(char*dir,int*gameres) {
	if (GetAsyncKeyState(VK_UP) && *dir != DOWN) {//上
		*dir = UP;
	}
	else if (GetAsyncKeyState(VK_DOWN) && *dir != UP) {//下
		*dir = DOWN;
	}
	else if (GetAsyncKeyState(VK_LEFT) && *dir != RIGHT) {//左
		*dir = LEFT;
	}
	else if (GetAsyncKeyState(VK_RIGHT) && *dir != LEFT) {//右
		*dir = RIGHT;
	}
	else if (GetAsyncKeyState(VK_ESCAPE)) {//退出游戏
		*gameres = EXIT;
	}
	else if (GetAsyncKeyState(VK_SPACE)) {//暂停游戏
		*gameres = PAUSE;
	}
}


void move(node*&head, node*&nexthead, char*dir,int*gameres) {
	if (*dir == UP) {
		nexthead->x = head->x;
		nexthead->y = head->y - 1;
	}
	else if (*dir == DOWN) {
		nexthead->x = head->x;
		nexthead->y = head->y + 1;
	}
	else if (*dir == LEFT) {
		nexthead->x = head->x - 1;
		nexthead->y = head->y;
	}
	else if (*dir == RIGHT) {
		nexthead->x = head->x + 1;
		nexthead->y = head->y;
	}
	keyboard(dir,gameres);
}
