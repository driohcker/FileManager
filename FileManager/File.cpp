#include "File.h"
using namespace std;

/*
 * 文件类的构造函数
 * 对文件名、所有者、内容和打开状态进行初始化
 * 对传入的权限进行识别
 */
File::File(const string& name, const string& owner, const string& permissions) 
    : name(name), owner(owner), content(""), isOpen(false) {
    this->permissions["read"] = permissions.find('r') != string::npos;
    this->permissions["write"] = permissions.find('w') != string::npos;
    this->permissions["execute"] = permissions.find('x') != string::npos;
}

string File::getName()
{
    return string();
}

void File::setName(string newname)
{
    this->name = newname;
}

void File::changePermission(string permissions)
{
    this->permissions["read"] = permissions.find('r') != string::npos;
    this->permissions["write"] = permissions.find('w') != string::npos;
    this->permissions["execute"] = permissions.find('x') != string::npos;
}



