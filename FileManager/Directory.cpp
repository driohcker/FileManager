#include "Directory.h"

using namespace std;
/*
 * Ŀ¼��Ĺ��캯��
 * �����ֺ͸��ڵ��ʼ��
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
