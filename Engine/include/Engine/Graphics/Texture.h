//
// Created by Clemens on 09.12.2022.
//

#ifndef PIXELART3DGAME_TEXTURE_H
#define PIXELART3DGAME_TEXTURE_H

#include "Engine/Assets/AssetManager.h"

namespace Engine{
	namespace Graphics{
		class Texture{
		public:
			int width;
			int height;
			int channelCount;
			unsigned int gpuTexture;
			uint8_t* data;

		public:
			void loadFromAsset(Engine::Asset::Asset asset);
			void bind() const;
		};
	}
}

#endif //PIXELART3DGAME_TEXTURE_H
