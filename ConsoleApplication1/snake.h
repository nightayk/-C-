#pragma once
#define LEFT  'A'
#define RIGHT 'D'
#define UP    'W'
#define DOWN  'S'
#define ESC   0x011B
#define ENTER 0x1C0D
#define STARTX 50                 /*表示游戏区在屏幕上的起始X坐标*/ 
#define STARTY 50                 /*表示游戏区在屏幕上的起始Y坐标*/
#define SIZEX 10                  /*表示一个方块的长度*/
#define SIZEY 10                  /*表示一个方块的宽度*/
#define WALL '#'                  /*表示墙*/
#define FOOD 'O'                  /*表示食物*/
#define SNAKE '*'                 /*表示蛇*/
#define BOMB '@'                  /*表示炸弹*/
#define POISON '-'                /*表示毒药*/
#define AIR '+'                   /*表示空气*/
#define WRONG -3                  /*表示游戏错误*/
#define EXIT -2                   /*表示按Esc键退出*/
#define FAIL -1                   /*表示失败*/
#define PAUSE 0                   /*表示按空格键暂停*/
#define ALLRIGHT 1                /*表示游戏正常进行*/
#define WIN 2                     /*表示胜利*/
#define SAVE 3                    /*表示存档*/
#define RETURNMENU                /*表示回到主菜单*/
#define SHINE 1                   /*表示毒草显示*/
#define DARK 0                    /*表示毒草消失*/
#define NONE -1                   /*表示无东西*/
#define CAMPAIGN 1                /*表示进入战役界面*/
#define READ 2                    /*表示进入读档界面*/
#define LIST 3                    /*表示进入排行榜界面*/
#define QUIT 4                    /*表示退出游戏*/
#define ENEMY 'E'                 /*表示敌人*/
#define SIGHT 'L'                 /*表示敌人视线*/
#define TELEPORT 'T'              /*表示传送门*/
#define VAN 'V'                   /*表示角色*/
#define LYQ 'L'                   /*表示角色*/
#define CAT 'C'                   /*表示角色*/
#define AVAILABLE 'A'             /*表示技能可用*/
#define COOLDOWN 'C'              /*表示技能冷却*/
#define USING 'U'                 /*表示技能生效*/

struct Node {/*************蛇结构体**************/
	int x;
	int y;
	struct Node *previous;/*前*/
	struct Node *next;
};

typedef struct Node node;

/*
战役关卡数据存储顺序:
Map[0][0]->Map[0][1]...Map[1][0]...dir
head->y,head->x,slen,poisonmaxcount,bombmaxcount,goal,sscore,sleeptime;

存档存储顺序:
Map[][]...dir,button
head...len,poisonmaxcount,snakebodyx[len]y[len],以x一组,再y一组方式存)...
poitime,goal,score,skillcool1,skillcool2,char*skill1、2...
*/
