#pragma once
#include <easyx.h>
#include "snake.h"

extern void PrintSnake(node*head, char*map[30], IMAGE CHARACTER, IMAGE C);
extern void move(node*&head, node*&nexthead, char*dir,int*gameres);
extern void PoisonACT(int*poisonmap[2], int*poisonaction, int*poisonmaxcount, IMAGE POI);
extern void RemovePoison(char*map[30], int*poisonmap[2], int*poisonmaxcount);
extern void PrintMap(char*map[30], IMAGE WAL, IMAGE BOOM, IMAGE TELE, IMAGE ENE,IMAGE SIG,IMAGE FOOD1);
extern void Skill_VAN(char*skill1, int*skillcool1, char*map[30], node*&nexthead, int*score, IMAGE UNSKILL1, int*poisonmap[2], int*poisonmaxcount, int*foodcount);
extern void Skill_LYQ(int*foodcount,int *poisonmap[2], int*poisonmaxcount, char*map[30], node*&nexthead, node*&head, node*&tail, char*dir, int*len, int*score, char*skill2, int*skillcool2, IMAGE UNSKILL2);
extern void Skill_CAT(int*poisonmap[2], int*poisonmaxcount, char*skill1, int*skillcool1, char*map[30], node*&nexthead, IMAGE SKILLUSING1, IMAGE UNSKILL1, node*&head);
extern void Win(int*button, int*score);
extern void Fail(int*button, int*score);
extern void Record(int*button, char*charac, int*score);
extern void SaveGame(char*charac, int*button, char*map[30], char*dir, node*&head, int*len, int*poisonmaxcount, int poitime, int*goal, int*score, int*skillcool1, int*skillcool2, char*skill1, char*skill2);
extern void Pause(int*gameres, int*button, IMAGE SAV, IMAGE CONTI, IMAGE MENU, IMAGE UNSAV, IMAGE UNCONTI, IMAGE UNMENU);
extern void FindPoison(char*map[30], int*poisonmap[2], int*poisonmaxcount);
extern void FindTeleport(char*map[30], int*telemap[2]);


