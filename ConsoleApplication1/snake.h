#pragma once
#define LEFT  'A'
#define RIGHT 'D'
#define UP    'W'
#define DOWN  'S'
#define ESC   0x011B
#define ENTER 0x1C0D
#define STARTX 50                 /*��ʾ��Ϸ������Ļ�ϵ���ʼX����*/ 
#define STARTY 50                 /*��ʾ��Ϸ������Ļ�ϵ���ʼY����*/
#define SIZEX 10                  /*��ʾһ������ĳ���*/
#define SIZEY 10                  /*��ʾһ������Ŀ��*/
#define WALL '#'                  /*��ʾǽ*/
#define FOOD 'O'                  /*��ʾʳ��*/
#define SNAKE '*'                 /*��ʾ��*/
#define BOMB '@'                  /*��ʾը��*/
#define POISON '-'                /*��ʾ��ҩ*/
#define AIR '+'                   /*��ʾ����*/
#define WRONG -3                  /*��ʾ��Ϸ����*/
#define EXIT -2                   /*��ʾ��Esc���˳�*/
#define FAIL -1                   /*��ʾʧ��*/
#define PAUSE 0                   /*��ʾ���ո����ͣ*/
#define ALLRIGHT 1                /*��ʾ��Ϸ��������*/
#define WIN 2                     /*��ʾʤ��*/
#define SAVE 3                    /*��ʾ�浵*/
#define RETURNMENU                /*��ʾ�ص����˵�*/
#define SHINE 1                   /*��ʾ������ʾ*/
#define DARK 0                    /*��ʾ������ʧ*/
#define NONE -1                   /*��ʾ�޶���*/
#define CAMPAIGN 1                /*��ʾ����ս�۽���*/
#define READ 2                    /*��ʾ�����������*/
#define LIST 3                    /*��ʾ�������а����*/
#define QUIT 4                    /*��ʾ�˳���Ϸ*/
#define ENEMY 'E'                 /*��ʾ����*/
#define SIGHT 'L'                 /*��ʾ��������*/
#define TELEPORT 'T'              /*��ʾ������*/
#define VAN 'V'                   /*��ʾ��ɫ*/
#define LYQ 'L'                   /*��ʾ��ɫ*/
#define CAT 'C'                   /*��ʾ��ɫ*/
#define AVAILABLE 'A'             /*��ʾ���ܿ���*/
#define COOLDOWN 'C'              /*��ʾ������ȴ*/
#define USING 'U'                 /*��ʾ������Ч*/

struct Node {/*************�߽ṹ��**************/
	int x;
	int y;
	struct Node *previous;/*ǰ*/
	struct Node *next;
};

typedef struct Node node;

/*
ս�۹ؿ����ݴ洢˳��:
Map[0][0]->Map[0][1]...Map[1][0]...dir
head->y,head->x,slen,poisonmaxcount,bombmaxcount,goal,sscore,sleeptime;

�浵�洢˳��:
Map[][]...dir,button
head...len,poisonmaxcount,snakebodyx[len]y[len],��xһ��,��yһ�鷽ʽ��)...
poitime,goal,score,skillcool1,skillcool2,char*skill1��2...
*/
