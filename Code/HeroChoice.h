

#ifndef _CHOICE_HERO_H

#define _CHOICE_HERO_H
#include "cocos2d.h"
#include "EnumClass.h"

class HeroChoice : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(HeroChoice);
	static cocos2d::Scene* scene();
	void clickDownAction(typeNum _type);
	void update();
private:
	
	
};

#endif