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
	std::string identifier;
};

struct assetList{
	assetEntry* entries;
};

struct dataList{
	uint8_t* data;
};

std::vector<std::string> files;

void collectFilesFromDir(std::string dir){
	for(const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(dir)){
		if(std::filesystem::is_directory(entry.path())) {
			collectFilesFromDir(entry.path().string());
		} else {
			files.push_back(entry.path().string());
		}
	}
}

// argv[1] is the output file
// argv[2] is the asset directory
int main(int argc, const char** argv){
	if(argc != 3){
		std::cout << "Wrong arguments provided!" << std::endl;
		return -1;
	}

	std::cout << "Collecting files" << std::endl;
	std::string path = argv[2];
	collectFilesFromDir(path);


	return 0;
}