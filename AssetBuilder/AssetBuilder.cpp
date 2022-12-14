//
// Created by Clemens on 23.11.2022.
//

#include <vector>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string.h>

#define MAGIC_NUMBER 0x61736574

#pragma pack(push, 1)
struct assetHeader{
	uint64_t magicNum;
	uint64_t filesize;
	uint64_t assetListSize;
	uint64_t dataListSize;
	uint32_t assetListEntryAmount;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct assetEntry{
	uint16_t entrySize;
	uint64_t dataSize;
	uint64_t dataPointer;
	std::string* identifier;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct assetList{
	assetEntry* entries;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct dataList{
	uint8_t* data;
};
#pragma pack(pop)

std::vector<std::string> files;
const char* assetDirName = R"(Assets\)";
const std::string textFiles[] = {".txt", ".json", ".frag", ".vert"};

void collectFilesFromDir(std::string dir){
	for(const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(dir)){
		if(std::filesystem::is_directory(entry.path())) {
			collectFilesFromDir(entry.path().string());
		} else {
			files.push_back(entry.path().string());
		}
	}
}

void writeEntryToFile(std::fstream* stream, assetEntry* entry){
	stream->write(reinterpret_cast<char*>(&entry->entrySize), 2);
	stream->write(reinterpret_cast<char*>(&entry->dataSize), 8);
	stream->write(reinterpret_cast<char*>(&entry->dataPointer), 8);
	stream->write(entry->identifier->c_str(), entry->identifier->size()+1);
}

// argv[1] is the output file
// argv[2] is the asset directory
int main(int argc, const char** argv){
	if(argc != 3){
		std::cout << "Wrong arguments provided!" << std::endl;
		return -1;
	}

	assetHeader header{};
	std::vector<assetEntry> assets;
	dataList data{};

	std::cout << "Collecting files..." << std::endl;
	std::string path = argv[2];
	collectFilesFromDir(path);

	std::cout << "Creating entries..." << std::endl;
	for(int i = 0; i < files.size(); i++){
		assetEntry ent{};
		ent.dataSize = std::filesystem::file_size(files[i]);
		std::cout << ent.dataSize << std::endl;
		ent.identifier = &files[i];
		ent.entrySize = sizeof(uint16_t) + sizeof(uint64_t) * 2;
		assets.push_back(ent);
	}

	std::cout << "Creating header..." << std::endl;
	header.magicNum = MAGIC_NUMBER;
	header.assetListEntryAmount = files.size();
	header.dataListSize = 0;
	header.assetListSize = 0;
	for(int j = 0; j < header.assetListEntryAmount; j++){
		header.dataListSize += assets[j].dataSize;
	}


	std::cout << "Collecting Data..." << std::endl;
	data.data = (uint8_t*)malloc(header.dataListSize);
	uint64_t dataPos = 0;
	for(int j = 0; j < header.assetListEntryAmount; j++){
		if(j == 0)
			assets[j].dataPointer = 0;
		else
			assets[j].dataPointer = assets[j-1].dataPointer + assets[j-1].dataSize;
		std::ifstream ifs = std::ifstream(*assets[j].identifier, std::ios::binary);
		if(ifs.is_open()){
			uint8_t c;
			c = ifs.get();
			while(!ifs.eof()){
				//if(data.data[dataPos - 1] != 0x0D && c != 0x0D)
					data.data[dataPos++] = c;
				c = ifs.get();
			}
			ifs.close();
		} else {
			std::cout << assets[j].identifier << " could not be opened!!! Aborting..." << std::endl;
			free(data.data);
			return -1;
		}
	}

	std::cout << "Updating Identifiers and Header..." << std::endl;
	for(int i = 0; i < assets.size(); i++){
		size_t pos = assets[i].identifier->find(assetDirName) + strlen(assetDirName);
		assets[i].identifier->erase(0, pos);
		assets[i].entrySize += assets[i].identifier->size()+1;
		header.assetListSize += assets[i].entrySize;
	}
	header.filesize = sizeof(assetHeader) + header.dataListSize + header.assetListSize;

	std::cout << "Creating asset file..." << std::endl;
	std::fstream assetFile(argv[1], std::ios::out | std::ios::binary);
	assetFile.write(reinterpret_cast<char*>(&header), sizeof(header));
	for(int j = 0; j < header.assetListEntryAmount; j++){
		writeEntryToFile(&assetFile, &assets[j]);
	}
	assetFile.write(reinterpret_cast<char*>(data.data), header.dataListSize);
	assetFile.close();

	std::cout << "Done!\nCreated asset file at: " << argv[1] << std::endl;
	free(data.data);
	return 0;
}