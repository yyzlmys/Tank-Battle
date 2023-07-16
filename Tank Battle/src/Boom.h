#pragma once
#ifndef _BOOM_H_
#define _BOOM_H_

#include"Game.h"
#include"GameObject.h"
#include"Messager.h"

class Boom :public GameObject
{ 
public:
	Boom(int x, int y, MOVE gsture, ACL_Color brushColor, ACL_Color penColor);
	bool hit_edge() { return getx() <= 0 || getx() >= x_edge || gety() <= 0 || gety() >= y_edge; }
	void tick();
	virtual bool collide_check(GameObject* obj, GOTYPE type)override;
	virtual void draw()override;
	virtual void Receive(Messager::MESSAGE message)override;
};

#endif