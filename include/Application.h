//
// Created by Clemens on 22.11.2022.
//

#ifndef PIXELART3DGAME_APPLICATION_H
#define PIXELART3DGAME_APPLICATION_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Engine {
	namespace Core {
		void framebufferSizeCallback(GLFWwindow *window, int width, int height);

		class Application {
		public:
			GLFWwindow *window;
			int windowWidth = 1920;
			int windowHeight = 1080;
		public:
			void init();

			void update();

			void render();

			void end();
		};
	}
} // Engine

#endif //PIXELART3DGAME_APPLICATION_H
