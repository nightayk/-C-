#include <easyx.h>
#include "snake.h"
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")



void StartButton(int*button, IMAGE USTART_CAMPAIGN, IMAGE USTART_READ, IMAGE USTART_LIST, IMAGE USTART_QUIT, IMAGE START_CAMPAIGN, IMAGE START_READ, IMAGE START_LIST, IMAGE START_QUIT) {
	setlinecolor(BLACK);
	for (int i = 0;i < 640;i++) {
		line(0, i, 1119, i);
	}
	loadimage(NULL, _T(".\\Picture\\background_2.jpg"));
	putimage(749, 49, &USTART_CAMPAIGN);
	putimage(749, 209, &USTART_READ);
	putimage(749, 369, &USTART_LIST);
	putimage(749, 529, &USTART_QUIT);
	if(*button==CAMPAIGN)putimage(749, 49, &START_CAMPAIGN);
	else if(*button==READ)putimage(749, 209, &START_READ);
	else if(*button==LIST)putimage(749, 369, &START_LIST);
	FlushBatchDraw();
	while (1) {
		if (GetAsyncKeyState(VK_RETURN)) {//按下回车键
			if (*button == CAMPAIGN) {//进入战役选择界面
				break;
			}
			else if (*button == READ) {//进入读档界面
				mciSendString(TEXT("close Sound"), NULL, 0, NULL);
				Sleep(1);
				mciSendString(TEXT(" open .\\SoundEffect\\Read.mp3 alias Sound"), NULL, 0, NULL);
				mciSendString(TEXT("play Sound "), NULL, 0, NULL);
				Sleep(1000);
				setlinecolor(BLACK);
				settextstyle(100, 0, 0);
				for (int i = 0;i < 640;i++) {
					line(0, i, 1119, i);
				}
				outtextxy(409, 269, _T("读取存档中..."));
				break;
			}
			else if (*button == LIST) {//进入排行榜界面
				mciSendString(TEXT("close Sound"), NULL, 0, NULL);
				Sleep(1);
				mciSendString(TEXT(" open .\\SoundEffect\\Choose.mp3 alias Sound"), NULL, 0, NULL);
				mciSendString(TEXT("play Sound "), NULL, 0, NULL);
				Sleep(1000);
				break;
			}
			else {//退出
				*button = 0;
				break;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN)) {//按下"↓"
			*button = *button + 1;
			mciSendString(TEXT("close Sound"), NULL, 0, NULL);
			Sleep(1);
			mciSendString(TEXT(" open .\\SoundEffect\\Button.mp3 alias Sound"), NULL, 0, NULL);
			mciSendString(TEXT("play Sound "), NULL, 0, NULL);
			if (*button == 2) {//由CAMPAIGN->READ
				putimage(749, 49, &USTART_CAMPAIGN);
				putimage(749, 209, &START_READ);
			}
			else if (*button == 3) {//由READ->LIST
				putimage(749, 209, &USTART_READ);
				putimage(749, 369, &START_LIST);
			}
			else if (*button == 4) {//由LIST->QUIT
				putimage(749, 369, &USTART_LIST);
				putimage(749, 529, &START_QUIT);
			}
			else {//由QUIT->CAMPAIGN
				*button = 1;
				putimage(749, 49, &START_CAMPAIGN);
				putimage(749, 529, &USTART_QUIT);
			}
			FlushBatchDraw();
		}
		else if (GetAsyncKeyState(VK_UP)) {//按下"↑"
			*button = *button - 1;
			mciSendString(TEXT("close Sound"), NULL, 0, NULL);
			Sleep(1);
			mciSendString(TEXT(" open .\\SoundEffect\\Button.mp3 alias Sound"), NULL, 0, NULL);
			mciSendString(TEXT("play Sound "), NULL, 0, NULL);
			if (*button == 0) {//由CAMPAIGN->QUIT
				*button = 4;
				putimage(749, 49, &USTART_CAMPAIGN);
				putimage(749, 529, &START_QUIT);
			}
			else if (*button == 1) {//由READ->CAMPAIGN
				putimage(749, 209, &USTART_READ);
				putimage(749, 49, &START_CAMPAIGN);
			}
			else if (*button == 2) {//由LIST->READ
				putimage(749, 369, &USTART_LIST);
				putimage(749, 209, &START_READ);
			}
			else {//由QUIT->CHOOSE
				putimage(749, 529, &USTART_QUIT);
				putimage(749, 369, &START_LIST);
			}
			FlushBatchDraw();
		}
		else if (GetAsyncKeyState('C')) {//快捷键Campaign
			if (*button != 1) {//是跳转到Campaign
				mciSendString(TEXT("close Sound"), NULL, 0, NULL);
				Sleep(1);
				mciSendString(TEXT(" open .\\SoundEffect\\Button.mp3 alias Sound"), NULL, 0, NULL);
				mciSendString(TEXT("play Sound "), NULL, 0, NULL);
				*button = 1;
				putimage(749, 209, &USTART_READ);
				putimage(749, 369, &USTART_LIST);
				putimage(749, 529, &USTART_QUIT);
				putimage(749, 49, &START_CAMPAIGN);
				FlushBatchDraw();
			}
			else {//已经选定目标,再次按快捷键相当于回车
				break;
			}
		}
		else if (GetAsyncKeyState('R')) {//快捷键Read
			if (*button != 2) {//是跳转到Read
				mciSendString(TEXT("close Sound"), NULL, 0, NULL);
				Sleep(1);
				mciSendString(TEXT(" open .\\SoundEffect\\Button.mp3 alias Sound"), NULL, 0, NULL);
				mciSendString(TEXT("play Sound "), NULL, 0, NULL);
				*button = 2;
				putimage(749, 49, &USTART_CAMPAIGN);
				putimage(749, 369, &USTART_LIST);
				putimage(749, 529, &USTART_QUIT);
				putimage(749, 209, &START_READ);
				FlushBatchDraw();
			}
			else {//已经选定目标,再次按快捷键相当于回车
				break;
			}
		}
		else if (GetAsyncKeyState('T')) {//快捷键List
			if (*button != 3) {//是跳转到List
				mciSendString(TEXT("close Sound"), NULL, 0, NULL);
				Sleep(1);
				mciSendString(TEXT(" open .\\SoundEffect\\Button.mp3 alias Sound"), NULL, 0, NULL);
				mciSendString(TEXT("play Sound "), NULL, 0, NULL);
				*button = 3;
				putimage(749, 49, &USTART_CAMPAIGN);
				putimage(749, 209, &USTART_READ);
				putimage(749, 529, &USTART_QUIT);
				putimage(749, 369, &START_LIST);
				FlushBatchDraw();
			}
			else {//已经选定目标,再次按快捷键相当于回车
				break;
			}
		}
		else if (GetAsyncKeyState('Q')) {//快捷键Quit
			if (*button != 4) {//是跳转到Quit
				mciSendString(TEXT("close Sound"), NULL, 0, NULL);
				Sleep(1);
				mciSendString(TEXT(" open .\\SoundEffect\\Button.mp3 alias Sound"), NULL, 0, NULL);
				mciSendString(TEXT("play Sound "), NULL, 0, NULL);
				*button = 4;
				putimage(749, 49, &USTART_CAMPAIGN);
				putimage(749, 209, &USTART_READ);
				putimage(749, 369, &USTART_LIST);
				putimage(749, 529, &START_QUIT);
				FlushBatchDraw();
			}
			else {//已经选定目标,再次按快捷键相当于回车
				*button = 0;
				break;
			}
		}
		else if (GetAsyncKeyState(VK_ESCAPE)) {
			HWND hwnd = GetHWnd();
			int MB;
			MB = MessageBox(hwnd, _T("是否要退出游戏?"), _T("退出游戏"), MB_YESNO);
			if (MB == IDYES) {
				*button = 0;
				break;
			}
		}
		Sleep(250);
	}
}



