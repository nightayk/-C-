#include "snake.h"
#include <easyx.h>

void PoisonACT(int*poisonmap[2], int*poisonaction, int*poisonmaxcount, IMAGE POI) {
	int i = 0, j = 0;
	if (*poisonaction == SHINE) {
		for (int temp = 0;temp < (*poisonmaxcount);temp++) {
			if (poisonmap[0][temp] != NONE) {
				putimage(199 + poisonmap[0][temp] * 20, 19 + poisonmap[1][temp] * 20, &POI);
			}
		}
		*poisonaction = DARK;
		FlushBatchDraw();
	}
	else {
		for (int temp = 0;temp < (*poisonmaxcount);temp++) {
			if (poisonmap[0][temp] != NONE) {
				fillrectangle(199 + poisonmap[0][temp] * 20, 19 + poisonmap[1][temp] * 20, 219 + poisonmap[0][temp] * 20, 39 + poisonmap[1][temp] * 20);
			}
		}
		*poisonaction = SHINE;
		FlushBatchDraw();
	}
}