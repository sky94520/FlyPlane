#ifndef __ShootingDelegate_H__
#define __ShootingDelegate_H__

class Plane;
enum BulletType;
class ShootingDelegate
{
public:
	virtual void shooting(Plane*plane,BulletType type)=0;
};
#endif