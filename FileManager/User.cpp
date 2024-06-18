#include "User.h"
using namespace std;

User::User(const string& username)
    : username(username), rootDirectory(make_shared<Directory>(username)) {}

string User::getUsername() {
    return username;
}