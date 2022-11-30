#include "tracy/Tracy.hpp"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"
#include "Engine/Assets/AssetManager.h"

int main() {
	Engine::Core::Application app;

	app.init();
	while(!glfwWindowShouldClose(app.window)){
		app.update();
		app.render();
		FrameMark;
	}
	app.end();
	return 0;
}
