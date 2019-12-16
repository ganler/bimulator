

#ifndef _COLLISION_HERO_H

#define _COLLISION_HERO_H
#include "cocos2d.h"
#include "Sprite2D.h"
#include "Box2D/Box2D.h"


class CollisonDetector : public b2ContactListener
{
public:
	virtual void BeginContact(b2Contact* contact);
	//virtual void EndContact(b2Contact* contact);
	//virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	//virtual void EndContact(b2Contact* contact);
};
#endif