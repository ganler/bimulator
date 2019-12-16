#ifndef __BILLARDBALL_
#define __BILLARDBALL_

#include "Sprite2D.h"
#include "Box2D\Box2D.h"

class BillardBall : public Sprite2D {
public:
	CC_SYNTHESIZE(bool, _select, Select);
	CC_SYNTHESIZE(bool, _die, Die);
	~BillardBall();
	BillardBall(b2World* game, int type, Vec2 position, int color);
	static BillardBall* create(b2World* game, int type, Vec2 position, int color);
	bool init();
	void reset();
	void die();
	void update(float delta);
	
private:
	Vec2 _startPosition;
	int _color;
	Vec3 _rotateVector;
	float _rotateAngle;
};


#endif