#include "windowControl.hpp"

windowControl::windowControl(int width, int height, std::string name) : width(width), height(height), name(name) {
	createWindow();
}

void windowControl::createWindow() {
	
	// Iniciando glfw
	glfwInit();

	// Definindo versão e o perfil do openGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Criando a janela
	window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	
	// Verificação da janela
	if (window == NULL) {
		std::cout << "Failed to create GLFW Window" << '\n';
		glfwTerminate();
	}

	// Tornando a janela ativa
	glfwMakeContextCurrent(window);

	// Carrega o openGL e define a viewport
	gladLoadGL();
	glViewport(0, 0, width, height);
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
}

GLFWwindow* windowControl::getWindow() {
	return window;
}
