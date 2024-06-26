#include "Index.h"
#include <string>
#include <unordered_map>
#include <chrono>
#include <ctime>
using namespace std;

void Index::addRegister(string fileName, string filePath)
{
	indexRegisters.push_back({ fileName,filePath,chrono::system_clock::to_time_t(chrono::system_clock::now())});
	
}

void Index::deleteRegister(string fileName)
{
	for (int i = 0; i < indexRegisters.size(); i++) {
		if (fileName == indexRegisters[i].fileName) {
			indexRegisters.erase(indexRegisters.begin() + i);
			return;
		}
	}
}

void Index::changeRegister(string fileName, string newFileName, string newFilePath)
{
	for (int i = 0; i < indexRegisters.size(); i++) {
		if (fileName == indexRegisters[i].fileName) {
			if (newFileName != "") indexRegisters[i].fileName = newFileName;
			indexRegisters[i].filePath = newFilePath;
			indexRegisters[i].changeTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
		}
		
	}
}

Index::Index()
{
}

