#include <Windows.h>
#include <easyx.h>
#include "snake.h"

void Fail(int*button,int*score) {
	loadimage(NULL, _T(".\\Picture\\BigBlack.jpg"));
	settextstyle(100, 0, 0);
	TCHAR FINALSCORE[8];
	swprintf_s(FINALSCORE, _T("%d"), *score);
	outtextxy(349, 149, FINALSCORE);
	settextstyle(50, 0, 0);
	outtextxy(300, 269, _T("你太菜了"));
	char Choose = 'R';
	IMAGE RESTART, ENDGAME, UNRESTART, UNENDGAME;
	loadimage(&RESTART, _T(".\\Picture\\Restart.jpg"));
	loadimage(&UNRESTART, _T(".\\Picture\\UnRestart.jpg"));
	loadimage(&ENDGAME, _T(".\\Picture\\EndGame.jpg"));
	loadimage(&UNENDGAME, _T(".\\Picture\\UnEndGame.jpg"));
	putimage(59, 349, &RESTART);
	putimage(559, 349, &UNENDGAME);
	FlushBatchDraw();
	while (1) {
		if (GetAsyncKeyState(VK_RIGHT)|| GetAsyncKeyState(VK_LEFT)) {
			if (Choose == 'R') {
				mciSendString(TEXT("close Sound"), NULL, 0, NULL);
				Sleep(1);
				mciSendString(TEXT(" open .\\SoundEffect\\Button.mp3 alias Sound"), NULL, 0, NULL);
				mciSendString(TEXT("play Sound "), NULL, 0, NULL);
				Choose = 'E';
				putimage(59, 349, &UNRESTART);
				putimage(559, 349, &ENDGAME);
			}
			else {
				mciSendString(TEXT("close Sound"), NULL, 0, NULL);
				Sleep(1);
				mciSendString(TEXT(" open .\\SoundEffect\\Button.mp3 alias Sound"), NULL, 0, NULL);
				mciSendString(TEXT("play Sound "), NULL, 0, NULL);
				Choose = 'R';
				putimage(59, 349, &RESTART);
				putimage(559, 349, &UNENDGAME);
			}
			FlushBatchDraw();
		}
		else if (GetAsyncKeyState(VK_RETURN)) {
			if (Choose == 'E')*button = 0;//回到开始界面
			break;
		}
		Sleep(400);
	}
}

void Win(int*button,int*score) {
	loadimage(NULL, _T(".\\Picture\\BigBlack.jpg"));
	settextstyle(100, 0, 0);
	TCHAR FINALSCORE[8];
	swprintf_s(FINALSCORE, _T("%d"), *score);
	outtextxy(349, 149, FINALSCORE);
	if (*button < 3) {
		settextstyle(50, 0, 0);
		outtextxy(300, 269, _T("恭喜你通过本章节"));
		settextstyle(30, 0, 0);
		outtextxy(330, 349, _T("正在读取下一章..."));
	}
	else {
		outtextxy(300, 269, _T("恭喜你完成了全部章节"));
	}
	*button = *button + 1;
}