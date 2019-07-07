#include "PanelLayer.h"
#include "Player.h"
#include "DynamicData.h"

PanelLayer::PanelLayer()
	:m_pScoreLabel(nullptr),m_pLifeLabel(nullptr)
	,m_pBulletLabel(nullptr),m_pSpeedLabel(nullptr)
{
}
PanelLayer::~PanelLayer()
{
}
bool PanelLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//加载ui模块
	Node*node = ui::UIWidgetManager::getInstance()->createWidgetsWithXml("PanelLayer.xml");
	this->addChild(node);
	//获取组件
	m_pScoreLabel = node->getChildByName<LabelBMFont*>("score");
	m_pLifeLabel = node->getChildByName<LabelBMFont*>("life");
	m_pBulletLabel = node->getChildByName<LabelBMFont*>("bullet");
	m_pSpeedLabel = node->getChildByName<LabelBMFont*>("speed");
	//添加事件监听
	_eventDispatcher->addEventCustomListener("dynamic data",SDL_CALLBACK_1(PanelLayer::updateDynamicData,this),this);
	_eventDispatcher->addEventCustomListener("player",SDL_CALLBACK_1(PanelLayer::updatePlayer,this),this);
	return true;
}
void PanelLayer::updateDynamicData(EventCustom*custom)
{
	int life = DynamicData::getInstance()->getLife();
	int score = DynamicData::getInstance()->getScore();

	string text1 = StringUtils::format("生命：%d",life);
	string text2 = StringUtils::format("分数：%d",score);

	m_pLifeLabel->setString(text1);
	m_pScoreLabel->setString(text2);
}

void PanelLayer::updatePlayer(EventCustom*custom)
{
	auto player = static_cast<Player*>(custom->getUserData());
	int speed = player->getCurSpeed();
	int bullet = player->getBulletNum();
	//更新
	std::string text1 = StringUtils::format("速度：%d",speed);
	std::string text2 = StringUtils::format("子弹：%d",bullet);

	m_pSpeedLabel->setString(text1);
	m_pBulletLabel->setString(text2);
}