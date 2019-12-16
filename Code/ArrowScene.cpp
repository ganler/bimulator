#include "ArrowScene.h"
#include "HeroChoice.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* arrowFight::createScene()
{
	return arrowFight::create();
}

// on "init" you need to initialize your instance
bool arrowFight::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*创建结束按钮*/
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(arrowFight::menuCloseCallback, this));

	float x = origin.x + visibleSize.width / 2;
	float y = origin.y + visibleSize.height * 1.0f / 4.0f;
	closeItem->setPosition(Vec2(x, y));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO); 
	this->addChild(menu, 1);

	/*创建开始按钮*/
	auto itemPlay = MenuItemImage::create(
		"StartNormal.png",
		"StartSelected.png",
		CC_CALLBACK_1(arrowFight::menuStartCallBack, this));

	x = origin.x + visibleSize.width / 2;
	y = origin.y + visibleSize.height * 1.0f / 2.0;
	itemPlay->setPosition(Vec2(x, y));
	itemPlay->setScaleX(0.5);
	itemPlay->setScaleY(0.5);
	auto pMenuPlay = Menu::create(itemPlay, NULL);
	pMenuPlay->setPosition(Vec2::ZERO);
	this->addChild(pMenuPlay, 1);


	/*创建背景*/
	auto pSprite = Sprite::create("BackGround1.jpg");
	pSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto pSize = pSprite->getContentSize();
	pSprite->setScaleX(visibleSize.width / pSize.width);
	pSprite->setScaleY(visibleSize.height / pSize.height);
	pSprite->setOpacity(200);
	this->addChild(pSprite, 0);

	/*创建标签*/
	auto label = Label::createWithTTF("Billards Simulation", "fonts/Marker Felt.ttf", 60);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);


	return true;
}


void arrowFight::menuCloseCallback(Ref * pSender)
{
	Director::getInstance()->end();
	return;
}
void arrowFight::menuStartCallBack(Ref* pSender)
{
	
	auto pScene = HeroChoice::scene();
	Director::getInstance()->pushScene(pScene);
	return;
}

