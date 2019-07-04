#pragma once
#include "snake.h"
#include <easyx.h>

extern void CreatSnake(node*&head, node*&tail, int s_len, int sx, int sy, char dir);
extern void NewCrossMap(node*&p);//如果新生的蛇离开边界,进行操作
extern void CreatFood(int*seed, char*map[30], int*foodcount, IMAGE FOOD1);
extern void CreatPoison(int*seed, char*map[30], int*poisonmap[2], int*poisoncount, IMAGE POI);
extern void CreatBomb(int*seed, char*map[30], int*bombcount, IMAGE BOOM);
extern void CreatTeleport(int*seed, char*map[30], int*telemap[2], IMAGE TELE);