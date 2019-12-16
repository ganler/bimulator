#ifndef __OPENGL_DRAW__
#define __OPENGL_DRAW__

#include "cocos2d.h"
#include <stdio.h>
USING_NS_CC;


#define desk_LEN 250.0f //台球桌的尺寸大概是2500mm*1300mm
#define desk_WID 130.0f	

#define edge_WID 10.0f  //桌子沿
#define edge_HIG 5.0f

#define ball_PCS 50
#define ball_RAD 3.0f	//球直径6mm

class OpenGLDraw : public Node
{
public:
	GLuint _program = 0;
	virtual bool init() override;
	static OpenGLDraw* create();
	virtual void draw(Renderer* renderer, const Mat4& parentTransform, uint32_t parentFlags) override;
	void onDraw();

	cocos2d::CustomCommand _command;
	GLProgram* _glProgram;
	unsigned trac_VBO, trac_VAO, trac_EBO;
	unsigned raytrace_TEX, shadow_TEX;
	unsigned sphere_VBO, sphere_VAO, sphere_EBO;
	unsigned desk_VBO, desk_VAO, desk_EBO;
	unsigned edge_VBO[2], edge_VAO[2];
	unsigned desk_TEX, edge_TEX, sphere_TEX[11];
	unsigned cube_VAO, cube_VBO, cube_TEX[6];

};



#endif