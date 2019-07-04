#include "snake.h"
#include <easyx.h>


//(199+x*20,19+y*20)	,(219+x*20,39+y*20)左上点与右下点
void PrintSnake(node*head, char*map[30], IMAGE CHARACTER, IMAGE C) {//打印初始化的蛇
	putimage(199 + (head->x) * 20, 19 + (head->y) * 20, &CHARACTER);//打印蛇头
	map[head->y][head->x] = SNAKE;
	node*pr;
	pr = head->next;
	while (pr != NULL) {//打印蛇身
		map[pr->y][pr->x] = SNAKE;
		putimage(199 + (pr->x) * 20, 19 + (pr->y) * 20, &C);
		pr = pr->next;
	}
}

void PrintMap(char*map[30], IMAGE WAL, IMAGE BOOM, IMAGE TELE, IMAGE ENE,IMAGE SIG,IMAGE FOOD1) {//打印地图
	for (int i = 0;i < 30;i++) {
		for (int j = 0;j < 30;j++) {
			if (map[i][j] == WALL) {
				putimage(199 + j * 20, 19 + i * 20, &WAL);
			}
			else if (map[i][j] == BOMB) {
				putimage(199 + j * 20, 19 + i * 20, &BOOM);
			}
			else if (map[i][j] == TELEPORT) {
				putimage(199 + j * 20, 19 + i * 20, &TELE);
			}
			else if (map[i][j] == ENEMY) {
				putimage(199 + j * 20, 19 + i * 20, &ENE);
			}
			else if (map[i][j] == SIGHT) {
				putimage(199 + j * 20, 19 + i * 20, &SIG);
			}
			else if (map[i][j] == FOOD) {
				putimage(199 + j * 20, 19 + i * 20, &FOOD1);
			}
		}
	}
}
