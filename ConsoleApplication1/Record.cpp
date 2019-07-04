#include "snake.h"
#include <stdio.h>

void Record(int*button, char*charac,int*score) {
	FILE*P;
	fopen_s(&P, ".\\List.txt", "rb");
	int van_record[15];
	int lyq_record[15];
	int cat_record[15];
	fread(van_record, sizeof(int), 15, P);
	fread(lyq_record, sizeof(int), 15, P);
	fread(cat_record, sizeof(int), 15, P);
	fclose(P);
	int i = 0;
	if (*button != 1) {
		i = 5;
		if (*button == 3) {
			i = 10;
		}
	}
	int n = i + 5;
	int temp1, temp2;
	if (*charac == VAN) {
		for (;i < n;i++) {
			if (*score > van_record[i]) {
				temp1 = van_record[i];
				van_record[i] = *score;
				i++;
				break;
			}
		}
		for (;i < n;i++) {
			temp2 = van_record[i];
			van_record[i] = temp1;
			temp1 = temp2;
		}
	}
	else if (*charac == LYQ) {
		for (;i < n;i++) {
			if (*score > lyq_record[i]) {
				temp1 = lyq_record[i];
				lyq_record[i] = *score;
				i++;
				break;
			}
		}
		for (;i < n;i++) {
			temp2 = lyq_record[i];
			lyq_record[i] = temp1;
			temp1 = temp2;
		}
	}
	else if (*charac == CAT) {
		for (;i < n;i++) {
			if (*score > cat_record[i]) {
				temp1 = cat_record[i];
				cat_record[i] = *score;
				i++;
				break;
			}
		}
		for (;i < n;i++) {
			temp2 = cat_record[i];
			cat_record[i] = temp1;
			temp1 = temp2;
		}
	}
	FILE*M;
	fopen_s(&M, ".\\List.txt", "wb+");
	fwrite(van_record, sizeof(int), 15, M);
	fwrite(lyq_record, sizeof(int), 15, M);
	fwrite(cat_record, sizeof(int), 15, M);
	fclose(M);
}