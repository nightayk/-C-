#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <easyx.h>
#include <Windows.h>
#include "snake.h"

void StartFlash() {//��������Ч��
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

void CreatStartBack(IMAGE USTART_CAMPAIGN,IMAGE USTART_READ,IMAGE USTART_LIST,IMAGE USTART_QUIT) {//������ʼ���汳��
	initgraph(1120, 640);//��������
	// ��ȡ���ھ��
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, _T("C����֮ս:������!"));
	// ���ô��ڱ�������
	BeginBatchDraw();
	setlinecolor(WHITE);
	for (int y = 0;y < 640;y++) {
		line(0, y, 1129, y);
	}
	loadimage(NULL, _T(".\\Picture\\background_1.bmp"));
	FlushBatchDraw();
	Sleep(4000);
	for (int FlashTime = 0;FlashTime < 5;FlashTime++)
		StartFlash();//��������
	setlinecolor(BLACK);
	for (int y = 0;y < 640;y++) {
		line(0, y, 1129, y);
	}
	Sleep(300);
	loadimage(NULL, _T(".\\Picture\\background_2.jpg"));
	FlushBatchDraw();
}
