#include "snake.h"
#include <Windows.h>
#include <easyx.h>
#include <time.h>

void CreatFood(int*seed, char*map[30], int*foodcount, IMAGE FOOD1) {//随机出现食物
	if (*seed % 20 == 0)//循环种子
		*seed = (unsigned)time(NULL);
	*seed = *seed + 1;
	srand(*seed);//为了防止每次产生的随机数相同，种子设置为seed
	int foodx = rand() % 30;
	int foody = rand() % 30;
	if (map[foody][foodx] == AIR) {
		map[foody][foodx] = FOOD;
		putimage(199 + (foodx) * 20, 19 + (foody) * 20, &FOOD1);
		*foodcount = *foodcount + 1;
	}
}

void CreatPoison(int*seed, char*map[30], int*poisonmap[2], int*poisoncount, IMAGE POI) {
	if (*seed % 20 == 0)//循环种子
		*seed = (unsigned)time(NULL);
	*seed = *seed + 1;
	srand(*seed);//为了防止每次产生的随机数相同，种子设置为seed
	int poix = rand() % 30;
	int poiy = rand() % 30;
	if (map[poiy][poix] == AIR){
		poisonmap[0][*poisoncount] = poix;
		poisonmap[1][*poisoncount] = poiy;
		map[poiy][poix] = POISON;
		*poisoncount = *poisoncount + 1;
	}
}

void CreatBomb(int*seed, char*map[30], int*bombcount, IMAGE BOOM) {//各个战役出现的炸弹随难度和关卡数不同
	if (*seed % 20 == 0)//循环种子
		*seed = (unsigned)time(NULL);
	*seed = *seed + 1;
	srand(*seed);//为了防止每次产生的随机数相同，种子设置为seed
	int bomx = rand() % 30;
	int bomy = rand() % 30;
	if (map[bomy][bomx] == AIR) {
		*bombcount = *bombcount + 1;
		map[bomy][bomx] = BOMB;
		putimage(199 + (bomx) * 20, 19 + (bomy) * 20, &BOOM);
	}
}

void CreatTeleport(int*seed, char*map[30], int*telemap[2], IMAGE TELE) {
	if (*seed % 20 == 0)//循环种子
		*seed = (unsigned)time(NULL);
	*seed = *seed + 1;
	srand(*seed);
	int telex;
	int teley;
	while (1) {
		telex = rand() % 30;
		teley = rand() % 30;
		if (map[teley][telex] == AIR) {
			map[teley][telex] = TELEPORT;
			telemap[0][0] = telex;
			telemap[1][0] = teley;
			putimage(199 + (telex) * 20, 19 + (teley) * 20, &TELE);
			break;
		}
	}
	while (1) {
		telex = rand() % 30;
		teley = rand() % 30;
		if (map[teley][telex] == AIR) {
			map[teley][telex] = TELEPORT;
			telemap[0][1] = telex;
			telemap[1][1] = teley;
			putimage(199 + (telex) * 20, 19 + (teley) * 20, &TELE);
			break;
		}
	}
}
