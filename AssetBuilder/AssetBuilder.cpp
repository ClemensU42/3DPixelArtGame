//
// Created by Clemens on 23.11.2022.
//

#include <vector>
#include <iostream>
#include <filesystem>

struct assetHeader{
	uint64_t magicNum;
	uint64_t filesize;
	uint64_t assetListSize;
	uint64_t dataListSize;
	uint32_t assetListEntryAmount;
};

struct assetEntry{
	uint16_t entrySize;
	uint64_t dataSize;
	uint64_t dataPointer;
	const char* identifier;
};

struct assetList{
	assetEntry* entries;
};

struct dataList{
	uint8_t* data;
};

int main(int argc, const char** argv){
	if(argc != 2){
		std::cout << "Wrong arguments provided!" << std::endl;
		return -1;
	}
	return 0;
}