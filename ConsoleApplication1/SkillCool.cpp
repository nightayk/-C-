#include <Windows.h>
#include <easyx.h>
#include "snake.h"

void SkillCool(char*skill1, char*skill2, int*skillcool1, int*skillcool2,IMAGE SKILL1,IMAGE SKILL2) {
	if (*skill1 == COOLDOWN) {//��ȴ��
		*skillcool1 = *skillcool1 - 1;
		if (*skillcool1 == 0) {//��ȴ����
			*skill1 = AVAILABLE;
			putimage(829, 159, &SKILL1);
			FlushBatchDraw();
		}
	}
	if (*skill2 == COOLDOWN) {//��ȴ��
		*skillcool2 = *skillcool2 - 1;
		if (*skillcool2 == 0) {//��ȴ����
			*skill2 = AVAILABLE;
			putimage(829, 249, &SKILL2);
			FlushBatchDraw();
		}
	}
}
