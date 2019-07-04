#include "snake.h"
#include <malloc.h>


void InitialPoisonMap(int*poisonmap[2]) {
	for (int i = 0;i <= 29;i++) {
		poisonmap[0][i] = NONE;
		poisonmap[1][i] = NONE;
	}
}

void InitialMap(char*map[30]) {//初始化地图
	for (int i = 0;i <= 29;i++) {
		for (int j = 0;j <= 29;j++) {
			map[i][j] = AIR;//初始化
		}
	}
}


void NewCrossMap(node*&p) {//判断新生成是否离开边界
	if (p->x == 30)//右边离开
		p->x = 0;
	if (p->x == -1)//左边离开
		p->x = 29;
	if (p->y == 30)//下边离开
		p->y = 0;
	if (p->y == -1)//上边离开
		p->y = 29;
}

void CreatSnake(node*&head, node*&tail, int s_len, int sx, int sy, char dir) {//生成蛇的函数 
	

	tail = head;
	node*p;
	for (int i = 1;i < s_len;i++) {//生成s_len节蛇
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

