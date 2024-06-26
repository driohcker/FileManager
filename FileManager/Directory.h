#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <unordered_map>
#include <memory>
#include "File.h" // 包含 File.h 以获取 File 类的完整定义
#include "Index.h"

using namespace std;

class Directory {
public:
    Index index;
    string name;
    string path;
    time_t createTime;
    time_t _changeTime = NULL;
    string owner;


    shared_ptr<Directory> parent;
    unordered_map<string, shared_ptr<File>> files;
    unordered_map<string, shared_ptr<Directory>> subdirectories;

    Directory(const string& name, shared_ptr<Directory> parent = nullptr);
    Index& getIndex();
    string getname();
    void initCreateTime(time_t createTime);
    void setChangeTime(time_t changeTime);
};

#endif // DIRECTORY_H
