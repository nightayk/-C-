#include "snake.h"
#include <easyx.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")



void HitSelf(int shotx,int shoty,node*&head, node*&tail, char*map[30], int*len) {
	node*p;//开始遍历
	p = head;
	int num = 0;
	while (p->x != shotx || p->y != shoty) {
		num++;
		p = p->next;
	}
	while (tail->x != p->x||tail->y!=p->y) {
		map[tail->y][tail->x] = AIR;
		fillrectangle(199 + (tail->x) * 20, 19 + (tail->y) * 20, 219 + (tail->x) * 20, 39 + (tail->y) * 20);
		tail = tail->previous;
		free(tail->next);
		tail->next = NULL;
	}
	p = NULL;
	map[tail->y][tail->x] = AIR;
	fillrectangle(199 + (tail->x) * 20, 19 + (tail->y) * 20, 219 + (tail->x) * 20, 39 + (tail->y) * 20);
	tail = tail->previous;
	free(tail->next);
	tail->next = NULL;
	*len = num;
}

void Kill(int x,int y, char*map[30]) {
	setlinecolor(WHITE);
	int enex = x;
	int eney = y;
	if (map[eney - 1][enex] == SIGHT) {//敌人视线向上
		for (int i = 1;i <= 5;i++) {
			map[eney - i][enex] = AIR;
			fillrectangle(199 + enex * 20, 19 + (eney - i) * 20, 219 + enex * 20, 39 + (eney - i) * 20);
		}
	}
	else if (map[eney + 1][enex] == SIGHT) {//敌人视线向下
		for (int i = 1;i <= 5;i++) {
			map[eney + i][enex] = AIR;
			fillrectangle(199 + enex * 20, 19 + (eney + i) * 20, 219 + enex * 20, 39 + (eney + i) * 20);
		}
		FlushBatchDraw();
	}
	else if (map[eney][enex - 1] == SIGHT) {//敌人视线向左
		for (int i = 1;i <= 5;i++) {
			map[eney][enex - i] = AIR;
			fillrectangle(199 + (enex - i) * 20, 19 + eney * 20, 219 + (enex - i) * 20, 39 + eney * 20);
		}
		FlushBatchDraw();
	}
	else {//敌人视线向右
		for (int i = 1;i <= 5;i++) {
			map[eney][enex + i] = AIR;
			fillrectangle(199 + (enex + i) * 20, 19 + eney * 20, 219 + (enex + i) * 20, 39 + eney * 20);
		}
		FlushBatchDraw();
	}
}

void Shot(int*foodcount,int*poisonmap[2],int*poisonmaxcount,int shotx, int shoty, node*&head, node*&tail, char*map[30], int*len, int*score) {
	if (map[shoty][shotx] == ENEMY) {
		*score = *score + 200;
		Kill(shotx, shoty, map);
		fillrectangle(199 + shotx * 20, 19 + shoty * 20, 219 + shotx * 20, 39 + shoty * 20);
	}
	else if (map[shoty][shotx] == SNAKE) {//打到自己
		int temp = *len;
		HitSelf(shotx, shoty, head, tail, map, len);
		*score = *score - (temp - (*len) * 100);
	}
	else if (map[shoty][shotx] == POISON) {//打到毒药
		for (int temp = 0;temp < (*poisonmaxcount);temp++) {
			if (poisonmap[0][temp] == shotx&&poisonmap[1][temp]==shoty){
				poisonmap[0][temp] = NONE;
				poisonmap[1][temp] = NONE;
				fillrectangle(199 + shotx * 20, 19 + shoty * 20, 219 + shotx * 20, 39 + shoty * 20);
			}
		}
		map[shoty][shotx] = AIR;
	}
	else if (map[shoty][shotx] == FOOD) {
		map[shoty][shotx] = AIR;
		*foodcount = *foodcount - 1;
		fillrectangle(199 + shotx * 20, 19 + shoty * 20, 219 + shotx * 20, 39 + shoty * 20);
	}
	else if (map[shoty][shotx] != BOMB && map[shoty][shotx] != SIGHT) {
		map[shoty][shotx] = AIR;
		fillrectangle(199 + shotx * 20, 19 + shoty * 20, 219 + shotx * 20, 39 + shoty * 20);
	}
	FlushBatchDraw();
}

void Skill_VAN(char*skill1, int*skillcool1, char*map[30], node*&nexthead, int*score, IMAGE UNSKILL1, int*poisonmap[2], int*poisonmaxcount, int*foodcount) {
	if (*skill1 == AVAILABLE) {
		if (map[nexthead->y][nexthead->x] == POISON) {
			map[nexthead->y][nexthead->x] = FOOD;
			*foodcount = *foodcount + 1;
			for (int temp = 0;temp < (*poisonmaxcount);temp++) {
				if (poisonmap[0][temp] == nexthead->x && poisonmap[1][temp] == nexthead->y) {
					poisonmap[0][temp] = NONE;
					poisonmap[1][temp] = NONE;
					break;
				}
			}
			*skill1 = COOLDOWN;
			*skillcool1 = 80;
			*score = *score + 10;
			putimage(829, 159, &UNSKILL1);
			FlushBatchDraw();
		}
	}
}

