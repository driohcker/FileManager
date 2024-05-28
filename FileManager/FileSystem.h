#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <unordered_map>
#include <memory>
#include "User.h"

using namespace std;

class FileSystem {
public:
    unordered_map<string, shared_ptr<User>> users;
    shared_ptr<User> currentUser;

    void addUser(const string& username);
    void login(const string& username);
    void logout();
};

#endif