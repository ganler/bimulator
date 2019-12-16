#ifndef GL_H
#define GL_H
//#include<glad/glad.h>
#include<array>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

#include<GLFW/glfw3.h>

//
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>



void processInput(GLFWwindow* window);

void framebuffer_size_callback
(
	GLFWwindow* window,
	int width,
	int height
);

GLFWwindow* initialize_GL_and_Window
(
	int e1,
	int e2,
	int width,
	int height,
	const char* wName
);


void buildSphere
(
	std::vector<float>& vertice,
	std::vector<unsigned>& indice,
	int sectornum,
	int stacknum,
	float radius
);

unsigned load_texture(const char* filename,unsigned&texture);

unsigned int createShader(const char* vpath, const char* fpath);

void vec3_to_shader
(
	unsigned shader_id,
	const char* vecname,
	glm::vec3& uniform
);

void mat4_to_shader(
	unsigned shader_id,
	const char* vecname,
	glm::mat4& uniform
);



#endif