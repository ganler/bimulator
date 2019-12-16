#ifndef _NORMALDEFINE
#define _NORMALDEFINE

#include <cmath>
#define PTM_RATIO 32.0f
#define BALL_RADIUS 3.0f
#define MAX_BALL 10
#define ROUND 3
#define TABLE_WIDTH 250
#define TABLE_HEIGHT 130

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define Pi acos(-1)

struct MyVec3 {
	float x, y, z;
	MyVec3(int _x = 0, int _y = 0, int _z = 0)
		:x(_x), y(_y), z(_z){}
};

#endif // !_NORMALDEFINE
