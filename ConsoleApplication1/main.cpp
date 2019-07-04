#include "snake.h"
#include <malloc.h>
#include <easyx.h>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "snake.h"
#include "Interface.h"


TCHAR SCORE[8];//����ͼ�ν�����ʾ����
TCHAR REMAIN[8];//����ͼ�ν�����ʾ��ʤ��Ŀ��ľ���
int FoodMinCount = 1;//ʳ���������
int PoisonMaxCount = 0;//�����������
int*poisonmaxcount = &PoisonMaxCount;//�����������ָ��
int Seed;//����
int*seed = &Seed;//����ָ��
int Sleeptime;//���
int*sleeptime = &Sleeptime;//���ָ��
char Dir;//����
char*dir = &Dir;//����ָ��
IMAGE CHARACTER, C, FOOD1, POI, BOOM, HEAD, WAL, TELE, ENE, SKILL1, SKILL2, UNSKILL1, UNSKILL2, SKILLUSING1, SKILLUSING2,SIG,BLA;//ͼƬ
IMAGE SAV, CONTI, MENU, UNSAV, UNCONTI, UNMENU;
int GameRes = ALLRIGHT;//��Ϸ״̬
int*gameres = &GameRes;//��Ϸ״ָ̬��
char Map[30][30];//��ͼ
char*map[30];//��ͼָ��
int PoisonMap[2][30];//��¼����λ�õ�����
int*poisonmap[2];//ָ���¼����λ�������ָ��
int Score;//����
int*score = &Score;//����ָ��
int Goal;//Ŀ��
int*goal = &Goal;//Ŀ��ָ��
char Charac;//��ɫ
char*charac = &Charac;//��ɫָ��
char Judge = 'I';//�ж��߼�����
char*judge = &Judge;//�ж��߼�����ָ��
int Len = 5;//����
int*len = &Len;//����ָ��
int FoodCount = 0;//ʳ������
int*foodcount = &FoodCount;//ʳ������ָ��
int PoisonCount = 0;//��������
int*poisoncount = &PoisonCount;//��������ָ��
int PoisonAction = SHINE;//������ʾ״̬
int*poisonaction = &PoisonAction;//������ʾ״ָ̬��
int Button = CAMPAIGN;//��ť
int*button = &Button;//��ťָ��
int TeleMap[2][2];//��¼������λ��
int*telemap[2];
int SkillCool1 = 0;//����1��ȴ
int*skillcool1 = &SkillCool1;
int SkillCool2 = 0;//����2��ȴ
int*skillcool2 = &SkillCool2;
char Skill1 = AVAILABLE;//����״̬
char*skill1 = &Skill1;
char Skill2 = AVAILABLE;
char*skill2 = &Skill2;
node*head, *tail, *nexthead;
int poitime = 0;//���ݸ���ʱ��
IMAGE USTART_CAMPAIGN, USTART_READ, USTART_LIST, USTART_QUIT;


IMAGE START_CAMPAIGN, START_READ, START_LIST, START_QUIT;

