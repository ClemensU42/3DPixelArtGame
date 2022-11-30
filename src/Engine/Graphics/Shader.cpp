//
// Created by Clemens on 23.11.2022.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Engine/Graphics/Shader.h"

namespace Engine{
	namespace Graphics{
		void Shader::loadFromAsset(Engine::Asset::Asset vertexShaderAsset, Engine::Asset::Asset fragmentShaderAsset){
			unsigned int vertexShader, fragmentShader;
			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertexSource = Asset::readAssetAsString(&vertexShaderAsset);
			std::string fragmentSource = Asset::readAssetAsString(&fragmentShaderAsset);

			const char* vertexStr = vertexSource.c_str();
			const char* fragStr = fragmentSource.c_str();

			glShaderSource(vertexShader, 1, &vertexStr, nullptr);
			glShaderSource(fragmentShader, 1, &fragStr, nullptr);

			glCompileShader(vertexShader);
			glCompileShader(fragmentShader);

			int success;
			char infoLog[512];
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
			if(!success){
				glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
				return;
			}

			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
			if(!success){
				glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
				std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION::FAILED\n" << infoLog << std::endl;
			}

			this->shaderProgram = glCreateProgram();
			glAttachShader(this->shaderProgram, vertexShader);
			glAttachShader(this->shaderProgram, fragmentShader);
			glLinkProgram(shaderProgram);

			glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
			if(!success){
				glGetProgramInfoLog(this->shaderProgram, 512, nullptr, infoLog);
			}

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
		}
		void Shader::use() const{
			glUseProgram(this->shaderProgram);
		}

		void Shader::setUniform(const char* name, int value){

		}
		void Shader::setUniform(const char* name, float value){

		}
		void Shader::setUniform(const char* name, glm::vec2 value){

		}
		void Shader::setUniform(const char* name, glm::vec3 value){

		}
		void Shader::setUniform(const char* name, glm::vec4 value){

		}
		void Shader::setUniform(const char* name, glm::mat2x2 value){

		}
		void Shader::setUniform(const char* name, glm::mat3x3 value){

		}
		void Shader::setUniform(const char* name, glm::mat4x4 value){

		}
	}
}