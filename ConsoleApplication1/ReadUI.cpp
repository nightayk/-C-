#include <Windows.h>
#include <easyx.h>

void Read_Character(int*button) {
	*button = 1;
	IMAGE C1, C2, C3, UNC1, UNC2, UNC3;
	loadimage(&C1, _T(".\\Picture\\VANhead.bmp"));
	loadimage(&C2, _T(".\\Picture\\LYQhead.jpg"));
	loadimage(&C3, _T(".\\Picture\\CAThead.jpg"));
	loadimage(&UNC1, _T(".\\Picture\\UNVANhead.jpg"));
	loadimage(&UNC2, _T(".\\Picture\\UNLYQhead.jpg"));
	loadimage(&UNC3, _T(".\\Picture\\UNCAThead.jpg"));
	setlinecolor(BLACK);
	settextcolor(WHITE);
	settextstyle(50, 20, 0);
	for (int y = 0;y < 640;y++) {
		line(0, y, 1129, y);
	}
	putimage(99, 69, &UNC1);
	outtextxy(249, 94, _T("�������� VAN"));
	putimage(99, 269, &UNC2);
	outtextxy(249, 294, _T("�ع� ����Ȩ"));
	putimage(99, 469, &UNC3);
	outtextxy(249, 494, _T("ʥ��ʿ (>��<)"));
	if (*button == 1) {
		putimage(99, 69, &C1);
	}
	else if (*button == 2) {
		putimage(99, 269, &C2);
	}
	else if (*button == 3) {
		putimage(99, 469, &C3);
	}
	outtextxy(449, 19, _T("ѡ���ɫ"));
	FlushBatchDraw();
	mciSendString(TEXT("close Sound"), NULL, 0, NULL);
	Sleep(1);
	mciSendString(TEXT(" open .\\SoundEffect\\ChooseVAN.wav alias Sound"), NULL, 0, NULL);
	mciSendString(TEXT("play Sound "), NULL, 0, NULL);
	while (1) {
		if (GetAsyncKeyState(VK_RETURN)) {//ѡ��ǰ��ɫ
			break;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {//�л���ɫ
			*button = *button + 1;
			if (*button == 2) {
				putimage(99, 69, &UNC1);
				putimage(99, 269, &C2);
				FlushBatchDraw();
				mciSendString(TEXT("close Sound"), NULL, 0, NULL);
				Sleep(1);
				mciSendString(TEXT(" open .\\SoundEffect\\ChooseLYQ.wav alias Sound"), NULL, 0, NULL);
				mciSendString(TEXT("play Sound "), NULL, 0, NULL);
			}
			else if (*button == 3) {
				putimage(99, 269, &UNC2);
				putimage(99, 469, &C3);
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
				FlushBatchDraw();
				mciSendString(TEXT("close Sound"), NULL, 0, NULL);
				Sleep(1);
				mciSendString(TEXT(" open .\\SoundEffect\\ChooseCAT.mp3 alias Sound"), NULL, 0, NULL);
				mciSendString(TEXT("play Sound "), NULL, 0, NULL);
			}
			else if (*button == 1) {
				putimage(99, 269, &UNC2);
				putimage(99, 69, &C1);
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
				FlushBatchDraw();
				mciSendString(TEXT("close Sound"), NULL, 0, NULL);
				Sleep(1);
				mciSendString(TEXT(" open .\\SoundEffect\\ChooseLYQ.wav alias Sound"), NULL, 0, NULL);
				mciSendString(TEXT("play Sound "), NULL, 0, NULL);
			}
		}
		else if (GetAsyncKeyState('1')) {//��ݼ�
			*button = 1;
			putimage(99, 269, &UNC2);
			putimage(99, 469, &UNC3);
			putimage(99, 69, &C1);
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
		else if (GetAsyncKeyState('2')) {//��ݼ�
			*button = 2;
			putimage(99, 69, &UNC1);
			putimage(99, 469, &UNC3);
			putimage(99, 269, &C2);
			FlushBatchDraw();
			mciSendString(TEXT("close Sound"), NULL, 0, NULL);
			Sleep(1);
			mciSendString(TEXT(" open .\\SoundEffect\\ChooseLYQ.wav alias Sound"), NULL, 0, NULL);
			mciSendString(TEXT("play Sound "), NULL, 0, NULL);
		}
		else if (GetAsyncKeyState('3')) {//��ݼ�
			*button = 3;
			putimage(99, 69, &UNC1);
			putimage(99, 269, &UNC2);
			putimage(99, 469, &C3);
			FlushBatchDraw();
			mciSendString(TEXT("close Sound"), NULL, 0, NULL);
			Sleep(1);
			mciSendString(TEXT(" open .\\SoundEffect\\ChooseCAT.mp3 alias Sound"), NULL, 0, NULL);
			mciSendString(TEXT("play Sound "), NULL, 0, NULL);
		}
		else if (GetAsyncKeyState(VK_ESCAPE)) {//�˳�ѡ���ɫҳ��
			*button = 0;
			break;
		}
		Sleep(300);
	}
}