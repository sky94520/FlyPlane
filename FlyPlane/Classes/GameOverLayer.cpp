﻿#include "GameOverLayer.h"
#include "DynamicData.h"

GameOverLayer::GameOverLayer()
	:m_pDelegate(nullptr)
{
}
GameOverLayer::~GameOverLayer()
{
}
bool GameOverLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//添加一个半灰色背景
	LayerColor*bg = LayerColor::create(Color4B(0,0,0,128));
	this->addChild(bg);
	//添加分数信息
	//LabelTTF*scoreLabel = LabelTTF::createWithWrapLine("Game Over",50,20);
	LabelBMFont* scoreLabel = LabelBMFont::create("游戏结束", "fonts/1.fnt", 200, Color3B(0, 0, 0));
	
	scoreLabel->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(scoreLabel);
	//添加重新开始按钮
	MenuItemLabel*restartBtn = MenuItemLabel::create(LabelBMFont::create("重新开始", "fonts/1.fnt", 200, Color3B(255, 255, 255)));
	restartBtn->setCallback(SDL_CALLBACK_1(GameOverLayer::gameRestart,this));
	restartBtn->setPosition(visibleSize.width/2,visibleSize.height/2 + scoreLabel->getContentSize().height);

	auto menu = Menu::create(restartBtn,nullptr);
	this->addChild(menu);

	return true;
}
void GameOverLayer::setDelegate(GameOverDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
void GameOverLayer::gameRestart(Object*sender)
{
	m_pDelegate->gameRestart();
}