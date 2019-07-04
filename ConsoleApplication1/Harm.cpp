#include <malloc.h>
#include <easyx.h>
#include "snake.h"


void TouchPoison(char*charac,node*&head, node*&tail, char*map[30], int*poisonmap[2], int*len, int*poisonmaxcount, int*gameres,int*score) {
	if (map[head->y][head->x] == POISON) {//吃到毒药
		*score = *score - 100;
		mciSendString(TEXT("close Sound"), NULL, 0, NULL);
		Sleep(1);
		if (*charac == VAN) {
			mciSendString(TEXT(" open .\\SoundEffect\\VANharm.wav alias Sound"), NULL, 0, NULL);
		}
		else if (*charac == LYQ) {
			mciSendString(TEXT(" open .\\SoundEffect\\LYQharm.wav alias Sound"), NULL, 0, NULL);
		}
		else if (*charac == CAT) {
			mciSendString(TEXT(" open .\\SoundEffect\\CATharm.mp3 alias Sound"), NULL, 0, NULL);
		}
		mciSendString(TEXT("play Sound "), NULL, 0, NULL);
		if (*len == 1) {//只有一节，失败
			*gameres = FAIL;
		}
		else {
			for (int temp = 0;temp < (*poisonmaxcount);temp++) {
				if (poisonmap[0][temp] == head->x && poisonmap[1][temp] == head->y) {
					poisonmap[0][temp] = NONE;
					poisonmap[1][temp] = NONE;
					break;
				}
			}
			map[head->x][head->y] = SNAKE;
			map[tail->y][tail->x] = AIR;
			fillrectangle(199 + (tail->x) * 20, 19 + (tail->y) * 20, 219 + (tail->x) * 20, 39 + (tail->y) * 20);
			tail = tail->previous;
			free(tail->next);
			tail->next = NULL;
			*len = *len - 1;
			FlushBatchDraw();
		}
	}
}


void TouchBomb(char*charac,node*&head, node*&tail, char*map[30], int*len, int*gameres,int*score) {//触碰炸弹
	if (map[head->y][head->x] == BOMB) {
		*score = (*score) / 2;
		mciSendString(TEXT("close Sound"), NULL, 0, NULL);
		Sleep(1);
		if (*charac == VAN) {
			mciSendString(TEXT(" open .\\SoundEffect\\VANharm.wav alias Sound"), NULL, 0, NULL);
		}
		else if (*charac == LYQ) {
			mciSendString(TEXT(" open .\\SoundEffect\\LYQharm.wav alias Sound"), NULL, 0, NULL);
		}
		else if (*charac == CAT) {
			mciSendString(TEXT(" open .\\SoundEffect\\CATharm.mp3 alias Sound"), NULL, 0, NULL);
		}
		mciSendString(TEXT("play Sound "), NULL, 0, NULL);
		if (*len == 1) {//只有一节被炸死
			*gameres = FAIL;
		}
		else {//炸去一半
			map[head->x][head->y] = SNAKE;
			int boom = (*len) / 2;
			for (int boomcount = 0;boomcount < boom;boomcount++) {//炸蛇
				map[tail->y][tail->x] = AIR;
				fillrectangle(199 + (tail->x) * 20, 19 + (tail->y) * 20, 219 + (tail->x) * 20, 39 + (tail->y) * 20);
				tail = tail->previous;
				free(tail->next);
				tail->next = NULL;
			}
			FlushBatchDraw();
			*len=((*len)/2)+((*len)%2);
		}
	}
}

void HitWall(node*&head, char*map[30], int*gameres,int*score) {//撞墙
	if (map[head->y][head->x] == WALL|| map[head->y][head->x] == SIGHT) {//撞到了
		*score = (*score) / 4;
		*gameres = FAIL;//游戏失败
	}
}