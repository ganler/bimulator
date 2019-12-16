#ifndef __SPRITE2D__
#define __SPRITE2D__


#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "NormalDefine.h"

USING_NS_CC;

class Sprite2D : public Sprite {
public:
	Sprite2D(b2World* game, int type);

	CC_SYNTHESIZE(b2Body*, _body, Body);
	CC_SYNTHESIZE(b2World*, _game, Game);
	CC_SYNTHESIZE(int, _type, Type);

	virtual void setSpritePosition(Vec2 position);
	virtual void update(float dt);
	virtual void reset();
};



#endif