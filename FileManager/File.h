#ifndef FILE_H
#define FILE_H

#include <string>
#include <unordered_map>
using namespace std;

class File {
public:
    string name;
    string owner;
    unordered_map<string, bool> permissions;
    string content;
    bool isOpen;

    File(const string& name, const string& owner, const string& permissions);
};

#endif