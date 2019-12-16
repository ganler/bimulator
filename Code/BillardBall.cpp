#include "BillardBall.h"
#include "SimpleAudioEngine.h"
#include "cmath"
#include "ctime"
#include "GlobalVar.h"
USING_NS_CC;

BillardBall::~BillardBall() {

}

BillardBall::BillardBall(b2World* game, int type, Vec2 position, int color) :Sprite2D(game, type) {

	_startPosition = position;
	_color = color;
	setSelect(false);
	setDie(false);
	_rotateVector = Vec3(0.0f, 0.0f, 0.0f);	
	_rotateAngle = 0.0f;

}

BillardBall* BillardBall::create(b2World* game, int type, Vec2 position, int color) {
	BillardBall* sprite = new BillardBall(game, type, position, color);
	if (sprite) {
		sprite->init();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

bool BillardBall::init() {
	if (!Sprite::init()){
		return false;
	}
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	setBody(getGame()->CreateBody(&bodyDef));
	getBody()->SetSleepingAllowed(true);
	getBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	if (nowHero == 1 || nowHero == 3) {
		getBody()->SetLinearDamping(0.4f);
		getBody()->SetAngularDamping(0.4f);
	}
	else{
		getBody()->SetLinearDamping(0.0f);
		getBody()->SetAngularDamping(0.0f);
	}
	b2CircleShape circle;
	circle.m_radius = BALL_RADIUS / PTM_RATIO;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 15;
	fixtureDef.restitution = 1.0;
	fixtureDef.isSensor = false;
	if (nowHero == 1 || nowHero == 3)
		fixtureDef.friction = 0.01;
	else
		fixtureDef.friction = 0.0f;
	getBody()->SetBullet(true);
	initWithFile("Sprite1.png");
	setScale(0.6f);
	setVisible(false);
	getBody()->CreateFixture(&fixtureDef);
	getBody()->SetUserData(this);

	setSpritePosition(_startPosition);
}

void BillardBall::reset() {
	if (getBody()) {
		getBody()->SetLinearVelocity(b2Vec2_zero);
		getBody()->SetAngularVelocity(0);
		getBody()->SetAwake(true);
	}
	setSpritePosition(_startPosition);
	setSelect(false);
	setVisible(false);
}

void BillardBall::die()
{
	if (getBody()) {
		b2World* _pWorld = getGame();
		_pWorld->DestroyBody(getBody());
	}
	setDie(true);
	return;
}
void BillardBall::update(float delta) {
	if (getBody()) {
		setPosition(Vec2(getBody()->GetPosition().x * PTM_RATIO, getBody()->GetPosition().y * PTM_RATIO));
		setRotation(CC_RADIANS_TO_DEGREES(-1 * _body->GetAngle()));
		b2Vec2 VelTo = getBody()->GetLinearVelocity();
		_rotateVector = Vec3(VelTo.y, VelTo.x, 0.0f)/VelTo.Length();
		_rotateAngle = VelTo.Length() / BALL_RADIUS;
	}
	return;
}