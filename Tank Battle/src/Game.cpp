#include"Game.h"
#include"acllib.h"
#include"Messager.h"
#include<functional>

void Game::init()
{
	initWindow("Ì¹¿Ë´óÕ½", 0, 0, 1300, 900);
	loadSound("music/begin.mp3", &begin);
	loadSound("music/playing.mp3", &playing);
	loadSound("music/teach.mp3", &teach_s); 
	loadSound("music/win.mp3", &win);
	loadImage("images/heng.jpg", &heng);
	loadImage("images/shu.jpg", &shu);
	loadImage("images/sponsor.jpg", &sponsor);
	loadImage("images/background.jpg", &background);
	loadImage("images/background2.jpg", &background2);
	loadImage("images/greenwin.jpg", &greenwin);
	loadImage("images/redwin.jpg", &redwin);
	loadImage("images/preface.jpg", &preface);
	loadImage("images/teach.jpg", &teach_i);
	loadImage("images/title.jpg", &title);
	loadImage("images/cdpr.jpg", &cdpr);
	loadImage("images/explode.jpg", &explode_i);
	loadSound("music/explode.mp3", &explode_s);
	buttonfunc = std::bind(&Game::music_button, this);
}

void Game::loadscene()
{
	switch (state)
	{
	case PLAYING:
		putImageScale(&background2, 0, 0, 1300, 900);
		putImageScale(&heng, 0, y_edge, x_edge, 10);
		putImageScale(&shu, x_edge, 0, 10, y_edge + 10);
		putImageScale(&background, 0, 0, x_edge, y_edge);
		break;
	case BEGIN1:
		putImageScale(&cdpr, 0, 0, 1300, 900);
		break;
	case BEGIN3	:
		putImageScale(&title, 0, 0, 1300, 900); 
		break;
	case BEGIN2:
		putImageScale(&sponsor, 0, 0, 1300, 900);
		break;
	case RED_WIN:
		putImageScale(&redwin, 0, 0, 1300, 900);
		break;
	case GREEN_WIN:
		putImageScale(&greenwin, 0, 0, 1300, 900);
		break;
	case IFTEACH:
		putImageScale(&preface, 0, 0, 1300, 900);
		break;
	case TEACH:
		putImageScale(&teach_i, 0, 0, 1300, 900);
		break;
	}
	
}

void Game::Receive(Messager::MESSAGE message)
{
	switch (message)
	{
	case REDWIN:
		DestroyWindow(hbutton);
		state = RED_WIN;
		stopSound(playing);
		playSound(win, 0);
		Keymanager.Register(&Game::keyevent, this);
		break;
	case GREENWIN:
		DestroyWindow(hbutton);
		state = GREEN_WIN;
		stopSound(playing);
		playSound(win, 0);
		Keymanager.Register(&Game::keyevent, this);
		break;
	case RESTART:
		stopSound(teach_s);
		stopSound(win);
		hbutton = CreateWindow("BUTTON", "Play/Stop Music", WS_VISIBLE | WS_CHILD,
			1093, 100, 130, 40, g_hWnd, (HMENU)1, nullptr, NULL);
		playSound(playing, 10);
		break;
	}
}

void Game::keyevent(int key, int event)
{
	if (event == 0)
	{
		if (key == skip_key)
		{
			if (state == IFTEACH)
			{
				state = PLAYING;
				Keymanager.Cancel(this);
				return;
			}
		}
		if (key == teach_key)
		{
			if (state == IFTEACH)
			{
				state = TEACH;
				return;
			}
		}
		if (key == continue_key)
		{
			if (state == TEACH)
			{
				state = PLAYING;
				Keymanager.Cancel(this);
				return;
			}
		}
		if (key == restart_key)
		{
			if (state == RED_WIN || state == GREEN_WIN)
			{
				state = PLAYING;
				ifsend = false;
				return;
			}
		}
	}
}

void Game::setkey(int teach_key, int skip_key, int continue_key, int restart_key)
{
	this->teach_key = teach_key; this->skip_key = skip_key;
	this->continue_key = continue_key; this->restart_key = restart_key;
}

void Game::add_boom(int x, int y)
{
	for (int i = 0; i < 5; i++)
	{
		if (explode_animations[i]) continue;
		explode_animations[i] = new explode_animation(x, y);
		return;
	}
}

void Game::paint_boom()
{
	for (int i = 0; i < 5; i++)
	{
		if (!explode_animations[i]) continue;
		if (!explode_animations[i]->time)
		{
			delete explode_animations[i];
			explode_animations[i] = nullptr;
			continue;
		}
		if (!explode_animations[i]->ifplaySound)
		{
			playSound(explode_s, 0);
			explode_animations[i]->ifplaySound = true;
		}
		putImageScale(&explode_i, explode_animations[i]->x - 20, explode_animations[i]->y - 20, 40, 40);
		explode_animations[i]->time--;
	}
}

void Game::music_button()
{
	if (ifplay)
	{
		stopSound(playing);
		ifplay = false;
	}
	else
	{
		playSound(playing, 10);
		ifplay = true;
	}
}