void StartGame() {
	PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	PlaySound(TEXT(".\\Music\\StartMusic.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	loadimage(&USTART_CAMPAIGN, _T(".\\Picture\\UnStartCampaign.jpg"));
	loadimage(&USTART_READ, _T(".\\Picture\\UnRead.jpg"));
	loadimage(&USTART_LIST, _T(".\\Picture\\UnList.jpg"));
	loadimage(&USTART_QUIT, _T(".\\Picture\\UnQuit.jpg"));

	loadimage(&START_CAMPAIGN, _T(".\\Picture\\StartCampaign.jpg"));
	loadimage(&START_READ, _T(".\\Picture\\Read.jpg"));
	loadimage(&START_LIST, _T(".\\Picture\\List.jpg"));
	loadimage(&START_QUIT, _T(".\\Picture\\Quit.jpg"));

	loadimage(&UNSAV, _T(".\\Picture\\UnSave.jpg"));
	loadimage(&UNCONTI, _T(".\\Picture\\UnContinue.jpg"));
	loadimage(&UNMENU, _T(".\\Picture\\UnMenu.jpg"));
	loadimage(&SAV, _T(".\\Picture\\Save.jpg"));
	loadimage(&CONTI, _T(".\\Picture\\Continue.jpg"));
	loadimage(&MENU, _T(".\\Picture\\Menu.jpg"));
	if (*judge == 'I') {//���ν��벥�Ŷ���
		CreatStartBack(USTART_CAMPAIGN, USTART_READ, USTART_LIST, USTART_QUIT);
	}
	while (1) {
		while (_kbhit())_getch();//��ռ��̻�����
		StartButton(button, USTART_CAMPAIGN, USTART_READ, USTART_LIST, USTART_QUIT, START_CAMPAIGN, START_READ, START_LIST, START_QUIT);
		if (*button == CAMPAIGN) {//ս��
			Campaign(button, charac);
			if (*button != 0) {
				*judge = 'C';
				break;
			}
			else *button = 1;//�����˵�
		}
		else if (*button == READ) {//����
			Read_Character(button);//ѡ���ɫ
			if (*button != 0) {
				*judge = 'R';
				if (*button == 1) {
					*charac = VAN;
				}
				else if (*button == 2) {
					*charac = LYQ;
				}
				else/* *button==3 */{
					*charac = CAT;
				}
				break;
			}
			else*button = 2;//�����˵�
		}
		else if (*button == LIST) {
			OpenList();//�����а�
		}
		else if (*button == 0) {
			break;//�˳���Ϸ
		}
	}
}

void LoadGame() {
	poisonmap[0] = PoisonMap[0];//x������
	poisonmap[1] = PoisonMap[1];//y������
	telemap[0] = TeleMap[0];
	telemap[1] = TeleMap[1];
	head = (node*)malloc(sizeof(node));
	loadimage(&BOOM, _T(".\\Picture\\Calculas.jpg"));
	loadimage(&POI, _T(".\\Picture\\Bug.jpg"));
	loadimage(&C, _T(".\\Picture\\c.png"));
	loadimage(&FOOD1, _T(".\\Picture\\Baidu.bmp"));
	loadimage(&ENE, _T(".\\Picture\\Enemy.jpg"));
	loadimage(&TELE, _T(".\\Picture\\Google.jpg"));
	loadimage(&SIG, _T(".\\Picture\\Sight.jpg"));
	loadimage(&BLA, _T(".\\Picture\\BLACK.png"));
	for (int i = 0;i <= 29;i++) {
		map[i] = Map[i];
	}
	if (Judge == 'C') {//�µ���Ϸ
		FILE *P;
		int BombCount = 0;//ը������
		int*bombcount = &BombCount;//ը������ָ��
		int BombMaxCount;
		int*bombmaxcount = &BombMaxCount;
		if (*charac == VAN) {
			loadimage(&CHARACTER, _T(".\\Picture\\VANnormal.jpg"));
			loadimage(&HEAD, _T(".\\Picture\\VANhead.bmp"));
			loadimage(&WAL, _T(".\\Picture\\VANwall.jpg"));
			loadimage(&SKILL1, _T(".\\Picture\\VANskill1.jpg"));
			loadimage(&UNSKILL1, _T(".\\Picture\\UNVANskill1.jpg"));
			loadimage(&SKILL2, _T(".\\Picture\\EmptySkill.jpg"));
			if (*button == 1) {
				fopen_s(&P, ".\\Campaign\\VAN_1.txt", "rb");
			}
			else if (*button == 2) {
				fopen_s(&P, ".\\Campaign\\VAN_2.txt", "rb");
			}
			else /*if (*button == 3)*/ {
				fopen_s(&P, ".\\Campaign\\VAN_3.txt", "rb");
			}
			telemap[0] = TeleMap[0];//x������
			telemap[1] = TeleMap[1];//y������
			for (int i = 0;i <= 1;i++) {//��ʼ��������������
				for (int j = 0;j <= 1;j++) {
					TeleMap[i][j] = NONE;
				}
			}
			settextstyle(30, 20, 0);//���������С���ʽ
			settextcolor(WHITE);//����������ɫ
			FlushBatchDraw();
		}
		else if (*charac == LYQ) {
			loadimage(&CHARACTER, _T(".\\Picture\\LYQnormal.jpg"));
			loadimage(&HEAD, _T(".\\Picture\\LYQhead.jpg"));
			loadimage(&WAL, _T(".\\Picture\\LYQwall.jpg"));
			loadimage(&SKILL1, _T(".\\Picture\\LYQskill1.jpg"));
			loadimage(&SKILL2, _T(".\\Picture\\LYQskill2.jpg"));
			loadimage(&UNSKILL2, _T(".\\Picture\\UNLYQskill2.jpg"));
			if (*button == 1) {
				fopen_s(&P, ".\\Campaign\\LYQ_1.txt", "rb");
			}
			else if (*button == 2) {
				fopen_s(&P, ".\\Campaign\\LYQ_2.txt", "rb");
			}
			else  /*if (*button == 3)*/ {
				fopen_s(&P, ".\\Campaign\\LYQ_3.txt", "rb");
			}
		}
		else /*if (*charac == CAT)*/ {
			loadimage(&CHARACTER, _T(".\\Picture\\CATnormal.jpg"));
			loadimage(&HEAD, _T(".\\Picture\\CAThead.jpg"));
			loadimage(&WAL, _T(".\\Picture\\CATwall.jpg"));
			loadimage(&SKILL1, _T(".\\Picture\\CATskill1.jpg"));
			loadimage(&SKILL2, _T(".\\Picture\\CATskill2.jpg"));
			loadimage(&UNSKILL1, _T(".\\Picture\\UNCATskill1.jpg"));
			loadimage(&SKILLUSING1, _T(".\\Picture\\CATskillusing1.jpg"));
			if (*button == 1) {
				fopen_s(&P, ".\\Campaign\\CAT_1.txt", "rb");
			}
			else if (*button == 2) {
				fopen_s(&P, ".\\Campaign\\CAT_2.txt", "rb");
			}
			else /*if (*button == 3)*/ {
				fopen_s(&P, ".\\Campaign\\CAT_3.txt", "rb");
			}
		}
		for (int i = 0;i < 30;i++) {
			fread(&Map[i][0], sizeof(char), 30, P);
		}
		fread(&Dir, sizeof(char), 1, P);
		int syx[2];
		fread(syx, sizeof(int), 2, P);
		head->y = syx[0];
		head->x = syx[1];
		fread(&Len, sizeof(int), 1, P);
		fread(&PoisonMaxCount, sizeof(int), 1, P);
		fread(&BombMaxCount, sizeof(int), 1, P);
		fread(&Goal, sizeof(int), 1, P);
		fread(&Score, sizeof(int), 1, P);
		fread(&Sleeptime, sizeof(int), 1, P);
		fclose(P);
		Seed = (unsigned)time(NULL);
		srand(Seed);
		CreatSnake(head, tail, Len, head->x, head->y, Dir);
		while (*bombcount < *bombmaxcount) {
			CreatBomb(seed, map, bombcount, BOOM);
		}
		putimage(829, 159, &SKILL1);
		putimage(829, 249, &SKILL2);
		if(*charac==VAN)		CreatTeleport(seed, map, telemap, TELE);
		/*���¿�ʼ��Ϸʱ��������*/
		*poisoncount = 0;
		*foodcount = 0;
		poitime = 0;
		*skill1 = AVAILABLE;
		*skill2 = AVAILABLE;
		for (int i = 0;i <= 1;i++) {//��ʼ�����ݵ�ͼ
			for (int j = 0;j <= 29;j++) {
				PoisonMap[i][j] = NONE;
			}
		}
		while (*poisoncount < *poisonmaxcount) {
			CreatPoison(seed, map, poisonmap, poisoncount, POI);
		}
	}
	else {//����
		FILE*R;
		if (*charac == VAN) {
			loadimage(&CHARACTER, _T(".\\Picture\\VANnormal.jpg"));
			loadimage(&HEAD, _T(".\\Picture\\VANhead.bmp"));
			loadimage(&WAL, _T(".\\Picture\\VANwall.jpg"));
			loadimage(&SKILL1, _T(".\\Picture\\VANskill1.jpg"));
			loadimage(&UNSKILL1, _T(".\\Picture\\UNVANskill1.jpg"));
			loadimage(&SKILL2, _T(".\\Picture\\EmptySkill.jpg"));
			fopen_s(&R, ".\\Save\\VAN.txt", "rb");
		}
		else if (*charac == LYQ) {
			loadimage(&CHARACTER, _T(".\\Picture\\LYQnormal.jpg"));
			loadimage(&HEAD, _T(".\\Picture\\LYQhead.jpg"));
			loadimage(&WAL, _T(".\\Picture\\LYQwall.jpg"));
			loadimage(&SKILL1, _T(".\\Picture\\LYQskill1.jpg"));
			loadimage(&SKILL2, _T(".\\Picture\\LYQskill2.jpg"));
			loadimage(&UNSKILL2, _T(".\\Picture\\UNLYQskill2.jpg"));
			fopen_s(&R, ".\\Save\\LYQ.txt", "rb");
		}
		else /*if (*charac == CAT)*/ {
			loadimage(&CHARACTER, _T(".\\Picture\\CATnormal.jpg"));
			loadimage(&HEAD, _T(".\\Picture\\CAThead.jpg"));
			loadimage(&WAL, _T(".\\Picture\\CATwall.jpg"));
			loadimage(&SKILL1, _T(".\\Picture\\CATskill1.jpg"));
			loadimage(&SKILL2, _T(".\\Picture\\CATskill2.jpg"));
			loadimage(&UNSKILL1, _T(".\\Picture\\UNCATskill1.jpg"));
			loadimage(&SKILLUSING1, _T(".\\Picture\\CATskillusing1.jpg"));
			fopen_s(&R, ".\\Save\\CAT.txt", "rb");
		}
		for (int i = 0;i < 30;i++) {
			fread(&Map[i][0], sizeof(char), 30, R);
		}
		fread(&Dir, sizeof(char), 1, R);
		fread(&Button, sizeof(int), 1, R);
		int yx[2];
		fread(yx, sizeof(int), 2, R);
		head->y = yx[0];
		head->x = yx[1];
		fread(&Len, sizeof(int), 1, R);
		fread(&PoisonMaxCount, sizeof(int), 1, R);
		int*snakebodyx;
		snakebodyx = (int*)malloc(sizeof(int)*(*len));
		int*snakebodyy;
		snakebodyy = (int*)malloc(sizeof(int)*(*len));
		fread(snakebodyx, sizeof(int), *len, R);
		fread(snakebodyy, sizeof(int), *len, R);
		node*s;
		node*p;
		s = head;
		head->x = snakebodyx[0];
		head->y = snakebodyy[0];
		head->previous = NULL;
		for (int i = 1;i < (*len);i++) {
			p = (node*)malloc(sizeof(node));
			p->x = snakebodyx[i];
			p->y = snakebodyy[i];
			s->next = p;
			p->previous = s;
			s = s->next;
			p = NULL;
		}
		tail = s;
		s->next = NULL;
		fread(&poitime, sizeof(int), 1, R);
		fread(&Goal, sizeof(int), 1, R);
		fread(&Score, sizeof(int), 1, R);
		fread(&SkillCool1, sizeof(int), 1, R);//������ȴ�����ʱ��
		fread(&SkillCool2, sizeof(int), 1, R);
		fread(&Skill1, sizeof(char), 1, R);//����״̬
		fread(&Skill2, sizeof(char), 1, R);
		fclose(R);

		for (int i = 0;i <= 1;i++) {//��ʼ�����ݵ�ͼ
			for (int j = 0;j <= 29;j++) {
				PoisonMap[i][j] = NONE;
			}
		}
		FindPoison(map, poisonmap, poisonmaxcount);
		if (*charac == VAN)FindTeleport(map, telemap);
	}
	setlinecolor(BLACK);
	for (int i = 0;i < 640;i++) {
		line(0, i, 1119, i);
	}
	setlinecolor(WHITE);
	for (int i = 19;i < 619;i++) {
		line(199, i, 798, i);
	}
	settextstyle(30, 20, 0);//���������С���ʽ
	settextcolor(WHITE);//����������ɫ
	if (*charac == VAN) {
		outtextxy(984, 59, _T("VAN"));
		outtextxy(954, 89, _T("��������"));
		settextstyle(30, 15, 0);
		outtextxy(934, 174, _T("�ڰ�ת��"));
	}
	else if (*charac == LYQ) {
		outtextxy(969, 59, _T("����Ȩ"));
		outtextxy(954, 99, _T("  �� ��"));
		settextstyle(30, 15, 0);
		outtextxy(934, 174, _T("��ר��"));
		outtextxy(934, 264, _T("���� (F)"));
	}
	else if (*charac == CAT) {
		outtextxy(984, 59, _T("(>��<)"));
		outtextxy(954, 89, _T("ʥ��ʿ"));
		settextstyle(30, 15, 0);
		outtextxy(934, 174, _T("��ʥ���� (F)"));
		outtextxy(934, 264, _T("����ʥ���"));
		FoodMinCount = 2;
	}
	if (*skill1 == AVAILABLE)putimage(829, 159, &SKILL1);
	else if (*skill1 == COOLDOWN)putimage(829, 159, &UNSKILL1);
	else putimage(829, 159, &SKILLUSING1);
	if (*skill2 == AVAILABLE)putimage(829, 249, &SKILL2);
	else if (*skill2 == COOLDOWN)putimage(829, 249, &UNSKILL2);
	else putimage(829, 249, &SKILLUSING2);
	putimage(849, 579, &UNMENU);
	putimage(849, 519, &UNSAV);
	putimage(849, 459, &UNCONTI);
	PrintMap(map, WAL, BOOM, TELE, ENE, SIG,FOOD1);
	PrintSnake(head, map, CHARACTER, C);
	putimage(849, 49, &HEAD);
	outtextxy(39, 139, _T("����Ŀ��"));
	outtextxy(39, 259, _T("��.C�ļ�"));
	putimage(4, 324, &FOOD1);
	outtextxy(29, 319, _T(":����.C�ļ�"));
	putimage(4, 384, &POI);
	outtextxy(29, 379, _T(":����.C�ļ�"));
	putimage(4, 444, &BOOM);
	outtextxy(29, 439, _T(":.C�ļ�����"));
	outtextxy(829, 329, _T("����"));
	outtextxy(834, 394, _T("���ո����ͣ\\����"));
	if (*charac == VAN) {
		putimage(4, 504, &TELE);
		outtextxy(29, 499, _T(":������"));
	}
	FlushBatchDraw();
}

void RunGame(){
	PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	Sleep(1);
	nexthead = (node*)malloc(sizeof(node));//�����ڴ�ռ�
	mciSendString(TEXT(" open .\\Music\\TANK.wav alias Sound"), NULL, 0, NULL);
	mciSendString(TEXT("play Sound "), NULL, 0, NULL);
	Sleep(5000);
	PlaySound(TEXT(".\\Music\\BGM.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	mciSendString(TEXT("close Sound"), NULL, 0, NULL);
	setlinecolor(WHITE);//���û�ͼ��ɫ
	*gameres = ALLRIGHT;
	while (1) {
		if (*gameres == FAIL) {//��Ϸʧ�����¿�ʼ
			while (head->next != NULL) {//�ͷ��ڴ�ռ�
				head = head->next;
				free(head->previous);
				head->previous = NULL;
			}
			free(head);
			head = NULL;
			Record(button, charac, score);//��¼�÷�
			Fail(button, score);//����ʧ�ܽ���
			break;
		}
		else if (*len == *goal) {//��Ϸʤ��
			Record(button, charac, score);//��¼�÷�
			Win(button, score);//����ʤ������
			Sleep(5000);
			break;
		}
		while (*foodcount < FoodMinCount) {//����ʳ��
			CreatFood(seed, map, foodcount, FOOD1);
		}
		poitime++;//����ͣ��ʱ�������
		if (poitime % 50 == 0) {//����������
			*poisoncount = 0;
			RemovePoison(map, poisonmap, poisonmaxcount);//�Ƴ�����
			while (*poisoncount <= *poisonmaxcount) {//�������ɶ���
				CreatPoison(seed, map, poisonmap, poisoncount, POI);
			}
		}
		PoisonACT(poisonmap, poisonaction, poisonmaxcount, POI);//������˸
		move(head, nexthead, dir,gameres);//�ƶ�
		if (*gameres == PAUSE) {//��ͣ
			while (1) {
				Pause(gameres, button, SAV, CONTI, MENU, UNSAV, UNCONTI, UNMENU);
				if (*gameres == SAVE) {//�浵
					SaveGame(charac, button, map, dir, head, len, poisonmaxcount, poitime, goal, score, skillcool1, skillcool2, skill1, skill2);
					*gameres = PAUSE;
				}
				else { 
					*gameres = ALLRIGHT;
					break;
				}
			}
			if ((*button == 0) || (*button == -1)) break;//�������˵�||�˳���Ϸ
		}
		else if (*gameres == EXIT) {//�˳�
			HWND hwnd = GetHWnd();
			int MB;
			MB = MessageBox(hwnd, _T("�Ƿ�Ҫ�˳���Ϸ?"), _T("�˳���Ϸ"), MB_YESNO);
			if (MB == IDYES) {
				*button = -1;
				break;
			}
			else *gameres = ALLRIGHT;
			if (*button == -1)break;
		}
		CrossMap(nexthead);//��Խ��ͼ�Ĳ���
		if (*charac == VAN) {
			Teleport(nexthead, map, telemap, dir);
			Skill_VAN(skill1, skillcool1, map, nexthead, score, UNSKILL1, poisonmap, poisonmaxcount, foodcount);
		}
		else if (*charac == LYQ) {
			Skill_LYQ(foodcount, poisonmap, poisonmaxcount, map, nexthead, head, tail, dir, len, score, skill2, skillcool2, UNSKILL2);
		}
		else /* *charac ==CAT */ {
			Skill_CAT(poisonmap, poisonmaxcount, skill1, skillcool1, map, nexthead, SKILLUSING1, UNSKILL1, head);
		}
		Sleep(1);
		EatFoodOrItself(nexthead, head, tail, map, len, foodcount, CHARACTER, C, gameres, charac, score);
		TouchBomb(charac, head, tail, map, len, gameres, score);
		TouchPoison(charac, head, tail, map, poisonmap, len, poisonmaxcount, gameres, score);
		HitWall(head, map, gameres, score);
		SkillCool(skill1, skill2, skillcool1, skillcool2, SKILL1, SKILL2);
		Sleep(Sleeptime);
		map[head->y][head->x] = SNAKE;
		nexthead = NULL;
		nexthead = (node*)malloc(sizeof(node));
		*score = *score - 1;
		putimage(919, 329, &BLA);
		swprintf_s(SCORE, _T("%d"), Score);
		outtextxy(919, 329, SCORE);
		putimage(89, 199, &BLA);
		swprintf_s(REMAIN, _T("%d"), (Goal-Len));
		outtextxy(89, 199, REMAIN);
		FlushBatchDraw();
	}
}

int main() {//�������б��뻷����֧��void main,�����ش���int
	while (1) {
		StartGame();//��ʼ��Ϸ
		if (*button == 0) return 0;//�˳���Ϸ
		while (1) {
			if (*button == 0) {
				*button = CAMPAIGN;
				break;
			}//֮ǰ��Ϸʧ�ܺ�ѡ���˳�������Ϸ�з������˵�
			else if (*button == 4) {//����½�ͨ��
				OpenList();//�����а�
				*button = LIST;
				break;
			}
			else if (*button == -1)return 0;//��ESC��ǿ���˳�
			LoadGame();//������Ϸ��ͼ��
			RunGame();//������Ϸ
		}
	}
}