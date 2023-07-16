#pragma once
#ifndef _GO_H_
#define _GO_H_
#include"Game.h"
#include"acllib.h"

enum MOVE
{
	FORWARD,
	RIGHT,
	BACKWARD,
	LEFT,
};

class GameObject :public Messager
{
	int x; int y;
	MOVE gesture;
	ACL_Color brushcolor;
	ACL_Color pencolor;
	bool ifdraw = false;
public:
	static enum GOTYPE
	{
		TANK,
		BOOM,
		TARGET,
	};
	GOTYPE type;
	GameObject(int x, int y, MOVE gesture, ACL_Color brushcolor, ACL_Color pencolor);
	virtual bool collide_check(GameObject* obj, GOTYPE type) = 0;
	virtual void draw() = 0;
	virtual int getx() { return x; }
	virtual int gety() { return y; }
	virtual MOVE getgst() { return gesture; }
	virtual ACL_Color getpencolor() { return pencolor; }
	virtual ACL_Color getbrushcolor() { return brushcolor; }
	virtual bool getifdraw() { return ifdraw; }
	virtual void setx(int x) { this->x = x; }
	virtual void sety(int y) { this->y = y; }
	virtual void setgst(MOVE gesture) { this->gesture = gesture; }
	virtual void setifdraw(bool ifdraw) { this->ifdraw = ifdraw; }
	virtual void Receive(MESSAGE message) = 0;
};

#endif