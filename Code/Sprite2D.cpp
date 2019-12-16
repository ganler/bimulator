#include "Sprite2D.h"

USING_NS_CC;
Sprite2D::Sprite2D(b2World* game, int type) {
	setGame(game);
	setType(type);
}

void Sprite2D::setSpritePosition(Vec2 position) {
	setPosition(position);

	if (getBody()) {
		getBody()->SetTransform(b2Vec2(
			position.x / PTM_RATIO,
			position.y / PTM_RATIO),
			getBody()->GetAngle());
	}
}

void Sprite2D::update(float dt) {

	if (getBody()) {
		setPosition(getBody()->GetPosition().x * PTM_RATIO, getBody()->GetPosition().y * PTM_RATIO);
		//setRotation(CC_RADIANS_TO_DEGREES(-1 * _body->GetAngle()));
	}
}

void Sprite2D::reset() {
	if (getBody()) {
		getBody()->SetLinearVelocity(b2Vec2_zero);
		getBody()->SetAngularVelocity(0);
		getBody()->SetAwake(true);
	}
	return;
}

