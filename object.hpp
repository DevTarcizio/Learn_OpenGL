#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shaderSource.hpp"

class object {
public:
	object();
	void draw();

private:

	void configVertices();
	void createVAO();
	void createVBO();
	void configVertexAttributes();
	void createShaders();
	void createShaderProgram();

	float vertices[9];
	unsigned int VAO;
	unsigned int VBO;
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;


};