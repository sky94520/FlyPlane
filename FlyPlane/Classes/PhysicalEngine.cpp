#include "PhysicalEngine.h"
#include "DebugDraw.h"
#include "PhysicalDrawNode.h"

NS_SDL_BEGIN
PhysicalEngine*PhysicalEngine::m_pInstance = nullptr;
const int PhysicalEngine::PTM_RATIO = 32;

PhysicalEngine::PhysicalEngine()
	:m_pWorld(nullptr),m_pDebugDraw(nullptr),m_bDebug(true)
{
}
PhysicalEngine::~PhysicalEngine()
{
	SDL_SAFE_DELETE(m_pDebugDraw);
	SDL_SAFE_DELETE(m_pWorld);
}
PhysicalEngine*PhysicalEngine::getInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new PhysicalEngine();
		m_pInstance->initPhysicalWorld();
	}
	return m_pInstance;
}
void PhysicalEngine::purge()
{
	SDL_SAFE_DELETE(m_pInstance);
}
bool PhysicalEngine::initPhysicalWorld()
{
	b2Vec2 gravity(0.f,0.f);
	//创建物理世界
	m_pWorld = new b2World(gravity);
	m_pWorld->SetAllowSleeping(true);//允许休眠
	m_pWorld->SetContinuousPhysics(true);//连续物理测试
	//开启调试
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	//flags += b2Draw::e_jointBit;
	//flags += b2Draw::e_aabbBit;
	//flags += b2Draw::e_pairBit;
	//flags += b2Draw::e_centerOfMassBit;
	m_pDebugDraw = new DebugDraw(flags, PTM_RATIO);
	m_pWorld->SetDebugDraw(m_pDebugDraw);

	//m_pDebugDraw->SetFlags(flags);
	return true;
}
b2Body*PhysicalEngine::createBody(const b2BodyDef*def)
{
	return m_pWorld->CreateBody(def);
}
void PhysicalEngine::destroyBody(b2Body*body)
{
	m_pWorld->DestroyBody(body);
}
void PhysicalEngine::setGravity(const b2Vec2& gravity)
{
	m_pWorld->SetGravity(gravity);
}
b2Vec2 PhysicalEngine::getGravity() const
{
	return m_pWorld->GetGravity();
}
void PhysicalEngine::step(float32 dt, int32 velocityIterations, int32 positionIterations)
{
	m_pWorld->Step(dt,velocityIterations,positionIterations);
}
void PhysicalEngine::setContactListener(b2ContactListener*listener)
{
	m_pWorld->SetContactListener(listener);
}
void PhysicalEngine::drawDebugData()
{
	m_pWorld->DrawDebugData();
}
void PhysicalEngine::setDebugDrawFlags(uint32 flags)
{
	m_pDebugDraw->SetFlags(flags);
}
uint32 PhysicalEngine::getDebugDrawFlags()const
{
	return m_pDebugDraw->GetFlags();
}
void PhysicalEngine::appendDebugDrawFlags(uint32 flags)
{
	m_pDebugDraw->AppendFlags(flags);
}
void PhysicalEngine::clearDebugDrawFlags(uint32 flags)
{
	m_pDebugDraw->ClearFlags(flags);
}
b2Body*PhysicalEngine::getBodyList()const
{
	return m_pWorld->GetBodyList();
}
b2Body*PhysicalEngine::createEdge(const Point&pos1,const Point&pos2,b2BodyType type)
{
	b2Vec2 v1 = b2Vec2(pos1.getX()/PTM_RATIO,pos1.getY()/PTM_RATIO);
	b2Vec2 v2 = b2Vec2(pos2.getX()/PTM_RATIO,pos2.getY()/PTM_RATIO);
	//创建body
	b2BodyDef bodyDef;
	bodyDef.type = type;

	b2Body*body = m_pWorld->CreateBody(&bodyDef);
	b2EdgeShape shape;
	shape.Set(v1,v2);

	body->CreateFixture(&shape,1.f);
	return body;
}
b2Body*PhysicalEngine::createBox(const Size&size,b2BodyType type)
{
	float32 wx = size.width/PTM_RATIO/2;
	float32 hx = size.height/PTM_RATIO/2;

	b2BodyDef bodyDef;
	bodyDef.type = type;

	b2Body*body = m_pWorld->CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(wx,hx);

	body->CreateFixture(&shape,1.f);
	return body;
}

PhysicalDrawNode*PhysicalEngine::getDrawNode()
{
	return PhysicalDrawNode::create(m_pWorld, PTM_RATIO);
}
NS_SDL_END