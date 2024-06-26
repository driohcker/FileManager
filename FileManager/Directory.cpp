#include "Directory.h"

using namespace std;
/*
 * 目录类的构造函数
 * 对名字和父节点初始化
 */
Directory::Directory(const string& name, shared_ptr<Directory> parent, string path, time_t createTime)
    : name(name), parent(parent), path(path), createTime(createTime){
     
}

Index& Directory::getIndex()
{
    return index;
}

string Directory::getname()
{
    return name;
}

void Directory::setChangeTime(time_t changeTime)
{
    
}
