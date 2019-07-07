#include "PlayerLayer.h"
#include "GameScene.h"
#include "FlyBehavior.h"
#include "Player.h"
#include "DynamicData.h"

const string PlayerLayer::GAME_OVER = "game over";

PlayerLayer::PlayerLayer()
	:m_pPlayer(nullptr),m_pDelegate(nullptr)
	,m_bAdjustPos(false),m_endAngle(0.f)
{
}
PlayerLayer::~PlayerLayer()
{
}
bool PlayerLayer::init()
{

	m_pPlayer = Player::create();

	//设置颜色
	m_pPlayer->getSprite()->setColorMod(0,255,255);
	//设置飞行
	m_pPlayer->setFlyBehavior(new SteadyFly());
	//设置发射子弹
	m_pPlayer->setBulletNum(2);
	//m_pPlayer->setDelegate(this);
	//设置相应参数
	this->playerRevive();

	this->addChild(m_pPlayer);
	//绑定刚体
	this->bindPhysicalPlane(m_pPlayer);
	//设置主角子弹属性
	b2Filter bulletFilter;
	bulletFilter.maskBits = GameScene::PLAYER_BULLET_MASKBIT;
	bulletFilter.categoryBits = GameScene::ENEMY_MASKBIT | GameScene::BORDER_MASKBIT | GameScene::ENEMY_BULLET_MASKBIT;

	m_pPlayer->setBulletFilter(bulletFilter);

	return true;
}
void PlayerLayer::update(float dt)
{
	//判断是否可以重生
	if(m_pPlayer->isAlive() == false)
	{
		int life = DynamicData::getInstance()->getLife();
		//游戏结束
		if (life <= 0)
		{
			_eventDispatcher->dispatchCustomEvent(GAME_OVER, m_pPlayer);
		}
		else
		{
			DynamicData::getInstance()->alterLife(-1);//生命减一
			m_pPlayer->revive();//重生
			this->playerRevive();
		}
	}
	//角色死亡，不再接收按键
	if(m_pPlayer->isDead())
		return;
	//需要调整位置
	/*if(m_bAdjustPos)
	{
		float curAngle = m_pPlayer->getSprite()->getRotation();
		if(m_endAngle > curAngle)
		{
			curAngle += 5;
			if(curAngle > m_endAngle)
				m_bAdjustPos = false;
		}
		else
		{
			curAngle -= 5;
			if(curAngle < m_endAngle)
				m_bAdjustPos = false;
		}
		m_pPlayer->getSprite()->setRotation(curAngle);
	}*/
	m_pPlayer->update(dt);
	//每次更新都更新信息
	_eventDispatcher->dispatchCustomEvent("player",m_pPlayer);
}

void PlayerLayer::rotationOfPlayer(float angle, bool delta)
{
	if (delta)
		m_pPlayer->rotateBy(angle);
	else
		m_pPlayer->rotateTo(angle);
}

void PlayerLayer::changeSpeedOfPlayer(float speed, bool delta)
{
	float newSpeed = speed;
	if (delta)
	{
		newSpeed += m_pPlayer->getCurSpeed();
		//限定最小速度和最大速度
		if (newSpeed <= 0.f)
			newSpeed = 1.f;
		else if (newSpeed > 3.f)
			newSpeed = 3.f;
	}
	m_pPlayer->setCurSpeed(newSpeed);
}

void PlayerLayer::wantToShoot()
{
	m_pPlayer->shoot();
}

void PlayerLayer::bindPhysicalPlane(Plane*plane)
{
	b2Body*body = PhysicalEngine::getInstance()->createBox(plane->getContentSize(),b2_dynamicBody);
	b2Fixture*fixture = body->GetFixtureList();
	b2Filter filter;

	filter.maskBits = GameScene::PLAYER_MASKBIT;
	filter.categoryBits = GameScene::ENEMY_MASKBIT | GameScene::ENEMY_BULLET_MASKBIT | GameScene::BORDER_MASKBIT;

	fixture->SetFilterData(filter);
	body->ResetMassData();
	//互相保留对方的引用
	body->SetUserData(plane);
	plane->setUserData(body);
	//为该body设置初始速度
	/*body->SetLinearVelocity(b2Vec2(0,-1));
	//无阻尼
	body->SetLinearDamping(0.f);*/
}

 Plane* PlayerLayer::getPlayer()const
{
	return m_pPlayer;
}

void PlayerLayer::setDelegate(ShootingDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
	m_pPlayer->setDelegate(pDelegate);
}

void PlayerLayer::reset()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size size = m_pPlayer->getContentSize();

	//设置相应参数
	m_pPlayer->setCurSpeed(1.f);
	//
	m_pPlayer->setCurHp(1);
	m_pPlayer->setMaxHp(1);
	m_pPlayer->setAtk(1);
	m_pPlayer->setAlive(true);
	m_pPlayer->setVisible(true);
	m_pPlayer->setBulletNum(2);
	m_pPlayer->getSprite()->setRotation(-90.f);
	m_pPlayer->setPosition(visibleSize.width/2,visibleSize.height - size.height);
}
void PlayerLayer::playerRevive()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size size = m_pPlayer->getContentSize();

	//设置相应参数
	m_pPlayer->setCurSpeed(1.f);
	//
	m_pPlayer->setCurHp(1);
	m_pPlayer->setMaxHp(1);
	m_pPlayer->setAtk(1);
	m_pPlayer->setAlive(true);
	m_pPlayer->setVisible(true);
	m_pPlayer->getSprite()->setRotation(-90.f);
	m_pPlayer->setPosition(visibleSize.width/2,visibleSize.height - size.height);
}
