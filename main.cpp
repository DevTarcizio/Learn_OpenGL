#include <iostream>
#include <glad/glad.h>	
#include <GLFW/glfw3.h>
#include "shaderClass.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "EBO.hpp"


// Definição dos vertices
GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.0f, -0.5f, 0.0f,
	-0.25f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.25f, 0.5f, 0.0f
};

// Definição dos indices
GLuint indices[] = {
	0, 1, 2,
	1, 3, 4
};


int main() {
	
	// Configurações da janela
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
	
	// Criação dos shaders, passando os caminhos do arquivos como argumentos
	Shader shaderProgram("vertex.vert", "fragment.frag");

	// Criando o VAO e o ativando
	VAO VAO1;
	VAO1.Bind();

	// Criando o VBO e o EBO, com seus respectivos parametros
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// Linkando o VBO ao VAO para a configuração dos atributos dos vertices
	VAO1.LinkVBO(VBO1, 0);

	// Desativando todos os VBO, VAO e EBO
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	
	// Loop principal
	while (!glfwWindowShouldClose(window)) {

		// Definindo a cor do background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Ativando o shader program
		shaderProgram.Activate();
		// Ativando o VAO
		VAO1.Bind();
		// Desenhando os elementos
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		// Troca de buffers visuais
		glfwSwapBuffers(window);
		// Captura de eventos
		glfwPollEvents();
	}

	// Liberando recursos
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
}