#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <string>
#include <vector>
#include "FileSystem.h"

using namespace std;

class CommandProcessor {
public:
    FileSystem& filesystem;

    CommandProcessor(FileSystem& filesystem);
    void execute(const string& command);

private:
    void createFile(const string& filename, const string& permissions);//增加文件
    void openFile(const string& filename);//打开文件
    void closeFile(const string& filename);//关闭文件
    void deleteFile(const string& filename);//删除文件
    void readFile(const string& filename);//读取文件
    void writeFile(const string& filename, const string& content);//写文件
    void copyFile(const string& srcFilename, const string& destFilename);//复制文件
    void listDirectory();//显示文件列表
    void changeDirectory(const string& path);//更改当前目录
    void createDirectory(const string& dirname);//创建目录
    void printAllDirectory();//显示所有文件
    void helpList();//help清单

    vector<string> splitCommand(const string& command);//分析命令
};

#endif // COMMANDPROCESSOR_H
