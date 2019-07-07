#ifndef __PanelLayer_H__
#define __PanelLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class PanelLayer:public Layer
{
private:
	LabelBMFont*m_pScoreLabel;
	LabelBMFont*m_pLifeLabel;
	LabelBMFont*m_pBulletLabel;
	LabelBMFont*m_pSpeedLabel;
public:
	PanelLayer();
	~PanelLayer();
	CREATE_FUNC(PanelLayer);
	bool init();
private:
	void updateDynamicData(EventCustom*custom);
	void updatePlayer(EventCustom*custom);
};
#endif