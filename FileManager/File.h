#ifndef FILE_H
#define FILE_H

#include <string>
#include <unordered_map>
using namespace std;

class File {
public:
    string name; //文件名
    string filePath;
    time_t createTime;
    time_t changeTime = NULL;
    string owner; //所有者
    unordered_map<string, bool> permissions; //文件权限
    string content; //内容
    bool isOpen; //打开状态

    File(const string& name, const string& owner, const string& permissions);
    string getName();
    void setName(string newname);
    void changePermission(string permissions);
    void changeContent() {}

};

#endif