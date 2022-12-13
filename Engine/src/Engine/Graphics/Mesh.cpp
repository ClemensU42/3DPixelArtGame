//
// Created by Clemens on 22.11.2022.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include "Engine/Graphics/Mesh.h"

namespace Engine{
	namespace Graphics{
		void Mesh::loadMeshFromVectors(std::vector<float> verticesArg, std::vector<unsigned int> indicesArg, unsigned int type){
			glGenVertexArrays(1, &this->VAO);
			glBindVertexArray(this->VAO);

			glGenBuffers(1, &this->VBO);
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferData(GL_ARRAY_BUFFER, verticesArg.size() * sizeof(float), verticesArg.data(), type);

			glGenBuffers(1, &this->EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesArg.size() * sizeof(int), indicesArg.data(), type);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);

			this->vertices = verticesArg;
			this->indices = indicesArg;

		}

		void Mesh::render() {
			this->shader->use();
			if(texture) this->texture->bind();
			glBindVertexArray(this->VAO);
			glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}
	}
}