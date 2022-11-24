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

int main(int argc, const char** argv){
	if(argc != 2){
		std::cout << "Wrong arguments provided!" << std::endl;
		return -1;
	}
	return 0;
}