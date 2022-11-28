//
// Created by Clemens on 22.11.2022.
//

#include "tracy/Tracy.hpp"

#include <iostream>
#include "Application.h"

namespace Engine {
	namespace Core {
		void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
			glViewport(0, 0, width, height);
		}

		void Application::init() {
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			window = glfwCreateWindow(windowWidth, windowHeight, "Pixel Art Game", NULL, NULL);
			if (window == NULL) {
				std::cout << "Failed to create GLFW window" << std::endl;
				glfwTerminate();
				exit(- 1);
			}

			glfwMakeContextCurrent(window);

			if (! gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
				std::cout << "Failed to initialize GLAD" << std::endl;
				exit(- 1);
			}

			glViewport(0, 0, windowWidth, windowHeight);

			glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
		}

		void Application::update() {
			ZoneScopedN("update");
			glfwPollEvents();
		}

		void Application::render() {
			ZoneScopedN("render");
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(window);
		}

		void Application::end() {
			glfwTerminate();
		}
	}
} // Engine