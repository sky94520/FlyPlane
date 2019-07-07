#ifndef __PhysicalEngine_H__
#define __PhysicalEngine_H__

#include<vector>

#include "SDL_Engine/SDL_Engine.h"

#include "Box2D/Box2D.h"
NS_SDL_BEGIN

class PhysicalDrawNode;

class PhysicalEngine:public Object
{
private:
	static PhysicalEngine*m_pInstance;

	b2World*m_pWorld;
	b2Draw*m_pDebugDraw;
	SDL_BOOL_SYNTHESIZE(m_bDebug,Debug);//是否开启调试 默认为true
public:
	static const int PTM_RATIO;
public:
	PhysicalEngine();
	~PhysicalEngine();
	static PhysicalEngine*getInstance();
	static void purge();
	//简单封装了box2d的部分函数
	//创建一个刚体
	b2Body*createBody(const b2BodyDef*def);
	void destroyBody(b2Body*body);
	//设置重力
	void setGravity(const b2Vec2& gravity);
	///获取重力
	b2Vec2 getGravity() const;
	//时间步
	void step(float32 dt, int32 velocityIterations, int32 positionIterations);
	//设置监听事件
	void setContactListener(b2ContactListener*listener);
	//显示调试内容
	void drawDebugData();
	//设置调试视图绘制选项
	void setDebugDrawFlags(uint32 flags);
	uint32 getDebugDrawFlags()const;
	//追加调试绘图选项
	void appendDebugDrawFlags(uint32 flags);
	//从当前调试绘图选项中删除指定
	void clearDebugDrawFlags(uint32 flags);
	//获取刚体
	b2Body*getBodyList()const;
	//创建b2EdgeShape 无法旋转，线段之间不会碰撞
	b2Body*createEdge(const Point&pos1,const Point&pos2,b2BodyType type);
	b2Body*createBox(const Size&size,b2BodyType type);

	//获取调试绘制节点
	PhysicalDrawNode*getDrawNode();

	b2World*getWorld()const
	{
		return m_pWorld;
	}
private:
	//初始化物理世界
	bool initPhysicalWorld();
};
NS_SDL_END
#endif