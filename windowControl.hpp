#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class windowControl {

public:
	windowControl(int width, int height, std::string name);

	void createWindow();
	GLFWwindow* getWindow();

	int width;
	int height;
	std::string name;

	GLFWwindow* window;
};