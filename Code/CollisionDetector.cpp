#include "CollisionDetector.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

void CollisonDetector::BeginContact(b2Contact* contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	Sprite2D* spriteA = (Sprite2D*)bodyA->GetUserData();
	Sprite2D* spriteB = (Sprite2D*)bodyB->GetUserData();

	if (spriteA && spriteB){
		/**contact event**/

	}
	return;
}


