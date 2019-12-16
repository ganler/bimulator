#ifndef _BILLARD_HERO_H

#define _BILLARD_HERO_H

#include "map"
#include "cocos2d.h"
#include "EnumClass.h"
#include "NormalDefine.h"
#include "BillardBall.h"
#include "CollisionDetector.h"
#include "vector"

USING_NS_CC;


struct SightLine {
	Vec3 oriVector;
	Vec3 dirVector;
	SightLine(Vec3 _ori = Vec3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 30.0f), Vec3 _dir = Vec3(1.0f, 0.0f, 0.0f))
		:oriVector(_ori), dirVector(_dir) {}
	bool RayBallIntersection(const Vec3& centerPoint, float radius)
		
	{
		radius = radius * 1.2f;
		Vec3 oc = centerPoint - oriVector;
		if (oc.length() <= radius) {
			return true;
		}
		dirVector.normalize();
		const float proj = oc.dot(dirVector);
		if (proj <= 0) {
			return false;
		}
		const float distance2 = oc.dot(oc) - proj * proj;
		if (distance2 <= radius * radius) {
			return true;
		}
		else {
			return false;
		}
	}
	Vec3 RayPlaneIntersection(const Vec3& planePoint, Vec3 planeNormal)
	{
		planeNormal.normalize();
		const float t = (planeNormal.dot(planePoint) - planeNormal.dot(oriVector)) / planeNormal.dot(dirVector);
		return oriVector + t * oriVector;

	}
};

class BillardScene : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(BillardScene);
	static cocos2d::Scene* scene();

	void update(float delta);

	void billardSceneListener();

	void postDataInterface(std::vector<MyVec3>& billardPositon, std::vector<MyVec3>& rotateNormal, std::vector<float>& rotateAngle, MyVec3& rayPoint, MyVec3& rayDir, MyVec3& rayEnd);

private:
	BillardBall* _billbard[MAX_BALL];
	b2World* _world;
	CollisonDetector* _contactListener;
	SightLine _sightline;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	float _force;
};



#endif