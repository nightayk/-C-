#include "snake.h"
#include <Windows.h>

void Teleport(node*&nexthead, char*map[30], int*telemap[2], char*dir) {
	if (map[nexthead->y][nexthead->x] == TELEPORT) {
		int telex, teley;//��ȡ���ﴫ����λ��
		if (nexthead->x == telemap[0][0] && nexthead->y == telemap[1][0]) {
			telex = telemap[0][1];
			teley = telemap[1][1];
		}
		else {
			telex = telemap[0][0];
			teley = telemap[1][0];
		}
		/*��ʼ����*/
		if (*dir == UP) {
			nexthead->x = telex;
			nexthead->y = teley - 1;
		}
		else if (*dir == DOWN) {
			nexthead->x = telex;
			nexthead->y = teley + 1;
		}
		else if (*dir == LEFT) {
			nexthead->x = telex - 1;
			nexthead->y = teley;
		}
		else if (*dir == RIGHT) {
			nexthead->x = telex + 1;
			nexthead->y = teley;
		}
	}
}