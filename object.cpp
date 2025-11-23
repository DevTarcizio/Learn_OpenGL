#include "object.hpp"

object::object() {
	configVertices();
	createVAO();
	createVBO();
	configVertexAttributes();
	createShaders();
	createShaderProgram();
}

void object::configVertices() {
	float temp[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	std::copy(std::begin(temp), std::end(temp), vertices);
}

void object::createVAO() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void object::createVBO() {
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void object::configVertexAttributes() {
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void object::createShaders() {
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

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	int successFragment;
	char infologFragment[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successFragment);
	if (!successFragment) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infologFragment);
		std::cout << "Erro na compilacao: " << infologFragment << '\n';
	}
}

void object::createShaderProgram() {
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	int successProgram;
	char infologProgram[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successProgram);
	if (!successProgram) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infologProgram);
		std::cout << "Erro na linkagem do shaderProgram: " << infologProgram << '\n';
	}
}

void object::draw() {
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
