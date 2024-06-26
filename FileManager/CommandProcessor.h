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
    void createFile(const string& filename, const string& permissions);//�����ļ�
    void openFile(const string& filename);//���ļ�
    void closeFile(const string& filename);//�ر��ļ�
    void deleteFile(const string& filename);//ɾ���ļ�
    void readFile(const string& filename);//��ȡ�ļ�
    void writeFile(const string& filename, const string& content);//д�ļ�
    void copyFile(const string& srcFilename, const string& destFilename);//�����ļ�
    void listDirectory();//��ʾ�ļ��б�
    void changeDirectory(const string& path);//���ĵ�ǰĿ¼
    void createDirectory(const string& dirname);//����Ŀ¼
    void printAllDirectory();//��ʾ�����ļ�
    void helpList();//help�嵥

    vector<string> splitCommand(const string& command);//��������
};

#endif // COMMANDPROCESSOR_H
