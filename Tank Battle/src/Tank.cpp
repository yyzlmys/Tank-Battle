#include"Tank.h"
#include"Game.h"
#include"GameObject.h"
#include"Messager.h"
#include"acllib.h"
#include<string>

struct SHAPE tkshape[4] =
{
	{
		0,0,1,0,0,
		0,0,1,0,0,
		0,1,1,1,0,
		0,1,1,1,0,
		0,1,1,1,0,
		RIGHT,LEFT
	},
	{
		0,0,0,0,0,
		1,1,1,0,0,
		1,1,1,1,1,
		1,1,1,0,0,
		0,0,0,0,0,
		BACKWARD,FORWARD
	},
	{
		0,1,1,1,0,
		0,1,1,1,0,
		0,1,1,1,0,
		0,0,1,0,0,
		0,0,1,0,0,
		LEFT,RIGHT
	},
	{
		0,0,0,0,0,
		0,0,1,1,1,
		1,1,1,1,1,
		0,0,1,1,1,
		0,0,0,0,0,
		FORWARD,BACKWARD
	}
};

Tank::Tank(int camp, int x, int y, MOVE gesture, ACL_Color brushColor, ACL_Color penColor)
	:GameObject(x, y, gesture, brushColor, penColor)
{
	switch (gesture)
	{
	case FORWARD:
		p_x = x + 25;
		p_y = y;
		break;
	case BACKWARD:
		p_x = x + 25;
		p_y = y + 50;
		break;
	case LEFT:
		p_x = x;
		p_y = y + 25;
		break;
	case RIGHT:
		p_x = x + 50;
		p_y = y + 25;
		break;
	}
	x_start = x;
	y_start = y;
	p_x_start = p_x;
	p_y_start = p_y;
	gesture_start = gesture;
	this->type = GameObject::TANK;
	this->camp = camp;
}

void Tank::draw()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (tkshape[getgst()].shape[i][j])
			{
				setPenColor(getpencolor());
				setBrushColor(getbrushcolor());
				rectangle(getx() + j * pit, gety() + i * pit, getx() + (j + 1) * pit, gety() + (i + 1) * pit);
			}
		}
	}
}

void Tank::Receive(Messager::MESSAGE message)
{
	switch (message)
	{
	case RESTART:
		ifpaintscore = true;
		restart();
		break;
	case EXPLODE:
		Keymanager.Cancel(this);
		ifpaintscore = false;
		clearbullet();
		setifdraw(false);
		pts = 0;
		lastpos = new Lastpos(x_start, y_start, gesture_start, p_x_start, p_y_start);
		break;
	case HITYOU:
		Keymanager.Cancel(this);
		setifdraw(false);
		lastpos = new Lastpos(getx(), gety(), getgst(), p_x, p_y);
		break;
	}
}

void Tank::clearbullet()
{
	for (auto& boom : booms)
	{
		if (!boom) continue;
		delete boom;
		boom = nullptr;
	}
}

bool Tank::ifFire()
{
	if (hot_index > 50)
	{
		hot_index = 0;
		return true;
	}
	return false;
}

void Tank::keyevent(int key, int event)
{
	
	if (event == 0)
	{
		if (key == forward_key)
		{
			switch (getgst())
			{
			case FORWARD:
				up();
				break;
			case BACKWARD:
				down();
				break;
			case LEFT:
				left();
				break;
			case RIGHT:
				right();
				break;
			}
		}
		else if (key == backward_key)
		{
			switch (getgst())
			{
			case FORWARD:
				down();
				break;
			case BACKWARD:
				up();
				break;
			case LEFT:
				right();
				break;
			case RIGHT:
				left();
				break;
			}
		}
		else if (key == left_key)
		{
			switch (getgst())
			{
			case FORWARD:
				p_x = p_x - roll;
				p_y = p_y + roll;
				break;
			case BACKWARD:
				p_x = p_x + roll;
				p_y = p_y - roll;
				break;
			case LEFT:
				p_x = p_x + roll;
				p_y = p_y + roll;
				break;
			case RIGHT:
				p_x = p_x - roll;
				p_y = p_y - roll;
				break;
			}
			setgst(tkshape[getgst()].next2);
		}
		else if (key == right_key)
		{
			switch (getgst())
			{
			case FORWARD:
				p_x = p_x + roll;
				p_y = p_y + roll;
				break;
			case BACKWARD:
				p_x = p_x - roll;
				p_y = p_y - roll;
				break;
			case LEFT:
				p_x = p_x + roll;
				p_y = p_y - roll;
				break;
			case RIGHT:
				p_x = p_x - roll;
				p_y = p_y + roll;
				break;
			}
			setgst(tkshape[getgst()].next1);
		}
		else if (key == fire_key)
		{
			Fire();
		}
	}
}

void Tank::Fire()
{
	if (ifFire())
	{
		for (int i = 0; i < 5; i++)
		{
			if (booms[i]) continue;
			booms[i] = new Boom(p_x, p_y, getgst(), getbrushcolor(), getpencolor());
			break;
		}
	}
}

void Tank::setkey(int forward_key, int backward_key, int left_key, int right_key, int fire_key)
{
	this->forward_key = forward_key; this->backward_key = backward_key;
	this->left_key = left_key; this->right_key= right_key; this->fire_key = fire_key;
}

void Tank::restart()
{
	if (getifdraw()) return;
	setx(lastpos->x_last); sety(lastpos->y_last); setgst(lastpos->gesture_last);
	p_x = lastpos->p_x_last; p_y = lastpos->p_y_last; 
	clearbullet();
	Keymanager.Register(&Tank::keyevent, this);
	setifdraw(true);
}

bool Tank::collide_check(GameObject* obj, GOTYPE type) { return true; }

void Tank::paint_score()
{
	setTextColor(BLACK);
	setTextSize(20);
	switch (camp)
	{
	case Green:
		paintText(1100, 20, "绿方积分：");
		paintText(1200, 20, std::to_string(pts).c_str());
		break;
	case Red:
		paintText(1100, 40, "红方积分：");
		paintText(1200, 40, std::to_string(pts).c_str());
		break;
	}
}