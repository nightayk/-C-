#include "snake.h"
#include <Windows.h>


void keyboard(char*dir,int*gameres) {
	if (GetAsyncKeyState(VK_UP) && *dir != DOWN) {//��
		*dir = UP;
	}
	else if (GetAsyncKeyState(VK_DOWN) && *dir != UP) {//��
		*dir = DOWN;
	}
	else if (GetAsyncKeyState(VK_LEFT) && *dir != RIGHT) {//��
		*dir = LEFT;
	}
	else if (GetAsyncKeyState(VK_RIGHT) && *dir != LEFT) {//��
		*dir = RIGHT;
	}
	else if (GetAsyncKeyState(VK_ESCAPE)) {//�˳���Ϸ
		*gameres = EXIT;
	}
	else if (GetAsyncKeyState(VK_SPACE)) {//��ͣ��Ϸ
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
