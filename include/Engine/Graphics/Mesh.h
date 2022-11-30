//
// Created by Clemens on 22.11.2022.
//

#ifndef PIXELART3DGAME_MESH_H
#define PIXELART3DGAME_MESH_H

#include <vector>
#include "Engine/Graphics/Shader.h"

namespace Engine{
	namespace Graphics{
		class Mesh{
		public:
			unsigned int VBO;
			unsigned int VAO;
			unsigned int EBO;
			Engine::Graphics::Shader* shader;

			std::vector<float> vertices;
			std::vector<unsigned int> indices;

		public:
			void loadMeshFromVectors(std::vector<float> verticesArg, std::vector<unsigned int> indicesArg, unsigned int type);
			void render();

		};
	}
}

#endif //PIXELART3DGAME_MESH_H
