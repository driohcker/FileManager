#ifndef USER_H
#define USER_H

#include <string>
#include <memory>
#include "Directory.h"

using namespace std;

class User {
public:
    string username;
    shared_ptr<Directory> rootDirectory;

    User(const string& username);
    string getUsername();
};

#endif