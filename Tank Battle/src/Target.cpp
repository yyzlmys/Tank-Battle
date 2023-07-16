#include"Target.h"
#include"acllib.h"
#include"GameObject.h"
#include"Game.h"
#include<stdlib.h>
#include<ctime>
#include"Messager.h"

Target::Target(ACL_Color brushcolor, ACL_Color pencolor)
	:GameObject(0, 0, FORWARD, brushcolor, pencolor)
{
	type = GameObject::TARGET;
}

void Target::draw()
{
	setBrushColor(getbrushcolor());
	setPenColor(getpencolor());
	ellipse(getx() - 20, gety() - 20, getx() + 20, gety() + 20);
}

void Target::reset()
{
	srand(time(nullptr));
	int z = rand();
	setx(rand() % x_edge);
	sety(rand() % y_edge);
	if (getx() < 20) setx(20);
	if (getx() >= x_edge - 20) setx(x_edge - 20);
	if (gety() < 20) sety(20);
	if (gety() >= y_edge - 20) sety(y_edge - 20);
}

bool Target::collide_check(GameObject* obj, GOTYPE type)
{
	switch (type)
	{
	case GameObject::TANK:
		return (getx() > obj->getx() - 20 && getx() < obj->getx() + 70) && (gety() > obj->gety() - 20 && gety() < obj->gety() + 70);
		break;
	}
}

void Target::Receive(Messager::MESSAGE message)
{
	switch (message)
	{
	case EXPLODE:
		setifdraw(false);
		break;
	case RESTART:
		if_need_reset = true;
		setifdraw(true);
		reset();
		break;
	}
}