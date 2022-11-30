//
// Created by Clemens on 25.11.2022.
//

#define MAGIC_NUMBER 0x61736574
#include <vector>
#include <regex>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include "Engine/Assets/AssetManager.h"

namespace Engine {
	namespace Asset {

		char *buffer;
		size_t bufferLength = 1024; // starting size of read buffer is 1024 bytes / 1 kb

		AssetHeader header{};

		std::unordered_map<std::string, Asset> assetMap;
		std::unordered_map<std::string, AssetEntry> assetEntries;

		std::ifstream file;

		int64_t dataBegin = 0;

		void ensureBufferSize(size_t size) {
			while (bufferLength < size) {
				buffer = (char *) realloc(buffer, bufferLength * 2);
				if(buffer == NULL){
					std::cout << "Error requesting memory for asset manager buffer!" << std::endl;
					exit(-1);
				}
				bufferLength *= 2;
			}
		}

		void openAssetFile(const char *path) {
			buffer = (char*)malloc(bufferLength);
			file.open(path, std::ios::in | std::ios::binary);
			header = readHeader();
			for(int i = 0; i < header.assetListEntryAmount; i++){
				AssetEntry entry{};
				entry.entrySize = readUint16_t();
				entry.dataSize = readUint64_t();
				entry.dataPointer = readUint64_t();

				std::string identifier = readString(entry.entrySize - 17);
				entry.identifier = identifier;
				assetEntries.insert(std::pair<std::string, AssetEntry>(identifier, entry));
			}
			dataBegin = file.tellg();
		}

		void loadAsset(const std::string& identifier) {
			std::cout << "loading asset: " << identifier << std::endl;
			AssetEntry entry = assetEntries[identifier];
			Asset asset{};
			asset.assetSize = entry.dataSize;
			asset.data = malloc(asset.assetSize);
			file.seekg(dataBegin + entry.dataPointer);
			file.read(static_cast<char*>(asset.data), asset.assetSize);
			assetMap.insert(std::pair<std::string, Asset>(identifier, asset));
		}

		void unloadAsset(const std::string& identifier) {
			free(assetMap[identifier].data);
			assetMap.erase(identifier);
		}

		void unloadAllAssets() {
			for(std::pair<std::string, Asset> p : assetMap){
				free(p.second.data);
			}
			assetMap.clear();
		}

		Asset getAsset(const std::string& identifier) {
			if(assetMap.find(identifier) == assetMap.end()){
				loadAsset(identifier);
			}
			return assetMap[identifier];
		}

		std::string readAssetAsString(const Asset* asset){
			return {(char*)asset->data, 0, asset->assetSize};
		}

		uint8_t readUint8_t() {
			ensureBufferSize(1);
			file.read(buffer, 1);
			return ((uint8_t *) buffer)[0];
		}

		uint16_t readUint16_t() {
			ensureBufferSize(2);
			file.read(buffer, 2);
			return ((uint16_t *) buffer)[0];
		}

		uint32_t readUint32_t() {
			ensureBufferSize(4);
			file.read(buffer, 4);
			return ((uint32_t *) buffer)[0];
		}

		uint64_t readUint64_t() {
			ensureBufferSize(8);
			file.read(buffer, 8);
			return ((uint64_t *) buffer)[0];
		}

		std::string readString(int64_t length) {
			ensureBufferSize(length);
			char c;
			int i = 0;
			file.read(&c, 1);
			while(c){
				buffer[i++] = c;
				file.read(&c, 1);
			}
			buffer[i] = '\0';
			std::string result = buffer;
			return result;
		}

		AssetHeader readHeader() {
			ensureBufferSize(sizeof(AssetHeader));
			file.read(buffer, sizeof(AssetHeader));
			return ((AssetHeader*)buffer)[0];
		}

	}
}