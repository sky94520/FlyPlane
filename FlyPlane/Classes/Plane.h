#ifndef __Plane_H__
#define __Plane_H__

#include "Box2D/Box2D.h"
#include "Entity.h"
#include "BulletFactory.h"

class ShootingDelegate;

class Plane:public Entity
{
public:
	Plane();
	~Plane();
	CREATE_FUNC(Plane);
	bool init();
	//发射子弹
	bool shoot();
	virtual void update(float dt);
	virtual void onDead();
	ShootingDelegate*getDelegate() const;
	void setDelegate(ShootingDelegate* pDelegate);

	SDL_SYNTHESIZE(b2Filter,m_bulletFilter,BulletFilter);//子弹碰撞属性
	SDL_SYNTHESIZE(int,m_nBulletNum,BulletNum);//一次能发射子弹的最大数目
private:
	ShootingDelegate*m_pDelegate;
};
#endif