#ifndef __EnemyState_H__
#define __EnemyState_H__

class Plane;
class EnemyStateFSM;

class EnemyState
{
protected:
	EnemyStateFSM*m_pFSM;
	EnemyState(EnemyStateFSM*fsm):m_pFSM(fsm){}
public:
	virtual ~EnemyState(){}
	virtual void chase(Plane*enemy,Plane*player)=0;//追击
	virtual void flee(Plane*enemy,Plane*player)=0;//逃跑
	virtual void shoot(Plane*enemy,Plane*player)=0;//射击
};
//--------------------ChaseState------------------------------------
class ChaseState:public EnemyState
{
public:
	ChaseState(EnemyStateFSM*fsm);
	virtual void chase(Plane*enemy,Plane*player);
	virtual void flee(Plane*enemy,Plane*player);
	virtual void shoot(Plane*enemy,Plane*player);
};
//--------------------FleeState------------------------------------
class FleeState:public EnemyState
{
public:
	FleeState(EnemyStateFSM*fsm);
	virtual void chase(Plane*enemy,Plane*player);
	virtual void flee(Plane*enemy,Plane*player);
	virtual void shoot(Plane*enemy,Plane*player);
};
//--------------------ShootState------------------------------------
class ShootState:public EnemyState
{
public:
	ShootState(EnemyStateFSM*fsm);
	virtual void chase(Plane*enemy,Plane*player);
	virtual void flee(Plane*enemy,Plane*player);
	virtual void shoot(Plane*enemy,Plane*player);
};
#endif