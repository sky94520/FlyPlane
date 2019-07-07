#ifndef __GameScene_H__
#define __GameScene_H__
#include "SDL_Engine/SDL_Engine.h"
#include "OperateLayer.h"
#include "BulletLayer.h"
#include "Plane.h"
#include "PlayerLayer.h"
#include "EnemyLayer.h"
#include "GameOverLayer.h"
#include "ShootingDelegate.h"

using namespace SDL;
class PanelLayer;

class GameScene:public Scene,public OperateDelegate,public ShootingDelegate
	,public GameOverDelegate
	,public b2ContactListener
{
public:
	static int PLAYER_MASKBIT;//主角
	static int PLAYER_BULLET_MASKBIT;//主角子弹
	static int ENEMY_MASKBIT;//敌机
	static int ENEMY_BULLET_MASKBIT;//敌机子弹
	static int BORDER_MASKBIT;//边界
private:
	Layer* m_pOperateLayer;
	PlayerLayer*m_pPlayerLayer;
	BulletLayer*m_pBulletLayer;
	EnemyLayer*m_pEnemyLayer;
	PanelLayer*m_pPanelLayer;
	GameOverLayer*m_pGameOverLayer;
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	bool init();

	virtual void update(float dt);
private:
	virtual void rotationOfPlayer(float angle, bool delta=false);
	virtual void changeSpeedOfPlayer(float speed, bool delta=false);
	virtual void wantToShoot();

	virtual void shooting(Plane*plane,BulletType type);
	virtual void gamePause();//游戏暂停
	virtual void gameResume();//游戏恢复
	void gameEnd(EventCustom* ec);//游戏结束
	virtual void gameRestart();//重新开始游戏

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
private:
	void initPhysicalWorld();
};
#endif