void Campaign_Character(int*button) {
	IMAGE C1, C2, C3, UNC1, UNC2, UNC3, C1T, C2T, C3T;
	loadimage(&C1, _T(".\\Picture\\VANhead.bmp"));
	loadimage(&C2, _T(".\\Picture\\LYQhead.jpg"));
	loadimage(&C3, _T(".\\Picture\\CAThead.jpg"));
	loadimage(&UNC1, _T(".\\Picture\\UNVANhead.jpg"));
	loadimage(&UNC2, _T(".\\Picture\\UNLYQhead.jpg"));
	loadimage(&UNC3, _T(".\\Picture\\UNCAThead.jpg"));
	loadimage(&C1T, _T(".\\Picture\\VANtext.jpg"));
	loadimage(&C2T, _T(".\\Picture\\LYQtext.jpg"));
	loadimage(&C3T, _T(".\\Picture\\CATtext.jpg"));
	IMAGE C1S1, C2S1, C2S2, C3S1, C3S2;
	loadimage(&C1S1, _T(".\\Picture\\VANskill1.jpg"));
	loadimage(&C2S1, _T(".\\Picture\\LYQskill1.jpg"));
	loadimage(&C2S2, _T(".\\Picture\\LYQskill2.jpg"));
	loadimage(&C3S1, _T(".\\Picture\\CATskill1.jpg"));
	loadimage(&C3S2, _T(".\\Picture\\CATskill2.jpg"));
	IMAGE C1S1T, C2S1T, C2S2T, C3S1T, C3S2T;
	loadimage(&C1S1T, _T(".\\Picture\\VANskill1text.jpg"));
	loadimage(&C2S1T, _T(".\\Picture\\LYQskill1text.jpg"));
	loadimage(&C2S2T, _T(".\\Picture\\LYQskill2text.jpg"));
	loadimage(&C3S1T, _T(".\\Picture\\CATskill1text.jpg"));
	loadimage(&C3S2T, _T(".\\Picture\\CATskill2text.jpg"));
	setlinecolor(BLACK);
	settextcolor(WHITE);
	settextstyle(50, 20, 0);
	for (int y = 0;y < 640;y++) {
		line(0, y, 1129, y);
	}
	putimage(99, 69, &UNC1);
	outtextxy(249, 94, _T("暗黑贤者 VAN"));
	putimage(99, 269, &UNC2);
	outtextxy(249, 294, _T("特工 廖昱权"));
	putimage(99, 469, &UNC3);
	outtextxy(249, 494, _T("圣骑士 (>ω<)"));
	putimage(599, 279, &C1S1);
	putimage(669, 259, &C1S1T);
	putimage(559, 39, &C1T);
	if (*button == 1) {
		putimage(99, 69, &C1);
	}
	else if (*button == 2) {
		putimage(99, 269, &C2);
	}
	else if (*button == 3) {
		putimage(99, 469, &C3);
	}
	FlushBatchDraw();
	mciSendString(TEXT("close Sound"), NULL, 0, NULL);
	Sleep(1);
	mciSendString(TEXT(" open .\\SoundEffect\\ChooseVAN.wav alias Sound"), NULL, 0, NULL);
	mciSendString(TEXT("play Sound "), NULL, 0, NULL);
	while (1) {
		if (GetAsyncKeyState(VK_RETURN)) {//选择当前角色
			break;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {//切换角色
			*button = *button + 1;
			if (*button == 2) {
				putimage(99, 69, &UNC1);
				putimage(99, 269, &C2);
				putimage(599, 279, &C2S1);
				putimage(669, 259, &C2S1T);
				putimage(599, 459, &C2S2);
				putimage(669, 439, &C2S2T);
				putimage(559, 39, &C2T);
				FlushBatchDraw();
				mciSendString(TEXT("close Sound"), NULL, 0, NULL);
				Sleep(1);
				mciSendString(TEXT(" open .\\SoundEffect\\ChooseLYQ.wav alias Sound"), NULL, 0, NULL);
				mciSendString(TEXT("play Sound "), NULL, 0, NULL);
			}
			else if (*button == 3) {
				putimage(99, 269, &UNC2);
				putimage(99, 469, &C3);
				putimage(599, 279, &C3S1);
				putimage(669, 259, &C3S1T);
				putimage(599, 459, &C3S2);
				putimage(669, 439, &C3S2T);
				putimage(559, 39, &C3T);
				FlushBatchDraw();
				mciSendString(TEXT("close Sound"), NULL, 0, NULL);
				Sleep(1);
				mciSendString(TEXT(" open .\\SoundEffect\\ChooseCAT.mp3 alias Sound"), NULL, 0, NULL);
				mciSendString(TEXT("play Sound "), NULL, 0, NULL);
			}
			else if (*button == 4) {
				*button = 1;
				putimage(99, 469, &UNC3);
				putimage(99, 69, &C1);
				putimage(599, 279, &C1S1);
				putimage(669, 259, &C1S1T);
				putimage(559, 39, &C1T);
				setlinecolor(BLACK);
				for (int y = 439;y < 640;y++) {
					line(599, y, 1119, y);
				}
				FlushBatchDraw();
				mciSendString(TEXT("close Sound"), NULL, 0, NULL);
				Sleep(1);
				mciSendString(TEXT(" open .\\SoundEffect\\ChooseVAN.wav alias Sound"), NULL, 0, NULL);
				mciSendString(TEXT("play Sound "), NULL, 0, NULL);
			}
		}
		else if (GetAsyncKeyState(VK_UP)) {
			*button = *button - 1;
			if (*button == 0) {
				*button = 3;
				putimage(99, 69, &UNC1);
				putimage(99, 469, &C3);
				putimage(599, 279, &C3S1);
				putimage(669, 259, &C3S1T);
				putimage(599, 459, &C3S2);
				putimage(669, 439, &C3S2T);
				putimage(559, 39, &C3T);
				FlushBatchDraw();
				mciSendString(TEXT("close Sound"), NULL, 0, NULL);
				Sleep(1);
				mciSendString(TEXT(" open .\\SoundEffect\\ChooseCAT.mp3 alias Sound"), NULL, 0, NULL);
				mciSendString(TEXT("play Sound "), NULL, 0, NULL);
			}
			else if (*button == 1) {
				putimage(99, 269, &UNC2);
				putimage(99, 69, &C1);
				putimage(599, 279, &C1S1);
				putimage(669, 259, &C1S1T);
				putimage(559, 39, &C1T);
				setlinecolor(BLACK);
				for (int y = 439;y < 640;y++) {
					line(599, y, 1119, y);
				}
				FlushBatchDraw();
				mciSendString(TEXT("close Sound"), NULL, 0, NULL);
				Sleep(1);
				mciSendString(TEXT(" open .\\SoundEffect\\ChooseVAN.wav alias Sound"), NULL, 0, NULL);
				mciSendString(TEXT("play Sound "), NULL, 0, NULL);
			}
			else if (*button == 2) {
				putimage(99, 469, &UNC3);
				putimage(99, 269, &C2);
				putimage(599, 279, &C2S1);
				putimage(669, 259, &C2S1T);
				putimage(599, 459, &C2S2);
				putimage(669, 439, &C2S2T);
				putimage(559, 39, &C2T);
				FlushBatchDraw();
				mciSendString(TEXT("close Sound"), NULL, 0, NULL);
				Sleep(1);
				mciSendString(TEXT(" open .\\SoundEffect\\ChooseLYQ.wav alias Sound"), NULL, 0, NULL);
				mciSendString(TEXT("play Sound "), NULL, 0, NULL);
			}
		}
		else if (GetAsyncKeyState(VK_ESCAPE)) {//退出选择角色页面
			*button = 0;
			break;
		}
		else if (GetAsyncKeyState('1')) {//快捷键
			*button = 1;
			putimage(99, 269, &UNC2);
			putimage(99, 469, &UNC3);
			putimage(99, 69, &C1);
			putimage(599, 279, &C1S1);
			putimage(669, 259, &C1S1T);
			putimage(559, 39, &C1T);
			setlinecolor(BLACK);
			for (int y = 439;y < 640;y++) {
				line(599, y, 1119, y);
			}
			FlushBatchDraw();
			mciSendString(TEXT("close Sound"), NULL, 0, NULL);
			Sleep(1);
			mciSendString(TEXT(" open .\\SoundEffect\\ChooseVAN.wav alias Sound"), NULL, 0, NULL);
			mciSendString(TEXT("play Sound "), NULL, 0, NULL);
		}
		else if (GetAsyncKeyState('2')) {//快捷键
			*button = 2;
			putimage(99, 69, &UNC1);
			putimage(99, 469, &UNC3);
			putimage(99, 269, &C2);
			putimage(599, 279, &C2S1);
			putimage(669, 259, &C2S1T);
			putimage(599, 459, &C2S2);
			putimage(669, 439, &C2S2T);
			putimage(559, 39, &C2T);
			FlushBatchDraw();
			mciSendString(TEXT("close Sound"), NULL, 0, NULL);
			Sleep(1);
			mciSendString(TEXT(" open .\\SoundEffect\\ChooseLYQ.wav alias Sound"), NULL, 0, NULL);
			mciSendString(TEXT("play Sound "), NULL, 0, NULL);
		}
		else if (GetAsyncKeyState('3')) {//快捷键
			*button = 3;
			putimage(99, 69, &UNC1);
			putimage(99, 269, &UNC2);
			putimage(99, 469, &C3);
			putimage(599, 279, &C3S1);
			putimage(669, 259, &C3S1T);
			putimage(599, 459, &C3S2);
			putimage(669, 439, &C3S2T);
			putimage(559, 39, &C3T);
			FlushBatchDraw();
			mciSendString(TEXT("close Sound"), NULL, 0, NULL);
			Sleep(1);
			mciSendString(TEXT(" open .\\SoundEffect\\ChooseCAT.mp3 alias Sound"), NULL, 0, NULL);
			mciSendString(TEXT("play Sound "), NULL, 0, NULL);
		}
		Sleep(300);
	}
}

void Campaign_VAN(int*button) {
	*button = 1;
	IMAGE SELECT;
	loadimage(&SELECT, _T(".\\Picture\\SELECT.jpg"));
	setlinecolor(WHITE);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(100, 40, 0);
	outtextxy(409,9,_T("选择章节"));
	putimage(79, 89, &SELECT);
	
	settextstyle(50, 20, 0);
	outtextxy(239, 149, _T("第一章:  控制台程序"));
	outtextxy(239, 299, _T("第二章:  蛇"));
	outtextxy(239, 449, _T("第三章:  我最后的BUG"));
	FlushBatchDraw();
	while (1) {
		if (GetAsyncKeyState(VK_RETURN)) {
			break;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			*button = *button + 1;
			mciSendString(TEXT("close Sound"), NULL, 0, NULL);
			Sleep(1);
			mciSendString(TEXT(" open .\\SoundEffect\\Button.mp3 alias Sound"), NULL, 0, NULL);
			mciSendString(TEXT("play Sound "), NULL, 0, NULL);
			if (*button == 2) {
				for (int y = 89;y < 240;y++) {
					line(79, y, 229, y);
				}
				putimage(79, 239, &SELECT);
				FlushBatchDraw();
			}
			else if(*button == 3) {
				for (int y = 239;y < 390;y++) {
					line(79, y, 229, y);
				}
				putimage(79, 389, &SELECT);
				FlushBatchDraw();
			}
			else *button = 3;//以后留着做其他关卡
		}
		else if (GetAsyncKeyState(VK_UP)) {
			*button = *button - 1;
			mciSendString(TEXT("close Sound"), NULL, 0, NULL);
			Sleep(1);
			mciSendString(TEXT(" open .\\SoundEffect\\Button.mp3 alias Sound"), NULL, 0, NULL);
			mciSendString(TEXT("play Sound "), NULL, 0, NULL);
			if (*button == 1) {
				for (int y = 239;y < 390;y++) {
					line(79, y, 229, y);
				}
				putimage(79, 89, &SELECT);
				FlushBatchDraw();
			}
			else if (*button == 2) {
				for (int y = 389;y < 540;y++) {
					line(79, y, 229, y);
				}
				putimage(79, 239, &SELECT);
				FlushBatchDraw();
			}
			else *button = 1;//以后留着做其他关卡
		}
		else if (GetAsyncKeyState(VK_ESCAPE)) {//退出当前界面
			*button = 0;
			break;
		}
		Sleep(400);
	}
}

void Campaign_LYQ(int*button) {
	*button = 1;
	IMAGE SELECT;
	loadimage(&SELECT, _T(".\\Picture\\SELECT.jpg"));
	setlinecolor(WHITE);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(100, 40, 0);
	outtextxy(409, 9, _T("选择章节"));
	putimage(79, 89, &SELECT);

	settextstyle(50, 20, 0);
	outtextxy(239, 149, _T("第一章:  大门"));
	outtextxy(239, 299, _T("第二章:  大厅机房"));
	outtextxy(239, 449, _T("第三章:  内部房间"));
	FlushBatchDraw();
	while (1) {
		if (GetAsyncKeyState(VK_RETURN)) {
			break;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			*button = *button + 1;
			mciSendString(TEXT("close Sound"), NULL, 0, NULL);
			Sleep(1);
			mciSendString(TEXT(" open .\\SoundEffect\\Button.mp3 alias Sound"), NULL, 0, NULL);
			mciSendString(TEXT("play Sound "), NULL, 0, NULL);
			if (*button == 2) {
				for (int y = 89;y < 240;y++) {
					line(79, y, 229, y);
				}
				putimage(79, 239, &SELECT);
				FlushBatchDraw();
			}
			else if (*button == 3) {
				for (int y = 239;y < 390;y++) {
					line(79, y, 229, y);
				}
				putimage(79, 389, &SELECT);
				FlushBatchDraw();
			}
			else *button = 3;//以后留着做其他关卡
		}
		else if (GetAsyncKeyState(VK_UP)) {
			*button = *button - 1;
			mciSendString(TEXT("close Sound"), NULL, 0, NULL);
			Sleep(1);
			mciSendString(TEXT(" open .\\SoundEffect\\Button.mp3 alias Sound"), NULL, 0, NULL);
			mciSendString(TEXT("play Sound "), NULL, 0, NULL);
			if (*button == 1) {
				for (int y = 239;y < 390;y++) {
					line(79, y, 229, y);
				}
				putimage(79, 89, &SELECT);
				FlushBatchDraw();
			}
			else if (*button == 2) {
				for (int y = 389;y < 540;y++) {
					line(79, y, 229, y);
				}
				putimage(79, 239, &SELECT);
				FlushBatchDraw();
			}
			else *button = 1;//以后留着做其他关卡
		}
		else if (GetAsyncKeyState(VK_ESCAPE)) {//退出当前界面
			*button = 0;
			break;
		}
		Sleep(400);
	}
}

void Campaign_CAT(int*button) {
	*button = 1;
	IMAGE SELECT;
	loadimage(&SELECT, _T(".\\Picture\\SELECT.jpg"));
	setlinecolor(WHITE);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(100, 40, 0);
	outtextxy(409, 9, _T("选择章节"));
	putimage(79, 89, &SELECT);

	settextstyle(50, 20, 0);
	outtextxy(239, 149, _T("第一章:  键盘"));
	outtextxy(239, 299, _T("第二章:  机箱"));
	outtextxy(239, 449, _T("第三章:  RTX2080ti"));
	FlushBatchDraw();
	while (1) {
		if (GetAsyncKeyState(VK_RETURN)) {
			break;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			*button = *button + 1;
			mciSendString(TEXT("close Sound"), NULL, 0, NULL);
			Sleep(1);
			mciSendString(TEXT(" open .\\SoundEffect\\Button.mp3 alias Sound"), NULL, 0, NULL);
			mciSendString(TEXT("play Sound "), NULL, 0, NULL);
			if (*button == 2) {
				for (int y = 89;y < 240;y++) {
					line(79, y, 229, y);
				}
				putimage(79, 239, &SELECT);
				FlushBatchDraw();
			}
			else if (*button == 3) {
				for (int y = 239;y < 390;y++) {
					line(79, y, 229, y);
				}
				putimage(79, 389, &SELECT);
				FlushBatchDraw();
			}
			else *button = 3;//以后留着做其他关卡
		}
		else if (GetAsyncKeyState(VK_UP)) {
			*button = *button - 1;
			mciSendString(TEXT("close Sound"), NULL, 0, NULL);
			Sleep(1);
			mciSendString(TEXT(" open .\\SoundEffect\\Button.mp3 alias Sound"), NULL, 0, NULL);
			mciSendString(TEXT("play Sound "), NULL, 0, NULL);
			if (*button == 1) {
				for (int y = 239;y < 390;y++) {
					line(79, y, 229, y);
				}
				putimage(79, 89, &SELECT);
				FlushBatchDraw();
			}
			else if (*button == 2) {
				for (int y = 389;y < 540;y++) {
					line(79, y, 229, y);
				}
				putimage(79, 239, &SELECT);
				FlushBatchDraw();
			}
			else *button = 1;//以后留着做其他关卡
		}
		else if (GetAsyncKeyState(VK_ESCAPE)) {//退出当前界面
			*button = 0;
			break;
		}
		Sleep(400);
	}
}


void Campaign(int*button,char*charac) {
	PlaySound(NULL, NULL, SND_FILENAME);
	mciSendString(TEXT("close Sound"), NULL, 0, NULL);
	Sleep(1);
	mciSendString(TEXT(" open .\\SoundEffect\\Campaign.mp3 alias Sound"), NULL, 0, NULL);
	mciSendString(TEXT("play Sound "), NULL, 0, NULL);
	Sleep(1000);
	while (_kbhit())_getch();//清空键盘缓冲区
	while (1) {
		*button = 1;
		Campaign_Character(button);
		setlinecolor(WHITE);
		for (int y = 0;y < 640;y++) {
			line(0, y, 1119, y);
		}
		FlushBatchDraw();
		if (*button == 0) {
			break;
		}
		else if (*button == 1) {
			Campaign_VAN(button);
			*charac = VAN;
			break;
		}
		else if (*button == 2) {
			Campaign_LYQ(button);
			*charac = LYQ;
			break;
		}
		else if (*button == 3) {
			Campaign_CAT(button);
			*charac = CAT;
			break;
		}
	}
}


