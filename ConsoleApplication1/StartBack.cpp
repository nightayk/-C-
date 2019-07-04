#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <easyx.h>
#include <Windows.h>
#include "snake.h"

void StartFlash() {//开场闪动效果
	setlinecolor(BLACK);
	for (int y = 0;y < 640;y++) {
		line(0, y, 1129, y);
	}
	FlushBatchDraw();
	Sleep(250);
	setlinecolor(WHITE);
	for (int y = 0;y < 640;y++) {
		line(0, y, 1129, y);
	}
	Sleep(1);
	loadimage(NULL, _T(".\\Picture\\background_1.bmp"));
	FlushBatchDraw();
	Sleep(250);
}

void CreatStartBack(IMAGE USTART_CAMPAIGN,IMAGE USTART_READ,IMAGE USTART_LIST,IMAGE USTART_QUIT) {//建立开始界面背景
	initgraph(1120, 640);//创建窗口
	// 获取窗口句柄
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, _T("C课设之战:做个蛇!"));
	// 设置窗口标题文字
	BeginBatchDraw();
	setlinecolor(WHITE);
	for (int y = 0;y < 640;y++) {
		line(0, y, 1129, y);
	}
	loadimage(NULL, _T(".\\Picture\\background_1.bmp"));
	FlushBatchDraw();
	Sleep(4000);
	for (int FlashTime = 0;FlashTime < 5;FlashTime++)
		StartFlash();//开场动画
	setlinecolor(BLACK);
	for (int y = 0;y < 640;y++) {
		line(0, y, 1129, y);
	}
	Sleep(300);
	loadimage(NULL, _T(".\\Picture\\background_2.jpg"));
	FlushBatchDraw();
}
