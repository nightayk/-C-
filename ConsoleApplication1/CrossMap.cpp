#include "snake.h"

void CrossMap(node*&nexthead) {//�ж��Ƿ��뿪�߽�
	if (nexthead->x == 30)//�ұ��뿪
		nexthead->x = 0;
	if (nexthead->x == -1)//����뿪
		nexthead->x = 29;
	if (nexthead->y == 30)//�±��뿪
		nexthead->y = 0;
	if (nexthead->y == -1)//�ϱ��뿪
		nexthead->y = 29;
}
