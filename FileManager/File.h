#ifndef FILE_H
#define FILE_H

#include <string>
#include <unordered_map>
using namespace std;

class File {
public:
    string name; //�ļ���
    string filePath;
    time_t createTime;
    time_t changeTime = NULL;
    string owner; //������
    unordered_map<string, bool> permissions; //�ļ�Ȩ��
    string content; //����
    bool isOpen; //��״̬

    File(const string& name, const string& owner, const string& permissions);
    string getName();
    void setName(string newname);
    void changePermission(string permissions);
    void changeContent() {}

};

#endif