#include "snake.h"
#include <malloc.h>
#include <easyx.h>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "snake.h"
#include "Interface.h"


TCHAR SCORE[8];//用于图形界面显示分数
TCHAR REMAIN[8];//用于图形界面显示与胜利目标的距离
int FoodMinCount = 1;//食物最低数量
int PoisonMaxCount = 0;//毒草最大数量
int*poisonmaxcount = &PoisonMaxCount;//毒草最大数量指针
int Seed;//种子
int*seed = &Seed;//种子指针
int Sleeptime;//间隔
int*sleeptime = &Sleeptime;//间隔指针
char Dir;//方向
char*dir = &Dir;//方向指针
IMAGE CHARACTER, C, FOOD1, POI, BOOM, HEAD, WAL, TELE, ENE, SKILL1, SKILL2, UNSKILL1, UNSKILL2, SKILLUSING1, SKILLUSING2,SIG,BLA;//图片
IMAGE SAV, CONTI, MENU, UNSAV, UNCONTI, UNMENU;
int GameRes = ALLRIGHT;//游戏状态
int*gameres = &GameRes;//游戏状态指针
char Map[30][30];//地图
char*map[30];//地图指针
int PoisonMap[2][30];//记录毒草位置的数组
int*poisonmap[2];//指向记录毒草位置数组的指针
int Score;//分数
int*score = &Score;//分数指针
int Goal;//目标
int*goal = &Goal;//目标指针
char Charac;//角色
char*charac = &Charac;//角色指针
char Judge = 'I';//判断逻辑操作
char*judge = &Judge;//判断逻辑操作指针
int Len = 5;//长度
int*len = &Len;//长度指针
int FoodCount = 0;//食物数量
int*foodcount = &FoodCount;//食物数量指针
int PoisonCount = 0;//毒草数量
int*poisoncount = &PoisonCount;//毒草数量指针
int PoisonAction = SHINE;//毒草显示状态
int*poisonaction = &PoisonAction;//毒草显示状态指针
int Button = CAMPAIGN;//按钮
int*button = &Button;//按钮指针
int TeleMap[2][2];//记录传送门位置
int*telemap[2];
int SkillCool1 = 0;//技能1冷却
int*skillcool1 = &SkillCool1;
int SkillCool2 = 0;//技能2冷却
int*skillcool2 = &SkillCool2;
char Skill1 = AVAILABLE;//技能状态
char*skill1 = &Skill1;
char Skill2 = AVAILABLE;
char*skill2 = &Skill2;
node*head, *tail, *nexthead;
int poitime = 0;//毒草更新时间
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
	if (*judge == 'I') {//初次进入播放动画
		CreatStartBack(USTART_CAMPAIGN, USTART_READ, USTART_LIST, USTART_QUIT);
	}
	while (1) {
		while (_kbhit())_getch();//清空键盘缓冲区
		StartButton(button, USTART_CAMPAIGN, USTART_READ, USTART_LIST, USTART_QUIT, START_CAMPAIGN, START_READ, START_LIST, START_QUIT);
		if (*button == CAMPAIGN) {//战役
			Campaign(button, charac);
			if (*button != 0) {
				*judge = 'C';
				break;
			}
			else *button = 1;//回主菜单
		}
		else if (*button == READ) {//读档
			Read_Character(button);//选择角色
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
			else*button = 2;//回主菜单
		}
		else if (*button == LIST) {
			OpenList();//打开排行榜
		}
		else if (*button == 0) {
			break;//退出游戏
		}
	}
}

