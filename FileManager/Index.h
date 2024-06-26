#ifndef INDEX_H
#define INDEX_H
#include <iostream>
#include <vector>
using namespace std;

struct indexRegister {
	string fileName;
	string filePath;
	time_t createTime;
	time_t changeTime = NULL;

};
class Index {
private:
	vector<indexRegister> indexRegisters;

public:
	void addRegister(string fileName,string filePath);
	void deleteRegister(string fileName);
	void changeRegister(string fileName, string newFileName, string newFilePath);
	Index();
};

#endif 

