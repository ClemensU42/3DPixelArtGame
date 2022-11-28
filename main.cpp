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



	Engine::Asset::openAssetFile("assets.asset");
	Engine::Asset::Asset asset = Engine::Asset::getAsset(R"(.\Assets\game\test.txt)");
	Engine::Asset::Asset asset3 = Engine::Asset::getAsset(R"(.\Assets\game\test2.txt)");
	std::string str((char*)asset.data, 0, asset.assetSize);
	std::string str2((char*)asset3.data, 0, asset3.assetSize);
	std::cout << str << std::endl << str2 << std::endl;

	return 0;
}
