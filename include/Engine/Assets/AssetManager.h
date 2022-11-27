//
// Created by Clemens on 25.11.2022.
//

#ifndef PIXELART3DGAME_ASSETMANAGER_H
#define PIXELART3DGAME_ASSETMANAGER_H

#include <cstdint>
#include <string>

namespace Engine{
	namespace Asset{
#pragma pack(push, 1)
		struct AssetHeader{
			uint64_t magicNum;
			uint64_t filesize;
			uint64_t assetListSize;
			uint64_t dataListSize;
			uint32_t assetListEntryAmount;
		};
#pragma pack(pop)
#pragma pack(push, 1)
		struct AssetEntry{
			uint16_t entrySize;
			uint64_t dataSize;
			uint64_t dataPointer;
			std::string identifier;
		};
#pragma pack(pop)

		struct Asset{
			uint64_t assetSize;
			void* data;
		};


		void openAssetFile(const char* path);
		void loadAsset(const std::string& identifier);
		void unloadAsset(const std::string& identifier);
		void unloadAllAssets();
		Asset getAsset(const std::string& identifier);

		uint8_t readUint8_t();
		uint16_t readUint16_t();
		uint32_t readUint32_t();
		uint64_t readUint64_t();
		std::string readString(int64_t length);

		AssetHeader readHeader();
	}
}

#endif //PIXELART3DGAME_ASSETMANAGER_H