void Skill_LYQ(int*foodcount,int *poisonmap[2],int*poisonmaxcount,char*map[30],node*&nexthead,node*&head,node*&tail,char*dir,int*len,int*score,char*skill2,int*skillcool2,IMAGE UNSKILL2) {
	if (map[nexthead->y][nexthead->x] == ENEMY) {
		mciSendString(TEXT("close Sound"), NULL, 0, NULL);
		Sleep(1);
		mciSendString(TEXT(" open .\\SoundEffect\\LYQskill1.mp3 alias Sound"), NULL, 0, NULL);
		mciSendString(TEXT("play Sound "), NULL, 0, NULL);
		map[nexthead->y][nexthead->x] = AIR;
		Kill(nexthead->x, nexthead->y, map);
		FlushBatchDraw();
		*score = *score + 250;
	}
	if (GetAsyncKeyState('F')) {
		if (*skill2 == AVAILABLE) {
			*skill2 = COOLDOWN;
			*skillcool2 = 30;
			int shotx = nexthead->x;
			int shoty = nexthead->y;
			mciSendString(TEXT("close Sound"), NULL, 0, NULL);
			Sleep(1);
			mciSendString(TEXT(" open .\\SoundEffect\\LYQskill2.mp3 alias Sound"), NULL, 0, NULL);
			mciSendString(TEXT("play Sound "), NULL, 0, NULL);
			putimage(829, 249, &UNSKILL2);
			if (*dir == UP) {
				if (nexthead->y != 29) {//防止穿越地图边界让子弹打回来
					while ((map[shoty][shotx] == AIR || map[shoty][shotx] == SIGHT) && shoty > 0) {
						shoty = shoty - 1;
					}
					Shot(foodcount,poisonmap,poisonmaxcount,shotx, shoty, head, tail, map, len, score);
				}
			}
			else if (*dir == DOWN) {
				if (nexthead->y != 0) {
					while ( shoty < 29 && (map[shoty][shotx] == AIR || map[shoty][shotx] == SIGHT)) {
						shoty = shoty + 1;
					}
					if(shoty!=30)Shot(foodcount,poisonmap, poisonmaxcount, shotx, shoty, head, tail, map, len, score);
				}
			}
			else if (*dir == LEFT) {
				if (nexthead->x != 29) {
					while (shotx > 0 && (map[shoty][shotx] == AIR || map[shoty][shotx] == SIGHT)) {
						shotx = shotx - 1;
					}
					Shot(foodcount,poisonmap, poisonmaxcount, shotx, shoty, head, tail, map, len, score);
				}
			}
			else /*if (*dir == RIGHT)*/ {
				if (nexthead->x != 0) {
					while ((map[shoty][shotx] == AIR || map[shoty][shotx] == SIGHT) && shotx < 29) {
						shotx = shotx + 1;
					}
					Shot(foodcount,poisonmap, poisonmaxcount, shotx, shoty, head, tail, map, len, score);
				}
			}
			FlushBatchDraw();
		}
	}
}

void Skill_CAT(int*poisonmap[2],int*poisonmaxcount,char*skill1, int*skillcool1, char*map[30], node*&nexthead, IMAGE SKILLUSING1, IMAGE UNSKILL1, node*&head) {
	if (*skill1 == USING) {
		*skillcool1 = *skillcool1 - 1;
		if (map[nexthead->y][nexthead->x] != AIR && map[nexthead->y][nexthead->x] != FOOD&&map[nexthead->y][nexthead->x]!=SNAKE) {
			if (map[nexthead->y][nexthead->x] == POISON) {
				for (int temp = 0;temp < (*poisonmaxcount);temp++) {
					if (poisonmap[0][temp] == nexthead->x && poisonmap[1][temp] == nexthead->y) {
						poisonmap[0][temp] = NONE;
						poisonmap[1][temp] = NONE;
					}
				}
			}
			map[nexthead->y][nexthead->x] = AIR;
		}
		if (*skillcool1 == 0) {
			*skill1 = COOLDOWN;
			*skillcool1 = 101;
			putimage(829, 159, &UNSKILL1);
		}
	}
	else if (GetAsyncKeyState('F')) {
		if (*skill1 == AVAILABLE) {
			*skill1 = USING;
			*skillcool1 = 20;
			putimage(829, 159, &SKILLUSING1);
		}
	}
	FlushBatchDraw();
}