void LoadGame() {
	poisonmap[0] = PoisonMap[0];//x坐标组
	poisonmap[1] = PoisonMap[1];//y坐标组
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
	if (Judge == 'C') {//新的游戏
		FILE *P;
		int BombCount = 0;//炸弹数量
		int*bombcount = &BombCount;//炸弹数量指针
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
			telemap[0] = TeleMap[0];//x坐标组
			telemap[1] = TeleMap[1];//y坐标组
			for (int i = 0;i <= 1;i++) {//初始化传送门坐标组
				for (int j = 0;j <= 1;j++) {
					TeleMap[i][j] = NONE;
				}
			}
			settextstyle(30, 20, 0);//设置字体大小与格式
			settextcolor(WHITE);//设置字体颜色
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
		/*重新开始游戏时必须重置*/
		*poisoncount = 0;
		*foodcount = 0;
		poitime = 0;
		*skill1 = AVAILABLE;
		*skill2 = AVAILABLE;
		for (int i = 0;i <= 1;i++) {//初始化毒草地图
			for (int j = 0;j <= 29;j++) {
				PoisonMap[i][j] = NONE;
			}
		}
		while (*poisoncount < *poisonmaxcount) {
			CreatPoison(seed, map, poisonmap, poisoncount, POI);
		}
	}
	else {//读档
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
		fread(&SkillCool1, sizeof(int), 1, R);//技能冷却或持续时间
		fread(&SkillCool2, sizeof(int), 1, R);
		fread(&Skill1, sizeof(char), 1, R);//技能状态
		fread(&Skill2, sizeof(char), 1, R);
		fclose(R);

		for (int i = 0;i <= 1;i++) {//初始化毒草地图
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
	settextstyle(30, 20, 0);//设置字体大小与格式
	settextcolor(WHITE);//设置字体颜色
	if (*charac == VAN) {
		outtextxy(984, 59, _T("VAN"));
		outtextxy(954, 89, _T("暗黑贤者"));
		settextstyle(30, 15, 0);
		outtextxy(934, 174, _T("黑暗转换"));
	}
	else if (*charac == LYQ) {
		outtextxy(969, 59, _T("廖昱权"));
		outtextxy(954, 99, _T("  特 工"));
		settextstyle(30, 15, 0);
		outtextxy(934, 174, _T("格斗专家"));
		outtextxy(934, 264, _T("开火 (F)"));
	}
	else if (*charac == CAT) {
		outtextxy(984, 59, _T("(>ω<)"));
		outtextxy(954, 89, _T("圣骑士"));
		settextstyle(30, 15, 0);
		outtextxy(934, 174, _T("神圣护甲 (F)"));
		outtextxy(934, 264, _T("信仰圣光吧"));
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
	outtextxy(39, 139, _T("距离目标"));
	outtextxy(39, 259, _T("份.C文件"));
	putimage(4, 324, &FOOD1);
	outtextxy(29, 319, _T(":增加.C文件"));
	putimage(4, 384, &POI);
	outtextxy(29, 379, _T(":减少.C文件"));
	putimage(4, 444, &BOOM);
	outtextxy(29, 439, _T(":.C文件减半"));
	outtextxy(829, 329, _T("分数"));
	outtextxy(834, 394, _T("按空格键暂停\\继续"));
	if (*charac == VAN) {
		putimage(4, 504, &TELE);
		outtextxy(29, 499, _T(":传送门"));
	}
	FlushBatchDraw();
}

void RunGame(){
	PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	Sleep(1);
	nexthead = (node*)malloc(sizeof(node));//分配内存空间
	mciSendString(TEXT(" open .\\Music\\TANK.wav alias Sound"), NULL, 0, NULL);
	mciSendString(TEXT("play Sound "), NULL, 0, NULL);
	Sleep(5000);
	PlaySound(TEXT(".\\Music\\BGM.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	mciSendString(TEXT("close Sound"), NULL, 0, NULL);
	setlinecolor(WHITE);//设置绘图颜色
	*gameres = ALLRIGHT;
	while (1) {
		if (*gameres == FAIL) {//游戏失败重新开始
			while (head->next != NULL) {//释放内存空间
				head = head->next;
				free(head->previous);
				head->previous = NULL;
			}
			free(head);
			head = NULL;
			Record(button, charac, score);//记录得分
			Fail(button, score);//进入失败界面
			break;
		}
		else if (*len == *goal) {//游戏胜利
			Record(button, charac, score);//记录得分
			Win(button, score);//进入胜利界面
			Sleep(5000);
			break;
		}
		while (*foodcount < FoodMinCount) {//生成食物
			CreatFood(seed, map, foodcount, FOOD1);
		}
		poitime++;//毒草停留时间计数器
		if (poitime % 50 == 0) {//计数器到期
			*poisoncount = 0;
			RemovePoison(map, poisonmap, poisonmaxcount);//移除毒草
			while (*poisoncount <= *poisonmaxcount) {//重新生成毒草
				CreatPoison(seed, map, poisonmap, poisoncount, POI);
			}
		}
		PoisonACT(poisonmap, poisonaction, poisonmaxcount, POI);//毒草闪烁
		move(head, nexthead, dir,gameres);//移动
		if (*gameres == PAUSE) {//暂停
			while (1) {
				Pause(gameres, button, SAV, CONTI, MENU, UNSAV, UNCONTI, UNMENU);
				if (*gameres == SAVE) {//存档
					SaveGame(charac, button, map, dir, head, len, poisonmaxcount, poitime, goal, score, skillcool1, skillcool2, skill1, skill2);
					*gameres = PAUSE;
				}
				else { 
					*gameres = ALLRIGHT;
					break;
				}
			}
			if ((*button == 0) || (*button == -1)) break;//返回主菜单||退出游戏
		}
		else if (*gameres == EXIT) {//退出
			HWND hwnd = GetHWnd();
			int MB;
			MB = MessageBox(hwnd, _T("是否要退出游戏?"), _T("退出游戏"), MB_YESNO);
			if (MB == IDYES) {
				*button = -1;
				break;
			}
			else *gameres = ALLRIGHT;
			if (*button == -1)break;
		}
		CrossMap(nexthead);//穿越地图的操作
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

int main() {//并非所有编译环境都支持void main,所以特此用int
	while (1) {
		StartGame();//开始游戏
		if (*button == 0) return 0;//退出游戏
		while (1) {
			if (*button == 0) {
				*button = CAMPAIGN;
				break;
			}//之前游戏失败后选择退出或者游戏中返回主菜单
			else if (*button == 4) {//最后章节通关
				OpenList();//打开排行榜
				*button = LIST;
				break;
			}
			else if (*button == -1)return 0;//按ESC键强制退出
			LoadGame();//加载游戏地图等
			RunGame();//进行游戏
		}
	}
}