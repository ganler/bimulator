#include<glad/glad.h>
#include <opencv2/opencv.hpp>
#include"myGL.h"

//#include "std_image.h"






void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void buildSphere(std::vector<float>& vertice,
	std::vector<unsigned>& indice,
	int sectornum,
	int stacknum,
	float radius)
{
	const float PI = 3.1415926f;
	const float sectorstep = 2 * PI / sectornum;
	const float stackstep = PI / stacknum;
	float sectorangle, stackangle;
	float x_y, x, y, z;
	unsigned int k1, k2;
	for (int i = 0; i <= stacknum; ++i)
	{
		stackangle = PI / 2 - i * stackstep;
		x_y = radius * cos(stackangle);
		z = radius * sin(stackangle);
		k1 = i * (sectornum + 1);
		k2 = k1 + sectornum + 1;
		for (int j = 0; j <= sectornum; ++j, ++k1, ++k2)
		{
			sectorangle = j * sectorstep;
			x = x_y * cos(sectorangle);
			y = x_y * sin(sectorangle);
			vertice.push_back(x);
			vertice.push_back(y);
			vertice.push_back(z);
			vertice.push_back(float(j) / sectornum);
			vertice.push_back(float(i) / stacknum);
			vertice.push_back(x / radius);
			vertice.push_back(y / radius);
			vertice.push_back(z / radius);
			if (i < stacknum && j < sectornum) {
				if (i != 0)
				{
					indice.push_back(k1);
					indice.push_back(k2);
					indice.push_back(k1 + 1);
				}
				if (i != (stacknum - 1))
				{
					indice.push_back(k1 + 1);
					indice.push_back(k2);
					indice.push_back(k2 + 1);
				}
			}
		}
	}
}

unsigned int createShader(const char* vpath, const char* fpath)
{
	std::string vertexGLSL;
	std::string fragmentGLSL;
	std::ifstream vertexFile(vpath);
	std::ifstream fragmentFile(fpath);
	std::stringstream vertexStream, fragmentStream;
	vertexStream << vertexFile.rdbuf();
	fragmentStream << fragmentFile.rdbuf();
	vertexFile.close();
	fragmentFile.close();
	vertexGLSL = vertexStream.str();
	fragmentGLSL = fragmentStream.str();
	const char* vertexGLSL_C = vertexGLSL.c_str();
	const char* fragmentGLSL_C = fragmentGLSL.c_str();
	unsigned int vertex, fragment;

	int success;
	char infoLog[1024];
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexGLSL_C, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentGLSL_C, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	unsigned Shader_ID = glCreateProgram();
	glAttachShader(Shader_ID, vertex);
	glAttachShader(Shader_ID, fragment);
	glLinkProgram(Shader_ID);
	glGetShaderiv(Shader_ID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(Shader_ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return Shader_ID;
}

GLFWwindow* initialize_GL_and_Window(int e1, int e2, int width, int height, const char* wName)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, e1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, e2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(width, height, "Colorful Cube", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Initialize GLAD failure" << std::endl;
		exit(1);
	}
	return window;
}

unsigned load_texture(const char* filename,unsigned&texture)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	auto im = cv::imread(filename);
	cv::cvtColor(im, im, cv::COLOR_BGR2RGB);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im.cols, im.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, im.data);
	glGenerateMipmap(GL_TEXTURE_2D);

	return texture;
}

void vec3_to_shader(unsigned shader_id, const char* vecname, glm::vec3& uniform) {
	unsigned int loc = glGetUniformLocation(shader_id, vecname);
	glUniform3fv(loc, 1, &uniform[0]);
}
void mat4_to_shader(unsigned shader_id, const char* vecname, glm::mat4& uniform) {
	unsigned int loc = glGetUniformLocation(shader_id, vecname);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(uniform));
}



