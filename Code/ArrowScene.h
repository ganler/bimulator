#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include <cstdio>
#include "cocos2d.h"

class arrowFight : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuStartCallBack(cocos2d::Ref* pSender);
	CREATE_FUNC(arrowFight);

};

#endif // __HELLOWORLD_SCENE_H__
