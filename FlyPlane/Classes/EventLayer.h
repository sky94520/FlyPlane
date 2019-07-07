#ifndef __EventLayer_H__
#define __EventLayer_H__

#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;

class OperateDelegate;

class EventLayer:public Layer
{
public:
	EventLayer();
	~EventLayer();
	CREATE_FUNC(EventLayer);
	bool init();
	virtual void update(float dt);

	void setDelegate(OperateDelegate*pDelegate);

	virtual void onKeyPressed(SDL_Keycode,SDL_Event*);
	virtual void onKeyReleased(SDL_Keycode,SDL_Event*);
private:
	OperateDelegate* m_pDelegate;
	bool m_bRightPressed;
	bool m_bLeftPressed;
};
#endif