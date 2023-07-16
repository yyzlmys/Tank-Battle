#include"Game.h"
#include"acllib.h"
#include"GameObject.h"

GameObject::GameObject(int x, int y, MOVE gesture, ACL_Color brushcolor, ACL_Color pencolor)
{
	this->x = x; this->y = y; this->gesture = gesture;
	this->brushcolor = brushcolor; this->pencolor = pencolor;
}
