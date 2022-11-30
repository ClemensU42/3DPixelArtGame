//
// Created by Clemens on 22.11.2022.
//

#include "tracy/Tracy.hpp"

#include <iostream>
#include "Application.h"
#include "Engine/Assets/AssetManager.h"
#include "Engine/Graphics/Mesh.h"

namespace Engine {
	namespace Core {

		Graphics::Mesh testMesh;
		Graphics::Shader testShader;

		std::vector<float> vertices = {
				0.5f, 0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				-0.5f, -0.5f, 0.0f,
				-0.5f, 0.5f, 0.0f
		};

		std::vector<unsigned int> indices = {
				0, 1, 3,
				1, 2, 3
		};

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


			Engine::Asset::openAssetFile("assets.asset");

			Engine::Asset::Asset fragmentShaderAsset = Engine::Asset::getAsset(R"(game\shaders\fallback.frag)");
			Engine::Asset::Asset vertexShaderAsset = Engine::Asset::getAsset(R"(game\shaders\fallback.vert)");
			testShader.loadFromAsset(vertexShaderAsset, fragmentShaderAsset);

			testMesh.loadMeshFromVectors(vertices, indices, GL_STATIC_DRAW);
			testMesh.shader = &testShader;
		}

		void Application::update() {
			ZoneScopedN("update");
			glfwPollEvents();
		}

		void Application::render() {
			ZoneScopedN("render");
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			testMesh.render();

			glfwSwapBuffers(window);
		}

		void Application::end() {
			glfwTerminate();
		}
	}
} // Engine