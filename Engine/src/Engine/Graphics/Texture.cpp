//
// Created by Clemens on 09.12.2022.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define STBI_FAILURE_USERMSG

#include "stb_image.h"

#include "Engine/Graphics/Texture.h"

namespace Engine{
	namespace Graphics{
		void Texture::loadFromAsset(Engine::Asset::Asset asset) {
			data = stbi_load_from_memory((unsigned char*)asset.data, asset.assetSize, &width, &height, &channelCount, 3);

			if(!data){
				std::cout << "Failed to load texture!" << std::endl;
				std::cout << stbi_failure_reason() << std::endl;
				stbi_image_free(data);
				return;
			}

			glGenTextures(1, &gpuTexture);
			glBindTexture(GL_TEXTURE_2D, gpuTexture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}

		void Texture::bind() const{
			glBindTexture(GL_TEXTURE_2D, gpuTexture);
		}
	}
}