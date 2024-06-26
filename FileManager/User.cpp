#include "User.h"
using namespace std;

/*
 * 用户类的构造函数
 * 对用户名和用户的根目录初始化
 */
User::User(const string& username)
    : username(username), rootDirectory(make_shared<Directory>(username)) {}

/*
 * 获取用户名的函数
 */
string User::getUsername() {
    return username;
}