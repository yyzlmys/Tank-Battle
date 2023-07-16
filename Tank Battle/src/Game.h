#pragma once
#ifndef _GAME_H_
#define _GAME_H_

#include "acllib.h"
#include"Messager.h"
#include<vector>

constexpr int pit = 10;
constexpr int x_edge = 910;
constexpr int y_edge = 630;
constexpr int roll = 25;
constexpr int edge = 60;
constexpr int hit_t = 20;

class Game :public Messager
{
	struct explode_animation
	{
		int x; int y;
		int time = 20;
		bool ifplaySound = false;
		explode_animation(int x, int y)
		{
			this->x = x; this->y = y;
		}
	};
	std::vector<explode_animation*> explode_animations = std::vector<explode_animation*>(5, nullptr);
	static enum STATE
	{
		BEGIN1,
		BEGIN2,
		BEGIN3,
		IFTEACH,
		TEACH,
		PLAYING,
		RED_WIN,
		GREEN_WIN,
	};
	ACL_Sound begin;
	ACL_Sound teach_s;
	ACL_Sound playing;
	ACL_Sound win;
	ACL_Sound explode_s;
	ACL_Image explode_i;
	ACL_Image heng;
	ACL_Image sponsor;
	ACL_Image background2;
	ACL_Image shu;
	ACL_Image background;
	ACL_Image redwin;
	ACL_Image greenwin;
	ACL_Image teach_i;
	ACL_Image preface;
	ACL_Image cdpr;
	ACL_Image title;
	STATE state = BEGIN1;
	int time = 0;
	int teach_key; int skip_key;
	int continue_key; int restart_key;
	bool ifsend = false;
	HWND hbutton;
	bool ifplay = true;
public:
	void music_button();
	void add_boom(int x, int y);
	void paint_boom();
	void setkey(int teach_key, int skip_key, int continue_key, int restart_key);
	void init();
	void loadscene();
	virtual void Receive(Messager::MESSAGE message)override;
	void keyevent(int key, int event);

	template<typename ...Args>
	void tick(Messager* arg, Args... args);
};

template<typename ...Args>
void Game::tick(Messager* arg, Args... args)
{
	loadscene();
	paint_boom();
	if (!ifsend && state == PLAYING)
	{
		Send(Messager::RESTART, arg, args...);
		Receive(RESTART);
		ifsend = true;
	}
	if (time == -1) return;
	if (time == 0)
	{
		time++;
		state = BEGIN1;
		Send(Messager::EXPLODE, arg, args...);
		playSound(begin, 0);
		return;
	}
	if (time < 300)
	{
		time++;
		return;
	}
	if (time == 300)
	{
		state = BEGIN2;
		time++;
		return;
	}
	if (time < 600)
	{
		time++;
		return;
	}
	if (time == 600)
	{
		state = BEGIN3;
		time++;
		return;
	}
	if (time < 950)
	{
		time++;
		return;
	}
	if (time == 950)
	{
		playSound(teach_s, 0);
		Keymanager.Register(&Game::keyevent, this);
		state = IFTEACH;
		time = -1;
	}
}

#endif