#include"Boom.h"
#include"Game.h"
#include"GameObject.h"
#include"Messager.h"
#include"acllib.h"

Boom::Boom(int x, int y, MOVE gesture, ACL_Color brushColor, ACL_Color penColor)
	:GameObject(x, y, gesture, brushColor, penColor) 
{
	type = GameObject::BOOM;
}
void Boom::draw()
{
	setPenColor(getpencolor());
	setBrushColor(getbrushcolor());
	ellipse(getx() - 5, gety() - 5, getx() + 5, gety() + 5);
}

void Boom::tick()
{
	switch (getgst())
	{
	case FORWARD:
		sety(gety() - 5);
		break;
	case BACKWARD:
		sety(gety() + 5);
		break;
	case LEFT:
		setx(getx() - 5);
		break;
	case RIGHT:
		setx(getx() + 5);
		break;
	}
	draw();
}

bool Boom::collide_check(GameObject* obj, GOTYPE type)
{
	switch (type)
	{
	case GameObject::TANK:
		switch (obj->getgst())
		{
		case FORWARD:
			return (gety() > obj->gety() && gety() < obj->gety() + 20 && getx() > obj->getx() + 20 && getx() < obj->getx() + 30) || (gety() > obj->gety() + 20 && gety() < obj->gety() + 50 && getx() > obj->getx() + 10 && getx() < obj->getx() + 40);
		case BACKWARD:
			return (gety() > obj->gety() + 30 && gety() < obj->gety() + 50 && getx() > obj->getx() + 20 && getx() < obj->getx() + 30) || (gety() > obj->gety() && gety() < obj->gety() + 30 && getx() > obj->getx() + 10 && getx() < obj->getx() + 40);
		case LEFT:
			return (getx() > obj->getx() && getx() < obj->getx() + 20 && gety() > obj->gety() + 20 && gety() < obj->gety() + 30) || (getx() > obj->getx() + 20 && getx() < obj->getx() + 50 && gety() > obj->gety() + 10 && gety() < obj->gety() + 40);
		case RIGHT:
			return (getx() > obj->getx() && getx() < obj->getx() + 30 && gety() > obj->gety() + 10 && gety() < obj->gety() + 40) || (getx() > obj->getx() + 30 && getx() < obj->getx() + 50 && gety() > obj->gety() + 20 && gety() < obj->gety() + 30);
		}
		break;
	case GameObject::TARGET:
		return getx() <= obj->getx() + hit_t && getx() >= obj->getx() - hit_t && gety() <= obj->gety() + hit_t && gety() >= obj->gety() - hit_t;
		break;
	}
}

void Boom::Receive(Messager::MESSAGE message) {}