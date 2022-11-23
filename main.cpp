#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"

int main() {

	Engine::Core::Application app;

	app.init();
	while(!glfwWindowShouldClose(app.window)){
		app.update();
		app.render();
	}
	app.end();
	return 0;
}
