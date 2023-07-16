#pragma once
#ifndef _TARGET_H_
#define _TARGET_H_

#include"Game.h"
#include"GameObject.h"
#include"Messager.h"

class Target :public GameObject
{
	bool if_reset;
	bool if_need_reset = false;
public:
	Target(ACL_Color brushcolor, ACL_Color pencolor);
	virtual bool collide_check(GameObject* obj, GOTYPE type)override;
	virtual void draw()override;
	virtual void Receive(MESSAGE message)override;
	void reset();

	template<typename... Args>
	void tick(GameObject* arg, Args... args);

	template<typename... Args>
	void check_ifrebuild(GameObject* arg, Args... args);
	void check_ifrebuild() { if_reset = false; }
};

template<typename... Args>
void Target::check_ifrebuild(GameObject* arg, Args... args)
{
	if (collide_check(arg, arg->type))
	{
		if_reset = true;
		return;
	}
	check_ifrebuild(args...);
}

template<typename... Args>
void Target::tick(GameObject* arg, Args... args)
{
	if (if_need_reset)
	{
		check_ifrebuild(arg, args...);
		while (if_reset)
		{
			reset();
			check_ifrebuild(arg, args...);
		}
		if_need_reset = false;
	}
	if (getifdraw()) draw();
}

#endif