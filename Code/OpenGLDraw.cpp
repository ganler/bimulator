#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<opencv2/opencv.hpp>
#include<ctime>
#include<cmath>
#include "OpenGLDraw.h"
#include "GlobalVar.h"
#include "myGL.h"
#include<iostream>
USING_NS_CC;

const char* texture_source[] =//cc
{
	"textures/0.bmp",
	"textures/1.bmp",
	"textures/2.bmp",
	"textures/3.bmp",
	"textures/4.bmp",
	"textures/5.bmp",
	"textures/6.bmp",
	"textures/7.bmp",
	"textures/8.bmp",
	"textures/9.bmp",
	"textures/10.bmp"
};
const char* skybox_source[] =
{
	"textures/skybox/down.bmp",
	"textures/skybox/west.bmp",
	"textures/skybox/east.bmp",
	"textures/skybox/up.bmp",
	"textures/skybox/north.bmp",
	"textures/skybox/south.bmp"
};
const float BOXWID = 800.0f;
float skybox_ver[] = {
	// positions          
	-BOXWID,  BOXWID, -BOXWID,//0 down
	-BOXWID, -BOXWID, -BOXWID,
	 BOXWID, -BOXWID, -BOXWID,
	 BOXWID, -BOXWID, -BOXWID,
	 BOXWID,  BOXWID, -BOXWID,
	-BOXWID,  BOXWID, -BOXWID,

	-BOXWID, -BOXWID,  BOXWID,//18  west
	-BOXWID, -BOXWID, -BOXWID,
	-BOXWID,  BOXWID, -BOXWID,
	-BOXWID,  BOXWID, -BOXWID,
	-BOXWID,  BOXWID,  BOXWID,
	-BOXWID, -BOXWID,  BOXWID,

	 BOXWID, -BOXWID, -BOXWID,//36  east
	 BOXWID, -BOXWID,  BOXWID,
	 BOXWID,  BOXWID,  BOXWID,
	 BOXWID,  BOXWID,  BOXWID,
	 BOXWID,  BOXWID, -BOXWID,
	 BOXWID, -BOXWID, -BOXWID,

	-BOXWID, -BOXWID,  BOXWID,//54  up
	-BOXWID,  BOXWID,  BOXWID,
	 BOXWID,  BOXWID,  BOXWID,
	 BOXWID,  BOXWID,  BOXWID,
	 BOXWID, -BOXWID,  BOXWID,
	-BOXWID, -BOXWID,  BOXWID,

	-BOXWID,  BOXWID, -BOXWID,//72  front
	 BOXWID,  BOXWID, -BOXWID,
	 BOXWID,  BOXWID,  BOXWID,
	 BOXWID,  BOXWID,  BOXWID,
	-BOXWID,  BOXWID,  BOXWID,
	-BOXWID,  BOXWID, -BOXWID,

	-BOXWID, -BOXWID, -BOXWID,//90  back
	-BOXWID, -BOXWID,  BOXWID,
	 BOXWID, -BOXWID, -BOXWID,
	 BOXWID, -BOXWID, -BOXWID,
	-BOXWID, -BOXWID,  BOXWID,
	 BOXWID, -BOXWID,  BOXWID
};
float    desk_ver[] =//,屎绿色纹理,法向量朝上
{
	 desk_LEN / 2.0, desk_WID / 2.0, -ball_RAD, 1.0, 1.0,	 0.0, 0.0, 1.0,//台球z坐标为0的话-ball_RAD
	 desk_LEN / 2.0,-desk_WID / 2.0, -ball_RAD, 1.0, 0.0,	 0.0, 0.0, 1.0,
	-desk_LEN / 2.0, desk_WID / 2.0, -ball_RAD, 0.0, 1.0,	 0.0, 0.0, 1.0,
	-desk_LEN / 2.0,-desk_WID / 2.0, -ball_RAD, 0.0, 0.0,	 0.0, 0.0, 1.0
};
unsigned desk_idx[] =
{
	0,1,2,
	1,2,3
};
float edge_ver_x[] =  //非要说的话也就4个重复的长方体，贴4份图就行
{
		-desk_LEN / 2.0, -edge_WID / 2.0, -edge_HIG,  0.0f,  0.0f, -1.0f,	-1.0f,-1.0f,
		 desk_LEN / 2.0, -edge_WID / 2.0, -edge_HIG,  0.0f,  0.0f, -1.0f,	 1.0f,-1.0f,
		 desk_LEN / 2.0,  edge_WID / 2.0, -edge_HIG,  0.0f,  0.0f, -1.0f,	 1.0f, 1.0f,
		 desk_LEN / 2.0,  edge_WID / 2.0, -edge_HIG,  0.0f,  0.0f, -1.0f,	 1.0f, 1.0f,
		-desk_LEN / 2.0,  edge_WID / 2.0, -edge_HIG,  0.0f,  0.0f, -1.0f,	-1.0f, 1.0f,
		-desk_LEN / 2.0, -edge_WID / 2.0, -edge_HIG,  0.0f,  0.0f, -1.0f,	-1.0f,-1.0f,

		-desk_LEN / 2.0, -edge_WID / 2.0,  edge_HIG,  0.0f,  0.0f,  1.0f,	-1.0f,-1.0f,
		 desk_LEN / 2.0, -edge_WID / 2.0,  edge_HIG,  0.0f,  0.0f,  1.0f,	 1.0f,-1.0f,
		 desk_LEN / 2.0,  edge_WID / 2.0,  edge_HIG,  0.0f,  0.0f,  1.0f,	 1.0f, 1.0f,
		 desk_LEN / 2.0,  edge_WID / 2.0,  edge_HIG,  0.0f,  0.0f,  1.0f,	1.0f, 1.0f,
		-desk_LEN / 2.0,  edge_WID / 2.0,  edge_HIG,  0.0f,  0.0f,  1.0f,	-1.0f, 1.0f,
		-desk_LEN / 2.0, -edge_WID / 2.0,  edge_HIG,  0.0f,  0.0f,  1.0f,	-1.0f,-1.0f,

		-desk_LEN / 2.0,  edge_WID / 2.0,  edge_HIG, -1.0f,  0.0f,  0.0f,	 1.0f, 1.0f,
		-desk_LEN / 2.0,  edge_WID / 2.0, -edge_HIG, -1.0f,  0.0f,  0.0f,	 1.0f,-1.0f,
		-desk_LEN / 2.0, -edge_WID / 2.0, -edge_HIG, -1.0f,  0.0f,  0.0f,	-1.0f,-1.0f,
		-desk_LEN / 2.0, -edge_WID / 2.0, -edge_HIG, -1.0f,  0.0f,  0.0f,	-1.0f,-1.0f,
		-desk_LEN / 2.0, -edge_WID / 2.0,  edge_HIG, -1.0f,  0.0f,  0.0f,	-1.0f, 1.0f,
		-desk_LEN / 2.0,  edge_WID / 2.0,  edge_HIG, -1.0f,  0.0f,  0.0f,	 1.0f, 1.0f,

		 desk_LEN / 2.0,  edge_WID / 2.0,  edge_HIG,  1.0f,  0.0f,  0.0f,	 1.0f, 1.0f,
		 desk_LEN / 2.0,  edge_WID / 2.0, -edge_HIG,  1.0f,  0.0f,  0.0f,	 1.0f,-1.0f,
		 desk_LEN / 2.0, -edge_WID / 2.0, -edge_HIG,  1.0f,  0.0f,  0.0f,	-1.0f,-1.0f,
		 desk_LEN / 2.0, -edge_WID / 2.0, -edge_HIG,  1.0f,  0.0f,  0.0f,	-1.0f,-1.0f,
		 desk_LEN / 2.0, -edge_WID / 2.0,  edge_HIG,  1.0f,  0.0f,  0.0f,	-1.0f, 1.0f,
		 desk_LEN / 2.0,  edge_WID / 2.0,  edge_HIG,  1.0f,  0.0f,  0.0f,	 1.0f, 1.0f,

		-desk_LEN / 2.0, -edge_WID / 2.0, -edge_HIG,  0.0f, -1.0f,  0.0f,	-1.0f,-1.0f,
		 desk_LEN / 2.0, -edge_WID / 2.0, -edge_HIG,  0.0f, -1.0f,  0.0f,	1.0f,-1.0f,
		 desk_LEN / 2.0, -edge_WID / 2.0,  edge_HIG,  0.0f, -1.0f,  0.0f,	1.0f, 1.0f,
		 desk_LEN / 2.0, -edge_WID / 2.0,  edge_HIG,  0.0f, -1.0f,  0.0f,	1.0f, 1.0f,
		-desk_LEN / 2.0, -edge_WID / 2.0,  edge_HIG,  0.0f, -1.0f,  0.0f,	-1.0f, 1.0f,
		-desk_LEN / 2.0, -edge_WID / 2.0, -edge_HIG,  0.0f, -1.0f,  0.0f,	-1.0f,-1.0f,

		-desk_LEN / 2.0,  edge_WID / 2.0, -edge_HIG,  0.0f,  1.0f,  0.0f,	-1.0f,-1.0f,
		 desk_LEN / 2.0,  edge_WID / 2.0, -edge_HIG,  0.0f,  1.0f,  0.0f,	 1.0f,-1.0f,
		 desk_LEN / 2.0,  edge_WID / 2.0,  edge_HIG,  0.0f,  1.0f,  0.0f,	 1.0f, 1.0f,
		 desk_LEN / 2.0,  edge_WID / 2.0,  edge_HIG,  0.0f,  1.0f,  0.0f,	 1.0f, 1.0f,
		-desk_LEN / 2.0,  edge_WID / 2.0,  edge_HIG,  0.0f,  1.0f,  0.0f,	-1.0f, 1.0f,
		-desk_LEN / 2.0,  edge_WID / 2.0, -edge_HIG,  0.0f,  1.0f,  0.0f,	-1.0f,-1.0f
};
float edge_ver_y[] =
{
		-edge_WID / 2.0, -desk_WID / 2.0, -edge_HIG,  0.0f,  0.0f, -1.0f,	-1.0f,-1.0f,
		 edge_WID / 2.0, -desk_WID / 2.0, -edge_HIG,  0.0f,  0.0f, -1.0f,	 1.0f,-1.0f,
		 edge_WID / 2.0,  desk_WID / 2.0, -edge_HIG,  0.0f,  0.0f, -1.0f,	 1.0f, 1.0f,
		 edge_WID / 2.0,  desk_WID / 2.0, -edge_HIG,  0.0f,  0.0f, -1.0f,	 1.0f, 1.0f,
		-edge_WID / 2.0,  desk_WID / 2.0, -edge_HIG,  0.0f,  0.0f, -1.0f,	-1.0f, 1.0f,
		-edge_WID / 2.0, -desk_WID / 2.0, -edge_HIG,  0.0f,  0.0f, -1.0f,	-1.0f,-1.0f,

		-edge_WID / 2.0, -desk_WID / 2.0,  edge_HIG,  0.0f,  0.0f,  1.0f,	-1.0f,-1.0f,
		 edge_WID / 2.0, -desk_WID / 2.0,  edge_HIG,  0.0f,  0.0f,  1.0f,	 1.0f,-1.0f,
		 edge_WID / 2.0,  desk_WID / 2.0,  edge_HIG,  0.0f,  0.0f,  1.0f,	 1.0f, 1.0f,
		 edge_WID / 2.0,  desk_WID / 2.0,  edge_HIG,  0.0f,  0.0f,  1.0f,	1.0f, 1.0f,
		-edge_WID / 2.0,  desk_WID / 2.0,  edge_HIG,  0.0f,  0.0f,  1.0f,	-1.0f, 1.0f,
		-edge_WID / 2.0, -desk_WID / 2.0,  edge_HIG,  0.0f,  0.0f,  1.0f,	-1.0f,-1.0f,

		-edge_WID / 2.0,  desk_WID / 2.0,  edge_HIG, -1.0f,  0.0f,  0.0f,	 1.0f, 1.0f,
		-edge_WID / 2.0,  desk_WID / 2.0, -edge_HIG, -1.0f,  0.0f,  0.0f,	 1.0f,-1.0f,
		-edge_WID / 2.0, -desk_WID / 2.0, -edge_HIG, -1.0f,  0.0f,  0.0f,	-1.0f,-1.0f,
		-edge_WID / 2.0, -desk_WID / 2.0, -edge_HIG, -1.0f,  0.0f,  0.0f,	-1.0f,-1.0f,
		-edge_WID / 2.0, -desk_WID / 2.0,  edge_HIG, -1.0f,  0.0f,  0.0f,	-1.0f, 1.0f,
		-edge_WID / 2.0,  desk_WID / 2.0,  edge_HIG, -1.0f,  0.0f,  0.0f,	 1.0f, 1.0f,

		 edge_WID / 2.0,  desk_WID / 2.0,  edge_HIG,  1.0f,  0.0f,  0.0f,	 1.0f, 1.0f,
		 edge_WID / 2.0,  desk_WID / 2.0, -edge_HIG,  1.0f,  0.0f,  0.0f,	 1.0f,-1.0f,
		 edge_WID / 2.0, -desk_WID / 2.0, -edge_HIG,  1.0f,  0.0f,  0.0f,	-1.0f,-1.0f,
		 edge_WID / 2.0, -desk_WID / 2.0, -edge_HIG,  1.0f,  0.0f,  0.0f,	-1.0f,-1.0f,
		 edge_WID / 2.0, -desk_WID / 2.0,  edge_HIG,  1.0f,  0.0f,  0.0f,	-1.0f, 1.0f,
		 edge_WID / 2.0,  desk_WID / 2.0,  edge_HIG,  1.0f,  0.0f,  0.0f,	 1.0f, 1.0f,

		-edge_WID / 2.0, -desk_WID / 2.0, -edge_HIG,  0.0f, -1.0f,  0.0f,	-1.0f,-1.0f,
		 edge_WID / 2.0, -desk_WID / 2.0, -edge_HIG,  0.0f, -1.0f,  0.0f,	1.0f,-1.0f,
		 edge_WID / 2.0, -desk_WID / 2.0,  edge_HIG,  0.0f, -1.0f,  0.0f,	1.0f, 1.0f,
		 edge_WID / 2.0, -desk_WID / 2.0,  edge_HIG,  0.0f, -1.0f,  0.0f,	1.0f, 1.0f,
		-edge_WID / 2.0, -desk_WID / 2.0,  edge_HIG,  0.0f, -1.0f,  0.0f,	-1.0f, 1.0f,
		-edge_WID / 2.0, -desk_WID / 2.0, -edge_HIG,  0.0f, -1.0f,  0.0f,	-1.0f,-1.0f,

		-edge_WID / 2.0,  desk_WID / 2.0, -edge_HIG,  0.0f,  1.0f,  0.0f,	-1.0f,-1.0f,
		 edge_WID / 2.0,  desk_WID / 2.0, -edge_HIG,  0.0f,  1.0f,  0.0f,	 1.0f,-1.0f,
		 edge_WID / 2.0,  desk_WID / 2.0,  edge_HIG,  0.0f,  1.0f,  0.0f,	 1.0f, 1.0f,
		 edge_WID / 2.0,  desk_WID / 2.0,  edge_HIG,  0.0f,  1.0f,  0.0f,	 1.0f, 1.0f,
		-edge_WID / 2.0,  desk_WID / 2.0,  edge_HIG,  0.0f,  1.0f,  0.0f,	-1.0f, 1.0f,
		-edge_WID / 2.0,  desk_WID / 2.0, -edge_HIG,  0.0f,  1.0f,  0.0f,	-1.0f,-1.0f
};
float trac_ver[] =
{
	1.0,1.0,0.0,
	1.0,-1.0,0.0,
	-1.0,1.0,0.0,
	-1.0,1.0,0.0
};
float trac_idx[] =
{
	0,1,2,
	1,2,3
};
std::vector<float>_vertice;
std::vector<unsigned>_indice;

