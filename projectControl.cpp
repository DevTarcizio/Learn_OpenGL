#include "projectControl.hpp"

projectControl::projectControl() : window_control(800, 600, "My First Triangle in OpenGL") {

}

void projectControl::render() {
	object_control.draw();
}

void projectControl::update() {

}

void projectControl::run() {
	
	while (!glfwWindowShouldClose(window_control.getWindow())) {
		glfwPollEvents();
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		update();
		render();

		glfwSwapBuffers(window_control.getWindow());
	}

	glfwDestroyWindow(window_control.getWindow());
	glfwTerminate();
}
