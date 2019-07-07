#ifndef __Player_H__
#define __Player_H__
#include "Plane.h"

class Player:public Plane
{
public:
	Player();
	~Player();
	CREATE_FUNC(Player);
	bool init();

	void revive();//重生
	virtual void onDead();
};
#endif