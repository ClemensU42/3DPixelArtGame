//
// Created by Clemens on 22.11.2022.
//

#ifndef PIXELART3DGAME_MESH_H
#define PIXELART3DGAME_MESH_H

#include <vector>

namespace Engine{
	namespace Graphics{
		class Mesh{
		public:
			unsigned int VBO;
			unsigned int VAO;

		public:
			void loadMeshFromVectors(std::vector<float> vertices, std::vector<int> indices);
			void render();

		};

		enum MESH_TYPE{
			STATIC,
			DYNAMIC,
			STREAM
		};
	}
}

#endif //PIXELART3DGAME_MESH_H
