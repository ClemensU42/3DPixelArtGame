//
// Created by Clemens on 25.11.2022.
//

#define MAGIC_NUMBER 0x61736574
#include <vector>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include "Engine/Assets/AssetManager.h"

namespace Engine {
	namespace Asset {

		char *buffer;
		size_t bufferLength = 1024; // starting size of read buffer is 1024 bytes / 1 kb

		AssetHeader header{};
		std::vector<AssetEntry> assetEntries;

		std::unordered_map<std::string, Asset> assetMap;

		std::ifstream file;

		uint64_t dataBegin = 0;

		void ensureBufferSize(size_t size) {
			while (bufferLength < size) {
				buffer = (char *) realloc(buffer, bufferLength * 2);
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

				std::string identifier = readString(entry.entrySize - 18);
				entry.identifier = identifier;
				assetEntries.push_back(entry);
			}
			dataBegin = file.tellg();
		}

		void loadAsset(std::string identifier) {

		}

		void unloadAsset(std::string Identifier) {

		}

		void unloadAllAssets() {

		}

		Asset getAsset(std::string identifier) {

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
			ensureBufferSize(length + 1); // + 1 to accommodate the \0
			file.read(buffer, length);
			buffer[length] = '\0';
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