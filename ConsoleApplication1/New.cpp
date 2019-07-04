#include "snake.h"
#include <malloc.h>


void InitialPoisonMap(int*poisonmap[2]) {
	for (int i = 0;i <= 29;i++) {
		poisonmap[0][i] = NONE;
		poisonmap[1][i] = NONE;
	}
}

void InitialMap(char*map[30]) {//��ʼ����ͼ
	for (int i = 0;i <= 29;i++) {
		for (int j = 0;j <= 29;j++) {
			map[i][j] = AIR;//��ʼ��
		}
	}
}


void NewCrossMap(node*&p) {//�ж��������Ƿ��뿪�߽�
	if (p->x == 30)//�ұ��뿪
		p->x = 0;
	if (p->x == -1)//����뿪
		p->x = 29;
	if (p->y == 30)//�±��뿪
		p->y = 0;
	if (p->y == -1)//�ϱ��뿪
		p->y = 29;
}

void CreatSnake(node*&head, node*&tail, int s_len, int sx, int sy, char dir) {//�����ߵĺ��� 
	

	tail = head;
	node*p;
	for (int i = 1;i < s_len;i++) {//����s_len����
		p = (node*)malloc(sizeof(node));
		if (dir == DOWN) {
			p->x = tail->x;
			p->y = tail->y - 1;
		}
		if (dir == UP) {
			p->x = tail->x;
			p->y = tail->y + 1;
		}
		if (dir == RIGHT) {
			p->x = tail->x - 1;
			p->y = tail->y;
		}
		if (dir == LEFT) {
			p->x = tail->x + 1;
			p->y = tail->y;
		}
		NewCrossMap(p);
		tail->next = p;
		p->previous = tail;
		tail = p;
		p = NULL;
	}
	tail->next = NULL;
}

