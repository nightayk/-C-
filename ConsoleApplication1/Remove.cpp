#include <easyx.h>
#include "snake.h"

void RemovePoison(char*map[30], int*poisonmap[2], int*poisonmaxcount) {
	for (int temp = 0;temp < (*poisonmaxcount);temp++) {
		if(poisonmap[1][temp]!=NONE)
		map[poisonmap[1][temp]][poisonmap[0][temp]] = AIR;
		fillrectangle(199 + poisonmap[0][temp] * 20, 19 + poisonmap[1][temp] * 20, 219 + poisonmap[0][temp] * 20, 39 + poisonmap[1][temp] * 20);
	}
	FlushBatchDraw();
}