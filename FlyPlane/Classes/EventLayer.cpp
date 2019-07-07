#include "EventLayer.h"
#include "OperateLayer.h"

EventLayer::EventLayer()
	:m_pDelegate(nullptr)
	,m_bLeftPressed(false)
	,m_bRightPressed(false)
{
}

EventLayer::~EventLayer()
{
}

bool EventLayer::init()
{
	//键盘事件监听
	EventListenerKeyboard*listener = EventListenerKeyboard::create();

	listener->onKeyPressed = SDL_CALLBACK_2(EventLayer::onKeyPressed,this);
	listener->onKeyReleased = SDL_CALLBACK_2(EventLayer::onKeyReleased,this);
	_eventDispatcher->addEventListener(listener,this);

	return true;
}

void EventLayer::setDelegate(OperateDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}

void EventLayer::update(float dt)
{
	if(m_bRightPressed)
	{
		m_pDelegate->rotationOfPlayer(5, true);
	}
	if(m_bLeftPressed)
	{
		m_pDelegate->rotationOfPlayer(-5, true);
	}
}

void EventLayer::onKeyPressed(SDL_Keycode keycode,SDL_Event*)
{
	if(keycode == SDLK_RIGHT)
	{
		m_bRightPressed = true;
		m_bLeftPressed = false;
	}
	else if(keycode == SDLK_LEFT)
	{
		m_bRightPressed = false;
		m_bLeftPressed = true;
	}
	else if(keycode == SDLK_UP)
	{
		m_pDelegate->changeSpeedOfPlayer(1, true);
	}
	else if(keycode == SDLK_DOWN)
	{
		m_pDelegate->changeSpeedOfPlayer(-1, true);
	}
	else if(keycode == SDLK_SPACE)
	{
		m_pDelegate->wantToShoot();
	}
}

void EventLayer::onKeyReleased(SDL_Keycode keycode,SDL_Event*)
{
	if(keycode == SDLK_RIGHT)
		m_bRightPressed = false;
	else if(keycode == SDLK_LEFT)
		m_bLeftPressed = false;
}
