#include "BillardScene.h"
#include "SimpleAudioEngine.h"
#include "NormalDefine.h"
#include "CollisionDetector.h"
#include "GlobalVar.h"
#include <cstdio>
#include "ray_tracing.h"
#include "OpenGLDraw.h"
USING_NS_CC;
cv::Mat view_global;
ray_tracing_controller rtc;
OpenGLDraw* openglLayer;
float ball_positions[10][3];
float camera_eye[3];
float camera_look_at[3];
float ball_rotateAngle[10];
float ball_rotateVec[10][3];
float sample_results[VIEW_ROW][VIEW_COL][3];
float shadow_factor[VIEW_ROW][VIEW_COL];
bool ball_selected[10];
bool ball_die[10];
Vec2 ball_hole[6];
bool BillardScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	_force = 0.0f;
	Size windowSize = Director::getInstance()->getVisibleSize();

	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);
	_world = new b2World(gravity);

	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);


	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	b2Body* groundBody = _world->CreateBody(&groundBodyDef);
	b2EdgeShape groundBox;

	//b2BodyDef中默认初始化为静态物体，所以这里我们不需要特意指定
	//不过下面的飞猪与子弹就需要指定了

	//bottom
	groundBox.Set(b2Vec2((windowSize.width - TABLE_WIDTH) / 2 / PTM_RATIO, (windowSize.height - TABLE_HEIGHT)/ 2 / PTM_RATIO), b2Vec2((windowSize.width + TABLE_WIDTH) / 2 / PTM_RATIO, (windowSize.height - TABLE_HEIGHT) / 2 / PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);

	//right
	groundBox.Set(b2Vec2((windowSize.width + TABLE_WIDTH) / 2 / PTM_RATIO, (windowSize.height - TABLE_HEIGHT) / 2 / PTM_RATIO), b2Vec2((windowSize.width + TABLE_WIDTH) / 2 / PTM_RATIO, (windowSize.height + TABLE_HEIGHT) / 2 / PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);

	//top
	groundBox.Set(b2Vec2((windowSize.width - TABLE_WIDTH) / 2 / PTM_RATIO, (windowSize.height + TABLE_HEIGHT) / 2 / PTM_RATIO), b2Vec2((windowSize.width + TABLE_WIDTH) / 2 / PTM_RATIO, (windowSize.height + TABLE_HEIGHT) / 2 / PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);

	//left
	groundBox.Set(b2Vec2((windowSize.width - TABLE_WIDTH) / 2 / PTM_RATIO, (windowSize.height - TABLE_HEIGHT) / 2 / PTM_RATIO), b2Vec2((windowSize.width - TABLE_WIDTH) / 2 / PTM_RATIO, (windowSize.height + TABLE_HEIGHT) / 2 / PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);

	for (int i = 0; i < MAX_BALL; ++i) {
		_billbard[i] = BillardBall::create(_world, 0, Vec2((windowSize.width - TABLE_WIDTH) / 2.0f + 0.08f * (i + 1) * TABLE_WIDTH, windowSize.height * 0.5f), i);
		this->addChild(_billbard[i]);
		ball_die[i] = false;
	}

	

	_contactListener = new CollisonDetector();
	_world->SetContactListener(_contactListener);

	scheduleUpdate();
	billardSceneListener();

	//srand(time(0));
	//cv::namedWindow("Billbard Windows", cv::WINDOW_KEEPRATIO | cv::WINDOW_NORMAL);
	//view_global = cv::Mat(VIEW_ROW, VIEW_COL, CV_8UC3);

	ball_hole[0] = Vec2((windowSize.width - TABLE_WIDTH) / 2.0, (windowSize.height + TABLE_HEIGHT) / 2.0);
	ball_hole[1] = Vec2((windowSize.width) / 2.0, (windowSize.height + TABLE_HEIGHT) / 2.0);
	ball_hole[2] = Vec2((windowSize.width + TABLE_WIDTH) / 2.0, (windowSize.height + TABLE_HEIGHT) / 2.0);
	ball_hole[3] = Vec2((windowSize.width - TABLE_WIDTH) / 2.0, (windowSize.height - TABLE_HEIGHT) / 2.0);
	ball_hole[4] = Vec2((windowSize.width) / 2.0, (windowSize.height - TABLE_HEIGHT) / 2.0);
	ball_hole[5] = Vec2((windowSize.width + TABLE_WIDTH) / 2.0, (windowSize.height - TABLE_HEIGHT) / 2.0);
	return true;
}

Scene * BillardScene::scene()
{
	auto scene = Scene::create();
	auto layer = BillardScene::create();
	openglLayer = OpenGLDraw::create();
	if (scene && layer)
	{
		scene->addChild(layer, 1);
		

	}
	if (scene && openglLayer) {
		scene->addChild(openglLayer, 0);
	}
	return scene;
}



void BillardScene::update(float delta)
{
	_world->Step(delta, 10, 10);

	for (int i = 0; i < MAX_BALL; ++i) {
		if (!_billbard[i]->getDie()) {
			_billbard[i]->update(delta);
		}
	}
	if (_force <= 2.0f) {
		_force = _force + 1e-2f;
	}
	else {
		_force = std::min(_force + 5e-3f, 3.0f);
	}

	cocos2d::EventKeyboard::KeyCode leftArrow[2] = { EventKeyboard::KeyCode::KEY_A, EventKeyboard::KeyCode::KEY_LEFT_ARROW };
	cocos2d::EventKeyboard::KeyCode rightArrow[2] = { EventKeyboard::KeyCode::KEY_D, EventKeyboard::KeyCode::KEY_RIGHT_ARROW };
	cocos2d::EventKeyboard::KeyCode upArrow[2] = { EventKeyboard::KeyCode::KEY_W, EventKeyboard::KeyCode::KEY_UP_ARROW };
	cocos2d::EventKeyboard::KeyCode downArrow[2] = { EventKeyboard::KeyCode::KEY_S, EventKeyboard::KeyCode::KEY_DOWN_ARROW };
	Vec2 forwardVecLR = Vec2(_sightline.dirVector.x, _sightline.dirVector.y);
	Vec3 forwardVec = _sightline.dirVector;
	if (forwardVec.length() > 1e-4) {
		forwardVecLR.normalize();
		forwardVec.normalize();
		if (keys[upArrow[0]] || keys[upArrow[1]]) {
			_sightline.oriVector.x = _sightline.oriVector.x + 2.0f * forwardVec.x;
			_sightline.oriVector.y = _sightline.oriVector.y + 2.0f * forwardVec.y;
			_sightline.oriVector.z = _sightline.oriVector.z + 2.0f * forwardVec.z;
		}
		if (keys[downArrow[0]] || keys[downArrow[1]]) {
			_sightline.oriVector.x = _sightline.oriVector.x - 2.0f * forwardVec.x;
			_sightline.oriVector.y = _sightline.oriVector.y - 2.0f * forwardVec.y;
			_sightline.oriVector.z = _sightline.oriVector.z - 2.0f * forwardVec.z;
		}
		if (keys[leftArrow[0]] || keys[leftArrow[1]]) {
			_sightline.oriVector.x = _sightline.oriVector.x - 2.0f * forwardVecLR.y;
			_sightline.oriVector.y = _sightline.oriVector.y + 2.0f * forwardVecLR.x;
		}
		if (keys[rightArrow[0]] || keys[rightArrow[1]]) {
			_sightline.oriVector.x = _sightline.oriVector.x + 2.0f * forwardVecLR.y;
			_sightline.oriVector.y = _sightline.oriVector.y - 2.0f * forwardVecLR.x;
		}
		if (_sightline.oriVector.x < 0.0f) {
			_sightline.oriVector.x = 0.0f;
		}
		if (_sightline.oriVector.y < 0.0f) {
			_sightline.oriVector.y = 0.0f;
		}
		if (_sightline.oriVector.x > SCREEN_WIDTH) {
			_sightline.oriVector.x = SCREEN_WIDTH;
		}
		if (_sightline.oriVector.y > SCREEN_HEIGHT) {
			_sightline.oriVector.y = SCREEN_HEIGHT;
		}
		for (int i = 0; i < MAX_BALL; ++i) {
			if (!_billbard[i]->getDie()) {
				Vec2 Pos = _billbard[i]->getPosition();
				if (_sightline.RayBallIntersection(Vec3(Pos.x, Pos.y, 0.0f), BALL_RADIUS)) {
					_billbard[i]->setSelect(true);
					//_billbard[i]->setVisible(false);
				}
				else {
					_billbard[i]->setSelect(false);
					//_billbard[i]->setVisible(true);
				}
			}
		}

	}
	for (int i = 0; i < MAX_BALL; ++i) {
		if (!_billbard[i]->getDie()) {
			Vec2 Pos = _billbard[i]->getPosition();
			ball_positions[i][0] = (Pos.x - (SCREEN_WIDTH - TABLE_WIDTH) / 2.0 - 125.0);
			ball_positions[i][1] = (Pos.y - (SCREEN_HEIGHT - TABLE_HEIGHT) / 2.0 - 65.0);
			ball_positions[i][2] = 0.0f;
			ball_selected[i] = _billbard[i]->getSelect();
			b2Vec2 Velo = _billbard[i]->getBody()->GetLinearVelocity();
			if (Velo.Length() / BALL_RADIUS < b2_epsilon) {
				ball_rotateAngle[i] = 0.0;
				ball_rotateVec[i][0] = 1.0;
				ball_rotateVec[i][1] = 0.0;
				ball_rotateVec[i][2] = 0.0;
			}
			else {
				ball_rotateAngle[i] = Velo.Length() / BALL_RADIUS;
				Velo.Normalize();
				ball_rotateVec[i][0] = Velo.y;
				ball_rotateVec[i][1] = -Velo.x;
				ball_rotateVec[i][2] = 0.0;
			}
		}
		else {
			ball_positions[i][0] = 0.0;
			ball_positions[i][1] = 0.0;
			ball_positions[i][2] = 0.0;
			ball_rotateAngle[i] = 0.0;
			ball_rotateVec[i][0] = 1.0;
			ball_rotateVec[i][1] = 0.0;
			ball_rotateVec[i][2] = 0.0;
		}
	}
	for (int i = 0; i < MAX_BALL; ++i) {
		if (!_billbard[i]->getDie()) {
			for (int j = 0; j < 6; ++j) {
				if (_billbard[i]->getPosition().distance(ball_hole[j]) < 5.0f) {
					_billbard[i]->die();
					ball_die[i] = true;
					break;
					
				}
			}
		}
	}
	

	camera_eye[0] = _sightline.oriVector.x - SCREEN_WIDTH / 2.0f;
	camera_eye[1] = _sightline.oriVector.y - SCREEN_HEIGHT / 2.0f;
	camera_eye[2] = _sightline.oriVector.z;
	camera_look_at[0] = _sightline.dirVector.x;
	camera_look_at[1] = _sightline.dirVector.y;
	camera_look_at[2] = _sightline.dirVector.z;
	rtc.render();
	//cv::imshow("Billbard Windows", view_global);
	//cv::waitKey(1);

	return;
}

void BillardScene::billardSceneListener()
{
	
	EventListenerMouse* mouseListener = EventListenerMouse::create();
	EventListenerKeyboard* keyBoardListener = EventListenerKeyboard::create();

	mouseListener->onMouseMove = [=](Event * event)
	{
		
		EventMouse* e = (EventMouse*)event;

		float cursorX = (1.5*SCREEN_WIDTH  - 3.0 * e->getCursorX())/SCREEN_WIDTH;
		float cursorY = (SCREEN_HEIGHT - e->getCursorY())/SCREEN_HEIGHT;

		_sightline.dirVector.x = sin(cursorY * Pi)*cos(cursorX * Pi);
		_sightline.dirVector.y = sin(cursorY * Pi)*sin(cursorX * Pi);
		_sightline.dirVector.z = cos(cursorY * Pi);
		_sightline.dirVector.normalize(); //not urged

		for (int i = 0; i < MAX_BALL; ++i) {
			if (!_billbard[i]->getDie()) {
				Vec2 Pos = _billbard[i]->getPosition();
				if (_sightline.RayBallIntersection(Vec3(Pos.x, Pos.y, 0.0f), BALL_RADIUS)) {
					_billbard[i]->setSelect(true);
					//_billbard[i]->setVisible(false);
				}
				else {
					_billbard[i]->setSelect(false);
					//_billbard[i]->setVisible(true);
				}
			}
		}
		
	};
	mouseListener->onMouseDown = [=](Event * event)
	{
		_force = 0.0f;
	};
	mouseListener->onMouseUp = [=](Event * event)
	{

		for (int i = 0; i < MAX_BALL; ++i) {
			if (!_billbard[i]->getDie() && _billbard[i]->getSelect()) {

				b2Vec2 Vel = _billbard[i]->getBody()->GetLinearVelocity();
				Vec2 sDir = Vec2(_sightline.dirVector.x, _sightline.dirVector.y);
				if (sDir.length() <= 1e-4) {
					continue;
				}
				sDir.normalize();
				if (nowHero == 1 || nowHero == 2) {
					Vel.x = Vel.x + sDir.x * _force * 30.0f;
					Vel.y = Vel.y + sDir.y * _force * 30.0f;
					_billbard[i]->getBody()->SetAwake(true);
					_billbard[i]->getBody()->SetLinearVelocity(Vel);
				}
				else {
					Vel.x = Vel.x + sDir.x * _force * 100.0f;
					Vel.y = Vel.y + sDir.y * _force * 100.0f;
					_billbard[i]->getBody()->SetAwake(true);
					_billbard[i]->getBody()->SetLinearVelocity(Vel);
				}
			}
		}
	};
	keyBoardListener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event * event)
	{
		keys[keycode] = true;
	};
	keyBoardListener->onKeyReleased = [=](EventKeyboard::KeyCode keycode, Event * event)
	{
		keys[keycode] = false;
	};
	auto _eventDispatcher = Director::getInstance()->getEventDispatcher();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
	return;
}

void BillardScene::postDataInterface(std::vector<MyVec3>& billardPositon, std::vector<MyVec3>& rotateNormal, std::vector<float>& rotateAngle, MyVec3& rayPoint, MyVec3& rayDir, MyVec3& rayEnd)
{
	for (int i = 0; i < MAX_BALL; ++i) {
		if (!_billbard[i]->getDie()) {
			Vec2 Pos = _billbard[i]->getPosition();
			billardPositon.push_back(MyVec3(Pos.x, Pos.y, 0.0f));
			b2Vec2 Velo = _billbard[i]->getBody()->GetLinearVelocity();
			rotateAngle.push_back(Velo.Length());
			Velo.Normalize();
			rotateNormal.push_back(MyVec3(Velo.y, -Velo.x, 0.0f));
		}
	}
	rayPoint = MyVec3(_sightline.oriVector.x, _sightline.oriVector.y, _sightline.oriVector.z);
	rayDir = MyVec3(_sightline.dirVector.x, _sightline.dirVector.y, _sightline.dirVector.z);
	Vec3 intPoint = _sightline.RayPlaneIntersection(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
	rayEnd = MyVec3(intPoint.x, intPoint.y, intPoint.z);
	return;

}