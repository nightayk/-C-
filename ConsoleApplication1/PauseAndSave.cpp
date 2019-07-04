#include "snake.h"
#include <Windows.h>
#include <stdio.h>
#include <easyx.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")


void SaveGame(char*charac,int*button, char*map[30], char*dir, node*&head, int*len, int*poisonmaxcount, int poitime, int*goal, int*score, int*skillcool1,int*skillcool2,char*skill1,char*skill2) {
	FILE*S;
	if (*charac == VAN)fopen_s(&S, ".\\Save\\VAN.txt", "wb+");
	else if (*charac == LYQ)fopen_s(&S, ".\\Save\\LYQ.txt", "wb+");
	else /*if (*charac == CAT)*/fopen_s(&S, ".\\Save\\CAT.txt", "wb+");
	char buffer[900];
	int n = 0;
	for (int i = 0;i < 30;i++) {
		for (int j = 0;j < 30;j++) {
			buffer[n] = map[i][j];
			n++;
		}
	}
	fwrite(buffer, sizeof(char), 900, S);//存储地图
	fwrite(dir, sizeof(char), 1, S);//存储方向
	fwrite(button, sizeof(int), 1, S);
	int savehead[2];
	savehead[0] = head->y;
	savehead[1] = head->x;
	fwrite(savehead, sizeof(int), 2, S);//存储头方位
	fwrite(len, sizeof(int), 1, S);//存储长度
	fwrite(poisonmaxcount, sizeof(int), 1, S);//存储毒草最大数量
	int*snakebodyx;
	snakebodyx = (int*)malloc(sizeof(int)*(*len));
	int*snakebodyy;
	snakebodyy = (int*)malloc(sizeof(int)*(*len));
	node*p;
	p = head;
	for (int i = 0;i<(*len);i++) {
		snakebodyx[i] = p->x;
		snakebodyy[i] = p->y;
		p = p->next;
	}
	fwrite(snakebodyx, sizeof(int), *len, S);
	fwrite(snakebodyy, sizeof(int), *len, S);
	fwrite(&poitime, sizeof(int), 1, S);
	fwrite(goal, sizeof(int), 1, S);
	fwrite(score, sizeof(int), 1, S);
	fwrite(skillcool1, sizeof(int), 1, S);//技能冷却或持续时间
	fwrite(skillcool2, sizeof(int), 1, S);
	fwrite(skill1, sizeof(char), 1, S);//技能状态
	fwrite(skill2, sizeof(char), 1, S);
	fclose(S);
}

void Pause(int*gameres,int*button,IMAGE SAV,IMAGE CONTI,IMAGE MENU,IMAGE UNSAV,IMAGE UNCONTI,IMAGE UNMENU) {
	putimage(849, 459, &CONTI);
	FlushBatchDraw();
	char pausebutton = 'C';
	while (1) {
		if (GetAsyncKeyState(VK_RETURN)) {
			if (pausebutton == 'C') {//继续
				putimage(849, 459, &UNCONTI);
			}
			else if (pausebutton == 'S') {//存档
				putimage(849, 519, &UNSAV);
				mciSendString(TEXT("close Sound"), NULL, 0, NULL);
				Sleep(1);
				mciSendString(TEXT(" open .\\SoundEffect\\Save.mp3 alias Sound"), NULL, 0, NULL);
				mciSendString(TEXT("play Sound "), NULL, 0, NULL);
				*gameres = SAVE;
			}
			else {//返回主菜单
				putimage(849, 579, &UNMENU);
				*button = 0;
			}
			FlushBatchDraw();
			break;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			if (pausebutton == 'C') {
				putimage(849, 459, &UNCONTI);
				putimage(849, 519, &SAV);
				pausebutton = 'S';
			}
			else if (pausebutton == 'S') {
				putimage(849, 519, &UNSAV);
				putimage(849, 579, &MENU);
				pausebutton = 'M';
			}
			else if (pausebutton == 'M') {
				putimage(849, 579, &UNMENU);
				putimage(849, 459, &CONTI);
				pausebutton = 'C';
			}
			FlushBatchDraw();
		}
		else if (GetAsyncKeyState(VK_UP)) {
			if (pausebutton == 'C') {
				putimage(849, 459, &UNCONTI);
				putimage(849, 579, &MENU);
				pausebutton = 'M';
			}
			else if (pausebutton == 'S') {
				putimage(849, 519, &UNSAV);
				putimage(849, 459, &CONTI);
				pausebutton = 'C';
			}
			else if (pausebutton == 'M') {
				putimage(849, 579, &UNMENU);
				putimage(849, 519, &SAV);
				pausebutton = 'S';
			}
			FlushBatchDraw();
		}
		else if (GetAsyncKeyState(VK_ESCAPE)) {
			HWND hwnd = GetHWnd();
			int MB;
			MB = MessageBox(hwnd, _T("是否要退出游戏?"), _T("退出游戏"), MB_YESNO);
			if (MB == IDYES) {
				*button = -1;
				break;
			}
		}
		else if (GetAsyncKeyState(VK_SPACE)) {
			if (pausebutton == 'C') {
				putimage(849, 459, &UNCONTI);
			}
			else if (pausebutton == 'S') {
				putimage(849, 519, &UNSAV);
			}
			else {
				putimage(849, 579, &UNMENU);
			}
			FlushBatchDraw();
			break;
		}
		Sleep(400);
	}
}