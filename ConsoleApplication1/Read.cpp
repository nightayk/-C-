#include "snake.h"


void FindPoison(char*map[30], int*poisonmap[2], int*poisonmaxcount) {
	int n = 0;
	for (int j = 0;j < 30;j++) {
		for (int i = 0;i < 30;i++) {
			if (map[j][i] == POISON) {
				poisonmap[0][n] = i;
				poisonmap[1][n] = j;
				n++;
				if (n == (*poisonmaxcount)) return;
			}
		}
	}
	for (;n < (*poisonmaxcount);n++) {
		poisonmap[0][n] = NONE;
		poisonmap[1][n] = NONE;
	}
}

void FindTeleport(char*map[30], int*telemap[2]) {
	int n = 0;
	for (int j = 0;j < 30;j++) {
		for (int i = 0;i < 30;i++) {
			if (map[j][i] == TELEPORT) {
				telemap[0][n] = i;
				telemap[1][n] = j;
				n++;
				if (n == 2) break;
			}
		}
		if (n == 2)break;
	}
}