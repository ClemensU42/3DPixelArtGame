//
// Created by Clemens on 23.11.2022.
//

#ifndef PIXELART3DGAME_SHADER_H
#define PIXELART3DGAME_SHADER_H

#include <vector>
#include "Engine/Assets/AssetManager.h"

#include <glm.hpp>

namespace Engine{
	namespace Graphics{
		class Shader{
			unsigned int shaderProgram;

		public:
			void loadFromAsset(Engine::Asset::Asset vertexShaderAsset, Engine::Asset::Asset fragmentShaderAsset);
			void use() const;

			void setUniform(const char* name, int value);
			void setUniform(const char* name, float value);
			void setUniform(const char* name, glm::vec2 value);
			void setUniform(const char* name, glm::vec3 value);
			void setUniform(const char* name, glm::vec4 value);
			void setUniform(const char* name, glm::mat2x2 value);
			void setUniform(const char* name, glm::mat3x3 value);
			void setUniform(const char* name, glm::mat4x4 value);
		};
	}
}

#endif //PIXELART3DGAME_SHADER_H
