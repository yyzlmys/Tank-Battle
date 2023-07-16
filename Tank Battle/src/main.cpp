#include"acllib.h"
#include"Boom.h"
#include"Tank.h"
#include"Target.h"
#include<vector>

void update(int id);

Game Tank_Battle;
Tank redtank(Tank::Red, 0, 0, FORWARD, RED, BLUE);
Tank greentank(Tank::Green, x_edge - 60, 0, BACKWARD, GREEN, BLUE);
Target target(YELLOW, BLUE);

int Setup()
{
	redtank.setkey(0x57, 0x53, 0x41, 0x44, 0x43);
	greentank.setkey(VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_SPACE);
	Tank_Battle.init();
	Tank_Battle.setkey(VK_SPACE, VK_BACK, VK_SPACE, VK_SPACE);
	registerTimerEvent(update);
	startTimer(1, 10);
	return 0;
}

void update(int id)
{
	beginPaint();
	clearDevice();
	Tank_Battle.tick(&greentank,&redtank,&target);
	redtank.tick(&Tank_Battle, &target, &greentank);
	greentank.tick(&Tank_Battle, &target, &redtank);
	target.tick(&greentank, &redtank);
	endPaint();
}