extern float ball_positions[10][3];
float last_positions[10][3] = { 0 };
glm::mat4 ball_lastRotate[10];
extern float camera_eye[3];
extern float camera_look_at[3];
extern float ball_rotateAngle[10];
extern float ball_rotateVec[10][3];
extern bool ball_selected[10];
extern float shadow_factor[VIEW_ROW][VIEW_COL];
extern float sample_results[VIEW_ROW][VIEW_COL][3];

unsigned char _sresults[VIEW_ROW][VIEW_COL][3] = { 0 };
unsigned char _sshadows[VIEW_ROW][VIEW_COL][3] = { 0 };

unsigned baseLoc, tracLoc, shadLoc,cubeLoc;

OpenGLDraw* OpenGLDraw::create()
{
	OpenGLDraw* test = new(std::nothrow) OpenGLDraw();
	if (test && test->init())
	{
		test->autorelease();
		return test;
	}
	else
	{
		delete test;
		test = nullptr;
		return nullptr;
	}
}

bool OpenGLDraw::init()
{
	for (int i = 0; i < 10; ++i)
	{
		ball_lastRotate[i] = glm::mat4(1.0);
		ball_rotateVec[i][0] = 1.0f;
		ball_rotateVec[i][1] = 0.0f;
		ball_rotateVec[i][2] = 0.0f;
		ball_rotateAngle[i] = 0.0f;
	}


	_glProgram = new GLProgram();  
    _glProgram->initWithFilenames("shaders/cube.vsh", "shaders/cube.fsh");
	std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "shd:"<<_glProgram->getProgramLog() << std::endl;
	std::cout << "vsh:"<< _glProgram->getVertexShaderLog() << std::endl;
	std::cout << "fsh:" << _glProgram->getFragmentShaderLog() << std::endl << std::endl;
	_glProgram->link();
	_glProgram->updateUniforms();
	//std::cout << _glProgram->getProgram() << std::endl;
	//set uniform locations
	//使用此shader
	_glProgram->use();
	unsigned aPosLoc = _glProgram->getAttribLocation("aPos");
	unsigned aTxLoc = _glProgram->getAttribLocation("aTx");
	unsigned aNormLoc = _glProgram->getAttribLocation("aNorm");
	baseLoc = _glProgram->getUniformLocation("CC_Texture0");
	tracLoc = _glProgram->getUniformLocation("CC_Texture1");
	shadLoc = _glProgram->getUniformLocation("CC_Texture2");
	cubeLoc = _glProgram->getUniformLocation("CC_Texture3");
	std::cout << baseLoc << " " << tracLoc << std::endl;

	
	buildSphere(_vertice, _indice, ball_PCS, ball_PCS, ball_RAD);//初始化球模型
	glGenVertexArrays(1, &sphere_VAO);
	glGenBuffers(1, &sphere_VBO);
	glGenBuffers(1, &sphere_EBO);
	GL::bindVAO(sphere_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, sphere_VBO);
	glBufferData(GL_ARRAY_BUFFER, _vertice.size() * sizeof(float), &_vertice[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indice.size() * sizeof(unsigned), &_indice[0], GL_STATIC_DRAW);
	glVertexAttribPointer(aPosLoc, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), NULL);
	glEnableVertexAttribArray(aPosLoc);
	glVertexAttribPointer(aTxLoc, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(aTxLoc);
	glVertexAttribPointer(aNormLoc, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(aNormLoc);
	for (int i = 0; i < 11; ++i)
	{
		glGenTextures(1, &sphere_TEX[i]);
		GL::bindTexture2DN(0,sphere_TEX[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		auto im = cv::imread(texture_source[i]);
		cv::cvtColor(im, im, cv::COLOR_BGR2RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im.cols, im.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, im.data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glGenVertexArrays(1, &desk_VAO);//初始化桌子模型
	glGenBuffers(1, &desk_VBO);
	glGenBuffers(1, &desk_EBO);
	GL::bindVAO(desk_VAO);
	glBindBuffer(GL_ARRAY_BUFFER,desk_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(desk_ver), desk_ver, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, desk_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(desk_idx), desk_idx, GL_STATIC_DRAW);
	glVertexAttribPointer(aPosLoc, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), NULL);
	glEnableVertexAttribArray(aPosLoc);
	glVertexAttribPointer(aTxLoc, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(aTxLoc);
	glVertexAttribPointer(aNormLoc, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(aNormLoc);
	{
		glGenTextures(1, &desk_TEX);
		GL::bindTexture2DN(0,desk_TEX);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		auto im = cv::imread("textures/desk.bmp");
		cv::cvtColor(im, im, cv::COLOR_BGR2RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im.cols, im.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, im.data);
		glGenerateMipmap(GL_TEXTURE_2D);
		
	}


	glGenVertexArrays(2, edge_VAO);
	glGenBuffers(2, edge_VBO);
	GL::bindVAO(edge_VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, edge_VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(edge_ver_x), edge_ver_x, GL_STATIC_DRAW);
	glVertexAttribPointer(aPosLoc, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), NULL);
	glEnableVertexAttribArray(aPosLoc);
	glVertexAttribPointer(aTxLoc, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(aTxLoc);
	glVertexAttribPointer(aNormLoc, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(aNormLoc);
	GL::bindVAO(edge_VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, edge_VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(edge_ver_y), edge_ver_y, GL_STATIC_DRAW);
	glVertexAttribPointer(aPosLoc, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), NULL);
	glEnableVertexAttribArray(aPosLoc);
	glVertexAttribPointer(aTxLoc, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(aTxLoc);
	glVertexAttribPointer(aNormLoc, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(aNormLoc);
	{
		glGenTextures(1, &edge_TEX);
		GL::bindTexture2DN(0,edge_TEX);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		auto im = cv::imread("textures/wood.jpg");
		cv::cvtColor(im, im, cv::COLOR_BGR2RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im.cols, im.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, im.data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glGenTextures(1, &raytrace_TEX);
	GL::bindTexture2DN(1, raytrace_TEX);
	glGenTextures(1, &shadow_TEX);
	GL::bindTexture2DN(2, shadow_TEX);

	//立方体贴图
	glGenVertexArrays(1, &cube_VAO);
	glGenBuffers(1, &cube_VBO);
	GL::bindVAO(cube_VAO);
	GL::bindVAO(0);
	glGenTextures(6, cube_TEX);//cocos2dx貌似不支持cubemap所以只能这么干了
	for (int i = 0; i < 6; ++i)
	{
		GL::bindTexture2DN(3, cube_TEX[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		auto im = cv::imread(skybox_source[i]);
		cv::cvtColor(im, im, cv::COLOR_BGR2RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im.cols, im.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, im.data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	GL::bindTexture2DN(3,0);

	_command.init(_globalZOrder);
	_command.func = CC_CALLBACK_0(OpenGLDraw::onDraw, this);

	return true;
}

void OpenGLDraw::draw(Renderer* renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
	Director::getInstance()->getRenderer()->addCommand(&_command);
}

void OpenGLDraw::onDraw()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(true);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//绘制光锥得到的图片
	for (int i = 0; i < (int)VIEW_ROW; ++i) {
		for (int j = 0; j < (int)VIEW_COL; ++j) {
			_sshadows[i][j][0] = (unsigned char)(255 * shadow_factor[i][j]);
			for (int k = 0; k < 3; ++k) {
				_sresults[i][j][k] = (unsigned char)(255 * sample_results[i][j][k]);
			}
		}
	}

	GL::bindTexture2DN(1,raytrace_TEX);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, VIEW_COL, VIEW_ROW, 0, GL_RGB, GL_UNSIGNED_BYTE, _sresults);
	glGenerateMipmap(GL_TEXTURE_2D);

	GL::bindTexture2DN(2, shadow_TEX);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, VIEW_COL, VIEW_ROW, 0, GL_RGB, GL_UNSIGNED_BYTE, _sshadows);
	glGenerateMipmap(GL_TEXTURE_2D);


	_glProgram->use();
	_glProgram->setUniformsForBuiltins();


	glm::mat4 model(1.0f);
	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);
	glm::mat4 rot(1.0f);
	glm::vec3 light_pos(0.0, 0.0, 30.0);
	glm::vec3 view_pos(camera_eye[0],camera_eye[1],camera_eye[2]);
	glm::vec3 lookcenter(camera_look_at[0], camera_look_at[1], camera_look_at[2]);
	unsigned int modelLoc = _glProgram->getUniformLocation("model");
	unsigned int viewLoc = _glProgram->getUniformLocation("view");
	unsigned int projectionLoc = _glProgram->getUniformLocation("projection");
	unsigned int rotLoc= _glProgram->getUniformLocation("rot");
	unsigned int light_posLoc = _glProgram->getUniformLocation("light_pos");
	unsigned int view_posLoc = _glProgram->getUniformLocation("view_pos");
	unsigned int flagLoc = _glProgram->getUniformLocation("flag");

	view = glm::lookAt(view_pos, lookcenter+view_pos, glm::vec3(0.0f, 0.0f, 1));
	projection = glm::perspective(glm::radians(60.0f), float(800 / 600.0), 0.1f, 2000.0f);
	

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniform3fv(light_posLoc, 1, glm::value_ptr(light_pos));
	glUniform3fv(view_posLoc, 1, glm::value_ptr(view_pos));


	GL::bindVAO(sphere_VAO);                 //ball
	for (int i = 0; i < 10; ++i) {
		if (!ball_die[i]) {
			model = glm::translate(glm::mat4(1.0), glm::vec3(ball_positions[i][0], ball_positions[i][1], ball_positions[i][2]));
			if (abs(ball_rotateAngle[i]) > 1e-6)
			{
				rot = glm::rotate
				(
					glm::mat4(1.0),
					-ball_rotateAngle[i],
					glm::vec3(
						ball_rotateVec[i][0],
						ball_rotateVec[i][1],
						ball_rotateVec[i][2]
					)
				);
				rot = rot * ball_lastRotate[i];
				ball_lastRotate[i] = rot;
				model = model * rot;
			}
			glUniformMatrix4fv(rotLoc, 1, GL_FALSE, glm::value_ptr(rot));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			if (ball_selected[i])
				GL::bindTexture2DN(0, sphere_TEX[10]);
			else
				GL::bindTexture2DN(0, sphere_TEX[i]);
			glUniform1i(baseLoc, 0);
			GL::bindTexture2DN(1, raytrace_TEX);
			glUniform1i(tracLoc, 1);
			GL::bindTexture2DN(2, shadow_TEX);
			glUniform1i(shadLoc, 2);
			glDrawElements(GL_TRIANGLES, _vertice.size(), GL_UNSIGNED_INT, 0);
			rot = glm::mat4(1.0);
		}
	}
	glUniformMatrix4fv(rotLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0)));


	GL::bindVAO(desk_VAO);				//desk
	model = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 0));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	GL::bindTexture2DN(0, desk_TEX);
	glUniform1i(baseLoc, 0);
	GL::bindTexture2DN(1, raytrace_TEX);
	glUniform1i(tracLoc, 1);
	GL::bindTexture2DN(2, shadow_TEX);
	glUniform1i(shadLoc, 2);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



	GL::bindVAO(edge_VAO[0]);
	model = glm::translate(glm::mat4(1.0), glm::vec3(0.0, desk_WID / 2+edge_WID/2, -ball_RAD));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	GL::bindTexture2DN(0, edge_TEX);
	glUniform1i(baseLoc, 0);
	GL::bindTexture2DN(1, raytrace_TEX);
	glUniform1i(tracLoc, 1);
	GL::bindTexture2DN(2, shadow_TEX);
	glUniform1i(shadLoc, 2);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::translate(glm::mat4(1.0), glm::vec3(0.0, -desk_WID /2- edge_WID / 2, -ball_RAD));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	GL::bindTexture2DN(0, edge_TEX);
	glUniform1i(baseLoc, 0);
	GL::bindTexture2DN(1, raytrace_TEX);
	glUniform1i(tracLoc, 1);
	GL::bindTexture2DN(2, shadow_TEX);
	glUniform1i(shadLoc, 2);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	GL::bindVAO(edge_VAO[1]);
	model = glm::translate(glm::mat4(1.0), glm::vec3(desk_LEN / 2+ edge_WID / 2, 0, -ball_RAD));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	GL::bindTexture2DN(0, edge_TEX);
	glUniform1i(baseLoc, 0);
	GL::bindTexture2DN(1, raytrace_TEX);
	glUniform1i(tracLoc, 1);
	GL::bindTexture2DN(2, shadow_TEX);
	glUniform1i(shadLoc, 2);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::translate(glm::mat4(1.0), glm::vec3(-desk_LEN / 2- edge_WID / 2, 0, -ball_RAD));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	GL::bindTexture2DN(0, edge_TEX);
	glUniform1i(baseLoc, 0);
	GL::bindTexture2DN(1, raytrace_TEX);
	glUniform1i(tracLoc, 1);
	GL::bindTexture2DN(2, shadow_TEX);
	glUniform1i(shadLoc, 2);
	glDrawArrays(GL_TRIANGLES, 0, 36);



	glDepthMask(GL_FALSE);
	model = glm::translate(glm::mat4(1.0), glm::vec3(0.0,0.0,0.0));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	for (int i = 0; i < 6; ++i)
	{
		GL::bindVAO(cube_VAO);
		GL::bindTexture2DN(3, cube_TEX[i]);
		glBindVertexArray(cube_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, cube_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skybox_ver)/6, &skybox_ver[i*18], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
		glEnableVertexAttribArray(0);
		glUniform1i(cubeLoc, 3);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glDepthMask(GL_TRUE);



	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 3; ++j)
			last_positions[i][j] = ball_positions[i][j];
	}

	GL::bindTexture2DN(0, 0);
	GL::bindTexture2DN(1, 0);
	GL::bindTexture2DN(2, 0);
	GL::bindTextureN(3, 0, GL_TEXTURE_CUBE_MAP);
	GL::bindVAO(0);
}
