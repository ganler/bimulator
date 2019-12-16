#include "HeroChoice.h"
#include "Paddle.h"
#include "SimpleAudioEngine.h"
#include "NormalDefine.h"
#include "BillardScene.h"
#include "ctime"
USING_NS_CC;

int nowHero;
bool HeroChoice::init()
{
	if (!Layer::init())
	{
		return false;
	}
	srand((unsigned)time(NULL));
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto pSprite = Sprite::create("BackGroundHero.jpg");


	/*设置背景*/
	pSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto pSize = pSprite->getContentSize();
	pSprite->setScaleX(visibleSize.width / pSize.width);
	pSprite->setScaleY(visibleSize.height / pSize.height);
	pSprite->setOpacity(150);
	this->addChild(pSprite, 0);

	/*设置标题*/
	auto label0 = Label::createWithTTF("Hero Select", "fonts/Marker Felt.ttf", 60);
	label0->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label0->getContentSize().height));
	label0->setColor(Color3B(50, 10, 20));
	this->addChild(label0, 1);

	/*设置管卡选择按钮*/
	const char* chooseImage[3] = { "LeftArrow.jpg", "RightArrow.jpg",
		"MidArrow.jpg" };
	float fSettings[4][4] = {
		{ 50.0f / 1280, 45.0f / 720, 480.0f / 1280, 220.0f / 720 },
		{ 50.0f / 1280, 45.0f / 720, 800.0f / 1280, 220.0f / 720 },
		{ 50.0f / 1280, 45.0f / 720, 640.0f / 1280, 220.0f / 720 },
		{ 70.0f / 1280, 60.0f / 720, 740.0f / 1280, 150.0f / 320 }
	};

	typeNum evts[4] = { typeNum::left, typeNum::right, typeNum::mid, typeNum::text };
	for (int i = 0; i < 3; ++i)
	{
		float* fSetting = fSettings[i];
		auto paddleTexture = Director::getInstance()->getTextureCache()->addImage(chooseImage[i]);
		auto pPaddle = Paddle::paddleWithTexture(paddleTexture, evts[i]);
		Size szBtn = pPaddle->getContentSize();
		pPaddle->setParentScene(this);
		pPaddle->setScaleX(visibleSize.width / szBtn.width * fSetting[0]);
		pPaddle->setScaleY(visibleSize.height / szBtn.height * fSetting[1]);
		pPaddle->setPosition(Vec2(origin.x + visibleSize.width * fSetting[2], origin.y + visibleSize.height * fSetting[3]));
		pPaddle->mouseClickListener();
		this->addChild(pPaddle, 1);


	}

	/*设置Round*/
	nowHero = 1;
	auto labelRound = Label::createWithTTF("Hero:", "fonts/arial.ttf", 30);
	labelRound->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2.2 - labelRound->getContentSize().height));
	labelRound->setColor(Color3B(255, 255, 255));
	labelRound->enableShadow(Color4B::RED, Size(2, -2), 0.8);
	this->addChild(labelRound, 1);

	Sprite * spt = Sprite::create("Hero1.png");
	spt->setScale(1.2);
	spt->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 1.5));
	spt->setTag(999);
	this->addChild(spt, 0);
	/*服务器*/

	CCLOG("%s\n", "Create HereScene Successfully!");

	return true;
}

Scene * HeroChoice::scene()
{
	auto scene = Scene::create();
	auto layer = HeroChoice::create();

	if (scene && layer)
	{
		scene->addChild(layer);
	}
	return scene;
}

void HeroChoice::clickDownAction(typeNum _type)
{
	if (_type == typeNum::mid) {
		auto pScene = BillardScene::scene();
		Director::getInstance()->pushScene(pScene);
	}
	else if (_type == typeNum::left) {
		nowHero = (nowHero - 1 + ROUND - 1) % ROUND + 1;
		update();
	}
	else if (_type == typeNum::right) {
		nowHero = (nowHero + 1 + ROUND - 1) % ROUND + 1;
		update();
	}
	return;

}

void HeroChoice::update()
{
	Sprite* sp = (Sprite*)getChildByTag(999);
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("Hero" + std::to_string(nowHero) + ".png");
	sp->setTexture(texture);
	Rect tmp;
	tmp.size = texture->getContentSize();
	sp->setTextureRect(tmp);
	sp->setScale(1.2);
	return;
}