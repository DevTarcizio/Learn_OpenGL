#include <iostream>
#include <glad/glad.h>	
#include <GLFW/glfw3.h>
#include "shaderSource.hpp"

int main() {
	
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 500, "OpenGL Program", NULL, NULL);
	if (window == NULL) {
		std::cout << "Falha ao carregar a janela" << '\n';
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, 800, 500);
	

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.0f, -0.5f, 0.0f,
		-0.25f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.25f, 0.5f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		1, 3, 4
	};
	
	
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int successVertex;
	char infologVertex[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertex);
	if (!successVertex) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infologVertex);
		std::cout << "Erro na compilacao: " << infologVertex << '\n';
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	int successFragment;
	char infologFragment[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragment);
	if (!successFragment) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infologFragment);
		std::cout << "Erro na compilacao: " << infologFragment << '\n';
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	

	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwDestroyWindow(window);
	glfwTerminate();
}