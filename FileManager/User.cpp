#include "User.h"
using namespace std;

/*
 * �û���Ĺ��캯��
 * ���û������û��ĸ�Ŀ¼��ʼ��
 */
User::User(const string& username)
    : username(username), rootDirectory(make_shared<Directory>(username)) {}

/*
 * ��ȡ�û����ĺ���
 */
string User::getUsername() {
    return username;
}