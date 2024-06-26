#include "File.h"
using namespace std;

/*
 * �ļ���Ĺ��캯��
 * ���ļ����������ߡ����ݺʹ�״̬���г�ʼ��
 * �Դ����Ȩ�޽���ʶ��
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



