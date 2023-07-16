#pragma once
#ifndef _TANK_H_
#define _TANK_H_

#include"Game.h"
#include"GameObject.h"
#include"Messager.h"
#include"Boom.h"
#include<vector>

struct SHAPE
{
	int shape[5][5];
	MOVE next1;
	MOVE next2;
};

extern struct SHAPE tkshape[4];

class Tank :public GameObject
{
	struct Lastpos
	{
		int x_last; int y_last; 
		MOVE gesture_last;
		int p_x_last; int p_y_last;
		Lastpos(int x_last, int y_last, MOVE gesture_last, int p_x_last, int p_y_last)
		{
			this->x_last = x_last; this->y_last = y_last; this->gesture_last = gesture_last;
			this->p_x_last = p_x_last; this->p_y_last = p_y_last;
		}
	};
	Lastpos* lastpos = nullptr;
	int camp;
	int p_x, p_y;
	int pts = 0;
	int x_start, y_start;
	int p_x_start; int p_y_start;
	MOVE gesture_start;
	int hot_index = 50;
	int forward_key; int backward_key;
	int left_key; int right_key;
	int fire_key;
	bool ifpaintscore = false;
	std::vector<Boom*> booms = std::vector<Boom*>(5, nullptr);
public:
	static enum CAMP
	{
		Red,
		Green,
	};
	Tank
	(
		int camp,
		int x, int y,
		MOVE gesture,
		ACL_Color brushColor,
		ACL_Color penColor
	);
	void paint_score();
	void Fire();
	virtual bool collide_check(GameObject* obj, GOTYPE type)override;
	virtual void draw()override;
	virtual void Receive(MESSAGE message)override;
	bool ifFire();
	void keyevent(int key, int event);
	void setkey(int forward_key, int backward_key, int left_key, int right_key, int fire_key);
	void clearbullet();
	void restart();

	template<typename... Args>
	void check_booms(Game* game, GameObject* arg, Args... args);
	void check_booms(Game* game) {}

	template<typename... Args>
	void tick(Game* game, GameObject* arg, Args... args);

	void up()
	{
		if (gety() >= 10)
		{
			sety(gety() - 10);
			p_y = p_y - 10;
		}
	}
	void down()
	{
		if (gety() <= y_edge - edge)
		{
			sety(gety() + 10);
			p_y = p_y + 10;
		}
	}
	void left()
	{
		if (getx() >= 10)
		{
			setx(getx() - 10);
			p_x = p_x - 10;
		}
	}
	void right()
	{
		if (getx() <= x_edge - edge)
		{
			setx(getx() + 10);
			p_x = p_x + 10;
		}
	}
};

template<typename... Args>
void Tank::check_booms(Game* game, GameObject* arg, Args... args)
{
	for (int i = 0; i < 5; i++)
	{
		if (!booms[i]) continue;
		if (arg->getifdraw() && booms[i]->collide_check(arg, arg->type))
		{
			game->add_boom(booms[i]->getx(), booms[i]->gety());
			switch(arg->type)
			{
			case GameObject::TANK:
				Send(Messager::HITYOU, arg);
				break;
			case GameObject::TARGET:
				Send(Messager::RESTART, arg, args...);
				pts++;
				break;
			}
			delete booms[i];
			booms[i] = nullptr;
			continue;
		}
		if (booms[i]->hit_edge())
		{
			switch (booms[i]->getgst())
			{
			case FORWARD:
				game->add_boom(booms[i]->getx(), booms[i]->gety() + 20);
				break;
			case BACKWARD:
				game->add_boom(booms[i]->getx(), booms[i]->gety() - 20);
				break;
			case LEFT:
				game->add_boom(booms[i]->getx() + 20 , booms[i]->gety());
				break;
			case RIGHT:
				game->add_boom(booms[i]->getx() - 20 , booms[i]->gety());
				break;
			}
			delete booms[i];
			booms[i] = nullptr;
		}
	}
	check_booms(game, args...);
}

template<typename... Args>
void Tank::tick(Game* game, GameObject* arg, Args... args)
{
	if(ifpaintscore) paint_score();
	if (getifdraw()) draw();
	if (hot_index < 100) hot_index++;
	check_booms(game, arg, args...);
	if (pts == 10)
	{
		pts = 0;
		if (camp == Red) Send(Messager::REDWIN, game);
		if (camp == Green) Send(Messager::GREENWIN, game);
		Send(Messager::EXPLODE, arg, args...);
		Receive(Messager::EXPLODE);
	}
	for (int i = 0; i < 5; i++)
	{
		if (!booms[i]) continue;
		booms[i]->tick();
	}
}

#endif