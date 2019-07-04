#include "snake.h"
#include <easyx.h>
#include <Windows.h>
#include <stdio.h>

void OpenList() {
	setlinecolor(BLACK);
	for (int i = 0;i < 640;i++) {
		line(0, i, 1119, i);
	}
	int n, p, q;
	FILE*P;
	fopen_s(&P, ".\\List.txt", "rb");
	
	int van_record[15];
	int lyq_record[15];
	int cat_record[15];
	n = fread(van_record, sizeof(int), 15, P);
	p = fread(lyq_record, sizeof(int), 15, P);
	q = fread(cat_record, sizeof(int), 15, P);
	if (n < 15 || p < 15 || q <15 ) {
		settextstyle(100, 70, 0);
		outtextxy(199, 284, _T("读取错误!!!"));
		FlushBatchDraw();
		fclose(P);
		Sleep(4000);
	}
	else {
		
		IMAGE Van, Lyq, Cat;
		loadimage(&Van, _T(".\\Picture\\VANhead.bmp"));
		loadimage(&Lyq, _T(".\\Picture\\LYQhead.jpg"));
		loadimage(&Cat, _T(".\\Picture\\CAThead.jpg"));
		putimage(249, 19, &Van);
		putimage(549, 19, &Lyq);
		putimage(849, 19, &Cat);
		settextstyle(50, 0, 0);
		outtextxy(9, 124, _T("第一章"));
		outtextxy(9, 284, _T("第二章"));
		outtextxy(9, 444, _T("第三章"));
		outtextxy(49,4,_T("按Esc键"));
		outtextxy(59, 59, _T("离开"));
		setlinecolor(WHITE);
		line(0, 123, 1119, 123);
		line(0, 283, 1119, 283);
		line(0, 443, 1119, 443);
		line(247, 0, 247, 639);
		line(547, 0, 547, 639);
		line(847, 0, 847, 639);
		TCHAR RECORD[45][8];
		for (int i = 0;i < 15;i++) {//将记录转化为字符串
			swprintf_s(RECORD[i], _T("%d"), van_record[i]);
		}
		for (int i = 0;i < 15;i++) {//将记录转化为字符串
			swprintf_s(RECORD[i + 15], _T("%d"), lyq_record[i]);
		}
		for (int i = 0;i < 15;i++) {//将记录转化为字符串
			swprintf_s(RECORD[i + 30], _T("%d"), cat_record[i]);
		}
		settextstyle(30, 0, 0);
		int number = 0;
		for (int j = 249;j <= 1149;j = j + 300) {//每次循环切换人物
			for (int i = 129;i < 279;i = i + 30) {//该人物第一章
				outtextxy(j, i, RECORD[number]);
				number++;
			}
			for (int i = 289;i < 439;i = i + 30) {//该人物第二章
				outtextxy(j, i, RECORD[number]);
				number++;
			}
			for (int i = 449;i < 599;i = i + 30) {//该人物第三章
				outtextxy(j, i, RECORD[number]);
				number++;
			}
		}
		FlushBatchDraw();
		fclose(P);
		while (1) {//按Esc键退出
			if (GetAsyncKeyState(VK_ESCAPE)) {
				setlinecolor(BLACK);
				for (int i = 0;i < 640;i++) {
					line(0, i, 1119, i);
				}
				FlushBatchDraw();
				break;
			}
			Sleep(500);
		}
	}

}