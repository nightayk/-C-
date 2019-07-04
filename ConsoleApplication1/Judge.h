#pragma once
#include "snake.h"
#include <easyx.h>
extern void EatFoodOrItself(node*&nexthead, node*&head, node*&tail, char*map[30], int*len, int*foodcount, IMAGE CHARACTER, IMAGE C, int*gameres,char*charac,int*score);
extern void CrossMap(node*&nexthead);
extern void TouchPoison(char*charac,node*&head, node*&tail, char*map[30], int*poisonmap[2], int*len, int*poisonmaxcount, int*gameres,int*score);
extern void TouchBomb(char*charac,node*&head, node*&tail, char*map[30], int*len, int*gameres,int*score);
extern void HitWall(node*&head, char*map[30], int*gameres,int*score);
extern void Teleport(node*&nexthead, char*map[30], int*telemap[2], char*dir);
extern void SkillCool(char*skill1, char*skill2, int*skillcool1, int*skillcool2, IMAGE SKILL1, IMAGE SKILL2);
