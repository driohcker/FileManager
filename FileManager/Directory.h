#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <unordered_map>
#include <memory>
#include "File.h" // 包含 File.h 以获取 File 类的完整定义

using namespace std;

class Directory {
public:
    string name;
    shared_ptr<Directory> parent;
    unordered_map<string, shared_ptr<File>> files;
    unordered_map<string, shared_ptr<Directory>> subdirectories;

    Directory(const string& name, shared_ptr<Directory> parent = nullptr);
};

#endif // DIRECTORY_H
