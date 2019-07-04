#include "snake.h"
#include <easyx.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")

void EatFoodOrItself(node*&nexthead, node*&head, node*&tail, char*map[30], int*len, int*foodcount, IMAGE CHARACTER, IMAGE C, int*gameres,char*charac,int*score) {//判断吃到食物
	if (map[nexthead->y][nexthead->x] == FOOD) {//吃到了
		*score = *score + 50;
		mciSendString(TEXT("close Sound"), NULL, 0, NULL);
		Sleep(1);
		if (*charac == VAN) {
			mciSendString(TEXT(" open .\\SoundEffect\\VANeat.wav alias Sound"), NULL, 0, NULL);
		}
		else if (*charac == LYQ) {
			mciSendString(TEXT(" open .\\SoundEffect\\LYQeat.mp3 alias Sound"), NULL, 0, NULL);
		}
		else if (*charac == CAT) {
			mciSendString(TEXT(" open .\\SoundEffect\\CATeat.mp3 alias Sound"), NULL, 0, NULL);
		}
		mciSendString(TEXT("play Sound "), NULL, 0, NULL);
		nexthead->next = head;
		head->previous = nexthead;
		head = nexthead;
		putimage(199 + (head->x) * 20, 19 + (head->y) * 20, &CHARACTER);
		putimage(199 + (head->next->x) * 20, 19 + (head->next->y) * 20, &C);
		map[head->y][head->x] = SNAKE;
		*len = *len + 1;
		*foodcount = *foodcount - 1;
		FlushBatchDraw();
	}
	else {//没吃到
		if (map[nexthead->y][nexthead->x] == SNAKE) {//吃到自己了
			*score = (*score) / 4;
			*gameres = FAIL;
		}
		else {
			nexthead->next = head;
			head->previous = nexthead;
			head = nexthead;
			putimage(199 + (head->x) * 20, 19 + (head->y) * 20, &CHARACTER);
			putimage(199 + (head->next->x) * 20, 19 + (head->next->y) * 20, &C);
			map[tail->y][tail->x] = AIR;
			fillrectangle(199 + (tail->x) * 20, 19 + (tail->y) * 20, 219 + (tail->x) * 20, 39 + (tail->y) * 20);
			tail = tail->previous;//消除蛇尾
			free(tail->next);
			tail->next = NULL;
			FlushBatchDraw();
		}
	}
}