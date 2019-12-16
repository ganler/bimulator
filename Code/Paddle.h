#ifndef _PADDLE_STRUCT
#define _PADDLE_STRUCT

#include "cocos2d.h"
#include "HeroChoice.h"
#include "EnumClass.h"

class Paddle :public cocos2d::Sprite
{
public:
	typeNum typeNumber;
	HeroChoice* hScene;


	static Paddle* paddleWithTexture(cocos2d::Texture2D* pTexture, typeNum _type);
	void mouseClickListener();
	void setParentScene(HeroChoice* _pscene);
};
#endif