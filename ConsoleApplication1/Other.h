#pragma once
#include "snake.h"
#include <easyx.h>

extern void CreatStartBack(IMAGE USTART_CAMPAIGN, IMAGE USTART_READ, IMAGE USTART_CHOOSE, IMAGE USTART_QUIT);
extern void StartButton(int*button, IMAGE USTART_CAMPAIGN, IMAGE USTART_READ, IMAGE USTART_LIST, IMAGE USTART_QUIT, IMAGE START_CAMPAIGN, IMAGE START_READ, IMAGE START_LIST, IMAGE START_QUIT);
extern void Campaign(int*button,char*charac);
extern void OpenList();
extern void Read_Character(int*button);