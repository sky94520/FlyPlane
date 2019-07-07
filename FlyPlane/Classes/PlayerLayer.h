#ifndef __PlayerLayer_H__
#define __PlayerLayer_H__
#include "SDL_Engine/SDL_Engine.h"
#include "Plane.h"

using namespace SDL;
class Player;

class PlayerLayer:public Layer
{
public:
	PlayerLayer();
	~PlayerLayer();
	CREATE_FUNC(PlayerLayer);
	bool init();
	virtual void update(float dt);
	//对主角进行操作
	void degreeUpdate(const Point& degree);
	void wantShooting();

	 Plane*getPlayer()const;
	 void setDelegate(ShootingDelegate* pDelegate);
	 void reset();
private:
	void playerRevive();//主角重生
	void bindPhysicalPlane(Plane* plane);
public:
	static const string GAME_OVER;
private:
	Player*m_pPlayer;
	bool m_bAdjustPos;//是否调整飞机位置
	float m_endAngle;
	ShootingDelegate*m_pDelegate;
};
#endif
